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
    "Fringe": 0x38,
    "SubSegment": 0x4220,
    "SubTracks": 0x1A5978,
    "TrackRowCell": 0x54,
    "SubRow": 0xF4,
    "SubgameRuntime": 0x1272838,
}

EXPECTED_STRUCT_FIELDS = {
    "BodNode": {
        0x04: ("list_flags", "uint32_t"),
    },
    "SubSegment": {
        0x04: ("row_count", "int32_t"),
    },
    "SubTracks": {
        0x00: ("segment_count", "int32_t"),
        0x04: ("segment_slots", "SubSegment[100]"),
    },
    "TrackRowCell": {
        0x00: ("bod", "BodNode"),
        0x28: ("color", "tColour"),
        0x3C: ("tile_id", "SubLocTileId"),
        0x3D: ("open_edge_mask", "uint8_t"),
        0x40: ("lane_and_flags", "uint32_t"),
        0x44: ("fringe_front", "Fringe*"),
        0x48: ("fringe_right", "Fringe*"),
        0x4C: ("fringe_left", "Fringe*"),
        0x50: ("fringe_back", "Fringe*"),
    },
    "SubRow": {
        0x00: ("flags", "uint32_t"),
        0x90: ("projection_payload", "Vec3"),
        0x9C: ("parcel_set_id", "int32_t"),
        0xA0: ("attachment_template_index", "int32_t"),
        0xA4: ("primary_attachment_cell", "TrackRowCell*"),
        0xAC: ("installed_heading_delta", "float"),
        0xE8: ("ring_speed", "float"),
        0xEC: ("source_segment", "SubSegment*"),
        0xF0: ("row_event_id", "int32_t"),
    },
    "SubgameRuntime": {
        0xA874: ("level_definition", "SubTracks"),
        0x3BFAC8: ("runtime_cells", "TrackRowCell[3200][8]"),
        0x5CCAC8: ("runtime_rows", "SubRow[3200]"),
    },
}

# The first loop borrows SubSegment::row_count from each authored segment slot.
# The second uses two exact field cursors: one based at
# TrackRowCell::fringe_front/lane_and_flags and one based at
# SubRow::projection_payload.y. Preserve those physical cursor shapes instead
# of inventing negatively biased whole-record pointers.
RUNTIME_GRID_CLEAR_USER_VAR_UPDATES = (
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        435,
        66,
        "segment_slot_index",
        "int32_t",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        450,
        67,
        "segment_row_count_cursor",
        "int32_t*",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        456,
        68,
        "segment_row_count",
        "int32_t",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "StackVariableSourceType",
        569,
        -40,
        "row_fringe_front_cursor",
        "Fringe**",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        573,
        73,
        "row_projection_y_cursor",
        "int32_t*",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "StackVariableSourceType",
        579,
        -48,
        "rows_remaining",
        "int32_t",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        636,
        71,
        "cell_lanes_remaining",
        "int32_t",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        633,
        72,
        "lane_and_flags_cursor",
        "uint32_t*",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        638,
        67,
        "cell_lane_and_flags",
        "uint32_t",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        669,
        68,
        "cell_list_flags",
        "uint32_t",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        689,
        66,
        "next_row_fringe_front_cursor",
        "Fringe**",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        698,
        72,
        "cell_fringe_front_cursor",
        "Fringe**",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay only the authored row-count and runtime-grid clear "
            "lifetimes in populate_runtime_track_cells_from_segments."
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
        help="Header documenting the canonical runtime-grid owners.",
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
            "canonical runtime-grid clear ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_runtime_grid_clear_owner_layouts",
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
            updates=RUNTIME_GRID_CLEAR_USER_VAR_UPDATES,
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
