#!/usr/bin/env python3

from __future__ import annotations

import argparse
import sys
from pathlib import Path

from runner import DEFAULT_IDA_DB_PATH, REPO_ROOT, find_ida_binary, run_ida_script

IDAPYTHON_SCRIPT_PATH = REPO_ROOT / "tools/ida/apply_rtext_types.py"


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Replay the mobile-proven RShell RText contracts in IDA 9.4."
    )
    parser.add_argument(
        "--ida-bin",
        help="Path to the IDA 9.4 headless binary.",
    )
    parser.add_argument(
        "--db",
        type=Path,
        default=DEFAULT_IDA_DB_PATH,
        help="Path to the IDA database to update.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    ida_bin = find_ida_binary(args.ida_bin)
    db_path = args.db.resolve()

    if not db_path.is_file():
        raise FileNotFoundError(f"IDA database not found: {db_path}")
    if not IDAPYTHON_SCRIPT_PATH.is_file():
        raise FileNotFoundError(
            f"IDAPython RText sync script not found: {IDAPYTHON_SCRIPT_PATH}"
        )

    exit_code, log_text = run_ida_script(
        ida_bin=ida_bin,
        script_path=IDAPYTHON_SCRIPT_PATH,
        db_path=db_path,
        script_args=[],
        log_stem="sync-rtext-types",
    )
    sys.stdout.write(log_text)
    return exit_code


if __name__ == "__main__":
    sys.exit(main())
