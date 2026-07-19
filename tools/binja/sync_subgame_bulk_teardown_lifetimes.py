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
    "BodNode": 0x10,
    "BodList": 0x0C,
    "RenderableBod": 0x80,
    "RowModel": 0x8C,
    "SubRow": 0xF4,
    "TrackRowCell": 0x54,
    "SubHealth": 0x74,
    "SubGarbage": 0xC4,
    "SubGarbagePool": 0x264C,
    "Slug": 0xEC,
    "SlugPool": 0x760,
    "SubRing": 0x1F8,
    "SubRingPool": 0x3F0,
    "SubgameRuntime": 0x1272838,
}

EXPECTED_STRUCT_FIELDS = {
    "BodNode": {
        0x04: ("list_flags", "uint32_t"),
        0x08: ("list_prev", "BodNode*"),
        0x0C: ("list_next", "BodNode*"),
    },
    "BodList": {
        0x04: ("first", "BodNode*"),
        0x08: ("free_top", "BodNode*"),
    },
    "RowModel": {
        0x00: ("body", "RenderableBod"),
    },
    "SubRow": {
        0x04: ("row_model", "RowModel"),
    },
    "TrackRowCell": {
        0x00: ("bod", "BodNode"),
    },
    "SubHealth": {
        0x00: ("bod", "BodBase"),
        0x38: ("state", "TrackPickupState"),
    },
    "SubGarbage": {
        0x00: ("body", "RenderableBod"),
        0x84: ("state", "SubGarbageState"),
    },
    "SubGarbagePool": {
        0x00: ("active_head", "SubGarbage*"),
        0x04: ("slots", "SubGarbage[50]"),
    },
    "Slug": {
        0x00: ("body", "RenderableBod"),
        0x80: ("state", "SubSlugState"),
    },
    "SlugPool": {
        0x00: ("slots", "Slug[8]"),
    },
    "SubRing": {
        0x00: ("bod", "BodNode"),
        0x80: ("state", "SubRingState"),
    },
    "SubRingPool": {
        0x00: ("slots", "SubRing[2]"),
    },
    "SubgameRuntime": {
        0x356000: ("health_pickups", "SubHealth[8]"),
        0x3563A0: ("slug_hazards", "SlugPool"),
        0x359140: ("garbage_hazards", "SubGarbagePool"),
        0x35B78C: ("ring_effects", "SubRingPool"),
        0x3BFAC8: ("runtime_cells", "TrackRowCell[3200][8]"),
        0x5CCAC8: ("runtime_rows", "SubRow[3200]"),
    },
}

# Bulk teardown never frees the backing row/pickup/hazard records. It borrows
# each embedded BodNode's list links, unlinks that node from the root BodList,
# and pushes it onto the list's free stack. Preserve the five independent list
# borrows and countdowns without inventing a common pool owner or flattening
# the compiler-sensitive list_next field cursors.
SUBGAME_BULK_TEARDOWN_USER_VAR_UPDATES = (
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        21,
        71,
        "rows_remaining",
        "int32_t",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        39,
        67,
        "row_active_list",
        "BodList*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        45,
        66,
        "row_list_flags",
        "uint32_t",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        87,
        66,
        "row_list_next",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        99,
        66,
        "row_list_prev",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        118,
        68,
        "row_free_top",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        129,
        66,
        "row_flags_after_clear",
        "uint32_t",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        138,
        69,
        "cells_remaining",
        "int32_t",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        187,
        73,
        "health_remaining",
        "int32_t",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        194,
        66,
        "health_list_flags",
        "uint32_t",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        208,
        67,
        "health_active_list",
        "BodList*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        253,
        66,
        "health_list_next",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        265,
        66,
        "health_list_prev",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        284,
        68,
        "health_free_top",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        295,
        66,
        "health_flags_after_clear",
        "uint32_t",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        582,
        73,
        "garbage_remaining",
        "int32_t",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        604,
        66,
        "garbage_list_flags",
        "uint32_t",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        610,
        67,
        "garbage_active_list",
        "BodList*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        652,
        66,
        "garbage_list_next",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        664,
        66,
        "garbage_list_prev",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        683,
        68,
        "garbage_free_top",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        694,
        66,
        "garbage_flags_after_clear",
        "uint32_t",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        718,
        73,
        "slug_remaining",
        "int32_t",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        740,
        66,
        "slug_list_flags",
        "uint32_t",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        743,
        67,
        "slug_active_list",
        "BodList*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        788,
        66,
        "slug_list_next",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        800,
        66,
        "slug_list_prev",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        819,
        68,
        "slug_free_top",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        830,
        66,
        "slug_flags_after_clear",
        "uint32_t",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        854,
        73,
        "ring_remaining",
        "int32_t",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        870,
        66,
        "ring_list_flags",
        "uint32_t",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        873,
        67,
        "ring_active_list",
        "BodList*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        918,
        66,
        "ring_list_next",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        930,
        66,
        "ring_list_prev",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        949,
        68,
        "ring_free_top",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        960,
        66,
        "ring_flags_after_clear",
        "uint32_t",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay only the embedded-pool countdowns and borrowed intrusive "
            "list lifetimes in remove_subgame_bods."
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
        help="Header documenting the canonical subgame pool and list owners.",
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
            "canonical subgame bulk-teardown ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_subgame_bulk_teardown_owner_layouts",
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
            updates=SUBGAME_BULK_TEARDOWN_USER_VAR_UPDATES,
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
