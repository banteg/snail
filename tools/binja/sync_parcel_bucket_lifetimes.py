#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import (
    apply_user_var_updates,
    current_struct_fields_batch,
    current_type_widths,
    emit_summary,
)
from _target import DEFAULT_TARGET


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/parcel_bucket_types.h"

EXPECTED_TYPE_WIDTHS = {
    "Vec3": 0x0C,
    "ParcelCandidate": 0x10,
    "ParcelBucket": 0x20C,
}

EXPECTED_STRUCT_FIELDS = {
    "Vec3": {
        0x00: ("x", "float"),
        0x04: ("y", "float"),
        0x08: ("z", "float"),
    },
    "ParcelCandidate": {
        0x00: ("row", "int32_t"),
        0x04: ("position", "Vec3"),
    },
    "ParcelBucket": {
        0x000: ("candidates", "ParcelCandidate[32]"),
        0x200: ("candidate_count", "int32_t"),
        0x204: ("set_id", "int32_t"),
        0x208: ("segment_index", "int32_t"),
    },
}

# The positive-set compactor copies the next bucket's candidate records over
# the selected bucket before publishing its three metadata words. These three
# registers are borrowed element cursors into the two global ParcelBucket
# banks; none owns either bank or a separate allocation.
PARCEL_BUCKET_USER_VAR_UPDATES = (
    (
        "place_parcels_on_track",
        "RegisterVariableSourceType",
        1494,
        67,
        "destination_candidate",
        "ParcelCandidate*",
    ),
    (
        "place_parcels_on_track",
        "RegisterVariableSourceType",
        1500,
        72,
        "source_candidate",
        "ParcelCandidate*",
    ),
    (
        "place_parcels_on_track",
        "RegisterVariableSourceType",
        1506,
        73,
        "destination_candidate_write",
        "ParcelCandidate*",
    ),
    (
        "place_parcels_on_track",
        "RegisterVariableSourceType",
        1875,
        67,
        "zero_candidate_position",
        "Vec3*",
    ),
    (
        "place_parcels_on_track",
        "RegisterVariableSourceType",
        1972,
        66,
        "zero_destination_bucket",
        "ParcelBucket*",
    ),
)

def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the borrowed parcel candidate and bucket lifetimes in "
            "cRSubGame::PlaceParcels."
        )
    )
    parser.add_argument(
        "--target",
        default=DEFAULT_TARGET,
        help="Binary Ninja target selector. Defaults to the Snail Mail database.",
    )
    parser.add_argument(
        "--header",
        type=Path,
        default=DEFAULT_HEADER_PATH,
        help="Header documenting the canonical parcel scratch-bank owners.",
    )
    return parser.parse_args()


def verify_owner_layouts(target: str) -> dict[str, object]:
    widths = current_type_widths(
        REPO_ROOT,
        target=target,
        type_names=EXPECTED_TYPE_WIDTHS,
    )
    layouts = current_struct_fields_batch(
        REPO_ROOT,
        target=target,
        struct_names=EXPECTED_STRUCT_FIELDS,
    )
    mismatches: list[str] = []
    for type_name, expected_width in EXPECTED_TYPE_WIDTHS.items():
        observed_width = widths[type_name]
        if observed_width != expected_width:
            mismatches.append(
                f"{type_name}: expected width {expected_width:#x}, "
                f"observed {observed_width!r}"
            )
    for struct_name, expected_fields in EXPECTED_STRUCT_FIELDS.items():
        observed_fields = layouts[struct_name]
        for offset, expected in expected_fields.items():
            observed = observed_fields.get(offset)
            if observed != expected:
                mismatches.append(
                    f"{struct_name}+{offset:#x}: expected {expected!r}, "
                    f"observed {observed!r}"
                )
    if mismatches:
        raise RuntimeError(
            "canonical parcel scratch-bank ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_parcel_bucket_owner_layouts",
        "status": "verified",
        "types": tuple(EXPECTED_TYPE_WIDTHS),
    }


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"parcel-bucket type header not found: {header_path}")

    operations = [
        verify_owner_layouts(args.target),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=PARCEL_BUCKET_USER_VAR_UPDATES,
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
