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
    "PathTemplateSample": 0xA8,
}

EXPECTED_STRUCT_FIELDS = {
    "Vec3": {
        0x00: ("x", "float"),
        0x04: ("y", "float"),
        0x08: ("z", "float"),
    },
    "TransformMatrix": {
        0x00: ("basis_right", "Vec3"),
        0x10: ("basis_up", "Vec3"),
        0x20: ("basis_forward", "Vec3"),
        0x30: ("position", "Vec3"),
    },
    "PathTemplateSample": {
        0x00: ("transform", "TransformMatrix"),
        0x80: ("delta_dir_to_next", "Vec3"),
        0x8C: ("delta_length", "float"),
    },
}

# The ordinary traversal branch owns a current and next secondary sample, then
# publishes the interpolated transform rows into the live player matrix. A
# second branch repeats the same matrix publication before copying the stored
# FollowState output vector back to the caller. All ten identities preserve a
# zero-__offset decompile in transactional preview.
#
# Two tempting enclosing-sample views are intentionally omitted. Typing the
# primary interpolation cursor at 559 as PathTemplateSample* creates three
# forward offsets for fields in the next sample; typing the terminal boundary
# at 744 creates five negative offsets while reading the preceding sample.
ATTACHMENT_FOLLOW_LIFETIME_SPECS = (
    (1406, 66, "current_secondary_sample", "PathTemplateSample*"),
    (1596, 72, "secondary_sample", "PathTemplateSample*"),
    (1717, 72, "next_secondary_sample", "PathTemplateSample*"),
    (1491, 68, "player_right", "Vec3*"),
    (1523, 67, "player_up", "Vec3*"),
    (1554, 66, "player_forward", "Vec3*"),
    (2058, 66, "player_transform", "TransformMatrix*"),
    (2091, 68, "player_up_reloaded", "Vec3*"),
    (2123, 67, "player_forward_reloaded", "Vec3*"),
    (2538, 68, "output_position_copy", "Vec3*"),
)

ATTACHMENT_FOLLOW_USER_VAR_UPDATES = tuple(
    (
        "update_track_attachment_follow_state",
        "RegisterVariableSourceType",
        index,
        storage,
        variable_name,
        variable_type,
    )
    for index, storage, variable_name, variable_type in (
        ATTACHMENT_FOLLOW_LIFETIME_SPECS
    )
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the proved sample, player-matrix, and output-vector "
            "lifetimes in the track-attachment traversal."
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
        help="Header documenting the canonical path-follow owners.",
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
            "canonical attachment-follow ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_attachment_follow_owner_layouts",
        "status": "verified",
        "types": tuple(EXPECTED_TYPE_WIDTHS),
    }


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"path ownership header not found: {header_path}")

    operations = [
        verify_owner_layouts(args.target),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=ATTACHMENT_FOLLOW_USER_VAR_UPDATES,
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
