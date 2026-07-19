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
    "SubRow": 0xF4,
    "TrackRowCell": 0x54,
    "Fringe": 0x38,
    "FringeManager": 0x5FB44,
    "RootTrackFringeBodCatalog": 0x3F00,
    "RootBodCatalog": 0x4D00,
    "SubgameRuntime": 0x1272838,
}

EXPECTED_STRUCT_FIELDS = {
    "SubRow": {
        0x00: ("flags", "uint32_t"),
    },
    "TrackRowCell": {
        0x10: ("anchor_position", "Vec3"),
        0x3C: ("tile_id", "SubLocTileId"),
        0x3D: ("open_edge_mask", "uint8_t"),
        0x44: ("fringe_front", "Fringe*"),
        0x48: ("fringe_right", "Fringe*"),
        0x4C: ("fringe_left", "Fringe*"),
        0x50: ("fringe_back", "Fringe*"),
    },
    "Fringe": {
        0x00: ("bod", "BodBase"),
    },
    "FringeManager": {
        0x00: ("objects", "Fringe[7000]"),
        0x5FB40: ("count", "int32_t"),
    },
    "RootTrackFringeBodCatalog": {
        0x00: ("entries", "RootBodCatalogEntry[8][4][3][3]"),
    },
    "RootBodCatalog": {
        0xCB0: ("fringe_catalog", "RootTrackFringeBodCatalog"),
    },
    "SubgameRuntime": {
        0x54: ("runtime_row_count", "int32_t"),
        0x35BBBC: ("fringe_manager", "FringeManager"),
        0x3BFAC8: ("runtime_cells", "TrackRowCell[3200][8]"),
        0x5CCAC8: ("runtime_rows", "SubRow[3200]"),
    },
}

# MakeFringe preserves the SubgameRuntime receiver across helper calls, walks
# the separately owned row and cell slabs, selects one object from the root
# fringe-BOD catalog, and borrows each emitted Fringe from the embedded pool.
# Keep those ownership domains distinct; the per-direction integers are only
# catalog selectors, and TrackRowCell stores non-owning handles to the results.
TRACK_FRINGE_BUILDER_USER_VAR_UPDATES = (
    (
        "build_track_fringe_objects",
        "RegisterVariableSourceType",
        10,
        71,
        "runtime",
        "SubgameRuntime*",
    ),
    (
        "build_track_fringe_objects",
        "StackVariableSourceType",
        18,
        -80,
        "runtime_saved",
        "SubgameRuntime*",
    ),
    (
        "build_track_fringe_objects",
        "RegisterVariableSourceType",
        30,
        69,
        "edge_variant_a",
        "int32_t",
    ),
    (
        "build_track_fringe_objects",
        "StackVariableSourceType",
        34,
        -72,
        "row_index",
        "int32_t",
    ),
    (
        "build_track_fringe_objects",
        "RegisterVariableSourceType",
        44,
        68,
        "row",
        "SubRow*",
    ),
    (
        "build_track_fringe_objects",
        "RegisterVariableSourceType",
        52,
        72,
        "cell",
        "TrackRowCell*",
    ),
    (
        "build_track_fringe_objects",
        "StackVariableSourceType",
        58,
        -68,
        "row_cursor",
        "SubRow*",
    ),
    (
        "build_track_fringe_objects",
        "StackVariableSourceType",
        70,
        -76,
        "cells_remaining",
        "int32_t",
    ),
    (
        "build_track_fringe_objects",
        "RegisterVariableSourceType",
        73,
        73,
        "fringe_family",
        "int32_t",
    ),
    (
        "build_track_fringe_objects",
        "RegisterVariableSourceType",
        316,
        71,
        "front_edge_variant_b",
        "int32_t",
    ),
    (
        "build_track_fringe_objects",
        "RegisterVariableSourceType",
        355,
        66,
        "front_fringe",
        "Fringe*",
    ),
    (
        "build_track_fringe_objects",
        "StackVariableSourceType",
        0,
        -64,
        "front_color",
        "tColour",
    ),
    (
        "build_track_fringe_objects",
        "RegisterVariableSourceType",
        576,
        71,
        "right_edge_variant_b",
        "int32_t",
    ),
    (
        "build_track_fringe_objects",
        "RegisterVariableSourceType",
        615,
        66,
        "right_fringe",
        "Fringe*",
    ),
    (
        "build_track_fringe_objects",
        "StackVariableSourceType",
        0,
        -48,
        "right_color",
        "tColour",
    ),
    (
        "build_track_fringe_objects",
        "RegisterVariableSourceType",
        836,
        71,
        "left_edge_variant_b",
        "int32_t",
    ),
    (
        "build_track_fringe_objects",
        "RegisterVariableSourceType",
        875,
        66,
        "left_fringe",
        "Fringe*",
    ),
    (
        "build_track_fringe_objects",
        "StackVariableSourceType",
        0,
        -32,
        "left_color",
        "tColour",
    ),
    (
        "build_track_fringe_objects",
        "RegisterVariableSourceType",
        1096,
        71,
        "back_edge_variant_b",
        "int32_t",
    ),
    (
        "build_track_fringe_objects",
        "RegisterVariableSourceType",
        1135,
        66,
        "back_fringe",
        "Fringe*",
    ),
    (
        "build_track_fringe_objects",
        "StackVariableSourceType",
        0,
        -16,
        "back_color",
        "tColour",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay only the row/cell, catalog-selector, and borrowed Fringe "
            "lifetimes in build_track_fringe_objects."
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
        help="Header documenting the canonical fringe builder owners.",
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
            "canonical track-fringe builder ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_track_fringe_builder_owner_layouts",
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
            updates=TRACK_FRINGE_BUILDER_USER_VAR_UPDATES,
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
