import json
import pathlib
import re
import sys

import ida_auto
import ida_funcs
import ida_hexrays
import ida_kernwin
import ida_name
import ida_pro
import ida_typeinf
import idc

SCRIPT_ROOT = pathlib.Path(__file__).resolve().parent
if str(SCRIPT_ROOT) not in sys.path:
    sys.path.insert(0, str(SCRIPT_ROOT))

from game_root_owner import sync_game_root_owner_graph  # noqa: E402


TRUSTED_DECLARATIONS = [
    (
        "initialize_textured_backdrop_quad",
        "void __cdecl initialize_textured_backdrop_quad(Object* object, char* texture_path, float x_offset);",
    ),
    (
        "raise_backdrop_quad_edge_pair",
        "void __cdecl raise_backdrop_quad_edge_pair(int32_t selector, Object* object);",
    ),
    (
        "initialize_backdrop_slice_quad",
        "void __cdecl initialize_backdrop_slice_quad(Object* object, char* texture_path, float x_offset);",
    ),
    (
        "initialize_backdrop_corner_quad",
        "void __cdecl initialize_backdrop_corner_quad(int32_t selector, Object* object, char* texture_path);",
    ),
    (
        "initialize_backdrop_tile_quad",
        "void __cdecl initialize_backdrop_tile_quad(Object* object, int32_t edge_selector, int32_t orientation, int32_t row_selector, int32_t column_selector, char* texture_path);",
    ),
    (
        "rotate_object_facequad_uv_pairs",
        "void __fastcall rotate_object_facequad_uv_pairs(ObjectFaceQuad* quad);",
    ),
    (
        "initialize_direct3d_renderer_defaults",
        "void __thiscall initialize_direct3d_renderer_defaults(Direct3DRenderer* renderer);",
    ),
    (
        "release_direct3d_renderer_resources",
        "void __thiscall release_direct3d_renderer_resources(Direct3DRenderer* renderer);",
    ),
    (
        "direct3d_renderer_set_cull_mode",
        "int32_t __thiscall direct3d_renderer_set_cull_mode(Direct3DRenderer* renderer, uint8_t cull_front);",
    ),
    (
        "initialize_d3d8_device",
        "void __thiscall initialize_d3d8_device(Direct3DRenderer* renderer, uint8_t use_present_interval_one);",
    ),
    (
        "reset_direct3d_render_state",
        "void __thiscall reset_direct3d_render_state(Direct3DRenderer* renderer);",
    ),
    (
        "release_direct3d_device_interfaces",
        "void __thiscall release_direct3d_device_interfaces(Direct3DRenderer* renderer);",
    ),
    (
        "initialize_direct3d_renderer",
        "uint8_t __cdecl initialize_direct3d_renderer(void);",
    ),
    (
        "set_cull_mode",
        "int32_t __cdecl set_cull_mode(int32_t cull_front);",
    ),
    (
        "set_blend_mode",
        "void __cdecl set_blend_mode(int32_t blend_mode);",
    ),
    (
        "set_immediate_blend_mode",
        "void __cdecl set_immediate_blend_mode(int32_t blend_mode);",
    ),
    (
        "draw_textured_quad_immediate",
        "void __cdecl draw_textured_quad_immediate(TextureRef* texture, "
        "float x0, float y0, float x1, float y1, float x2, float y2, "
        "float x3, float y3, float width, float height, float u0, float v0, "
        "float u1, float v1, tColour* color, int32_t blend_mode, float rotation);",
    ),
    (
        "release_global_direct3d_renderer_resources",
        "void __cdecl release_global_direct3d_renderer_resources(void);",
    ),
    (
        "present_backbuffer",
        "int32_t __cdecl present_backbuffer(void);",
    ),
    (
        "set_fullscreen_mode",
        "void __cdecl set_fullscreen_mode(uint8_t enabled);",
    ),
    (
        "direct3d_renderer_set_fullscreen_mode",
        "void __thiscall direct3d_renderer_set_fullscreen_mode(Direct3DRenderer* renderer, uint8_t enabled);",
    ),
    (
        "restore_texture_ref_stage_states",
        "void __thiscall restore_texture_ref_stage_states(Direct3DRenderer* renderer);",
    ),
    (
        "bind_texture_ref",
        "void __cdecl bind_texture_ref(TextureRef* texture);",
    ),
    (
        "query_direct3d_device_caps",
        "void __thiscall query_direct3d_device_caps(Direct3DRenderer* renderer);",
    ),
    (
        "reset_render_counters",
        "int32_t __cdecl reset_render_counters(void);",
    ),
    (
        "noop_this_constructor",
        "void* __thiscall noop_this_constructor(void* self);",
    ),
    (
        "initialize_object_distort",
        "void __thiscall initialize_object_distort(ObjectDistort* distort);",
    ),
    (
        "apply_distort_to_object",
        "void __thiscall apply_distort_to_object(ObjectDistort* distort, Object* object);",
    ),
    (
        "initialize_object",
        "void __thiscall initialize_object(Object* object);",
    ),
    (
        "initialize_object_list",
        "void __thiscall initialize_object_list(ObjectList* object_list, int capacity);",
    ),
    (
        "build_all_objects",
        "void __thiscall build_all_objects(ObjectList* object_list);",
    ),
    (
        "add_object_to_list",
        "Object* __thiscall add_object_to_list(ObjectList* object_list);",
    ),
    (
        "replace_object_list_texture_refs",
        "void __thiscall replace_object_list_texture_refs(ObjectList* object_list, TextureRef* new_texture, TextureRef* old_texture);",
    ),
    (
        "initialize_directx_loader",
        "void __thiscall initialize_directx_loader(DirectXLoader* loader);",
    ),
    (
        "load_x_mesh",
        "void __thiscall load_x_mesh(DirectXLoader* loader, char* mesh_path, Object* object, int32_t options_flags);",
    ),
    (
        "load_or_reuse_cached_x_mesh",
        "int __thiscall load_or_reuse_cached_x_mesh(DirectXLoader* loader, char* mesh_name);",
    ),
    (
        "load_x_animation_clip",
        "void __thiscall load_x_animation_clip(DirectXLoader* loader, char* mesh_name, Object* object);",
    ),
    (
        "initialize_duplicate_vertices",
        "void* __thiscall initialize_duplicate_vertices(DuplicateVertices* duplicate_vertices, int count);",
    ),
    (
        "clean_duplicate_vertices",
        "int __thiscall clean_duplicate_vertices(DuplicateVertices* duplicate_vertices, int unused);",
    ),
    (
        "calc_object_bounding_box",
        "void __thiscall calc_object_bounding_box(Object* object);",
    ),
    (
        "calc_object_facequad_normals",
        "void __thiscall calc_object_facequad_normals(Object* object);",
    ),
    (
        "calc_object_texture_groups",
        "void __thiscall calc_object_texture_groups(Object* object);",
    ),
    (
        "request_object_texture_groups",
        "void __thiscall request_object_texture_groups(Object* object, int group_count);",
    ),
    (
        "add_object_edge",
        "void __thiscall add_object_edge(Object* object, int vertex_a, int vertex_b, int normal_index);",
    ),
    (
        "calc_object_edges",
        "void __thiscall calc_object_edges(Object* object);",
    ),
    (
        "load_object_definition",
        "void __cdecl load_object_definition(char* path, Object* object);",
    ),
    (
        "create_vertex_buffer",
        "ObjectRenderBuffers* __thiscall create_vertex_buffer(VertexBufferFactory* factory, int vertex_count, int fvf);",
    ),
    (
        "create_index_buffer",
        "ObjectIndexBuffer* __thiscall create_index_buffer(IndexBufferFactory* factory, int index_count);",
    ),
    (
        "request_object_animation",
        "void __thiscall request_object_animation(Object* object, int keyframe_count, XAnimationKeyframe* keyframes, float progress_step, int flags);",
    ),
    (
        "advance_frame_sequence",
        "void __thiscall advance_frame_sequence(FrameSequence* sequence);",
    ),
    (
        "get_or_append_object_texture_group_vertex",
        "int32_t __cdecl get_or_append_object_texture_group_vertex(Object* object, int vertex_index, float u, float v);",
    ),
    (
        "sort_object_faces_by_texture_group",
        "void __cdecl sort_object_faces_by_texture_group(Object* object);",
    ),
    (
        "build_object_texture_group_buffers",
        "void __cdecl build_object_texture_group_buffers(Object* object);",
    ),
    (
        "refresh_object_vertex_buffer",
        "void __cdecl refresh_object_vertex_buffer(Object* object);",
    ),
    (
        "pack_color_rgba_u8",
        "tColourSmall* __thiscall pack_color_rgba_u8(tColourSmall* out, tColour* color);",
    ),
    (
        "set_object_color",
        "void __cdecl set_object_color(Object* object, tColour color);",
    ),
    (
        "render_object_toon",
        "int __cdecl render_object_toon(Object* object, TransformMatrix* matrix);",
    ),
    (
        "render_object",
        "int __cdecl render_object(Object* object, TransformMatrix* matrix, float texture_u, float texture_v, tColour* color, char after_sprites);",
    ),
    (
        "render_camera",
        "TransformMatrix* __cdecl render_camera(float viewport_x, float viewport_y, float viewport_width, float viewport_height, float fov_degrees, TransformMatrix* camera_matrix, TransformMatrix* view_matrix, char draw_world, char post_sprite_pass);",
    ),
    (
        "build_perspective_projection_matrix",
        "TransformMatrix* __stdcall build_perspective_projection_matrix(TransformMatrix* matrix, float vertical_fov_radians, float aspect_ratio, float near_z, float far_z);",
    ),
    (
        "build_camera_view_matrix",
        "TransformMatrix* __stdcall build_camera_view_matrix(TransformMatrix* matrix, const Vec3* eye, const Vec3* target, const Vec3* up);",
    ),
]

TRUSTED_NAMES = [
    (0x405640, "load_x_mesh"),
    (0x41A0B0, "initialize_textured_backdrop_quad"),
    (0x41A170, "raise_backdrop_quad_edge_pair"),
    (0x41A1C0, "initialize_backdrop_slice_quad"),
    (0x41A290, "initialize_backdrop_corner_quad"),
    (0x41A4D0, "initialize_backdrop_tile_quad"),
    (0x41AA30, "initialize_object_distort"),
    (0x41AA50, "apply_distort_to_object"),
    (0x4114B0, "create_vertex_buffer"),
    (0x4115D0, "create_index_buffer"),
    (0x411630, "initialize_direct3d_renderer_defaults"),
    (0x4116F0, "release_direct3d_renderer_resources"),
    (0x411700, "direct3d_renderer_set_cull_mode"),
    (0x411730, "initialize_d3d8_device"),
    (0x4118B0, "reset_direct3d_render_state"),
    (0x411960, "release_direct3d_device_interfaces"),
    (0x411D70, "release_global_direct3d_renderer_resources"),
    (0x411FA0, "render_camera"),
    (0x4129C0, "initialize_direct3d_renderer"),
    (0x4129F0, "set_cull_mode"),
    (0x412D00, "set_blend_mode"),
    (0x412E50, "set_immediate_blend_mode"),
    (0x413030, "draw_textured_quad_immediate"),
    (0x413520, "present_backbuffer"),
    (0x414260, "set_fullscreen_mode"),
    (0x414270, "direct3d_renderer_set_fullscreen_mode"),
    (0x4143C0, "restore_texture_ref_stage_states"),
    (0x414500, "bind_texture_ref"),
    (0x414600, "query_direct3d_device_caps"),
    (0x414650, "reset_render_counters"),
    (0x413BB0, "get_or_append_object_texture_group_vertex"),
    (0x413D50, "build_object_texture_group_buffers"),
    (0x419FD0, "sort_object_faces_by_texture_group"),
    (0x42F930, "request_object_texture_groups"),
    (0x42F990, "initialize_object_list"),
    (0x42F9E0, "build_all_objects"),
    (0x42FAD0, "add_object_to_list"),
    (0x42FB10, "calc_object_bounding_box"),
    (0x42FCB0, "calc_object_facequad_normals"),
    (0x4303F0, "calc_object_texture_groups"),
    (0x4305A0, "add_object_edge"),
    (0x4308B0, "calc_object_edges"),
    (0x430A30, "rotate_object_facequad_uv_pairs"),
    (0x430D90, "replace_object_list_texture_refs"),
    (0x450314, "build_perspective_projection_matrix"),
    (0x451AD9, "build_camera_view_matrix"),
    (0x4A3C40, "g_backdrop_raise_first_vertex_index"),
    (0x4A3C44, "g_backdrop_raise_second_vertex_index"),
    (0x4A3CE0, "g_backdrop_corner_vertex_indices"),
    (0x4B7648, "g_object_list"),
    (0x4F7450, "g_render_triangle_count"),
    (0x4F7454, "g_render_successful_primitive_count"),
    (0x4F7458, "g_direct3d_renderer"),
    (0x50316C, "g_render_projection_param_b"),
    (0x503170, "g_draw_primitive_call_count"),
    (0x503174, "g_current_texture_ref"),
    (0x5031B8, "g_render_camera_source_matrix"),
    (0x5031BC, "g_object_grouped_vertex_cursor"),
    (0x5031C0, "g_texture_bind_call_count"),
    (0x5031C4, "g_object_grouped_vertex_scratch"),
    (0x5031C8, "g_d3d_texture_slots"),
    (0x5031CC, "g_render_projection_near_z"),
    (0x5031D0, "g_render_projection_far_z"),
    (0x5031D4, "g_render_projection_param_a"),
    (0x503218, "g_render_camera_view_matrix"),
    (0x503260, "g_object_render_pass_filter"),
    (0x503300, "g_object_edge_build_edges"),
    (0x503318, "g_object_edge_build_count"),
]

TRUSTED_DATA_DECLARATIONS = [
    (0x4B7648, "g_object_list", "ObjectList g_object_list;"),
    (
        0x4A3C40,
        "g_backdrop_raise_first_vertex_index",
        "int32_t g_backdrop_raise_first_vertex_index;",
    ),
    (
        0x4A3C44,
        "g_backdrop_raise_second_vertex_index",
        "int32_t g_backdrop_raise_second_vertex_index;",
    ),
    (
        0x4A3CE0,
        "g_backdrop_corner_vertex_indices",
        "int32_t g_backdrop_corner_vertex_indices[4];",
    ),
    (0x4F7450, "g_render_triangle_count", "int32_t g_render_triangle_count;"),
    (
        0x4F7454,
        "g_render_successful_primitive_count",
        "int32_t g_render_successful_primitive_count;",
    ),
    (0x4F7458, "g_direct3d_renderer", "Direct3DRenderer g_direct3d_renderer;"),
    (0x50316C, "g_render_projection_param_b", "float g_render_projection_param_b;"),
    (0x503170, "g_draw_primitive_call_count", "int32_t g_draw_primitive_call_count;"),
    (0x503174, "g_current_texture_ref", "TextureRef* g_current_texture_ref;"),
    (
        0x5031B8,
        "g_render_camera_source_matrix",
        "TransformMatrix* g_render_camera_source_matrix;",
    ),
    (
        0x5031BC,
        "g_object_grouped_vertex_cursor",
        "int32_t g_object_grouped_vertex_cursor;",
    ),
    (0x5031C0, "g_texture_bind_call_count", "int32_t g_texture_bind_call_count;"),
    (
        0x5031C4,
        "g_object_grouped_vertex_scratch",
        "ObjectGroupedVertex* g_object_grouped_vertex_scratch;",
    ),
    (0x5031C8, "g_d3d_texture_slots", "Direct3DTexture8** g_d3d_texture_slots;"),
    (0x5031CC, "g_render_projection_near_z", "float g_render_projection_near_z;"),
    (0x5031D0, "g_render_projection_far_z", "float g_render_projection_far_z;"),
    (0x5031D4, "g_render_projection_param_a", "float g_render_projection_param_a;"),
    (
        0x503218,
        "g_render_camera_view_matrix",
        "TransformMatrix* g_render_camera_view_matrix;",
    ),
    (
        0x503260,
        "g_object_render_pass_filter",
        "uint8_t g_object_render_pass_filter;",
    ),
    (
        0x503300,
        "g_object_edge_build_edges",
        "ObjectToonEdge* g_object_edge_build_edges;",
    ),
    (0x503318, "g_object_edge_build_count", "int32_t g_object_edge_build_count;"),
]

REQUIRED_OWNER_MARKERS = (
    "typedef struct ObjectRenderBuffers {",
    "typedef struct ObjectIndexBuffer {",
    "typedef struct VertexBufferFactory {",
    "typedef struct IndexBufferFactory {",
    "typedef struct Direct3DRenderer {",
    "typedef struct ObjectDistort {",
    "typedef struct ObjectGroupedVertex {",
    "typedef struct ObjectToonEdge {",
    "typedef struct Object {",
    "typedef struct ObjectList {",
    "ObjectList_must_be_0x0c",
    "extern ObjectList g_object_list;",
    "typedef struct DirectXLoader {",
    "void __thiscall load_x_mesh(",
    "void __thiscall calc_object_bounding_box(Object* object);",
    "void __thiscall calc_object_texture_groups(Object* object);",
    "void __thiscall request_object_texture_groups(Object* object, int32_t group_count);",
    "void __cdecl sort_object_faces_by_texture_group(Object* object);",
    "int32_t __cdecl get_or_append_object_texture_group_vertex(",
    "void __thiscall add_object_edge(",
    "extern int32_t g_object_grouped_vertex_cursor;",
    "extern ObjectGroupedVertex* g_object_grouped_vertex_scratch;",
    "extern ObjectToonEdge* g_object_edge_build_edges;",
    "ObjectRenderBuffers* __thiscall create_vertex_buffer(",
    "ObjectIndexBuffer* __thiscall create_index_buffer(",
    "void __thiscall apply_distort_to_object(ObjectDistort* distort, Object* object);",
    "TransformMatrix* __cdecl render_camera(",
    "extern TransformMatrix* g_render_camera_source_matrix;",
    "extern TransformMatrix* g_render_camera_view_matrix;",
    "extern uint8_t g_object_render_pass_filter;",
)

EXPECTED_OWNER_SIZES = {
    "Vec3": 0xC,
    "TextureRef": 0xA4,
    "ObjectRenderBuffers": 0xC,
    "ObjectIndexBuffer": 0x4,
    "VertexBufferFactory": 0x8CA4,
    "IndexBufferFactory": 0x2EE4,
    "Direct3DRenderer": 0xBCC0,
    "ObjectFaceQuad": 0x30,
    "ObjectGroupedVertex": 0x1C,
    "ObjectToonEdge": 0x24,
    "ObjectDistort": 0x14,
    "Object": 0xDC,
    "ObjectList": 0xC,
    "DuplicateVertices": 0x8,
    "CachedXMeshSlot": 0xBC,
    "DirectXLoader": 0x5E10,
}

# Rebuild the recovered helpers and their direct ownership-bearing callers.
REANALYSIS_FUNCTIONS = (
    0x405640,  # load_x_mesh
    0x405CC0,  # load_or_reuse_cached_x_mesh
    0x405D60,  # load_x_animation_clip
    0x40ACF0,  # initialize_game_assets_and_world
    0x4114B0,  # create_vertex_buffer
    0x4115D0,  # create_index_buffer
    0x411630,  # initialize_direct3d_renderer_defaults
    0x4116F0,  # release_direct3d_renderer_resources
    0x411FA0,  # render_camera
    0x412250,  # refresh_object_vertex_buffer
    0x4129C0,  # initialize_direct3d_renderer
    0x413BB0,  # get_or_append_object_texture_group_vertex
    0x413D50,  # build_object_texture_group_buffers
    0x418B50,  # initialize_loading_screen
    0x419110,  # open_logo
    0x419FD0,  # sort_object_faces_by_texture_group
    0x41AA30,  # initialize_object_distort
    0x41AA50,  # apply_distort_to_object
    0x4246A0,  # build_track_fringe_mesh
    0x424AD0,  # build_track_fringe_supertramp_mesh
    0x42F990,  # initialize_object_list
    0x42F9E0,  # build_all_objects
    0x42FAD0,  # add_object_to_list
    0x42F930,  # request_object_texture_groups
    0x42FB10,  # calc_object_bounding_box
    0x42FCB0,  # calc_object_facequad_normals
    0x4303F0,  # calc_object_texture_groups
    0x4305A0,  # add_object_edge
    0x4308B0,  # calc_object_edges
    0x430A70,  # request_object_animation
    0x430D90,  # replace_object_list_texture_refs
    0x433060,  # initialize_track_render_cache_manager
    0x44AE10,  # initialize_font3d_objects
)

# The stale 11-argument usercall left two compensating stack points around
# render_camera's first and last indirect D3D calls. The native pushes prove
# SetViewport consumes two arguments while SetRenderState consumes three.
# Guard both observed stale values so replay cannot rewrite an unrelated edit.
RENDER_CAMERA_STACK_POINT_SPECS = (
    (0x41201E, 12, 8, "SetViewport"),
    (0x412229, 8, 12, "SetRenderState"),
)

BUFFER_FACTORY_LVAR_SPECS = (
    ("create_vertex_buffer", 0x4115A8, "next_count", "int32_t next_count;"),
    ("create_index_buffer", 0x4115F9, "next_count", "int32_t next_count;"),
)

TOPOLOGY_LVAR_SPECS = (
    (
        "calc_object_facequad_normals",
        0x42FCD3,
        "normal_tally",
        "float *normal_tally;",
    ),
    (
        "calc_object_facequad_normals",
        0x42FCF0,
        "byte_offset",
        "uint32_t byte_offset;",
    ),
    (
        "calc_object_facequad_normals",
        0x42FCF4,
        "face_index",
        "int32_t face_index;",
    ),
    (
        "calc_object_facequad_normals",
        0x42FCFE,
        "normal_index",
        "int32_t normal_index;",
    ),
    (
        "calc_object_facequad_normals",
        0x42FDD0,
        "face_normal",
        "Vec3 face_normal;",
    ),
    (
        "calc_object_facequad_normals",
        0x42FEBE,
        "quad_normal",
        "Vec3 quad_normal;",
    ),
    (
        "calc_object_facequad_normals",
        0x43017D,
        "vertex_index",
        "int32_t vertex_index;",
    ),
    ("add_object_edge", 0x4305D2, "build_count", "int32_t build_count;"),
    ("add_object_edge", 0x4305E0, "edge_index", "int32_t edge_index;"),
    ("add_object_edge", 0x43078C, "shift_index", "int32_t shift_index;"),
    ("add_object_edge", 0x430799, "found_index", "int32_t found_index;"),
    ("add_object_edge", 0x43086B, "copy_index", "int32_t copy_index;"),
    (
        "calc_object_edges",
        0x4308CA,
        "build_edges",
        "ObjectToonEdge *build_edges;",
    ),
    ("calc_object_edges", 0x4308CC, "edge_count", "int32_t edge_count;"),
    ("calc_object_edges", 0x4308DD, "face_index", "int32_t face_index;"),
    ("calc_object_edges", 0x4308E9, "normal_index", "int32_t normal_index;"),
    ("calc_object_edges", 0x4309A5, "edge_index", "int32_t edge_index;"),
    ("calc_object_edges", 0x4309AB, "edge_offset", "int32_t edge_offset;"),
    (
        "calc_object_edges",
        0x4309AD,
        "saved_edge_offset",
        "int32_t saved_edge_offset;",
    ),
    ("calc_object_edges", 0x4309BA, "shift_index", "int32_t shift_index;"),
)


def _resolve_function(selector: str) -> tuple[int | None, str]:
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR:
        return None, selector
    return address, selector


def _normalize_type_text(value: str | None) -> str | None:
    if value is None:
        return None
    normalized = value.strip().removesuffix(";")
    normalized = re.sub(r"\bint32_t\b", "int", normalized)
    normalized = re.sub(r"\s+", " ", normalized)
    normalized = re.sub(r"\b(?:struct|union|enum)\s+", "", normalized)
    normalized = re.sub(r"\s*\(\s*", "(", normalized)
    normalized = re.sub(r"\s*\)\s*", ")", normalized)
    normalized = re.sub(r"\s*,\s*", ", ", normalized)
    normalized = re.sub(r"\s*\*\s*", " *", normalized)
    normalized = re.sub(r"\s*\[\s*", "[", normalized)
    normalized = re.sub(r"\s*\]\s*", "]", normalized)
    normalized = re.sub(r"\(\s*", "(", normalized)
    normalized = re.sub(r"\s*\)", ")", normalized)
    normalized = normalized.strip()
    return re.sub(r"\(void\)$", "()", normalized)


def _declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\s*(?=\()", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


def _data_declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\b", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


def _named_struct_size(name: str) -> int | None:
    value = ida_typeinf.tinfo_t()
    if not value.get_named_type(None, name, ida_typeinf.BTF_STRUCT):
        return None
    return value.get_size()


def _sync_refresh_vertex_lvars() -> dict[str, object]:
    selector = "refresh_object_vertex_buffer"
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR or ida_funcs.get_func(address) is None:
        return {"status": "failed", "reason": "missing_function", "selector": selector}

    declaration = "ObjectRenderVertex *vertices;"
    local_type = ida_typeinf.tinfo_t()
    if not ida_typeinf.parse_decl(
        local_type,
        None,
        declaration,
        ida_typeinf.PT_SIL,
    ):
        return {
            "status": "failed",
            "reason": "parse_vertex_type_failed",
            "selector": selector,
            "declaration": declaration,
        }

    expected_type = _normalize_type_text(str(local_type))
    split_specs = (
        ("animated_vertices", 0x4122D0),
        ("dynamic_vertices", 0x412350),
    )
    cfunc = ida_hexrays.decompile(address)
    source_candidates = [
        lvar
        for lvar in cfunc.get_lvars()
        if lvar.is_arg_var
        and lvar.is_stk_var()
        and lvar.get_stkoff() == 40
        and lvar.name == "object"
        and _normalize_type_text(str(lvar.type())) == "Object *"
    ]
    if len(source_candidates) != 1:
        return {
            "status": "failed",
            "reason": "unexpected_object_argument_candidates",
            "selector": selector,
            "candidate_count": len(source_candidates),
        }

    applied = []
    unchanged = []
    for name, split_definition_address in split_specs:
        existing = [
            lvar
            for lvar in cfunc.get_lvars()
            if not lvar.is_arg_var
            and lvar.name == name
            and _normalize_type_text(str(lvar.type())) == expected_type
            and lvar.defea == split_definition_address
        ]
        if len(existing) == 1:
            unchanged.append(name)
            continue
        if existing:
            return {
                "status": "failed",
                "reason": "unexpected_existing_vertex_lvars",
                "selector": selector,
                "name": name,
                "candidate_count": len(existing),
            }

        info = ida_hexrays.lvar_saved_info_t()
        info.ll = ida_hexrays.lvar_locator_t(
            source_candidates[0].location,
            split_definition_address,
        )
        info.name = name
        info.type = local_type
        info.set_split_lvar()
        if not ida_hexrays.modify_user_lvar_info(
            address,
            ida_hexrays.MLI_NAME
            | ida_hexrays.MLI_TYPE
            | ida_hexrays.MLI_SET_FLAGS,
            info,
        ):
            return {
                "status": "failed",
                "reason": "modify_split_vertex_lvar_failed",
                "selector": selector,
                "name": name,
                "definition_address": hex(split_definition_address),
            }
        applied.append(name)

    ida_hexrays.mark_cfunc_dirty(address, True)
    verified_cfunc = ida_hexrays.decompile(address)
    verified = {
        name: [
            lvar
            for lvar in verified_cfunc.get_lvars()
            if not lvar.is_arg_var
            and lvar.name == name
            and _normalize_type_text(str(lvar.type())) == expected_type
            and lvar.defea == split_definition_address
        ]
        for name, split_definition_address in split_specs
    }
    invalid = {name: len(candidates) for name, candidates in verified.items() if len(candidates) != 1}
    if invalid:
        return {
            "status": "failed",
            "reason": "split_vertex_lvar_readback_failed",
            "selector": selector,
            "candidate_counts": invalid,
        }

    return {
        "status": "applied" if applied else "unchanged",
        "selector": selector,
        "type": str(local_type),
        "applied": applied,
        "unchanged": unchanged,
        "definitions": {
            name: hex(split_definition_address)
            for name, split_definition_address in split_specs
        },
    }


def _sync_owned_lvar(
    selector: str,
    definition_address: int,
    expected_name: str,
    declaration: str,
) -> dict[str, object]:
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR or ida_funcs.get_func(address) is None:
        return {
            "status": "failed",
            "reason": "missing_function",
            "selector": selector,
        }

    local_type = ida_typeinf.tinfo_t()
    if not ida_typeinf.parse_decl(
        local_type,
        None,
        declaration,
        ida_typeinf.PT_SIL,
    ):
        return {
            "status": "failed",
            "reason": "parse_owned_lvar_type_failed",
            "selector": selector,
            "declaration": declaration,
        }

    cfunc = ida_hexrays.decompile(address)
    candidates = [
        lvar
        for lvar in cfunc.get_lvars()
        if not lvar.is_arg_var and lvar.defea == definition_address
    ]
    if len(candidates) != 1:
        return {
            "status": "failed",
            "reason": "unexpected_owned_lvar_candidates",
            "selector": selector,
            "definition_address": hex(definition_address),
            "candidate_count": len(candidates),
        }

    lvar = candidates[0]
    expected_type = _normalize_type_text(str(local_type))
    observed_type = _normalize_type_text(str(lvar.type()))
    if lvar.name == expected_name and observed_type == expected_type:
        return {
            "status": "unchanged",
            "selector": selector,
            "name": expected_name,
            "type": str(local_type),
            "definition_address": hex(definition_address),
        }

    before_name = lvar.name
    before_type = str(lvar.type())
    info = ida_hexrays.lvar_saved_info_t()
    info.ll = ida_hexrays.lvar_locator_t(lvar.location, lvar.defea)
    info.name = expected_name
    info.type = local_type
    if not ida_hexrays.modify_user_lvar_info(
        address,
        ida_hexrays.MLI_NAME | ida_hexrays.MLI_TYPE,
        info,
    ):
        return {
            "status": "failed",
            "reason": "modify_owned_lvar_failed",
            "selector": selector,
            "definition_address": hex(definition_address),
        }

    ida_hexrays.mark_cfunc_dirty(address, True)
    verified_cfunc = ida_hexrays.decompile(address)
    verified = [
        candidate
        for candidate in verified_cfunc.get_lvars()
        if not candidate.is_arg_var
        and candidate.defea == definition_address
        and candidate.name == expected_name
        and _normalize_type_text(str(candidate.type())) == expected_type
    ]
    if len(verified) != 1:
        return {
            "status": "failed",
            "reason": "owned_lvar_readback_failed",
            "selector": selector,
            "definition_address": hex(definition_address),
            "candidate_count": len(verified),
        }

    return {
        "status": "applied",
        "selector": selector,
        "before_name": before_name,
        "before_type": before_type,
        "name": expected_name,
        "type": str(local_type),
        "definition_address": hex(definition_address),
    }


def _sync_topology_lvars() -> dict[str, object]:
    results = [
        _sync_owned_lvar(selector, definition_address, expected_name, declaration)
        for selector, definition_address, expected_name, declaration in TOPOLOGY_LVAR_SPECS
    ]
    failures = [result for result in results if result.get("status") == "failed"]
    return {
        "status": (
            "failed"
            if failures
            else "applied"
            if any(result.get("status") == "applied" for result in results)
            else "unchanged"
        ),
        "locals": results,
        "failures": failures,
    }


def _sync_buffer_factory_lvars() -> dict[str, object]:
    results = [
        _sync_owned_lvar(selector, definition_address, expected_name, declaration)
        for selector, definition_address, expected_name, declaration in (
            BUFFER_FACTORY_LVAR_SPECS
        )
    ]
    failures = [result for result in results if result.get("status") == "failed"]
    return {
        "status": (
            "failed"
            if failures
            else "applied"
            if any(result.get("status") == "applied" for result in results)
            else "unchanged"
        ),
        "locals": results,
        "failures": failures,
    }


def _sync_render_camera_stack_points() -> dict[str, object]:
    results = []
    for address, stale_delta, target_delta, call_name in (
        RENDER_CAMERA_STACK_POINT_SPECS
    ):
        observed_delta = idc.get_sp_delta(address)
        if observed_delta == target_delta:
            results.append(
                {
                    "status": "unchanged",
                    "address": hex(address),
                    "call": call_name,
                    "delta": observed_delta,
                }
            )
            continue
        if observed_delta != stale_delta:
            results.append(
                {
                    "status": "failed",
                    "reason": "unexpected_stack_point_delta",
                    "address": hex(address),
                    "call": call_name,
                    "expected_stale_delta": stale_delta,
                    "target_delta": target_delta,
                    "observed_delta": observed_delta,
                }
            )
            continue
        if not idc.add_user_stkpnt(address, target_delta):
            results.append(
                {
                    "status": "failed",
                    "reason": "stack_point_update_failed",
                    "address": hex(address),
                    "call": call_name,
                    "target_delta": target_delta,
                }
            )
            continue

        idc.recalc_spd(address)
        ida_auto.auto_wait()
        verified_delta = idc.get_sp_delta(address)
        results.append(
            {
                "status": "applied" if verified_delta == target_delta else "failed",
                "reason": (
                    None
                    if verified_delta == target_delta
                    else "stack_point_readback_failed"
                ),
                "address": hex(address),
                "call": call_name,
                "before_delta": observed_delta,
                "delta": verified_delta,
            }
        )

    failures = [result for result in results if result.get("status") == "failed"]
    if not failures:
        ida_hexrays.mark_cfunc_dirty(0x411FA0, True)
    return {
        "status": (
            "failed"
            if failures
            else "applied"
            if any(result.get("status") == "applied" for result in results)
            else "unchanged"
        ),
        "stack_points": results,
        "failures": failures,
    }


def _sync_types(header_path: pathlib.Path) -> int:
    header_text = header_path.read_text(encoding="utf-8")
    missing_owner_markers = [
        marker for marker in REQUIRED_OWNER_MARKERS if marker not in header_text
    ]
    if missing_owner_markers:
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "header": str(header_path),
                    "missing_owner_markers": missing_owner_markers,
                    "failed": [{"reason": "noncanonical_object_owner_header"}],
                },
                indent=2,
            )
        )
        return 1

    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE | idc.PT_REPLACE)
    owner_sizes = {name: _named_struct_size(name) for name in EXPECTED_OWNER_SIZES}
    size_failures = [
        {
            "selector": name,
            "reason": "owner_size_mismatch",
            "expected": expected_size,
            "observed": owner_sizes[name],
        }
        for name, expected_size in EXPECTED_OWNER_SIZES.items()
        if owner_sizes[name] != expected_size
    ]
    if parse_errors or size_failures:
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "header": str(header_path),
                    "parse_errors": parse_errors,
                    "owner_sizes": owner_sizes,
                    "failed": size_failures,
                },
                indent=2,
            )
        )
        return 1

    applied = 0
    unchanged = 0
    renamed = 0
    names_unchanged = 0
    missing = []
    failed = []

    for address, name in TRUSTED_NAMES:
        current_name = idc.get_name(address)
        if current_name == name:
            names_unchanged += 1
            continue
        if not idc.set_name(address, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
            failed.append(
                {
                    "selector": name,
                    "address": hex(address),
                    "reason": "rename_failed",
                }
            )
            continue
        if idc.get_name(address) != name:
            failed.append(
                {
                    "selector": name,
                    "address": hex(address),
                    "observed": idc.get_name(address),
                    "reason": "rename_readback_failed",
                }
            )
            continue
        renamed += 1

    for selector, declaration in TRUSTED_DECLARATIONS:
        address, _name = _resolve_function(selector)
        if address is None:
            missing.append({"selector": selector, "reason": "missing_symbol"})
            continue

        if ida_funcs.get_func(address) is None:
            missing.append({"selector": selector, "address": hex(address), "reason": "missing_function"})
            continue

        expected_observed = _declaration_to_observed_type(selector, declaration)
        normalized_current = _normalize_type_text(idc.get_type(address))

        if normalized_current == expected_observed:
            unchanged += 1
            continue

        if not idc.SetType(address, declaration):
            failed.append(
                {
                    "selector": selector,
                    "address": hex(address),
                    "declaration": declaration,
                    "reason": "set_type_failed",
                }
            )
            continue

        observed = idc.get_type(address)
        normalized_observed = _normalize_type_text(observed)
        if normalized_observed != expected_observed:
            failed.append(
                {
                    "selector": selector,
                    "address": hex(address),
                    "declaration": declaration,
                    "observed": observed,
                    "reason": "verification_failed",
                }
            )
            continue

        applied += 1

    for address, selector, declaration in TRUSTED_DATA_DECLARATIONS:
        expected_observed = _data_declaration_to_observed_type(selector, declaration)
        normalized_current = _normalize_type_text(idc.get_type(address))

        if normalized_current == expected_observed:
            unchanged += 1
            continue

        if not idc.SetType(address, declaration):
            failed.append(
                {
                    "selector": selector,
                    "address": hex(address),
                    "declaration": declaration,
                    "reason": "set_data_type_failed",
                }
            )
            continue

        observed = idc.get_type(address)
        normalized_observed = _normalize_type_text(observed)
        if normalized_observed != expected_observed:
            failed.append(
                {
                    "selector": selector,
                    "address": hex(address),
                    "declaration": declaration,
                    "observed": observed,
                    "reason": "data_verification_failed",
                }
            )
            continue

        applied += 1

    game_root_owner_graph = sync_game_root_owner_graph(require=False)
    if game_root_owner_graph.get("status") == "failed":
        failed.append({"selector": "GameRoot", "owner_graph": game_root_owner_graph})

    render_camera_stack_points = _sync_render_camera_stack_points()
    if render_camera_stack_points.get("status") == "failed":
        failed.append(
            {
                "selector": "render_camera",
                "stack_points": render_camera_stack_points,
            }
        )

    refresh_vertex_lvars = _sync_refresh_vertex_lvars()
    if refresh_vertex_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "refresh_object_vertex_buffer",
                "vertex_lvars": refresh_vertex_lvars,
            }
        )

    topology_lvars = _sync_topology_lvars()
    if topology_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "object_topology_lvars",
                "topology_lvars": topology_lvars,
            }
        )

    buffer_factory_lvars = _sync_buffer_factory_lvars()
    if buffer_factory_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "buffer_factory_lvars",
                "buffer_factory_lvars": buffer_factory_lvars,
            }
        )

    ida_auto.auto_wait()
    reanalysis_functions = []
    for address in REANALYSIS_FUNCTIONS:
        function = ida_funcs.get_func(address)
        if function is None:
            missing.append(
                {"address": hex(address), "reason": "missing_reanalysis_function"}
            )
            continue
        ida_hexrays.mark_cfunc_dirty(function.start_ea, True)
        reanalysis_functions.append(hex(function.start_ea))

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "parse_errors": parse_errors,
                "owner_sizes": owner_sizes,
                "applied": applied,
                "unchanged": unchanged,
                "renamed": renamed,
                "names_unchanged": names_unchanged,
                "game_root_owner_graph": game_root_owner_graph,
                "render_camera_stack_points": render_camera_stack_points,
                "refresh_vertex_lvars": refresh_vertex_lvars,
                "topology_lvars": topology_lvars,
                "buffer_factory_lvars": buffer_factory_lvars,
                "reanalysis_functions": reanalysis_functions,
                "missing": missing,
                "failed": failed,
            },
            indent=2,
        )
    )

    if parse_errors or failed or missing:
        return 1
    return 0


def main() -> None:
    argv = list(idc.ARGV)
    if len(argv) < 2:
        print("usage: apply_object_render_types.py <header-path>", file=sys.stderr)
        ida_pro.qexit(2)
        return

    header_path = pathlib.Path(argv[1]).resolve()
    exit_code = _sync_types(header_path)
    try:
        idc.save_database(idc.get_idb_path(), 0)
    except Exception as exc:  # pragma: no cover - IDA runtime dependent
        ida_kernwin.msg(f"warning: failed to save database explicitly: {exc}\n")
    ida_pro.qexit(exit_code)


if __name__ == "__main__":
    main()
