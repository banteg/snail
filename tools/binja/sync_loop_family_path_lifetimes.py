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

# Transactional previews proved the same eleven semantic lifetimes in all
# three loop constructors without introducing any __offset expressions. The
# loopout register-variable IDs are deliberately recorded separately: its
# approach/departure setup gives the shared native skeleton a different SSA
# schedule from the two loop-the-loop variants.
LOOPTHELOOP_PATH_LIFETIME_SPECS = (
    (1047, 66, "primary_right", "Vec3*"),
    (1122, 66, "primary_right_reloaded", "Vec3*"),
    (1152, 68, "secondary_right", "Vec3*"),
    (1225, 66, "secondary_right_reloaded", "Vec3*"),
    (1524, 68, "primary_terminal_delta", "Vec3*"),
    (1613, 67, "secondary_terminal_delta", "Vec3*"),
    (1778, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (1844, 67, "vertex", "Vec3*"),
    (1966, 68, "terminal_vertex", "Vec3*"),
    (2210, 71, "face_first", "ObjectFaceQuad*"),
    (2389, 71, "face_second", "ObjectFaceQuad*"),
)

LOOPTHELOOPW_PATH_LIFETIME_SPECS = (
    (1111, 66, "primary_right", "Vec3*"),
    (1181, 66, "primary_right_reloaded", "Vec3*"),
    (1224, 68, "secondary_right", "Vec3*"),
    (1301, 66, "secondary_right_reloaded", "Vec3*"),
    (1613, 68, "primary_terminal_delta", "Vec3*"),
    (1702, 67, "secondary_terminal_delta", "Vec3*"),
    (1867, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (1933, 67, "vertex", "Vec3*"),
    (2055, 68, "terminal_vertex", "Vec3*"),
    (2299, 71, "face_first", "ObjectFaceQuad*"),
    (2484, 71, "face_second", "ObjectFaceQuad*"),
)

LOOPOUT_PATH_LIFETIME_SPECS = (
    (1025, 67, "primary_right", "Vec3*"),
    (1112, 66, "primary_right_reloaded", "Vec3*"),
    (1141, 66, "secondary_right", "Vec3*"),
    (1215, 66, "secondary_right_reloaded", "Vec3*"),
    (1515, 68, "primary_terminal_delta", "Vec3*"),
    (1604, 67, "secondary_terminal_delta", "Vec3*"),
    (1769, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (1835, 67, "vertex", "Vec3*"),
    (1957, 68, "terminal_vertex", "Vec3*"),
    (2201, 71, "face_first", "ObjectFaceQuad*"),
    (2380, 71, "face_second", "ObjectFaceQuad*"),
)

LOOP_FAMILY_PATH_USER_VAR_UPDATES = tuple(
    (
        function_name,
        "RegisterVariableSourceType",
        index,
        storage,
        variable_name,
        variable_type,
    )
    for function_name, specs in (
        (
            "initialize_looptheloop_path_template_pair",
            LOOPTHELOOP_PATH_LIFETIME_SPECS,
        ),
        (
            "initialize_looptheloopw_path_template_pair",
            LOOPTHELOOPW_PATH_LIFETIME_SPECS,
        ),
        ("initialize_loopout_path_template_pair", LOOPOUT_PATH_LIFETIME_SPECS),
    )
    for index, storage, variable_name, variable_type in specs
)

# The paired Android and iOS BuildLoopTheLoop bodies independently preserve
# the portable setup through CalcLengthZ: derived counts and radii, fixed
# seven-sample lead and tail passes, the circular sample pass, and the delta
# pass. Windows remains authoritative for every exact MLIL identity below and
# for its additional strip-mesh and facequad tail, which this pass leaves
# untouched.
LOOPTHELOOP_CONTROL_USER_VAR_UPDATES = (
    (
        "initialize_looptheloop_path_template_pair",
        "StackVariableSourceType",
        98,
        -72,
        "curve_count_f",
        "float",
    ),
    (
        "initialize_looptheloop_path_template_pair",
        "StackVariableSourceType",
        137,
        -76,
        "lead_sample_z",
        "float",
    ),
    (
        "initialize_looptheloop_path_template_pair",
        "StackVariableSourceType",
        711,
        -76,
        "secondary_radius",
        "float",
    ),
    (
        "initialize_looptheloop_path_template_pair",
        "StackVariableSourceType",
        764,
        -68,
        "angle",
        "float",
    ),
)

LOOPTHELOOP_CONTROL_LIFETIME_SPLITS = (
    (
        (
            ("0x41b105", "mlil", "StackVariableSourceType", 21, -84),
            ("0x41b10e", "mlil", "StackVariableSourceType", 30, -84),
            ("0x41b116", "mlil_ssa", "StackVariableSourceType", 38, -84),
        ),
        ("StackVariableSourceType", 21, -84),
        "loop_wiggle",
        "float",
    ),
    (
        (
            ("0x41b12a", "mlil", "RegisterVariableSourceType", 58, 66),
            ("0x41b12f", "mlil", "StackVariableSourceType", 63, -80),
        ),
        ("RegisterVariableSourceType", 58, 66),
        "curve_count",
        "int32_t",
    ),
    (
        (
            ("0x41b133", "mlil", "RegisterVariableSourceType", 67, 66),
            ("0x41b136", "mlil", "StackVariableSourceType", 70, -68),
        ),
        ("RegisterVariableSourceType", 67, 66),
        "total_segment_count",
        "int32_t",
    ),
    (
        (("0x41b15c", "mlil", "StackVariableSourceType", 108, 4),),
        ("StackVariableSourceType", 108, 4),
        "loop_radius",
        "float",
    ),
    (
        (
            ("0x41b16c", "mlil", "StackVariableSourceType", 124, 8),
            ("0x41b24e", "mlil", "StackVariableSourceType", 350, 8),
            ("0x41b172", "mlil_ssa", "StackVariableSourceType", 130, 8),
        ),
        ("StackVariableSourceType", 124, 8),
        "lead_sample_index",
        "int32_t",
    ),
    (
        (
            ("0x41b170", "mlil", "RegisterVariableSourceType", 128, 73),
            ("0x41b23d", "mlil", "RegisterVariableSourceType", 333, 73),
            ("0x41b172", "mlil_ssa", "RegisterVariableSourceType", 130, 73),
        ),
        ("RegisterVariableSourceType", 128, 73),
        "lead_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x41b25c", "mlil", "RegisterVariableSourceType", 364, 69),
            ("0x41b25e", "mlil", "StackVariableSourceType", 366, 8),
            ("0x41b333", "mlil", "RegisterVariableSourceType", 579, 69),
            ("0x41b33b", "mlil", "StackVariableSourceType", 587, 8),
            ("0x41b274", "mlil_ssa", "RegisterVariableSourceType", 388, 69),
            ("0x41b274", "mlil_ssa", "StackVariableSourceType", 388, 8),
        ),
        ("RegisterVariableSourceType", 364, 69),
        "tail_index",
        "int32_t",
    ),
    (
        (("0x41b300", "mlil", "StackVariableSourceType", 528, 8),),
        ("StackVariableSourceType", 528, 8),
        "tail_sample_z",
        "float",
    ),
    (
        (
            ("0x41b271", "mlil", "RegisterVariableSourceType", 385, 73),
            ("0x41b351", "mlil", "RegisterVariableSourceType", 609, 73),
            ("0x41b274", "mlil_ssa", "RegisterVariableSourceType", 388, 73),
        ),
        ("RegisterVariableSourceType", 385, 73),
        "tail_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x41b3c6", "mlil", "RegisterVariableSourceType", 726, 67),
            ("0x41b3c9", "mlil", "StackVariableSourceType", 729, -64),
            ("0x41b3d4", "mlil", "RegisterVariableSourceType", 740, 67),
            ("0x41b3d8", "mlil_ssa", "RegisterVariableSourceType", 744, 67),
        ),
        ("RegisterVariableSourceType", 726, 67),
        "terminal_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x41b36c", "mlil", "StackVariableSourceType", 636, 8),
            ("0x41b5d1", "mlil", "RegisterVariableSourceType", 1249, 66),
            ("0x41b5da", "mlil", "StackVariableSourceType", 1258, 8),
            ("0x41b3d8", "mlil_ssa", "StackVariableSourceType", 744, 8),
        ),
        ("StackVariableSourceType", 636, 8),
        "curve_index",
        "int32_t",
    ),
    (
        (
            ("0x41b3cd", "mlil", "RegisterVariableSourceType", 733, 73),
            ("0x41b5d2", "mlil", "RegisterVariableSourceType", 1250, 73),
            ("0x41b3d8", "mlil_ssa", "RegisterVariableSourceType", 744, 73),
        ),
        ("RegisterVariableSourceType", 733, 73),
        "curve_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x41b5e7", "mlil", "RegisterVariableSourceType", 1271, 69),
            ("0x41b6a0", "mlil", "RegisterVariableSourceType", 1456, 69),
            ("0x41b5f4", "mlil_ssa", "RegisterVariableSourceType", 1284, 69),
        ),
        ("RegisterVariableSourceType", 1271, 69),
        "delta_index",
        "int32_t",
    ),
    (
        (
            ("0x41b5f2", "mlil", "RegisterVariableSourceType", 1282, 73),
            ("0x41b6ab", "mlil", "RegisterVariableSourceType", 1467, 73),
            ("0x41b5f4", "mlil_ssa", "RegisterVariableSourceType", 1284, 73),
        ),
        ("RegisterVariableSourceType", 1282, 73),
        "delta_sample_offset",
        "int32_t",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the proved control, vector, terminal-delta, mesh-vertex, "
            "and facequad lifetimes in the loop-the-loop, W-loop, and loopout "
            "constructors."
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
            "canonical loop-family ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_loop_family_path_owner_layouts",
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
                LOOP_FAMILY_PATH_USER_VAR_UPDATES
                + LOOPTHELOOP_CONTROL_USER_VAR_UPDATES
            ),
        ),
        *apply_split_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=tuple(
                (
                    "initialize_looptheloop_path_template_pair",
                    definitions,
                    target_var,
                    variable_name,
                    variable_type,
                )
                for definitions, target_var, variable_name, variable_type in (
                    LOOPTHELOOP_CONTROL_LIFETIME_SPLITS
                )
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
