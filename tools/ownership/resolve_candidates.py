#!/usr/bin/env python3
"""Resolve the research candidate inventory without changing Binary Ninja."""
import argparse
import hashlib
import json
from pathlib import Path

import pefile

from snail.library_attribution import resolve
from snail.symbols import REPO_ROOT


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--input", type=Path, default=REPO_ROOT / "artifacts/ownership/candidates.json")
    parser.add_argument("--output", type=Path, default=REPO_ROOT / "artifacts/ownership/resolved.json")
    args = parser.parse_args()
    candidates = json.loads(args.input.read_text())
    manifest = json.loads((REPO_ROOT / "analysis/symbols/gameplay-functions.json").read_text())
    data = (REPO_ROOT / manifest["primary_target"]).read_bytes()
    if hashlib.sha256(data).hexdigest() != candidates["target_sha256"]:
        raise ValueError("candidate evidence belongs to another executable")
    pe = pefile.PE(data=data)
    imports = {entry.address: entry.name.decode() for descriptor in pe.DIRECTORY_ENTRY_IMPORT
               for entry in descriptor.imports if entry.name}
    resolved = resolve(candidates["providers"], pe.get_memory_mapped_image(), pe.OPTIONAL_HEADER.ImageBase, imports)
    args.output.write_text(json.dumps(resolved, indent=2) + "\n")
    print(f"Selected {len(resolved['accepted'])} identities; {len(resolved['remaining_candidates'])} ambiguous/unsupported candidate entries remain")


if __name__ == "__main__":
    main()
