#!/usr/bin/env python3

from __future__ import annotations

import argparse
import sys
from pathlib import Path

from _narrow_sync import (
    apply_split_away_user_var_update,
    apply_split_user_var_update,
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

# Android and iOS preserve these four branch-selected values in
# cRPath::BuildToad. The Windows stack lifetimes prove the same roles. Keep the
# late sample-bank reload separate so correcting the integer lead count cannot
# flatten its genuine PathTemplateSample owner.
TOAD_CONTROL_LIFETIME_SPECS = (
    ("StackVariableSourceType", 61, -84, "lead_count", "int32_t"),
    ("StackVariableSourceType", 45, -80, "start_x", "float"),
    ("StackVariableSourceType", 65, -76, "tail_count", "int32_t"),
    ("StackVariableSourceType", 53, -72, "turn_sign", "float"),
)

# ECX is joined with the lead-count carrier through the seed loops, then reloads
# the real primary sample bank for the curved secondary-position offset. Split
# only that reload before typing it so neither physical lifetime infects the
# other.
TOAD_PRIMARY_SAMPLE_BANK_DEFINITIONS = (
    ("0x42cfd1", "mlil", "RegisterVariableSourceType", 993, 67),
)

TOAD_PRIMARY_SAMPLE_BANK_VAR = (
    "RegisterVariableSourceType",
    993,
    67,
)

# GetNodes is void but clobbers the same ECX physical lane later reloaded with
# lead_count. Detach the call definition before naming that loop-bound lifetime
# so the decompiler does not invent a return value for GetNodes.
TOAD_LEAD_BOUND_DETACHED_DEFINITIONS = (
    ("0x42cc7f", "mlil", "RegisterVariableSourceType", 143, 67),
)

TOAD_LEAD_BOUND_VAR = (
    "RegisterVariableSourceType",
    343,
    67,
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

# Android and iOS keep the authored Hill controls in distinct locals. Windows
# preserves the same values, but VC6 later reuses their dead argument homes for
# mesh and UV temporaries. These definition-bounded splits retain both sides of
# that ownership boundary instead of typing the whole physical stack slot.
HILL_STACK_LIFETIME_SPLITS = (
    (
        (("0x42d59c", "mlil", "StackVariableSourceType", 44, 4),),
        ("StackVariableSourceType", 44, 4),
        "steps",
        "int32_t",
    ),
    (
        (("0x42d5ad", "mlil", "StackVariableSourceType", 61, 12),),
        ("StackVariableSourceType", 61, 12),
        "segment_count_value",
        "int32_t",
    ),
    (
        (("0x42d664", "mlil", "StackVariableSourceType", 244, 16),),
        ("StackVariableSourceType", 244, 16),
        "last_index",
        "int32_t",
    ),
    (
        (("0x42d6ef", "mlil", "StackVariableSourceType", 383, 16),),
        ("StackVariableSourceType", 383, 16),
        "last_z",
        "float",
    ),
    (
        (
            ("0x42d726", "mlil", "StackVariableSourceType", 438, 16),
            ("0x42d9c7", "mlil", "StackVariableSourceType", 1111, 16),
        ),
        ("StackVariableSourceType", 438, 16),
        "phase_index",
        "int32_t",
    ),
    (
        (("0x42d74a", "mlil", "StackVariableSourceType", 474, 12),),
        ("StackVariableSourceType", 474, 12),
        "steps_f",
        "float",
    ),
    (
        (("0x42d79f", "mlil", "StackVariableSourceType", 559, 16),),
        ("StackVariableSourceType", 559, 16),
        "phase",
        "float",
    ),
    (
        (("0x42db8a", "mlil", "StackVariableSourceType", 1562, 4),),
        ("StackVariableSourceType", 1562, 4),
        "mesh_vertices",
        "Vec3*",
    ),
    (
        (
            ("0x42dba1", "mlil", "StackVariableSourceType", 1585, 16),
            ("0x42dca6", "mlil", "StackVariableSourceType", 1846, 16),
        ),
        ("StackVariableSourceType", 1585, 16),
        "mesh_column",
        "int32_t",
    ),
    (
        (
            ("0x42dba5", "mlil", "StackVariableSourceType", 1589, 8),
            ("0x42dca0", "mlil", "StackVariableSourceType", 1840, 8),
        ),
        ("StackVariableSourceType", 1589, 8),
        "mesh_width_cells",
        "int32_t",
    ),
    (
        (
            ("0x42dcd6", "mlil", "StackVariableSourceType", 1894, 16),
            ("0x42dece", "mlil", "StackVariableSourceType", 2398, 16),
        ),
        ("StackVariableSourceType", 1894, 16),
        "face_column_for_uv",
        "int32_t",
    ),
    (
        (("0x42dcee", "mlil", "StackVariableSourceType", 1918, 8),),
        ("StackVariableSourceType", 1918, 8),
        "v0_index",
        "int32_t",
    ),
    (
        (("0x42dcf7", "mlil", "StackVariableSourceType", 1927, 4),),
        ("StackVariableSourceType", 1927, 4),
        "v1_index",
        "int32_t",
    ),
    (
        (("0x42dd01", "mlil", "StackVariableSourceType", 1937, 8),),
        ("StackVariableSourceType", 1937, 8),
        "v0",
        "float",
    ),
    (
        (("0x42dd0f", "mlil", "StackVariableSourceType", 1951, 12),),
        ("StackVariableSourceType", 1951, 12),
        "v1",
        "float",
    ),
    (
        (("0x42dd2a", "mlil", "StackVariableSourceType", 1978, 16),),
        ("StackVariableSourceType", 1978, 16),
        "u0",
        "float",
    ),
    (
        (("0x42dd38", "mlil", "StackVariableSourceType", 1992, 4),),
        ("StackVariableSourceType", 1992, 4),
        "u1",
        "float",
    ),
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

SBEND_CONTROL_LIFETIME_SPECS = (
    ("StackVariableSourceType", 56, -72, "steps", "int32_t"),
)

# The exact Android and iOS BuildSBend bodies preserve steps, sample_index, and
# phase as authored controls. Windows then reuses the former parameter homes
# for the mesh and UV pass, so keep each Windows definition-bounded lifetime
# separate rather than spreading a mobile-derived type across the whole slot.
SBEND_STACK_LIFETIME_SPLITS = (
    (
        (("0x42df42", "mlil", "StackVariableSourceType", 66, 4),),
        ("StackVariableSourceType", 66, 4),
        "segment_count_value",
        "int32_t",
    ),
    (
        (
            ("0x42dfdb", "mlil", "StackVariableSourceType", 219, 16),
            ("0x42e1dd", "mlil", "StackVariableSourceType", 733, 16),
        ),
        ("StackVariableSourceType", 219, 16),
        "sample_index",
        "int32_t",
    ),
    (
        (("0x42e072", "mlil", "StackVariableSourceType", 370, 4),),
        ("StackVariableSourceType", 370, 4),
        "phase",
        "float",
    ),
    (
        (("0x42e3a7", "mlil", "StackVariableSourceType", 1191, 4),),
        ("StackVariableSourceType", 1191, 4),
        "mesh_vertices",
        "Vec3*",
    ),
    (
        (
            ("0x42e3ba", "mlil", "StackVariableSourceType", 1210, 16),
            ("0x42e4bd", "mlil", "StackVariableSourceType", 1469, 16),
        ),
        ("StackVariableSourceType", 1210, 16),
        "mesh_column",
        "int32_t",
    ),
    (
        (
            ("0x42e3be", "mlil", "StackVariableSourceType", 1214, 8),
            ("0x42e4b7", "mlil", "StackVariableSourceType", 1463, 8),
        ),
        ("StackVariableSourceType", 1214, 8),
        "mesh_width_cells",
        "int32_t",
    ),
    (
        (
            ("0x42e4ed", "mlil", "StackVariableSourceType", 1517, 16),
            ("0x42e6e3", "mlil", "StackVariableSourceType", 2019, 16),
        ),
        ("StackVariableSourceType", 1517, 16),
        "face_column_for_uv",
        "int32_t",
    ),
    (
        (("0x42e505", "mlil", "StackVariableSourceType", 1541, 8),),
        ("StackVariableSourceType", 1541, 8),
        "v0_index",
        "int32_t",
    ),
    (
        (("0x42e50e", "mlil", "StackVariableSourceType", 1550, 4),),
        ("StackVariableSourceType", 1550, 4),
        "v1_index",
        "int32_t",
    ),
    (
        (("0x42e518", "mlil", "StackVariableSourceType", 1560, 8),),
        ("StackVariableSourceType", 1560, 8),
        "v0",
        "float",
    ),
    (
        (("0x42e526", "mlil", "StackVariableSourceType", 1574, 12),),
        ("StackVariableSourceType", 1574, 12),
        "v1",
        "float",
    ),
    (
        (("0x42e541", "mlil", "StackVariableSourceType", 1601, 16),),
        ("StackVariableSourceType", 1601, 16),
        "u0",
        "float",
    ),
    (
        (("0x42e54f", "mlil", "StackVariableSourceType", 1615, 4),),
        ("StackVariableSourceType", 1615, 4),
        "u1",
        "float",
    ),
)

TOAD_HILL_SBEND_PATH_USER_VAR_UPDATES = (
    tuple(
        (
            "initialize_toad_path_template_pair",
            source_type,
            index,
            storage,
            variable_name,
            variable_type,
        )
        for source_type, index, storage, variable_name, variable_type in (
            TOAD_CONTROL_LIFETIME_SPECS
        )
    )
    + tuple(
        (
            "initialize_sbend_path_template_pair",
            source_type,
            index,
            storage,
            variable_name,
            variable_type,
        )
        for source_type, index, storage, variable_name, variable_type in (
            SBEND_CONTROL_LIFETIME_SPECS
        )
    )
    + tuple(
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
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the proved control, sample, vector, mesh-vertex, and "
            "facequad lifetimes in the toad, hill/valley, and s-bend "
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

    operations = [verify_owner_layouts(args.target)]
    operations.extend(
        apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=TOAD_HILL_SBEND_PATH_USER_VAR_UPDATES,
        )
    )
    operations.extend(
        apply_split_away_user_var_update(
            REPO_ROOT,
            target=args.target,
            identifier="initialize_toad_path_template_pair",
            detached_definitions=TOAD_LEAD_BOUND_DETACHED_DEFINITIONS,
            residual_var=TOAD_LEAD_BOUND_VAR,
            variable_name="lead_count_bound",
            variable_type="int32_t",
        )
    )
    operations.extend(
        apply_split_user_var_update(
            REPO_ROOT,
            target=args.target,
            identifier="initialize_toad_path_template_pair",
            definitions=TOAD_PRIMARY_SAMPLE_BANK_DEFINITIONS,
            target_var=TOAD_PRIMARY_SAMPLE_BANK_VAR,
            variable_name="primary_sample_bank",
            variable_type="PathTemplateSample*",
        )
    )
    for function_name, split_specs in (
        (
            "initialize_hill_valley_path_template_pair",
            HILL_STACK_LIFETIME_SPLITS,
        ),
        (
            "initialize_sbend_path_template_pair",
            SBEND_STACK_LIFETIME_SPLITS,
        ),
    ):
        for definitions, target_var, variable_name, variable_type in split_specs:
            operations.extend(
                apply_split_user_var_update(
                    REPO_ROOT,
                    target=args.target,
                    identifier=function_name,
                    definitions=definitions,
                    target_var=target_var,
                    variable_name=variable_name,
                    variable_type=variable_type,
                )
            )
    return emit_summary(
        repo_root=REPO_ROOT,
        target=args.target,
        header_path=header_path,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
