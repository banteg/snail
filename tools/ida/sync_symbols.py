#!/usr/bin/env python3

from __future__ import annotations

import argparse
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_MANIFEST_PATH = REPO_ROOT / "analysis/symbols/gameplay-functions.json"
DEFAULT_IDA_DB_PATH = REPO_ROOT / "artifacts/ida/SnailMail_unwrapped.exe.i64"
IDAPYTHON_SCRIPT_PATH = REPO_ROOT / "tools/ida/apply_symbol_manifest.py"
STRIP_ENV_VARS = {
    "PYTHONHOME",
    "PYTHONPATH",
    "PYTHONSTARTUP",
    "PYTHONUSERBASE",
    "PYTHONEXECUTABLE",
    "VIRTUAL_ENV",
    "__PYVENV_LAUNCHER__",
}


def find_ida_binary(explicit_path: str | None) -> str:
    if explicit_path:
        return explicit_path

    for candidate in ("idat64", "idat", "ida64", "ida"):
        resolved = shutil.which(candidate)
        if resolved is not None:
            return resolved

    raise FileNotFoundError(
        "could not find an IDA binary on PATH; pass --ida-bin explicitly"
    )


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the tracked Snail Mail symbol manifest to an IDA database."
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
        "--manifest",
        type=Path,
        default=DEFAULT_MANIFEST_PATH,
        help="Path to the tracked gameplay function manifest.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    ida_bin = find_ida_binary(args.ida_bin)
    db_path = args.db.resolve()
    manifest_path = args.manifest.resolve()

    if not db_path.is_file():
        raise FileNotFoundError(f"IDA database not found: {db_path}")
    if not manifest_path.is_file():
        raise FileNotFoundError(f"symbol manifest not found: {manifest_path}")
    if not IDAPYTHON_SCRIPT_PATH.is_file():
        raise FileNotFoundError(f"IDAPython sync script not found: {IDAPYTHON_SCRIPT_PATH}")

    child_env = {
        key: value
        for key, value in os.environ.items()
        if key not in STRIP_ENV_VARS and not key.startswith("UV_")
    }
    log_path = Path(tempfile.gettempdir()) / f"ida-sync-{db_path.stem}.log"
    if log_path.exists():
        log_path.unlink()

    command = [
        ida_bin,
        "-A",
        f"-L{log_path}",
        f"-S{IDAPYTHON_SCRIPT_PATH} {manifest_path}",
        str(db_path),
    ]
    completed = subprocess.run(command, check=False, env=child_env)
    if log_path.is_file():
        sys.stdout.write(log_path.read_text(encoding="utf-8", errors="replace"))
    return completed.returncode


if __name__ == "__main__":
    sys.exit(main())
