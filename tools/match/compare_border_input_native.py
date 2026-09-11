#!/usr/bin/env python3
"""Compare editor state and callback order with the original InputText routine.

Keyboard input, OK-widget updates, layout and teardown are explicit harness
seams. This diagnostic contributes no normalized or linked-game matching credit.
"""
from __future__ import annotations

import argparse
import fcntl
import hashlib
import json
import os
import re
import shutil
import struct
from pathlib import Path

from compare_loaders_native import verify_source_link
from compare_quaternion_native import checked_run
from compare_sbend_native import digest, make_oracle, verify_oracle_link
from link_path_math import support_inputs
from snail.match import (
    DEFAULT_MATCH_ROOT, compile_scratch, extract_object_function,
    load_scratch_config, object_function_fingerprint, parse_coff_object,
    run_match, scratch_dependency_sha256,
)
from snail.symbols import DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH, REPO_ROOT, load_function_symbol_manifest

FUNCTION = "border_input_text"
FIXTURE = struct.Struct("<10I64s")
HEADER = struct.Struct("<4I")
WIDGET_SIZE = 0x724
EVENT_BYTES = 4 * 5 * 4
RECORD_SIZE = 8 + EVENT_BYTES + 2 * WIDGET_SIZE


def file_digest(path: Path) -> str:
    with path.open("rb") as stream:
        return hashlib.file_digest(stream, "sha256").hexdigest()


def prepare_fixtures(path: Path) -> dict:
    texts = [b"", b"A", b"abc", b"a b", b"ab>cde", b"a>>b", b"a>b>", b" 12.3 ", b"a\x80b"]
    keys = [0, *range(1, 11), 32, 44, 46, 48, 65, 122, 128, 255]
    modes = [0, 1, 2, 3, 4, 8, 12, 15]
    blinks = [
        (0x00000000, 0x00000000, 0),
        (0x3f800000, 0x00000000, 1),  # exactly one: no toggle
        (0x3f733333, 0x3dcccccd, 1),  # crosses one
        (0xbf000000, 0x3e000000, 0),
        (0x80000000, 0x00000000, 1),
        (0x7fc12345, 0x3e800000, 2),  # quiet NaN and a noncanonical visible value
    ]
    rows = []
    for text in texts:
        for cursor in range(len(text) + 1):
            for mode in modes:
                for key in keys:
                    for blink, step, visible in blinks:
                        case_id = len(rows)
                        capacity = [len(text), len(text) + 1, 64][case_id % 3]
                        flags = 0xa0202012 | (0x08000000 if case_id % 5 == 0 else 0)
                        controls = case_id % 4 | (4 if case_id % 7 == 0 else 0)
                        rows.append(FIXTURE.pack(case_id, key, mode, cursor, capacity,
                                                 blink, step, visible, flags, controls,
                                                 text.ljust(64, b"\0")))
    path.write_bytes(struct.pack("<III", 0x31464942, len(rows), FIXTURE.size) + b"".join(rows))
    return {
        "cases": len(rows), "record_bytes": FIXTURE.size, "sha256": file_digest(path),
        "texts_hex": [text.hex() for text in texts], "keys": keys, "input_modes": modes,
        "blink_bit_patterns_and_visibility": blinks,
        "capacity_cycle": "text length; text length plus one; 64",
        "submit_requested": "case_id divisible by five",
        "initial_ok_triggered": "case_id divisible by seven",
        "ai_action_cycle": ["no change", "set OK triggered", "toggle source filter bit 0", "set source submit requested"],
        "fill_patterns": {"subject": [0, 0xa5], "ok_widget": [0, 0x3c]},
        "limitations": "Short terminated strings with one cursor marker; no leading separator, overflowing buffer, dangling pointer or arbitrary UI behavior. Two pointer identities are checked then canonicalized in the complete subject snapshot. Layout and teardown are nonmutating callback seams.",
    }


def compare_outputs(left: Path, right: Path) -> dict:
    """Check framing, callback records and every byte of both complete objects."""
    differences = []
    compared = 0
    event_totals = [0, 0]
    with left.open("rb") as a, right.open("rb") as b:
        ha, hb = a.read(HEADER.size), b.read(HEADER.size)
        if len(ha) != HEADER.size or ha != hb:
            raise ValueError("missing or unequal output headers")
        magic, cases, size, widget_size = HEADER.unpack(ha)
        if magic != 0x314f4942 or not 0 < cases <= 100000 or size != RECORD_SIZE or widget_size != WIDGET_SIZE:
            raise ValueError("invalid output format")
        expected_size = HEADER.size + cases * RECORD_SIZE
        if left.stat().st_size != expected_size or right.stat().st_size != expected_size:
            raise ValueError("truncated or trailing output bytes")
        for case in range(cases):
            ra, rb = a.read(size), b.read(size)
            for side, record in enumerate((ra, rb)):
                case_id, events = struct.unpack_from("<II", record)
                if case_id != case or not 1 <= events <= 4:
                    raise ValueError("invalid case identity or event count")
                if struct.unpack_from("<I", record, 8)[0] != 1:
                    raise ValueError("keyboard callback must occur first")
                kinds = tuple(struct.unpack_from("<I", record, 8 + i * 20)[0] for i in range(events))
                if kinds not in {(1, 3), (1, 2, 3), (1, 2, 3, 4)}:
                    raise ValueError("invalid callback order")
                if any(record[8 + events * 20:8 + EVENT_BYTES]):
                    raise ValueError("nonzero unused callback slots")
                tokens = struct.unpack_from("<II", record, 8 + EVENT_BYTES + 0x2c4)
                if tokens != (0xf00d0001, 0xf00d0002):
                    raise ValueError("invalid canonical pointer identities")
                event_totals[side] += events
            compared += len(ra)
            if ra != rb:
                changed = [i for i, (x, y) in enumerate(zip(ra, rb)) if x != y]
                differences.append({"case": case, "different_bytes": len(changed),
                                    "first_record_offsets": changed[:16],
                                    "source": [ra[i] for i in changed[:16]],
                                    "candidate": [rb[i] for i in changed[:16]]})
        if a.read(1) or b.read(1):
            raise ValueError("trailing output records")
    return {"equal": not differences, "cases": cases, "object_regions": cases * 2,
            "event_totals": event_totals,
            "compared_record_bytes": compared, "compared_object_bytes": cases * 2 * WIDGET_SIZE,
            "differing_cases": len(differences), "differences": differences[:16]}


def compare(runtime: Path, out: Path) -> dict:
    receipt_path = out / "comparison.json"
    receipt_path.unlink(missing_ok=True)
    runner_name = os.environ.get("WIBO") or str(DEFAULT_MATCH_ROOT / "bin/wibo")
    runner = Path(shutil.which(runner_name) or runner_name).resolve(strict=True)
    linker = DEFAULT_MATCH_ROOT / "compilers/msvc6.5/Bin/LINK.EXE"
    manifest = load_function_symbol_manifest(DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH)
    native_path = REPO_ROOT / manifest.primary_target
    if file_digest(native_path) != manifest.unwrapped_sha256:
        raise ValueError("native image differs from matching manifest")
    config = load_scratch_config(DEFAULT_MATCH_ROOT / "scratches" / FUNCTION)
    if config.compiler != "msvc6.5":
        raise ValueError("diagnostic requires the current VC6 profile")
    fixed = [runtime, runner, linker, native_path, Path(__file__).resolve(),
             DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
             DEFAULT_MATCH_ROOT / "compare_loaders_native.py",
             DEFAULT_MATCH_ROOT / "compare_sbend_native.py",
             DEFAULT_MATCH_ROOT / "compare_quaternion_native.py",
             DEFAULT_MATCH_ROOT / "link_path_math.py",
             REPO_ROOT / "src/snail/match.py", REPO_ROOT / "src/snail/match_link.py",
             REPO_ROOT / "src/snail/symbols.py",
             REPO_ROOT / "analysis/symbols/gameplay-references.json"]
    identities = {str(p): file_digest(p) for p in fixed}
    fixture_path = out / "fixtures.bin"
    fixtures = prepare_fixtures(fixture_path)
    identities[str(fixture_path)] = fixtures["sha256"]
    dependencies = scratch_dependency_sha256(config)
    source_object = out / "border_input_text.obj"
    source_object.write_bytes(compile_scratch(config).read_bytes())
    obj = parse_coff_object(source_object.read_bytes())
    function = extract_object_function(obj, config.symbol or config.function)
    match = run_match(obj_path=source_object, function_name=FUNCTION, image_path=native_path,
                      manifest=manifest, symbol_name=config.symbol, end_va=config.end_va)
    if match.masked_operand_audit.problem_count or match.masked_operand_audit.ok_count != 8:
        raise ValueError("editor must have all eight references clean")
    record = {"function": FUNCTION, "object_name": source_object.name, "symbol": function.name,
              "match_ratio": match.ratio, "compiler": config.compiler, "cflags": config.cflags,
              "source_sha256": file_digest(config.directory / "scratch.cpp"),
              "config_sha256": file_digest(config.directory / "scratch.conf"),
              "dependency_sha256": dependencies, "code_sha256": object_function_fingerprint(function),
              "object_sha256": file_digest(source_object)}
    fixture_source = DEFAULT_MATCH_ROOT / "link/border_input_smoke.cpp"
    fixture_inputs = support_inputs(fixture_source)
    fixture_object = out / "border_input_smoke.obj"
    checked_run([str(DEFAULT_MATCH_ROOT / "cl.sh"), "/c", "/O2", "/G5", "/W3",
                 f"/FoZ:{fixture_object}", f"Z:{fixture_source}"], out / "fixture.compile.log",
                env={**os.environ, "MSVC_VER": "msvc6.5"})
    native_object = out / "border_input_text.native.obj"
    oracle = make_oracle(native_object, function_name=FUNCTION, source_object=source_object)
    for path in (source_object, fixture_object, native_object):
        identities[str(path)] = file_digest(path)
    results = {}
    for label, implementation in [("source", source_object), ("native", native_object)]:
        exe, mapping = out / f"{label}.exe", out / f"{label}.map"
        for path in (exe, mapping):
            path.unlink(missing_ok=True)
        options = ["/nologo", "/subsystem:console", "/entry:mainCRTStartup", "/nodefaultlib",
                   "/opt:noref", "/debug", "/debugtype:coff", "/pdb:none", "/incremental:no",
                   f"/out:Z:{exe}", f"/map:Z:{mapping}", f"Z:{implementation}",
                   f"Z:{fixture_object}", f"Z:{runtime}"]
        if any('"' in s or "\n" in s for s in options):
            raise ValueError("invalid linker path")
        rsp = out / f"{label}.rsp"
        rsp.write_text("\n".join(f'"{s}"' for s in options) + "\n")
        checked_run([str(runner), str(linker), f"@Z:{rsp}"], out / f"{label}.link.log")
        if label == "source":
            linked_proof = verify_source_link(exe, mapping, [source_object, fixture_object], [record], None)
        else:
            linked_proof = verify_oracle_link(exe, mapping, native_object, oracle)
            oracle["link_verification"] = linked_proof
        output = out / f"{label}.bin"
        output.unlink(missing_ok=True)
        run = checked_run([str(runner), str(exe), f"Z:{fixture_path}", f"Z:{output}"],
                          out / f"{label}.run.log", timeout=60)
        summary = re.fullmatch(r"border-input cases=(\d+) events=(\d+)\s*", run.stdout)
        if summary is None or int(summary[1]) != fixtures["cases"]:
            raise ValueError("incomplete fixture run")
        results[label] = {"stdout": run.stdout, "cases": int(summary[1]), "events": int(summary[2]),
                          "output_sha256": file_digest(output), "link_verification": linked_proof}
        for path in (exe, mapping, rsp, output):
            identities[str(path)] = file_digest(path)
    comparison = compare_outputs(out / "source.bin", out / "native.bin")
    if (not comparison["equal"] or comparison["cases"] != fixtures["cases"]
            or comparison["event_totals"] != [results[label]["events"] for label in ("source", "native")]):
        (out / "differences.json").write_text(json.dumps(comparison, indent=2) + "\n")
        raise ValueError("source and original editor behavior differ")
    negative = out / "negative-one-byte.bin"
    shutil.copyfile(out / "native.bin", negative)
    changed_offset = HEADER.size + 8 + EVENT_BYTES + 0x2cc
    with negative.open("r+b") as stream:
        stream.seek(changed_offset)
        byte = stream.read(1)
        stream.seek(changed_offset)
        stream.write(bytes([byte[0] ^ 1]))
    negative_result = compare_outputs(out / "source.bin", negative)
    if negative_result["equal"] or negative_result["differing_cases"] != 1 or negative_result["differences"][0]["different_bytes"] != 1:
        raise ValueError("one-byte negative control was not isolated")
    if scratch_dependency_sha256(config) != dependencies or file_digest(config.directory / "scratch.cpp") != record["source_sha256"]:
        raise ValueError("source dependencies changed during diagnostic")
    for path, expected in identities.items():
        if file_digest(Path(path)) != expected:
            raise ValueError(f"input changed: {path}")
    if support_inputs(fixture_source) != fixture_inputs:
        raise ValueError("harness dependencies changed during diagnostic")
    receipt = {"schema": 1, "function": FUNCTION, "source": record, "fixtures": fixtures,
               "results": results, "comparison": comparison, "negative_control": negative_result,
               "oracle": oracle, "input_identities": identities, "harness_dependencies": fixture_inputs,
               "harness_source": fixture_source.read_text(),
               "scope": "Complete subject and OK-widget bytes plus ordered callbacks at harness seams; two subject pointer identities are checked and normalized. This does not execute real layout, UI input or teardown and adds no matching credit."}
    receipt_path.write_text(json.dumps(receipt, indent=2) + "\n")
    return receipt


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--runtime-lib", type=Path, required=True)
    parser.add_argument("--out", type=Path, default=REPO_ROOT / "artifacts/match/border-input-native")
    args = parser.parse_args()
    out = args.out.resolve()
    out.mkdir(parents=True, exist_ok=True)
    with (out / ".lock").open("w") as lock:
        fcntl.flock(lock, fcntl.LOCK_EX)
        receipt = compare(args.runtime_lib.resolve(strict=True), out)
    print(json.dumps({"comparison": receipt["comparison"], "negative_control": receipt["negative_control"],
                      "receipt": str(out / "comparison.json")}, indent=2))


if __name__ == "__main__":
    main()
