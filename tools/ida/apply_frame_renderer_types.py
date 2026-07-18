from __future__ import annotations

import json
import pathlib
import re
import sys

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


EXPECTED_OWNER_SIZES = {
    "RenderableBod": 0x80,
    "Sprite": 0xB4,
    "ObjectRenderVertex": 0x18,
    "SpriteDepthNode": 0x18,
    "FrameColor4f": 0x10,
    "FrontendFade": 0x14,
    "GameInput": 0x70,
    "GamePlayer": 0x1F8,
    "FrameBodBase": 0x38,
    "FrameBodList": 0xC,
    "BodNode": 0x10,
    "BodList": 0xC,
    "FrameRenderableBod": 0x80,
    "FrameRenderCamera": 0xC8,
    "FrameOverlay": 0x14C,
    "FrameRenderCameraSlot": 0x28,
    "Track": 0x24,
    "BorderStackEntry": 0x8,
    "BorderStack": 0x64C,
    "BorderRecord": 0x724,
    "BorderManager": 0x435B4,
    "GameRoot": 0x12E6FF4,
}


TRUSTED_NAMES = [
    (0x408000, "initialize_game_player"),
    (0x4107D0, "update_frontend_state_machine"),
    (0x4137F0, "draw_sprite_quad"),
    (0x44E410, "update_sprite_facing_angle"),
    (0x4119C0, "initialize_game_window_and_input_wrapper"),
    (0x4119D0, "initialize_game_window_and_input"),
    (0x44C3B0, "is_mouse_captured"),
    (0x44C3C0, "capture_mouse_cursor"),
    (0x44C400, "release_mouse_cursor"),
    (0x4972F4, "g_game_player_callback_table"),
    (0x4DFB10, "g_post_sprite_bods"),
    (0x4E5510, "g_sprite_depth_nodes"),
    (0x4F7050, "g_sprite_depth_buckets"),
    (0x814C94, "g_sprite_active_heads"),
]

TRUSTED_FUNCTION_DECLARATIONS = [
    (
        "initialize_game_window_and_input_wrapper",
        "int __cdecl initialize_game_window_and_input_wrapper(char *window_name);",
    ),
    (
        "initialize_game_window_and_input",
        "int __cdecl initialize_game_window_and_input(char *window_name);",
    ),
    (
        "kill_all_borders",
        "void __thiscall kill_all_borders(BorderManager *manager);",
    ),
    (
        "set_border_justify_centre",
        "void __thiscall set_border_justify_centre("
        "BorderManager *manager, float justify_centre);",
    ),
    (
        "allocate_border",
        "FrontendWidget *__thiscall allocate_border(BorderManager *manager);",
    ),
    (
        "activate_all_borders",
        "void __thiscall activate_all_borders(BorderManager *manager);",
    ),
    (
        "hide_all_borders",
        "void __thiscall hide_all_borders(BorderManager *manager);",
    ),
    (
        "unhide_all_borders",
        "void __thiscall unhide_all_borders(BorderManager *manager);",
    ),
    (
        "queue_frontend_widget_flag_after_delay",
        "char __thiscall queue_frontend_widget_flag_after_delay("
        "BorderManager *manager, FrontendWidget *widget, int32_t queued_flags);",
    ),
    (
        "update_border_manager",
        "void __thiscall update_border_manager(BorderManager *manager);",
    ),
    (
        "initialize_border_record",
        "BorderRecord *__thiscall initialize_border_record(BorderRecord *record);",
    ),
    (
        "initialize_game_player",
        "GamePlayer *__thiscall initialize_game_player(GamePlayer *player);",
    ),
    (
        "update_frontend_state_machine",
        "void __thiscall update_frontend_state_machine(GamePlayer *player);",
    ),
    (
        "is_mouse_captured",
        "uint8_t __thiscall is_mouse_captured(MouseCursorState *mouse);",
    ),
    (
        "capture_mouse_cursor",
        "void __thiscall capture_mouse_cursor(MouseCursorState *mouse);",
    ),
    (
        "release_mouse_cursor",
        "void __thiscall release_mouse_cursor(MouseCursorState *mouse);",
    ),
    (
        "initialize_game_assets_and_world",
        "uint8_t __thiscall initialize_game_assets_and_world(GameRoot *game);",
    ),
    (
        "run_frame_update",
        "int __thiscall run_frame_update(GameRoot *game);",
    ),
    (
        "render_game_frame",
        "void __thiscall render_game_frame(GameRoot *game);",
    ),
    (
        "draw_sprite_quad",
        "int __cdecl draw_sprite_quad(Vec3 *position, Sprite *sprite);",
    ),
    (
        "update_sprite_facing_angle",
        "void __thiscall update_sprite_facing_angle("
        "Sprite *sprite, const TransformMatrix *matrix);",
    ),
    (
        "select_level_track_texture_set",
        "void __thiscall select_level_track_texture_set(Track *track, int32_t texture_set);",
    ),
]

TRUSTED_DATA_DECLARATIONS = [
    (
        0x4972F4,
        "g_game_player_callback_table",
        "void *g_game_player_callback_table;",
    ),
    (
        0x4DF904,
        "g_game_base",
        "GameRoot *g_game_base;",
    ),
    (
        0x4DFB10,
        "g_post_sprite_bods",
        "RenderableBod *g_post_sprite_bods;",
    ),
    (
        0x4E5510,
        "g_sprite_depth_nodes",
        "SpriteDepthNode g_sprite_depth_nodes[3000];",
    ),
    (
        0x4F7050,
        "g_sprite_depth_buckets",
        "SpriteDepthNode *g_sprite_depth_buckets[256];",
    ),
    (
        0x814C94,
        "g_sprite_active_heads",
        "Sprite *g_sprite_active_heads[5];",
    ),
]


def _normalize_type_text(value: str | None) -> str | None:
    if value is None:
        return None
    normalized = value.strip().removesuffix(";")
    normalized = re.sub(r"\s+", " ", normalized)
    normalized = re.sub(r"\s*\(\s*", "(", normalized)
    normalized = re.sub(r"\s*\)\s*", ")", normalized)
    normalized = re.sub(r"\s*,\s*", ", ", normalized)
    normalized = re.sub(r"\s*\*\s*", " *", normalized)
    normalized = re.sub(r"\s*\[\s*", "[", normalized)
    normalized = re.sub(r"\s*\]", "]", normalized)
    return normalized.strip()


def _declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\b", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


def _named_struct_size(name: str) -> int | None:
    value = ida_typeinf.tinfo_t()
    if not value.get_named_type(None, name, ida_typeinf.BTF_STRUCT):
        return None
    return value.get_size()


def _sync_draw_sprite_vertex_lvar() -> dict[str, object]:
    selector = "draw_sprite_quad"
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
    split_definition_address = 0x413933
    cfunc = ida_hexrays.decompile(address)
    existing = [
        lvar
        for lvar in cfunc.get_lvars()
        if not lvar.is_arg_var
        and lvar.name == "vertices"
        and _normalize_type_text(str(lvar.type())) == expected_type
        and lvar.defea == split_definition_address
    ]
    if len(existing) == 1:
        return {
            "status": "unchanged",
            "selector": selector,
            "name": existing[0].name,
            "type": str(existing[0].type()),
            "definition_address": hex(existing[0].defea),
        }
    if existing:
        return {
            "status": "failed",
            "reason": "unexpected_existing_vertex_lvars",
            "selector": selector,
            "candidate_count": len(existing),
        }

    sources = [
        lvar
        for lvar in cfunc.get_lvars()
        if lvar.is_arg_var
        and lvar.is_stk_var()
        and lvar.get_stkoff() == 120
        and lvar.name == "position"
        and _normalize_type_text(str(lvar.type())) == "Vec3 *"
    ]
    if len(sources) != 1:
        return {
            "status": "failed",
            "reason": "unexpected_position_argument_candidates",
            "selector": selector,
            "candidate_count": len(sources),
        }

    info = ida_hexrays.lvar_saved_info_t()
    info.ll = ida_hexrays.lvar_locator_t(
        sources[0].location,
        split_definition_address,
    )
    info.name = "vertices"
    info.type = local_type
    info.set_split_lvar()
    if not ida_hexrays.modify_user_lvar_info(
        address,
        ida_hexrays.MLI_NAME | ida_hexrays.MLI_TYPE | ida_hexrays.MLI_SET_FLAGS,
        info,
    ):
        return {
            "status": "failed",
            "reason": "modify_split_vertex_lvar_failed",
            "selector": selector,
        }

    ida_hexrays.mark_cfunc_dirty(address, True)
    verified_cfunc = ida_hexrays.decompile(address)
    verified = [
        lvar
        for lvar in verified_cfunc.get_lvars()
        if not lvar.is_arg_var
        and lvar.name == "vertices"
        and _normalize_type_text(str(lvar.type())) == expected_type
        and lvar.defea == split_definition_address
    ]
    if len(verified) != 1:
        return {
            "status": "failed",
            "reason": "split_vertex_lvar_readback_failed",
            "selector": selector,
            "candidate_count": len(verified),
        }

    return {
        "status": "applied",
        "selector": selector,
        "name": verified[0].name,
        "type": str(verified[0].type()),
        "definition_address": hex(verified[0].defea),
    }


def _normalize_struct_pointer_type(value: str | None) -> str:
    normalized = (_normalize_type_text(value) or "").removeprefix("struct ")
    return re.sub(r"\s+", "", normalized)


def _sync_render_pointer_lvar(
    *,
    definition_address: int,
    accepted_names: set[str],
    accepted_types: set[str],
    target_name: str,
    target_struct_name: str,
    pointer_depth: int,
) -> dict[str, object]:
    """Persist one evidence-backed pointer relationship in Render()."""
    selector = "render_game_frame"
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR:
        return {"status": "failed", "reason": "missing_function", "selector": selector}

    target_pointer_type = _normalize_struct_pointer_type(
        f"{target_struct_name} {'*' * pointer_depth}"
    )
    normalized_accepted_types = {
        _normalize_struct_pointer_type(value) for value in accepted_types
    }
    cfunc = ida_hexrays.decompile(address)
    candidates = [
        lvar
        for lvar in cfunc.get_lvars()
        if not lvar.is_arg_var
        and not lvar.is_stk_var()
        and lvar.defea == definition_address
        and lvar.name in accepted_names
        and _normalize_struct_pointer_type(str(lvar.type()))
        in normalized_accepted_types
    ]
    if len(candidates) != 1:
        return {
            "status": "failed",
            "reason": "unexpected_render_pointer_lvar_candidates",
            "candidate_count": len(candidates),
            "definition_address": hex(definition_address),
            "target_name": target_name,
            "selector": selector,
        }

    lvar = candidates[0]
    observed_type = _normalize_struct_pointer_type(str(lvar.type()))
    if lvar.name == target_name and observed_type == target_pointer_type:
        return {
            "status": "unchanged",
            "name": lvar.name,
            "type": str(lvar.type()),
            "definition_address": hex(lvar.defea),
            "selector": selector,
        }

    target_type = ida_typeinf.tinfo_t()
    if not target_type.get_named_type(
        None,
        target_struct_name,
        ida_typeinf.BTF_STRUCT,
    ):
        return {
            "status": "failed",
            "reason": "missing_render_pointer_target_type",
            "target_struct_name": target_struct_name,
            "selector": selector,
        }

    pointer_type = target_type
    for _ in range(pointer_depth):
        next_pointer_type = ida_typeinf.tinfo_t()
        if not next_pointer_type.create_ptr(pointer_type):
            return {
                "status": "failed",
                "reason": "create_render_pointer_type_failed",
                "target_struct_name": target_struct_name,
                "pointer_depth": pointer_depth,
                "selector": selector,
            }
        pointer_type = next_pointer_type

    info = ida_hexrays.lvar_saved_info_t()
    info.ll = ida_hexrays.lvar_locator_t(lvar.location, lvar.defea)
    info.name = target_name
    info.type = pointer_type
    if not ida_hexrays.modify_user_lvar_info(
        address,
        ida_hexrays.MLI_NAME | ida_hexrays.MLI_TYPE,
        info,
    ):
        return {
            "status": "failed",
            "reason": "modify_render_pointer_lvar_failed",
            "target_name": target_name,
            "selector": selector,
        }

    ida_hexrays.mark_cfunc_dirty(address, True)
    verified_cfunc = ida_hexrays.decompile(address)
    verified = [
        candidate
        for candidate in verified_cfunc.get_lvars()
        if not candidate.is_arg_var
        and candidate.defea == definition_address
        and candidate.name == target_name
    ]
    verified_type = (
        _normalize_struct_pointer_type(str(verified[0].type()))
        if len(verified) == 1
        else None
    )
    if len(verified) != 1 or verified_type != target_pointer_type:
        return {
            "status": "failed",
            "reason": "render_pointer_lvar_readback_failed",
            "candidate_count": len(verified),
            "observed_type": verified_type,
            "target_type": target_pointer_type,
            "target_name": target_name,
            "selector": selector,
        }

    return {
        "status": "applied",
        "before_name": lvar.name,
        "before_type": str(lvar.type()),
        "name": verified[0].name,
        "type": str(verified[0].type()),
        "definition_address": hex(verified[0].defea),
        "selector": selector,
    }


RENDER_POINTER_LVAR_SPECS = (
    (
        "active_bod",
        0x40A64E,
        {"first", "bod"},
        {"BodNode *", "RenderableBod *"},
        "bod",
        "RenderableBod",
        1,
    ),
    (
        "depth_bucket_cursor",
        0x40A8C0,
        {"v52", "depth_bucket_cursor"},
        {"int *", "SpriteDepthNode **"},
        "depth_bucket_cursor",
        "SpriteDepthNode",
        2,
    ),
    (
        "depth_bucket_sprite",
        0x40A8CB,
        {"sprite", "v54"},
        {"int", "Sprite *"},
        "sprite",
        "Sprite",
        1,
    ),
    (
        "post_cursor",
        0x40A991,
        {"v58", "post_cursor"},
        {"int *", "RenderableBod **"},
        "post_cursor",
        "RenderableBod",
        2,
    ),
)


def _sync_types(header_path: pathlib.Path) -> int:
    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE)
    owner_sizes = {name: _named_struct_size(name) for name in EXPECTED_OWNER_SIZES}
    applied = 0
    unchanged = 0
    renamed = 0
    names_unchanged = 0
    missing = []
    failed = [
        {
            "selector": name,
            "reason": "owner_size_mismatch",
            "expected": expected,
            "observed": owner_sizes[name],
        }
        for name, expected in EXPECTED_OWNER_SIZES.items()
        if owner_sizes[name] != expected
    ]

    for address, name in TRUSTED_NAMES:
        if idc.get_name(address) == name:
            names_unchanged += 1
            continue
        if not idc.set_name(address, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
            failed.append({"address": hex(address), "selector": name, "reason": "rename_failed"})
            continue
        renamed += 1

    for selector, declaration in TRUSTED_FUNCTION_DECLARATIONS:
        address = idc.get_name_ea_simple(selector)
        if address == idc.BADADDR or ida_funcs.get_func(address) is None:
            missing.append({"selector": selector, "reason": "missing_function"})
            continue

        expected = _declaration_to_observed_type(selector, declaration)
        if _normalize_type_text(idc.get_type(address)) == expected:
            unchanged += 1
            continue
        if not idc.SetType(address, declaration):
            failed.append({"selector": selector, "reason": "set_type_failed"})
            continue
        observed = idc.get_type(address)
        if _normalize_type_text(observed) != expected:
            failed.append(
                {
                    "selector": selector,
                    "reason": "verification_failed",
                    "observed": observed,
                    "expected": expected,
                }
            )
            continue
        applied += 1

    for address, selector, declaration in TRUSTED_DATA_DECLARATIONS:
        expected = _declaration_to_observed_type(selector, declaration)
        if _normalize_type_text(idc.get_type(address)) == expected:
            unchanged += 1
            continue
        if not idc.SetType(address, declaration):
            failed.append({"selector": selector, "reason": "set_data_type_failed"})
            continue
        observed = idc.get_type(address)
        if _normalize_type_text(observed) != expected:
            failed.append(
                {
                    "selector": selector,
                    "reason": "data_verification_failed",
                    "observed": observed,
                    "expected": expected,
                }
            )
            continue
        applied += 1

    game_root_owner_graph = sync_game_root_owner_graph(require=False)
    if game_root_owner_graph.get("status") == "failed":
        failed.append(
            {"selector": "GameRoot", "owner_graph": game_root_owner_graph}
        )

    draw_sprite_vertex_lvar = _sync_draw_sprite_vertex_lvar()
    if draw_sprite_vertex_lvar.get("status") == "failed":
        failed.append(
            {
                "selector": "draw_sprite_quad",
                "vertex_lvar": draw_sprite_vertex_lvar,
            }
        )

    render_pointer_lvars = {}
    for (
        result_name,
        definition_address,
        accepted_names,
        accepted_types,
        target_name,
        target_struct_name,
        pointer_depth,
    ) in RENDER_POINTER_LVAR_SPECS:
        result = _sync_render_pointer_lvar(
            definition_address=definition_address,
            accepted_names=accepted_names,
            accepted_types=accepted_types,
            target_name=target_name,
            target_struct_name=target_struct_name,
            pointer_depth=pointer_depth,
        )
        render_pointer_lvars[result_name] = result
        if result.get("status") == "failed":
            failed.append(
                {"selector": "render_game_frame", "lvar": result_name, "result": result}
            )

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
                "draw_sprite_vertex_lvar": draw_sprite_vertex_lvar,
                "render_pointer_lvars": render_pointer_lvars,
                "missing": missing,
                "failed": failed,
            },
            indent=2,
        )
    )
    return 1 if parse_errors or missing or failed else 0


def main() -> None:
    argv = list(idc.ARGV)
    if len(argv) != 2:
        print("usage: apply_frame_renderer_types.py <header-path>", file=sys.stderr)
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
