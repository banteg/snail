import json
import pathlib
import re
import sys

import ida_funcs
import ida_name
import ida_pro
import idc


TRUSTED_DECLARATIONS = [
    (
        "noop_this_constructor",
        "void* __thiscall noop_this_constructor(void* self);",
    ),
    (
        "initialize_object",
        "int __thiscall initialize_object(Object* object);",
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
        "initialize_directx_loader",
        "void __thiscall initialize_directx_loader(DirectXLoader* loader);",
    ),
    (
        "load_x_mesh",
        "void __thiscall load_x_mesh(DirectXLoader* loader, char* mesh_path, Object* object, uint8_t options_flags);",
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
        "load_object_definition",
        "int __cdecl load_object_definition(char* path, Object* object);",
    ),
    (
        "create_object_vertex_buffer_resource",
        "ObjectRenderBuffers* __thiscall create_object_vertex_buffer_resource(VertexBufferFactory* factory, int vertex_count, int fvf);",
    ),
    (
        "create_object_index_buffer_resource",
        "ObjectIndexBuffer* __thiscall create_object_index_buffer_resource(IndexBufferFactory* factory, int index_count);",
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
        "render_object",
        "int __cdecl render_object(Object* object, TransformMatrix* matrix, int texture_scroll_bits, float texture_v, Color4f* color, char after_sprites);",
    ),
]

TRUSTED_NAMES = [
    (0x4114B0, "create_object_vertex_buffer_resource"),
    (0x4115D0, "create_object_index_buffer_resource"),
    (0x411630, "initialize_direct3d_renderer_defaults"),
    (0x4118B0, "reset_direct3d_render_state"),
    (0x411D70, "release_global_direct3d_renderer_resources"),
    (0x4129C0, "initialize_direct3d_renderer"),
    (0x414270, "direct3d_renderer_set_fullscreen_mode"),
    (0x4143C0, "restore_texture_ref_stage_states"),
    (0x414600, "query_direct3d_device_caps"),
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
    return normalized.strip()


def _declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\s*(?=\()", "", declaration, count=1)
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
    ida_pro.qexit(_sync_types(header_path))


if __name__ == "__main__":
    main()
