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
    "Vec3": 0x0C,
    "TransformMatrix": 0x40,
    "RenderableBod": 0x80,
    "Snail": 0x19B4,
}

EXPECTED_STRUCT_FIELDS = {
    "Vec3": {
        0x00: ("x", "float"),
        0x04: ("y", "float"),
        0x08: ("z", "float"),
    },
    "RenderableBod": {
        0x38: ("transform", "TransformMatrix"),
    },
    "Snail": {
        0x15CC: ("snail_hotspot_source_body", "RenderableBod"),
        0x164C: ("snail_hotspot_body", "RenderableBod"),
        0x16CC: ("snail_hotspots_local", "Vec3[19]"),
        0x17B0: ("snail_hotspots_world", "Vec3[19]"),
    },
}

# EBP walks the 19-entry world bank. EAX borrows the corresponding local slot
# exactly 19 Vec3 records behind it, while ECX retains the pre-increment world
# destination. All three are element borrows from Snail-owned arrays.
SNAIL_HOTSPOT_CURSOR_USER_VAR_UPDATES = (
    (
        "update_snail_skin",
        "RegisterVariableSourceType",
        13,
        71,
        "hotspot_world_cursor",
        "Vec3*",
    ),
    (
        "update_snail_skin",
        "RegisterVariableSourceType",
        25,
        66,
        "hotspot_local_slot",
        "Vec3*",
    ),
    (
        "update_snail_skin",
        "RegisterVariableSourceType",
        97,
        67,
        "hotspot_world_slot",
        "Vec3*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Replay the borrowed Snail local/world hotspot cursors."
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
        help="Header documenting the canonical Snail hotspot owners.",
    )
    return parser.parse_args()


def verify_snail_hotspot_owner_layout(target: str) -> dict[str, object]:
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
            "canonical Snail hotspot ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_snail_hotspot_owner_layout",
        "status": "verified",
        "types": tuple(EXPECTED_TYPE_WIDTHS),
    }


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations = [
        verify_snail_hotspot_owner_layout(args.target),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=SNAIL_HOTSPOT_CURSOR_USER_VAR_UPDATES,
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
