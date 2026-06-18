#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import (
    apply_data_var_updates,
    apply_proto_updates,
    apply_struct_field_updates,
    apply_symbol_updates,
    emit_summary,
    types_declare,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_object_render_types.h"

OBJECT_FIELDS = (
    ("0x08", "toon_vertices", "Vec3*"),
    ("0x0c", "toon_facequad_normals", "ObjectToonFaceQuadNormal*"),
    ("0x10", "flags", "uint32_t"),
    ("0x14", "blend_mode", "int32_t"),
    ("0x18", "override_texture_ref", "TextureRef*"),
    ("0x2c", "vertex_count", "int32_t"),
    ("0x38", "vertices", "Vec3*"),
    ("0x3c", "copied_vertices", "Vec3*"),
    ("0x40", "field_40", "int32_t"),
    ("0x44", "vertex_normals", "Vec3*"),
    ("0x48", "vertex_colours", "Color4f*"),
    ("0x54", "facequad_count", "int32_t"),
    ("0x58", "facequad_capacity", "int32_t"),
    ("0x5c", "facequads", "ObjectFaceQuad*"),
    ("0x60", "facequad_normals", "Vec3*"),
    ("0x64", "texture_group_count", "int32_t"),
    ("0x68", "texture_group_capacity", "int32_t"),
    ("0x6c", "texture_group_ends", "int32_t*"),
    ("0x70", "edge_count", "int32_t"),
    ("0x74", "edges", "ObjectToonEdge*"),
    ("0x80", "distort", "ObjectDistort"),
    ("0x94", "bounding_radius", "float"),
    ("0xa4", "bounds_min", "Vec3"),
    ("0xb0", "bounds_max", "Vec3"),
    ("0xbc", "animation", "ObjectAnimation*"),
    ("0xc0", "render_buffers", "ObjectRenderBuffers*"),
    ("0xc4", "grouped_vertex_count", "int32_t"),
    ("0xc8", "index_buffer", "ObjectIndexBuffer*"),
    ("0xcc", "group_index_starts", "int32_t*"),
    ("0xd0", "group_texture_refs", "TextureRef**"),
    ("0xd4", "group_primitive_counts", "int32_t*"),
    ("0xd8", "toon_index_buffer", "ObjectIndexBuffer*"),
)

SYMBOL_UPDATES = (
    ("0x4f7458", "g_direct3d_renderer"),
    ("0x5000fc", "g_object_index_buffer_factory"),
    ("0x5031bc", "g_object_grouped_vertex_cursor"),
    ("0x5031c4", "g_object_grouped_vertex_scratch"),
    ("0x5031d8", "g_object_texture_transform_matrix"),
)

FUNCTION_SYMBOL_UPDATES = (
    ("0x4114b0", "create_object_vertex_buffer_resource"),
    ("0x4115d0", "create_object_index_buffer_resource"),
    ("0x414270", "direct3d_renderer_set_fullscreen_mode"),
)

DATA_VAR_UPDATES = (
    ("0x5031bc", "int32_t"),
    ("0x5031c4", "ObjectGroupedVertex*"),
    ("0x5031d8", "TransformMatrix"),
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
    operations.extend(apply_symbol_updates(REPO_ROOT, target=args.target, updates=SYMBOL_UPDATES, kind="data"))
    operations.extend(apply_symbol_updates(REPO_ROOT, target=args.target, updates=FUNCTION_SYMBOL_UPDATES, kind="function"))
    operations.extend(apply_data_var_updates(REPO_ROOT, target=args.target, updates=DATA_VAR_UPDATES))
    operations.extend(apply_proto_updates(REPO_ROOT, target=args.target, updates=PROTO_UPDATES))
    return emit_summary(repo_root=REPO_ROOT, target=args.target, header_path=header_path, operations=operations)


if __name__ == "__main__":
    sys.exit(main())
