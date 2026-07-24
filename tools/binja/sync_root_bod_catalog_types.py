#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_struct_and_proto_updates,
    apply_user_var_updates,
    current_struct_size,
    emit_summary,
    reanalyze_functions,
    types_declare_if_missing,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_root_bod_catalog_types.h"
REQUIRED_STRUCTS = (
    "RootBodCatalogEntry",
    "RootTrackCornerBodBank",
    "RootTrackSliceBodBank",
    "RootTrackFringeBodCatalog",
    "RootBodCatalog",
    "RootTrackSliceTripletStrideView",
    "RootFringeCatalogObjectStrideCursor",
)
ROOT_BOD_CATALOG_ENTRY_FIELD_UPDATES = (
    ("0x24", "object", "Object*"),
)
ROOT_FRINGE_CATALOG_OBJECT_STRIDE_CURSOR_FIELD_UPDATES = (
    ("0x00", "object", "Object*"),
    ("0x04", "color", "RootBodCatalogColor4f"),
    ("0x14", "_stride_tail", "uint8_t[0x24]"),
)
ROOT_TRACK_SLICE_TRIPLET_STRIDE_VIEW_FIELD_UPDATES = (
    ("0x00", "root_to_floor_slice", "uint8_t[0x44790]"),
    ("0x44790", "floor_slice", "RootBodCatalogEntry"),
    ("0x447c8", "floor_to_warning_slice", "uint8_t[0x188]"),
    ("0x44950", "warning_slice", "RootBodCatalogEntry"),
    ("0x44988", "warning_to_slide_slice", "uint8_t[0x188]"),
    ("0x44b10", "slide_slice", "RootBodCatalogEntry"),
)
GAME_ROOT_FIELD_UPDATES = (
    ("0x44100", "root_bod_catalog", "RootBodCatalog"),
)

# The backdrop-slice initializer carries `game + i * sizeof(BodBase)` while
# touching corresponding entries in three independently owned catalog banks.
# Preserve the shifted root-relative lifetime instead of asserting one false
# contiguous owner across the intervening bank tails.
WORLD_INITIALIZER_USER_VAR_UPDATES = (
    (
        "initialize_game_assets_and_world",
        "RegisterVariableSourceType",
        2681,
        73,
        "track_slice_triplet_stride_view",
        "RootTrackSliceTripletStrideView*",
    ),
    (
        "initialize_game_assets_and_world",
        "RegisterVariableSourceType",
        21231,
        66,
        "fringe_orientation_object_cursor",
        "RootFringeCatalogObjectStrideCursor*",
    ),
    (
        "initialize_game_assets_and_world",
        "RegisterVariableSourceType",
        21245,
        72,
        "fringe_entry_object_cursor",
        "RootFringeCatalogObjectStrideCursor*",
    ),
)


def require_borrowed_object_owner(*, target: str) -> None:
    """Require the canonical object owner before borrowing it in the catalog."""
    size = current_struct_size(REPO_ROOT, target=target, struct_name="Object")
    if size != 0xDC:
        raise RuntimeError(
            "Object must be exactly 0xdc bytes before catalog replay; "
            f"observed {size!r}"
        )


def require_catalog_extents(*, target: str) -> None:
    """Reject an overlapping or truncated catalog before rebinding GameRoot."""
    expected_sizes = {
        "RootBodCatalogEntry": 0x38,
        "RootTrackCornerBodBank": 0xE0,
        "RootTrackSliceBodBank": 0x1C0,
        "RootTrackFringeBodCatalog": 0x3F00,
        "RootBodCatalog": 0x4D00,
        "RootTrackSliceTripletStrideView": 0x44B48,
        "RootFringeCatalogObjectStrideCursor": 0x38,
    }
    observed_sizes = {
        name: current_struct_size(REPO_ROOT, target=target, struct_name=name)
        for name in expected_sizes
    }
    mismatches = {
        name: {"expected": expected_sizes[name], "observed": observed}
        for name, observed in observed_sizes.items()
        if observed != expected_sizes[name]
    }
    if mismatches:
        raise RuntimeError(f"root BOD catalog extent mismatch: {mismatches}")


PROTO_UPDATES = (
    (
        "initialize_game_assets_and_world",
        "uint8_t __thiscall initialize_game_assets_and_world(GameRoot* game)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the narrow root BOD-catalog owner to a Binary Ninja target."
    )
    parser.add_argument("--target", default=DEFAULT_TARGET, help="Binary Ninja target selector.")
    parser.add_argument(
        "--header",
        type=Path,
        default=DEFAULT_HEADER_PATH,
        help="Narrow Binary Ninja type header.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    require_borrowed_object_owner(target=args.target)
    operations: list[dict[str, object]] = [
        types_declare_if_missing(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            required_structs=REQUIRED_STRUCTS,
        ),
    ]
    require_catalog_extents(target=args.target)
    operations.extend(
        apply_struct_and_proto_updates(
            REPO_ROOT,
            target=args.target,
            struct_updates=(
                ("RootBodCatalogEntry", ROOT_BOD_CATALOG_ENTRY_FIELD_UPDATES),
                (
                    "RootTrackSliceTripletStrideView",
                    ROOT_TRACK_SLICE_TRIPLET_STRIDE_VIEW_FIELD_UPDATES,
                ),
                (
                    "RootFringeCatalogObjectStrideCursor",
                    ROOT_FRINGE_CATALOG_OBJECT_STRIDE_CURSOR_FIELD_UPDATES,
                ),
                ("GameRoot", GAME_ROOT_FIELD_UPDATES),
            ),
            proto_updates=PROTO_UPDATES,
        )
    )
    user_var_results = apply_user_var_updates(
        REPO_ROOT,
        target=args.target,
        updates=WORLD_INITIALIZER_USER_VAR_UPDATES,
    )
    operations.extend(user_var_results)
    if any(
        operation.get("op") == "user_var_batch" for operation in user_var_results
    ):
        operations.extend(
            reanalyze_functions(
                REPO_ROOT,
                target=args.target,
                identifiers=("initialize_game_assets_and_world",),
            )
        )
    return emit_summary(
        repo_root=REPO_ROOT,
        target=args.target,
        header_path=header_path,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
