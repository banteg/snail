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
    "BodBase": 0x38,
    "TrackRenderCacheSlot": 0x3C,
    "SegmentCache": 0xA7F8,
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
    "BodBase": {
        0x00: ("bod", "BodNode"),
    },
    "TrackRenderCacheSlot": {
        0x00: ("bod", "BodBase"),
        0x38: ("cache_row_base", "float"),
    },
    "SegmentCache": {
        0x58: ("slots", "TrackRenderCacheSlot[143][5]"),
    },
}

# SegmentCache owns the embedded 143-by-5 records, but its teardown only
# borrows their BodNode linkage and the root BodList. Native keeps one
# continuous pointer to the current list_next field across both loop levels.
TRACK_CACHE_TEARDOWN_USER_VAR_UPDATES = (
    (
        "remove_track_render_cache_bods",
        "RegisterVariableSourceType",
        5,
        72,
        "next_ref",
        "BodNode**",
    ),
    (
        "remove_track_render_cache_bods",
        "StackVariableSourceType",
        8,
        -4,
        "rows_remaining",
        "int32_t",
    ),
    (
        "remove_track_render_cache_bods",
        "RegisterVariableSourceType",
        34,
        73,
        "families_remaining",
        "int32_t",
    ),
    (
        "remove_track_render_cache_bods",
        "RegisterVariableSourceType",
        41,
        67,
        "active_list",
        "BodList*",
    ),
    (
        "remove_track_render_cache_bods",
        "RegisterVariableSourceType",
        47,
        66,
        "list_flags",
        "uint32_t",
    ),
    (
        "remove_track_render_cache_bods",
        "RegisterVariableSourceType",
        88,
        66,
        "list_next",
        "BodNode*",
    ),
    (
        "remove_track_render_cache_bods",
        "RegisterVariableSourceType",
        100,
        66,
        "list_prev",
        "BodNode*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay only the embedded-grid cursor and borrowed BodList "
            "lifetimes in remove_track_render_cache_bods."
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
        help="Header documenting the canonical cache-grid and list owners.",
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
            "canonical track-cache teardown ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_track_cache_teardown_owner_layouts",
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
            updates=TRACK_CACHE_TEARDOWN_USER_VAR_UPDATES,
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
