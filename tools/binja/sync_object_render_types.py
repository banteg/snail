#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_data_var_updates,
    apply_direct_proto_update,
    apply_symbol_removals,
    apply_struct_and_proto_updates,
    apply_symbol_updates,
    emit_summary,
    types_declare_if_changed,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_object_render_types.h"

GAME_ROOT_FIELDS = (
    ("0x48e00", "directx_loader", "DirectXLoader"),
)

TEXTURE_REF_FIELDS = (
    ("0x00", "flags", "TextureRefFlags"),
    ("0x04", "loaded_width", "int32_t"),
    ("0x08", "loaded_height", "int32_t"),
    ("0x0c", "name", "char[0x80]"),
    ("0x8c", "slot_index", "int32_t"),
    ("0x90", "frame_count", "int32_t"),
    ("0x94", "frame_progress_step", "float"),
    ("0x98", "texture_ref", "void*"),
    ("0xa0", "mip_levels", "int32_t"),
)

OBJECT_FIELDS = (
    ("0x08", "toon_vertices", "Vec3*"),
    ("0x0c", "toon_facequad_normals", "ObjectToonFaceQuadNormal*"),
    ("0x10", "flags", "ObjectFlag"),
    ("0x14", "blend_mode", "int32_t"),
    ("0x18", "override_texture_ref", "TextureRef*"),
    ("0x1c", "heightmap_sample_count", "int32_t"),
    ("0x24", "heightmap_sample_divisor", "float"),
    ("0x28", "heightmap_sample_scale", "float"),
    ("0x2c", "vertex_count", "int32_t"),
    ("0x38", "vertices", "Vec3*"),
    ("0x3c", "copied_vertices", "Vec3*"),
    ("0x40", "field_40", "int32_t"),
    ("0x44", "vertex_normals", "Vec3*"),
    ("0x48", "vertex_colours", "tColour*"),
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

FRAME_SEQUENCE_FIELDS = (
    ("0x00", "object", "Object"),
    ("0xdc", "sequence_flags", "int32_t"),
    ("0xe0", "current_frame_index", "int32_t"),
    ("0xe4", "phase", "float"),
    ("0xe8", "phase_step", "float"),
    ("0xec", "current_texture_ref", "TextureRef*"),
)

OBJECT_LIST_FIELDS = (
    ("0x00", "count", "int32_t"),
    ("0x04", "capacity", "int32_t"),
    ("0x08", "objects", "Object*"),
)

DIRECT3D_RENDERER_FIELDS = (
    ("0x0000", "vertex_buffer_factory", "VertexBufferFactory"),
    ("0x8ca4", "index_buffer_factory", "IndexBufferFactory"),
    ("0xbb88", "renderer_state", "ObjectRenderBuffers*"),
    ("0xbb8c", "device_initialized", "uint8_t"),
    ("0xbb90", "d3d", "Direct3D8*"),
    ("0xbb94", "device", "Direct3DDevice8*"),
    ("0xbb98", "present", "D3DPresentParameters"),
    ("0xbbcc", "device_caps", "D3DDeviceCaps8"),
    ("0xbca0", "display_format", "uint32_t"),
    ("0xbca4", "requested_width", "uint32_t"),
    ("0xbca8", "requested_height", "uint32_t"),
    ("0xbcac", "create_device_flags", "uint32_t"),
    ("0xbcb0", "unknown_bcb0", "uint32_t"),
    ("0xbcb4", "unknown_bcb4", "uint32_t"),
    ("0xbcb8", "depth_stencil_format", "uint32_t"),
    ("0xbcbc", "multisample_type", "uint32_t"),
)

SYMBOL_UPDATES = (
    ("0x4a3c40", "g_backdrop_raise_first_vertex_index"),
    ("0x4a3c44", "g_backdrop_raise_second_vertex_index"),
    ("0x4a3ce0", "g_backdrop_corner_vertex_indices"),
    ("0x4b7648", "g_object_list"),
    ("0x4f7450", "g_render_triangle_count"),
    ("0x4f7454", "g_render_successful_primitive_count"),
    ("0x4f7458", "g_direct3d_renderer"),
    ("0x50316c", "g_render_projection_param_b"),
    ("0x503170", "g_draw_primitive_call_count"),
    ("0x503174", "g_current_texture_ref"),
    ("0x5031b8", "g_render_camera_source_matrix"),
    ("0x5031bc", "g_object_grouped_vertex_cursor"),
    ("0x5031c0", "g_texture_bind_call_count"),
    ("0x5031c4", "g_object_grouped_vertex_scratch"),
    ("0x5031c8", "g_d3d_texture_slots"),
    ("0x5031cc", "g_render_projection_near_z"),
    ("0x5031d0", "g_render_projection_far_z"),
    ("0x5031d4", "g_render_projection_param_a"),
    ("0x5031d8", "g_object_texture_transform_matrix"),
    ("0x503218", "g_render_camera_view_matrix"),
    ("0x503260", "g_object_render_pass_filter"),
    ("0x503300", "g_object_edge_build_edges"),
    ("0x503318", "g_object_edge_build_count"),
)

SYMBOL_REMOVALS = (
    ("0x5000fc", "g_object_index_buffer_factory"),
)

FUNCTION_SYMBOL_UPDATES = (
    ("0x405640", "load_x_mesh"),
    ("0x41a0b0", "initialize_textured_backdrop_quad"),
    ("0x41a170", "raise_backdrop_quad_edge_pair"),
    ("0x41a1c0", "initialize_backdrop_slice_quad"),
    ("0x41a290", "initialize_backdrop_corner_quad"),
    ("0x41a4d0", "initialize_backdrop_tile_quad"),
    ("0x41aa30", "initialize_object_distort"),
    ("0x41aa50", "apply_distort_to_object"),
    ("0x4114b0", "create_vertex_buffer"),
    ("0x4115d0", "create_index_buffer"),
    ("0x411630", "initialize_direct3d_renderer_defaults"),
    ("0x4116f0", "release_direct3d_renderer_resources"),
    ("0x411700", "direct3d_renderer_set_cull_mode"),
    ("0x411730", "initialize_d3d8_device"),
    ("0x4118b0", "reset_direct3d_render_state"),
    ("0x411960", "release_direct3d_device_interfaces"),
    ("0x411d70", "release_global_direct3d_renderer_resources"),
    ("0x411fa0", "render_camera"),
    ("0x4129c0", "initialize_direct3d_renderer"),
    ("0x4129f0", "set_cull_mode"),
    ("0x412d00", "set_blend_mode"),
    ("0x412e50", "set_immediate_blend_mode"),
    ("0x413030", "draw_textured_quad_immediate"),
    ("0x413520", "present_backbuffer"),
    ("0x414260", "set_fullscreen_mode"),
    ("0x414270", "direct3d_renderer_set_fullscreen_mode"),
    ("0x4143c0", "restore_texture_ref_stage_states"),
    ("0x414500", "bind_texture_ref"),
    ("0x414600", "query_direct3d_device_caps"),
    ("0x414650", "reset_render_counters"),
    ("0x413bb0", "get_or_append_object_texture_group_vertex"),
    ("0x413d50", "build_object_texture_group_buffers"),
    ("0x419fd0", "sort_object_faces_by_texture_group"),
    ("0x42f930", "request_object_texture_groups"),
    ("0x42f990", "initialize_object_list"),
    ("0x42f9e0", "build_all_objects"),
    ("0x42fad0", "add_object_to_list"),
    ("0x42fb10", "calc_object_bounding_box"),
    ("0x42fcb0", "calc_object_facequad_normals"),
    ("0x4303f0", "calc_object_texture_groups"),
    ("0x4305a0", "add_object_edge"),
    ("0x4308b0", "calc_object_edges"),
    ("0x430a30", "rotate_object_facequad_uv_pairs"),
    ("0x450314", "build_perspective_projection_matrix"),
    ("0x451ad9", "build_camera_view_matrix"),
)

DATA_VAR_UPDATES = (
    ("0x4a3c40", "int32_t"),
    ("0x4a3c44", "int32_t"),
    ("0x4a3ce0", "int32_t[4]"),
    ("0x4b7648", "ObjectList"),
    ("0x4f7450", "int32_t"),
    ("0x4f7454", "int32_t"),
    ("0x4f7458", "Direct3DRenderer"),
    ("0x50316c", "float"),
    ("0x503170", "int32_t"),
    ("0x503174", "TextureRef*"),
    ("0x5031b8", "TransformMatrix*"),
    ("0x5031bc", "int32_t"),
    ("0x5031c0", "int32_t"),
    ("0x5031c4", "ObjectGroupedVertex*"),
    ("0x5031c8", "Direct3DTexture8**"),
    ("0x5031cc", "float"),
    ("0x5031d0", "float"),
    ("0x5031d4", "float"),
    ("0x5031d8", "TransformMatrix"),
    ("0x503218", "TransformMatrix*"),
    ("0x503260", "uint8_t"),
    ("0x503300", "ObjectToonEdge*"),
    ("0x503318", "int32_t"),
)

# `load_object_definition` is declared in the canonical header, but the live
# database's pre-existing zero-argument user type rejects both `proto set` and
# direct Function.set_user_type updates. Keep it out of the repeatable sync
# until that Binary Ninja function-type defect is cleared.
PROTO_UPDATES = (
    (
        "initialize_textured_backdrop_quad",
        "void __cdecl initialize_textured_backdrop_quad(Object* object, char* texture_path, float x_offset)",
    ),
    (
        "raise_backdrop_quad_edge_pair",
        "void __cdecl raise_backdrop_quad_edge_pair(int32_t selector, Object* object)",
    ),
    (
        "initialize_backdrop_slice_quad",
        "void __cdecl initialize_backdrop_slice_quad(Object* object, char* texture_path, float x_offset)",
    ),
    (
        "initialize_backdrop_corner_quad",
        "void __cdecl initialize_backdrop_corner_quad(int32_t selector, Object* object, char* texture_path)",
    ),
    (
        "initialize_backdrop_tile_quad",
        "void __cdecl initialize_backdrop_tile_quad(Object* object, int32_t edge_selector, int32_t orientation, int32_t row_selector, int32_t column_selector, char* texture_path)",
    ),
    (
        "rotate_object_facequad_uv_pairs",
        "void __fastcall rotate_object_facequad_uv_pairs(ObjectFaceQuad* quad)",
    ),
    (
        "initialize_direct3d_renderer_defaults",
        "void __thiscall initialize_direct3d_renderer_defaults(Direct3DRenderer* renderer)",
    ),
    (
        "release_direct3d_renderer_resources",
        "void __thiscall release_direct3d_renderer_resources(Direct3DRenderer* renderer)",
    ),
    (
        "direct3d_renderer_set_cull_mode",
        "int32_t __thiscall direct3d_renderer_set_cull_mode(Direct3DRenderer* renderer, uint8_t cull_front)",
    ),
    (
        "initialize_d3d8_device",
        "void __thiscall initialize_d3d8_device(Direct3DRenderer* renderer, uint8_t use_present_interval_one)",
    ),
    (
        "reset_direct3d_render_state",
        "void __thiscall reset_direct3d_render_state(Direct3DRenderer* renderer)",
    ),
    (
        "release_direct3d_device_interfaces",
        "void __thiscall release_direct3d_device_interfaces(Direct3DRenderer* renderer)",
    ),
    (
        "initialize_direct3d_renderer",
        "uint8_t __cdecl initialize_direct3d_renderer()",
    ),
    ("set_cull_mode", "int32_t __cdecl set_cull_mode(int32_t cull_front)"),
    ("set_blend_mode", "void __cdecl set_blend_mode(int32_t blend_mode)"),
    (
        "set_immediate_blend_mode",
        "void __cdecl set_immediate_blend_mode(int32_t blend_mode)",
    ),
    (
        "draw_textured_quad_immediate",
        "void __cdecl draw_textured_quad_immediate(TextureRef* texture, float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3, float width, float height, float u0, float v0, float u1, float v1, tColour* color, int32_t blend_mode, float rotation)",
    ),
    (
        "release_global_direct3d_renderer_resources",
        "void __cdecl release_global_direct3d_renderer_resources()",
    ),
    ("present_backbuffer", "int32_t __cdecl present_backbuffer()"),
    ("set_fullscreen_mode", "void __cdecl set_fullscreen_mode(uint8_t enabled)"),
    (
        "direct3d_renderer_set_fullscreen_mode",
        "void __thiscall direct3d_renderer_set_fullscreen_mode(Direct3DRenderer* renderer, uint8_t enabled)",
    ),
    (
        "restore_texture_ref_stage_states",
        "void __thiscall restore_texture_ref_stage_states(Direct3DRenderer* renderer)",
    ),
    ("bind_texture_ref", "void __cdecl bind_texture_ref(TextureRef* texture)"),
    (
        "query_direct3d_device_caps",
        "void __thiscall query_direct3d_device_caps(Direct3DRenderer* renderer)",
    ),
    ("reset_render_counters", "int32_t __cdecl reset_render_counters()"),
    (
        "initialize_object_distort",
        "void __thiscall initialize_object_distort(ObjectDistort* distort)",
    ),
    (
        "apply_distort_to_object",
        "void __thiscall apply_distort_to_object(ObjectDistort* distort, Object* object)",
    ),
    (
        "initialize_object",
        "void __thiscall initialize_object(Object* object)",
    ),
    (
        "initialize_object_list",
        "void __thiscall initialize_object_list(ObjectList* object_list, int32_t capacity)",
    ),
    (
        "build_all_objects",
        "void __thiscall build_all_objects(ObjectList* object_list)",
    ),
    (
        "add_object_to_list",
        "Object* __thiscall add_object_to_list(ObjectList* object_list)",
    ),
    (
        "replace_object_list_texture_refs",
        "void __thiscall replace_object_list_texture_refs(ObjectList* object_list, TextureRef* new_texture, TextureRef* old_texture)",
    ),
    (
        "apply_object_toon",
        "void __thiscall apply_object_toon(Object* object, int32_t toon_flags)",
    ),
    (
        "request_object_vertices",
        "void __thiscall request_object_vertices(Object* object, int32_t vertex_count)",
    ),
    (
        "copy_object_vertices",
        "void __thiscall copy_object_vertices(Object* object)",
    ),
    (
        "request_object_vertices_copy",
        "void __thiscall request_object_vertices_copy(Object* object)",
    ),
    (
        "request_object_vertex_colours",
        "void __fastcall request_object_vertex_colours(Object* object)",
    ),
    (
        "request_object_facequad_normals",
        "Vec3* __thiscall request_object_facequad_normals(Object* object)",
    ),
    (
        "request_object_facequads",
        "void __thiscall request_object_facequads(Object* object, int32_t facequad_count)",
    ),
    (
        "request_object_texture_groups",
        "void __thiscall request_object_texture_groups(Object* object, int32_t group_count)",
    ),
    (
        "request_object_edges",
        "void __thiscall request_object_edges(Object* object, int32_t edge_count)",
    ),
    (
        "initialize_directx_loader",
        "void __thiscall initialize_directx_loader(DirectXLoader* loader)",
    ),
    (
        "load_x_mesh",
        "void __thiscall load_x_mesh(DirectXLoader* loader, char* mesh_path, Object* object, int32_t options_flags)",
    ),
    (
        "load_or_reuse_cached_x_mesh",
        "int32_t __thiscall load_or_reuse_cached_x_mesh(DirectXLoader* loader, char* mesh_name)",
    ),
    (
        "load_x_animation_clip",
        "void __thiscall load_x_animation_clip(DirectXLoader* loader, char* mesh_name, Object* object)",
    ),
    (
        "initialize_duplicate_vertices",
        "void* __thiscall initialize_duplicate_vertices(DuplicateVertices* duplicate_vertices, int32_t count)",
    ),
    (
        "clean_duplicate_vertices",
        "int32_t __thiscall clean_duplicate_vertices(DuplicateVertices* duplicate_vertices, int32_t unused)",
    ),
    (
        "calc_object_bounding_box",
        "void __thiscall calc_object_bounding_box(Object* object)",
    ),
    (
        "calc_object_facequad_normals",
        "void __thiscall calc_object_facequad_normals(Object* object)",
    ),
    (
        "calc_object_texture_groups",
        "void __thiscall calc_object_texture_groups(Object* object)",
    ),
    (
        "add_object_edge",
        "void __thiscall add_object_edge(Object* object, int32_t vertex_a, int32_t vertex_b, int32_t normal_index)",
    ),
    (
        "calc_object_edges",
        "void __thiscall calc_object_edges(Object* object)",
    ),
    (
        "create_vertex_buffer",
        "ObjectRenderBuffers* __thiscall create_vertex_buffer(VertexBufferFactory* factory, int32_t vertex_count, int32_t fvf)",
    ),
    (
        "create_index_buffer",
        "ObjectIndexBuffer* __thiscall create_index_buffer(IndexBufferFactory* factory, int32_t index_count)",
    ),
    (
        "request_object_animation",
        "void __thiscall request_object_animation(Object* object, int32_t keyframe_count, XAnimationKeyframe* keyframes, float progress_step, int32_t flags)",
    ),
    (
        "advance_frame_sequence",
        "void __thiscall advance_frame_sequence(FrameSequence* sequence)",
    ),
    (
        "sort_object_faces_by_texture_group",
        "void __cdecl sort_object_faces_by_texture_group(Object* object)",
    ),
    (
        "build_object_texture_group_buffers",
        "void __cdecl build_object_texture_group_buffers(Object* object)",
    ),
    (
        "get_or_append_object_texture_group_vertex",
        "int32_t __cdecl get_or_append_object_texture_group_vertex(Object* object, int32_t vertex_index, float u, float v)",
    ),
    (
        "refresh_object_vertex_buffer",
        "void __cdecl refresh_object_vertex_buffer(Object* object)",
    ),
    # `pack_color_rgba_u8` is declared with the recovered tColourSmall owner in
    # the header, but the live database restores its pinned ColorBGRA8 user
    # type after a successful preview. Keep that one direct prototype update
    # deferred instead of making this repeatable sync fail verification.
    (
        "set_object_color",
        "void __cdecl set_object_color(Object* object, tColour color)",
    ),
    (
        "render_object_toon",
        "int32_t __cdecl render_object_toon(Object* object, TransformMatrix* matrix)",
    ),
    (
        "render_object",
        "int32_t __cdecl render_object(Object* object, TransformMatrix* matrix, float texture_u, float texture_v, tColour* color, char after_sprites)",
    ),
    (
        "render_camera",
        "TransformMatrix* __cdecl render_camera(float viewport_x, float viewport_y, float viewport_width, float viewport_height, float fov_degrees, TransformMatrix* camera_matrix, TransformMatrix* view_matrix, char draw_world, char post_sprite_pass)",
    ),
    (
        "build_perspective_projection_matrix",
        "TransformMatrix* __stdcall build_perspective_projection_matrix(TransformMatrix* matrix, float vertical_fov_radians, float aspect_ratio, float near_z, float far_z)",
    ),
    (
        "build_camera_view_matrix",
        "TransformMatrix* __stdcall build_camera_view_matrix(TransformMatrix* matrix, const Vec3* eye, const Vec3* target, const Vec3* up)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the narrow object render/animation type slice to a Binary Ninja target."
    )
    parser.add_argument("--target", default=DEFAULT_TARGET, help="Binary Ninja target selector.")
    parser.add_argument("--header", type=Path, default=DEFAULT_HEADER_PATH, help="Narrow Binary Ninja type header.")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations: list[dict[str, object]] = []
    operations.append(
        types_declare_if_changed(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
        )
    )
    operations.append(
        apply_direct_proto_update(
            REPO_ROOT,
            target=args.target,
            identifier="noop_this_constructor",
            prototype="void* __thiscall noop_this_constructor(void* self)",
        )
    )
    operations.extend(
        apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=FUNCTION_SYMBOL_UPDATES,
            kind="function",
        )
    )
    operations.extend(
        apply_struct_and_proto_updates(
            REPO_ROOT,
            target=args.target,
            struct_updates=(
                ("Direct3DRenderer", DIRECT3D_RENDERER_FIELDS),
                ("Object", OBJECT_FIELDS),
                ("FrameSequence", FRAME_SEQUENCE_FIELDS),
                ("TextureRef", TEXTURE_REF_FIELDS),
                ("ObjectList", OBJECT_LIST_FIELDS),
                ("GameRoot", GAME_ROOT_FIELDS),
            ),
            proto_updates=PROTO_UPDATES,
        )
    )
    operations.extend(
        apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=SYMBOL_UPDATES,
            kind="data",
        )
    )
    operations.extend(
        apply_symbol_removals(
            REPO_ROOT,
            target=args.target,
            removals=SYMBOL_REMOVALS,
        )
    )
    operations.extend(apply_data_var_updates(REPO_ROOT, target=args.target, updates=DATA_VAR_UPDATES))
    return emit_summary(repo_root=REPO_ROOT, target=args.target, header_path=header_path, operations=operations)


if __name__ == "__main__":
    sys.exit(main())
