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
    },
    "ObjectFaceQuad": {
        0x02: ("vertex_0", "uint16_t"),
        0x08: ("vertex_3", "uint16_t"),
        0x0C: ("texture_ref", "TextureRef*"),
        0x10: ("uv", "ObjectUv[4]"),
    },
}

# BuildSlalomDoubleA and BuildP share the same post-curve ownership stages,
# but their curve bodies and mesh branches produce distinct MLIL identities.
# Transactional preview proved the preceding forward vectors, current-sample
# reloads, terminal deltas, mesh samples, and complete face records below.
# The alternative prior-row mesh cursors remain automatic because typing their
# negative byte-relative addressing made the decompiles less exact.
SLALOMDOUBLE_PATH_LIFETIME_SPECS = (
    (791, 67, "primary_forward", "Vec3*"),
    (906, 66, "primary_sample_cursor_reloaded", "PathTemplateSample*"),
    (987, 68, "secondary_forward", "Vec3*"),
    (1107, 66, "secondary_sample_cursor_reloaded", "PathTemplateSample*"),
    (1481, 67, "primary_terminal_delta", "Vec3*"),
    (1570, 66, "secondary_terminal_delta", "Vec3*"),
    (1729, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (2129, 73, "face", "ObjectFaceQuad*"),
)

P_PATH_LIFETIME_SPECS = (
    (784, 68, "primary_forward", "Vec3*"),
    (904, 66, "primary_sample_cursor_reloaded", "PathTemplateSample*"),
    (955, 66, "secondary_forward", "Vec3*"),
    (1073, 66, "secondary_sample_cursor_reloaded", "PathTemplateSample*"),
    (1412, 68, "primary_terminal_delta", "Vec3*"),
    (1501, 67, "secondary_terminal_delta", "Vec3*"),
    (1660, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (2070, 71, "face_first", "ObjectFaceQuad*"),
    (2249, 71, "face_second", "ObjectFaceQuad*"),
)

SLALOMDOUBLE_P_PATH_USER_VAR_UPDATES = tuple(
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
            "initialize_slalomdouble_path_template_pair",
            SLALOMDOUBLE_PATH_LIFETIME_SPECS,
        ),
        ("initialize_p_path_template_pair", P_PATH_LIFETIME_SPECS),
    )
    for index, storage, variable_name, variable_type in specs
)

# The exact Android and iOS BuildSlalomDouble bodies preserve the authored
# four-sample lead/tail loops and the 62-sample curve induction graph. Windows
# compiles those logical owners through repeatedly reused argument homes. These
# two stack values already have bounded automatic lifetimes and need only their
# independently observed scalar types.
SLALOMDOUBLE_CONTROL_USER_VAR_UPDATES = (
    (
        "initialize_slalomdouble_path_template_pair",
        "StackVariableSourceType",
        152,
        -68,
        "lead_sample_z",
        "float",
    ),
    (
        "initialize_slalomdouble_path_template_pair",
        "StackVariableSourceType",
        460,
        -76,
        "curve_phase",
        "float",
    ),
)

# Every split below is anchored to its exact Windows MLIL definition. The
# paired mobile bodies prove the logical lead, tail, curve, and folded-distance
# graph, but do not supply Windows addresses or variable identities.
SLALOMDOUBLE_CONTROL_STACK_LIFETIME_SPLITS = (
    (
        (
            ("0x425091", "mlil", "StackVariableSourceType", 65, 8),
            ("0x425139", "mlil", "StackVariableSourceType", 233, 8),
            ("0x425097", "mlil_ssa", "StackVariableSourceType", 71, 8),
        ),
        ("StackVariableSourceType", 65, 8),
        "lead_sample_index",
        "int32_t",
    ),
    (
        (
            ("0x42514d", "mlil", "StackVariableSourceType", 253, 8),
            ("0x4251ef", "mlil", "StackVariableSourceType", 415, 8),
            ("0x425151", "mlil_ssa", "StackVariableSourceType", 257, 8),
        ),
        ("StackVariableSourceType", 253, 8),
        "tail_sample_index",
        "int32_t",
    ),
    (
        (("0x4251a2", "mlil", "StackVariableSourceType", 338, 8),),
        ("StackVariableSourceType", 338, 8),
        "tail_sample_z",
        "float",
    ),
    (
        (
            ("0x425206", "mlil", "StackVariableSourceType", 438, 8),
            ("0x42550c", "mlil", "StackVariableSourceType", 1212, 8),
            ("0x42520a", "mlil_ssa", "StackVariableSourceType", 442, 8),
        ),
        ("StackVariableSourceType", 438, 8),
        "curve_index",
        "int32_t",
    ),
    (
        (
            ("0x42523d", "mlil", "StackVariableSourceType", 493, -72),
            ("0x425237", "mlil", "StackVariableSourceType", 487, -72),
            ("0x425241", "mlil_ssa", "StackVariableSourceType", 497, -72),
        ),
        ("StackVariableSourceType", 493, -72),
        "center_distance_a",
        "float",
    ),
    (
        (("0x425254", "mlil", "StackVariableSourceType", 516, 8),),
        ("StackVariableSourceType", 516, 8),
        "center_distance_b",
        "float",
    ),
    (
        (("0x4252f0", "mlil", "StackVariableSourceType", 672, 8),),
        ("StackVariableSourceType", 672, 8),
        "curve_sample_index",
        "int32_t",
    ),
    (
        (("0x425304", "mlil", "StackVariableSourceType", 692, 8),),
        ("StackVariableSourceType", 692, 8),
        "curve_sample_z",
        "float",
    ),
)

# Both mobile bodies stop at CalcLengthZ. The generated strip mesh and its
# two-winding face pass are Windows-only, so these owners come exclusively from
# the native Windows instructions and exact MLIL definitions.
SLALOMDOUBLE_MESH_STACK_LIFETIME_SPLITS = (
    (
        (("0x4256d0", "mlil", "StackVariableSourceType", 1664, -64),),
        ("StackVariableSourceType", 1664, -64),
        "mesh_facequads",
        "ObjectFaceQuad*",
    ),
    (
        (("0x4256d8", "mlil", "StackVariableSourceType", 1672, -68),),
        ("StackVariableSourceType", 1672, -68),
        "mesh_vertices",
        "Vec3*",
    ),
    (
        (
            ("0x4256e9", "mlil", "StackVariableSourceType", 1689, 8),
            ("0x4257ee", "mlil", "StackVariableSourceType", 1950, 8),
            ("0x4256f7", "mlil_ssa", "StackVariableSourceType", 1703, 8),
        ),
        ("StackVariableSourceType", 1689, 8),
        "mesh_column",
        "int32_t",
    ),
    (
        (
            ("0x4256ed", "mlil", "StackVariableSourceType", 1693, -76),
            ("0x4257e8", "mlil", "StackVariableSourceType", 1944, -76),
            ("0x4256f7", "mlil_ssa", "StackVariableSourceType", 1703, -76),
        ),
        ("StackVariableSourceType", 1693, -76),
        "mesh_width_cells",
        "int32_t",
    ),
    (
        (
            ("0x42581e", "mlil", "StackVariableSourceType", 1998, 8),
            ("0x425a04", "mlil", "StackVariableSourceType", 2484, 8),
            ("0x42585b", "mlil_ssa", "StackVariableSourceType", 2059, 8),
        ),
        ("StackVariableSourceType", 1998, 8),
        "face_column_for_uv",
        "int32_t",
    ),
    (
        (("0x425836", "mlil", "StackVariableSourceType", 2022, -68),),
        ("StackVariableSourceType", 2022, -68),
        "v0_index",
        "int32_t",
    ),
    (
        (("0x42583f", "mlil", "StackVariableSourceType", 2031, -68),),
        ("StackVariableSourceType", 2031, -68),
        "v1_index",
        "int32_t",
    ),
    (
        (("0x425849", "mlil", "StackVariableSourceType", 2041, -84),),
        ("StackVariableSourceType", 2041, -84),
        "v0",
        "float",
    ),
    (
        (("0x425857", "mlil", "StackVariableSourceType", 2055, -76),),
        ("StackVariableSourceType", 2055, -76),
        "v1",
        "float",
    ),
    (
        (("0x425864", "mlil", "StackVariableSourceType", 2068, -68),),
        ("StackVariableSourceType", 2068, -68),
        "u1_index",
        "int32_t",
    ),
    (
        (
            ("0x425868", "mlil", "StackVariableSourceType", 2072, -72),
            ("0x4259f1", "mlil", "StackVariableSourceType", 2465, -72),
            ("0x42588a", "mlil_ssa", "StackVariableSourceType", 2106, -72),
        ),
        ("StackVariableSourceType", 2072, -72),
        "face_pass",
        "int32_t",
    ),
    (
        (("0x425872", "mlil", "StackVariableSourceType", 2082, 8),),
        ("StackVariableSourceType", 2082, 8),
        "u0",
        "float",
    ),
    (
        (("0x425880", "mlil", "StackVariableSourceType", 2096, -80),),
        ("StackVariableSourceType", 2096, -80),
        "u1",
        "float",
    ),
)

# The face pass partially reloads width+1 through ECX and EDX in both winding
# arms. Keep the two register lifetimes separate so neither contaminates the
# stack-owned pass counter or the authored width argument.
SLALOMDOUBLE_FACE_REGISTER_LIFETIME_SPLITS = (
    (
        (
            ("0x4258af", "mlil", "RegisterVariableSourceType", 2143, 67),
            ("0x4258b5", "mlil", "RegisterVariableSourceType", 2149, 67),
            ("0x4258d3", "mlil", "RegisterVariableSourceType", 2179, 67),
            ("0x4258da", "mlil", "RegisterVariableSourceType", 2186, 67),
            ("0x4258e7", "mlil", "RegisterVariableSourceType", 2199, 67),
            ("0x4258eb", "mlil", "RegisterVariableSourceType", 2203, 67),
            ("0x425964", "mlil", "RegisterVariableSourceType", 2324, 67),
            ("0x425968", "mlil", "RegisterVariableSourceType", 2328, 67),
            ("0x425985", "mlil", "RegisterVariableSourceType", 2357, 67),
            ("0x425989", "mlil", "RegisterVariableSourceType", 2361, 67),
        ),
        ("RegisterVariableSourceType", 2143, 67),
        "face_width_plus_one_ecx",
        "int32_t",
    ),
    (
        (
            ("0x4258c2", "mlil", "RegisterVariableSourceType", 2162, 68),
            ("0x4258c6", "mlil", "RegisterVariableSourceType", 2166, 68),
            ("0x42594f", "mlil", "RegisterVariableSourceType", 2303, 68),
            ("0x425955", "mlil", "RegisterVariableSourceType", 2309, 68),
            ("0x425976", "mlil", "RegisterVariableSourceType", 2342, 68),
            ("0x42597a", "mlil", "RegisterVariableSourceType", 2346, 68),
        ),
        ("RegisterVariableSourceType", 2162, 68),
        "face_width_plus_one_edx",
        "int32_t",
    ),
)

# The paired Android and iOS BuildP bodies independently preserve the portable
# sample-count, endpoint, zero-based curve counter, one-based sample index, and
# curve-angle owners. Windows remains authoritative for every definition below:
# VC6 merely coalesces those values into the dead scale/start/end argument homes.
P_CONTROL_LIFETIME_SPLITS = (
    (
        (("0x425a68", "mlil", "StackVariableSourceType", 40, 8),),
        ("StackVariableSourceType", 40, 8),
        "sample_count",
        "int32_t",
    ),
    (
        (("0x425b30", "mlil", "StackVariableSourceType", 240, 16),),
        ("StackVariableSourceType", 240, 16),
        "last_sample_index",
        "int32_t",
    ),
    (
        (("0x425b90", "mlil", "StackVariableSourceType", 336, 16),),
        ("StackVariableSourceType", 336, 16),
        "terminal_sample_z",
        "float",
    ),
    (
        (
            ("0x425bc0", "mlil", "RegisterVariableSourceType", 384, 71),
            ("0x425ccb", "mlil", "RegisterVariableSourceType", 651, 71),
            ("0x425bf5", "mlil_ssa", "RegisterVariableSourceType", 437, 71),
            ("0x425bcd", "mlil", "StackVariableSourceType", 397, 16),
            ("0x425ccc", "mlil", "StackVariableSourceType", 652, 16),
            ("0x425eba", "mlil", "StackVariableSourceType", 1146, 16),
            ("0x425bf5", "mlil_ssa", "StackVariableSourceType", 437, 16),
        ),
        ("RegisterVariableSourceType", 384, 71),
        "curve_index",
        "int32_t",
    ),
    (
        (("0x425bf1", "mlil", "StackVariableSourceType", 433, 20),),
        ("StackVariableSourceType", 433, 20),
        "curve_segments_f",
        "float",
    ),
    (
        (("0x425c09", "mlil", "StackVariableSourceType", 457, 16),),
        ("StackVariableSourceType", 457, 16),
        "curve_phase",
        "float",
    ),
    (
        (("0x425ce6", "mlil", "StackVariableSourceType", 678, 16),),
        ("StackVariableSourceType", 678, 16),
        "curve_sample_z",
        "float",
    ),
)

# The mobile functions end after CalcLengthZ. Everything here is therefore
# recovered solely from the native Windows mesh tail. In particular, the
# vertices/facequads pointers, nested loop counters, UV scalars, and winding
# pass are not authored mutations of BuildP's incoming arguments.
P_MESH_LIFETIME_SPLITS = (
    (
        (("0x42607d", "mlil", "StackVariableSourceType", 1597, 16),),
        ("StackVariableSourceType", 1597, 16),
        "mesh_vertices",
        "Vec3*",
    ),
    (
        (("0x426083", "mlil", "StackVariableSourceType", 1603, 12),),
        ("StackVariableSourceType", 1603, 12),
        "mesh_facequads",
        "ObjectFaceQuad*",
    ),
    (
        (
            ("0x426090", "mlil", "RegisterVariableSourceType", 1616, 73),
            ("0x426192", "mlil", "RegisterVariableSourceType", 1874, 73),
            ("0x4260a2", "mlil_ssa", "RegisterVariableSourceType", 1634, 73),
            ("0x426094", "mlil", "StackVariableSourceType", 1620, 8),
            ("0x426199", "mlil", "StackVariableSourceType", 1881, 8),
            ("0x4260a2", "mlil_ssa", "StackVariableSourceType", 1634, 8),
        ),
        ("RegisterVariableSourceType", 1616, 73),
        "mesh_column",
        "int32_t",
    ),
    (
        (
            ("0x426098", "mlil", "StackVariableSourceType", 1624, 24),
            ("0x426193", "mlil", "StackVariableSourceType", 1875, 24),
            ("0x4260a2", "mlil_ssa", "StackVariableSourceType", 1634, 24),
        ),
        ("StackVariableSourceType", 1624, 24),
        "mesh_width_cells",
        "int32_t",
    ),
    (
        (
            ("0x4261c5", "mlil", "RegisterVariableSourceType", 1925, 73),
            ("0x4263b8", "mlil", "RegisterVariableSourceType", 2424, 73),
            ("0x426206", "mlil_ssa", "RegisterVariableSourceType", 1990, 73),
            ("0x4261c9", "mlil", "StackVariableSourceType", 1929, 8),
            ("0x4263c1", "mlil", "StackVariableSourceType", 2433, 8),
            ("0x426206", "mlil_ssa", "StackVariableSourceType", 1990, 8),
        ),
        ("RegisterVariableSourceType", 1925, 73),
        "face_column",
        "int32_t",
    ),
    (
        (("0x4261e1", "mlil", "StackVariableSourceType", 1953, 24),),
        ("StackVariableSourceType", 1953, 24),
        "v0_index",
        "int32_t",
    ),
    (
        (("0x4261ea", "mlil", "StackVariableSourceType", 1962, 16),),
        ("StackVariableSourceType", 1962, 16),
        "v1_index",
        "int32_t",
    ),
    (
        (("0x4261f4", "mlil", "StackVariableSourceType", 1972, 24),),
        ("StackVariableSourceType", 1972, 24),
        "v0",
        "float",
    ),
    (
        (("0x426202", "mlil", "StackVariableSourceType", 1986, 20),),
        ("StackVariableSourceType", 1986, 20),
        "v1",
        "float",
    ),
    (
        (("0x42620f", "mlil", "StackVariableSourceType", 1999, -64),),
        ("StackVariableSourceType", 1999, -64),
        "u1_index",
        "int32_t",
    ),
    (
        (
            ("0x42620d", "mlil", "RegisterVariableSourceType", 1997, 67),
            ("0x426231", "mlil", "RegisterVariableSourceType", 2033, 67),
            ("0x426235", "mlil_ssa", "RegisterVariableSourceType", 2037, 67),
            ("0x426213", "mlil", "StackVariableSourceType", 2003, 4),
            ("0x4263ae", "mlil", "StackVariableSourceType", 2414, 4),
            ("0x426235", "mlil_ssa", "StackVariableSourceType", 2037, 4),
        ),
        ("RegisterVariableSourceType", 1997, 67),
        "face_pass",
        "int32_t",
    ),
    (
        (("0x42621d", "mlil", "StackVariableSourceType", 2013, 8),),
        ("StackVariableSourceType", 2013, 8),
        "u0",
        "float",
    ),
    (
        (("0x42622b", "mlil", "StackVariableSourceType", 2027, 16),),
        ("StackVariableSourceType", 2027, 16),
        "u1",
        "float",
    ),
)

# Each branch-local face record reconstructs width + 1 in physical registers.
# Preserve the EAX, ECX, and EDX lifetimes independently; merging them would
# falsely make the face-pass or authored width owners change type mid-loop.
P_FACE_REGISTER_LIFETIME_SPLITS = (
    (
        (
            ("0x42625f", "mlil", "RegisterVariableSourceType", 2079, 66),
            ("0x426263", "mlil", "RegisterVariableSourceType", 2083, 66),
            ("0x426323", "mlil", "RegisterVariableSourceType", 2275, 66),
            ("0x426327", "mlil", "RegisterVariableSourceType", 2279, 66),
        ),
        ("RegisterVariableSourceType", 2079, 66),
        "face_width_plus_one_eax",
        "int32_t",
    ),
    (
        (
            ("0x42626e", "mlil", "RegisterVariableSourceType", 2094, 67),
            ("0x426272", "mlil", "RegisterVariableSourceType", 2098, 67),
            ("0x426282", "mlil", "RegisterVariableSourceType", 2114, 67),
            ("0x426286", "mlil", "RegisterVariableSourceType", 2118, 67),
            ("0x426293", "mlil", "RegisterVariableSourceType", 2131, 67),
            ("0x426297", "mlil", "RegisterVariableSourceType", 2135, 67),
            ("0x426312", "mlil", "RegisterVariableSourceType", 2258, 67),
            ("0x426316", "mlil", "RegisterVariableSourceType", 2262, 67),
            ("0x426332", "mlil", "RegisterVariableSourceType", 2290, 67),
            ("0x426339", "mlil", "RegisterVariableSourceType", 2297, 67),
        ),
        ("RegisterVariableSourceType", 2094, 67),
        "face_width_plus_one_ecx",
        "int32_t",
    ),
    (
        (
            ("0x426344", "mlil", "RegisterVariableSourceType", 2308, 68),
            ("0x426348", "mlil", "RegisterVariableSourceType", 2312, 68),
        ),
        ("RegisterVariableSourceType", 2308, 68),
        "face_width_plus_one_edx",
        "int32_t",
    ),
)

SLALOMDOUBLE_P_SPLIT_LIFETIME_GROUPS = (
    (
        "initialize_slalomdouble_path_template_pair",
        SLALOMDOUBLE_CONTROL_STACK_LIFETIME_SPLITS
        + SLALOMDOUBLE_MESH_STACK_LIFETIME_SPLITS
        + SLALOMDOUBLE_FACE_REGISTER_LIFETIME_SPLITS,
    ),
    (
        "initialize_p_path_template_pair",
        P_CONTROL_LIFETIME_SPLITS
        + P_MESH_LIFETIME_SPLITS
        + P_FACE_REGISTER_LIFETIME_SPLITS,
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the basis-vector, terminal-delta, sample, and facequad "
            "lifetimes in the double-slalom and P path constructors."
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
            "canonical double-slalom/P ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_slalomdouble_p_path_owner_layouts",
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
                SLALOMDOUBLE_P_PATH_USER_VAR_UPDATES
                + SLALOMDOUBLE_CONTROL_USER_VAR_UPDATES
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
                for function_name, groups in SLALOMDOUBLE_P_SPLIT_LIFETIME_GROUPS
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
