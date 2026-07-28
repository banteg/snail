#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

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

# BuildSweepA and BuildSnakeA share the same ownership stages, but their
# different curve/orientation bodies produce distinct MLIL identities. Keep
# the schedules separate and replay only temporaries whose transactional
# previews resolved to direct Vec3, PathTemplateSample, or ObjectFaceQuad
# fields. The initial current-sample and previous-row cursors are deliberately
# omitted because their negative byte-relative addressing became less exact
# when typed.
SWEEP_PATH_LIFETIME_SPECS = (
    (726, 67, "primary_forward", "Vec3*"),
    (841, 66, "primary_sample_cursor_reloaded", "PathTemplateSample*"),
    (893, 67, "secondary_forward", "Vec3*"),
    (1008, 66, "secondary_sample_cursor_reloaded", "PathTemplateSample*"),
    (1352, 68, "primary_terminal_delta", "Vec3*"),
    (1441, 67, "secondary_terminal_delta", "Vec3*"),
    (1600, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (2010, 71, "face_first", "ObjectFaceQuad*"),
    (2189, 71, "face_second", "ObjectFaceQuad*"),
)

SNAKE_PATH_LIFETIME_SPECS = (
    (727, 68, "primary_right", "Vec3*"),
    (847, 66, "primary_sample_cursor_reloaded", "PathTemplateSample*"),
    (898, 66, "secondary_right", "Vec3*"),
    (1016, 66, "secondary_sample_cursor_reloaded", "PathTemplateSample*"),
    (1360, 68, "primary_terminal_delta", "Vec3*"),
    (1449, 67, "secondary_terminal_delta", "Vec3*"),
    (1608, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (2018, 71, "face_first", "ObjectFaceQuad*"),
    (2197, 71, "face_second", "ObjectFaceQuad*"),
)

SWEEP_SNAKE_PATH_USER_VAR_UPDATES = tuple(
    (
        function_name,
        "RegisterVariableSourceType",
        index,
        storage,
        variable_name,
        variable_type,
    )
    for function_name, specs in (
        ("initialize_sweep_path_template_pair", SWEEP_PATH_LIFETIME_SPECS),
        ("initialize_snake_path_template_pair", SNAKE_PATH_LIFETIME_SPECS),
    )
    for index, storage, variable_name, variable_type in specs
)

# The exact Android and iOS BuildSweep and BuildSnake bodies independently
# preserve their lead/tail loops and logical curve induction. These two stack
# values already have bounded automatic lifetimes; naming them does not
# transfer mobile addresses into the Windows analysis.
SWEEP_SNAKE_CONTROL_USER_VAR_UPDATES = (
    (
        "initialize_sweep_path_template_pair",
        "StackVariableSourceType",
        167,
        -64,
        "lead_sample_z",
        "float",
    ),
    (
        "initialize_sweep_path_template_pair",
        "StackVariableSourceType",
        483,
        -72,
        "curve_phase",
        "float",
    ),
    (
        "initialize_snake_path_template_pair",
        "StackVariableSourceType",
        145,
        -64,
        "lead_sample_z",
        "float",
    ),
    (
        "initialize_snake_path_template_pair",
        "StackVariableSourceType",
        452,
        -72,
        "curve_phase",
        "float",
    ),
)

# Mobile proves the logical control graph; each split below is anchored to an
# exact Windows MLIL definition. Sweep and Snake have different lead-loop
# lengths and orientation bodies, so their identities remain explicit.
SWEEP_CONTROL_STACK_LIFETIME_SPLITS = (
    (
        (
            ("0x422c41", "mlil", "StackVariableSourceType", 65, 8),
            ("0x422cf8", "mlil", "StackVariableSourceType", 248, 8),
            ("0x422c47", "mlil_ssa", "StackVariableSourceType", 71, 8),
        ),
        ("StackVariableSourceType", 65, 8),
        "lead_sample_index",
        "int32_t",
    ),
    (
        (
            ("0x422d0c", "mlil", "StackVariableSourceType", 268, 8),
            ("0x422dbd", "mlil", "StackVariableSourceType", 445, 8),
            ("0x422d10", "mlil_ssa", "StackVariableSourceType", 272, 8),
        ),
        ("StackVariableSourceType", 268, 8),
        "tail_sample_index",
        "int32_t",
    ),
    (
        (("0x422d70", "mlil", "StackVariableSourceType", 368, 8),),
        ("StackVariableSourceType", 368, 8),
        "tail_sample_z",
        "float",
    ),
    (
        (
            ("0x422dcd", "mlil", "StackVariableSourceType", 461, 8),
            ("0x42303e", "mlil", "StackVariableSourceType", 1086, 8),
            ("0x422dd6", "mlil_ssa", "StackVariableSourceType", 470, 8),
        ),
        ("StackVariableSourceType", 461, 8),
        "curve_index",
        "int32_t",
    ),
    (
        (("0x422e62", "mlil", "StackVariableSourceType", 610, -64),),
        ("StackVariableSourceType", 610, -64),
        "curve_sample_index",
        "int32_t",
    ),
    (
        (("0x422e73", "mlil", "StackVariableSourceType", 627, -64),),
        ("StackVariableSourceType", 627, -64),
        "curve_sample_z",
        "float",
    ),
)

SNAKE_CONTROL_STACK_LIFETIME_SPLITS = (
    (
        (
            ("0x4235c1", "mlil", "StackVariableSourceType", 65, 8),
            ("0x423658", "mlil", "StackVariableSourceType", 216, 8),
            ("0x4235c7", "mlil_ssa", "StackVariableSourceType", 71, 8),
        ),
        ("StackVariableSourceType", 65, 8),
        "lead_sample_index",
        "int32_t",
    ),
    (
        (
            ("0x42366c", "mlil", "StackVariableSourceType", 236, 8),
            ("0x42371d", "mlil", "StackVariableSourceType", 413, 8),
            ("0x423670", "mlil_ssa", "StackVariableSourceType", 240, 8),
        ),
        ("StackVariableSourceType", 236, 8),
        "tail_sample_index",
        "int32_t",
    ),
    (
        (("0x4236d0", "mlil", "StackVariableSourceType", 336, 8),),
        ("StackVariableSourceType", 336, 8),
        "tail_sample_z",
        "float",
    ),
    (
        (
            ("0x42372d", "mlil", "StackVariableSourceType", 429, 8),
            ("0x4239c6", "mlil", "StackVariableSourceType", 1094, 8),
            ("0x423736", "mlil_ssa", "StackVariableSourceType", 438, 8),
        ),
        ("StackVariableSourceType", 429, 8),
        "curve_index",
        "int32_t",
    ),
    (
        (("0x4237e2", "mlil", "StackVariableSourceType", 610, -64),),
        ("StackVariableSourceType", 610, -64),
        "curve_sample_index",
        "int32_t",
    ),
    (
        (("0x4237ea", "mlil", "StackVariableSourceType", 618, -64),),
        ("StackVariableSourceType", 618, -64),
        "curve_sample_z",
        "float",
    ),
)

# Both mobile bodies stop after CalcLengthZ. The generated strip mesh, UVs,
# winding pass, and repeated width reloads are Windows-only evidence.
SWEEP_MESH_STACK_LIFETIME_SPLITS = (
    (
        (("0x423201", "mlil", "StackVariableSourceType", 1537, -64),),
        ("StackVariableSourceType", 1537, -64),
        "mesh_vertices",
        "Vec3*",
    ),
    (
        (("0x423207", "mlil", "StackVariableSourceType", 1543, -68),),
        ("StackVariableSourceType", 1543, -68),
        "mesh_facequads",
        "ObjectFaceQuad*",
    ),
    (
        (
            ("0x423218", "mlil", "StackVariableSourceType", 1560, 8),
            ("0x42331d", "mlil", "StackVariableSourceType", 1821, 8),
            ("0x423226", "mlil_ssa", "StackVariableSourceType", 1574, 8),
        ),
        ("StackVariableSourceType", 1560, 8),
        "mesh_column",
        "int32_t",
    ),
    (
        (
            ("0x42321c", "mlil", "StackVariableSourceType", 1564, -76),
            ("0x423317", "mlil", "StackVariableSourceType", 1815, -76),
            ("0x423226", "mlil_ssa", "StackVariableSourceType", 1574, -76),
        ),
        ("StackVariableSourceType", 1564, -76),
        "mesh_width_cells",
        "int32_t",
    ),
    (
        (
            ("0x42334d", "mlil", "StackVariableSourceType", 1869, 8),
            ("0x423548", "mlil", "StackVariableSourceType", 2376, 8),
            ("0x42338a", "mlil_ssa", "StackVariableSourceType", 1930, 8),
        ),
        ("StackVariableSourceType", 1869, 8),
        "face_column_for_uv",
        "int32_t",
    ),
    (
        (("0x423365", "mlil", "StackVariableSourceType", 1893, -64),),
        ("StackVariableSourceType", 1893, -64),
        "v0_index",
        "int32_t",
    ),
    (
        (("0x42336e", "mlil", "StackVariableSourceType", 1902, -64),),
        ("StackVariableSourceType", 1902, -64),
        "v1_index",
        "int32_t",
    ),
    (
        (("0x423378", "mlil", "StackVariableSourceType", 1912, -84),),
        ("StackVariableSourceType", 1912, -84),
        "v0",
        "float",
    ),
    (
        (("0x423386", "mlil", "StackVariableSourceType", 1926, -76),),
        ("StackVariableSourceType", 1926, -76),
        "v1",
        "float",
    ),
    (
        (("0x423393", "mlil", "StackVariableSourceType", 1939, -64),),
        ("StackVariableSourceType", 1939, -64),
        "u1_index",
        "int32_t",
    ),
    (
        (
            ("0x423397", "mlil", "StackVariableSourceType", 1943, -72),
            ("0x423535", "mlil", "StackVariableSourceType", 2357, -72),
            ("0x4233b9", "mlil_ssa", "StackVariableSourceType", 1977, -72),
        ),
        ("StackVariableSourceType", 1943, -72),
        "face_pass",
        "int32_t",
    ),
    (
        (("0x4233a1", "mlil", "StackVariableSourceType", 1953, 8),),
        ("StackVariableSourceType", 1953, 8),
        "u0",
        "float",
    ),
    (
        (("0x4233af", "mlil", "StackVariableSourceType", 1967, -80),),
        ("StackVariableSourceType", 1967, -80),
        "u1",
        "float",
    ),
)

SNAKE_MESH_STACK_LIFETIME_SPLITS = (
    (
        (("0x423b89", "mlil", "StackVariableSourceType", 1545, -64),),
        ("StackVariableSourceType", 1545, -64),
        "mesh_vertices",
        "Vec3*",
    ),
    (
        (("0x423b8f", "mlil", "StackVariableSourceType", 1551, -68),),
        ("StackVariableSourceType", 1551, -68),
        "mesh_facequads",
        "ObjectFaceQuad*",
    ),
    (
        (
            ("0x423ba0", "mlil", "StackVariableSourceType", 1568, 8),
            ("0x423ca5", "mlil", "StackVariableSourceType", 1829, 8),
            ("0x423bae", "mlil_ssa", "StackVariableSourceType", 1582, 8),
        ),
        ("StackVariableSourceType", 1568, 8),
        "mesh_column",
        "int32_t",
    ),
    (
        (
            ("0x423ba4", "mlil", "StackVariableSourceType", 1572, -76),
            ("0x423c9f", "mlil", "StackVariableSourceType", 1823, -76),
            ("0x423bae", "mlil_ssa", "StackVariableSourceType", 1582, -76),
        ),
        ("StackVariableSourceType", 1572, -76),
        "mesh_width_cells",
        "int32_t",
    ),
    (
        (
            ("0x423cd5", "mlil", "StackVariableSourceType", 1877, 8),
            ("0x423ed0", "mlil", "StackVariableSourceType", 2384, 8),
            ("0x423d12", "mlil_ssa", "StackVariableSourceType", 1938, 8),
        ),
        ("StackVariableSourceType", 1877, 8),
        "face_column_for_uv",
        "int32_t",
    ),
    (
        (("0x423ced", "mlil", "StackVariableSourceType", 1901, -64),),
        ("StackVariableSourceType", 1901, -64),
        "v0_index",
        "int32_t",
    ),
    (
        (("0x423cf6", "mlil", "StackVariableSourceType", 1910, -64),),
        ("StackVariableSourceType", 1910, -64),
        "v1_index",
        "int32_t",
    ),
    (
        (("0x423d00", "mlil", "StackVariableSourceType", 1920, -84),),
        ("StackVariableSourceType", 1920, -84),
        "v0",
        "float",
    ),
    (
        (("0x423d0e", "mlil", "StackVariableSourceType", 1934, -76),),
        ("StackVariableSourceType", 1934, -76),
        "v1",
        "float",
    ),
    (
        (("0x423d1b", "mlil", "StackVariableSourceType", 1947, -64),),
        ("StackVariableSourceType", 1947, -64),
        "u1_index",
        "int32_t",
    ),
    (
        (
            ("0x423d1f", "mlil", "StackVariableSourceType", 1951, -72),
            ("0x423ebd", "mlil", "StackVariableSourceType", 2365, -72),
            ("0x423d41", "mlil_ssa", "StackVariableSourceType", 1985, -72),
        ),
        ("StackVariableSourceType", 1951, -72),
        "face_pass",
        "int32_t",
    ),
    (
        (("0x423d29", "mlil", "StackVariableSourceType", 1961, 8),),
        ("StackVariableSourceType", 1961, 8),
        "u0",
        "float",
    ),
    (
        (("0x423d37", "mlil", "StackVariableSourceType", 1975, -80),),
        ("StackVariableSourceType", 1975, -80),
        "u1",
        "float",
    ),
)

# The two face records repeatedly reload width + 1 through EAX, ECX, and EDX.
# Preserve those physical lifetimes separately from the face pointers, row
# cursor, and stack-owned winding pass.
SWEEP_FACE_REGISTER_LIFETIME_SPLITS = (
    (
        (
            ("0x4233e3", "mlil", "RegisterVariableSourceType", 2019, 66),
            ("0x4233e7", "mlil", "RegisterVariableSourceType", 2023, 66),
            ("0x4234a7", "mlil", "RegisterVariableSourceType", 2215, 66),
            ("0x4234ab", "mlil", "RegisterVariableSourceType", 2219, 66),
        ),
        ("RegisterVariableSourceType", 2019, 66),
        "face_width_plus_one_eax",
        "int32_t",
    ),
    (
        (
            ("0x4233f2", "mlil", "RegisterVariableSourceType", 2034, 67),
            ("0x4233f6", "mlil", "RegisterVariableSourceType", 2038, 67),
            ("0x423406", "mlil", "RegisterVariableSourceType", 2054, 67),
            ("0x42340a", "mlil", "RegisterVariableSourceType", 2058, 67),
            ("0x423417", "mlil", "RegisterVariableSourceType", 2071, 67),
            ("0x42341b", "mlil", "RegisterVariableSourceType", 2075, 67),
            ("0x423496", "mlil", "RegisterVariableSourceType", 2198, 67),
            ("0x42349a", "mlil", "RegisterVariableSourceType", 2202, 67),
            ("0x4234b6", "mlil", "RegisterVariableSourceType", 2230, 67),
            ("0x4234bd", "mlil", "RegisterVariableSourceType", 2237, 67),
        ),
        ("RegisterVariableSourceType", 2034, 67),
        "face_width_plus_one_ecx",
        "int32_t",
    ),
    (
        (
            ("0x4234c8", "mlil", "RegisterVariableSourceType", 2248, 68),
            ("0x4234cc", "mlil", "RegisterVariableSourceType", 2252, 68),
        ),
        ("RegisterVariableSourceType", 2248, 68),
        "face_width_plus_one_edx",
        "int32_t",
    ),
)

SNAKE_FACE_REGISTER_LIFETIME_SPLITS = (
    (
        (
            ("0x423d6b", "mlil", "RegisterVariableSourceType", 2027, 66),
            ("0x423d6f", "mlil", "RegisterVariableSourceType", 2031, 66),
            ("0x423e2f", "mlil", "RegisterVariableSourceType", 2223, 66),
            ("0x423e33", "mlil", "RegisterVariableSourceType", 2227, 66),
        ),
        ("RegisterVariableSourceType", 2027, 66),
        "face_width_plus_one_eax",
        "int32_t",
    ),
    (
        (
            ("0x423d7a", "mlil", "RegisterVariableSourceType", 2042, 67),
            ("0x423d7e", "mlil", "RegisterVariableSourceType", 2046, 67),
            ("0x423d8e", "mlil", "RegisterVariableSourceType", 2062, 67),
            ("0x423d92", "mlil", "RegisterVariableSourceType", 2066, 67),
            ("0x423d9f", "mlil", "RegisterVariableSourceType", 2079, 67),
            ("0x423da3", "mlil", "RegisterVariableSourceType", 2083, 67),
            ("0x423e1e", "mlil", "RegisterVariableSourceType", 2206, 67),
            ("0x423e22", "mlil", "RegisterVariableSourceType", 2210, 67),
            ("0x423e3e", "mlil", "RegisterVariableSourceType", 2238, 67),
            ("0x423e45", "mlil", "RegisterVariableSourceType", 2245, 67),
        ),
        ("RegisterVariableSourceType", 2042, 67),
        "face_width_plus_one_ecx",
        "int32_t",
    ),
    (
        (
            ("0x423e50", "mlil", "RegisterVariableSourceType", 2256, 68),
            ("0x423e54", "mlil", "RegisterVariableSourceType", 2260, 68),
        ),
        ("RegisterVariableSourceType", 2256, 68),
        "face_width_plus_one_edx",
        "int32_t",
    ),
)

SWEEP_SNAKE_SPLIT_LIFETIME_GROUPS = (
    (
        "initialize_sweep_path_template_pair",
        SWEEP_CONTROL_STACK_LIFETIME_SPLITS
        + SWEEP_MESH_STACK_LIFETIME_SPLITS
        + SWEEP_FACE_REGISTER_LIFETIME_SPLITS,
    ),
    (
        "initialize_snake_path_template_pair",
        SNAKE_CONTROL_STACK_LIFETIME_SPLITS
        + SNAKE_MESH_STACK_LIFETIME_SPLITS
        + SNAKE_FACE_REGISTER_LIFETIME_SPLITS,
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the basis-vector, terminal-delta, sample, and facequad "
            "lifetimes in the sweep and snake path constructors."
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
            "canonical sweep/snake ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_sweep_snake_path_owner_layouts",
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
                SWEEP_SNAKE_PATH_USER_VAR_UPDATES
                + SWEEP_SNAKE_CONTROL_USER_VAR_UPDATES
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
                for function_name, groups in SWEEP_SNAKE_SPLIT_LIFETIME_GROUPS
                for definitions, target_var, variable_name, variable_type in groups
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
