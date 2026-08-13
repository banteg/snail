#!/usr/bin/env python3

from __future__ import annotations

import argparse
import sys
from pathlib import Path

from _narrow_sync import (
    apply_struct_and_proto_updates,
    apply_type_renames,
    current_header_type_equivalence,
    current_struct_size,
    current_type_widths,
    emit_summary,
    reanalyze_functions,
    types_declare_missing_only,
)
from _target import DEFAULT_TARGET

REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/completion_types.h"

EXPECTED_STRUCT_SIZES = {
    "cRCompletion": 0x50,
}

SUBGAME_EXPECTED_SIZE = 0x1272838

OWNER_TYPE_RENAMES = (("Completion", "cRCompletion"),)

REANALYSIS_FUNCTIONS = (
    "flush_row_event_display",
    "initialize_completion_screen",
    "update_row_event_display",
    "register_parcel_delivery",
)

COMPLETION_FIELD_UPDATES = (
    ("0x00", "title_widget", "FrontendWidget*"),
    ("0x04", "delivered_count_widget", "FrontendWidget*"),
    ("0x08", "bonus_summary_widget", "FrontendWidget*"),
    ("0x0c", "bonus_icon_widget", "FrontendWidget*"),
    ("0x10", "continue_widget", "FrontendWidget*"),
    ("0x14", "state", "CompletionState"),
    ("0x18", "fast_forward_enabled", "uint8_t"),
    ("0x19", "_pad_19", "uint8_t[0x3]"),
    ("0x1c", "parcel_target_count", "int32_t"),
    ("0x20", "bonus_enabled", "int32_t"),
    ("0x24", "staged_parcel_count", "int32_t"),
    ("0x28", "delivered_parcel_count", "int32_t"),
    ("0x2c", "progress", "float"),
    ("0x30", "progress_step", "float"),
    ("0x34", "widget_world", "Vec3"),
    ("0x40", "bonus_blink_progress", "float"),
    ("0x44", "bonus_blink_step", "float"),
    ("0x48", "bonus_score", "int32_t"),
    ("0x4c", "display_token", "int32_t"),
)

SUBGAME_BOUNDARY_UPDATES = (
    ("0x1270fd4", "enemy_manager", "EnemyManager"),
    ("0x12727d8", "completion", "cRCompletion"),
    ("0x1272828", "times_up", "cRTimesUp"),
)

PROTO_UPDATES = (
    (
        "flush_row_event_display",
        "void __thiscall flush_row_event_display(cRCompletion* completion)",
    ),
    (
        "initialize_completion_screen",
        "void __thiscall initialize_completion_screen(cRCompletion* completion, int32_t delivered_count, uint8_t perfect_delivery)",
    ),
    (
        "update_row_event_display",
        "void __thiscall update_row_event_display(cRCompletion* completion)",
    ),
    (
        "register_parcel_delivery",
        "void __thiscall register_parcel_delivery(cRCompletion* completion)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the exact Windows cRCompletion ownership lane."
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

    subgame_size = current_struct_size(
        REPO_ROOT,
        target=args.target,
        struct_name="cRSubGame",
    )
    if subgame_size != SUBGAME_EXPECTED_SIZE:
        raise RuntimeError(
            "refusing cRCompletion replay with cRSubGame-size mismatch: "
            f"expected {SUBGAME_EXPECTED_SIZE:#x}, observed {subgame_size!r}"
        )

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
            "reason": "cRCompletion owner layout already current",
            "header": str(header_path),
            "expected_sizes": EXPECTED_STRUCT_SIZES,
            "type_equivalence": {
                name: type_equivalence.get(name, False)
                for name in EXPECTED_STRUCT_SIZES
            },
        }

    operations.extend(
        [
            {
                "op": "owner_size_verify",
                "status": "verified",
                "owner_sizes": {"cRSubGame": subgame_size},
            },
            type_operation,
            *apply_struct_and_proto_updates(
                REPO_ROOT,
                target=args.target,
                struct_updates=(
                    ("cRCompletion", COMPLETION_FIELD_UPDATES),
                    ("cRSubGame", SUBGAME_BOUNDARY_UPDATES),
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
