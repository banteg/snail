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
    reanalyze_functions,
    types_declare_missing_only,
)
from _target import DEFAULT_TARGET

REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/time_trial_types.h"

EXPECTED_STRUCT_SIZES = {
    "TimeTrialCourseRecord": 0x10,
    "cRTimeTrial": 0x330,
}

OWNER_TYPE_RENAMES = (("TimeTrial", "cRTimeTrial"),)

REANALYSIS_FUNCTIONS = (
    "format_time_trial_string",
    "update_challenge_setup_screen",
    "initialize_subgame",
    "update_subgame",
)

COURSE_RECORD_FIELD_UPDATES = (
    ("0x00", "course_name", "char*"),
    ("0x04", "unknown_04", "uint8_t[0xc]"),
)

TIME_TRIAL_FIELD_UPDATES = (
    (
        "0x00",
        "course_records",
        "TimeTrialCourseRecord[0x33]",
    ),
)

PROTO_UPDATES = (
    (
        "format_time_trial_string",
        "char* __thiscall format_time_trial_string(cRTimeTrial* time_trial, cRTime* timer)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the exact Windows cRTimeTrial ownership lane."
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
            "reason": "cRTimeTrial owner layout already current",
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
            *apply_struct_and_proto_updates(
                REPO_ROOT,
                target=args.target,
                struct_updates=(
                    ("TimeTrialCourseRecord", COURSE_RECORD_FIELD_UPDATES),
                    ("cRTimeTrial", TIME_TRIAL_FIELD_UPDATES),
                    (
                        "cRSubGame",
                        (
                            ("0xff25e0", "time_trial", "cRTimeTrial"),
                            ("0xff2910", "path_manager", "cRPathManager"),
                        ),
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
