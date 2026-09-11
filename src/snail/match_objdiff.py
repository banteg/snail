"""Opt-in objdiff snapshots. Display objects never confer native match credit.

The pilot remains frozen under tools/match/differ_pilot for reproducibility.
This module owns the supported export path and requires no external viewer.
"""

from __future__ import annotations

import difflib
import hashlib
import json
import re
import shutil
import struct
from dataclasses import replace
from pathlib import Path

import capstone

from . import match as m

DISPLAY_SYMBOL = "_snail_snapshot"


def sha(data):
    return hashlib.sha256(data).hexdigest()


def write_json(path, value):
    path.write_text(json.dumps(value, indent=2) + "\n")


def display_symbol(key):
    # Readable, collision-resistant names; no alignment-dependent name transfer.
    label = re.sub(r"[^a-zA-Z0-9_]", "_", key)[:80]
    return label + "_" + sha(key.encode())[:16]


def coff(code, refs, symbol="_snail_snapshot"):
    """Write one i386 code section with external symbolic reference fields."""
    if len(refs) > 0xFFFF:
        raise ValueError("Too many display relocations for a single COFF section")
    names = [symbol] + list(dict.fromkeys(r["symbol"] for r in refs))
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
        if line.offset < 0 or line.size <= 0 or line.offset + line.size > len(data):
            raise ValueError("Disassembly line outside input bytes")
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
            if size != 4 or off <= 0 or off + size > line.size:
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


def export_snapshot(
    directory: str | Path,
    output: Path,
    *,
    match_root: Path = m.DEFAULT_MATCH_ROOT,
    manifest_path: Path = m.DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
    image_path: Path | None = None,
) -> dict:
    """Compile once, compare captured inputs, and export a new static project.

    Native audit failures are retained as diagnostics. Unknown reference keys,
    unsupported fields, changed inputs, and a wrong target image abort export.
    A failed write removes only the new directory created by this invocation.
    """
    output = output.absolute()
    if output.exists() or output.is_symlink():
        raise FileExistsError(f"Snapshot already exists: {output}; choose a new --out")
    config = m.load_scratch_config(m.resolve_scratch_directory(directory, match_root))
    manifest = m.load_function_symbol_manifest(manifest_path)
    image_path = image_path or m.REPO_ROOT / manifest.primary_target
    image_sha = sha(image_path.read_bytes())
    if image_sha != manifest.unwrapped_sha256:
        raise ValueError("Target image SHA-256 does not match the function manifest")
    epoch = m.scratch_experiment_epoch(
        config, match_root, image_path=image_path, manifest_path=manifest_path
    )
    object_data = m.compile_scratch(config, match_root).read_bytes()
    reference_manifest = m.load_default_reference_symbol_manifest()
    candidate = m.extract_object_function(
        m.parse_coff_object(object_data),
        config.symbol or config.function,
        reference_manifest=reference_manifest,
    )
    start, end = m.resolve_function_extent(manifest, config.function, config.end_va)
    image = m.load_image(image_path, manifest.image_base)
    target = image.function_bytes(start, end)
    if not target or len(target) != end - start:
        raise ValueError("Target extent is empty or outside the image")
    result = replace(
        m.match_function(
            target,
            candidate,
            image=image,
            target_va=start,
            manifest=manifest,
            reference_manifest=reference_manifest,
        ),
        candidate_object_sha256=sha(object_data),
    )
    artifacts = {"compiled.obj": object_data}
    receipt = {
        "schema": 1,
        "purpose": "diagnostic snapshot only; no native proof or progress credit",
        "scratch": str(config.directory),
        "function": config.function,
        "symbol": DISPLAY_SYMBOL,
        "source_symbol": config.symbol or config.function,
        "target_image_sha256": image_sha,
        "candidate_object_sha256": sha(object_data),
        "experiment_epoch": epoch,
        "exporter_sha256": sha(Path(__file__).read_bytes()),
        "decoder_version": capstone.__version__,
        "reference_model": "independent matcher keys; alternate keys are not merged",
        "objects": {},
    }
    for side, data, lines, base in (
        ("target", target, result.target_disassembly, start),
        ("candidate", candidate.data, result.candidate_disassembly, 0),
    ):
        blob, refs = lift(data, lines, base)
        artifacts[f"{side}.obj"] = blob
        artifacts[f"{side}.bin"] = data
        artifacts[f"{side}-refs.json"] = (json.dumps(refs, indent=2) + "\n").encode()
        receipt["objects"][side] = {
            "input_sha256": sha(data),
            "display_object_sha256": sha(blob),
            "bytes": len(data),
            "reference_fields": len(refs),
            "round_trip": True,
            "unexplained_fields": sum(not ref["explained"] for ref in refs),
        }
    if epoch != m.scratch_experiment_epoch(
        config, match_root, image_path=image_path, manifest_path=manifest_path
    ) or image_sha != sha(image_path.read_bytes()):
        raise ValueError(
            "Matching inputs changed during export; retry with stable inputs"
        )

    project = {
        "build_base": False,
        "build_target": False,
        "units": [
            {
                "name": config.function,
                "target_path": "target.obj",
                "base_path": "candidate.obj",
            }
        ],
    }
    diagnostics = m.match_result_payload(result)
    artifacts["native.diff"] = (
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
    ).encode()
    for name, value in (
        ("objdiff.json", project),
        ("native-diagnostics.json", diagnostics),
    ):
        artifacts[name] = (json.dumps(value, indent=2) + "\n").encode()
    receipt["files"] = {name: sha(data) for name, data in artifacts.items()}
    # Claim the destination only after all validation. Never replace a snapshot.
    output.mkdir(parents=True, exist_ok=False)
    try:
        for name, data in artifacts.items():
            (output / name).write_bytes(data)
        write_json(output / "receipt.json", receipt)
    except Exception:
        shutil.rmtree(output)
        raise
    return {"output": str(output), "unit": config.function, **receipt}
