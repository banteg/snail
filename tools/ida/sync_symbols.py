#!/usr/bin/env python3

from __future__ import annotations

import argparse
import json
from pathlib import Path
import sys
import tempfile

from runner import DEFAULT_IDA_DB_PATH, REPO_ROOT, find_ida_binary, run_ida_script

DEFAULT_MANIFEST_PATH = REPO_ROOT / "analysis/symbols/gameplay-functions.json"
IDAPYTHON_SCRIPT_PATH = REPO_ROOT / "tools/ida/apply_symbol_manifest.py"


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
    parser.add_argument(
        "--only",
        action="append",
        default=[],
        help="Optional function selector(s) to sync. Matches manifest name, alias, or hex address.",
    )
    return parser.parse_args()


def _parse_address(value: object) -> int:
    if isinstance(value, int):
        return value
    if isinstance(value, str):
        return int(value, 0)
    raise TypeError(f"unsupported address value: {value!r}")


def _select_manifest_functions(
    manifest: dict[str, object], selectors: list[str]
) -> dict[str, object]:
    if not selectors:
        return manifest

    functions = manifest.get("functions")
    if not isinstance(functions, list):
        raise ValueError("manifest field 'functions' must be a list")

    requested = {selector.lower() for selector in selectors}
    selected: list[object] = []
    matched: set[str] = set()
    for function in functions:
        if not isinstance(function, dict):
            raise ValueError("manifest function entries must be objects")
        name = function.get("name")
        address = function.get("address")
        aliases = function.get("aliases", [])
        if not isinstance(name, str) or not name:
            raise ValueError("manifest function entry has an invalid name")
        if not isinstance(aliases, list) or not all(
            isinstance(alias, str) and alias for alias in aliases
        ):
            raise ValueError("manifest function entry has invalid aliases")
        address_hex = f"0x{_parse_address(address):x}"
        selectors_for_function = {
            name.lower(),
            address_hex.lower(),
            *(alias.lower() for alias in aliases),
        }
        hits = requested & selectors_for_function
        if hits:
            selected.append(function)
            matched.update(hits)

    missing = sorted(requested - matched)
    if missing:
        raise RuntimeError(
            "manifest does not contain requested function selector(s): "
            + ", ".join(missing)
        )

    filtered = dict(manifest)
    filtered["functions"] = selected
    return filtered


def _write_filtered_manifest(
    manifest_path: Path, selectors: list[str], directory: Path
) -> Path:
    manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
    if not isinstance(manifest, dict):
        raise ValueError("manifest root must be an object")
    filtered = _select_manifest_functions(manifest, selectors)
    directory.mkdir(parents=True, exist_ok=True)
    filtered_path = directory / manifest_path.name
    filtered_path.write_text(json.dumps(filtered, indent=2) + "\n", encoding="utf-8")
    return filtered_path


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

    with tempfile.TemporaryDirectory(prefix="snail-ida-symbols-") as temp_dir:
        selected_manifest_path = manifest_path
        if args.only:
            selected_manifest_path = _write_filtered_manifest(
                manifest_path,
                list(args.only),
                Path(temp_dir),
            )

        exit_code, log_text = run_ida_script(
            ida_bin=ida_bin,
            script_path=IDAPYTHON_SCRIPT_PATH,
            db_path=db_path,
            script_args=[str(selected_manifest_path)],
            log_stem="sync-symbols",
        )
    sys.stdout.write(log_text)
    return exit_code


if __name__ == "__main__":
    sys.exit(main())
