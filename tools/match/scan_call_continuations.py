#!/usr/bin/env python3
"""Find positive call-continuation controls in native and recovered code.

This is a structural search, not a matcher or a proof of source equivalence.
Incomplete decoded ranges stay visible. Pattern blocks require physical adjacency.
"""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path

import probe_texture_continuations as continuation

from snail.match import compile_scratch, scratch_dependency_sha256

p = continuation.p


def scan_instructions(instructions):
    calls = {item.address for item in instructions if item.mnemonic == "call"}
    return continuation.cold_continuations(instructions, calls)


def scan_native(inventory_path: Path):
    inventory_bytes = inventory_path.read_bytes()
    inventory = json.loads(inventory_bytes)
    manifest = p.load_function_symbol_manifest(p.DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH)
    image_path = p.ROOT / manifest.primary_target
    image_bytes = image_path.read_bytes()
    image_sha256 = p.digest(image_bytes)
    if image_sha256 != inventory["target_sha256"] or image_sha256 != manifest.unwrapped_sha256:
        raise ValueError("native image disagrees with the code inventory or manifest")
    image = p.pefile.PE(data=image_bytes)
    rows = []
    for function in inventory["functions"]:
        ranges = function["ranges"]
        instructions = []
        decoded = []
        incomplete = []
        previous_end = None
        for start, end in ranges:
            if end <= start or (previous_end is not None and start < previous_end):
                raise ValueError(f"invalid/overlapping ranges at {function['start']:#x}")
            previous_end = end
            data = image.get_data(start - manifest.image_base, end - start)
            if len(data) != end - start:
                raise ValueError(f"native range is outside image data: {start:#x}..{end:#x}")
            identity = {"start": start, "end": end, "sha256": p.digest(data)}
            try:
                part = p.decode(data, start)
            except ValueError:
                incomplete.append(identity)
            else:
                instructions.extend(part)
                decoded.append(identity)
        rows.append({
            "function_start": function["start"],
            "name": function.get("curated_name") or function.get("names", {}).get("binja")
            or f"{function['start']:#x}",
            "decoded_ranges": decoded,
            "incomplete_ranges": incomplete,
            "continuations": scan_instructions(instructions),
        })
    return {
        "image_sha256": image_sha256,
        "inventory_sha256": p.digest(inventory_bytes),
        "manifest_sha256": p.digest(p.DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH.read_bytes()),
        "functions": rows,
    }


def scan_sources():
    rows = []
    identities = []
    for config_path in sorted((p.DEFAULT_MATCH_ROOT / "scratches").glob("*/scratch.conf")):
        config = p.load_scratch_config(config_path.parent)
        config_sha256 = p.digest(config_path.read_bytes())
        dependency_sha256 = scratch_dependency_sha256(config)
        # Rebuild stale objects; never search an arbitrary old cache snapshot.
        object_bytes = compile_scratch(config).read_bytes()
        if (
            scratch_dependency_sha256(config) != dependency_sha256
            or p.digest(config_path.read_bytes()) != config_sha256
        ):
            raise ValueError(f"source inputs changed during scan: {config.function}")
        identities.append((config, config_path, config_sha256, dependency_sha256))
        function = p.extract_object_function(
            p.parse_coff_object(object_bytes), config.symbol or config.function,
        )
        row = {
            "name": config.function,
            "object_sha256": p.digest(object_bytes),
            "config_sha256": config_sha256,
            "dependency_sha256": dependency_sha256,
            "code_sha256": p.object_function_fingerprint(function),
            "body_bytes": len(function.data),
            "completely_decoded": False,
            "continuations": [],
        }
        try:
            instructions = p.decode(function.data)
        except ValueError:
            pass
        else:
            row["completely_decoded"] = True
            row["continuations"] = scan_instructions(instructions)
        rows.append(row)
    for config, config_path, config_sha256, dependency_sha256 in identities:
        if (
            scratch_dependency_sha256(config) != dependency_sha256
            or p.digest(config_path.read_bytes()) != config_sha256
        ):
            raise ValueError(f"source inputs changed during scan: {config.function}")
    return rows


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--inventory", type=Path,
                        default=p.ROOT / "analysis/progress/executable-code-inventory.json")
    parser.add_argument("--include-sources", action="store_true")
    parser.add_argument("--out", type=Path,
                        default=p.ROOT / "artifacts/match/call-continuations/receipt.json")
    args = parser.parse_args()
    receipt = {
        "schema": 1,
        "interpretation": "Positive structural controls only; missing patterns and incomplete ranges do not prove semantic absence or a compiler limitation.",
        "tool_sha256": p.digest(Path(__file__).read_bytes()),
        "recognizer_sha256": p.digest(Path(continuation.__file__).read_bytes()),
        "decoder_sha256": p.digest(Path(p.__file__).read_bytes()),
        "native": scan_native(args.inventory),
        "sources": scan_sources() if args.include_sources else None,
    }
    rows = receipt["native"]["functions"]
    # Multiple inventory owners may overlap. Count unique native branch sites.
    branches = {
        match["branch"]["address"]
        for row in rows for match in row["continuations"]
    }
    summary = {
        "native_owners": len(rows),
        "native_decoded_ranges": sum(len(row["decoded_ranges"]) for row in rows),
        "native_incomplete_ranges": sum(len(row["incomplete_ranges"]) for row in rows),
        "native_positive_owners": sum(bool(row["continuations"]) for row in rows),
        "native_unique_branch_sites": len(branches),
    }
    if receipt["sources"] is not None:
        summary.update({
            "source_functions": len(receipt["sources"]),
            "source_completely_decoded": sum(row["completely_decoded"] for row in receipt["sources"]),
            "source_positive_functions": sum(bool(row["continuations"]) for row in receipt["sources"]),
        })
    receipt["summary"] = summary
    if p.digest(args.inventory.read_bytes()) != receipt["native"]["inventory_sha256"]:
        raise ValueError("code inventory changed during scan")
    if p.digest(p.DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH.read_bytes()) != receipt["native"]["manifest_sha256"]:
        raise ValueError("native manifest changed during scan")
    args.out.parent.mkdir(parents=True, exist_ok=True)
    args.out.write_text(json.dumps(receipt, indent=2) + "\n")
    print(json.dumps(summary, indent=2))
    print(f"Receipt: {args.out} ({hashlib.sha256(args.out.read_bytes()).hexdigest()})")


if __name__ == "__main__":
    main()
