#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import (
    apply_split_user_var_update,
    apply_user_var_updates,
    current_struct_fields_batch,
    current_type_widths,
    emit_summary,
)
from _target import DEFAULT_TARGET


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"

EXPECTED_TYPE_WIDTHS = {
    "Vec3": 0xC,
    "TransformMatrix": 0x40,
    "RenderableBod": 0x80,
    "Player": 0x4364,
}

EXPECTED_STRUCT_FIELDS = {
    "Vec3": {
        0x00: ("x", "float"),
        0x04: ("y", "float"),
        0x08: ("z", "float"),
    },
    "TransformMatrix": {
        0x30: ("position", "Vec3"),
        0x3C: ("position_w", "float"),
    },
    "RenderableBod": {
        0x38: ("transform", "TransformMatrix"),
    },
    "Player": {
        0x00: ("body", "RenderableBod"),
    },
}

# Both replay branches initialize the same source-level position cursor from
# Player + offsetof(Player, body.transform.position) == Player + 0x68. The
# native local borrows that owned Vec3 while the adjacent position_w scalar
# remains part of the enclosing TransformMatrix.
PLAYER_POSITION_DEFINITIONS = (
    ("0x43b2c0", "mlil", "RegisterVariableSourceType", 416, 69),
    ("0x43b4f6", "mlil", "RegisterVariableSourceType", 982, 69),
)

PLAYER_POSITION_VAR = (
    "RegisterVariableSourceType",
    416,
    69,
)

# Binary Ninja materializes the post-branch PHI as its own stable EBX
# lifetime. Naming the two producers alone leaves every consumer on the
# analyzer's `ebx_1`; replay the joined lifetime as the same source local.
PLAYER_POSITION_USER_VAR_UPDATES = (
    (
        "update_subgoldy",
        "RegisterVariableSourceType",
        1396,
        69,
        "p_position",
        "Vec3*",
    ),
    (
        "update_subgoldy",
        "RegisterVariableSourceType",
        3225,
        67,
        "swept_position",
        "Vec3*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay update_subgoldy's branch-merged Player position cursor "
            "without changing TransformMatrix ownership."
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
        help="Header documenting the canonical Player transform owner.",
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
            "canonical Player position ownership is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_subgoldy_player_position_owner",
        "status": "verified",
        "types": tuple(EXPECTED_TYPE_WIDTHS),
    }


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations = [verify_owner_layouts(args.target)]
    operations.extend(
        apply_split_user_var_update(
            REPO_ROOT,
            target=args.target,
            identifier="update_subgoldy",
            definitions=PLAYER_POSITION_DEFINITIONS,
            target_var=PLAYER_POSITION_VAR,
            variable_name="p_position",
            variable_type="Vec3*",
        )
    )
    operations.extend(
        apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=PLAYER_POSITION_USER_VAR_UPDATES,
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
