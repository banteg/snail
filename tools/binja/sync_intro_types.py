#!/usr/bin/env python3

from __future__ import annotations

import argparse
import sys
from pathlib import Path

from _narrow_sync import (
    apply_struct_and_proto_updates,
    apply_type_renames,
    current_header_type_equivalence,
    current_type_widths,
    emit_summary,
    types_declare_missing_only,
)
from _target import DEFAULT_TARGET


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_intro_types.h"

EXPECTED_STRUCT_SIZES = {
    "cRIntro": 0x48,
}

GAME_ROOT_FIELD_UPDATES = (("0x4f2dc", "intro", "cRIntro"),)

TYPE_RENAMES = (("Intro", "cRIntro"),)

PROTO_UPDATES = (
    (
        "initialize_new_game_menu",
        "void __thiscall initialize_new_game_menu(cRIntro* intro)",
    ),
    (
        "update_new_game_menu",
        "void __thiscall update_new_game_menu(cRIntro* intro)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the narrow cRIntro ownership slice to Binary Ninja."
    )
    parser.add_argument(
        "--target", default=DEFAULT_TARGET, help="Binary Ninja target selector."
    )
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

    type_rename_operations = apply_type_renames(
        REPO_ROOT,
        target=args.target,
        renames=TYPE_RENAMES,
    )
    observed_widths = current_type_widths(
        REPO_ROOT,
        target=args.target,
        type_names=EXPECTED_STRUCT_SIZES,
    )
    type_equivalence = current_header_type_equivalence(
        REPO_ROOT,
        target=args.target,
        header_path=header_path,
    )
    mismatched_types = tuple(
        name
        for name, expected_size in EXPECTED_STRUCT_SIZES.items()
        if (
            observed_widths.get(name) != expected_size
            or not type_equivalence.get(name, False)
        )
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
            "reason": "intro owner size already current",
            "header": str(header_path),
            "expected_sizes": EXPECTED_STRUCT_SIZES,
            "type_equivalence": type_equivalence,
        }

    operations: list[dict[str, object]] = [
        *type_rename_operations,
        type_operation,
        *apply_struct_and_proto_updates(
            REPO_ROOT,
            target=args.target,
            struct_updates=(("GameRoot", GAME_ROOT_FIELD_UPDATES),),
            proto_updates=PROTO_UPDATES,
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
