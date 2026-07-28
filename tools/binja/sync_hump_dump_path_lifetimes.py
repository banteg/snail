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

# BuildHumpA and BuildDumpA have the same post-curve ownership skeleton with a
# ten-identity shift in the dump constructor. Keep only the identities whose
# transactional preview produced direct fields without negative __offset
# expressions. The earlier current-sample temporaries at 892/1063 and 902/1073
# are intentionally omitted because typing them made the decompile less exact.
HUMP_PATH_LIFETIME_SPECS = (
    (850, 68, "primary_right", "Vec3*"),
    (970, 66, "primary_sample_cursor_reloaded", "PathTemplateSample*"),
    (1021, 66, "secondary_right", "Vec3*"),
    (1139, 66, "secondary_sample_cursor_reloaded", "PathTemplateSample*"),
    (1483, 68, "primary_terminal_delta", "Vec3*"),
    (1572, 67, "secondary_terminal_delta", "Vec3*"),
    (1731, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (2141, 71, "face_first", "ObjectFaceQuad*"),
    (2320, 71, "face_second", "ObjectFaceQuad*"),
)

DUMP_PATH_LIFETIME_SPECS = (
    (860, 68, "primary_right", "Vec3*"),
    (980, 66, "primary_sample_cursor_reloaded", "PathTemplateSample*"),
    (1031, 66, "secondary_right", "Vec3*"),
    (1149, 66, "secondary_sample_cursor_reloaded", "PathTemplateSample*"),
    (1493, 68, "primary_terminal_delta", "Vec3*"),
    (1582, 67, "secondary_terminal_delta", "Vec3*"),
    (1741, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (2151, 71, "face_first", "ObjectFaceQuad*"),
    (2330, 71, "face_second", "ObjectFaceQuad*"),
)

HUMP_DUMP_PATH_USER_VAR_UPDATES = tuple(
    (
        function_name,
        "RegisterVariableSourceType",
        index,
        storage,
        variable_name,
        variable_type,
    )
    for function_name, specs in (
        ("initialize_hump_path_template_pair", HUMP_PATH_LIFETIME_SPECS),
        ("initialize_dump_path_template_pair", DUMP_PATH_LIFETIME_SPECS),
    )
    for index, storage, variable_name, variable_type in specs
)

# Android and iOS BuildHump/BuildDump independently retain the same portable
# control graph: seven approach samples, a cosine-profile middle run, seven
# departure samples, and the final delta pass through CalcLengthZ. Windows is
# authoritative for the exact IL identities below, including reuse of dead
# parameter stack slots and the native-only strip-mesh tail.
HUMP_DUMP_CONTROL_USER_VAR_UPDATES = (
    (
        "initialize_hump_path_template_pair",
        "StackVariableSourceType",
        84,
        -72,
        "curve_count_f",
        "float",
    ),
    (
        "initialize_hump_path_template_pair",
        "StackVariableSourceType",
        215,
        -64,
        "approach_sample_z",
        "float",
    ),
    (
        "initialize_hump_path_template_pair",
        "StackVariableSourceType",
        571,
        -68,
        "angle",
        "float",
    ),
    (
        "initialize_hump_path_template_pair",
        "StackVariableSourceType",
        712,
        -64,
        "curve_sample_index",
        "int32_t",
    ),
    (
        "initialize_hump_path_template_pair",
        "StackVariableSourceType",
        731,
        -64,
        "curve_sample_z",
        "float",
    ),
    (
        "initialize_dump_path_template_pair",
        "StackVariableSourceType",
        84,
        -72,
        "curve_count_f",
        "float",
    ),
    (
        "initialize_dump_path_template_pair",
        "StackVariableSourceType",
        219,
        -64,
        "approach_sample_z",
        "float",
    ),
    (
        "initialize_dump_path_template_pair",
        "StackVariableSourceType",
        579,
        -68,
        "angle",
        "float",
    ),
    (
        "initialize_dump_path_template_pair",
        "StackVariableSourceType",
        722,
        -64,
        "curve_sample_index",
        "int32_t",
    ),
    (
        "initialize_dump_path_template_pair",
        "StackVariableSourceType",
        743,
        -64,
        "curve_sample_z",
        "float",
    ),
)

HUMP_CONTROL_LIFETIME_SPLITS = (
    (
        (
            ("0x41d05a", "mlil", "RegisterVariableSourceType", 42, 66),
            ("0x41d062", "mlil", "StackVariableSourceType", 50, -76),
            ("0x41d4e4", "mlil_ssa", "RegisterVariableSourceType", 1204, 67),
        ),
        ("RegisterVariableSourceType", 42, 66),
        "curve_count",
        "int32_t",
    ),
    (
        (
            ("0x41d06f", "mlil", "RegisterVariableSourceType", 63, 66),
            ("0x41d072", "mlil", "StackVariableSourceType", 66, 4),
        ),
        ("RegisterVariableSourceType", 63, 66),
        "total_segment_count",
        "int32_t",
    ),
    (
        (("0x41d08e", "mlil", "StackVariableSourceType", 94, 4),),
        ("StackVariableSourceType", 94, 4),
        "profile_radius",
        "float",
    ),
    (
        (
            ("0x41d09d", "mlil", "StackVariableSourceType", 109, 12),
            ("0x41d158", "mlil", "StackVariableSourceType", 296, 12),
            ("0x41d0a3", "mlil_ssa", "StackVariableSourceType", 115, 12),
        ),
        ("StackVariableSourceType", 109, 12),
        "approach_sample_index",
        "int32_t",
    ),
    (
        (
            ("0x41d0a1", "mlil", "RegisterVariableSourceType", 113, 73),
            ("0x41d14b", "mlil", "RegisterVariableSourceType", 283, 73),
            ("0x41d0a3", "mlil_ssa", "RegisterVariableSourceType", 115, 73),
        ),
        ("RegisterVariableSourceType", 113, 73),
        "approach_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x41d05f", "mlil", "RegisterVariableSourceType", 47, 71),
            ("0x41d174", "mlil", "StackVariableSourceType", 324, 12),
            ("0x41d234", "mlil", "RegisterVariableSourceType", 516, 71),
            ("0x41d237", "mlil", "StackVariableSourceType", 519, 12),
            ("0x41d184", "mlil_ssa", "RegisterVariableSourceType", 340, 71),
            ("0x41d184", "mlil_ssa", "StackVariableSourceType", 340, 12),
        ),
        ("RegisterVariableSourceType", 47, 71),
        "departure_index",
        "int32_t",
    ),
    (
        (("0x41d1e4", "mlil", "StackVariableSourceType", 436, 12),),
        ("StackVariableSourceType", 436, 12),
        "departure_sample_z",
        "float",
    ),
    (
        (
            ("0x41d17b", "mlil", "RegisterVariableSourceType", 331, 73),
            ("0x41d22e", "mlil", "RegisterVariableSourceType", 510, 73),
            ("0x41d184", "mlil_ssa", "RegisterVariableSourceType", 340, 73),
        ),
        ("RegisterVariableSourceType", 331, 73),
        "departure_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x41d248", "mlil", "StackVariableSourceType", 536, 12),
            ("0x41d4f1", "mlil", "StackVariableSourceType", 1217, 12),
            ("0x41d259", "mlil_ssa", "StackVariableSourceType", 553, 12),
        ),
        ("StackVariableSourceType", 536, 12),
        "curve_index",
        "int32_t",
    ),
    (
        (
            ("0x41d254", "mlil", "RegisterVariableSourceType", 548, 73),
            ("0x41d4e9", "mlil", "RegisterVariableSourceType", 1209, 73),
            ("0x41d259", "mlil_ssa", "RegisterVariableSourceType", 553, 73),
        ),
        ("RegisterVariableSourceType", 548, 73),
        "curve_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x41d4fe", "mlil", "RegisterVariableSourceType", 1230, 71),
            ("0x41d5b7", "mlil", "RegisterVariableSourceType", 1415, 71),
            ("0x41d50b", "mlil_ssa", "RegisterVariableSourceType", 1243, 71),
        ),
        ("RegisterVariableSourceType", 1230, 71),
        "delta_index",
        "int32_t",
    ),
    (
        (
            ("0x41d509", "mlil", "RegisterVariableSourceType", 1241, 73),
            ("0x41d5c2", "mlil", "RegisterVariableSourceType", 1426, 73),
            ("0x41d50b", "mlil_ssa", "RegisterVariableSourceType", 1243, 73),
        ),
        ("RegisterVariableSourceType", 1241, 73),
        "delta_sample_offset",
        "int32_t",
    ),
)

DUMP_CONTROL_LIFETIME_SPLITS = (
    (
        (
            ("0x41da5a", "mlil", "RegisterVariableSourceType", 42, 66),
            ("0x41da62", "mlil", "StackVariableSourceType", 50, -76),
            ("0x41deee", "mlil_ssa", "RegisterVariableSourceType", 1214, 67),
        ),
        ("RegisterVariableSourceType", 42, 66),
        "curve_count",
        "int32_t",
    ),
    (
        (
            ("0x41da6f", "mlil", "RegisterVariableSourceType", 63, 66),
            ("0x41da72", "mlil", "StackVariableSourceType", 66, 4),
        ),
        ("RegisterVariableSourceType", 63, 66),
        "total_segment_count",
        "int32_t",
    ),
    (
        (("0x41da8e", "mlil", "StackVariableSourceType", 94, 4),),
        ("StackVariableSourceType", 94, 4),
        "profile_radius",
        "float",
    ),
    (
        (
            ("0x41da9d", "mlil", "StackVariableSourceType", 109, 12),
            ("0x41db5c", "mlil", "StackVariableSourceType", 300, 12),
            ("0x41daa3", "mlil_ssa", "StackVariableSourceType", 115, 12),
        ),
        ("StackVariableSourceType", 109, 12),
        "approach_sample_index",
        "int32_t",
    ),
    (
        (
            ("0x41daa1", "mlil", "RegisterVariableSourceType", 113, 73),
            ("0x41db4f", "mlil", "RegisterVariableSourceType", 287, 73),
            ("0x41daa3", "mlil_ssa", "RegisterVariableSourceType", 115, 73),
        ),
        ("RegisterVariableSourceType", 113, 73),
        "approach_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x41da5f", "mlil", "RegisterVariableSourceType", 47, 71),
            ("0x41db78", "mlil", "StackVariableSourceType", 328, 12),
            ("0x41dc3c", "mlil", "RegisterVariableSourceType", 524, 71),
            ("0x41dc3f", "mlil", "StackVariableSourceType", 527, 12),
            ("0x41db88", "mlil_ssa", "RegisterVariableSourceType", 344, 71),
            ("0x41db88", "mlil_ssa", "StackVariableSourceType", 344, 12),
        ),
        ("RegisterVariableSourceType", 47, 71),
        "departure_index",
        "int32_t",
    ),
    (
        (("0x41dbec", "mlil", "StackVariableSourceType", 444, 12),),
        ("StackVariableSourceType", 444, 12),
        "departure_sample_z",
        "float",
    ),
    (
        (
            ("0x41db7f", "mlil", "RegisterVariableSourceType", 335, 73),
            ("0x41dc36", "mlil", "RegisterVariableSourceType", 518, 73),
            ("0x41db88", "mlil_ssa", "RegisterVariableSourceType", 344, 73),
        ),
        ("RegisterVariableSourceType", 335, 73),
        "departure_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x41dc50", "mlil", "StackVariableSourceType", 544, 12),
            ("0x41defb", "mlil", "StackVariableSourceType", 1227, 12),
            ("0x41dc61", "mlil_ssa", "StackVariableSourceType", 561, 12),
        ),
        ("StackVariableSourceType", 544, 12),
        "curve_index",
        "int32_t",
    ),
    (
        (
            ("0x41dc5c", "mlil", "RegisterVariableSourceType", 556, 73),
            ("0x41def3", "mlil", "RegisterVariableSourceType", 1219, 73),
            ("0x41dc61", "mlil_ssa", "RegisterVariableSourceType", 561, 73),
        ),
        ("RegisterVariableSourceType", 556, 73),
        "curve_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x41df08", "mlil", "RegisterVariableSourceType", 1240, 71),
            ("0x41dfc1", "mlil", "RegisterVariableSourceType", 1425, 71),
            ("0x41df15", "mlil_ssa", "RegisterVariableSourceType", 1253, 71),
        ),
        ("RegisterVariableSourceType", 1240, 71),
        "delta_index",
        "int32_t",
    ),
    (
        (
            ("0x41df13", "mlil", "RegisterVariableSourceType", 1251, 73),
            ("0x41dfcc", "mlil", "RegisterVariableSourceType", 1436, 73),
            ("0x41df15", "mlil_ssa", "RegisterVariableSourceType", 1253, 73),
        ),
        ("RegisterVariableSourceType", 1251, 73),
        "delta_sample_offset",
        "int32_t",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the basis-vector, terminal-delta, sample, and facequad "
            "lifetimes shared by the hump and dump path constructors."
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
            "canonical hump/dump ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_hump_dump_path_owner_layouts",
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
                HUMP_DUMP_PATH_USER_VAR_UPDATES
                + HUMP_DUMP_CONTROL_USER_VAR_UPDATES
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
                for function_name, split_specs in (
                    (
                        "initialize_hump_path_template_pair",
                        HUMP_CONTROL_LIFETIME_SPLITS,
                    ),
                    (
                        "initialize_dump_path_template_pair",
                        DUMP_CONTROL_LIFETIME_SPLITS,
                    ),
                )
                for definitions, target_var, variable_name, variable_type in split_specs
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
