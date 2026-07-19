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
    types_declare_if_missing,
)
from _target import DEFAULT_TARGET


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"

EXPECTED_TYPE_WIDTHS = {
    "TrackRowCell": 0x54,
    "TrackRowCellTileByteView": 0x54,
    "SubgameRuntime": 0x1272838,
}

EXPECTED_STRUCT_FIELDS = {
    "TrackRowCell": {
        0x3C: ("tile_id", "SubLocTileId"),
        0x3D: ("open_edge_mask", "uint8_t"),
        0x40: ("lane_and_flags", "uint32_t"),
    },
    "TrackRowCellTileByteView": {
        0x00: ("tile_id", "SubLocTileId"),
        0x01: ("open_edge_mask", "uint8_t"),
        0x04: ("lane_and_flags", "uint32_t"),
    },
    "SubgameRuntime": {
        0x54: ("runtime_row_count", "int32_t"),
        0x3BFAC8: ("runtime_cells", "TrackRowCell[3200][8]"),
    },
}

# WarnTrack holds one EAX row cursor, one EDX current-cell cursor, and a saved
# stack copy. All three point at TrackRowCell::tile_id (+0x3c) and advance by
# the full 0x54 cell stride. The overlapping field-first view records that
# physical borrow without rebasing any cursor to a false TrackRowCell owner.
TRACK_WARNING_USER_VAR_UPDATES = (
    (
        "mark_track_warning_zones",
        "RegisterVariableSourceType",
        25,
        66,
        "row_tile_cursor",
        "TrackRowCellTileByteView*",
    ),
    (
        "mark_track_warning_zones",
        "RegisterVariableSourceType",
        39,
        68,
        "cell_tile_cursor",
        "TrackRowCellTileByteView*",
    ),
    (
        "mark_track_warning_zones",
        "StackVariableSourceType",
        35,
        -8,
        "saved_cell_tile_cursor",
        "TrackRowCellTileByteView*",
    ),
)

# SmoothTrack uses the same field-first tile cursor for its exact 220/220 edge
# selection pass. The neighboring full-cell borrows remain explicit byte
# displacements from this cursor; this update only restores the current cell's
# tile/open-edge/packed-flag fields and the exact 0x54 induction.
TRACK_TILE_EDGE_USER_VAR_UPDATES = (
    (
        "select_track_tile_edge_variants",
        "RegisterVariableSourceType",
        28,
        72,
        "tile_cursor",
        "TrackRowCellTileByteView*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the field-first TrackRowCell tile cursors in the warning "
            "and edge-selection passes."
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
            "canonical track-warning ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_track_warning_owner_layouts",
        "status": "verified",
        "types": tuple(EXPECTED_TYPE_WIDTHS),
    }


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"runtime-grid type header not found: {header_path}")

    operations = [
        types_declare_if_missing(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            required_structs=("TrackRowCellTileByteView",),
        ),
        verify_owner_layouts(args.target),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=(
                *TRACK_WARNING_USER_VAR_UPDATES,
                *TRACK_TILE_EDGE_USER_VAR_UPDATES,
            ),
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
