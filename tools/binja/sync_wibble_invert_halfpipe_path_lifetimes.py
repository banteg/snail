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

# These three nonlinear constructors retain the same complete vector, sample,
# vertex, and face owners around different curve builders. Transactional
# preview proved every lifetime below without increasing each function's
# existing fixed-index __offset count. Halfpipe's transient curved-sample
# cursor is deliberately omitted: it is a pre-biased address, and forcing it
# to PathTemplateSample* introduced three backward __offset expressions.
WIBBLE_PATH_LIFETIME_SPECS = (
    (134, 66, "primary_seed_sample", "PathTemplateSample*"),
    (640, 68, "primary_up", "Vec3*"),
    (745, 67, "primary_right", "Vec3*"),
    (830, 66, "secondary_position", "Vec3*"),
    (1139, 67, "primary_terminal_delta", "Vec3*"),
    (1228, 66, "secondary_terminal_delta", "Vec3*"),
    (1389, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (1451, 66, "vertex", "Vec3*"),
    (1797, 73, "face_first", "ObjectFaceQuad*"),
    (1975, 73, "face_second", "ObjectFaceQuad*"),
)

INVERT_PATH_LIFETIME_SPECS = (
    (134, 66, "primary_seed_sample", "PathTemplateSample*"),
    (609, 68, "primary_up", "Vec3*"),
    (714, 67, "primary_right", "Vec3*"),
    (799, 66, "secondary_position", "Vec3*"),
    (1108, 67, "primary_terminal_delta", "Vec3*"),
    (1197, 66, "secondary_terminal_delta", "Vec3*"),
    (1358, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (1420, 66, "vertex", "Vec3*"),
    (1766, 73, "face_first", "ObjectFaceQuad*"),
    (1944, 73, "face_second", "ObjectFaceQuad*"),
)

HALFPIPE_PATH_LIFETIME_SPECS = (
    (240, 66, "primary_leadin_sample", "PathTemplateSample*"),
    (873, 67, "primary_up", "Vec3*"),
    (974, 67, "primary_right", "Vec3*"),
    (1012, 66, "primary_up_reloaded", "Vec3*"),
    (1049, 66, "secondary_position", "Vec3*"),
    (1367, 67, "primary_terminal_delta", "Vec3*"),
    (1456, 66, "secondary_terminal_delta", "Vec3*"),
    (1626, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (1692, 67, "vertex", "Vec3*"),
    (2167, 73, "face_first", "ObjectFaceQuad*"),
    (2351, 73, "face_second", "ObjectFaceQuad*"),
)

WIBBLE_INVERT_HALFPIPE_PATH_USER_VAR_UPDATES = tuple(
    (
        function_name,
        "RegisterVariableSourceType",
        index,
        storage,
        variable_name,
        variable_type,
    )
    for function_name, specs in (
        ("initialize_wibble_path_template_pair", WIBBLE_PATH_LIFETIME_SPECS),
        ("initialize_invert_path_template_pair", INVERT_PATH_LIFETIME_SPECS),
        ("initialize_halfpipe_path_template_pair", HALFPIPE_PATH_LIFETIME_SPECS),
    )
    for index, storage, variable_name, variable_type in specs
)

# The Android and iOS BuildWibble, BuildInvert, and BuildHalfPipe bodies
# independently preserve the portable fixed-range control graph. Windows
# remains authoritative for the exact native definitions below: Wibble and
# Invert each have one interior counter fragmented across register and stack
# homes, while HalfPipe has distinct lead, tail, and curved-middle counters.
# The byte cursors deliberately remain int32_t offsets because forcing the
# pre-biased Windows expressions to PathTemplateSample* regresses the HLIL.
WIBBLE_INVERT_HALFPIPE_CONTROL_USER_VAR_UPDATES = (
    (
        "initialize_wibble_path_template_pair",
        "StackVariableSourceType",
        433,
        -64,
        "base_phase",
        "float",
    ),
    (
        "initialize_wibble_path_template_pair",
        "StackVariableSourceType",
        566,
        -64,
        "roll_phase",
        "float",
    ),
    (
        "initialize_halfpipe_path_template_pair",
        "StackVariableSourceType",
        105,
        -176,
        "lead_profile_phase",
        "float",
    ),
    (
        "initialize_halfpipe_path_template_pair",
        "StackVariableSourceType",
        400,
        -176,
        "tail_profile_phase",
        "float",
    ),
)

WIBBLE_CONTROL_LIFETIME_SPLITS = (
    (
        (
            ("0x428b34", "mlil", "RegisterVariableSourceType", 404, 73),
            ("0x428b36", "mlil", "StackVariableSourceType", 406, 8),
            ("0x428b42", "mlil_ssa", "RegisterVariableSourceType", 418, 73),
            ("0x428b42", "mlil_ssa", "StackVariableSourceType", 418, 8),
            ("0x428bb2", "mlil", "StackVariableSourceType", 530, 8),
            ("0x428cb1", "mlil", "RegisterVariableSourceType", 785, 73),
            ("0x428cc7", "mlil", "StackVariableSourceType", 807, 8),
        ),
        ("RegisterVariableSourceType", 404, 73),
        "interior_index",
        "int32_t",
    ),
    (
        (
            ("0x428b29", "mlil", "RegisterVariableSourceType", 393, 69),
            ("0x428b42", "mlil_ssa", "RegisterVariableSourceType", 418, 69),
            ("0x428ce2", "mlil", "RegisterVariableSourceType", 834, 69),
        ),
        ("RegisterVariableSourceType", 393, 69),
        "interior_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x428d13", "mlil", "RegisterVariableSourceType", 883, 73),
            ("0x428d20", "mlil_ssa", "RegisterVariableSourceType", 896, 73),
            ("0x428dcf", "mlil", "RegisterVariableSourceType", 1071, 73),
        ),
        ("RegisterVariableSourceType", 883, 73),
        "delta_index",
        "int32_t",
    ),
    (
        (
            ("0x428d1e", "mlil", "RegisterVariableSourceType", 894, 72),
            ("0x428d20", "mlil_ssa", "RegisterVariableSourceType", 896, 72),
            ("0x428dda", "mlil", "RegisterVariableSourceType", 1082, 72),
        ),
        ("RegisterVariableSourceType", 894, 72),
        "delta_sample_offset",
        "int32_t",
    ),
)

INVERT_CONTROL_LIFETIME_SPLITS = (
    (
        (
            ("0x4293e8", "mlil", "RegisterVariableSourceType", 408, 73),
            ("0x4293ea", "mlil", "StackVariableSourceType", 410, 8),
            ("0x4293f6", "mlil_ssa", "RegisterVariableSourceType", 422, 73),
            ("0x4293f6", "mlil_ssa", "StackVariableSourceType", 422, 8),
            ("0x429470", "mlil", "StackVariableSourceType", 544, -72),
            ("0x429542", "mlil", "RegisterVariableSourceType", 754, 73),
            ("0x429558", "mlil", "StackVariableSourceType", 776, 8),
        ),
        ("RegisterVariableSourceType", 408, 73),
        "interior_index",
        "int32_t",
    ),
    (
        (
            ("0x4293dd", "mlil", "RegisterVariableSourceType", 397, 69),
            ("0x4293f6", "mlil_ssa", "RegisterVariableSourceType", 422, 69),
            ("0x429573", "mlil", "RegisterVariableSourceType", 803, 69),
        ),
        ("RegisterVariableSourceType", 397, 69),
        "interior_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x429405", "mlil", "StackVariableSourceType", 437, 8),
            ("0x42948a", "mlil", "RegisterVariableSourceType", 570, 72),
        ),
        ("StackVariableSourceType", 437, 8),
        "curve_phase",
        "float",
    ),
    (
        (
            ("0x4295a4", "mlil", "RegisterVariableSourceType", 852, 73),
            ("0x4295b1", "mlil_ssa", "RegisterVariableSourceType", 865, 73),
            ("0x429660", "mlil", "RegisterVariableSourceType", 1040, 73),
        ),
        ("RegisterVariableSourceType", 852, 73),
        "delta_index",
        "int32_t",
    ),
    (
        (
            ("0x4295af", "mlil", "RegisterVariableSourceType", 863, 72),
            ("0x4295b1", "mlil_ssa", "RegisterVariableSourceType", 865, 72),
            ("0x42966b", "mlil", "RegisterVariableSourceType", 1051, 72),
        ),
        ("RegisterVariableSourceType", 863, 72),
        "delta_sample_offset",
        "int32_t",
    ),
)

HALFPIPE_CONTROL_LIFETIME_SPLITS = (
    (
        (
            ("0x429b68", "mlil", "StackVariableSourceType", 72, -156),
            ("0x429b6e", "mlil_ssa", "StackVariableSourceType", 78, -156),
            ("0x429c80", "mlil", "StackVariableSourceType", 352, -156),
        ),
        ("StackVariableSourceType", 72, -156),
        "lead_index",
        "int32_t",
    ),
    (
        (
            ("0x429b6c", "mlil", "RegisterVariableSourceType", 76, 72),
            ("0x429b6e", "mlil_ssa", "RegisterVariableSourceType", 78, 72),
            ("0x429c6f", "mlil", "RegisterVariableSourceType", 335, 72),
        ),
        ("RegisterVariableSourceType", 76, 72),
        "lead_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x429c8a", "mlil", "StackVariableSourceType", 362, -156),
            ("0x429c93", "mlil_ssa", "StackVariableSourceType", 371, -156),
            ("0x429dbd", "mlil", "StackVariableSourceType", 669, -156),
        ),
        ("StackVariableSourceType", 362, -156),
        "tail_index",
        "int32_t",
    ),
    (
        (
            ("0x429c8e", "mlil", "RegisterVariableSourceType", 366, 72),
            ("0x429c93", "mlil_ssa", "RegisterVariableSourceType", 371, 72),
            ("0x429db1", "mlil", "RegisterVariableSourceType", 657, 72),
        ),
        ("RegisterVariableSourceType", 366, 72),
        "tail_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x429dc7", "mlil", "StackVariableSourceType", 679, -156),
            ("0x429dec", "mlil_ssa", "StackVariableSourceType", 716, -156),
            ("0x429f4e", "mlil", "StackVariableSourceType", 1070, -156),
        ),
        ("StackVariableSourceType", 679, -156),
        "curve_index",
        "int32_t",
    ),
    (
        (
            ("0x429de3", "mlil", "RegisterVariableSourceType", 707, 69),
            ("0x429dec", "mlil_ssa", "RegisterVariableSourceType", 716, 69),
            ("0x429f41", "mlil", "RegisterVariableSourceType", 1057, 69),
        ),
        ("RegisterVariableSourceType", 707, 69),
        "curve_sample_offset",
        "int32_t",
    ),
    (
        (
            ("0x429f77", "mlil", "RegisterVariableSourceType", 1111, 73),
            ("0x429f84", "mlil_ssa", "RegisterVariableSourceType", 1124, 73),
            ("0x42a033", "mlil", "RegisterVariableSourceType", 1299, 73),
        ),
        ("RegisterVariableSourceType", 1111, 73),
        "delta_index",
        "int32_t",
    ),
    (
        (
            ("0x429f82", "mlil", "RegisterVariableSourceType", 1122, 72),
            ("0x429f84", "mlil_ssa", "RegisterVariableSourceType", 1124, 72),
            ("0x42a03e", "mlil", "RegisterVariableSourceType", 1310, 72),
        ),
        ("RegisterVariableSourceType", 1122, 72),
        "delta_sample_offset",
        "int32_t",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the proved sample, vector, mesh-vertex, and facequad "
            "lifetimes in the wibble, invert, and halfpipe constructors."
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
            "canonical wibble/invert/halfpipe ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_wibble_invert_halfpipe_path_owner_layouts",
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
                WIBBLE_INVERT_HALFPIPE_PATH_USER_VAR_UPDATES
                + WIBBLE_INVERT_HALFPIPE_CONTROL_USER_VAR_UPDATES
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
                        "initialize_wibble_path_template_pair",
                        WIBBLE_CONTROL_LIFETIME_SPLITS,
                    ),
                    (
                        "initialize_invert_path_template_pair",
                        INVERT_CONTROL_LIFETIME_SPLITS,
                    ),
                    (
                        "initialize_halfpipe_path_template_pair",
                        HALFPIPE_CONTROL_LIFETIME_SPLITS,
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
