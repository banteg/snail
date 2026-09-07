#!/usr/bin/env python3
"""Compare full native extents with relocation-masked COFF functions.

Uses the sibling Crimson COFF implementation as a research dependency. Its exact
source hashes are recorded. Output is candidate evidence, never a rename list.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source_root", type=Path)
    parser.add_argument("--crimson-root", type=Path, default=ROOT.parent / "crimson")
    parser.add_argument("--output", type=Path, default=ROOT / "artifacts/ownership/candidates.json")
    args = parser.parse_args()
    crimson = args.crimson_root.resolve()
    sys.path.insert(0, str(crimson / "src"))
    from crimson import library_match as lib
    from crimson import match as matcher

    symbol_manifest = json.loads((ROOT / "analysis/symbols/gameplay-functions.json").read_text())
    image_path = ROOT / symbol_manifest["primary_target"]
    if digest(image_path.read_bytes()) != symbol_manifest["unwrapped_sha256"]:
        raise ValueError("reference executable identity changed")
    image = matcher.load_image(image_path)
    snapshot_path = ROOT / "analysis/progress/binja-code-inventory.json"
    functions = json.loads(snapshot_path.read_text())["functions"]
    providers = crimson / "tools/native/providers/build"
    archives = {
        "d3dx8": providers / "directx-8.1/d3dx8.lib",
        "vc6-sp6-libcmt": providers / "vc6-sp6/vc98/lib/libcmt.lib",
    }
    expected_archives = {
        "d3dx8": "39a8e21889a7c1f0b966f04a9e7d392de14ddebb3e091dfa1e5ce3e19564fc28",
        "vc6-sp6-libcmt": "a541c95e5ffdd6d5573d1976f5e5d0038f2c4fb0bcb02975c68948bf1d6e452a",
    }
    sources = []
    for identity, path in archives.items():
        data = path.read_bytes()
        if digest(data) != expected_archives[identity]:
            raise ValueError(f"pinned archive changed: {identity}")
        sources.append((identity, str(path), digest(data), lib.parse_coff_archive(data)))
    build_manifest = json.loads((args.source_root / "build-manifest.json").read_text())
    for entry in build_manifest["outputs"]:
        if digest((args.source_root / entry["object"]).read_bytes()) != entry["sha256"]:
            raise ValueError(f"reference object changed: {entry['object']}")
    for path in sorted((args.source_root / "objects").glob("*/*")):
        members = tuple(lib.CoffArchiveMember(p.name, p.read_bytes()) for p in sorted(path.glob("*.obj")))
        sources.append((path.name + "-" + path.parent.name, str(path), digest(b"".join(m.data for m in members)), members))

    results = []
    for identity, path, sha, members in sources:
        index, object_members, object_functions = lib._archive_function_index(members)
        matches = []
        for function in functions:
            start = function["start"]
            end = max(b for _, b in function["ranges"])
            target = image.function_bytes(start, end)
            for candidate in index.get(len(target), []):
                if not lib._candidate_matches(target, candidate):
                    continue
                refs = []
                for ref in candidate.function.relocation_references:
                    value = int.from_bytes(target[ref.offset:ref.offset + 4], "little")
                    if ref.relocation_type == 0x14:
                        value += start + ref.offset + 4
                    refs.append({"offset": ref.offset, "symbol": ref.symbol_name, "target": value & 0xffffffff,
                                 "addend": ref.addend, "type": ref.relocation_type,
                                 "data_hex": ref.symbol_data.hex() if ref.symbol_data else None,
                                 "readonly": ref.read_only_data})
                matches.append({"address": start, "current_name": function["name"], "end": start + len(target),
                                "size": len(target), "target_sha256": digest(target),
                                "unrelocated_sha256": digest(lib._mask_relocations(target, candidate.relocation_offsets)),
                                "member": candidate.candidate.member, "symbol": candidate.candidate.symbol,
                                "compiler_id": candidate.candidate.compiler_id, "extent": candidate.candidate.extent,
                                "refs": refs})
        results.append({"id": identity, "path": path, "sha256": sha, "object_members": object_members,
                        "object_functions": object_functions, "matches": matches})
        print(identity, "candidate functions:", len({r["address"] for r in matches}), flush=True)
    output = {
        "schema": 1, "target_sha256": symbol_manifest["unwrapped_sha256"],
        "inventory_sha256": digest(snapshot_path.read_bytes()),
        "matcher_sources": {name: digest((crimson / "src/crimson" / name).read_bytes())
                            for name in ("library_match.py", "match.py")},
        "build_manifest": build_manifest, "providers": results,
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(output, indent=2) + "\n")


if __name__ == "__main__":
    main()
