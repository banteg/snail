#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import apply_proto_updates, apply_struct_field_updates, emit_summary, types_declare


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_object_render_types.h"

OBJECT_FIELDS = (
    ("0x10", "flags", "uint32_t"),
    ("0x2c", "vertex_count", "int32_t"),
    ("0x38", "vertices", "Vec3*"),
    ("0x3c", "copied_vertices", "Vec3*"),
    ("0x54", "facequad_count", "int32_t"),
    ("0x5c", "facequads", "ObjectFaceQuad*"),
    ("0x60", "facequad_normals", "Vec3*"),
    ("0xbc", "animation", "ObjectAnimation*"),
    ("0xc0", "render_buffers", "ObjectRenderBuffers*"),
    ("0xc4", "grouped_vertex_count", "int32_t"),
)

PROTO_UPDATES = (
    (
        "request_object_animation",
        "ObjectAnimation* __thiscall request_object_animation(Object* object, int32_t keyframe_count, void* keyframes, float progress_step, uint16_t flags)",
    ),
    (
        "refresh_object_vertex_buffer",
        "void __cdecl refresh_object_vertex_buffer(Object* object)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the narrow object render/animation type slice to the active Binary Ninja target."
    )
    parser.add_argument("--target", default="active", help="Binary Ninja target selector.")
    parser.add_argument("--header", type=Path, default=DEFAULT_HEADER_PATH, help="Narrow Binary Ninja type header.")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations: list[dict[str, object]] = []
    operations.append(types_declare(REPO_ROOT, target=args.target, header_path=header_path))
    operations.extend(apply_struct_field_updates(REPO_ROOT, target=args.target, struct_name="Object", updates=OBJECT_FIELDS))
    operations.extend(apply_proto_updates(REPO_ROOT, target=args.target, updates=PROTO_UPDATES))
    return emit_summary(repo_root=REPO_ROOT, target=args.target, header_path=header_path, operations=operations)


if __name__ == "__main__":
    sys.exit(main())
