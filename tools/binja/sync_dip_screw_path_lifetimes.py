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

# These adjacent constructors share the terminal-delta and strip-mesh owner
# skeleton but build orientation differently. Dip owns two basis-right vectors
# and two simultaneous faces. Screw owns two basis-up vectors and reuses one
# face cursor across its two-pass inner loop. Their byte-biased forward-vector
# candidates are intentionally omitted: transactional previews introduced
# eight __offset expressions in dip and four in screw.
DIP_PATH_LIFETIME_SPECS = (
    (679, 66, "primary_right", "Vec3*"),
    (849, 67, "secondary_right", "Vec3*"),
    (1303, 68, "primary_terminal_delta", "Vec3*"),
    (1392, 67, "secondary_terminal_delta", "Vec3*"),
    (1553, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (1619, 67, "vertex", "Vec3*"),
    (1740, 67, "terminal_vertex", "Vec3*"),
    (1976, 71, "face_first", "ObjectFaceQuad*"),
    (2155, 71, "face_second", "ObjectFaceQuad*"),
)

SCREW_PATH_LIFETIME_SPECS = (
    (797, 67, "primary_up", "Vec3*"),
    (981, 68, "secondary_up", "Vec3*"),
    (1446, 68, "primary_terminal_delta", "Vec3*"),
    (1535, 67, "secondary_terminal_delta", "Vec3*"),
    (1694, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (1756, 66, "vertex", "Vec3*"),
    (2094, 73, "face", "ObjectFaceQuad*"),
)

DIP_SCREW_PATH_USER_VAR_UPDATES = tuple(
    (
        function_name,
        "RegisterVariableSourceType",
        index,
        storage,
        variable_name,
        variable_type,
    )
    for function_name, specs in (
        ("initialize_dip_path_template_pair", DIP_PATH_LIFETIME_SPECS),
        ("initialize_screw_path_template_pair", SCREW_PATH_LIFETIME_SPECS),
    )
    for index, storage, variable_name, variable_type in specs
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the proved vector, terminal-delta, mesh-vertex, and "
            "facequad lifetimes in the dip and screw constructors."
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
            "canonical dip/screw ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_dip_screw_path_owner_layouts",
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
            updates=DIP_SCREW_PATH_USER_VAR_UPDATES,
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
