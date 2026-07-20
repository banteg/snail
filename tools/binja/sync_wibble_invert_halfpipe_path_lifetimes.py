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

# These three nonlinear constructors retain the same complete vector, sample,
# vertex, and face owners around different curve builders. Transactional
# preview proved every lifetime below without increasing each function's
# existing fixed-index __offset count. Halfpipe's transient curved-sample
# cursor is deliberately omitted: it is a pre-biased address, and forcing it
# to PathTemplateSample* introduced three backward __offset expressions.
WIBBLE_PATH_LIFETIME_SPECS = (
    (134, 66, "primary_seed_sample", "PathTemplateSample*"),
    (640, 68, "primary_up", "Vec3*"),
    (745, 67, "primary_right", "Vec3*"),
    (830, 66, "secondary_position", "Vec3*"),
    (1139, 67, "primary_terminal_delta", "Vec3*"),
    (1228, 66, "secondary_terminal_delta", "Vec3*"),
    (1389, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (1451, 66, "vertex", "Vec3*"),
    (1797, 73, "face_first", "ObjectFaceQuad*"),
    (1975, 73, "face_second", "ObjectFaceQuad*"),
)

INVERT_PATH_LIFETIME_SPECS = (
    (134, 66, "primary_seed_sample", "PathTemplateSample*"),
    (609, 68, "primary_up", "Vec3*"),
    (714, 67, "primary_right", "Vec3*"),
    (799, 66, "secondary_position", "Vec3*"),
    (1108, 67, "primary_terminal_delta", "Vec3*"),
    (1197, 66, "secondary_terminal_delta", "Vec3*"),
    (1358, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (1420, 66, "vertex", "Vec3*"),
    (1766, 73, "face_first", "ObjectFaceQuad*"),
    (1944, 73, "face_second", "ObjectFaceQuad*"),
)

HALFPIPE_PATH_LIFETIME_SPECS = (
    (240, 66, "primary_leadin_sample", "PathTemplateSample*"),
    (873, 67, "primary_up", "Vec3*"),
    (974, 67, "primary_right", "Vec3*"),
    (1012, 66, "primary_up_reloaded", "Vec3*"),
    (1049, 66, "secondary_position", "Vec3*"),
    (1367, 67, "primary_terminal_delta", "Vec3*"),
    (1456, 66, "secondary_terminal_delta", "Vec3*"),
    (1626, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (1692, 67, "vertex", "Vec3*"),
    (2167, 73, "face_first", "ObjectFaceQuad*"),
    (2351, 73, "face_second", "ObjectFaceQuad*"),
)

WIBBLE_INVERT_HALFPIPE_PATH_USER_VAR_UPDATES = tuple(
    (
        function_name,
        "RegisterVariableSourceType",
        index,
        storage,
        variable_name,
        variable_type,
    )
    for function_name, specs in (
        ("initialize_wibble_path_template_pair", WIBBLE_PATH_LIFETIME_SPECS),
        ("initialize_invert_path_template_pair", INVERT_PATH_LIFETIME_SPECS),
        ("initialize_halfpipe_path_template_pair", HALFPIPE_PATH_LIFETIME_SPECS),
    )
    for index, storage, variable_name, variable_type in specs
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the proved sample, vector, mesh-vertex, and facequad "
            "lifetimes in the wibble, invert, and halfpipe constructors."
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
            "canonical wibble/invert/halfpipe ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_wibble_invert_halfpipe_path_owner_layouts",
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
            updates=WIBBLE_INVERT_HALFPIPE_PATH_USER_VAR_UPDATES,
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
