#!/usr/bin/env python3
"""Export bounded diagnostic COFF snapshots and compare external diff viewers.

These are generated display objects, not recovered original translation units.
The native matcher remains the acceptance authority. No scores are published.
"""

import argparse
import difflib
import hashlib
import importlib.util
import json
import re
import struct
import subprocess
import sys
import traceback
from collections import Counter
from dataclasses import replace
from pathlib import Path

import capstone

from snail import match as m

ROOT = Path(__file__).resolve().parents[3]
OBJD_SHA = "98f8275c27900c4fe2248fce3af37617658be49648fa7dbb5b376371f046dfdb"
ASM_SHA = "10b8b1f21fba9ffe4294ecf21dc67d14a41473d9ec3ebf0bb60a6d50955d3873"
SAMPLES = (
    "initialize_quaternion_from_matrix",
    "switch_track_mirror",
    "update_subgame",
    "initialize_snake_path_template_pair",
    "initialize_worm_path_template_pair",
    "populate_runtime_track_cells_from_segments",
    "initialize_game_assets_and_world",
    "update_subgoldy",
)


def sha(data):
    return hashlib.sha256(data).hexdigest()


def write_json(path, value):
    path.write_text(json.dumps(value, indent=2) + "\n")


def display_symbol(key):
    # Readable, collision-resistant names; no alignment-dependent name transfer.
    label = re.sub(r"[^a-zA-Z0-9_]", "_", key)[:80]
    return label + "_" + sha(key.encode())[:16]


def coff(code, refs):
    """Write one i386 code section with external symbolic reference fields."""
    names = ["_pilot"] + list(dict.fromkeys(r["symbol"] for r in refs))
    indexes = {name: i for i, name in enumerate(names)}
    strings = bytearray(b"\0" * 4)
    symbols = bytearray()
    for i, name in enumerate(names):
        raw = name.encode("ascii")
        if len(raw) > 8:
            field = struct.pack("<II", 0, len(strings))
            strings.extend(raw + b"\0")
        else:
            field = raw.ljust(8, b"\0")
        symbols.extend(
            field
            + struct.pack(
                "<IhHBB",
                0,
                1 if i == 0 else 0,
                0x20 if i == 0 else 0,
                2,
                0,
            )
        )
    struct.pack_into("<I", strings, 0, len(strings))
    rels = b"".join(
        struct.pack(
            "<IIH",
            r["offset"],
            indexes[r["symbol"]],
            r["type"],
        )
        for r in refs
    )
    symoff = 60 + len(code) + len(rels)
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, symoff, len(names), 0, 0)
    section = struct.pack(
        "<8sIIIIIIHHI",
        b".text",
        0,
        0,
        len(code),
        60,
        60 + len(code) if refs else 0,
        0,
        len(refs),
        0,
        0x60500020,
    )
    blob = header + section + code + rels + symbols + strings
    parsed = m.parse_coff_object(blob)
    if parsed.sections[0].data != code:
        raise ValueError("COFF serialization changed code")
    return blob


def lift(data, lines, base):
    """Represent the matcher's independent reference keys as COFF relocations.

    Round-trip checks preserve every input byte. This does not certify the keys,
    reconstruct referenced data, or validate a native linker relocation table.
    Unsupported fields fail closed. Alternate-key equivalences are not merged.
    """
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    body = bytearray(data)
    refs = []
    occupied = set()
    for line in lines:
        if not line.masked_references:
            continue
        instructions = list(
            md.disasm(
                data[line.offset : line.offset + line.size],
                base + line.offset,
            )
        )
        if len(instructions) != 1 or instructions[0].size != line.size:
            raise ValueError(
                f"Unsupported referenced data/decoding at {line.offset:#x}"
            )
        ins = instructions[0]
        for ref in line.masked_references:
            if not ref.key or ref.kind not in ("imm", "disp"):
                raise ValueError(f"Unsupported reference at {line.offset:#x}: {ref}")
            off, size = (
                (ins.imm_offset, ins.imm_size)
                if ref.kind == "imm"
                else (ins.disp_offset, ins.disp_size)
            )
            if size != 4:
                raise ValueError(f"Unsupported {size}-byte field at {line.offset:#x}")
            off += line.offset
            fields = set(range(off, off + size))
            if fields & occupied or off + size > len(data):
                raise ValueError("Overlapping or out-of-bounds relocation fields")
            occupied |= fields
            relative = ref.kind == "imm" and (
                ins.group(capstone.CS_GRP_CALL) or ins.group(capstone.CS_GRP_JUMP)
            )
            original = data[off : off + size]
            if ref.source == "image":
                decoded = int.from_bytes(original, "little")
                if relative:
                    decoded = (decoded + base + off + size) & 0xFFFFFFFF
                if decoded != ref.value:
                    raise ValueError(f"Native reference value mismatch at {off:#x}")
            refs.append(
                {
                    "offset": off,
                    "type": 0x14 if relative else 6,
                    "symbol": display_symbol(ref.key),
                    "key": ref.key,
                    "explained": ref.explained,
                    "alternate_keys": ref.alternate_keys,
                    "original": original.hex(),
                    "value": ref.value,
                }
            )
            body[off : off + size] = b"\0" * size
    blob = coff(bytes(body), refs)
    restored = bytearray(m.parse_coff_object(blob).sections[0].data)
    for ref in refs:
        restored[ref["offset"] : ref["offset"] + 4] = bytes.fromhex(ref["original"])
    if restored != data:
        raise ValueError("Display-object round trip changed input bytes")
    return blob, refs


def objdiff(tool, target, candidate, output):
    command = [
        str(tool),
        "diff",
        "-1",
        str(target),
        "-2",
        str(candidate),
        "-o",
        str(output),
    ]
    subprocess.run(command, check=True, capture_output=True, text=True)
    result = json.loads(output.read_text())
    left, right = (result[side]["symbols"][0] for side in ("left", "right"))
    return {
        "percent": left["match_percent"],
        "rows": len(left["instructions"]),
        "inferred_target_bytes": int(left["size"]),
        "inferred_candidate_bytes": int(right["size"]),
        "kinds": dict(
            Counter(row.get("diff_kind", "equal") for row in left["instructions"])
        ),
        "command": command,
    }


def load_asm(path):
    if sha(path.read_bytes()) != ASM_SHA:
        raise ValueError("asm-differ source differs from pinned pilot")
    spec = importlib.util.spec_from_file_location("pilot_asm_differ", path)
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


def asm_config(d):
    return d.Config(
        arch=d.get_arch("i686"),
        diff_obj=True,
        file=None,
        ref_file=None,
        make=False,
        source_old_binutils=False,
        diff_section=".text",
        inlines=False,
        max_function_size_lines=50000,
        max_function_size_bytes=250000,
        formatter=d.JsonFormatter(arch_str="i686"),
        diff_mode=d.DiffMode.NORMAL,
        base_shift=0,
        skip_lines=0,
        compress=None,
        show_rodata_refs=False,
        show_branches=True,
        show_line_numbers=False,
        show_source=False,
        stop_at_ret=None,
        ignore_large_imms=False,
        ignore_addr_diffs=False,
        algorithm="levenshtein",
        reg_categories={},
        diff_function_symbols=False,
    )


def asm_compare(d, objdump, target, candidate, out):
    cfg = asm_config(d)
    dumps = []
    for path in (target, candidate):
        raw = subprocess.check_output(
            [str(objdump), "-dr", "--no-show-raw-insn", str(path)],
            text=True,
        )
        dump = d.preprocess_objdump_out("_pilot", None, raw, cfg)
        path.with_suffix(".s").write_text(dump)
        dumps.append(dump)
    summaries = {}
    for algorithm in ("levenshtein", "difflib"):
        display = d.Display(*dumps, replace(cfg, algorithm=algorithm))
        rendered, _ = display.run_diff()
        (out / f"asm-{algorithm}.json").write_text(rendered + "\n")
        result = json.loads(rendered)
        summaries[algorithm] = {
            key: result[key] for key in ("current_score", "max_score")
        }
        summaries[algorithm]["rows"] = len(result["rows"])
    summaries["identical_output"] = (out / "asm-levenshtein.json").read_bytes() == (
        out / "asm-difflib.json"
    ).read_bytes()
    return summaries


def asm_parser_controls(d):
    """Reduce the two observed failures to ordinary GNU x86 disassembly."""
    cases = (
        ("register-change", "mov\t%eax,0x3bfb08(%esi)", "mov\t%ecx,0x3bfb08(%esi)"),
        ("offset-change", "mov\t%ebx,0x1067f04(%ebp)", "mov\t%ebx,0x1067f00(%ebp)"),
    )
    results = []
    for name, target, candidate in cases:
        result = {"name": name, "target": target, "candidate": candidate}
        cfg = asm_config(d)
        dumps = (" 0:\t" + target, " 0:\t" + candidate)
        if any(len(d.process(value, cfg)) != 1 for value in dumps):
            raise ValueError(
                "asm-differ did not consume the reduced control instructions"
            )
        try:
            output, _ = d.Display(*dumps, cfg).run_diff()
            result["output"] = json.loads(output)
        except ValueError as error:
            result["error"] = str(error)
        results.append(result)
    return results


def compare_scratch(name, out, objd, asm, objdump):
    cfg = m.load_scratch_config(m.resolve_scratch_directory(name))
    results = []
    status = m.evaluate_scratch(cfg, on_match=results.append)
    if status.error:
        raise ValueError(status.error)
    result = results[0]
    original_object = m.compile_scratch(cfg).read_bytes()
    if sha(original_object) != status.candidate_object_sha256:
        raise ValueError("Candidate object changed during export")
    candidate = m.extract_object_function(
        m.parse_coff_object(original_object),
        cfg.symbol or cfg.function,
        reference_manifest=m.load_default_reference_symbol_manifest(),
    )
    manifest = m.load_function_symbol_manifest(m.DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH)
    start, end = m.resolve_function_extent(manifest, cfg.function, cfg.end_va)
    target = m.load_image(
        ROOT / manifest.primary_target, manifest.image_base
    ).function_bytes(start, end)
    out.mkdir()
    receipt = {
        "scratch": name,
        "native": m.scratch_status_payload(status),
        "objects": {},
    }
    for side, data, lines, base in (
        ("target", target, result.target_disassembly, start),
        ("candidate", candidate.data, result.candidate_disassembly, 0),
    ):
        blob, refs = lift(data, lines, base)
        (out / f"{side}.obj").write_bytes(blob)
        (out / f"{side}.bin").write_bytes(data)
        write_json(out / f"{side}-refs.json", refs)
        receipt["objects"][side] = {
            "input_sha256": sha(data),
            "display_object_sha256": sha(blob),
            "bytes": len(data),
            "reference_fields": len(refs),
            "round_trip": True,
            "unexplained_fields": sum(not r["explained"] for r in refs),
        }
    receipt["objdiff"] = objdiff(
        objd, out / "target.obj", out / "candidate.obj", out / "objdiff.json"
    )
    if asm:
        try:
            receipt["asm_differ"] = asm_compare(
                asm, objdump, out / "target.obj", out / "candidate.obj", out
            )
        except (ValueError, OSError, subprocess.CalledProcessError) as error:
            (out / "asm-error.txt").write_text(traceback.format_exc())
            receipt["asm_differ"] = {"error": str(error)}
    (out / "native.diff").write_text(
        "\n".join(
            difflib.unified_diff(
                result.target_lines,
                result.candidate_lines,
                fromfile="native",
                tofile="candidate",
                lineterm="",
            )
        )
        + "\n"
    )
    write_json(out / "native-diagnostics.json", m.match_result_payload(result))
    write_json(out / "receipt.json", receipt)
    return receipt


def controls(out, objd, asm, objdump):
    """Corrupt one reference identity in an exact display-object baseline."""
    original = out / "initialize_quaternion_from_matrix"
    if not original.exists():
        return {}
    body = m.parse_coff_object((original / "target.obj").read_bytes()).sections[0].data
    refs = json.loads((original / "target-refs.json").read_text())
    summary = {}
    for label, kind in (("wrong-callee", 0x14), ("wrong-data-reference", 6)):
        changed = [dict(r) for r in refs]
        field = next(r for r in changed if r["type"] == kind)
        field["symbol"] = "wrong_reference_control"
        folder = out / label
        folder.mkdir()
        candidate = folder / "candidate.obj"
        candidate.write_bytes(coff(body, changed))
        result = objdiff(
            objd, original / "target.obj", candidate, folder / "objdiff.json"
        )
        if result["percent"] >= 100 or result["kinds"].get("DIFF_ARG_MISMATCH") != 1:
            raise ValueError(
                f"objdiff did not expose exactly one wrong reference: {label}"
            )
        summary[label] = {"objdiff": result, "changed_field": field}
        if asm:
            summary[label]["asm_differ"] = asm_compare(
                asm,
                objdump,
                original / "target.obj",
                candidate,
                folder,
            )
            if summary[label]["asm_differ"]["levenshtein"]["current_score"] <= 0:
                raise ValueError(f"asm-differ did not expose wrong reference: {label}")
    return summary


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--out", type=Path, required=True, help="New snapshot directory"
    )
    parser.add_argument(
        "--scratch",
        action="append",
        help="Repeat to select scratches; default: pilot sample",
    )
    parser.add_argument(
        "--tools", type=Path, default=ROOT / "artifacts/differ-pilot/tools"
    )
    parser.add_argument(
        "--asm-differ",
        action="store_true",
        help="Also run the pinned asm-differ module",
    )
    parser.add_argument(
        "--objdump",
        type=Path,
        default=Path("/opt/homebrew/bin/i686-w64-mingw32-objdump"),
    )
    args = parser.parse_args()
    out, tools = args.out.resolve(), args.tools.resolve()
    objd = tools / "objdiff-cli"
    if sha(objd.read_bytes()) != OBJD_SHA:
        raise ValueError("objdiff CLI differs from pinned macOS arm64 v3.8.1")
    asm = load_asm(tools / "diff.py") if args.asm_differ else None
    out.mkdir(parents=True, exist_ok=False)
    report = {
        "purpose": "diagnostic snapshots only; no native proof or progress credit",
        "reference_model": "independent matcher keys; byte-restoration receipts; no referenced-data reconstruction",
        "tools": {"objdiff_version": "3.8.1", "objdiff_sha256": OBJD_SHA},
        "script_sha256": sha(Path(__file__).read_bytes()),
        "matcher_sha256": sha(Path(m.__file__).read_bytes()),
        "samples": [],
        "errors": [],
    }
    if asm:
        report["tools"].update(
            {
                "asm_commit": "0dd09af8f8008f1f880327cf0aca3b26d2562ea2",
                "asm_sha256": ASM_SHA,
                "objdump_version": subprocess.check_output(
                    [str(args.objdump), "--version"], text=True
                ).splitlines()[0],
            }
        )
    units = []
    for name in args.scratch or SAMPLES:
        try:
            receipt = compare_scratch(
                name, out / Path(name).name, objd, asm, args.objdump
            )
            report["samples"].append(receipt)
            units.append(
                {
                    "name": receipt["scratch"],
                    "target_path": f"{Path(name).name}/target.obj",
                    "base_path": f"{Path(name).name}/candidate.obj",
                }
            )
            print(
                name,
                receipt["native"]["match_ratio"],
                receipt["objdiff"]["percent"],
                flush=True,
            )
        except (ValueError, OSError, subprocess.CalledProcessError) as error:
            report["errors"].append({"scratch": name, "error": str(error)})
            print(name, "ERROR", error, flush=True)
    report["controls"] = controls(out, objd, asm, args.objdump)
    if asm:
        report["asm_parser_controls"] = asm_parser_controls(asm)
    write_json(out / "report.json", report)
    write_json(
        out / "objdiff.json",
        {"build_base": False, "build_target": False, "units": units},
    )
    if report["errors"]:
        raise SystemExit(1)


if __name__ == "__main__":
    main()
