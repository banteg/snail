#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_struct_and_proto_updates,
    current_struct_size,
    emit_summary,
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
)
ROOT_BOD_CATALOG_ENTRY_FIELD_UPDATES = (
    ("0x24", "object", "Object*"),
)
GAME_ROOT_FIELD_UPDATES = (
    ("0x44100", "root_bod_catalog", "RootBodCatalog"),
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
        "RootBodCatalog": 0x4D00,
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
                ("GameRoot", GAME_ROOT_FIELD_UPDATES),
            ),
            proto_updates=PROTO_UPDATES,
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
