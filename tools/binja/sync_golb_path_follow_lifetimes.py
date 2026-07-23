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
    "TrackRowCell": 0x54,
    "GolbPathFollowState": 0x28,
    "GolbShot": 0x2E8,
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
        0x90: ("center_x", "float"),
        0x9C: ("lateral_scale", "float"),
        0xA0: ("special_scalar", "float"),
    },
    "TrackRowCell": {
        0x10: ("anchor_position", "Vec3"),
    },
    "GolbPathFollowState": {
        0x04: ("template_record", "Path*"),
        0x08: ("source_cell", "TrackRowCell*"),
        0x18: ("output_position", "Vec3"),
        0x24: ("shot", "GolbShot*"),
    },
    "GolbShot": {
        0x1C4: ("flight_transform", "TransformMatrix"),
        0x24C: ("velocity", "Vec3"),
        0x258: ("direction", "Vec3"),
    },
}

# The Golb traversal has three complete position publications, one ordinary
# secondary-sample owner, a kind-42 current-sample owner, the state output
# vector, and the three independently scheduled flight-transform basis rows.
# All eleven identities preserve a zero-__offset decompile in transactional
# preview.
#
# Two wider sample casts are intentionally omitted. Register lifetime 193 is a
# primary-sample byte cursor that also reaches into the next 0xa8-byte sample;
# forcing PathTemplateSample* creates three forward offsets. Lifetime 354 is
# the one-past-end secondary boundary used to read the terminal sample; the
# same cast creates five negative offsets.
GOLB_PATH_FOLLOW_LIFETIME_SPECS = (
    (261, 68, "flight_position_overflow", "Vec3*"),
    (360, 68, "source_anchor_position", "Vec3*"),
    (468, 68, "flight_position_terminal", "Vec3*"),
    (827, 66, "current_secondary_sample", "PathTemplateSample*"),
    (836, 67, "output_position", "Vec3*"),
    (924, 72, "secondary_sample", "PathTemplateSample*"),
    (1185, 66, "output_position_write", "Vec3*"),
    (1313, 66, "flight_transform", "TransformMatrix*"),
    (1341, 66, "flight_up", "Vec3*"),
    (1369, 66, "flight_forward", "Vec3*"),
    (1476, 68, "flight_position_side_exit", "Vec3*"),
)

GOLB_PATH_FOLLOW_USER_VAR_UPDATES = tuple(
    (
        "calc_path_length_z",
        "RegisterVariableSourceType",
        index,
        storage,
        variable_name,
        variable_type,
    )
    for index, storage, variable_name, variable_type in (
        GOLB_PATH_FOLLOW_LIFETIME_SPECS
    )
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the proved sample, output, and flight-transform lifetimes "
            "in the Golb path-follow traversal."
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
        help="Header documenting the canonical Golb path-follow owners.",
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
            "canonical Golb path-follow ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_golb_path_follow_owner_layouts",
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
            updates=GOLB_PATH_FOLLOW_USER_VAR_UPDATES,
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
