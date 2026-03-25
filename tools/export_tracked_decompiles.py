#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
from pathlib import Path
import subprocess
import sys


REPO_ROOT = Path(__file__).resolve().parents[1]
SRC_ROOT = REPO_ROOT / "src"
if str(SRC_ROOT) not in sys.path:
    sys.path.insert(0, str(SRC_ROOT))

from snail.symbols import DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH, load_function_symbol_manifest  # noqa: E402


DEFAULT_ROOT = REPO_ROOT / "analysis/decompile"


def _run_python(script: Path, *args: str) -> dict[str, object]:
    completed = subprocess.run(
        ["uv", "run", "python", str(script), *args],
        cwd=REPO_ROOT,
        check=False,
        text=True,
        capture_output=True,
    )
    if completed.returncode != 0:
        raise RuntimeError(
            f"{script.name} failed with exit code {completed.returncode}:"
            f"\nSTDOUT:\n{completed.stdout}\nSTDERR:\n{completed.stderr}"
        )
    stdout = completed.stdout.strip()
    if not stdout:
        raise RuntimeError(f"{script.name} did not produce JSON output")
    try:
        return json.loads(stdout)
    except json.JSONDecodeError as exc:
        raise RuntimeError(
            f"{script.name} did not produce valid JSON:\n{stdout}"
        ) from exc


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Refresh tracked Binary Ninja and IDA decompile artifacts for all named functions in the manifest."
    )
    parser.add_argument(
        "--manifest",
        type=Path,
        default=DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
        help="Path to the tracked gameplay function manifest.",
    )
    parser.add_argument(
        "--bn-target",
        default="active",
        help="Binary Ninja target selector for the BN export lane.",
    )
    parser.add_argument(
        "--ida-bin",
        help="Optional explicit IDA binary for the IDA export lane.",
    )
    parser.add_argument(
        "--ida-db",
        type=Path,
        help="Optional explicit IDA database for the IDA export lane.",
    )
    parser.add_argument(
        "--root",
        type=Path,
        default=DEFAULT_ROOT,
        help="Tracked decompile root under analysis/.",
    )
    parser.add_argument(
        "--sync-ida-symbols",
        action="store_true",
        help="Apply the tracked symbol manifest to the IDA database before exporting.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    manifest_path = args.manifest.resolve()
    root = args.root.resolve()
    bn_root = root / "binja"
    ida_root = root / "ida"
    bn_index = bn_root / "index.json"
    ida_index = ida_root / "index.json"

    manifest = load_function_symbol_manifest(manifest_path)

    if args.sync_ida_symbols:
        sync_args = ["--manifest", str(manifest_path)]
        if args.ida_bin:
            sync_args.extend(["--ida-bin", args.ida_bin])
        if args.ida_db:
            sync_args.extend(["--db", str(args.ida_db.resolve())])
        subprocess.run(
            ["uv", "run", "python", "tools/ida/sync_symbols.py", *sync_args],
            cwd=REPO_ROOT,
            check=True,
            text=True,
        )

    bn_result = _run_python(
        REPO_ROOT / "tools/binja/export_manifest_functions.py",
        "--manifest",
        str(manifest_path),
        "--target",
        args.bn_target,
        "--out-dir",
        str((bn_root / "functions").resolve()),
        "--index",
        str(bn_index),
    )

    ida_args = [
        "--manifest",
        str(manifest_path),
        "--out-dir",
        str((ida_root / "functions").resolve()),
        "--index",
        str(ida_index),
    ]
    if args.ida_bin:
        ida_args.extend(["--ida-bin", args.ida_bin])
    if args.ida_db:
        ida_args.extend(["--db", str(args.ida_db.resolve())])
    ida_result = _run_python(
        REPO_ROOT / "tools/ida/export_manifest_functions.py",
        *ida_args,
    )

    summary = {
        "manifest": str(manifest_path.relative_to(REPO_ROOT)),
        "root": str(root.relative_to(REPO_ROOT)),
        "function_count": len(manifest.functions),
        "bn_index": str(bn_index.relative_to(REPO_ROOT)),
        "ida_index": str(ida_index.relative_to(REPO_ROOT)),
        "bn_exported": bn_result.get("function_count"),
        "ida_exported": len(ida_result.get("exported", [])),
        "sync_ida_symbols": args.sync_ida_symbols,
    }
    (root / "index.json").write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(summary, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
