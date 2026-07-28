#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from runner import DEFAULT_IDA_DB_PATH, REPO_ROOT, find_ida_binary, run_ida_script


DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"
IDAPYTHON_SCRIPT_PATH = REPO_ROOT / "tools/ida/apply_path_template_types.py"


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the recovered path-template structs and trusted prototypes to an IDA database."
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
        help="Path to the checked-in path-template type header.",
    )
    narrow_mode = parser.add_mutually_exclusive_group()
    narrow_mode.add_argument(
        "--replay-start-cursor-only",
        action="store_true",
        help=(
            "Rename only the guarded replay-origin cursor fields after "
            "verifying owner sizes, offsets, integral widths, and the "
            "SubgameRuntime-to-Player ownership path."
        ),
    )
    narrow_mode.add_argument(
        "--golb-base-only",
        action="store_true",
        help=(
            "Recover only GolbShot's zero-offset RenderableBod base after "
            "verifying the complete prefix layout and authoritative header."
        ),
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
        raise FileNotFoundError(f"path-template type header not found: {header_path}")
    if not IDAPYTHON_SCRIPT_PATH.is_file():
        raise FileNotFoundError(f"IDAPython sync script not found: {IDAPYTHON_SCRIPT_PATH}")

    script_args = [str(header_path)]
    if args.replay_start_cursor_only:
        script_args.append("--replay-start-cursor-only")
    if args.golb_base_only:
        script_args.append("--golb-base-only")

    exit_code, log_text = run_ida_script(
        ida_bin=ida_bin,
        script_path=IDAPYTHON_SCRIPT_PATH,
        db_path=db_path,
        script_args=script_args,
        log_stem="sync-path-template-types",
    )
    sys.stdout.write(log_text)
    return exit_code


if __name__ == "__main__":
    sys.exit(main())
