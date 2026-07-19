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
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/star_manager_types.h"

EXPECTED_TYPE_WIDTHS = {
    "Vec3": 0x0C,
    "tColour": 0x10,
    "Sprite": 0xB4,
    "StarManagerEntry": 0x2C,
    "StarManager": 0x4C,
}

EXPECTED_STRUCT_FIELDS = {
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
    "Sprite": {
        0x04: ("flags", "SpriteFlag"),
        0x2C: ("color", "tColour"),
        0x48: ("position", "Vec3"),
        0x54: ("velocity", "Vec3"),
        0x60: ("size_start", "float"),
        0x64: ("size_end", "float"),
        0x68: ("progress", "float"),
        0x6C: ("progress_step", "float"),
        0x78: ("gravity_step", "float"),
        0x88: ("corner_scale", "float"),
        0x8C: ("facing_refresh_progress", "float"),
    },
    "StarManagerEntry": {
        0x04: ("position", "Vec3"),
        0x10: ("velocity", "Vec3"),
        0x1C: ("sprite", "Sprite*"),
        0x20: ("speed", "float"),
        0x24: ("travel_distance", "float"),
        0x28: ("alpha_scale", "float"),
    },
    "StarManager": {
        0x3C: ("entries", "StarManagerEntry*"),
        0x40: ("count", "int32_t"),
        0x44: ("fade", "float"),
    },
}

# Native retains a byte offset in EDI while the loop index advances in EBX.
# Retyping that offset as an integer makes HLIL incorrectly associate the final
# facing-refresh store with the incremented index, so it deliberately remains
# automatic. These exact derived definitions are genuine borrowed owners: one
# StarManagerEntry, its Sprite, and the Vec3/tColour children copied into it.
STAR_FIELD_USER_VAR_UPDATES = (
    (
        "initialize_star_field",
        "RegisterVariableSourceType",
        245,
        67,
        "entry_position",
        "Vec3*",
    ),
    (
        "initialize_star_field",
        "RegisterVariableSourceType",
        318,
        68,
        "entry_velocity",
        "Vec3*",
    ),
    (
        "initialize_star_field",
        "RegisterVariableSourceType",
        392,
        66,
        "scaled_velocity",
        "Vec3*",
    ),
    (
        "initialize_star_field",
        "RegisterVariableSourceType",
        507,
        66,
        "motion_entry",
        "StarManagerEntry*",
    ),
    (
        "initialize_star_field",
        "RegisterVariableSourceType",
        616,
        66,
        "sprite",
        "Sprite*",
    ),
    (
        "initialize_star_field",
        "RegisterVariableSourceType",
        680,
        68,
        "sprite_color",
        "tColour*",
    ),
    (
        "initialize_star_field",
        "RegisterVariableSourceType",
        720,
        66,
        "size_sprite",
        "Sprite*",
    ),
    (
        "initialize_star_field",
        "RegisterVariableSourceType",
        764,
        66,
        "velocity_entry",
        "StarManagerEntry*",
    ),
    (
        "initialize_star_field",
        "RegisterVariableSourceType",
        773,
        66,
        "sprite_velocity",
        "Vec3*",
    ),
    (
        "initialize_star_field",
        "RegisterVariableSourceType",
        795,
        66,
        "position_entry",
        "StarManagerEntry*",
    ),
    (
        "initialize_star_field",
        "RegisterVariableSourceType",
        803,
        68,
        "sprite_position",
        "Vec3*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the borrowed entry, Sprite, vector, and color lifetimes "
            "in cRStarManager::Init."
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
        help="Header documenting the canonical star and Sprite owners.",
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
            "canonical star-field ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_star_field_owner_layouts",
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
            updates=STAR_FIELD_USER_VAR_UPDATES,
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
