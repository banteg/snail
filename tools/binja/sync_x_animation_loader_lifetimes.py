#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import (
    apply_direct_proto_update,
    apply_user_var_updates,
    current_struct_fields_batch,
    current_type_widths,
    emit_summary,
)
from _target import DEFAULT_TARGET


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_object_render_types.h"

X_ANIMATION_LOADER_PROTOTYPE = (
    "void __thiscall load_x_animation_clip("
    "DirectXLoader* loader, char* mesh_name, Object* object)"
)

EXPECTED_TYPE_WIDTHS = {
    "XAnimationKeyframe": 0x80,
    "Object": 0xDC,
    "DuplicateVertices": 0x08,
    "DirectXLoader": 0x5E10,
}

EXPECTED_STRUCT_FIELDS = {
    "XAnimationKeyframe": {
        0x24: ("object", "Object*"),
        0x7C: ("frame_number", "int32_t"),
    },
    "Object": {
        0x10: ("flags", "ObjectFlag"),
        0xBC: ("animation", "ObjectAnimation*"),
    },
    "DuplicateVertices": {
        0x00: ("active_count", "int32_t"),
        0x04: ("records", "DuplicateVertexRecord*"),
    },
    "DirectXLoader": {
        0x00: ("animation_bytes", "char*"),
        0x5E08: ("duplicate_vertices", "DuplicateVertices"),
    },
}

# Native owns two adjacent frame buffers: a 0x80-byte "Anim:%s" tag and the
# 0x100-byte mesh path pattern passed to enumeration. The remaining stable
# stack slots carry the one shared parser cursor, saved delimiter byte,
# animation progress step, keyframe count, and allocated keyframe bank.
#
# Four register lifetimes are also ownership-bearing. ESI walks the fixed
# 0x80-byte directory-name records, EBP counts keyframes, EDI points at the
# current keyframe's frame_number field, and the later ESI/EBX pair retains the
# bounded animation block and its AnimEnd delimiter. The latter are borrowed
# pointers into DirectXLoader::animation_bytes; none owns or frees storage.
X_ANIMATION_LOADER_USER_VAR_UPDATES = (
    (
        "load_x_animation_clip",
        "StackVariableSourceType",
        0,
        -404,
        "cursor",
        "char*",
    ),
    (
        "load_x_animation_clip",
        "StackVariableSourceType",
        511,
        -397,
        "saved_end_char",
        "char",
    ),
    (
        "load_x_animation_clip",
        "StackVariableSourceType",
        575,
        -396,
        "progress_step",
        "float",
    ),
    (
        "load_x_animation_clip",
        "StackVariableSourceType",
        0,
        -392,
        "keyframe_count",
        "int32_t",
    ),
    (
        "load_x_animation_clip",
        "StackVariableSourceType",
        223,
        -388,
        "keyframes",
        "XAnimationKeyframe*",
    ),
    (
        "load_x_animation_clip",
        "StackVariableSourceType",
        0,
        -384,
        "animation_tag",
        "char[0x80]",
    ),
    (
        "load_x_animation_clip",
        "StackVariableSourceType",
        0,
        -256,
        "path_pattern",
        "char[0x100]",
    ),
    (
        "load_x_animation_clip",
        "RegisterVariableSourceType",
        209,
        66,
        "allocated_keyframes",
        "XAnimationKeyframe*",
    ),
    (
        "load_x_animation_clip",
        "RegisterVariableSourceType",
        214,
        67,
        "loop_keyframe_count",
        "int32_t",
    ),
    (
        "load_x_animation_clip",
        "RegisterVariableSourceType",
        221,
        71,
        "keyframe_index",
        "int32_t",
    ),
    (
        "load_x_animation_clip",
        "RegisterVariableSourceType",
        241,
        72,
        "mesh_path",
        "char*",
    ),
    (
        "load_x_animation_clip",
        "RegisterVariableSourceType",
        246,
        73,
        "frame_number_cursor",
        "int32_t*",
    ),
    (
        "load_x_animation_clip",
        "RegisterVariableSourceType",
        443,
        72,
        "animation_block",
        "char*",
    ),
    (
        "load_x_animation_clip",
        "RegisterVariableSourceType",
        467,
        69,
        "animation_end",
        "char*",
    ),
    (
        "load_x_animation_clip",
        "RegisterVariableSourceType",
        595,
        73,
        "mode_flags",
        "int32_t",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay load_x_animation_clip's authored member ABI, keyframe "
            "bank, parser cursors, and adjacent frame-buffer lifetimes."
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
        help="Header documenting the canonical DirectXLoader/Object owners.",
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
            "canonical X-animation loader ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_x_animation_loader_owner_layouts",
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
        apply_direct_proto_update(
            REPO_ROOT,
            target=args.target,
            identifier="load_x_animation_clip",
            prototype=X_ANIMATION_LOADER_PROTOTYPE,
        ),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=X_ANIMATION_LOADER_USER_VAR_UPDATES,
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
