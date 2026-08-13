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
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/time_types.h"

EXPECTED_STRUCT_SIZES = {
    "cRTime": 0x18,
}

OWNER_TYPE_RENAMES = (("Time", "cRTime"),)

FUNCTION_SYMBOL_UPDATES = (
    ("0x441b70", "zero_timer_counters"),
    ("0x441b90", "advance_timer_counters"),
)

REANALYSIS_FUNCTIONS = (
    "zero_timer_counters",
    "advance_timer_counters",
    "format_time_trial_string",
    "initialize_high_score_entry",
    "update_challenge_setup_screen",
    "populate_runtime_track_cells_from_segments",
    "initialize_subgame",
    "reset_subgame",
    "update_subgame",
    "update_subgoldy",
)

TIME_FIELD_UPDATES = (
    ("0x00", "total_seconds", "float"),
    ("0x04", "minutes", "int32_t"),
    ("0x08", "seconds", "int32_t"),
    ("0x0c", "display_hundredths", "int32_t"),
    ("0x10", "display_thousandths", "int32_t"),
    ("0x14", "second_fraction", "float"),
)

PROTO_UPDATES = (
    (
        "zero_timer_counters",
        "void __thiscall zero_timer_counters(cRTime* time)",
    ),
    (
        "advance_timer_counters",
        "void __thiscall advance_timer_counters(cRTime* time, float delta_ticks)",
    ),
    (
        "format_time_trial_string",
        "char* __thiscall format_time_trial_string(TimeTrial* time_trial, cRTime* timer)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the exact Windows cRTime ownership lane."
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
            "reason": "cRTime owner layout already current",
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
                    ("cRTime", TIME_FIELD_UPDATES),
                    ("Player", (("0x2e8", "stopwatch", "cRTime"),)),
                    (
                        "cRSubGame",
                        (("0x355d98", "active_level_timer", "cRTime"),),
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
