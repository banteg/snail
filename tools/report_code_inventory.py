"""Rebuild or verify the exploratory full-executable inventory from saved evidence."""

import argparse
import json
from pathlib import Path

from snail.code_inventory import build_inventory, snapshot_text


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    evidence = root / "analysis/progress"
    inventory = build_inventory(
        root / "artifacts/bin/SnailMail_unwrapped.exe",
        root / "analysis/symbols/gameplay-functions.json",
        evidence / "binja-code-inventory.json",
        evidence / "ida-code-inventory.json",
        evidence / "ghidra-code-inventory.json",
    )
    path = evidence / "executable-code-inventory.json"
    text = snapshot_text(inventory)
    if args.check:
        if not path.is_file() or path.read_text() != text:
            raise SystemExit("inventory is stale; regenerate with uv run tools/report_code_inventory.py")
    else:
        path.write_text(text)
    print(json.dumps(inventory["summary"], indent=2))


if __name__ == "__main__":
    main()
