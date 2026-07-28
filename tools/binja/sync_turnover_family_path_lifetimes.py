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

# BuildTurnoverA, BuildTurnoverDoubleA, and BuildTurnunderA share the same
# sample, terminal-delta, and mesh-owner skeleton, but their compiler-assigned
# MLIL identities differ. Transactional preview proved the complete aggregate
# owners below without introducing __offset expressions. Their curved-sample
# cursors remain honest byte offsets: forcing the pre-biased addresses to
# PathTemplateSample* produced backward __offset accesses.
TURNOVER_PATH_LIFETIME_SPECS = (
    (191, 66, "primary_seed_sample", "PathTemplateSample*"),
    (858, 67, "primary_up", "Vec3*"),
    (1044, 66, "secondary_position", "Vec3*"),
    (1358, 67, "primary_terminal_delta", "Vec3*"),
    (1446, 67, "secondary_terminal_delta", "Vec3*"),
    (1609, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (1671, 66, "vertex", "Vec3*"),
    (2017, 69, "face_first", "ObjectFaceQuad*"),
    (2195, 69, "face_second", "ObjectFaceQuad*"),
)

TURNOVERDOUBLE_PATH_LIFETIME_SPECS = (
    (191, 66, "primary_seed_sample", "PathTemplateSample*"),
    (892, 67, "primary_up", "Vec3*"),
    (1075, 66, "secondary_position", "Vec3*"),
    (1389, 67, "primary_terminal_delta", "Vec3*"),
    (1477, 67, "secondary_terminal_delta", "Vec3*"),
    (1640, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (1702, 66, "vertex", "Vec3*"),
    (2048, 69, "face_first", "ObjectFaceQuad*"),
    (2226, 69, "face_second", "ObjectFaceQuad*"),
)

TURNUNDER_PATH_LIFETIME_SPECS = (
    (195, 66, "primary_seed_sample", "PathTemplateSample*"),
    (902, 66, "primary_up", "Vec3*"),
    (1098, 66, "secondary_position", "Vec3*"),
    (1412, 67, "primary_terminal_delta", "Vec3*"),
    (1500, 67, "secondary_terminal_delta", "Vec3*"),
    (1663, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (1725, 66, "vertex", "Vec3*"),
    (2071, 69, "face_first", "ObjectFaceQuad*"),
    (2249, 69, "face_second", "ObjectFaceQuad*"),
)

TURNOVER_FAMILY_PATH_USER_VAR_UPDATES = tuple(
    (
        function_name,
        "RegisterVariableSourceType",
        index,
        storage,
        variable_name,
        variable_type,
    )
    for function_name, specs in (
        ("initialize_turnover_path_template_pair", TURNOVER_PATH_LIFETIME_SPECS),
        (
            "initialize_turnoverdouble_path_template_pair",
            TURNOVERDOUBLE_PATH_LIFETIME_SPECS,
        ),
        ("initialize_turnunder_path_template_pair", TURNUNDER_PATH_LIFETIME_SPECS),
    )
    for index, storage, variable_name, variable_type in specs
)

# The exact Android and iOS BuildTurnover, BuildTurnoverDouble, and
# BuildTurnunder bodies independently preserve the portable six-sample lead,
# two-sample tail, curved middle, orientation, and final-delta control graph.
# Windows remains authoritative for each definition identity, the native
# 0xa8-byte sample cursors, and the strip-mesh tail.
TURNOVER_FAMILY_CONTROL_USER_VAR_UPDATES = (
    (
        "initialize_turnover_path_template_pair",
        "StackVariableSourceType",
        82,
        -80,
        "curve_count_f",
        "float",
    ),
    (
        "initialize_turnover_path_template_pair",
        "StackVariableSourceType",
        622,
        -76,
        "angle",
        "float",
    ),
    (
        "initialize_turnoverdouble_path_template_pair",
        "StackVariableSourceType",
        82,
        -72,
        "curve_count_f",
        "float",
    ),
    (
        "initialize_turnoverdouble_path_template_pair",
        "StackVariableSourceType",
        611,
        -64,
        "curve_phase",
        "float",
    ),
    (
        "initialize_turnoverdouble_path_template_pair",
        "StackVariableSourceType",
        625,
        -80,
        "roll_angle",
        "float",
    ),
    (
        "initialize_turnunder_path_template_pair",
        "StackVariableSourceType",
        82,
        -80,
        "curve_count_f",
        "float",
    ),
    (
        "initialize_turnunder_path_template_pair",
        "StackVariableSourceType",
        634,
        -76,
        "angle",
        "float",
    ),
)

TURNOVER_CONTROL_LIFETIME_SPLITS = (
    (
        (
            ("0x426cda", "mlil", "RegisterVariableSourceType", 42, 66),
            ("0x426cdf", "mlil", "StackVariableSourceType", 47, -84),
        ),
        ("RegisterVariableSourceType", 42, 66),
        "curve_count",
        "int32_t",
    ),
    (
        (
            ("0x426ce3", "mlil", "RegisterVariableSourceType", 51, 66),
            ("0x426ce6", "mlil", "StackVariableSourceType", 54, 4),
        ),
        ("RegisterVariableSourceType", 51, 66),
        "total_segment_count",
        "int32_t",
    ),
    (
        (("0x426d0c", "mlil", "StackVariableSourceType", 92, 4),),
        ("StackVariableSourceType", 92, 4),
        "curve_radius",
        "float",
    ),
    (
        (
            ("0x426d1b", "mlil", "StackVariableSourceType", 107, 8),
            ("0x426de3", "mlil", "StackVariableSourceType", 307, 8),
            ("0x426d21", "mlil_ssa", "StackVariableSourceType", 113, 8),
        ),
        ("StackVariableSourceType", 107, 8),
        "lead_sample_index",
        "int32_t",
    ),
    (
        (
            ("0x426d1f", "mlil", "RegisterVariableSourceType", 111, 73),
            ("0x426dd2", "mlil", "RegisterVariableSourceType", 290, 73),
            (
                "0x426d21",
                "mlil_ssa",
                "RegisterVariableSourceType",
                113,
                73,
            ),
        ),
        ("RegisterVariableSourceType", 111, 73),
        "lead_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x426df4", "mlil", "StackVariableSourceType", 324, 8),
            ("0x426edd", "mlil", "StackVariableSourceType", 557, 8),
            ("0x426e16", "mlil_ssa", "StackVariableSourceType", 358, 8),
        ),
        ("StackVariableSourceType", 324, 8),
        "tail_sample_index",
        "int32_t",
    ),
    (
        (
            ("0x426e09", "mlil", "RegisterVariableSourceType", 345, 73),
            ("0x426ed4", "mlil", "RegisterVariableSourceType", 548, 73),
            (
                "0x426e16",
                "mlil_ssa",
                "RegisterVariableSourceType",
                358,
                73,
            ),
        ),
        ("RegisterVariableSourceType", 345, 73),
        "tail_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x426eee", "mlil", "StackVariableSourceType", 574, 8),
            ("0x4270f1", "mlil", "StackVariableSourceType", 1089, 8),
            ("0x426f07", "mlil_ssa", "StackVariableSourceType", 599, 8),
        ),
        ("StackVariableSourceType", 574, 8),
        "curve_index",
        "int32_t",
    ),
    (
        (
            ("0x426f02", "mlil", "RegisterVariableSourceType", 594, 69),
            ("0x4270c8", "mlil", "RegisterVariableSourceType", 1048, 69),
            (
                "0x426f07",
                "mlil_ssa",
                "RegisterVariableSourceType",
                599,
                69,
            ),
        ),
        ("RegisterVariableSourceType", 594, 69),
        "curve_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x4270fb", "mlil", "RegisterVariableSourceType", 1099, 69),
            ("0x4271ba", "mlil", "RegisterVariableSourceType", 1290, 69),
            (
                "0x42710b",
                "mlil_ssa",
                "RegisterVariableSourceType",
                1115,
                69,
            ),
        ),
        ("RegisterVariableSourceType", 1099, 69),
        "delta_index",
        "int32_t",
    ),
    (
        (
            ("0x427109", "mlil", "RegisterVariableSourceType", 1113, 73),
            ("0x4271c5", "mlil", "RegisterVariableSourceType", 1301, 73),
            (
                "0x42710b",
                "mlil_ssa",
                "RegisterVariableSourceType",
                1115,
                73,
            ),
        ),
        ("RegisterVariableSourceType", 1113, 73),
        "delta_sample_offset",
        "int32_t",
    ),
)

TURNOVERDOUBLE_CONTROL_LIFETIME_SPLITS = (
    (
        (
            ("0x42766a", "mlil", "RegisterVariableSourceType", 42, 66),
            ("0x42766f", "mlil", "StackVariableSourceType", 47, -76),
        ),
        ("RegisterVariableSourceType", 42, 66),
        "curve_count",
        "int32_t",
    ),
    (
        (
            ("0x427673", "mlil", "RegisterVariableSourceType", 51, 66),
            ("0x427676", "mlil", "StackVariableSourceType", 54, 4),
        ),
        ("RegisterVariableSourceType", 51, 66),
        "total_segment_count",
        "int32_t",
    ),
    (
        (("0x42769c", "mlil", "StackVariableSourceType", 92, 4),),
        ("StackVariableSourceType", 92, 4),
        "curve_radius",
        "float",
    ),
    (
        (
            ("0x4276ab", "mlil", "StackVariableSourceType", 107, 8),
            ("0x427773", "mlil", "StackVariableSourceType", 307, 8),
            ("0x4276b1", "mlil_ssa", "StackVariableSourceType", 113, 8),
        ),
        ("StackVariableSourceType", 107, 8),
        "lead_sample_index",
        "int32_t",
    ),
    (
        (
            ("0x4276af", "mlil", "RegisterVariableSourceType", 111, 73),
            ("0x427762", "mlil", "RegisterVariableSourceType", 290, 73),
            (
                "0x4276b1",
                "mlil_ssa",
                "RegisterVariableSourceType",
                113,
                73,
            ),
        ),
        ("RegisterVariableSourceType", 111, 73),
        "lead_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x427784", "mlil", "StackVariableSourceType", 324, 8),
            ("0x427869", "mlil", "StackVariableSourceType", 553, 8),
            ("0x4277a2", "mlil_ssa", "StackVariableSourceType", 354, 8),
        ),
        ("StackVariableSourceType", 324, 8),
        "tail_sample_index",
        "int32_t",
    ),
    (
        (
            ("0x427799", "mlil", "RegisterVariableSourceType", 345, 73),
            ("0x427860", "mlil", "RegisterVariableSourceType", 544, 73),
            (
                "0x4277a2",
                "mlil_ssa",
                "RegisterVariableSourceType",
                354,
                73,
            ),
        ),
        ("RegisterVariableSourceType", 345, 73),
        "tail_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x42787a", "mlil", "StackVariableSourceType", 570, 8),
            ("0x427aa0", "mlil", "StackVariableSourceType", 1120, 8),
            ("0x427893", "mlil_ssa", "StackVariableSourceType", 595, 8),
        ),
        ("StackVariableSourceType", 570, 8),
        "curve_index",
        "int32_t",
    ),
    (
        (
            ("0x42788e", "mlil", "RegisterVariableSourceType", 590, 69),
            ("0x427a77", "mlil", "RegisterVariableSourceType", 1079, 69),
            (
                "0x427893",
                "mlil_ssa",
                "RegisterVariableSourceType",
                595,
                69,
            ),
        ),
        ("RegisterVariableSourceType", 590, 69),
        "curve_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x427aaa", "mlil", "RegisterVariableSourceType", 1130, 69),
            ("0x427b69", "mlil", "RegisterVariableSourceType", 1321, 69),
            (
                "0x427aba",
                "mlil_ssa",
                "RegisterVariableSourceType",
                1146,
                69,
            ),
        ),
        ("RegisterVariableSourceType", 1130, 69),
        "delta_index",
        "int32_t",
    ),
    (
        (
            ("0x427ab8", "mlil", "RegisterVariableSourceType", 1144, 73),
            ("0x427b74", "mlil", "RegisterVariableSourceType", 1332, 73),
            (
                "0x427aba",
                "mlil_ssa",
                "RegisterVariableSourceType",
                1146,
                73,
            ),
        ),
        ("RegisterVariableSourceType", 1144, 73),
        "delta_sample_offset",
        "int32_t",
    ),
)

TURNUNDER_CONTROL_LIFETIME_SPLITS = (
    (
        (
            ("0x42800a", "mlil", "RegisterVariableSourceType", 42, 66),
            ("0x42800f", "mlil", "StackVariableSourceType", 47, -84),
        ),
        ("RegisterVariableSourceType", 42, 66),
        "curve_count",
        "int32_t",
    ),
    (
        (
            ("0x428013", "mlil", "RegisterVariableSourceType", 51, 66),
            ("0x428016", "mlil", "StackVariableSourceType", 54, 4),
        ),
        ("RegisterVariableSourceType", 51, 66),
        "total_segment_count",
        "int32_t",
    ),
    (
        (("0x42803c", "mlil", "StackVariableSourceType", 92, 4),),
        ("StackVariableSourceType", 92, 4),
        "curve_radius",
        "float",
    ),
    (
        (
            ("0x42804b", "mlil", "StackVariableSourceType", 107, 8),
            ("0x428119", "mlil", "StackVariableSourceType", 313, 8),
            ("0x428051", "mlil_ssa", "StackVariableSourceType", 113, 8),
        ),
        ("StackVariableSourceType", 107, 8),
        "lead_sample_index",
        "int32_t",
    ),
    (
        (
            ("0x42804f", "mlil", "RegisterVariableSourceType", 111, 73),
            ("0x428108", "mlil", "RegisterVariableSourceType", 296, 73),
            (
                "0x428051",
                "mlil_ssa",
                "RegisterVariableSourceType",
                113,
                73,
            ),
        ),
        ("RegisterVariableSourceType", 111, 73),
        "lead_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x42812a", "mlil", "StackVariableSourceType", 330, 8),
            ("0x428219", "mlil", "StackVariableSourceType", 569, 8),
            ("0x42814c", "mlil_ssa", "StackVariableSourceType", 364, 8),
        ),
        ("StackVariableSourceType", 330, 8),
        "tail_sample_index",
        "int32_t",
    ),
    (
        (
            ("0x42813f", "mlil", "RegisterVariableSourceType", 351, 73),
            ("0x428210", "mlil", "RegisterVariableSourceType", 560, 73),
            (
                "0x42814c",
                "mlil_ssa",
                "RegisterVariableSourceType",
                364,
                73,
            ),
        ),
        ("RegisterVariableSourceType", 351, 73),
        "tail_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x42822a", "mlil", "StackVariableSourceType", 586, 8),
            ("0x428457", "mlil", "StackVariableSourceType", 1143, 8),
            ("0x428243", "mlil_ssa", "StackVariableSourceType", 611, 8),
        ),
        ("StackVariableSourceType", 586, 8),
        "curve_index",
        "int32_t",
    ),
    (
        (
            ("0x42823e", "mlil", "RegisterVariableSourceType", 606, 69),
            ("0x42842e", "mlil", "RegisterVariableSourceType", 1102, 69),
            (
                "0x428243",
                "mlil_ssa",
                "RegisterVariableSourceType",
                611,
                69,
            ),
        ),
        ("RegisterVariableSourceType", 606, 69),
        "curve_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x428461", "mlil", "RegisterVariableSourceType", 1153, 69),
            ("0x428520", "mlil", "RegisterVariableSourceType", 1344, 69),
            (
                "0x428471",
                "mlil_ssa",
                "RegisterVariableSourceType",
                1169,
                69,
            ),
        ),
        ("RegisterVariableSourceType", 1153, 69),
        "delta_index",
        "int32_t",
    ),
    (
        (
            ("0x42846f", "mlil", "RegisterVariableSourceType", 1167, 73),
            ("0x42852b", "mlil", "RegisterVariableSourceType", 1355, 73),
            (
                "0x428471",
                "mlil_ssa",
                "RegisterVariableSourceType",
                1169,
                73,
            ),
        ),
        ("RegisterVariableSourceType", 1167, 73),
        "delta_sample_offset",
        "int32_t",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the control, sample, vector, mesh-vertex, and facequad "
            "lifetimes in the turnover path-constructor family."
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
            "canonical turnover-family ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_turnover_family_path_owner_layouts",
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
                TURNOVER_FAMILY_PATH_USER_VAR_UPDATES
                + TURNOVER_FAMILY_CONTROL_USER_VAR_UPDATES
            ),
        ),
        *apply_split_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=tuple(
                (
                    function_name,
                    definitions,
                    target_var,
                    variable_name,
                    variable_type,
                )
                for function_name, specs in (
                    (
                        "initialize_turnover_path_template_pair",
                        TURNOVER_CONTROL_LIFETIME_SPLITS,
                    ),
                    (
                        "initialize_turnoverdouble_path_template_pair",
                        TURNOVERDOUBLE_CONTROL_LIFETIME_SPLITS,
                    ),
                    (
                        "initialize_turnunder_path_template_pair",
                        TURNUNDER_CONTROL_LIFETIME_SPLITS,
                    ),
                )
                for (
                    definitions,
                    target_var,
                    variable_name,
                    variable_type,
                ) in specs
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
