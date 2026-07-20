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
            updates=SLALOMDOUBLE_P_PATH_USER_VAR_UPDATES,
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
