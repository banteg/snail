#!/usr/bin/env python3
"""Produce the reviewed identity map from resolved probes and native anchors."""
import argparse
import ast
import hashlib
import json
import re
from collections import Counter
from pathlib import Path

import pefile

from snail.symbols import REPO_ROOT


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--demangled", type=Path, required=True)
    parser.add_argument("--source-root", type=Path, required=True)
    args = parser.parse_args()
    root = REPO_ROOT
    probe = json.loads((root / "artifacts/ownership/candidates.json").read_text())
    resolved = json.loads((root / "artifacts/ownership/resolved.json").read_text())
    demangled = json.loads(args.demangled.read_text())
    live = {f["address"]: f for f in json.loads((root / "artifacts/ownership/snail-ownership-live.json").read_text())["functions"]}
    image_path = root / "artifacts/bin/SnailMail_unwrapped.exe"
    data = image_path.read_bytes()
    if sha(data) != probe["target_sha256"]:
        raise ValueError("reference executable changed")
    pe = pefile.PE(data=data, fast_load=True)
    image = pe.get_memory_mapped_image()
    image_base = pe.OPTIONAL_HEADER.ImageBase

    def read(start: int, end: int) -> bytes:
        return image[start-image_base:end-image_base]

    records = []
    for row in resolved["accepted"]:
        symbol, label = row["symbol"], row["component"]
        name = demangled[symbol]["name"] if symbol.startswith("?") else symbol
        if name.startswith("["):
            name = "::".join(ast.literal_eval(name))
        else:
            name = re.sub(r"@\d+$", "", name).removeprefix("_")
        if label == "d3dx8":
            name = "d3dx8::" + name.removeprefix("D3DX::")
        elif label == "msvc6-crt":
            name = "crt::" + name
        elif label == "zlib-1.2.1":
            name = "zlib::" + name
        current = live[row["address"]]["name"]
        preserved = not re.fullmatch(r"(?:j_)?(?:sub|FUN)_[0-9a-fA-F]+", current)
        if preserved:
            name = current
        records.append({
            "address": row["address"], "name": name, "original_binja_name": current,
            "component": label, "symbol": symbol, "provider": row["provider"], "member": row["member"],
            "basis": row["basis"], "extent": row["extent"],
            "compatible_candidates": row["compatible_candidates"],
            "body_ranges": [[row["address"], row["end"]]], "body_sha256": row["target_sha256"],
            "unrelocated_sha256": row["unrelocated_sha256"],
            "consistent_references": row["consistent_references"],
            "unresolved_references": row["unresolved_references"],
        })
    # Independently reviewed source/control-flow anchor, not a claimed exact build.
    native = json.loads((root / "analysis/progress/binja-code-inventory.json").read_text())
    native_ranges = {f["start"]: f["ranges"] for f in native["functions"]}
    ranges = native_ranges[0x47d91e]
    records.append({
        "address": 0x47d91e, "name": "png_create_read_struct_2", "original_binja_name": live[0x47d91e]["name"],
        "component": "libpng-1.2.5", "symbol": "_png_create_read_struct_2",
        "provider": "libpng-1.2.5-source", "member": "pngread.c",
        "basis": "reviewed-native-source-control-flow", "body_ranges": ranges,
        "body_sha256": sha(b"".join(read(a, b) for a, b in ranges)),
        "notes": "Seven-argument read-struct allocator; checks 1.2.5; installs png_zalloc/png_zfree; initializes inflate with 1.2.1 and 56-byte z_stream; sets read callback and second setjmp. Native/source sequence reviewed; no exact-build credit.",
    })
    for address, slot in [(0x40a190, 4), (0x411490, 6), (0x4119a0, 7), (0x411da0, 8), (0x411dc0, 9)]:
        pointer = 0x4a1000 + slot * 4
        if int.from_bytes(read(pointer, pointer+4), "little") != address:
            raise ValueError("initializer table changed")
        ranges = native_ranges[address]
        code = b"".join(read(a,b) for a,b in ranges)
        if len(code) != 6 or code[:1] != b"\xe9" or code[-1:] != b"\xc3":
            raise ValueError("no-op initializer changed")
        records.append({
            "address": address, "name": f"noop_static_initializer_{slot:02d}", "original_binja_name": live[address]["name"],
            "component": "game-init", "basis": "reviewed-native-initializer-table", "body_ranges": ranges,
            "body_sha256": sha(code), "initializer_slot": pointer,
            "notes": "C++ initializer table entry; jumps directly to a return. No state change. Original object/source owner remains unestablished; suffix identifies the table slot, not an invented source owner.",
        })
    records.sort(key=lambda r:r["address"])
    if len({r["address"] for r in records}) != len(records):
        raise ValueError("duplicate identity")
    for record in records:
        if sha(b"".join(read(a,b) for a,b in record["body_ranges"])) != record["body_sha256"]:
            raise ValueError(f"body hash changed: {record['name']}")
    archives = {p["id"]: {"sha256": p["sha256"], "object_functions": p["object_functions"]}
                for p in probe["providers"] if p["id"] in {"d3dx8", "vc6-sp6-libcmt"}}
    output = {
        "schema": 1, "target_sha256": probe["target_sha256"],
        "policy": "Function identity/ownership only; no additional matched, fuzzy or linked credit. Unresolved relocation identities are retained explicitly.",
        "archives": archives,
        "source_archives": [{"url": url, "sha256": sha((args.source_root / filename).read_bytes())}
            for filename,url in [
                ("libpng-1.2.5.tar.gz", "https://codeload.github.com/pnggroup/libpng/tar.gz/refs/tags/v1.2.5"),
                ("zlib-1.2.1.tar.gz", "https://codeload.github.com/madler/zlib/tar.gz/refs/tags/v1.2.1"),
            ]],
        "probe_sha256": sha((root / "artifacts/ownership/candidates.json").read_bytes()),
        "resolver_sha256": sha((root / "src/snail/library_attribution.py").read_bytes()),
        "matcher_sources": probe["matcher_sources"],
        "components": dict(Counter(r["component"] for r in records)),
        "functions": records,
    }
    path = root / "analysis/ownership/library-attribution.json"
    path.write_text(json.dumps(output, indent=2) + "\n")
    # Keep the source/build attestation separate from the much larger scratch probe.
    (root / "analysis/ownership/reference-build.json").write_text(json.dumps(probe["build_manifest"], indent=2) + "\n")
    print(f"Wrote {len(records)} attributed functions; {sum(r['name'] != r['original_binja_name'] for r in records)} name updates")


if __name__ == "__main__":
    main()
