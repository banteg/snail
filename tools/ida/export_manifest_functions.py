#!/usr/bin/env python3

from __future__ import annotations

import argparse
import json
from pathlib import Path
import sys

from runner import DEFAULT_IDA_DB_PATH, REPO_ROOT, find_ida_binary, run_ida_script


DEFAULT_MANIFEST_PATH = REPO_ROOT / "analysis/symbols/gameplay-functions.json"
DEFAULT_OUT_DIR = REPO_ROOT / "artifacts/ida/functions"
IDAPYTHON_SCRIPT_PATH = REPO_ROOT / "tools/ida/export_function_artifact.py"


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Export all named gameplay functions from the tracked manifest into IDA pseudocode artifacts."
    )
    parser.add_argument(
        "--ida-bin",
        help="Path to the IDA headless binary (defaults to the first idat*/ida* on PATH).",
    )
    parser.add_argument(
        "--db",
        type=Path,
        default=DEFAULT_IDA_DB_PATH,
        help="Path to the IDA database to read from.",
    )
    parser.add_argument(
        "--manifest",
        type=Path,
        default=DEFAULT_MANIFEST_PATH,
        help="Path to the tracked gameplay function manifest.",
    )
    parser.add_argument(
        "--out-dir",
        type=Path,
        default=DEFAULT_OUT_DIR,
        help="Directory to write exported pseudocode artifacts into.",
    )
    return parser.parse_args()


def load_manifest_selectors(manifest_path: Path) -> list[str]:
    manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
    selectors: list[str] = []
    for function in manifest.get("functions", []):
        name = function.get("name")
        if not isinstance(name, str) or not name:
            continue
        selectors.append(name)
    return selectors


def main() -> int:
    args = parse_args()
    ida_bin = find_ida_binary(args.ida_bin)
    db_path = args.db.resolve()
    manifest_path = args.manifest.resolve()
    out_dir = args.out_dir.resolve()

    if not db_path.is_file():
        raise FileNotFoundError(f"IDA database not found: {db_path}")
    if not manifest_path.is_file():
        raise FileNotFoundError(f"symbol manifest not found: {manifest_path}")
    if not IDAPYTHON_SCRIPT_PATH.is_file():
        raise FileNotFoundError(f"IDAPython export script not found: {IDAPYTHON_SCRIPT_PATH}")

    selectors = load_manifest_selectors(manifest_path)
    if not selectors:
        raise RuntimeError(f"no named functions found in manifest: {manifest_path}")

    exit_code, log_text = run_ida_script(
        ida_bin=ida_bin,
        script_path=IDAPYTHON_SCRIPT_PATH,
        db_path=db_path,
        script_args=[str(out_dir), *selectors],
        log_stem="export-manifest-functions",
    )
    sys.stdout.write(log_text)
    return exit_code


if __name__ == "__main__":
    sys.exit(main())
