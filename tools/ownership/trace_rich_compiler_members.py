#!/usr/bin/env python3
"""Compare D3DX8 member compiler IDs with the game's Rich-header counts.

Run with the sibling Crimson Python environment, as for probe_libraries.py.
This is compatible-member coverage, not an original linker-selection proof.
"""

from __future__ import annotations

import argparse
import hashlib
import json
from collections import Counter, defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
ARCHIVE_SHA256 = "39a8e21889a7c1f0b966f04a9e7d392de14ddebb3e091dfa1e5ce3e19564fc28"


def main() -> None:
    from crimson.library_match import parse_coff_archive
    from crimson.match import parse_coff_object

    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--archive",
        type=Path,
        default=ROOT.parent
        / "crimson/tools/native/providers/build/directx-8.1/d3dx8.lib",
    )
    parser.add_argument(
        "--output",
        type=Path,
        default=ROOT / "analysis/ownership/rich-d3dx8-coverage.json",
    )
    args = parser.parse_args()
    raw = args.archive.read_bytes()
    if hashlib.sha256(raw).hexdigest() != ARCHIVE_SHA256:
        raise ValueError("D3DX8 archive identity changed")
    source = ROOT / "analysis/ownership/library-attribution.json"
    attribution = json.loads(source.read_text())
    objects = {}
    exports = defaultdict(set)
    for member in parse_coff_archive(raw):
        try:
            obj = parse_coff_object(member.data)
        except ValueError:
            continue
        objects[member.name] = obj
        for symbol in obj.symbols:
            if symbol.section_number > 0 and symbol.storage_class == 2:
                exports[symbol.name].add(member.name)

    anchors = defaultdict(list)
    for function in attribution["functions"]:
        if function["component"] != "d3dx8":
            continue
        candidates = {
            row[1] for row in function["compatible_candidates"] if row[0] == "d3dx8"
        }
        if len(candidates) == 1:
            anchors[next(iter(candidates))].append(
                {
                    "address": hex(function["address"]),
                    "symbol": function["symbol"],
                    "size": sum(end - start for start, end in function["body_ranges"]),
                }
            )
    closure = set(anchors)
    edges = []
    while True:
        added = set()
        for member in sorted(closure):
            for symbol in objects[member].symbols:
                if (
                    symbol.section_number != 0
                    or symbol.storage_class != 2
                    or symbol.name not in exports
                    or exports[symbol.name] & closure
                ):
                    continue
                if len(exports[symbol.name]) != 1:
                    raise ValueError(f"ambiguous archive dependency: {symbol.name}")
                target = next(iter(exports[symbol.name]))
                added.add(target)
                edge = {"from": member, "symbol": symbol.name, "to": target}
                if edge not in edges:
                    edges.append(edge)
        if not added:
            break
        closure.update(added)

    def compiler_ids(member: str) -> list[str]:
        return [
            hex(symbol.value)
            for symbol in objects[member].symbols
            if symbol.name == "@comp.id"
        ]

    def counts(members) -> dict[str, int]:
        return dict(
            sorted(
                Counter(
                    value for member in members for value in compiler_ids(member)
                ).items()
            )
        )

    output = {
        "schema": 1,
        "target_sha256": attribution["target_sha256"],
        "archive_sha256": ARCHIVE_SHA256,
        "attribution_sha256": hashlib.sha256(source.read_bytes()).hexdigest(),
        "interpretation": (
            "Compatible archive members and whole-member symbol closure, not proof of "
            "the original linker selection or a function-to-compiler assignment. Closure "
            "includes references from unmatched or discarded member functions."
        ),
        "unique_compatible_member_count": len(anchors),
        "unique_compatible_compiler_counts": counts(anchors),
        "whole_member_closure_count": len(closure),
        "whole_member_closure_compiler_counts": counts(closure),
        "added_members": sorted(closure - set(anchors)),
        "added_dependency_edges": edges,
        "members": [
            {
                "member": member,
                "compiler_ids": compiler_ids(member),
                "native_anchor_count": len(anchors.get(member, [])),
                "representative_native_anchor": max(
                    anchors.get(member, []), key=lambda row: row["size"], default=None
                ),
            }
            for member in sorted(closure)
        ],
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(output, indent=2) + "\n")
    print(f"Unique compatible members: {counts(anchors)}")
    print(f"Whole-member dependency closure: {counts(closure)}")


if __name__ == "__main__":
    main()
