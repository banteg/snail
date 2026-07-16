#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_data_var_removals,
    apply_data_var_updates,
    apply_struct_and_proto_updates,
    apply_symbol_updates,
    current_struct_size,
    emit_summary,
    types_declare_missing_only,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/parcel_bucket_types.h"

EXPECTED_STRUCT_SIZES = {
    "ParcelCandidate": 0x10,
    "ParcelBucket": 0x20C,
}

DATA_SYMBOL_UPDATES = (
    ("0x53d190", "g_zero_parcel_buckets"),
    ("0x643390", "g_zero_parcel_bucket_count_lane_end"),
    ("0x6447e8", "g_parcel_group_survival_0"),
    ("0x6487e8", "g_parcel_set_buckets"),
)

LEGACY_WIDE_DATA_VAR_REMOVALS = (
    ("0x53d190", "ParcelBucket[0x800]"),
    ("0x6487e8", "ParcelBucket[0x800]"),
)

NARROW_PARCEL_DATA_VAR_UPDATES = (
    ("0x53d190", "ParcelBucket"),
    ("0x6487e8", "ParcelBucket"),
)

DATA_VAR_UPDATES = (
    *NARROW_PARCEL_DATA_VAR_UPDATES,
    ("0x6447e8", "int32_t[0x1000]"),
)

PROTO_UPDATES = (
    (
        "initialize_array_with_constructor",
        "void __stdcall initialize_array_with_constructor(void* base, int32_t stride, int32_t count, void* (__thiscall* constructor)(void* slot))",
    ),
    (
        "noop_runtime_slot_constructor",
        "void* __thiscall noop_runtime_slot_constructor(void* slot)",
    ),
    (
        "initialize_parcel_set_bucket_pool",
        "void __cdecl initialize_parcel_set_bucket_pool()",
    ),
    (
        "initialize_zero_parcel_bucket_pool",
        "void __cdecl initialize_zero_parcel_bucket_pool()",
    ),
    (
        "place_parcels_on_track",
        "int32_t __thiscall place_parcels_on_track(SubgameRuntime* game)",
    ),
    (
        "place_challenge_parcels_on_track",
        "int32_t __thiscall place_challenge_parcels_on_track(SubgameRuntime* game)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Replay the recovered parcel-bucket scratch-bank ownership."
    )
    parser.add_argument(
        "--target", default=DEFAULT_TARGET, help="Binary Ninja target selector."
    )
    parser.add_argument(
        "--header",
        type=Path,
        default=DEFAULT_HEADER_PATH,
        help="Shared parcel-bucket type header.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"parcel-bucket type header not found: {header_path}")

    mismatched_types = tuple(
        name
        for name, expected_size in EXPECTED_STRUCT_SIZES.items()
        if current_struct_size(
            REPO_ROOT,
            target=args.target,
            struct_name=name,
        )
        != expected_size
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
            "reason": "parcel-bucket owner sizes already current",
            "header": str(header_path),
            "expected_sizes": EXPECTED_STRUCT_SIZES,
        }

    operations: list[dict[str, object]] = [
        type_operation,
        *apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=DATA_SYMBOL_UPDATES,
            kind="data",
        ),
        *apply_data_var_removals(
            REPO_ROOT,
            target=args.target,
            removals=LEGACY_WIDE_DATA_VAR_REMOVALS,
            replacements=NARROW_PARCEL_DATA_VAR_UPDATES,
        ),
        *apply_data_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=DATA_VAR_UPDATES,
        ),
        *apply_struct_and_proto_updates(
            REPO_ROOT,
            target=args.target,
            struct_updates=(),
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
