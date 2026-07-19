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
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_object_render_types.h"

EXPECTED_TYPE_WIDTHS = {
    "ObjectAnimationFrame": 0x08,
    "ObjectAnimation": 0x14,
    "XAnimationKeyframe": 0x80,
    "Object": 0xDC,
}

EXPECTED_STRUCT_FIELDS = {
    "ObjectAnimationFrame": {
        0x00: ("vertices", "Vec3*"),
        0x04: ("facequad_normals", "Vec3*"),
    },
    "ObjectAnimation": {
        0x00: ("flags", "ObjectAnimationFlags"),
        0x04: ("generated_frame_count", "int32_t"),
        0x08: ("frames", "ObjectAnimationFrame**"),
        0x0C: ("progress", "float"),
        0x10: ("progress_step", "float"),
    },
    "XAnimationKeyframe": {
        0x24: ("object", "Object*"),
        0x7C: ("frame_number", "int32_t"),
    },
    "Object": {
        0x2C: ("vertex_count", "int32_t"),
        0x38: ("vertices", "Vec3*"),
        0x54: ("facequad_count", "int32_t"),
        0x60: ("facequad_normals", "Vec3*"),
        0xBC: ("animation", "ObjectAnimation*"),
    },
}

# RequestAnim retains a graph rooted at Object::animation: one frame-pointer
# bank, one ObjectAnimationFrame per generated frame, and two Vec3 banks per
# frame. Binary Ninja already knows the canonical owner layouts but repeatedly
# flattens the allocation results and frame reloads to void*/char*. Replay only
# the exact physical lifetimes that carry whole owners or whole Vec3 banks;
# interior byte cursors used by the copy/interpolation loops stay inferred.
OBJECT_ANIMATION_USER_VAR_UPDATES = (
    (
        "request_object_animation",
        "RegisterVariableSourceType",
        29,
        71,
        "validation_object",
        "Object*",
    ),
    (
        "request_object_animation",
        "RegisterVariableSourceType",
        280,
        66,
        "allocated_frame",
        "ObjectAnimationFrame*",
    ),
    (
        "request_object_animation",
        "RegisterVariableSourceType",
        312,
        66,
        "allocated_vertices",
        "Vec3*",
    ),
    (
        "request_object_animation",
        "RegisterVariableSourceType",
        331,
        67,
        "frame_for_vertices",
        "ObjectAnimationFrame*",
    ),
    (
        "request_object_animation",
        "RegisterVariableSourceType",
        346,
        66,
        "allocated_facequad_normals",
        "Vec3*",
    ),
    (
        "request_object_animation",
        "RegisterVariableSourceType",
        363,
        67,
        "frame_for_facequad_normals",
        "ObjectAnimationFrame*",
    ),
    (
        "request_object_animation",
        "RegisterVariableSourceType",
        539,
        66,
        "frame_vertices",
        "Vec3*",
    ),
    (
        "request_object_animation",
        "RegisterVariableSourceType",
        566,
        66,
        "next_object",
        "Object*",
    ),
    (
        "request_object_animation",
        "RegisterVariableSourceType",
        572,
        67,
        "next_vertices",
        "Vec3*",
    ),
    (
        "request_object_animation",
        "RegisterVariableSourceType",
        671,
        67,
        "output_frame",
        "ObjectAnimationFrame*",
    ),
    (
        "request_object_animation",
        "RegisterVariableSourceType",
        678,
        66,
        "output_vertices",
        "Vec3*",
    ),
    (
        "request_object_animation",
        "RegisterVariableSourceType",
        734,
        67,
        "installed_frame_for_vertices",
        "ObjectAnimationFrame*",
    ),
    (
        "request_object_animation",
        "RegisterVariableSourceType",
        745,
        67,
        "installed_frame_for_normals",
        "ObjectAnimationFrame*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay only the retained object-animation graph lifetimes in "
            "request_object_animation."
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
        help="Header documenting the canonical object-animation ownership graph.",
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
            "canonical object-animation ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_object_animation_owner_layouts",
        "status": "verified",
        "types": tuple(EXPECTED_TYPE_WIDTHS),
    }


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations = [
        verify_owner_layouts(args.target),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=OBJECT_ANIMATION_USER_VAR_UPDATES,
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
