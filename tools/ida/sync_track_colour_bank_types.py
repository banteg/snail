#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import shutil
import sys
import tempfile

from runner import DEFAULT_IDA_DB_PATH, REPO_ROOT, find_ida_binary, run_ida_script


DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/track_colour_bank_types.h"
IDAPYTHON_SCRIPT_PATH = REPO_ROOT / "tools/ida/apply_track_colour_bank_types.py"


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Preview on a temporary database, then replay recovered track-colour "
            "ownership to IDA."
        )
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
        help="Checked-in track-colour ownership header.",
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
        raise FileNotFoundError(f"track-colour type header not found: {header_path}")
    if not IDAPYTHON_SCRIPT_PATH.is_file():
        raise FileNotFoundError(
            f"IDAPython track-colour sync script not found: {IDAPYTHON_SCRIPT_PATH}"
        )

    with tempfile.TemporaryDirectory(prefix="snail-ida-track-colour-preview-") as temp_dir:
        preview_db_path = Path(temp_dir) / db_path.name
        shutil.copy2(db_path, preview_db_path)
        preview_exit_code, preview_log_text = run_ida_script(
            ida_bin=ida_bin,
            script_path=IDAPYTHON_SCRIPT_PATH,
            db_path=preview_db_path,
            script_args=[str(header_path)],
            log_stem="preview-track-colour-bank-types",
        )
        sys.stdout.write(preview_log_text)
        if preview_exit_code:
            return preview_exit_code

    exit_code, log_text = run_ida_script(
        ida_bin=ida_bin,
        script_path=IDAPYTHON_SCRIPT_PATH,
        db_path=db_path,
        script_args=[str(header_path)],
        log_stem="sync-track-colour-bank-types",
    )
    sys.stdout.write(log_text)
    return exit_code


if __name__ == "__main__":
    sys.exit(main())
