#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import (
    apply_split_away_user_var_update,
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

# ECX first carries the terminal center-X bits copied between the fixed final
# samples, then is reused by the curve loop for a previous transform and a
# rotate helper result. Split those later definitions away before typing the
# residual scalar; otherwise Binary Ninja renders the float as a matrix pointer.
CAGE2_TERMINAL_CENTER_DETACHED_DEFINITIONS = (
    ("0x42eb3f", "mlil", "RegisterVariableSourceType", 1055, 67),
    ("0x42eb26", "mlil", "RegisterVariableSourceType", 1030, 67),
)

CAGE2_TERMINAL_CENTER_VAR = (
    "RegisterVariableSourceType",
    329,
    67,
)

# Keep only complete owners whose transactional preview did not increase the
# constructor's thirteen pre-existing fixed-terminal-sample __offset views.
# The byte-biased forward pointers at 659/880 add eight offsets, while the
# terminal mesh current-sample pointer at 1685 adds six; all three are omitted.
CAGE2_PATH_LIFETIME_SPECS = (
    (614, 66, "primary_up", "Vec3*"),
    (732, 66, "primary_sample_cursor_reloaded", "PathTemplateSample*"),
    (835, 66, "secondary_up", "Vec3*"),
    (953, 66, "secondary_sample_cursor_reloaded", "PathTemplateSample*"),
    (1352, 67, "primary_terminal_delta", "Vec3*"),
    (1441, 66, "secondary_terminal_delta", "Vec3*"),
    (1600, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (1662, 66, "vertex", "Vec3*"),
    (2010, 71, "face_first", "ObjectFaceQuad*"),
    (2189, 71, "face_second", "ObjectFaceQuad*"),
)

CAGE2_PATH_USER_VAR_UPDATES = tuple(
    (
        "initialize_cage2_path_template_pair",
        "RegisterVariableSourceType",
        index,
        storage,
        variable_name,
        variable_type,
    )
    for index, storage, variable_name, variable_type in CAGE2_PATH_LIFETIME_SPECS
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the terminal-center split plus proved basis, terminal, "
            "mesh, vertex, and face lifetimes in the Cage2 constructor."
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
            "canonical Cage2 ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_cage2_path_owner_layouts",
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
        apply_split_away_user_var_update(
            REPO_ROOT,
            target=args.target,
            identifier="initialize_cage2_path_template_pair",
            detached_definitions=CAGE2_TERMINAL_CENTER_DETACHED_DEFINITIONS,
            residual_var=CAGE2_TERMINAL_CENTER_VAR,
            variable_name="terminal_center_x",
            variable_type="float",
        )
    )
    operations.extend(
        apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=CAGE2_PATH_USER_VAR_UPDATES,
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
