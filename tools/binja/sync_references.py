#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
from pathlib import Path
import re
import subprocess
import sys
import tempfile
from typing import Any

from _target import DEFAULT_TARGET


REPO_ROOT = Path(__file__).resolve().parents[2]
SRC_ROOT = REPO_ROOT / "src"
if str(SRC_ROOT) not in sys.path:
    sys.path.insert(0, str(SRC_ROOT))

from snail.symbols import is_auto_function_name  # noqa: E402


DEFAULT_MANIFEST_PATH = REPO_ROOT / "analysis/symbols/gameplay-references.json"
SYNCED_REFERENCE_KINDS = {
    "function": "function",
    "jump_table": "data",
    "lookup_table": "data",
}
TABLE_REFERENCE_KINDS = frozenset(("jump_table", "lookup_table"))
REFERENCE_SCOPES = frozenset(("functions", "tables", "all"))


def _parse_address(value: object) -> int:
    if isinstance(value, int):
        return value
    if isinstance(value, str):
        return int(value, 0)
    raise TypeError(f"unsupported address value: {value!r}")


def _load_references(path: Path) -> list[dict[str, Any]]:
    raw = json.loads(path.read_text(encoding="utf-8"))
    symbols = raw.get("symbols")
    if not isinstance(symbols, list):
        raise ValueError("reference manifest field 'symbols' must be a list")

    entries: list[dict[str, Any]] = []
    for index, symbol in enumerate(symbols):
        if not isinstance(symbol, dict):
            raise ValueError(f"symbol entry {index} must be an object")
        kind = symbol.get("kind")
        if kind not in SYNCED_REFERENCE_KINDS:
            continue

        name = symbol.get("name")
        if not isinstance(name, str) or not name:
            raise ValueError(f"reference entry {index} has invalid name")
        aliases = symbol.get("aliases", [])
        if aliases is None:
            aliases = []
        if not isinstance(aliases, list) or not all(
            isinstance(alias, str) for alias in aliases
        ):
            raise ValueError(f"reference entry {index} has invalid aliases")
        description = symbol.get("description")
        if description is not None and not isinstance(description, str):
            raise ValueError(f"reference entry {index} has invalid description")

        entries.append(
            {
                "address": _parse_address(symbol["address"]),
                "name": name,
                "kind": kind,
                "bn_kind": SYNCED_REFERENCE_KINDS[kind],
                "aliases": aliases,
                "description": description,
            }
        )
    return entries


def _run_bn_json(args: list[str]) -> Any:
    with tempfile.NamedTemporaryFile(suffix=".json", delete=False) as handle:
        out_path = Path(handle.name)
    try:
        completed = subprocess.run(
            ["bn", *args, "--format", "json", "--out", str(out_path)],
            cwd=REPO_ROOT,
            check=False,
            text=True,
            capture_output=True,
        )
        if completed.returncode != 0:
            raise RuntimeError(
                f"bn {' '.join(args)} failed with exit code {completed.returncode}:"
                f"\nSTDOUT:\n{completed.stdout}\nSTDERR:\n{completed.stderr}"
            )
        return json.loads(out_path.read_text(encoding="utf-8"))
    finally:
        out_path.unlink(missing_ok=True)


def _load_live_functions(target: str) -> dict[int, dict[str, Any]]:
    payload = _run_bn_json(["function", "list", "--target", target])
    if not isinstance(payload, list):
        raise RuntimeError("unexpected `bn function list` JSON shape")

    live: dict[int, dict[str, Any]] = {}
    for entry in payload:
        if not isinstance(entry, dict):
            continue
        address = entry.get("address")
        if not isinstance(address, str):
            continue
        live[int(address, 0)] = entry
    return live


def _load_live_table_symbols(
    target: str, symbols: list[dict[str, Any]]
) -> dict[int, dict[str, Any]]:
    addresses = [
        int(symbol["address"])
        for symbol in symbols
        if symbol["kind"] in TABLE_REFERENCE_KINDS
    ]
    if not addresses:
        return {}

    code = (
        f"addresses = {addresses!r}; "
        "result = [{'address': hex(address), "
        "'name': symbol.name if symbol else None, "
        "'symbol_type': str(symbol.type) if symbol else None} "
        "for address in addresses for symbol in [bv.get_symbol_at(address)]]"
    )
    payload = _run_bn_json(
        ["py", "exec", "--target", target, "--code", code]
    )
    rows = payload.get("result") if isinstance(payload, dict) else None
    if not isinstance(rows, list):
        raise RuntimeError("unexpected `bn py exec` table-symbol JSON shape")

    live: dict[int, dict[str, Any]] = {}
    for row in rows:
        if not isinstance(row, dict):
            continue
        address = row.get("address")
        if not isinstance(address, str):
            continue
        live[int(address, 0)] = row
    return live


def _is_auto_reference_name(symbol: dict[str, Any], current_name: str) -> bool:
    if symbol["kind"] == "function":
        return is_auto_function_name(current_name)
    if symbol["kind"] not in TABLE_REFERENCE_KINDS:
        return False

    match = re.fullmatch(
        rf"{re.escape(str(symbol['kind']))}_([0-9a-fA-F]+)", current_name
    )
    return match is not None and int(match.group(1), 16) == int(symbol["address"])


def _sync_reference(
    *,
    symbol: dict[str, Any],
    current_name: str,
    target: str,
    dry_run: bool,
    replace_existing: bool,
    skip_comments: bool,
) -> dict[str, Any]:
    address = int(symbol["address"])
    address_text = f"0x{address:x}"
    expected_name = str(symbol["name"])
    aliases = set(symbol["aliases"])

    result: dict[str, Any] = {
        "address": address_text,
        "current": current_name,
        "expected": expected_name,
    }

    should_rename = current_name != expected_name
    if should_rename:
        safe_to_rename = (
            replace_existing
            or _is_auto_reference_name(symbol, current_name)
            or current_name in aliases
        )
        if not safe_to_rename:
            return {
                **result,
                "status": "conflict",
                "reason": "current name is curated and not listed as an alias",
            }
        result["rename"] = True
        if not dry_run:
            rename_result = _run_bn_json(
                [
                    "symbol",
                    "rename",
                    "--target",
                    target,
                    "--kind",
                    str(symbol["bn_kind"]),
                    address_text,
                    expected_name,
                ]
            )
            result["rename_result"] = rename_result.get("success", True)
    else:
        result["rename"] = False

    description = symbol.get("description")
    if description and not skip_comments:
        result["comment"] = True
        if not dry_run:
            comment_scope = (
                ["--function", address_text]
                if symbol["bn_kind"] == "function"
                else ["--address", address_text]
            )
            comment_result = _run_bn_json(
                [
                    "comment",
                    "set",
                    "--target",
                    target,
                    *comment_scope,
                    description,
                ]
            )
            result["comment_result"] = comment_result.get("success", True)
    else:
        result["comment"] = False

    result["status"] = "planned" if dry_run else "synced"
    return result


def _save_snapshot(target: str) -> Any:
    return _run_bn_json(
        [
            "py",
            "exec",
            "--target",
            target,
            "--code",
            "saved = bv.file.save_auto_snapshot(); result = {'saved': saved}",
        ]
    )


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Apply tracked Snail Mail function and compiler-table references "
            "to an open Binary Ninja database."
        )
    )
    parser.add_argument(
        "--manifest",
        type=Path,
        default=DEFAULT_MANIFEST_PATH,
        help="Path to the tracked gameplay reference manifest.",
    )
    parser.add_argument(
        "--target",
        default=DEFAULT_TARGET,
        help="Binary Ninja target selector. Defaults to the Snail Mail database.",
    )
    parser.add_argument(
        "--scope",
        choices=sorted(REFERENCE_SCOPES),
        default="functions",
        help=(
            "Reference kinds to synchronize: functions (the backward-compatible "
            "default), compiler tables, or all supported references."
        ),
    )
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="Report planned reference renames/comments without changing Binary Ninja.",
    )
    parser.add_argument(
        "--replace-existing",
        action="store_true",
        help="Overwrite curated names even when they are not listed as aliases.",
    )
    parser.add_argument(
        "--skip-comments",
        action="store_true",
        help="Rename symbols only; do not set comments.",
    )
    parser.add_argument(
        "--save",
        action="store_true",
        help="Save a Binary Ninja auto snapshot after applying changes.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    manifest_path = args.manifest.resolve()
    symbols = _load_references(manifest_path)
    if args.scope == "functions":
        symbols = [symbol for symbol in symbols if symbol["kind"] == "function"]
    elif args.scope == "tables":
        symbols = [
            symbol for symbol in symbols if symbol["kind"] in TABLE_REFERENCE_KINDS
        ]
    live_functions = (
        _load_live_functions(args.target)
        if any(symbol["kind"] == "function" for symbol in symbols)
        else {}
    )
    live_tables = _load_live_table_symbols(args.target, symbols)

    entries: list[dict[str, Any]] = []
    missing: list[dict[str, str]] = []
    conflicts: list[dict[str, Any]] = []
    sync_candidates: list[tuple[dict[str, Any], str]] = []
    for symbol in symbols:
        address = int(symbol["address"])
        live = (
            live_functions.get(address)
            if symbol["bn_kind"] == "function"
            else live_tables.get(address)
        )
        if live is None:
            missing.append(
                {
                    "address": f"0x{address:x}",
                    "kind": str(symbol["kind"]),
                    "expected": str(symbol["name"]),
                }
            )
            continue
        current_name = live.get("name")
        if not isinstance(current_name, str):
            missing.append(
                {
                    "address": f"0x{address:x}",
                    "kind": str(symbol["kind"]),
                    "expected": str(symbol["name"]),
                }
            )
            continue
        symbol_type = live.get("symbol_type")
        if (
            symbol["bn_kind"] == "data"
            and isinstance(symbol_type, str)
            and not symbol_type.endswith("DataSymbol")
        ):
            entry = {
                "address": f"0x{address:x}",
                "current": current_name,
                "expected": str(symbol["name"]),
                "status": "conflict",
                "reason": f"address resolves to {symbol_type}, not a data symbol",
            }
            conflicts.append(entry)
            entries.append(entry)
            continue
        entry = _sync_reference(
            symbol=symbol,
            current_name=current_name,
            target=args.target,
            dry_run=True,
            replace_existing=args.replace_existing,
            skip_comments=args.skip_comments,
        )
        if entry.get("status") == "conflict":
            conflicts.append(entry)
        else:
            sync_candidates.append((symbol, current_name))
        entries.append(entry)

    if not args.dry_run and not conflicts:
        applied_by_address: dict[str, dict[str, Any]] = {}
        for symbol, current_name in sync_candidates:
            entry = _sync_reference(
                symbol=symbol,
                current_name=current_name,
                target=args.target,
                dry_run=False,
                replace_existing=args.replace_existing,
                skip_comments=args.skip_comments,
            )
            applied_by_address[str(entry["address"])] = entry
        entries = [
            applied_by_address.get(str(entry["address"]), entry) for entry in entries
        ]

    save_result = None
    if args.save and not args.dry_run and not conflicts:
        save_result = _save_snapshot(args.target)

    renamed = [entry for entry in entries if entry.get("rename") is True]
    commented = [entry for entry in entries if entry.get("comment") is True]
    report = {
        "manifest": str(manifest_path),
        "target": args.target,
        "scope": args.scope,
        "reference_count": len(symbols),
        "function_reference_count": sum(
            symbol["kind"] == "function" for symbol in symbols
        ),
        "table_reference_count": sum(
            symbol["kind"] in TABLE_REFERENCE_KINDS for symbol in symbols
        ),
        "renamed_count": len(renamed),
        "commented_count": len(commented),
        "missing_count": len(missing),
        "conflict_count": len(conflicts),
        "dry_run": args.dry_run,
        "apply_blocked_by_conflicts": not args.dry_run and bool(conflicts),
        "replace_existing": args.replace_existing,
        "skip_comments": args.skip_comments,
        "save_requested": args.save,
        "save_result": save_result,
        "renamed_preview": renamed[:20],
        "commented_preview": commented[:20],
        "missing_preview": missing[:20],
        "conflicts": conflicts[:20],
    }
    print(json.dumps(report, indent=2, sort_keys=True))
    return 1 if conflicts else 0


if __name__ == "__main__":
    raise SystemExit(main())
