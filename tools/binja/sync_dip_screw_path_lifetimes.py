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

# Android and iOS independently preserve the portable control graph for each
# constructor. Dip owns a derived curve count, one far endpoint, a cosine
# middle, and the final delta pass. Screw owns three entrance samples, five
# departure samples, a helical middle, and the final delta pass. Windows is
# authoritative for every exact definition identity below and for the
# native-only strip-mesh tail.
DIP_SCREW_CONTROL_USER_VAR_UPDATES = (
    (
        "initialize_dip_path_template_pair",
        "StackVariableSourceType",
        85,
        -72,
        "curve_count_f",
        "float",
    ),
    (
        "initialize_dip_path_template_pair",
        "RegisterVariableSourceType",
        246,
        73,
        "endpoint_sample_offset",
        "int32_t",
    ),
    (
        "initialize_dip_path_template_pair",
        "StackVariableSourceType",
        333,
        -64,
        "endpoint_sample_z",
        "float",
    ),
    (
        "initialize_dip_path_template_pair",
        "StackVariableSourceType",
        491,
        -76,
        "angle",
        "float",
    ),
    (
        "initialize_dip_path_template_pair",
        "StackVariableSourceType",
        560,
        -64,
        "curve_sample_z",
        "float",
    ),
    (
        "initialize_screw_path_template_pair",
        "StackVariableSourceType",
        161,
        -68,
        "entrance_sample_z",
        "float",
    ),
    (
        "initialize_screw_path_template_pair",
        "StackVariableSourceType",
        507,
        -68,
        "curve_count_f",
        "float",
    ),
    (
        "initialize_screw_path_template_pair",
        "StackVariableSourceType",
        530,
        -76,
        "angle",
        "float",
    ),
    (
        "initialize_screw_path_template_pair",
        "StackVariableSourceType",
        631,
        -72,
        "curve_sample_index",
        "int32_t",
    ),
    (
        "initialize_screw_path_template_pair",
        "StackVariableSourceType",
        655,
        -72,
        "curve_sample_z",
        "float",
    ),
)

DIP_CONTROL_LIFETIME_SPLITS = (
    (
        (
            ("0x41e46a", "mlil", "RegisterVariableSourceType", 42, 66),
            ("0x41e472", "mlil", "StackVariableSourceType", 50, 8),
        ),
        ("RegisterVariableSourceType", 42, 66),
        "curve_count",
        "int32_t",
    ),
    (
        (
            ("0x41e47d", "mlil", "RegisterVariableSourceType", 61, 66),
            ("0x41e483", "mlil", "StackVariableSourceType", 67, 4),
        ),
        ("RegisterVariableSourceType", 61, 66),
        "total_segment_count",
        "int32_t",
    ),
    (
        (("0x41e49f", "mlil", "StackVariableSourceType", 95, 4),),
        ("StackVariableSourceType", 95, 4),
        "profile_radius",
        "float",
    ),
    (
        (
            ("0x41e46f", "mlil", "RegisterVariableSourceType", 47, 73),
            ("0x41e50a", "mlil", "StackVariableSourceType", 202, -64),
        ),
        ("RegisterVariableSourceType", 47, 73),
        "endpoint_sample_index",
        "int32_t",
    ),
    (
        (
            ("0x41e5c2", "mlil", "StackVariableSourceType", 386, -76),
            ("0x41e84d", "mlil", "StackVariableSourceType", 1037, -76),
            ("0x41e5e2", "mlil_ssa", "StackVariableSourceType", 418, -76),
        ),
        ("StackVariableSourceType", 386, -76),
        "curve_phase_index",
        "int32_t",
    ),
    (
        (
            ("0x41e5b5", "mlil", "RegisterVariableSourceType", 373, 69),
            ("0x41e65a", "mlil", "RegisterVariableSourceType", 538, 69),
            ("0x41e65f", "mlil", "StackVariableSourceType", 543, -64),
            ("0x41e5e2", "mlil_ssa", "RegisterVariableSourceType", 418, 69),
        ),
        ("RegisterVariableSourceType", 373, 69),
        "curve_sample_index",
        "int32_t",
    ),
    (
        (
            ("0x41e5dd", "mlil", "RegisterVariableSourceType", 413, 73),
            ("0x41e845", "mlil", "RegisterVariableSourceType", 1029, 73),
            ("0x41e5e2", "mlil_ssa", "RegisterVariableSourceType", 418, 73),
        ),
        ("RegisterVariableSourceType", 413, 73),
        "curve_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x41e85a", "mlil", "RegisterVariableSourceType", 1050, 69),
            ("0x41e913", "mlil", "RegisterVariableSourceType", 1235, 69),
            ("0x41e867", "mlil_ssa", "RegisterVariableSourceType", 1063, 69),
        ),
        ("RegisterVariableSourceType", 1050, 69),
        "delta_index",
        "int32_t",
    ),
    (
        (
            ("0x41e865", "mlil", "RegisterVariableSourceType", 1061, 73),
            ("0x41e91e", "mlil", "RegisterVariableSourceType", 1246, 73),
            ("0x41e867", "mlil_ssa", "RegisterVariableSourceType", 1063, 73),
        ),
        ("RegisterVariableSourceType", 1061, 73),
        "delta_sample_offset",
        "int32_t",
    ),
)

SCREW_CONTROL_LIFETIME_SPLITS = (
    (
        (
            ("0x41edbb", "mlil", "RegisterVariableSourceType", 27, 66),
            ("0x41edc0", "mlil", "StackVariableSourceType", 32, 8),
        ),
        ("RegisterVariableSourceType", 27, 66),
        "total_segment_count",
        "int32_t",
    ),
    (
        (
            ("0x41edea", "mlil", "StackVariableSourceType", 74, 8),
            ("0x41ee9a", "mlil", "StackVariableSourceType", 250, 8),
            ("0x41edf0", "mlil_ssa", "StackVariableSourceType", 80, 8),
        ),
        ("StackVariableSourceType", 74, 8),
        "entrance_sample_index",
        "int32_t",
    ),
    (
        (
            ("0x41edee", "mlil", "RegisterVariableSourceType", 78, 73),
            ("0x41ee8d", "mlil", "RegisterVariableSourceType", 237, 73),
            ("0x41edf0", "mlil_ssa", "RegisterVariableSourceType", 80, 73),
        ),
        ("RegisterVariableSourceType", 78, 73),
        "entrance_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x41eead", "mlil", "RegisterVariableSourceType", 269, 71),
            ("0x41ef70", "mlil", "RegisterVariableSourceType", 464, 71),
            ("0x41eec9", "mlil_ssa", "RegisterVariableSourceType", 297, 71),
        ),
        ("RegisterVariableSourceType", 269, 71),
        "departure_sample_index",
        "int32_t",
    ),
    (
        (
            ("0x41eec0", "mlil", "RegisterVariableSourceType", 288, 73),
            ("0x41ef6a", "mlil", "RegisterVariableSourceType", 458, 73),
            ("0x41eec9", "mlil_ssa", "RegisterVariableSourceType", 297, 73),
        ),
        ("RegisterVariableSourceType", 288, 73),
        "departure_sample_offset",
        "int32_t",
    ),
    (
        (("0x41ef1e", "mlil", "StackVariableSourceType", 382, 8),),
        ("StackVariableSourceType", 382, 8),
        "departure_sample_z",
        "float",
    ),
    (
        (
            ("0x41ef84", "mlil", "RegisterVariableSourceType", 484, 71),
            ("0x41ef88", "mlil", "StackVariableSourceType", 488, 8),
            ("0x41f22e", "mlil", "RegisterVariableSourceType", 1166, 71),
            ("0x41f237", "mlil", "StackVariableSourceType", 1175, 8),
            ("0x41efa3", "mlil_ssa", "RegisterVariableSourceType", 515, 71),
            ("0x41efa3", "mlil_ssa", "StackVariableSourceType", 515, 8),
        ),
        ("RegisterVariableSourceType", 484, 71),
        "curve_index",
        "int32_t",
    ),
    (
        (
            ("0x41ef96", "mlil", "RegisterVariableSourceType", 502, 73),
            ("0x41f22f", "mlil", "RegisterVariableSourceType", 1167, 73),
            ("0x41efa3", "mlil_ssa", "RegisterVariableSourceType", 515, 73),
        ),
        ("RegisterVariableSourceType", 502, 73),
        "curve_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x41f246", "mlil", "RegisterVariableSourceType", 1190, 71),
            ("0x41f302", "mlil", "RegisterVariableSourceType", 1378, 71),
            ("0x41f253", "mlil_ssa", "RegisterVariableSourceType", 1203, 71),
        ),
        ("RegisterVariableSourceType", 1190, 71),
        "delta_index",
        "int32_t",
    ),
    (
        (
            ("0x41f251", "mlil", "RegisterVariableSourceType", 1201, 73),
            ("0x41f30d", "mlil", "RegisterVariableSourceType", 1389, 73),
            ("0x41f253", "mlil_ssa", "RegisterVariableSourceType", 1203, 73),
        ),
        ("RegisterVariableSourceType", 1201, 73),
        "delta_sample_offset",
        "int32_t",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the proved control, vector, terminal-delta, mesh-vertex, "
            "and facequad lifetimes in the dip and screw constructors."
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
            updates=(
                DIP_SCREW_PATH_USER_VAR_UPDATES
                + DIP_SCREW_CONTROL_USER_VAR_UPDATES
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
                        "initialize_dip_path_template_pair",
                        DIP_CONTROL_LIFETIME_SPLITS,
                    ),
                    (
                        "initialize_screw_path_template_pair",
                        SCREW_CONTROL_LIFETIME_SPLITS,
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
