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

# BuildLoopBow constructs two transform bases in stages, offsets the secondary
# position along the primary up vector, derives the per-sample deltas, and then
# emits separate ordinary and terminal mesh rows. Preserve each complete owner
# whose transactional preview remained at zero __offset expressions. The
# terminal-row current-sample view at 2180 is intentionally omitted: that
# lifetime reads the previous 0xa8-byte sample through negative displacements,
# and forcing PathTemplateSample* introduced six synthetic backward offsets.
LOOPBOW_PATH_LIFETIME_SPECS = (
    (1091, 66, "primary_right", "Vec3*"),
    (1122, 66, "primary_sample_cursor_first", "PathTemplateSample*"),
    (1143, 66, "primary_sample_cursor_second", "PathTemplateSample*"),
    (1164, 66, "primary_sample", "PathTemplateSample*"),
    (1194, 68, "secondary_right", "Vec3*"),
    (1229, 66, "secondary_sample_cursor_first", "PathTemplateSample*"),
    (1248, 66, "secondary_sample_cursor_second", "PathTemplateSample*"),
    (1270, 66, "secondary_sample", "PathTemplateSample*"),
    (1490, 66, "primary_up", "Vec3*"),
    (1516, 66, "secondary_position", "Vec3*"),
    (1658, 67, "primary_delta_dir", "Vec3*"),
    (1749, 67, "secondary_delta_dir", "Vec3*"),
    (1832, 68, "primary_terminal_delta", "Vec3*"),
    (1921, 67, "secondary_terminal_delta", "Vec3*"),
    (2086, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (2152, 67, "vertex", "Vec3*"),
    (2278, 67, "terminal_vertex", "Vec3*"),
    (2514, 69, "face_first", "ObjectFaceQuad*"),
    (2698, 69, "face_second", "ObjectFaceQuad*"),
)

LOOPBOW_PATH_USER_VAR_UPDATES = tuple(
    (
        "initialize_loopbow_path_template_pair",
        "RegisterVariableSourceType",
        index,
        storage,
        variable_name,
        variable_type,
    )
    for index, storage, variable_name, variable_type in LOOPBOW_PATH_LIFETIME_SPECS
)

# The paired Android and iOS BuildLoopBow bodies independently preserve the
# portable lead, tail, arc, and delta-loop ownership graph and end at
# CalcLengthZ. Windows remains authoritative for every exact MLIL identity
# below: VC6 coalesces the logical counters and byte cursors through registers,
# stack slots, and the dead incoming curve-scale home.
LOOPBOW_CONTROL_USER_VAR_UPDATES = (
    (
        "initialize_loopbow_path_template_pair",
        "StackVariableSourceType",
        27,
        -128,
        "center_offset",
        "float",
    ),
    (
        "initialize_loopbow_path_template_pair",
        "StackVariableSourceType",
        107,
        -148,
        "curve_segment_count_f",
        "float",
    ),
    (
        "initialize_loopbow_path_template_pair",
        "StackVariableSourceType",
        149,
        -144,
        "lead_sample_z",
        "float",
    ),
    (
        "initialize_loopbow_path_template_pair",
        "StackVariableSourceType",
        540,
        -120,
        "tail_sample_z",
        "float",
    ),
    (
        "initialize_loopbow_path_template_pair",
        "StackVariableSourceType",
        726,
        -144,
        "secondary_radius",
        "float",
    ),
    (
        "initialize_loopbow_path_template_pair",
        "StackVariableSourceType",
        744,
        -120,
        "terminal_sample_offset",
        "int32_t",
    ),
    (
        "initialize_loopbow_path_template_pair",
        "StackVariableSourceType",
        781,
        -116,
        "angle",
        "float",
    ),
    (
        "initialize_loopbow_path_template_pair",
        "StackVariableSourceType",
        836,
        -152,
        "half_angle",
        "float",
    ),
    (
        "initialize_loopbow_path_template_pair",
        "StackVariableSourceType",
        1305,
        -152,
        "half_sine",
        "float",
    ),
)

LOOPBOW_CONTROL_LIFETIME_SPLITS = (
    (
        (
            ("0x42bac3", "mlil", "RegisterVariableSourceType", 67, 66),
            ("0x42bac8", "mlil", "StackVariableSourceType", 72, -124),
        ),
        ("RegisterVariableSourceType", 67, 66),
        "curve_segment_count",
        "int32_t",
    ),
    (
        (
            ("0x42bacc", "mlil", "RegisterVariableSourceType", 76, 66),
            ("0x42bacf", "mlil", "StackVariableSourceType", 79, -116),
        ),
        ("RegisterVariableSourceType", 76, 66),
        "total_segment_count",
        "int32_t",
    ),
    (
        (("0x42baf5", "mlil", "StackVariableSourceType", 117, 4),),
        ("StackVariableSourceType", 117, 4),
        "curve_radius",
        "float",
    ),
    (
        (
            ("0x42bb08", "mlil", "StackVariableSourceType", 136, -156),
            ("0x42bbea", "mlil", "StackVariableSourceType", 362, -156),
            ("0x42bb0e", "mlil_ssa", "StackVariableSourceType", 142, -156),
        ),
        ("StackVariableSourceType", 136, -156),
        "lead_sample_index",
        "int32_t",
    ),
    (
        (
            ("0x42bb0c", "mlil", "RegisterVariableSourceType", 140, 73),
            ("0x42bbd9", "mlil", "RegisterVariableSourceType", 345, 73),
            ("0x42bb0e", "mlil_ssa", "RegisterVariableSourceType", 142, 73),
        ),
        ("RegisterVariableSourceType", 140, 73),
        "lead_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x42bbf8", "mlil", "RegisterVariableSourceType", 376, 69),
            ("0x42bbfa", "mlil", "StackVariableSourceType", 378, -156),
            ("0x42bccf", "mlil", "RegisterVariableSourceType", 591, 69),
            ("0x42bcd7", "mlil", "StackVariableSourceType", 599, -156),
            ("0x42bc10", "mlil_ssa", "RegisterVariableSourceType", 400, 69),
            ("0x42bc10", "mlil_ssa", "StackVariableSourceType", 400, -156),
        ),
        ("RegisterVariableSourceType", 376, 69),
        "tail_index",
        "int32_t",
    ),
    (
        (
            ("0x42bc0d", "mlil", "RegisterVariableSourceType", 397, 73),
            ("0x42bced", "mlil", "RegisterVariableSourceType", 621, 73),
            ("0x42bc10", "mlil_ssa", "RegisterVariableSourceType", 400, 73),
        ),
        ("RegisterVariableSourceType", 397, 73),
        "tail_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x42bd08", "mlil", "StackVariableSourceType", 648, -156),
            ("0x42c099", "mlil", "StackVariableSourceType", 1561, -156),
            ("0x42bd79", "mlil_ssa", "StackVariableSourceType", 761, -156),
        ),
        ("StackVariableSourceType", 648, -156),
        "curve_index",
        "int32_t",
    ),
    (
        (
            ("0x42bd6c", "mlil", "RegisterVariableSourceType", 748, 69),
            ("0x42c070", "mlil", "RegisterVariableSourceType", 1520, 69),
            ("0x42bd79", "mlil_ssa", "RegisterVariableSourceType", 761, 69),
        ),
        ("RegisterVariableSourceType", 748, 69),
        "curve_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x42c0a8", "mlil", "RegisterVariableSourceType", 1576, 69),
            ("0x42c164", "mlil", "RegisterVariableSourceType", 1764, 69),
            ("0x42c0b5", "mlil_ssa", "RegisterVariableSourceType", 1589, 69),
        ),
        ("RegisterVariableSourceType", 1576, 69),
        "delta_index",
        "int32_t",
    ),
    (
        (
            ("0x42c0b3", "mlil", "RegisterVariableSourceType", 1587, 73),
            ("0x42c16f", "mlil", "RegisterVariableSourceType", 1775, 73),
            ("0x42c0b5", "mlil_ssa", "RegisterVariableSourceType", 1589, 73),
        ),
        ("RegisterVariableSourceType", 1587, 73),
        "delta_sample_offset",
        "int32_t",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the proved control, basis, offset, delta, mesh, vertex, "
            "and face lifetimes in the LoopBow path constructor."
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
            "canonical LoopBow ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_loopbow_path_owner_layouts",
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
                LOOPBOW_PATH_USER_VAR_UPDATES + LOOPBOW_CONTROL_USER_VAR_UPDATES
            ),
        ),
        *apply_split_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=tuple(
                (
                    "initialize_loopbow_path_template_pair",
                    definitions,
                    target_var,
                    variable_name,
                    variable_type,
                )
                for definitions, target_var, variable_name, variable_type in (
                    LOOPBOW_CONTROL_LIFETIME_SPLITS
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
