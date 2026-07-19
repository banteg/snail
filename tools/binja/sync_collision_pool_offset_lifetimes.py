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
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"

EXPECTED_TYPE_WIDTHS = {
    "Salt": 0x98,
    "SaltManager": 0x17C0,
    "SubLazer": 0xB0,
    "SubLazerManager": 0xDC0,
    "Slug": 0xEC,
    "SlugPool": 0x760,
    "Parcel": 0x8C,
    "ParcelManager": 0x1B58,
    "SubHealth": 0x74,
    "SubGarbage": 0xC4,
    "SubGarbagePool": 0x264C,
    "SubRing": 0x1F8,
    "SubRingPool": 0x3F0,
    "SubgameRuntime": 0x1272838,
}

EXPECTED_STRUCT_FIELDS = {
    "SaltManager": {
        0x00: ("slots", "Salt[40]"),
    },
    "SubLazerManager": {
        0x00: ("slots", "SubLazer[20]"),
    },
    "SlugPool": {
        0x00: ("slots", "Slug[8]"),
    },
    "ParcelManager": {
        0x00: ("slots", "Parcel[50]"),
    },
    "SubRingPool": {
        0x00: ("slots", "SubRing[2]"),
    },
    "SubGarbagePool": {
        0x00: ("active_head", "SubGarbage*"),
        0x04: ("slots", "SubGarbage[50]"),
    },
    "SubgameRuntime": {
        0x356000: ("health_pickups", "SubHealth[8]"),
        0x3563A0: ("slug_hazards", "SlugPool"),
        0x356B00: ("sub_lazers", "SubLazerManager"),
        0x3578C0: ("salt_hazards", "SaltManager"),
        0x359140: ("garbage_hazards", "SubGarbagePool"),
        0x35B78C: ("ring_effects", "SubRingPool"),
        0x125E480: ("parcel_manager", "ParcelManager"),
    },
}

# Collision walks carry EDI as a signed byte offset from SubgameRuntime, not as
# an owner pointer. The exact pool extents and element widths prove all six
# lifetimes. Retype the four void-inferred walks to match the two int-inferred
# predecessors, but keep the separately typed slot cursors as the borrowed
# object views. The intervening garbage sweep is different: it borrows actual
# SubGarbage nodes from the pool-owned intrusive active list.
COLLISION_POOL_OFFSET_USER_VAR_UPDATES = (
    (
        "handle_subgoldy_collisions",
        "RegisterVariableSourceType",
        490,
        73,
        "active_garbage",
        "SubGarbage*",
    ),
    (
        "handle_subgoldy_collisions",
        "RegisterVariableSourceType",
        67,
        73,
        "salt_pool_byte_offset",
        "int32_t",
    ),
    (
        "handle_subgoldy_collisions",
        "RegisterVariableSourceType",
        304,
        73,
        "sub_lazer_pool_byte_offset",
        "int32_t",
    ),
    (
        "handle_subgoldy_collisions",
        "RegisterVariableSourceType",
        815,
        73,
        "slug_pool_byte_offset",
        "int32_t",
    ),
    (
        "handle_subgoldy_collisions",
        "RegisterVariableSourceType",
        1377,
        73,
        "parcel_pool_byte_offset",
        "int32_t",
    ),
    (
        "handle_subgoldy_collisions",
        "RegisterVariableSourceType",
        1657,
        73,
        "health_pool_byte_offset",
        "int32_t",
    ),
    (
        "handle_subgoldy_collisions",
        "RegisterVariableSourceType",
        2328,
        73,
        "ring_pool_byte_offset",
        "int32_t",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the intrusive garbage cursor and six byte-offset pool "
            "walks in handle_subgoldy_collisions."
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
        help="Header documenting the canonical collision pool owners.",
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
            "canonical collision pool ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_collision_pool_owner_layouts",
        "status": "verified",
        "types": tuple(EXPECTED_TYPE_WIDTHS),
    }


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations = [
        verify_owner_layouts(args.target),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=COLLISION_POOL_OFFSET_USER_VAR_UPDATES,
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
