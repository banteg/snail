#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
from pathlib import Path
import sys


REPO_ROOT = Path(__file__).resolve().parents[2]
SRC_ROOT = REPO_ROOT / "src"
if str(SRC_ROOT) not in sys.path:
    sys.path.insert(0, str(SRC_ROOT))

from snail.symbols import (  # noqa: E402
    DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
    FunctionSymbol,
    build_function_symbol_manifest,
    is_curated_function_name,
    load_function_symbol_manifest,
    summarize_function_symbol_manifest,
    write_function_symbol_manifest,
)


def _load_binary_view(binary_path: Path | None):
    import binaryninja as bn

    if binary_path is None:
        current = globals().get("current_view")
        if current is None:
            raise SystemExit(
                "No current Binary Ninja view is open. Pass --binary or run this inside Binary Ninja."
            )
        return current

    view = bn.load(str(binary_path))
    if view is None:
        raise SystemExit(f"Failed to load Binary Ninja view from {binary_path}")
    return view


def _export_curated_function_symbols(view) -> list[FunctionSymbol]:
    symbols: list[FunctionSymbol] = []
    for function in sorted(view.functions, key=lambda current: int(current.start)):
        name = function.name
        if not is_curated_function_name(name):
            continue
        description = getattr(function, "comment", None)
        if isinstance(description, str):
            description = description.strip() or None
        else:
            description = None
        symbols.append(
            FunctionSymbol(
                address=int(function.start),
                name=name,
                description=description,
            )
        )
    return symbols


def _export_manifest(args: argparse.Namespace) -> int:
    view = _load_binary_view(args.binary)
    template = load_function_symbol_manifest(args.manifest)
    manifest = build_function_symbol_manifest(
        template,
        _export_curated_function_symbols(view),
    )

    output_path = args.output or args.manifest
    write_function_symbol_manifest(manifest, output_path)

    print(
        json.dumps(
            {
                **summarize_function_symbol_manifest(manifest, path=output_path),
                "binary_view": getattr(getattr(view, "file", None), "filename", None),
            },
            indent=2,
            sort_keys=True,
        )
    )
    return 0


def _apply_manifest(args: argparse.Namespace) -> int:
    view = _load_binary_view(args.binary)
    manifest = load_function_symbol_manifest(args.manifest)

    renamed: list[dict[str, str]] = []
    commented: list[dict[str, str]] = []
    skipped: list[dict[str, str]] = []
    missing: list[dict[str, str]] = []
    conflicts: list[dict[str, str]] = []

    for symbol in manifest.functions:
        function = view.get_function_at(symbol.address)
        if function is None:
            missing.append({"address": symbol.address_hex, "expected": symbol.name})
            continue

        current_name = function.name
        if current_name == symbol.name:
            skipped.append({"address": symbol.address_hex, "name": symbol.name})
            continue
        if is_curated_function_name(current_name) and not args.replace_existing:
            conflicts.append(
                {
                    "address": symbol.address_hex,
                    "expected": symbol.name,
                    "current": current_name,
                }
            )
            continue

        if not args.dry_run:
            function.name = symbol.name
        renamed.append(
            {
                "address": symbol.address_hex,
                "old_name": current_name,
                "new_name": symbol.name,
            }
        )
        current_comment = getattr(function, "comment", None)
        if isinstance(current_comment, str):
            current_comment = current_comment.strip() or None
        else:
            current_comment = None
        if symbol.description is not None and current_comment != symbol.description:
            if not args.dry_run:
                function.comment = symbol.description
            commented.append(
                {
                    "address": symbol.address_hex,
                    "name": symbol.name,
                }
            )

    report = {
        "manifest": str(args.manifest),
        "binary_view": getattr(getattr(view, "file", None), "filename", None),
        "renamed_count": len(renamed),
        "commented_count": len(commented),
        "skipped_count": len(skipped),
        "missing_count": len(missing),
        "conflict_count": len(conflicts),
        "renamed_preview": renamed[:12],
        "commented_preview": commented[:12],
        "missing_preview": missing[:12],
        "conflict_preview": conflicts[:12],
        "dry_run": args.dry_run,
        "replace_existing": args.replace_existing,
        "note": "Save the Binary Ninja database after apply if you ran this inside the GUI.",
    }
    print(json.dumps(report, indent=2, sort_keys=True))
    return 0


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="Export or apply the tracked Snail Mail gameplay function symbols in Binary Ninja."
    )
    subparsers = parser.add_subparsers(dest="command", required=True)

    export_parser = subparsers.add_parser(
        "export",
        help="Export curated function names from the current Binary Ninja view into the tracked manifest.",
    )
    export_parser.add_argument(
        "--manifest",
        type=Path,
        default=DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
        help="Template manifest that provides metadata and the default output path.",
    )
    export_parser.add_argument(
        "--output",
        type=Path,
        help="Optional explicit output path for the exported manifest.",
    )
    export_parser.add_argument(
        "--binary",
        type=Path,
        help="Optional binary or .bndb path when running outside the Binary Ninja GUI.",
    )

    apply_parser = subparsers.add_parser(
        "apply",
        help="Apply the tracked manifest onto the current Binary Ninja view.",
    )
    apply_parser.add_argument(
        "--manifest",
        type=Path,
        default=DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
        help="Tracked manifest to apply.",
    )
    apply_parser.add_argument(
        "--binary",
        type=Path,
        help="Optional binary or .bndb path when running outside the Binary Ninja GUI.",
    )
    apply_parser.add_argument(
        "--dry-run",
        action="store_true",
        help="Report the planned renames without changing the Binary Ninja database.",
    )
    apply_parser.add_argument(
        "--replace-existing",
        action="store_true",
        help="Overwrite already-curated names instead of treating them as conflicts.",
    )

    return parser


def main(argv: list[str] | None = None) -> int:
    parser = build_parser()
    args = parser.parse_args(argv)

    if args.command == "export":
        return _export_manifest(args)
    return _apply_manifest(args)


if __name__ == "__main__":
    raise SystemExit(main())
