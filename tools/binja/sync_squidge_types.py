#!/usr/bin/env python3

from __future__ import annotations

import argparse
import sys
from pathlib import Path

from _narrow_sync import (
    apply_struct_and_proto_updates,
    apply_symbol_updates,
    apply_type_renames,
    current_header_type_equivalence,
    current_type_widths,
    emit_summary,
    reanalyze_functions,
    types_declare_missing_only,
)
from _target import DEFAULT_TARGET

REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/squidge_types.h"

EXPECTED_STRUCT_SIZES = {
    "cRSquidge": 0x18,
}

OWNER_TYPE_RENAMES = (("Squidge", "cRSquidge"),)

FUNCTION_SYMBOL_UPDATES = (
    ("0x444960", "initialize_squidge"),
    ("0x444980", "start_squidge_y"),
    ("0x4449a0", "start_squidge_z"),
    ("0x4449c0", "update_squidge"),
)

REANALYSIS_FUNCTIONS = (
    "initialize_squidge",
    "start_squidge_y",
    "start_squidge_z",
    "update_squidge",
    "try_enter_track_attachment_from_swept_motion",
    "initialize_subgoldy",
    "update_subgoldy",
)

SQUIDGE_FIELD_UPDATES = (
    ("0x00", "y_output", "float"),
    ("0x04", "y_velocity", "float"),
    ("0x08", "y_phase", "float"),
    ("0x0c", "z_output", "float"),
    ("0x10", "z_velocity", "float"),
    ("0x14", "z_phase", "float"),
)

PROTO_UPDATES = (
    (
        "initialize_squidge",
        "void __thiscall initialize_squidge(cRSquidge* squidge)",
    ),
    (
        "start_squidge_y",
        "void __thiscall start_squidge_y(cRSquidge* squidge, float value)",
    ),
    (
        "start_squidge_z",
        "void __thiscall start_squidge_z(cRSquidge* squidge, float value)",
    ),
    (
        "update_squidge",
        "void __thiscall update_squidge(cRSquidge* squidge)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the exact Windows cRSquidge ownership lane."
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

    operations = apply_type_renames(
        REPO_ROOT,
        target=args.target,
        renames=OWNER_TYPE_RENAMES,
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
    mismatched_structs = tuple(
        name
        for name, expected_size in EXPECTED_STRUCT_SIZES.items()
        if (
            observed_widths.get(name) != expected_size
            or not type_equivalence.get(name, False)
        )
    )
    if mismatched_structs:
        type_operation = types_declare_missing_only(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            replace_types=mismatched_structs,
            include_types=EXPECTED_STRUCT_SIZES,
        )
        type_operation["repaired_types"] = mismatched_structs
    else:
        type_operation = {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "cRSquidge owner layout already current",
            "header": str(header_path),
            "expected_sizes": EXPECTED_STRUCT_SIZES,
            "type_equivalence": {
                name: type_equivalence.get(name, False)
                for name in EXPECTED_STRUCT_SIZES
            },
        }

    operations.extend(
        [
            type_operation,
            *apply_symbol_updates(
                REPO_ROOT,
                target=args.target,
                updates=FUNCTION_SYMBOL_UPDATES,
                kind="function",
            ),
            *apply_struct_and_proto_updates(
                REPO_ROOT,
                target=args.target,
                struct_updates=(
                    ("cRSquidge", SQUIDGE_FIELD_UPDATES),
                    (
                        "Player",
                        (("0x4344", "squidge", "cRSquidge"),),
                    ),
                ),
                proto_updates=PROTO_UPDATES,
            ),
            *reanalyze_functions(
                REPO_ROOT,
                target=args.target,
                identifiers=REANALYSIS_FUNCTIONS,
            ),
        ]
    )
    return emit_summary(
        repo_root=REPO_ROOT,
        target=args.target,
        header_path=header_path,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
