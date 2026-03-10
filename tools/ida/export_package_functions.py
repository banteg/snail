#!/usr/bin/env python3

from __future__ import annotations

import argparse
import json
from pathlib import Path
import sys

from runner import DEFAULT_IDA_DB_PATH, REPO_ROOT, find_ida_binary, run_ida_script


IDAPYTHON_SCRIPT_PATH = REPO_ROOT / "tools/ida/export_function_artifact.py"


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Export IDA pseudocode artifacts for one or more package metadata manifests."
    )
    parser.add_argument(
        "packages",
        nargs="+",
        type=Path,
        help=(
            "Package directories or selected_symbols.json files. "
            "Exports functions into each package's functions/ directory."
        ),
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
    return parser.parse_args()


def resolve_manifest_and_out_dir(package_arg: Path) -> tuple[Path, Path]:
    path = package_arg.resolve()
    if path.is_dir():
        manifest_path = path / "metadata" / "selected_symbols.json"
        out_dir = path / "functions"
    else:
        manifest_path = path
        out_dir = path.parent.parent / "functions"

    if manifest_path.name != "selected_symbols.json":
        raise ValueError(
            f"expected a package directory or selected_symbols.json, got: {package_arg}"
        )
    return manifest_path, out_dir


def load_manifest_selectors(manifest_path: Path) -> list[str]:
    manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
    selectors: list[str] = []
    for function in manifest.get("functions", []):
        address = function.get("address")
        name = function.get("name")
        if isinstance(address, str) and address:
            selectors.append(address)
        elif isinstance(name, str) and name:
            selectors.append(name)
    return selectors


def export_package(
    *,
    ida_bin: str,
    db_path: Path,
    manifest_path: Path,
    out_dir: Path,
) -> tuple[int, str]:
    if not manifest_path.is_file():
        raise FileNotFoundError(f"package manifest not found: {manifest_path}")

    selectors = load_manifest_selectors(manifest_path)
    if not selectors:
        raise RuntimeError(f"no exportable functions found in manifest: {manifest_path}")

    exit_code, log_text = run_ida_script(
        ida_bin=ida_bin,
        script_path=IDAPYTHON_SCRIPT_PATH,
        db_path=db_path,
        script_args=[str(out_dir), *selectors],
        log_stem=f"export-package-{manifest_path.parent.parent.name}",
    )
    return exit_code, log_text


def main() -> int:
    args = parse_args()
    ida_bin = find_ida_binary(args.ida_bin)
    db_path = args.db.resolve()

    if not db_path.is_file():
        raise FileNotFoundError(f"IDA database not found: {db_path}")
    if not IDAPYTHON_SCRIPT_PATH.is_file():
        raise FileNotFoundError(f"IDAPython export script not found: {IDAPYTHON_SCRIPT_PATH}")

    overall_exit_code = 0
    for package_arg in args.packages:
        manifest_path, out_dir = resolve_manifest_and_out_dir(package_arg)
        exit_code, log_text = export_package(
            ida_bin=ida_bin,
            db_path=db_path,
            manifest_path=manifest_path,
            out_dir=out_dir,
        )
        sys.stdout.write(
            json.dumps(
                {
                    "package": str(manifest_path.parent.parent),
                    "manifest": str(manifest_path),
                    "out_dir": str(out_dir),
                    "exit_code": exit_code,
                }
            )
            + "\n"
        )
        sys.stdout.write(log_text)
        if exit_code != 0:
            overall_exit_code = exit_code

    return overall_exit_code


if __name__ == "__main__":
    sys.exit(main())
