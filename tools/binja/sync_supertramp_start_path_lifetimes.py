#!/usr/bin/env python3

from __future__ import annotations

import argparse
import sys
from pathlib import Path

from _narrow_sync import (
    apply_split_user_var_updates,
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
        0x90: ("center_x", "float"),
    },
    "ObjectFaceQuad": {
        0x02: ("vertex_0", "uint16_t"),
        0x08: ("vertex_3", "uint16_t"),
        0x0C: ("texture_ref", "TextureRef*"),
        0x10: ("uv", "ObjectUv[4]"),
    },
}

# BuildSupertrampA and BuildStartA both retain complete path samples, basis
# vectors, mesh vertices, and face records, but their curve builders produce
# unrelated MLIL identities. Transactional preview proved every lifetime below
# and introduced no __offset expressions. Start's intermediate secondary
# current-sample cursor is deliberately omitted because its negative
# byte-relative accesses became less exact when typed.
SUPERTRAMP_PATH_LIFETIME_SPECS = (
    (187, 66, "primary_seed_sample", "PathTemplateSample*"),
    (637, 67, "primary_right", "Vec3*"),
    (744, 66, "secondary_right", "Vec3*"),
    (772, 66, "secondary_curve_sample", "PathTemplateSample*"),
    (1185, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (1268, 67, "vertex", "Vec3*"),
    (1499, 71, "face_first", "ObjectFaceQuad*"),
    (1696, 71, "face_second", "ObjectFaceQuad*"),
)

START_PATH_LIFETIME_SPECS = (
    (660, 66, "primary_curve_sample", "PathTemplateSample*"),
    (831, 66, "primary_right", "Vec3*"),
    (949, 66, "primary_sample_cursor_reloaded", "PathTemplateSample*"),
    (1001, 67, "secondary_right", "Vec3*"),
    (1116, 66, "secondary_sample_cursor_reloaded", "PathTemplateSample*"),
    (1517, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (1596, 67, "vertex", "Vec3*"),
    (1820, 71, "face_first", "ObjectFaceQuad*"),
    (1988, 71, "face_second", "ObjectFaceQuad*"),
)

SUPERTRAMP_START_PATH_USER_VAR_UPDATES = tuple(
    (
        function_name,
        "RegisterVariableSourceType",
        index,
        storage,
        variable_name,
        variable_type,
    )
    for function_name, specs in (
        ("initialize_supertramp_path_template_pair", SUPERTRAMP_PATH_LIFETIME_SPECS),
        ("initialize_start_path_template_pair", START_PATH_LIFETIME_SPECS),
    )
    for index, storage, variable_name, variable_type in specs
)

# The exact Android and iOS BuildStart bodies independently preserve the
# portable five-sample lead, eleven-sample tail, cosine middle, orientation,
# and final-delta control graph. Windows remains authoritative for every
# definition identity, the native 0xa8-byte sample cursors, and the strip-mesh
# tail. These isolated stack values do not share storage identities with the
# mesh builder.
START_CONTROL_USER_VAR_UPDATES = (
    (
        "initialize_start_path_template_pair",
        "StackVariableSourceType",
        83,
        -64,
        "curve_count_f",
        "float",
    ),
    (
        "initialize_start_path_template_pair",
        "StackVariableSourceType",
        342,
        -60,
        "tail_samples_remaining",
        "int32_t",
    ),
    (
        "initialize_start_path_template_pair",
        "StackVariableSourceType",
        665,
        -52,
        "curve_sample_index",
        "int32_t",
    ),
    (
        "initialize_start_path_template_pair",
        "StackVariableSourceType",
        708,
        -88,
        "angle",
        "float",
    ),
)

START_CONTROL_LIFETIME_SPLITS = (
    (
        (
            ("0x42642a", "mlil", "RegisterVariableSourceType", 42, 66),
            ("0x42642f", "mlil", "StackVariableSourceType", 47, -68),
        ),
        ("RegisterVariableSourceType", 42, 66),
        "curve_count",
        "int32_t",
    ),
    (
        (("0x42645d", "mlil", "StackVariableSourceType", 93, 4),),
        ("StackVariableSourceType", 93, 4),
        "curve_radius",
        "float",
    ),
    (
        (
            ("0x426477", "mlil", "StackVariableSourceType", 119, 8),
            ("0x426544", "mlil", "StackVariableSourceType", 324, 8),
            ("0x42648e", "mlil_ssa", "StackVariableSourceType", 142, 8),
        ),
        ("StackVariableSourceType", 119, 8),
        "lead_sample_index",
        "int32_t",
    ),
    (
        (
            ("0x42647e", "mlil", "RegisterVariableSourceType", 126, 73),
            ("0x426538", "mlil", "RegisterVariableSourceType", 312, 73),
            ("0x42648e", "mlil_ssa", "RegisterVariableSourceType", 142, 73),
        ),
        ("RegisterVariableSourceType", 126, 73),
        "lead_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x426561", "mlil", "StackVariableSourceType", 353, 8),
            ("0x42662c", "mlil", "StackVariableSourceType", 556, 8),
            ("0x426574", "mlil_ssa", "StackVariableSourceType", 372, 8),
        ),
        ("StackVariableSourceType", 353, 8),
        "tail_sample_index",
        "int32_t",
    ),
    (
        (
            ("0x426571", "mlil", "RegisterVariableSourceType", 369, 73),
            ("0x426624", "mlil", "RegisterVariableSourceType", 548, 73),
            ("0x426574", "mlil_ssa", "RegisterVariableSourceType", 372, 73),
        ),
        ("RegisterVariableSourceType", 369, 73),
        "tail_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x42663e", "mlil", "StackVariableSourceType", 574, 8),
            ("0x4268aa", "mlil", "StackVariableSourceType", 1194, 8),
            ("0x42664f", "mlil_ssa", "StackVariableSourceType", 591, 8),
        ),
        ("StackVariableSourceType", 574, 8),
        "curve_index",
        "int32_t",
    ),
    (
        (
            ("0x42664a", "mlil", "RegisterVariableSourceType", 586, 73),
            ("0x4268a2", "mlil", "RegisterVariableSourceType", 1186, 73),
            ("0x42664f", "mlil_ssa", "RegisterVariableSourceType", 591, 73),
        ),
        ("RegisterVariableSourceType", 586, 73),
        "curve_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x4268b7", "mlil", "RegisterVariableSourceType", 1207, 69),
            ("0x426972", "mlil", "RegisterVariableSourceType", 1394, 69),
            ("0x4268c3", "mlil_ssa", "RegisterVariableSourceType", 1219, 69),
        ),
        ("RegisterVariableSourceType", 1207, 69),
        "delta_index",
        "int32_t",
    ),
    (
        (
            ("0x4268c1", "mlil", "RegisterVariableSourceType", 1217, 73),
            ("0x42697d", "mlil", "RegisterVariableSourceType", 1405, 73),
            ("0x4268c3", "mlil_ssa", "RegisterVariableSourceType", 1219, 73),
        ),
        ("RegisterVariableSourceType", 1217, 73),
        "delta_sample_offset",
        "int32_t",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the control, sample, basis-vector, mesh-vertex, and "
            "facequad lifetimes in the supertramp and start path constructors."
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
            "canonical supertramp/start ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_supertramp_start_path_owner_layouts",
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
            updates=(
                SUPERTRAMP_START_PATH_USER_VAR_UPDATES
                + START_CONTROL_USER_VAR_UPDATES
            ),
        ),
        *apply_split_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=tuple(
                (
                    "initialize_start_path_template_pair",
                    definitions,
                    target_var,
                    variable_name,
                    variable_type,
                )
                for (
                    definitions,
                    target_var,
                    variable_name,
                    variable_type,
                ) in START_CONTROL_LIFETIME_SPLITS
            ),
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
