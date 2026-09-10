"""Refresh build-bound mobile symbol indexes from the direct binary inventory."""

import argparse
import json
import subprocess
from pathlib import Path

from snail.ports import load_builds

SOURCES = {
    "android-armv7": "android-v7",
    "android-armv5": "android-v5",
    "ios-1.5-armv6": "ios15",
    "ios-1.9-armv6": "ios19-slice0",
    "ios-1.9-armv7": "ios19-slice1",
}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--raw-root", type=Path, default=Path("artifacts/mobile-audit-20260910")
    )
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    for build in load_builds()["builds"]:
        if build["id"] not in SOURCES:
            continue
        source = SOURCES[build["id"]]
        data = json.loads((args.raw_root / f"{source}-raw.json").read_text())
        sha = data.get("slice_sha256", data["file_sha256"])
        if sha != build["binary"]["sha256"]:
            raise ValueError(f"{source}: wrong binary identity")
        elf = data["format"].startswith("ELF")
        functions = {}
        for index, symbol in enumerate(data["symbols"]):
            name = symbol["name"]
            if not name.startswith(("_Z", "__Z")):
                continue
            size = None
            if elf:
                if symbol["type"] != 2 or symbol["section"] in [0, 65521]:
                    continue
                size = symbol["size"]
            else:
                if not (
                    symbol["type"] == 36
                    or (symbol["type"] in [14, 15] and symbol["section"] == 1)
                ):
                    continue
                if symbol["type"] == 36:
                    ending = data["symbols"][index + 1]
                    if ending["type"] == 36 and not ending["name"]:
                        size = ending["address"]
            mangled = name[1:] if name.startswith("__Z") else name
            if mangled not in functions or size is not None:
                functions[mangled] = {
                    "mangled": mangled,
                    "address": hex(symbol["address"]),
                    "size": size,
                    "extent_basis": "ELF symbol size"
                    if elf
                    else "STABS FUN size"
                    if size
                    else "unknown",
                }
        names = sorted(functions)
        demangled = subprocess.run(
            ["c++filt"],
            input="\n".join(names) + "\n",
            text=True,
            capture_output=True,
            check=True,
        ).stdout.splitlines()
        for name, dem in zip(names, demangled, strict=True):
            functions[name]["demangled"] = dem
        payload = {
            "schema": 1,
            "build_id": build["id"],
            "binary_sha256": sha,
            "address_space": "link-time-va",
            "functions": [functions[name] for name in names],
        }
        text = json.dumps(payload, indent=2) + "\n"
        path = Path(build["symbol_index"])
        if args.check:
            if path.read_text() != text:
                raise ValueError(f"{path}: stale symbol index")
        else:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(text)
        print(build["id"], len(names), "symbols")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
