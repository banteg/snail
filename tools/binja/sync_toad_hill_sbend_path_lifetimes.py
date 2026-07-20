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
    "PathTemplateSample": 0xA8,
    "ObjectFaceQuad": 0x30,
}

EXPECTED_STRUCT_FIELDS = {
    "Vec3": {
        0x00: ("x", "float"),
        0x04: ("y", "float"),
        0x08: ("z", "float"),
    },
    "PathTemplateSample": {
        0x00: ("transform", "TransformMatrix"),
        0x80: ("delta_dir_to_next", "Vec3"),
        0x8C: ("delta_length", "float"),
        0x90: ("center_x", "float"),
    },
    "ObjectFaceQuad": {
        0x02: ("vertex_0", "uint16_t"),
        0x08: ("vertex_3", "uint16_t"),
        0x0C: ("texture_ref", "TextureRef*"),
        0x10: ("uv", "ObjectUv[4]"),
    },
}

# These adjacent nonlinear constructors share the sample, terminal-delta,
# vertex, and face owner skeleton. Transactional preview proved every retained
# lifetime below without adding __offset expressions. Hill/valley's primary
# and secondary forward cursors and s-bend's primary forward cursor are
# deliberately omitted: they are byte-biased addresses, and forcing them to
# Vec3* introduced eight and four backward __offset expressions respectively.
TOAD_PATH_LIFETIME_SPECS = (
    (949, 67, "primary_right", "Vec3*"),
    (1036, 66, "secondary_position", "Vec3*"),
    (1351, 67, "primary_terminal_delta", "Vec3*"),
    (1440, 66, "secondary_terminal_delta", "Vec3*"),
    (1601, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (1663, 66, "vertex", "Vec3*"),
    (2009, 73, "face_first", "ObjectFaceQuad*"),
    (2187, 73, "face_second", "ObjectFaceQuad*"),
)

HILL_VALLEY_PATH_LIFETIME_SPECS = (
    (173, 66, "primary_seed_sample", "PathTemplateSample*"),
    (753, 66, "primary_right", "Vec3*"),
    (923, 67, "secondary_right", "Vec3*"),
    (1377, 68, "primary_terminal_delta", "Vec3*"),
    (1466, 67, "secondary_terminal_delta", "Vec3*"),
    (1625, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (1687, 66, "vertex", "Vec3*"),
    (2035, 71, "face_first", "ObjectFaceQuad*"),
    (2214, 71, "face_second", "ObjectFaceQuad*"),
)

SBEND_PATH_LIFETIME_SPECS = (
    (179, 66, "primary_seed_sample", "PathTemplateSample*"),
    (499, 68, "primary_up", "Vec3*"),
    (603, 66, "primary_right", "Vec3*"),
    (684, 66, "secondary_position", "Vec3*"),
    (999, 68, "primary_terminal_delta", "Vec3*"),
    (1087, 68, "secondary_terminal_delta", "Vec3*"),
    (1250, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (1312, 66, "vertex", "Vec3*"),
    (1658, 69, "face_first", "ObjectFaceQuad*"),
    (1836, 69, "face_second", "ObjectFaceQuad*"),
)

TOAD_HILL_SBEND_PATH_USER_VAR_UPDATES = tuple(
    (
        function_name,
        "RegisterVariableSourceType",
        index,
        storage,
        variable_name,
        variable_type,
    )
    for function_name, specs in (
        ("initialize_toad_path_template_pair", TOAD_PATH_LIFETIME_SPECS),
        (
            "initialize_hill_valley_path_template_pair",
            HILL_VALLEY_PATH_LIFETIME_SPECS,
        ),
        ("initialize_sbend_path_template_pair", SBEND_PATH_LIFETIME_SPECS),
    )
    for index, storage, variable_name, variable_type in specs
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the proved sample, vector, mesh-vertex, and facequad "
            "lifetimes in the toad, hill/valley, and s-bend constructors."
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
        help="Header documenting the canonical path and mesh owners.",
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
            "canonical toad/hill/s-bend ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_toad_hill_sbend_path_owner_layouts",
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
            updates=TOAD_HILL_SBEND_PATH_USER_VAR_UPDATES,
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
