#!/usr/bin/env python3
"""Compare recovered loaders against original routines on shipped archive files.

Only loader code is replaced in each native control. Resource and IO callbacks
are explicit harness seams; no source-matching or linked-game credit is given.
"""

from __future__ import annotations

import argparse
import fcntl
import json
import os
import re
import shutil
import struct
from pathlib import Path

import pefile
from compare_quaternion_native import checked_run
from compare_sbend_native import digest, make_oracle, verify_oracle_link
from link_path_math import support_inputs

from snail.archive import decode_bytes, parse_archive_index
from snail.match import (
    DEFAULT_MATCH_ROOT,
    CoffRelocation,
    compile_scratch,
    extract_object_function,
    load_scratch_config,
    object_function_fingerprint,
    parse_coff_object,
    run_match,
    scratch_dependency_sha256,
)
from snail.match_link import (
    externalize_coff_function,
    load_link_symbols,
    verify_relocated_bytes,
)
from snail.symbols import (
    DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
    REPO_ROOT,
    load_function_symbol_manifest,
)

TARGETS = (
    "load_segment_definitions",
    "load_level_definition_file",
    "copy_segment_definition_to_level_slot",
)
HELPERS = (
    "ascii_upper_if_lowercase",
    "find_case_insensitive_substring",
    "advance_to_next_crlf_line",
    "strings_equal_case_insensitive_path",
    "parse_next_signed_int",
    "parse_next_float32",
    "rstrcpy_checked_ascii",
    "store_color4f",
)


def fixed_name(name):
    encoded = name.encode("ascii")
    if len(encoded) >= 128 or b"\0" in encoded:
        raise ValueError("fixture name is too long or contains NUL")
    return encoded.ljust(128, b"\0")


def synthetic_files():
    """Safe parser controls for tags absent from the shipped segment corpus."""
    segment = (
        "ID:999\r\nName:'Loader control'\r\nData:\r\n@@@@@@@@@@\r\n"
        "@........@*3DModel=Probe.x (1.25,-2.5,3) Velocity=(.5,0,-1) "
        "Parcel=3,(4,5,6) NoFall Ring=PowerUp RingSpeed=2.5 JetPack=Off\r\n"
        "@........@Path=LOOPTHELOOP\r\n"
        "@........@Ring=None Ring=Normal Ring=Explode Ring=Slow\r\n"
        "@........@RingSpeed=+2.5\r\n@@@@@@@@@@\r\n"
    )
    level = (
        "Name:'Loader control'\r\nRandom:yes\r\nLength:auto\r\n"
        "Background:Probe.txt\r\nFringe:1 127 255\r\nTrack:r\r\n"
        "Parcels:9\r\nQuota:5\r\nSpeed:select\r\nGarbage:.25\r\nSalt:-.5\r\n"
        'Segments Begin:\r\nProbe.txt Angle=-30 Message="HELLO" '
        'Duration=2.5 Sample="Voice/probe.ogg"\r\nSegments End:\r\n'
        "First:\r\nProbe.txt\r\nLast:\r\nProbe.txt\r\n"
    )
    defaults = level
    for line in (
        "Random:yes",
        "Length:auto",
        "Fringe:1 127 255",
        "Track:r",
        "Speed:select",
        "Garbage:.25",
        "Salt:-.5",
    ):
        defaults = defaults.replace(line + "\r\n", "")
    return {
        "SEGMENTS/PROBE.TXT": segment.encode("ascii"),
        "LEVELS/PROBE.TXT": level.encode("ascii"),
        "LEVELS/PROBE DEFAULTS.TXT": defaults.encode("ascii"),
        "LEVELS/PROBE MISSING END.TXT": level.replace(
            "Segments End:", "Missing end:"
        ).encode("ascii"),
    }


def prepare_bundle(archive, output, native_image, image_base, include_synthetic=False):
    index = parse_archive_index(archive)
    raw = archive.read_bytes()
    pe = pefile.PE(data=native_image)
    # The exact NameCode consumer establishes this 63-slot native table.
    words = struct.unpack("<63I", pe.get_data(0x4A3D6C - image_base, 63 * 4))
    first_null = words.index(0)
    if any(words[first_null:]):
        raise ValueError("native path table is no longer a populated prefix")
    paths = [
        pe.get_string_at_rva(value - image_base).decode("ascii")
        for value in words[:first_null]
    ]
    bundle = bytearray(struct.pack("<I", len(paths)))
    bundle += b"".join(fixed_name(name) for name in paths)
    entries = [
        entry
        for entry in index.entries
        if entry.path.upper().startswith(("SEGMENTS/", "LEVELS/"))
    ]
    extra = synthetic_files() if include_synthetic else {}
    if any(e.path.upper() in extra for e in entries):
        raise ValueError("synthetic fixture shadows an archive member")
    bundle += struct.pack("<I", len(entries) + len(extra))
    files = []
    for entry in entries:
        data = decode_bytes(
            raw[entry.data_offset : entry.data_offset + entry.size], entry.data_offset
        )
        if not data or len(data) >= 4096:
            raise ValueError(f"fixture exceeds loader buffer: {entry.path}")
        bundle += fixed_name(entry.path) + struct.pack("<I", len(data)) + data
        files.append(
            {
                "path": entry.path,
                "data_offset": entry.data_offset,
                "size": len(data),
                "sha256": digest(data),
                "origin": "shipped",
            }
        )
    for name, data in extra.items():
        bundle += fixed_name(name) + struct.pack("<I", len(data)) + data
        files.append(
            {
                "path": name,
                "size": len(data),
                "sha256": digest(data),
                "origin": "synthetic",
            }
        )
    output.write_bytes(bundle)
    return {
        "archive_sha256": digest(raw),
        "files": files,
        "native_path_table_address": "0x4a3d6c",
        "path_names": paths,
        "bundle_sha256": digest(bundle),
    }


def decode_regions(data):
    """Strictly decode full regions; reject gaps hidden by invalid sparse spans."""
    offset = 0
    result = []
    while offset < len(data):
        if offset + 136 > len(data):
            raise ValueError("truncated region header")
        name = data[offset : offset + 128].split(b"\0", 1)[0].decode("ascii")
        size, fill = struct.unpack_from("<II", data, offset + 128)
        offset += 136
        if not 0 < size <= 0x260000 or fill > 255:
            raise ValueError("invalid region size or fill")
        region = bytearray([fill]) * size
        previous_end = 0
        while True:
            if offset + 4 > len(data):
                raise ValueError("truncated span offset")
            start = struct.unpack_from("<I", data, offset)[0]
            offset += 4
            if start == 0xFFFFFFFF:
                break
            if offset + 4 > len(data):
                raise ValueError("truncated span length")
            length = struct.unpack_from("<I", data, offset)[0]
            offset += 4
            if (
                not length
                or start < previous_end
                or start + length > size
                or offset + length > len(data)
            ):
                raise ValueError("invalid, overlapping or truncated span")
            region[start : start + length] = data[offset : offset + length]
            previous_end = start + length
            offset += length
        result.append((name, region))
    return result


def compare_regions(source, candidate):
    left, right = decode_regions(source), decode_regions(candidate)
    if [(n, len(b)) for n, b in left] != [(n, len(b)) for n, b in right]:
        raise ValueError("serialized region coverage differs")
    differences = []
    differing_regions = 0
    for index, ((name, a), (_, b)) in enumerate(zip(left, right, strict=True)):
        if a == b:
            continue
        differing_regions += 1
        positions = [i for i, (x, y) in enumerate(zip(a, b, strict=True)) if x != y]
        if len(differences) < 20:
            differences.append(
                {
                    "region": index,
                    "name": name,
                    "different_bytes": len(positions),
                    "first_offsets": positions[:16],
                    "source": [a[i] for i in positions[:16]],
                    "candidate": [b[i] for i in positions[:16]],
                }
            )
    return {
        "equal": differing_regions == 0,
        "regions": len(left),
        "compared_bytes": sum(len(b) for _, b in left),
        "differing_regions": differing_regions,
        "differences": differences,
    }


def verify_source_link(executable, map_path, objects, records, replaced, object_overrides=None):
    pe, symbols = load_link_symbols(executable, map_path)
    parsed = {obj.name: parse_coff_object(obj.read_bytes()) for obj in objects}
    symbols.bind_objects(parsed)
    mapped = pe.get_memory_mapped_image()
    verified = []
    object_overrides = object_overrides or {}
    for record in records:
        if record["function"] == replaced:
            continue
        owner = object_overrides.get(record["object_name"], record["object_name"])
        obj = parsed[owner]
        function = extract_object_function(obj, record["symbol"])
        symbol = next(s for s in obj.symbols if s.name == function.name)
        original = parse_coff_object((executable.parent / record["object_name"]).read_bytes())
        original_function = extract_object_function(original, record["symbol"])
        original_symbol = next(s for s in original.symbols if s.name == function.name)
        # Externalizing a callee changes its resolved reference metadata. The
        # retained caller's actual section, relocations and symbol must not change.
        if (
            object_function_fingerprint(original_function) != record["code_sha256"]
            or symbol != original_symbol
            or obj.sections[symbol.section_number - 1]
            != original.sections[original_symbol.section_number - 1]
        ):
            raise ValueError(f"retained source function changed: {record['function']}")
        relocations = tuple(
            CoffRelocation(
                r.virtual_address - symbol.value, r.symbol_index, r.relocation_type
            )
            for r in obj.sections[symbol.section_number - 1].relocations
            if symbol.value <= r.virtual_address < symbol.value + len(function.data)
        )
        address = symbols.resolve(function.name, owner)
        offset = address - pe.OPTIONAL_HEADER.ImageBase
        references = verify_relocated_bytes(
            function.data,
            mapped[offset : offset + len(function.data)],
            address,
            relocations,
            obj,
            symbols,
            owner,
        )
        verified.append(
            {
                "function": record["function"],
                "linked_address": address,
                "body_bytes": len(function.data),
                "references": references,
            }
        )
    return verified


def compare(runtime, archive, out, include_synthetic=False):
    receipt_path = out / "comparison.json"
    receipt_path.unlink(missing_ok=True)
    runner_name = os.environ.get("WIBO") or str(DEFAULT_MATCH_ROOT / "bin/wibo")
    runner = str(Path(shutil.which(runner_name) or runner_name).resolve(strict=True))
    linker = DEFAULT_MATCH_ROOT / "compilers/msvc6.5/Bin/LINK.EXE"
    manifest = load_function_symbol_manifest(DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH)
    native_path = REPO_ROOT / manifest.primary_target
    native_image = native_path.read_bytes()
    if digest(native_image) != manifest.unwrapped_sha256:
        raise ValueError("native image differs from matching manifest")
    fixed_inputs = [
        runtime,
        archive,
        Path(runner),
        linker,
        native_path,
        Path(__file__).resolve(),
        DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
        DEFAULT_MATCH_ROOT / "compare_sbend_native.py",
        DEFAULT_MATCH_ROOT / "compare_quaternion_native.py",
        REPO_ROOT / "src/snail/match.py",
        REPO_ROOT / "src/snail/match_link.py",
        REPO_ROOT / "src/snail/archive.py",
        REPO_ROOT / "src/snail/symbols.py",
        DEFAULT_MATCH_ROOT / "link_path_math.py",
        REPO_ROOT / "analysis/symbols/gameplay-references.json",
    ]
    identities = {str(p): digest(p.read_bytes()) for p in fixed_inputs}
    bundle = out / "files.bin"
    corpus = prepare_bundle(
        archive, bundle, native_image, manifest.image_base, include_synthetic
    )
    identities[str(bundle)] = digest(bundle.read_bytes())
    objects, records = [], []
    physical_objects, function_objects = {}, {}
    for name in (*TARGETS, *HELPERS):
        config = load_scratch_config(DEFAULT_MATCH_ROOT / "scratches" / name)
        if config.compiler not in {"msvc6.0", "msvc6.3", "msvc6.5"}:
            raise ValueError("loader diagnostic requires a supported VC6 profile")
        deps = scratch_dependency_sha256(config)
        compiled = compile_scratch(config).resolve()
        if compiled not in physical_objects:
            obj = out / f"{name}.obj"
            obj.write_bytes(compiled.read_bytes())
            physical_objects[compiled] = obj
            objects.append(obj)
        obj = physical_objects[compiled]
        function_objects[name] = obj
        match = run_match(
            obj_path=obj,
            function_name=name,
            image_path=native_path,
            manifest=manifest,
            symbol_name=config.symbol,
            end_va=config.end_va,
        )
        if name in HELPERS and (
            match.ratio != 1 or match.masked_operand_audit.problem_count
        ):
            raise ValueError(f"helper must be proof-grade exact: {name}")
        f = extract_object_function(
            parse_coff_object(obj.read_bytes()), config.symbol or config.function
        )
        records.append(
            {
                "function": name,
                "object_name": obj.name,
                "symbol": f.name,
                "match_ratio": match.ratio,
                "compiler": config.compiler,
                "cflags": config.cflags,
                "native_references_ok": match.masked_operand_audit.ok_count,
                "native_reference_debt": match.masked_operand_audit.problem_count,
                "source_sha256": digest(
                    (config.directory / "scratch.cpp").read_bytes()
                ),
                "config_sha256": digest(
                    (config.directory / "scratch.conf").read_bytes()
                ),
                "dependency_sha256": deps,
                "code_sha256": object_function_fingerprint(f),
                "object_sha256": digest(obj.read_bytes()),
            }
        )
    fixture_inputs = {}
    for name in ("loader_smoke", "loader_crt_compat"):
        source = DEFAULT_MATCH_ROOT / "link" / f"{name}.cpp"
        fixture_inputs[name] = support_inputs(source)
        obj = out / f"{name}.obj"
        checked_run(
            [
                str(DEFAULT_MATCH_ROOT / "cl.sh"),
                "/c",
                "/O2",
                "/G5",
                "/W3",
                f"/FoZ:{obj}",
                f"Z:{source}",
            ],
            out / f"{name}.compile.log",
            env={**os.environ, "MSVC_VER": "msvc6.5"},
        )
        objects.append(obj)
    identities.update({str(p): digest(p.read_bytes()) for p in objects})
    oracles = {}
    for name in TARGETS:
        obj = out / f"{name}.native.obj"
        oracles[name] = make_oracle(
            obj,
            function_name=name,
            source_object=function_objects[name],
            allow_candidate_only=name == "load_level_definition_file",
        )
        identities[str(obj)] = digest(obj.read_bytes())
    results, outputs = {}, {}
    for label, replaced in [("source", None), *[(f"native-{n}", n) for n in TARGETS]]:
        linked = list(objects)
        object_overrides = {}
        if replaced:
            original = function_objects[replaced]
            forwarded = out / f"{replaced}.source-peers.obj"
            record = next(r for r in records if r["function"] == replaced)
            forwarded.write_bytes(externalize_coff_function(original.read_bytes(), record["symbol"]))
            linked[linked.index(original)] = forwarded
            linked.append(out / f"{replaced}.native.obj")
            object_overrides[original.name] = forwarded.name
            identities[str(forwarded)] = digest(forwarded.read_bytes())
        executable = out / f"{label}.exe"
        mapping = out / f"{label}.map"
        for path in (executable, mapping):
            path.unlink(missing_ok=True)
        options = [
            "/nologo",
            "/subsystem:console",
            "/entry:mainCRTStartup",
            "/nodefaultlib",
            "/opt:noref",
            "/debug",
            "/debugtype:coff",
            "/pdb:none",
            "/incremental:no",
            f"/out:Z:{executable}",
            f"/map:Z:{mapping}",
            *(f"Z:{p}" for p in linked),
            f"Z:{runtime}",
        ]
        if any('"' in s or "\n" in s for s in options):
            raise ValueError("invalid linker path")
        rsp = out / f"{label}.rsp"
        rsp.write_text("\n".join(f'"{s}"' for s in options) + "\n")
        checked_run([runner, str(linker), f"@Z:{rsp}"], out / f"{label}.link.log")
        proof = verify_source_link(executable, mapping, linked, records, replaced, object_overrides)
        if replaced:
            oracles[replaced]["link_verification"] = verify_oracle_link(
                executable, mapping, out / f"{replaced}.native.obj", oracles[replaced]
            )
        for p in (executable, mapping, rsp):
            identities[str(p)] = digest(p.read_bytes())
        data, events = out / f"{label}.bin", out / f"{label}.events.txt"
        for p in (data, events):
            p.unlink(missing_ok=True)
        run = checked_run(
            [runner, str(executable), f"Z:{bundle}", f"Z:{data}", f"Z:{events}"],
            out / f"{label}.run.log",
            timeout=60,
        )
        expected_cases = 4 * sum(
            f["path"].upper().startswith("LEVELS/") for f in corpus["files"]
        )
        summary = re.fullmatch(r"loaders cases=(\d+) diagnostics=(\d+)\s*", run.stdout)
        if summary is None or int(summary[1]) != expected_cases:
            raise ValueError("incomplete loader fixture run")
        outputs[label] = (data.read_bytes(), events.read_bytes())
        results[label] = {
            "stdout": run.stdout,
            "linked_source_functions": proof,
            "output_sha256": digest(outputs[label][0]),
            "events_sha256": digest(outputs[label][1]),
        }
        print(label, run.stdout.strip(), flush=True)
    source, source_events = outputs["source"]
    expected_names = []
    for _ in range(2):
        expected_names.append("catalog")
        for _ in range(2):
            for item in corpus["files"]:
                if item["path"].upper().startswith("LEVELS/"):
                    expected_names.extend((item["path"], "galaxy"))
    if [name for name, _ in decode_regions(source)] != expected_names:
        raise ValueError("incomplete or reordered serialized source regions")
    catalog_files = [
        f for f in corpus["files"] if f["path"].upper().startswith("SEGMENTS/")
    ]
    for name, region in decode_regions(source):
        if name != "catalog":
            continue
        if len(region) != 0x25CFB4 or struct.unpack_from("<I", region)[0] != len(
            catalog_files
        ):
            raise ValueError("incomplete catalog count/extent")
        for i, item in enumerate(catalog_files):
            base = 4 + i * 0x4088
            filename = (
                region[base + 0x40 : base + 0x80].split(b"\0", 1)[0].decode("ascii")
            )
            rows = struct.unpack_from("<I", region, base + 0x84)[0]
            if filename.upper() != item["path"][9:].upper() or not 0 < rows <= 256:
                raise ValueError("catalog file not completely parsed")
            if item["origin"] == "synthetic":
                row0 = base + 0x888
                if rows != 4 or struct.unpack_from("<I", region, row0)[0] != 0xA10F:
                    raise ValueError(
                        "synthetic row flags differ from explicit expectation"
                    )
                if struct.unpack_from("<3f", region, row0 + 0x24) != (0.5, 0.0, -1.0):
                    raise ValueError(
                        "synthetic velocity differs from explicit expectation"
                    )
                if struct.unpack_from("<f", region, row0 + 0x34)[0] != 2.5:
                    raise ValueError(
                        "synthetic RingSpeed differs from explicit expectation"
                    )
                if struct.unpack_from("<f", region, row0 + 3 * 0x38 + 0x34)[0] != 0:
                    raise ValueError("native plus-sign float quirk was changed")
    for label, (data, events) in outputs.items():
        results[label]["comparison"] = compare_regions(source, data)
        results[label]["events_equal"] = source_events == events
    negative = out / "negative.bin"
    negative_events = out / "negative.events.txt"
    checked_run(
        [
            runner,
            str(out / "source.exe"),
            f"Z:{bundle}",
            f"Z:{negative}",
            f"Z:{negative_events}",
            "corrupt",
        ],
        out / "negative.run.log",
        timeout=60,
    )
    negative_result = compare_regions(source, negative.read_bytes())
    first = negative_result["differences"][0] if negative_result["differences"] else {}
    if (
        negative_result["differing_regions"] != 1
        or first.get("region") != 0
        or first.get("name") != "catalog"
        or first.get("different_bytes") != 1
        or first.get("first_offsets") != [0x84]
        or first["source"][0] ^ first["candidate"][0] != 1
        or negative_events.read_bytes() != source_events
    ):
        raise ValueError(
            "corruption control must change only the first catalog ID byte"
        )
    for record in records:
        config = load_scratch_config(
            DEFAULT_MATCH_ROOT / "scratches" / record["function"]
        )
        if (
            scratch_dependency_sha256(config) != record["dependency_sha256"]
            or digest((config.directory / "scratch.conf").read_bytes())
            != record["config_sha256"]
        ):
            raise ValueError("source/config inputs changed during comparison")
    for name, expected in fixture_inputs.items():
        if support_inputs(DEFAULT_MATCH_ROOT / "link" / f"{name}.cpp") != expected:
            raise ValueError("fixture inputs changed")
    for p, expected in identities.items():
        if digest(Path(p).read_bytes()) != expected:
            raise ValueError(f"input changed: {p}")
    passed = all(
        r["comparison"]["equal"] and r["events_equal"] for r in results.values()
    )
    receipt = {
        "schema": 1,
        "purpose": __doc__,
        "original_code_used": True,
        "public_matching_credit": False,
        "public_linked_credit": False,
        "corpus": corpus,
        "functions": records,
        "oracles": oracles,
        "fixture_inputs": fixture_inputs,
        "identities": identities,
        "results": results,
        "negative_control": negative_result,
        "comparison_passed": passed,
    }
    receipt_path.write_text(json.dumps(receipt, indent=2) + "\n")
    print(f"Comparison passed={passed}: {receipt_path}")
    if not passed:
        raise ValueError("loader behavior differs; see comparison receipt")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--runtime-library", type=Path, required=True)
    parser.add_argument("--include-synthetic", action="store_true")
    parser.add_argument(
        "--archive", type=Path, default=REPO_ROOT / "artifacts/bin/SnailMail.dat"
    )
    parser.add_argument(
        "--out", type=Path, default=REPO_ROOT / "artifacts/match/loader-comparison"
    )
    args = parser.parse_args()
    out = args.out.resolve()
    out.mkdir(parents=True, exist_ok=True)
    with (out / ".comparison.lock").open("a") as lock:
        fcntl.flock(lock, fcntl.LOCK_EX | fcntl.LOCK_NB)
        compare(
            args.runtime_library.resolve(strict=True),
            args.archive.resolve(strict=True),
            out,
            args.include_synthetic,
        )


if __name__ == "__main__":
    main()
