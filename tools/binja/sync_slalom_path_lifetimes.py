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
    },
    "ObjectFaceQuad": {
        0x02: ("vertex_0", "uint16_t"),
        0x08: ("vertex_3", "uint16_t"),
        0x0C: ("texture_ref", "TextureRef*"),
        0x10: ("uv", "ObjectUv[4]"),
    },
}

# BuildSlalomA and BuildSlalomBigA have identical native sizes and MLIL
# variable identities. Their orientation loops retain the preceding forward
# vectors and reload the current sample for the cross product. The mesh writer
# reuses one complete face record for the front/back branch. Earlier current-
# sample and previous-row temporaries are deliberately omitted because their
# ownership is expressed through negative byte-relative addresses in this IL.
SLALOM_PATH_LIFETIME_SPECS = (
    (811, 66, "primary_forward", "Vec3*"),
    (929, 66, "primary_sample_cursor_reloaded", "PathTemplateSample*"),
    (1010, 68, "secondary_forward", "Vec3*"),
    (1130, 66, "secondary_sample_cursor_reloaded", "PathTemplateSample*"),
    (1504, 67, "primary_terminal_delta", "Vec3*"),
    (1593, 66, "secondary_terminal_delta", "Vec3*"),
    (1754, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (2163, 73, "face", "ObjectFaceQuad*"),
)

SLALOM_PATH_USER_VAR_UPDATES = tuple(
    (
        function_name,
        "RegisterVariableSourceType",
        index,
        storage,
        variable_name,
        variable_type,
    )
    for function_name in (
        "initialize_slalom_path_template_pair",
        "initialize_slalombig_path_template_pair",
    )
    for index, storage, variable_name, variable_type in SLALOM_PATH_LIFETIME_SPECS
)

SLALOM_CONTROL_USER_VAR_UPDATES = tuple(
    (
        function_name,
        "StackVariableSourceType",
        index,
        storage,
        variable_name,
        variable_type,
    )
    for function_name in (
        "initialize_slalom_path_template_pair",
        "initialize_slalombig_path_template_pair",
    )
    for index, storage, variable_name, variable_type in (
        (164, -68, "lead_sample_z", "float"),
        (499, -68, "curve_segments_f", "float"),
        (519, -76, "curve_phase", "float"),
        (546, -72, "center_distance_a", "float"),
    )
)

# The two Windows constructors are instruction-for-instruction homologues from
# their prologues through the mesh tail. Keep one set of reference addresses
# and translate them by function base; every definition still has to resolve
# to the exact per-function MLIL identity before the guarded replay can apply.
SLALOM_REFERENCE_BASE = 0x41F760
SLALOM_FUNCTION_BASES = (
    ("initialize_slalom_path_template_pair", 0x41F760),
    ("initialize_slalombig_path_template_pair", 0x4221F0),
)

# Android and iOS preserve the logical curve induction owner, the four-sample
# lead-in/out boundaries, and two independent absolute center distances.
# Windows implements the same graph but repeatedly reuses the width argument
# home as an integer counter and then as a converted float. Include the exact
# loop Phi definitions so downstream reads join the new owners rather than
# falling back to the incoming width parameter.
SLALOM_CONTROL_STACK_LIFETIME_SPLITS = (
    (
        (("0x41f793", "mlil", "StackVariableSourceType", 51, 8),),
        ("StackVariableSourceType", 51, 8),
        "segment_count_value",
        "int32_t",
    ),
    (
        (
            ("0x41f7ad", "mlil", "StackVariableSourceType", 77, 8),
            ("0x41f85d", "mlil", "StackVariableSourceType", 253, 8),
            ("0x41f7b3", "mlil_ssa", "StackVariableSourceType", 83, 8),
        ),
        ("StackVariableSourceType", 77, 8),
        "lead_sample_index",
        "int32_t",
    ),
    (
        (
            ("0x41f879", "mlil", "StackVariableSourceType", 281, 8),
            ("0x41f92b", "mlil", "StackVariableSourceType", 459, 8),
            ("0x41f889", "mlil_ssa", "StackVariableSourceType", 297, 8),
        ),
        ("StackVariableSourceType", 281, 8),
        "tail_sample_index",
        "int32_t",
    ),
    (
        (("0x41f8de", "mlil", "StackVariableSourceType", 382, 8),),
        ("StackVariableSourceType", 382, 8),
        "tail_sample_z",
        "float",
    ),
    (
        (
            ("0x41f940", "mlil", "StackVariableSourceType", 480, 8),
            ("0x41fc33", "mlil", "StackVariableSourceType", 1235, 8),
            ("0x41f957", "mlil_ssa", "StackVariableSourceType", 503, 8),
        ),
        ("StackVariableSourceType", 480, 8),
        "curve_index",
        "int32_t",
    ),
    (
        (("0x41f99f", "mlil", "StackVariableSourceType", 575, 8),),
        ("StackVariableSourceType", 575, 8),
        "center_distance_b",
        "float",
    ),
    (
        (("0x41fa20", "mlil", "StackVariableSourceType", 704, 8),),
        ("StackVariableSourceType", 704, 8),
        "curve_sample_index",
        "int32_t",
    ),
    (
        (("0x41fa31", "mlil", "StackVariableSourceType", 721, 8),),
        ("StackVariableSourceType", 721, 8),
        "curve_sample_z",
        "float",
    ),
)

# Windows owns a mesh tail absent from the Android and iOS bodies. Raw Windows
# instructions prove that VC6 reuses the dead curve-count and width argument
# homes for mesh-column and UV values. Split only those definition-bounded
# lifetimes so the authored constructor inputs do not appear to mutate into
# pointers, loop counters, or floats.
SLALOM_MESH_STACK_LIFETIME_SPLITS = (
    (
        (("0x41fdf4", "mlil", "StackVariableSourceType", 1684, -64),),
        ("StackVariableSourceType", 1684, -64),
        "mesh_facequads",
        "ObjectFaceQuad*",
    ),
    (
        (("0x41fdfb", "mlil", "StackVariableSourceType", 1691, -72),),
        ("StackVariableSourceType", 1691, -72),
        "mesh_vertices",
        "Vec3*",
    ),
    (
        (
            ("0x41fe12", "mlil", "StackVariableSourceType", 1714, 4),
            ("0x41ff1a", "mlil", "StackVariableSourceType", 1978, 4),
            ("0x41fe20", "mlil_ssa", "StackVariableSourceType", 1728, 4),
        ),
        ("StackVariableSourceType", 1714, 4),
        "mesh_column",
        "int32_t",
    ),
    (
        (
            ("0x41fe16", "mlil", "StackVariableSourceType", 1718, 8),
            ("0x41ff1e", "mlil", "StackVariableSourceType", 1982, 8),
            ("0x41fe20", "mlil_ssa", "StackVariableSourceType", 1728, 8),
        ),
        ("StackVariableSourceType", 1718, 8),
        "mesh_width_cells",
        "int32_t",
    ),
    (
        (
            ("0x41ff4e", "mlil", "StackVariableSourceType", 2030, 4),
            ("0x420133", "mlil", "StackVariableSourceType", 2515, 4),
            ("0x41ff8d", "mlil_ssa", "StackVariableSourceType", 2093, 4),
        ),
        ("StackVariableSourceType", 2030, 4),
        "face_column_for_uv",
        "int32_t",
    ),
    (
        (("0x41ff68", "mlil", "StackVariableSourceType", 2056, 8),),
        ("StackVariableSourceType", 2056, 8),
        "v0_index",
        "int32_t",
    ),
    (
        (("0x41ff71", "mlil", "StackVariableSourceType", 2065, -68),),
        ("StackVariableSourceType", 2065, -68),
        "v1_index",
        "int32_t",
    ),
    (
        (("0x41ff7b", "mlil", "StackVariableSourceType", 2075, 8),),
        ("StackVariableSourceType", 2075, 8),
        "v0",
        "float",
    ),
    (
        (("0x41ff89", "mlil", "StackVariableSourceType", 2089, -76),),
        ("StackVariableSourceType", 2089, -76),
        "v1",
        "float",
    ),
    (
        (("0x41ff96", "mlil", "StackVariableSourceType", 2102, -68),),
        ("StackVariableSourceType", 2102, -68),
        "u1_index",
        "int32_t",
    ),
    (
        (
            ("0x41ff9a", "mlil", "StackVariableSourceType", 2106, -72),
            ("0x420120", "mlil", "StackVariableSourceType", 2496, -72),
            ("0x41ff8d", "mlil_ssa", "StackVariableSourceType", 2093, -72),
            ("0x41ffbc", "mlil_ssa", "StackVariableSourceType", 2140, -72),
        ),
        ("StackVariableSourceType", 2106, -72),
        "face_pass",
        "int32_t",
    ),
    (
        (("0x41ffa4", "mlil", "StackVariableSourceType", 2116, 4),),
        ("StackVariableSourceType", 2116, 4),
        "u0",
        "float",
    ),
    (
        (("0x41ffb2", "mlil", "StackVariableSourceType", 2130, -80),),
        ("StackVariableSourceType", 2130, -80),
        "u1",
        "float",
    ),
)

# The two face-winding arms both reuse ECX after testing the face pass. Their
# 16-bit width loads are a separate `width + 1` lifetime; without this split,
# naming the pass Phi makes the decompiler falsely show the pass counter itself
# acquiring the path width.
SLALOM_FACE_REGISTER_LIFETIME_SPLITS = (
    (
        (
            ("0x41ffe1", "mlil", "RegisterVariableSourceType", 2177, 67),
            ("0x41ffe7", "mlil", "RegisterVariableSourceType", 2183, 67),
            ("0x420096", "mlil", "RegisterVariableSourceType", 2358, 67),
            ("0x42009a", "mlil", "RegisterVariableSourceType", 2362, 67),
        ),
        ("RegisterVariableSourceType", 2177, 67),
        "face_width_plus_one",
        "int32_t",
    ),
)


def translated_definitions(
    function_base: int,
    definitions: tuple[tuple[str, str, str, int, int], ...],
) -> tuple[tuple[str, str, str, int, int], ...]:
    delta = function_base - SLALOM_REFERENCE_BASE
    return tuple(
        (
            f"{int(address, 0) + delta:#x}",
            view,
            source_type,
            index,
            storage,
        )
        for address, view, source_type, index, storage in definitions
    )


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the basis-vector, terminal-delta, sample, and facequad "
            "lifetimes shared by the slalom path constructors."
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
            "canonical slalom ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_slalom_path_owner_layouts",
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
            updates=(SLALOM_PATH_USER_VAR_UPDATES + SLALOM_CONTROL_USER_VAR_UPDATES),
        ),
    ]
    operations.extend(
        apply_split_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=tuple(
                (
                    function_name,
                    translated_definitions(function_base, definitions),
                    target_var,
                    variable_name,
                    variable_type,
                )
                for function_name, function_base in SLALOM_FUNCTION_BASES
                for definitions, target_var, variable_name, variable_type in (
                    SLALOM_CONTROL_STACK_LIFETIME_SPLITS
                    + SLALOM_MESH_STACK_LIFETIME_SPLITS
                    + SLALOM_FACE_REGISTER_LIFETIME_SPLITS
                )
            ),
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
