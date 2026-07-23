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
    "Vec3": 0x0C,
    "tColour": 0x10,
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
    "Vec3": {
        0x00: ("x", "float"),
        0x04: ("y", "float"),
        0x08: ("z", "float"),
    },
    "tColour": {
        0x00: ("r", "float"),
        0x04: ("g", "float"),
        0x08: ("b", "float"),
        0x0C: ("a", "float"),
    },
    "BodBase": {
        0x00: ("bod", "BodNode"),
        0x10: ("position", "Vec3"),
        0x28: ("color", "tColour"),
    },
    "TrackRenderCacheSlot": {
        0x00: ("bod", "BodBase"),
        0x38: ("cache_row_base", "float"),
    },
    "SegmentCache": {
        0x58: ("slots", "TrackRenderCacheSlot[143][5]"),
        0xA7F0: ("next_cache_row_z", "float"),
        0xA7F4: ("next_cache_row_index", "int32_t"),
    },
}

# SegmentCache owns every embedded slot. Each activation block borrows three
# narrower views of one selected family record: the complete slot for intrusive
# list insertion, its Vec3 position, and its tColour. The root-owned draw-list
# sentinel is a BodNode borrow. These are physical pointer lifetimes emitted by
# native code; the scaled row-index intermediates deliberately remain integers.
TRACK_CACHE_ROW_USER_VAR_UPDATES = (
    (
        "update_track_render_cache_rows",
        "RegisterVariableSourceType",
        56,
        67,
        "fringe_active_list",
        "BodNode*",
    ),
    (
        "update_track_render_cache_rows",
        "RegisterVariableSourceType",
        78,
        66,
        "fringe_slot",
        "TrackRenderCacheSlot*",
    ),
    (
        "update_track_render_cache_rows",
        "RegisterVariableSourceType",
        149,
        66,
        "fringe_position",
        "Vec3*",
    ),
    (
        "update_track_render_cache_rows",
        "RegisterVariableSourceType",
        176,
        66,
        "skirt_color",
        "tColour*",
    ),
    (
        "update_track_render_cache_rows",
        "RegisterVariableSourceType",
        196,
        68,
        "fringe_color",
        "tColour*",
    ),
    (
        "update_track_render_cache_rows",
        "StackVariableSourceType",
        0,
        -16,
        "skirt_color_out",
        "tColour",
    ),
    (
        "update_track_render_cache_rows",
        "RegisterVariableSourceType",
        240,
        67,
        "floor_active_list",
        "BodNode*",
    ),
    (
        "update_track_render_cache_rows",
        "RegisterVariableSourceType",
        252,
        66,
        "floor_slot",
        "TrackRenderCacheSlot*",
    ),
    (
        "update_track_render_cache_rows",
        "RegisterVariableSourceType",
        319,
        66,
        "floor_position",
        "Vec3*",
    ),
    (
        "update_track_render_cache_rows",
        "RegisterVariableSourceType",
        346,
        67,
        "floor_color",
        "tColour*",
    ),
    (
        "update_track_render_cache_rows",
        "RegisterVariableSourceType",
        373,
        67,
        "slide_active_list",
        "BodNode*",
    ),
    (
        "update_track_render_cache_rows",
        "RegisterVariableSourceType",
        392,
        66,
        "slide_slot",
        "TrackRenderCacheSlot*",
    ),
    (
        "update_track_render_cache_rows",
        "RegisterVariableSourceType",
        458,
        66,
        "slide_position",
        "Vec3*",
    ),
    (
        "update_track_render_cache_rows",
        "RegisterVariableSourceType",
        488,
        67,
        "slide_color",
        "tColour*",
    ),
    (
        "update_track_render_cache_rows",
        "RegisterVariableSourceType",
        515,
        67,
        "ramp_active_list",
        "BodNode*",
    ),
    (
        "update_track_render_cache_rows",
        "RegisterVariableSourceType",
        534,
        66,
        "ramp_slot",
        "TrackRenderCacheSlot*",
    ),
    (
        "update_track_render_cache_rows",
        "RegisterVariableSourceType",
        600,
        66,
        "ramp_position",
        "Vec3*",
    ),
    (
        "update_track_render_cache_rows",
        "RegisterVariableSourceType",
        630,
        67,
        "ramp_color",
        "tColour*",
    ),
    (
        "update_track_render_cache_rows",
        "RegisterVariableSourceType",
        657,
        67,
        "warning_active_list",
        "BodNode*",
    ),
    (
        "update_track_render_cache_rows",
        "RegisterVariableSourceType",
        676,
        66,
        "warning_slot",
        "TrackRenderCacheSlot*",
    ),
    (
        "update_track_render_cache_rows",
        "RegisterVariableSourceType",
        742,
        66,
        "warning_position",
        "Vec3*",
    ),
    (
        "update_track_render_cache_rows",
        "RegisterVariableSourceType",
        772,
        67,
        "warning_color",
        "tColour*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the exact cache-row activator's embedded slot, position, "
            "color, and root list borrows."
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
        help="Header documenting the canonical track-cache owners.",
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
            "canonical track-cache row ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_track_cache_row_owner_layouts",
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
            updates=TRACK_CACHE_ROW_USER_VAR_UPDATES,
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
