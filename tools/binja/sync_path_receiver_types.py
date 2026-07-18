#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_proto_updates,
    apply_symbol_updates,
    current_type_widths,
    emit_summary,
    types_declare_if_missing,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"

EXPECTED_OWNER_SIZES = {
    "Vec3": 0xC,
    "TrackRowCell": 0x54,
    "PathTemplateSample": 0xA8,
    "Path": 0xA8,
}

SYMBOL_UPDATES = (
    ("0x42b9c0", "get_path_position_at_node"),
    ("0x42ca90", "is_point_inside_track_attachment"),
)

PROTO_UPDATES = (
    (
        "get_path_position_at_node",
        "void __thiscall get_path_position_at_node(Path* self, Vec3* out, int32_t node, int32_t row_index, Vec3* local)",
    ),
    (
        "is_point_inside_track_attachment",
        "bool __thiscall is_point_inside_track_attachment(Path* self, Vec3 probe, Vec3 swept_motion, TrackRowCell* cell)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the focused exact Path receiver ABIs."
    )
    parser.add_argument(
        "--target",
        default=DEFAULT_TARGET,
        help="Binary Ninja target selector.",
    )
    parser.add_argument(
        "--header",
        type=Path,
        default=DEFAULT_HEADER_PATH,
        help="Canonical Path owner type header.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Path owner type header not found: {header_path}")

    operations: list[dict[str, object]] = [
        types_declare_if_missing(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            required_structs=EXPECTED_OWNER_SIZES,
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=SYMBOL_UPDATES,
            kind="function",
        ),
        *apply_proto_updates(
            REPO_ROOT,
            target=args.target,
            updates=PROTO_UPDATES,
        ),
    ]

    observed_sizes = current_type_widths(
        REPO_ROOT,
        target=args.target,
        type_names=EXPECTED_OWNER_SIZES,
    )
    mismatches = []
    for name, expected_size in EXPECTED_OWNER_SIZES.items():
        observed_size = observed_sizes.get(name)
        status = "verified" if observed_size == expected_size else "verification_failed"
        operations.append(
            {
                "op": "owner_size_verify",
                "name": name,
                "expected_size": expected_size,
                "observed_size": observed_size,
                "status": status,
            }
        )
        if status == "verification_failed":
            mismatches.append(
                f"{name}: expected {expected_size:#x}, observed {observed_size!r}"
            )

    if mismatches:
        raise RuntimeError("Path receiver owner size mismatch: " + "; ".join(mismatches))

    return emit_summary(
        repo_root=REPO_ROOT,
        target=args.target,
        header_path=header_path,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
