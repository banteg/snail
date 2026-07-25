from __future__ import annotations

import json
import pathlib
import re
import sys

import ida_bytes
import ida_funcs
import ida_hexrays
import ida_name
import ida_pro
import ida_typeinf
import idc


EXPECTED_STRUCT_SIZES = {
    "Rect": 0x10,
    "WndClassA": 0x28,
    "DevModeA": 0x9C,
}

TRUSTED_FUNCTION_DECLARATIONS = (
    (
        "initialize_game_window_and_input",
        "int __cdecl initialize_game_window_and_input(char *window_name);",
    ),
    (
        "enumerate_input_controllers",
        "int __cdecl enumerate_input_controllers("
        "HWND window, int *out_count);",
    ),
    (
        "game_window_proc",
        "LRESULT __stdcall game_window_proc("
        "HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);",
    ),
)

DATA_ITEMS = (
    {
        "address": 0x4B776C,
        "size": 0x4,
        "name": "g_controller_count_view",
        "declaration": "int g_controller_count_view;",
        "expected_type": "int",
        "create_kind": "dword",
        "accepted_types": {None, "_DWORD", "int"},
        "next_owner": 0x4B7770,
        "next_owner_name": "g_mouse_captured_client_rect",
    },
    {
        "address": 0x4DFAEC,
        "size": 0x4,
        "name": "g_main_window_dc",
        "declaration": "HDC g_main_window_dc;",
        "expected_type": "HDC",
        "create_kind": "dword",
        "accepted_types": {None, "HDC"},
        "next_owner": 0x4DFAF0,
        "next_owner_name": "g_main_window",
    },
    {
        "address": 0x4DFAF0,
        "size": 0x4,
        "name": "g_main_window",
        "declaration": "HWND g_main_window;",
        "expected_type": "HWND",
        "create_kind": "dword",
        "accepted_types": {"int", "HWND"},
        "next_owner": 0x4DFAF4,
        "next_owner_name": "g_fullscreen_active",
    },
    {
        "address": 0x4DFAF4,
        "size": 0x1,
        "name": "g_fullscreen_active",
        "declaration": "unsigned char g_fullscreen_active;",
        "expected_type": "unsigned char",
        "create_kind": "byte",
        "accepted_types": {None, "char", "unsigned char"},
        "next_owner": 0x4DFAF8,
        "next_owner_name": "g_bass_window",
    },
    {
        "address": 0x4DFAF8,
        "size": 0x4,
        "name": "g_bass_window",
        "declaration": "HWND g_bass_window;",
        "expected_type": "HWND",
        "create_kind": "dword",
        "accepted_types": {None, "HWND"},
        "next_owner": 0x4DFAFC,
        "next_owner_name": "g_frame_time_accumulator",
    },
    {
        "address": 0x503268,
        "size": 0x10,
        "name": "g_saved_window_rect",
        "declaration": "Rect g_saved_window_rect;",
        "expected_type": "Rect",
        "create_kind": "bytes",
        "accepted_types": {
            None,
            "AnimationDispatchState",
            "Rect",
        },
        "next_owner": 0x503278,
        "next_owner_name": "g_saved_window_rect_valid",
    },
    {
        "address": 0x503278,
        "size": 0x1,
        "name": "g_saved_window_rect_valid",
        "declaration": "unsigned char g_saved_window_rect_valid;",
        "expected_type": "unsigned char",
        "create_kind": "byte",
        "accepted_types": {None, "char", "unsigned char"},
        "next_owner": 0x50327C,
        "next_owner_name": "g_game_window_instance",
    },
    {
        "address": 0x50327C,
        "size": 0x4,
        "name": "g_game_window_instance",
        "declaration": "HINSTANCE g_game_window_instance;",
        "expected_type": "HINSTANCE",
        "create_kind": "dword",
        "accepted_types": {"uint16_t[2]", "HINSTANCE"},
        "next_owner": 0x503280,
        "next_owner_name": "g_loading_bar_on_texture",
    },
)

UNCLAIMED_GAPS = (
    (0x4DFAF5, 0x4DFAF8),
    (0x503279, 0x50327C),
)

STACK_STRUCT_LVARS = (
    {
        "selector": "initialize_game_window_and_input",
        "definition_address": 0x411B62,
        "stack_offset": 80,
        "accepted_names": {"Rect", "window_rect"},
        "accepted_types": {"__int64", "Rect"},
        "target_name": "window_rect",
        "target_type": "Rect",
    },
    {
        "selector": "initialize_game_window_and_input",
        "definition_address": 0x411A7F,
        "stack_offset": 96,
        "accepted_names": {"WndClass", "window_class"},
        "accepted_types": {"_DWORD[10]", "WndClassA"},
        "target_name": "window_class",
        "target_type": "WndClassA",
    },
    {
        "selector": "initialize_game_window_and_input",
        "definition_address": 0x411B21,
        "stack_offset": 136,
        "accepted_names": {"DevMode", "display_mode"},
        "accepted_types": {"_DWORD[39]", "DevModeA"},
        "target_name": "display_mode",
        "target_type": "DevModeA",
    },
)

DEPENDENT_DECOMPILE_FUNCTIONS = (
    "initialize_game_window_and_input",
    "direct3d_renderer_set_fullscreen_mode",
    "game_startup_and_main_loop",
    "initialize_audio_subsystem",
    "shutdown_bass_audio_window",
    "handle_game_window_activate",
    "handle_game_window_deactivate",
    "show_and_focus_game_window",
    "update_mouse",
    "click_mouse_screen",
    "convert_mouse_screen_xy",
)


def _normalize_type_text(value: str | None) -> str | None:
    if value is None:
        return None
    normalized = value.strip().removesuffix(";")
    normalized = normalized.replace("unsigned __int8", "unsigned char")
    normalized = re.sub(r"\bstruct\s+", "", normalized)
    normalized = re.sub(r"\s+", " ", normalized)
    normalized = re.sub(r"\s*\(\s*", "(", normalized)
    normalized = re.sub(r"\s*\)\s*", ")", normalized)
    normalized = re.sub(r"\s*,\s*", ", ", normalized)
    normalized = re.sub(r"\s*\*\s*", " *", normalized)
    normalized = re.sub(r"\s*\[\s*", "[", normalized)
    normalized = re.sub(r"\s*\]\s*", "]", normalized)
    return normalized.strip()


def _declaration_to_observed_type(
    selector: str,
    declaration: str,
) -> str:
    unnamed = re.sub(
        rf"\b{re.escape(selector)}\s*(?=\()",
        "",
        declaration,
        count=1,
    )
    return _normalize_type_text(unnamed) or ""


def _named_struct_size(name: str) -> int | None:
    value = ida_typeinf.tinfo_t()
    if not value.get_named_type(None, name, ida_typeinf.BTF_STRUCT):
        return None
    return value.get_size()


def _is_auto_data_name(address: int, name: str) -> bool:
    match = re.fullmatch(
        r"(?:byte|word|dword|qword|unk)_([0-9A-Fa-f]+)",
        name,
    )
    return match is not None and int(match.group(1), 16) == address


def _data_kind_matches(address: int, kind: str) -> bool:
    flags = ida_bytes.get_flags(address)
    if kind == "byte":
        return ida_bytes.is_byte(flags)
    if kind == "dword":
        return ida_bytes.is_dword(flags)
    return True


def _create_data_item(address: int, size: int, kind: str) -> bool:
    if kind == "byte":
        return ida_bytes.create_byte(address, size, True)
    if kind == "dword":
        return ida_bytes.create_dword(address, size, True)
    return ida_bytes.create_byte(address, size, True)


def _sync_data_item(
    spec: dict[str, object],
    *,
    apply: bool,
) -> dict[str, object]:
    address = int(spec["address"])
    size = int(spec["size"])
    end = address + size
    name = str(spec["name"])
    declaration = str(spec["declaration"])
    expected_type = _normalize_type_text(str(spec["expected_type"]))
    create_kind = str(spec["create_kind"])
    accepted_types = {
        _normalize_type_text(value)
        for value in spec["accepted_types"]
    }
    next_owner = int(spec["next_owner"])
    next_owner_name = str(spec["next_owner_name"])

    if end > next_owner:
        return {
            "status": "failed",
            "reason": "checked_in_window_owner_overlap",
            "address": hex(address),
            "end": hex(end),
            "next_owner": hex(next_owner),
        }

    item_head = ida_bytes.get_item_head(address)
    item_size = ida_bytes.get_item_size(item_head)
    observed_name = idc.get_name(address)
    observed_type = _normalize_type_text(idc.get_type(address))
    next_head = ida_bytes.get_item_head(next_owner)
    observed_next_name = idc.get_name(next_owner)
    if (
        item_head != address
        or observed_name != name
        or observed_type not in accepted_types
        or next_head < next_owner
        or observed_next_name != next_owner_name
    ):
        return {
            "status": "failed",
            "reason": "unexpected_window_owner_boundary",
            "address": hex(address),
            "expected_name": name,
            "expected_types": sorted(
                "None" if value is None else value
                for value in accepted_types
            ),
            "observed_head": hex(item_head),
            "observed_size": item_size,
            "observed_name": observed_name,
            "observed_type": observed_type,
            "next_owner": hex(next_owner),
            "next_head": hex(next_head),
            "expected_next_name": next_owner_name,
            "observed_next_name": observed_next_name,
        }

    interior_items: dict[int, int] = {}
    unexpected_interior_names = {}
    for interior_address in range(address + 1, end):
        interior_head = ida_bytes.get_item_head(interior_address)
        interior_size = ida_bytes.get_item_size(interior_head)
        interior_items[interior_head] = interior_size
        if interior_head < address or interior_head + interior_size > end:
            return {
                "status": "failed",
                "reason": "window_owner_crosses_checked_extent",
                "address": hex(address),
                "interior_address": hex(interior_address),
                "interior_head": hex(interior_head),
                "interior_size": interior_size,
                "end": hex(end),
            }
        interior_name = idc.get_name(interior_address)
        if interior_name and not _is_auto_data_name(
            interior_address,
            interior_name,
        ):
            unexpected_interior_names[hex(interior_address)] = interior_name
    if unexpected_interior_names:
        return {
            "status": "failed",
            "reason": "unexpected_window_owner_interior_names",
            "address": hex(address),
            "interior_names": unexpected_interior_names,
        }

    already_current = (
        item_size == size
        and observed_type == expected_type
        and _data_kind_matches(address, create_kind)
    )
    if already_current:
        return {
            "status": "unchanged",
            "address": hex(address),
            "size": size,
            "name": name,
            "type": observed_type,
            "next_owner": hex(next_owner),
        }

    if not apply:
        return {
            "status": "pending",
            "address": hex(address),
            "size": size,
            "name": name,
            "expected_type": expected_type,
            "previous_size": item_size,
            "previous_type": observed_type,
            "interior_item_count": len(interior_items),
            "next_owner": hex(next_owner),
        }

    boundary_current = item_size == size
    kind_current = _data_kind_matches(address, create_kind)
    if not boundary_current:
        if not ida_bytes.del_items(
            address,
            ida_bytes.DELIT_SIMPLE,
            size,
        ):
            return {
                "status": "failed",
                "reason": "delete_fragmented_window_owner_failed",
                "address": hex(address),
                "size": size,
            }
    if not boundary_current or not kind_current:
        if not _create_data_item(address, size, create_kind):
            return {
                "status": "failed",
                "reason": "create_window_owner_extent_failed",
                "address": hex(address),
                "size": size,
                "create_kind": create_kind,
            }
    if idc.get_name(address) != name and not idc.set_name(
        address,
        name,
        ida_name.SN_NOWARN | ida_name.SN_FORCE,
    ):
        return {
            "status": "failed",
            "reason": "restore_window_owner_name_failed",
            "address": hex(address),
            "name": name,
        }
    if not idc.SetType(address, declaration):
        return {
            "status": "failed",
            "reason": "set_window_owner_type_failed",
            "address": hex(address),
            "declaration": declaration,
        }

    verified_head = ida_bytes.get_item_head(address)
    verified_size = ida_bytes.get_item_size(verified_head)
    verified_name = idc.get_name(address)
    verified_type = _normalize_type_text(idc.get_type(address))
    verified_next_head = ida_bytes.get_item_head(next_owner)
    if (
        verified_head != address
        or verified_size != size
        or verified_name != name
        or verified_type != expected_type
        or verified_next_head < next_owner
    ):
        return {
            "status": "failed",
            "reason": "window_owner_readback_failed",
            "address": hex(address),
            "expected_size": size,
            "expected_name": name,
            "expected_type": expected_type,
            "observed_head": hex(verified_head),
            "observed_size": verified_size,
            "observed_name": verified_name,
            "observed_type": verified_type,
            "next_owner": hex(next_owner),
            "next_head": hex(verified_next_head),
        }

    return {
        "status": "applied",
        "address": hex(address),
        "size": verified_size,
        "name": verified_name,
        "type": verified_type,
        "previous_size": item_size,
        "previous_type": observed_type,
        "interior_item_count": len(interior_items),
        "next_owner": hex(next_owner),
    }


def _verify_unclaimed_gaps() -> dict[str, object]:
    results = []
    failed = []
    for start, end in UNCLAIMED_GAPS:
        entries = []
        for address in range(start, end):
            head = ida_bytes.get_item_head(address)
            size = ida_bytes.get_item_size(head)
            name = idc.get_name(address)
            type_text = _normalize_type_text(idc.get_type(address))
            entry = {
                "address": hex(address),
                "head": hex(head),
                "size": size,
                "name": name,
                "type": type_text,
            }
            entries.append(entry)
            if (
                head != address
                or size != 1
                or (name and not _is_auto_data_name(address, name))
                or type_text is not None
            ):
                failed.append(entry)
        results.append(
            {
                "extent": f"{start:#x}..{end:#x}",
                "status": "verified" if not any(
                    start <= int(entry["address"], 0) < end
                    for entry in failed
                ) else "failed",
                "entries": entries,
            }
        )
    return {
        "status": "failed" if failed else "verified",
        "gaps": results,
        "failed_entries": failed,
    }


def _sync_stack_struct_lvar(spec: dict[str, object]) -> dict[str, object]:
    selector = str(spec["selector"])
    definition_address = int(spec["definition_address"])
    stack_offset = int(spec["stack_offset"])
    accepted_names = set(spec["accepted_names"])
    accepted_types = {
        _normalize_type_text(value)
        for value in spec["accepted_types"]
    }
    target_name = str(spec["target_name"])
    target_type_name = str(spec["target_type"])

    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR or ida_funcs.get_func(address) is None:
        return {
            "status": "failed",
            "reason": "missing_function",
            "selector": selector,
        }

    ida_hexrays.mark_cfunc_dirty(address, True)
    cfunc = ida_hexrays.decompile(address)
    candidates = [
        lvar
        for lvar in cfunc.get_lvars()
        if not lvar.is_arg_var
        and lvar.is_stk_var()
        and lvar.defea == definition_address
        and lvar.get_stkoff() == stack_offset
        and lvar.name in accepted_names
        and _normalize_type_text(str(lvar.type())) in accepted_types
    ]
    if len(candidates) != 1:
        return {
            "status": "failed",
            "reason": "unexpected_window_stack_struct_candidates",
            "selector": selector,
            "definition_address": hex(definition_address),
            "stack_offset": stack_offset,
            "target_name": target_name,
            "candidate_count": len(candidates),
        }

    lvar = candidates[0]
    observed_type = _normalize_type_text(str(lvar.type()))
    if lvar.name == target_name and observed_type == target_type_name:
        return {
            "status": "unchanged",
            "selector": selector,
            "definition_address": hex(definition_address),
            "stack_offset": stack_offset,
            "name": lvar.name,
            "type": observed_type,
        }

    target_type = ida_typeinf.tinfo_t()
    if not target_type.get_named_type(
        None,
        target_type_name,
        ida_typeinf.BTF_STRUCT,
    ):
        return {
            "status": "failed",
            "reason": "missing_window_stack_struct_type",
            "selector": selector,
            "target_type": target_type_name,
        }

    before_name = lvar.name
    before_type = str(lvar.type())
    info = ida_hexrays.lvar_saved_info_t()
    info.ll = ida_hexrays.lvar_locator_t(lvar.location, lvar.defea)
    info.name = target_name
    info.type = target_type
    if not ida_hexrays.modify_user_lvar_info(
        address,
        ida_hexrays.MLI_NAME | ida_hexrays.MLI_TYPE,
        info,
    ):
        return {
            "status": "failed",
            "reason": "modify_window_stack_struct_failed",
            "selector": selector,
            "target_name": target_name,
            "target_type": target_type_name,
        }

    ida_hexrays.mark_cfunc_dirty(address, True)
    verified_cfunc = ida_hexrays.decompile(address)
    verified = [
        candidate
        for candidate in verified_cfunc.get_lvars()
        if not candidate.is_arg_var
        and candidate.is_stk_var()
        and candidate.defea == definition_address
        and candidate.get_stkoff() == stack_offset
        and candidate.name == target_name
        and _normalize_type_text(str(candidate.type())) == target_type_name
    ]
    if len(verified) != 1:
        return {
            "status": "failed",
            "reason": "window_stack_struct_readback_failed",
            "selector": selector,
            "definition_address": hex(definition_address),
            "stack_offset": stack_offset,
            "target_name": target_name,
            "target_type": target_type_name,
            "candidate_count": len(verified),
        }

    return {
        "status": "applied",
        "selector": selector,
        "definition_address": hex(definition_address),
        "stack_offset": stack_offset,
        "before_name": before_name,
        "before_type": before_type,
        "name": verified[0].name,
        "type": _normalize_type_text(str(verified[0].type())),
    }


def _sync_types(header_path: pathlib.Path) -> int:
    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE)
    struct_sizes = {
        name: _named_struct_size(name)
        for name in EXPECTED_STRUCT_SIZES
    }
    size_mismatches = {
        name: {"expected": expected, "observed": struct_sizes[name]}
        for name, expected in EXPECTED_STRUCT_SIZES.items()
        if struct_sizes[name] != expected
    }

    applied = 0
    unchanged = 0
    missing = []
    failed = []

    data_preflight = []
    data_items = []
    unclaimed_gaps: dict[str, object] = {
        "status": "not_run",
        "reason": "type_contract_not_verified",
    }
    if not parse_errors and not size_mismatches:
        data_preflight = [
            _sync_data_item(spec, apply=False)
            for spec in DATA_ITEMS
        ]
        failed.extend(
            {"data_item_preflight": result}
            for result in data_preflight
            if result.get("status") == "failed"
        )

        unclaimed_gaps = _verify_unclaimed_gaps()
        if unclaimed_gaps.get("status") == "failed":
            failed.append({"unclaimed_gaps": unclaimed_gaps})

        if not failed:
            data_items = [
                _sync_data_item(spec, apply=True)
                for spec in DATA_ITEMS
            ]
            failed.extend(
                {"data_item": result}
                for result in data_items
                if result.get("status") == "failed"
            )

    for selector, declaration in TRUSTED_FUNCTION_DECLARATIONS:
        address = idc.get_name_ea_simple(selector)
        if address == idc.BADADDR or ida_funcs.get_func(address) is None:
            missing.append(
                {"selector": selector, "reason": "missing_function"}
            )
            continue
        expected = _declaration_to_observed_type(selector, declaration)
        current = _normalize_type_text(idc.get_type(address))
        if current == expected:
            unchanged += 1
        elif not idc.SetType(address, declaration):
            failed.append(
                {"selector": selector, "reason": "set_type_failed"}
            )
            continue
        else:
            observed = _normalize_type_text(idc.get_type(address))
            if observed != expected:
                failed.append(
                    {
                        "selector": selector,
                        "reason": "function_type_readback_failed",
                        "observed": observed,
                        "expected": expected,
                    }
                )
                continue
            applied += 1

    stack_struct_lvars = []
    if not parse_errors and not size_mismatches and not failed:
        stack_struct_lvars = [
            _sync_stack_struct_lvar(spec)
            for spec in STACK_STRUCT_LVARS
        ]
        failed.extend(
            {"stack_struct_lvar": result}
            for result in stack_struct_lvars
            if result.get("status") == "failed"
        )

    invalidated = []
    for selector in DEPENDENT_DECOMPILE_FUNCTIONS:
        address = idc.get_name_ea_simple(selector)
        if address == idc.BADADDR or ida_funcs.get_func(address) is None:
            missing.append(
                {
                    "selector": selector,
                    "reason": "missing_dependent_function",
                }
            )
            continue
        ida_hexrays.mark_cfunc_dirty(address, True)
        invalidated.append(
            {"selector": selector, "address": hex(address)}
        )

    if size_mismatches:
        failed.append(
            {
                "selector": "win32_window_structs",
                "reason": "owner_size_mismatch",
                "types": size_mismatches,
            }
        )

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "parse_errors": parse_errors,
                "struct_sizes": struct_sizes,
                "data_preflight": data_preflight,
                "data_items": data_items,
                "unclaimed_gaps": unclaimed_gaps,
                "stack_struct_lvars": stack_struct_lvars,
                "applied": applied,
                "unchanged": unchanged,
                "invalidated": invalidated,
                "missing": missing,
                "failed": failed,
            },
            indent=2,
        )
    )
    return 1 if parse_errors or size_mismatches or missing or failed else 0


def main() -> None:
    argv = list(idc.ARGV)
    if len(argv) < 2:
        print(
            "usage: apply_win32_window_state_types.py <header-path>",
            file=sys.stderr,
        )
        ida_pro.qexit(2)
        return

    header_path = pathlib.Path(argv[1]).resolve()
    ida_pro.qexit(_sync_types(header_path))


if __name__ == "__main__":
    main()
