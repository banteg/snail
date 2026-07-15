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
MAX_SUMMARY_ITEMS = 10


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


def _display_path(path: Path) -> str:
    try:
        return str(path.relative_to(REPO_ROOT))
    except ValueError:
        return str(path)


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
        default="SnailMail_unwrapped.exe.bndb",
        help="Binary Ninja target selector for the BN export lane. Defaults to the pinned Snail Mail database.",
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
    parser.add_argument(
        "--skip-health-check",
        action="store_true",
        help="Skip the tracked decompile hotspot health checks after refreshing exports.",
    )
    parser.add_argument(
        "--only",
        action="append",
        default=[],
        help="Optional function selector(s) to refresh. Matches manifest name or hex address.",
    )
    parser.add_argument(
        "--strict",
        action="store_true",
        help="Exit nonzero if mismatches or failing health checks are present.",
    )
    return parser.parse_args()


def _select_manifest_functions(manifest, selectors: list[str]):
    if not selectors:
        return manifest.functions
    requested = {selector.lower() for selector in selectors}
    selected = [
        function
        for function in manifest.functions
        if function.name.lower() in requested or function.address_hex.lower() in requested
    ]
    missing = sorted(
        selector
        for selector in selectors
        if selector.lower() not in {function.name.lower() for function in selected}
        and selector.lower() not in {function.address_hex.lower() for function in selected}
    )
    if missing:
        raise RuntimeError(f"manifest does not contain requested function selector(s): {', '.join(missing)}")
    return selected


def _truncate_list(value: object, *, limit: int = MAX_SUMMARY_ITEMS) -> list[object]:
    if not isinstance(value, list):
        return []
    return value[:limit]


def _failing_health_checks(health_result: dict[str, object] | None) -> list[dict[str, object]]:
    if not isinstance(health_result, dict):
        return []
    checks = health_result.get("checks")
    if not isinstance(checks, list):
        return []
    failing: list[dict[str, object]] = []
    for check in checks:
        if not isinstance(check, dict):
            continue
        if check.get("passed") is False:
            failing.append(check)
    return failing


def main() -> int:
    args = parse_args()
    manifest_path = args.manifest.resolve()
    root = args.root.resolve()
    bn_root = root / "binja"
    ida_root = root / "ida"
    bn_index = bn_root / "index.json"
    ida_index = ida_root / "index.json"

    manifest = load_function_symbol_manifest(manifest_path)
    selected_functions = _select_manifest_functions(manifest, list(args.only))

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
        *[item for selector in args.only for item in ("--only", selector)],
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
        *[item for selector in args.only for item in ("--only", selector)],
    )

    health_result: dict[str, object] | None = None
    if not args.skip_health_check:
        health_result = _run_python(
            REPO_ROOT / "tools/check_decompile_health.py",
        )

    bn_mismatches = _truncate_list(bn_result.get("mismatches"))
    ida_mismatches = _truncate_list(ida_result.get("mismatches"))
    failing_checks = _truncate_list(_failing_health_checks(health_result))

    summary = {
        "manifest": _display_path(manifest_path),
        "root": _display_path(root),
        "function_count": len(selected_functions),
        "bn_index": _display_path(bn_index),
        "ida_index": _display_path(ida_index),
        "bn_exported": len(bn_result.get("exports", [])),
        "ida_exported": len(ida_result.get("exported", [])),
        "bn_mismatch_count": bn_result.get("mismatch_count", 0),
        "ida_mismatch_count": ida_result.get("mismatch_count", 0),
        "total_mismatch_count": bn_result.get("mismatch_count", 0) + ida_result.get("mismatch_count", 0),
        "has_mismatches": bool(bn_result.get("mismatch_count", 0) or ida_result.get("mismatch_count", 0)),
        "sync_ida_symbols": args.sync_ida_symbols,
        "health_check_ran": not args.skip_health_check,
        "strict": args.strict,
    }
    if args.only:
        summary["selected_functions"] = [
            {"name": function.name, "address": function.address_hex}
            for function in selected_functions
        ]
    if bn_mismatches:
        summary["bn_mismatches"] = bn_mismatches
    if ida_mismatches:
        summary["ida_mismatches"] = ida_mismatches
    if health_result is not None:
        summary["health_check_count"] = health_result.get("check_count", 0)
        summary["health_failing_check_count"] = health_result.get("failing_check_count", 0)
        summary["health_passed"] = health_result.get("passed", False)
        summary["health_config"] = health_result.get("config")
        if failing_checks:
            summary["failing_checks"] = failing_checks
    (root / "index.json").write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(summary, indent=2))
    if args.strict and (
        summary["has_mismatches"] or summary.get("health_passed") is False and not args.skip_health_check
    ):
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
