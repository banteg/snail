import json
import pathlib
import re
import sys

import ida_funcs
import ida_kernwin
import ida_name
import ida_pro
import idc

SCRIPT_ROOT = pathlib.Path(__file__).resolve().parent
if str(SCRIPT_ROOT) not in sys.path:
    sys.path.insert(0, str(SCRIPT_ROOT))

from game_root_owner import sync_game_root_owner_graph  # noqa: E402


TRUSTED_DECLARATIONS = [
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
        "void __cdecl set_fullscreen_mode(int32_t enabled);",
    ),
    (
        "direct3d_renderer_set_fullscreen_mode",
        "void __thiscall direct3d_renderer_set_fullscreen_mode(Direct3DRenderer* renderer, int32_t enabled);",
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
        "void __thiscall load_x_mesh(DirectXLoader* loader, char* mesh_path, Object* object, int options_flags);",
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
        "render_object",
        "int __cdecl render_object(Object* object, TransformMatrix* matrix, float texture_u, float texture_v, tColour* color, char after_sprites);",
    ),
]

TRUSTED_NAMES = [
    (0x4114B0, "create_vertex_buffer"),
    (0x4115D0, "create_index_buffer"),
    (0x411630, "initialize_direct3d_renderer_defaults"),
    (0x4116F0, "release_direct3d_renderer_resources"),
    (0x411700, "direct3d_renderer_set_cull_mode"),
    (0x411730, "initialize_d3d8_device"),
    (0x4118B0, "reset_direct3d_render_state"),
    (0x411960, "release_direct3d_device_interfaces"),
    (0x411D70, "release_global_direct3d_renderer_resources"),
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
    (0x430D90, "replace_object_list_texture_refs"),
    (0x4F7450, "g_render_triangle_count"),
    (0x4F7454, "g_render_successful_primitive_count"),
    (0x4F7458, "g_direct3d_renderer"),
    (0x503170, "g_draw_primitive_call_count"),
    (0x503174, "g_current_texture_ref"),
    (0x5031C0, "g_texture_bind_call_count"),
    (0x5031C8, "g_d3d_texture_slots"),
]

TRUSTED_DATA_DECLARATIONS = [
    (0x4F7450, "g_render_triangle_count", "int32_t g_render_triangle_count;"),
    (
        0x4F7454,
        "g_render_successful_primitive_count",
        "int32_t g_render_successful_primitive_count;",
    ),
    (0x4F7458, "g_direct3d_renderer", "Direct3DRenderer g_direct3d_renderer;"),
    (0x503170, "g_draw_primitive_call_count", "int32_t g_draw_primitive_call_count;"),
    (0x503174, "g_current_texture_ref", "TextureRef* g_current_texture_ref;"),
    (0x5031C0, "g_texture_bind_call_count", "int32_t g_texture_bind_call_count;"),
    (0x5031C8, "g_d3d_texture_slots", "Direct3DTexture8** g_d3d_texture_slots;"),
]


def _resolve_function(selector: str) -> tuple[int | None, str]:
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR:
        return None, selector
    return address, selector


def _normalize_type_text(value: str | None) -> str | None:
    if value is None:
        return None
    normalized = value.strip().removesuffix(";")
    normalized = re.sub(r"\s+", " ", normalized)
    normalized = re.sub(r"\s*\(\s*", "(", normalized)
    normalized = re.sub(r"\s*\)\s*", ")", normalized)
    normalized = re.sub(r"\s*,\s*", ", ", normalized)
    normalized = re.sub(r"\s*\*\s*", " *", normalized)
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


def _sync_types(header_path: pathlib.Path) -> int:
    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE)

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

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "parse_errors": parse_errors,
                "applied": applied,
                "unchanged": unchanged,
                "renamed": renamed,
                "names_unchanged": names_unchanged,
                "game_root_owner_graph": game_root_owner_graph,
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
