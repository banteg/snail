#!/usr/bin/env python3
"""Replay registered source groups against isolated and reversed controls."""

import argparse
import hashlib
import json
import tempfile
from dataclasses import replace
from pathlib import Path

from snail.match import (
    DEFAULT_MATCH_ROOT,
    compile_scratch,
    evaluate_scratch,
    extract_object_function,
    load_default_reference_symbol_manifest,
    load_image,
    load_scratch_config,
    match_result_payload,
    parse_coff_object,
    resolve_function_extent,
    run_match,
    scratch_compilation_source,
    scratch_status_payload,
    scratch_translation_unit,
)
from snail.symbols import (
    DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
    REPO_ROOT,
    load_function_symbol_manifest,
)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--out", type=Path, required=True)
    args = parser.parse_args()
    root = DEFAULT_MATCH_ROOT
    registry = json.loads((root / "translation_units.json").read_text())
    manifest = load_function_symbol_manifest(DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH)
    native = REPO_ROOT / manifest.primary_target
    native_sha256 = hashlib.sha256(native.read_bytes()).hexdigest()
    if native_sha256 != manifest.unwrapped_sha256:
        raise ValueError("native image differs from matching manifest")
    image = load_image(native, manifest.image_base)
    rows = []
    for registered in registry["units"]:
        configs = [load_scratch_config(root / "scratches" / name) for name in registered["members"]]
        unit = scratch_translation_unit(configs[0])
        sources = [(config.directory / "scratch.cpp").read_text() for config in configs]
        for index, config in enumerate(configs):
            variants = {
                "canonical": scratch_compilation_source(config),
                "isolated": sources[index],
                "reverse": "\n".join(reversed(sources)),
                "peer-headers-only": "\n".join(
                    line for peer, source in enumerate(sources) if peer != index
                    for line in source.splitlines() if line.startswith("#include")
                ) + "\n" + sources[index],
            }
            for label, source in variants.items():
                # A whole-unit experiment must be an explicit shadow: a
                # canonical overlay intentionally replaces just one member.
                with tempfile.TemporaryDirectory(prefix="snail-unit-control-") as temp:
                    shadow = replace(config, directory=Path(temp))
                    (shadow.directory / "scratch.cpp").write_text(source)
                    status = evaluate_scratch(shadow)
                    if status.error:
                        raise ValueError(f"{unit.name}/{config.function}/{label}: {status.error}")
                    obj_path = compile_scratch(shadow)
                    result = run_match(
                        obj_path=obj_path, function_name=config.function,
                        image_path=native, manifest=manifest, symbol_name=config.symbol,
                        end_va=config.end_va,
                    )
                    detail = match_result_payload(result)
                    detail.pop("cfg_alignment")  # CFG diagnostics do not certify exactness.
                    if label == "canonical":
                        positional = all(
                            entry.status == "ok" and entry.target_index == entry.candidate_index
                            and entry.target_offset == entry.candidate_offset
                            for entry in result.masked_operand_audit.entries
                        )
                        if not positional:
                            raise ValueError(f"reference positions differ: {config.function}")
                        function = extract_object_function(
                            parse_coff_object(obj_path.read_bytes()), config.symbol or config.function,
                            reference_manifest=load_default_reference_symbol_manifest(),
                        )
                        start, end = resolve_function_extent(manifest, config.function, config.end_va)
                        target = image.function_bytes(start, end)
                        # i386 COFF address relocations occupy four bytes.
                        masked = {i for offset in function.relocation_offsets for i in range(offset, offset + 4)}
                        mismatches = [
                            i for i in range(min(len(target), len(function.data)))
                            if i not in masked and target[i] != function.data[i]
                        ]
                        detail["body_encoding"] = {
                            "target_bytes": len(target), "candidate_bytes": len(function.data),
                            "target_sha256": hashlib.sha256(target).hexdigest(),
                            "candidate_sha256": hashlib.sha256(function.data).hexdigest(),
                            "raw_body_byte_exact": target == function.data,
                            "positional_references_exact": positional,
                            "compared_non_relocation_bytes": len(target) - len(masked),
                            "coff_relocation_offsets": sorted(function.relocation_offsets),
                            "non_relocation_mismatch_offsets": mismatches,
                            "unexplained_bytes": abs(len(target) - len(function.data)),
                        }
                        if len(target) != len(function.data) or mismatches:
                            raise ValueError(f"body encoding differs outside relocations: {config.function}")
                    payload = scratch_status_payload(status)
                    payload.pop("scratch")  # Ephemeral compiler directory is not provenance.
                    rows.append({
                        "unit": unit.name, "source_object": unit.source_object,
                        "members": registered["members"], "variant": label,
                        "source_sha256": hashlib.sha256(source.encode()).hexdigest(),
                        "status": payload, "diagnostic": detail,
                    })
                    print(config.function, label, status.state, status.ratio, flush=True)
                    if label == "canonical" and status.state != "match":
                        raise ValueError(f"registered source unit regressed: {config.function}")
    args.out.parent.mkdir(parents=True, exist_ok=True)
    args.out.write_text(json.dumps({
        "schema": 1, "native_image_sha256": native_sha256, "controls": rows,
    }, indent=2) + "\n")


if __name__ == "__main__":
    main()
