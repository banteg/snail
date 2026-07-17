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
    current_type_widths,
    emit_summary,
    types_declare_missing_only,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/warning_types.h"

EXPECTED_STRUCT_SIZES = {
    "Warning": 0x10,
}

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

WARNING_FIELD_UPDATES = (
    ("0x00", "state", "WarningState"),
    ("0x04", "phase", "float"),
    ("0x08", "phase_step", "float"),
    ("0x0c", "border", "FrontendWidget*"),
)

PROTO_UPDATES = (
    ("initialize_warning", "void __thiscall initialize_warning(Warning* warning)"),
    ("uninit_warning", "void __thiscall uninit_warning(Warning* warning)"),
    ("start_warning", "void __thiscall start_warning(Warning* warning)"),
    ("stop_warning", "void __thiscall stop_warning(Warning* warning)"),
    ("stop_warning_sample", "void __thiscall stop_warning_sample(Warning* warning)"),
    ("update_warning", "void __thiscall update_warning(Warning* warning)"),
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

    mismatched_structs = tuple(
        name
        for name, expected_size in EXPECTED_STRUCT_SIZES.items()
        if current_struct_size(
            REPO_ROOT,
            target=args.target,
            struct_name=name,
        )
        != expected_size
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
        )
        type_operation["repaired_types"] = repaired_types
    else:
        type_operation = {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "Warning owner size and WarningState width already current",
            "header": str(header_path),
            "expected_sizes": EXPECTED_STRUCT_SIZES,
            "expected_enum_widths": EXPECTED_ENUM_WIDTHS,
        }

    operations: list[dict[str, object]] = [
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
            struct_updates=(("Warning", WARNING_FIELD_UPDATES),),
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
