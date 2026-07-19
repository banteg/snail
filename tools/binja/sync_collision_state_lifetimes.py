#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import (
    apply_user_var_updates,
    current_enum_members,
    emit_summary,
    types_declare_missing_only,
)
from _target import DEFAULT_TARGET


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"

EXPECTED_ENUM_MEMBERS = {
    "ParcelState": (
        ("PARCEL_STATE_INACTIVE", 0),
        ("PARCEL_STATE_TRACK_ACTIVE", 1),
        ("PARCEL_STATE_UNKNOWN_2", 2),
        ("PARCEL_STATE_UNKNOWN_3", 3),
        ("PARCEL_STATE_COLLECT_PENDING", 4),
        ("PARCEL_STATE_COLLECTING", 5),
        ("PARCEL_STATE_DELIVERY_PENDING", 6),
        ("PARCEL_STATE_DELIVERING", 7),
    ),
    "TrackPickupState": (
        ("TRACK_PICKUP_STATE_INACTIVE", 0),
        ("TRACK_PICKUP_STATE_ACTIVE", 1),
        ("TRACK_PICKUP_STATE_TEARDOWN_PENDING", 2),
    ),
    "SubSlugState": (
        ("SUB_SLUG_STATE_INACTIVE", 0),
        ("SUB_SLUG_STATE_ACTIVE", 1),
        ("SUB_SLUG_STATE_DEATH_TOSS_PENDING", 2),
        ("SUB_SLUG_STATE_TEARDOWN_PENDING", 3),
        ("SUB_SLUG_STATE_LATERAL_ACTIVE", 4),
    ),
    "SubRingState": (
        ("SUB_RING_STATE_INACTIVE", 0),
        ("SUB_RING_STATE_ACTIVE", 1),
        ("SUB_RING_STATE_COLLECT_PENDING", 2),
        ("SUB_RING_STATE_COLLECTING", 3),
        ("SUB_RING_STATE_EXPAND_PENDING", 4),
        ("SUB_RING_STATE_EXPANDING", 5),
    ),
    "SubRingKind": (
        ("SUB_RING_KIND_UNKNOWN_0", 0),
        ("SUB_RING_KIND_UNKNOWN_1", 1),
        ("SUB_RING_KIND_EXPLODE_RAMP", 2),
        ("SUB_RING_KIND_SLOW_DEFAULT", 3),
        ("SUB_RING_KIND_NORMAL_DEFAULT", 4),
        ("SUB_RING_KIND_NORMAL_AUTHORED", 5),
        ("SUB_RING_KIND_EXPLODE_AUTHORED", 6),
        ("SUB_RING_KIND_SLOW_AUTHORED", 7),
        ("SUB_RING_KIND_POWER_UP_AUTHORED", 8),
    ),
}

# The byte-strided slug, parcel, health, and ring walks load enum fields through
# physical register lifetimes that are distinct from their typed slot cursors.
# Keep this batch intentionally function-local; the broad path/runtime replays
# own the surrounding structs and prototypes, not these six transient values.
COLLISION_STATE_USER_VAR_UPDATES = (
    (
        "handle_subgoldy_collisions",
        "RegisterVariableSourceType",
        821,
        67,
        "slug_state",
        "SubSlugState",
    ),
    (
        "handle_subgoldy_collisions",
        "RegisterVariableSourceType",
        1388,
        67,
        "parcel_state",
        "ParcelState",
    ),
    (
        "handle_subgoldy_collisions",
        "RegisterVariableSourceType",
        1666,
        67,
        "health_state",
        "TrackPickupState",
    ),
    (
        "handle_subgoldy_collisions",
        "RegisterVariableSourceType",
        2346,
        67,
        "ring_state",
        "SubRingState",
    ),
    (
        "handle_subgoldy_collisions",
        "RegisterVariableSourceType",
        2516,
        66,
        "ring_kind",
        "SubRingKind",
    ),
    (
        "handle_subgoldy_collisions",
        "RegisterVariableSourceType",
        2573,
        66,
        "effect_kind",
        "SubRingKind",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay only the exact enum-valued register lifetimes in "
            "handle_subgoldy_collisions."
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
        help="Header supplying the canonical collision enum definitions.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    enum_names = tuple(EXPECTED_ENUM_MEMBERS)
    current_members = current_enum_members(
        REPO_ROOT,
        target=args.target,
        enum_names=enum_names,
    )
    enums_current = all(
        current_members.get(name) == expected
        for name, expected in EXPECTED_ENUM_MEMBERS.items()
    )
    type_operation = (
        {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "canonical collision lifecycle enums already present",
            "header": str(header_path),
            "required_types": enum_names,
        }
        if enums_current
        else types_declare_missing_only(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            replace_types=enum_names,
            include_types=enum_names,
        )
    )

    operations = [
        type_operation,
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=COLLISION_STATE_USER_VAR_UPDATES,
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
