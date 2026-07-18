#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from runner import DEFAULT_IDA_DB_PATH, REPO_ROOT, find_ida_binary, run_ida_script


DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/main_loop_types.h"
IDAPYTHON_SCRIPT_PATH = REPO_ROOT / "tools/ida/apply_main_loop_types.py"


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the recovered WinMain-shaped startup-loop ABI to IDA."
    )
    parser.add_argument(
        "--ida-bin",
        help="Path to the IDA headless binary (defaults to the first idat*/ida* on PATH).",
    )
    parser.add_argument(
        "--db",
        type=Path,
        default=DEFAULT_IDA_DB_PATH,
        help="Path to the IDA database to update.",
    )
    parser.add_argument(
        "--header",
        type=Path,
        default=DEFAULT_HEADER_PATH,
        help="Path to the checked-in main-loop ABI declaration.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    ida_bin = find_ida_binary(args.ida_bin)
    db_path = args.db.resolve()
    header_path = args.header.resolve()

    if not db_path.is_file():
        raise FileNotFoundError(f"IDA database not found: {db_path}")
    if not header_path.is_file():
        raise FileNotFoundError(f"main-loop type header not found: {header_path}")
    if not IDAPYTHON_SCRIPT_PATH.is_file():
        raise FileNotFoundError(
            f"IDAPython sync script not found: {IDAPYTHON_SCRIPT_PATH}"
        )

    exit_code, log_text = run_ida_script(
        ida_bin=ida_bin,
        script_path=IDAPYTHON_SCRIPT_PATH,
        db_path=db_path,
        script_args=[str(header_path)],
        log_stem="sync-main-loop-types",
    )
    sys.stdout.write(log_text)
    return exit_code


if __name__ == "__main__":
    sys.exit(main())
