#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_struct_and_proto_updates,
    apply_symbol_updates,
    current_struct_size,
    emit_summary,
    types_declare_missing_only,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_logo_types.h"

EXPECTED_STRUCT_SIZES = {
    "LogoLetter": 0x90,
    "Logo": 0x25218,
}

GAME_ROOT_FIELD_UPDATES = (
    ("0x4f400", "logo", "Logo"),
)

DATA_SYMBOL_UPDATES = (
    ("0x497310", "g_logo_letter_vtable"),
)

PROTO_UPDATES = (
    (
        "initialize_intro_logo_renderable",
        "LogoLetter* __thiscall initialize_intro_logo_renderable(LogoLetter* letter)",
    ),
    ("open_logo", "int32_t __thiscall open_logo(Logo* logo)"),
    (
        "initialize_intro_screen",
        "void __thiscall initialize_intro_screen(Logo* logo, char* file_name)",
    ),
    ("destroy_intro_screen", "int32_t __thiscall destroy_intro_screen(Logo* logo)"),
    ("update_intro_screen", "void __thiscall update_intro_screen(Logo* logo)"),
    (
        "update_intro_logo_renderable",
        "void __thiscall update_intro_logo_renderable(LogoLetter* letter)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the narrow cRLogo ownership slice to Binary Ninja."
    )
    parser.add_argument("--target", default=DEFAULT_TARGET, help="Binary Ninja target selector.")
    parser.add_argument(
        "--header",
        type=Path,
        default=DEFAULT_HEADER_PATH,
        help="Narrow Binary Ninja type header.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    mismatched_types = tuple(
        name
        for name, expected_size in EXPECTED_STRUCT_SIZES.items()
        if current_struct_size(REPO_ROOT, target=args.target, struct_name=name) != expected_size
    )
    if mismatched_types:
        type_operation = types_declare_missing_only(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            replace_types=mismatched_types,
            include_types=EXPECTED_STRUCT_SIZES,
        )
        type_operation["repaired_types"] = mismatched_types
        type_operation["expected_sizes"] = {
            name: EXPECTED_STRUCT_SIZES[name] for name in mismatched_types
        }
    else:
        type_operation = {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "logo owner sizes already current",
            "header": str(header_path),
            "expected_sizes": EXPECTED_STRUCT_SIZES,
        }

    operations: list[dict[str, object]] = [
        type_operation,
        *apply_struct_and_proto_updates(
            REPO_ROOT,
            target=args.target,
            struct_updates=(("GameRoot", GAME_ROOT_FIELD_UPDATES),),
            proto_updates=PROTO_UPDATES,
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=DATA_SYMBOL_UPDATES,
            kind="data",
        ),
    ]
    return emit_summary(
        repo_root=REPO_ROOT,
        target=args.target,
        header_path=header_path,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
