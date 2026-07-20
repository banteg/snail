#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import (
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
        0x9C: ("lateral_scale", "float"),
    },
    "ObjectFaceQuad": {
        0x02: ("vertex_0", "uint16_t"),
        0x08: ("vertex_3", "uint16_t"),
        0x0C: ("texture_ref", "TextureRef*"),
        0x10: ("uv", "ObjectUv[4]"),
    },
}

# BuildWorm derives both right and corrected-up vectors from each normalized
# forward vector, so each side reloads its sample cursor twice. Keep those
# complete sample owners plus the terminal, mesh, and face lifetimes whose
# transactional preview stayed at zero __offset expressions. The byte-biased
# forward-vector candidates at 713 and 912 are intentionally omitted: typing
# them introduced eight backward offsets in the adjacent position reads.
WORM_PATH_LIFETIME_SPECS = (
    (668, 68, "primary_up", "Vec3*"),
    (788, 66, "primary_sample_cursor_first", "PathTemplateSample*"),
    (819, 66, "primary_sample_cursor_second", "PathTemplateSample*"),
    (870, 67, "secondary_up", "Vec3*"),
    (985, 66, "secondary_sample_cursor_first", "PathTemplateSample*"),
    (1017, 66, "secondary_sample_cursor_second", "PathTemplateSample*"),
    (1351, 68, "primary_terminal_delta", "Vec3*"),
    (1442, 66, "secondary_terminal_delta", "Vec3*"),
    (1663, 66, "primary_mesh_sample", "PathTemplateSample*"),
    (1754, 66, "primary_mesh_sample_reloaded", "PathTemplateSample*"),
    (1848, 66, "primary_position", "Vec3*"),
    (2008, 66, "vertex", "Vec3*"),
    (2091, 66, "previous_row_vertex", "Vec3*"),
    (2094, 68, "terminal_vertex", "Vec3*"),
    (2384, 73, "face", "ObjectFaceQuad*"),
)

WORM_PATH_USER_VAR_UPDATES = tuple(
    (
        "initialize_worm_path_template_pair",
        "RegisterVariableSourceType",
        index,
        storage,
        variable_name,
        variable_type,
    )
    for index, storage, variable_name, variable_type in WORM_PATH_LIFETIME_SPECS
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the proved basis, terminal, mesh, vertex, and face "
            "lifetimes in the worm path constructor."
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
            "canonical worm ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_worm_path_owner_layouts",
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
            updates=WORM_PATH_USER_VAR_UPDATES,
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
