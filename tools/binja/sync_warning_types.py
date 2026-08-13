#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
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


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/warning_types.h"

EXPECTED_STRUCT_SIZES = {
    "cRWarning": 0x10,
}

OWNER_TYPE_RENAMES = (("Warning", "cRWarning"),)

EXPECTED_ENUM_WIDTHS = {
    "WarningState": 0x04,
}

FUNCTION_SYMBOL_UPDATES = (
    ("0x446e80", "initialize_warning"),
    ("0x446f10", "uninit_warning"),
    ("0x446f30", "start_warning"),
    ("0x446f50", "stop_warning"),
    ("0x446f60", "stop_warning_sample"),
    ("0x446f80", "update_warning"),
)

REANALYSIS_FUNCTIONS = (
    "initialize_warning",
    "uninit_warning",
    "start_warning",
    "stop_warning",
    "stop_warning_sample",
    "update_warning",
    "initialize_subgame",
    "destroy_subgame",
    "update_damage_gauge",
    "update_subgoldy",
)

WARNING_FIELD_UPDATES = (
    ("0x00", "state", "WarningState"),
    ("0x04", "phase", "float"),
    ("0x08", "phase_step", "float"),
    ("0x0c", "border", "FrontendWidget*"),
)

PROTO_UPDATES = (
    ("initialize_warning", "void __thiscall initialize_warning(cRWarning* warning)"),
    ("uninit_warning", "void __thiscall uninit_warning(cRWarning* warning)"),
    ("start_warning", "void __thiscall start_warning(cRWarning* warning)"),
    ("stop_warning", "void __thiscall stop_warning(cRWarning* warning)"),
    (
        "stop_warning_sample",
        "void __thiscall stop_warning_sample(cRWarning* warning)",
    ),
    ("update_warning", "void __thiscall update_warning(cRWarning* warning)"),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the exact Windows cRWarning ownership lane."
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
    enum_widths = current_type_widths(
        REPO_ROOT,
        target=args.target,
        type_names=EXPECTED_ENUM_WIDTHS,
    )
    mismatched_enums = tuple(
        name
        for name, expected_width in EXPECTED_ENUM_WIDTHS.items()
        if enum_widths.get(name) != expected_width
    )
    if mismatched_structs or mismatched_enums:
        repaired_types = (*mismatched_structs, *mismatched_enums)
        type_operation = types_declare_missing_only(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            replace_types=repaired_types,
            include_types=EXPECTED_STRUCT_SIZES,
        )
        type_operation["repaired_types"] = repaired_types
    else:
        type_operation = {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "cRWarning owner layout and WarningState width already current",
            "header": str(header_path),
            "expected_sizes": EXPECTED_STRUCT_SIZES,
            "expected_enum_widths": EXPECTED_ENUM_WIDTHS,
            "type_equivalence": {
                name: type_equivalence.get(name, False)
                for name in EXPECTED_STRUCT_SIZES
            },
        }

    operations.extend([
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
                ("cRWarning", WARNING_FIELD_UPDATES),
                ("Player", (("0x3f4", "warning", "cRWarning"),)),
            ),
            proto_updates=PROTO_UPDATES,
        ),
        *reanalyze_functions(
            REPO_ROOT,
            target=args.target,
            identifiers=REANALYSIS_FUNCTIONS,
        ),
    ])
    return emit_summary(
        repo_root=REPO_ROOT,
        target=args.target,
        header_path=header_path,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
