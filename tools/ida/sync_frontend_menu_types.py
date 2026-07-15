#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from runner import DEFAULT_IDA_DB_PATH, REPO_ROOT, find_ida_binary, run_ida_script


DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_frontend_menu_types.h"
IDAPYTHON_SCRIPT_PATH = REPO_ROOT / "tools/ida/apply_frontend_menu_types.py"


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the contiguous cRMainMenu/cROptions/cRExit owners to IDA."
    )
    parser.add_argument("--ida-bin", help="Optional explicit IDA headless binary.")
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
        help="Shared front-end menu ownership header.",
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
        raise FileNotFoundError(f"front-end menu type header not found: {header_path}")

    exit_code, log_text = run_ida_script(
        ida_bin=ida_bin,
        script_path=IDAPYTHON_SCRIPT_PATH,
        db_path=db_path,
        script_args=[str(header_path)],
        log_stem="sync-frontend-menu-types",
    )
    sys.stdout.write(log_text)
    return exit_code


if __name__ == "__main__":
    sys.exit(main())
