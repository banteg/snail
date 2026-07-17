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


TRUSTED_NAMES = [
    (0x4972F0, "g_game_input_callback_table"),
    (0x50333C, "g_input_controller_slot0"),
    (0x503374, "g_input_controller_slot1"),
    (0x432440, "read_pressed_text_input_key_code"),
    (0x4327E0, "read_repeating_text_input_key_code"),
    (0x4321C0, "update_input_controller_pointer_region"),
    (0x4323A0, "set_input_controller_pointer_authored_xy"),
    (0x50339C, "g_text_input_repeat_step"),
    (0x5108B8, "g_text_input_repeat_accumulator"),
    (0x53C7F5, "g_text_input_last_repeat_code"),
    (0x508890, "g_input_region_top"),
    (0x508898, "g_input_region_bottom"),
    (0x5088A0, "g_input_region_left"),
    (0x5088A8, "g_input_region_right"),
    (0x44BBB0, "initialize_mouse_authored_scale_from_clip_rect"),
    (0x44BBD0, "update_mouse_authored_scale"),
    (0x44BC20, "resolve_uncaptured_cursor_sensitivity_scale"),
    (0x44BC50, "update_mouse"),
    (0x44C050, "set_hide_system_cursor_flag"),
    (0x44C060, "click_mouse_screen"),
    (0x44C100, "convert_mouse_screen_xy"),
    (0x44C2C0, "release_mouse_input"),
    (0x44C310, "initialize_mouse_input"),
    (0x44B3C0, "enumerate_input_controllers"),
    (0x44B490, "append_enumerated_input_controller_callback"),
    (0x44B4E0, "configure_input_controller_axis_range_callback"),
    (0x44B570, "update_joystick_input"),
    (0x44B770, "release_input_controllers"),
    (0x777B2C, "g_joystick_count"),
    (0x777B30, "g_joystick_input"),
    (0x777B34, "g_joystick_devices"),
    (0x777D58, "g_mouse_live_x"),
    (0x777D60, "g_mouse_live_y"),
    (0x777D68, "g_mouse_screen_to_authored_y_scale"),
    (0x777D6C, "g_mouse_screen_to_authored_x_scale"),
    (0x777D70, "g_hide_system_cursor_flag"),
    (0x777D74, "g_mouse_screen_y"),
    (0x777D7C, "g_mouse_screen_x"),
    (0x777D88, "g_mouse_clip_rect"),
    (0x777D98, "g_mouse_input"),
    (0x777D9C, "g_mouse_device"),
]


TRUSTED_DECLARATIONS = [
    (
        "update_input_controller_pointer_region",
        "void __cdecl update_input_controller_pointer_region(int slot, int left, int top, int right, int bottom, int x, int y, int pointer_value, char button_a, char button_b, char button_c, char capture_when_outside, char force_clamp);",
    ),
    (
        "set_input_controller_pointer_authored_xy",
        "void *__cdecl set_input_controller_pointer_authored_xy(int slot, float authored_x, float authored_y);",
    ),
    (
        "read_pressed_text_input_key_code",
        "char __cdecl read_pressed_text_input_key_code();",
    ),
    (
        "read_repeating_text_input_key_code",
        "char __cdecl read_repeating_text_input_key_code();",
    ),
    (
        "initialize_input",
        "void __thiscall initialize_input(InputState *state);",
    ),
    (
        "update_input",
        "void __thiscall update_input(InputState *state);",
    ),
    (
        "update_game_input",
        "void __thiscall update_game_input(GameInput *game_input);",
    ),
    (
        "copy_active_input_controller_state",
        "float *__cdecl copy_active_input_controller_state(int controller_slot, InputButtonFlag *out_buttons, float *out_axis_x, float *out_axis_y, float *out_authored_x, float *out_authored_y, float *out_pointer_value, float *out_pointer_x, float *out_pointer_y);",
    ),
    (
        "initialize_mouse_authored_scale_from_clip_rect",
        "int __cdecl initialize_mouse_authored_scale_from_clip_rect();",
    ),
    (
        "update_mouse_authored_scale",
        "int __cdecl update_mouse_authored_scale(float authored_width, float authored_height);",
    ),
    (
        "resolve_uncaptured_cursor_sensitivity_scale",
        "float __cdecl resolve_uncaptured_cursor_sensitivity_scale(float scale);",
    ),
    (
        "update_mouse",
        "int __cdecl update_mouse(int window_handle);",
    ),
    (
        "set_hide_system_cursor_flag",
        "char __cdecl set_hide_system_cursor_flag(char hidden);",
    ),
    (
        "click_mouse_screen",
        "void *__cdecl click_mouse_screen(int slot, int x, int y);",
    ),
    (
        "convert_mouse_screen_xy",
        "void __cdecl convert_mouse_screen_xy(int sensitivity_slot, float *x, float *y);",
    ),
    (
        "release_mouse_input",
        "int __cdecl release_mouse_input();",
    ),
    (
        "initialize_mouse_input",
        "int __cdecl initialize_mouse_input(int window_handle);",
    ),
    (
        "enumerate_input_controllers",
        "int __cdecl enumerate_input_controllers(int window_handle, int *out_count);",
    ),
    (
        "append_enumerated_input_controller_callback",
        "int __stdcall append_enumerated_input_controller_callback(DIDEVICEINSTANCEA *instance, void *context);",
    ),
    (
        "configure_input_controller_axis_range_callback",
        "int __stdcall configure_input_controller_axis_range_callback(DIDEVICEOBJECTINSTANCEA *instance, void *context);",
    ),
    (
        "update_joystick_input",
        "int __cdecl update_joystick_input();",
    ),
    (
        "release_input_controllers",
        "int __cdecl release_input_controllers();",
    ),
]

TRUSTED_DATA_DECLARATIONS = [
    (0x4972F0, "g_game_input_callback_table", "void *g_game_input_callback_table;"),
    (
        0x50333C,
        "g_input_controller_slot0",
        "InputControllerSlot g_input_controller_slot0;",
    ),
    (
        0x503374,
        "g_input_controller_slot1",
        "InputControllerSlot g_input_controller_slot1;",
    ),
    (0x508890, "g_input_region_top", "int g_input_region_top[2];"),
    (0x508898, "g_input_region_bottom", "int g_input_region_bottom[2];"),
    (0x5088A0, "g_input_region_left", "int g_input_region_left[2];"),
    (0x5088A8, "g_input_region_right", "int g_input_region_right[2];"),
    (0x50339C, "g_text_input_repeat_step", "float g_text_input_repeat_step;"),
    (
        0x5108B8,
        "g_text_input_repeat_accumulator",
        "float g_text_input_repeat_accumulator;",
    ),
    (
        0x53C7F5,
        "g_text_input_last_repeat_code",
        "unsigned char g_text_input_last_repeat_code;",
    ),
    (0x777D58, "g_mouse_live_x", "float g_mouse_live_x[2];"),
    (0x777D60, "g_mouse_live_y", "float g_mouse_live_y[2];"),
    (0x777D68, "g_mouse_screen_to_authored_y_scale", "float g_mouse_screen_to_authored_y_scale;"),
    (0x777D6C, "g_mouse_screen_to_authored_x_scale", "float g_mouse_screen_to_authored_x_scale;"),
    (0x777D70, "g_hide_system_cursor_flag", "uint8_t g_hide_system_cursor_flag;"),
    (0x777D74, "g_mouse_screen_y", "int g_mouse_screen_y[2];"),
    (0x777D7C, "g_mouse_screen_x", "int g_mouse_screen_x[2];"),
    (0x777D88, "g_mouse_clip_rect", "MouseScreenRect g_mouse_clip_rect;"),
    (0x777D98, "g_mouse_input", "void *g_mouse_input;"),
    (0x777D9C, "g_mouse_device", "void *g_mouse_device;"),
    (0x777B2C, "g_joystick_count", "int g_joystick_count;"),
    (0x777B30, "g_joystick_input", "IDirectInput8A *g_joystick_input;"),
    (
        0x777B34,
        "g_joystick_devices",
        "IDirectInputDevice8A *g_joystick_devices[4];",
    ),
]

TRUSTED_DATA_ITEMS = [
    (0x4972F0, 4),
    (0x50339C, 4),
    (0x5108B8, 4),
    (0x53C7F5, 1),
    (0x508890, 8),
    (0x508898, 8),
    (0x5088A0, 8),
    (0x5088A8, 8),
    (0x777D58, 8),
    (0x777D60, 8),
    (0x777D68, 4),
    (0x777D6C, 4),
    (0x777D70, 1),
    (0x777D74, 8),
    (0x777D7C, 8),
    (0x777D88, 16),
    (0x777D98, 4),
    (0x777D9C, 4),
    (0x777B2C, 4),
    (0x777B30, 4),
    (0x777B34, 16),
]

STALE_DATA_ITEM_SPECS = [
    (0x50339C, 20, "g_text_input_repeat_step", "float[5]"),
    (0x53C7F5, 3, "g_text_input_last_repeat_code", "char[3]"),
]

INPUT_CONTROLLER_INTERIOR_NAMES = (
    (0x503340, "g_input_slot0_axis_y"),
    (0x503344, "g_input_slot0_buttons"),
    (0x503348, "g_input_slot0_pointer_x"),
    (0x50334C, "g_input_slot0_pointer_y"),
    (0x503350, "g_input_slot0_authored_x"),
    (0x503354, "g_input_slot0_authored_y"),
    (0x503358, "g_input_slot0_pointer_value"),
    (0x503378, "unk_503378"),
    (0x50337C, "unk_50337c"),
    (0x503380, "unk_503380"),
    (0x503384, "unk_503384"),
    (0x503388, "unk_503388"),
    (0x50338C, "unk_50338c"),
    (0x503390, "unk_503390"),
)

INPUT_CONTROLLER_DIRTY_FUNCTIONS = (
    0x430E40,
    0x431FD0,
    0x431FF0,
    0x4320F0,
    0x4321C0,
    0x4323A0,
)

TRUSTED_STRUCT_LVARS = (
    (
        "configure_input_controller_axis_range_callback",
        20,
        "range",
        "DIPROPRANGE",
    ),
    ("update_joystick_input", 60, "state", "DIJOYSTATE2"),
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
    normalized = re.sub(r"\buint8_t\b|\bunsigned __int8\b", "unsigned char", normalized)
    normalized = re.sub(r"\s+", " ", normalized)
    normalized = re.sub(r"\s*\(\s*", "(", normalized)
    normalized = re.sub(r"\s*\)\s*", ")", normalized)
    normalized = re.sub(r"\s*,\s*", ", ", normalized)
    normalized = re.sub(r"\s*\*\s*", " *", normalized)
    normalized = re.sub(r"\(\s*", "(", normalized)
    normalized = re.sub(r"\s*\)", ")", normalized)
    normalized = re.sub(r"\s*\[\s*", "[", normalized)
    normalized = re.sub(r"\s*\]", "]", normalized)
    return normalized.strip()


def _declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\s*(?=\()", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


def _data_declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\b", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


def _clear_stale_data_item(
    address: int,
    expected_size: int,
    expected_name: str,
    expected_type: str,
) -> dict[str, object]:
    item_head = ida_bytes.get_item_head(address)
    item_size = ida_bytes.get_item_size(item_head)
    observed_name = idc.get_name(item_head)
    observed_type = _normalize_type_text(idc.get_type(item_head))
    if item_head != address or item_size != expected_size:
        return {
            "status": "unchanged",
            "address": hex(address),
            "item_head": hex(item_head),
            "item_size": item_size,
        }

    normalized_expected_type = _normalize_type_text(expected_type)
    if observed_name != expected_name or observed_type != normalized_expected_type:
        return {
            "status": "failed",
            "reason": "unexpected_stale_data_item",
            "address": hex(address),
            "expected_name": expected_name,
            "expected_type": normalized_expected_type,
            "observed_name": observed_name,
            "observed_type": observed_type,
            "item_size": item_size,
        }

    if not ida_bytes.del_items(address, ida_bytes.DELIT_SIMPLE, expected_size):
        return {
            "status": "failed",
            "reason": "delete_stale_data_item_failed",
            "address": hex(address),
        }
    return {
        "status": "applied",
        "address": hex(address),
        "removed_name": observed_name,
        "removed_type": observed_type,
        "removed_size": item_size,
    }


def _ensure_data_item(address: int, size: int) -> dict[str, object]:
    item_head = ida_bytes.get_item_head(address)
    item_size = ida_bytes.get_item_size(item_head)
    if item_head == address and item_size == size:
        return {
            "status": "unchanged",
            "address": hex(address),
            "item_size": item_size,
        }

    if item_head != address or item_size != 1:
        return {
            "status": "failed",
            "reason": "unexpected_data_item",
            "address": hex(address),
            "expected_size": size,
            "observed_head": hex(item_head),
            "observed_size": item_size,
        }

    if size == 1:
        created = ida_bytes.create_byte(address, size, True)
    else:
        created = ida_bytes.create_dword(address, size, True)
    if not created:
        return {
            "status": "failed",
            "reason": "create_data_item_failed",
            "address": hex(address),
            "expected_size": size,
        }

    verified_head = ida_bytes.get_item_head(address)
    verified_size = ida_bytes.get_item_size(verified_head)
    if verified_head != address or verified_size != size:
        return {
            "status": "failed",
            "reason": "data_item_readback_failed",
            "address": hex(address),
            "expected_size": size,
            "observed_head": hex(verified_head),
            "observed_size": verified_size,
        }
    return {
        "status": "applied",
        "address": hex(address),
        "item_size": verified_size,
    }


def _clear_input_controller_interior_name(
    address: int, expected_name: str
) -> dict[str, object]:
    observed_name = idc.get_name(address)
    if not observed_name:
        return {
            "status": "unchanged",
            "address": hex(address),
        }

    if observed_name.lower() != expected_name.lower():
        return {
            "status": "failed",
            "reason": "unexpected_input_controller_interior_name",
            "address": hex(address),
            "expected_name": expected_name,
            "observed_name": observed_name,
        }

    if not idc.set_name(address, "", ida_name.SN_NOWARN | ida_name.SN_FORCE):
        return {
            "status": "failed",
            "reason": "input_controller_interior_name_delete_failed",
            "address": hex(address),
            "observed_name": observed_name,
        }
    if idc.get_name(address):
        return {
            "status": "failed",
            "reason": "input_controller_interior_name_readback_failed",
            "address": hex(address),
            "observed_name": idc.get_name(address),
        }
    return {
        "status": "applied",
        "address": hex(address),
        "removed_name": observed_name,
    }


def _sync_struct_lvar(
    selector: str,
    stack_offset: int,
    expected_name: str,
    type_name: str,
) -> dict[str, object]:
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR:
        return {"status": "failed", "selector": selector, "reason": "missing_function"}

    cfunc = ida_hexrays.decompile(address)
    stack_locals = [lvar for lvar in cfunc.get_lvars() if lvar.is_stk_var()]
    candidates = [
        lvar for lvar in stack_locals if lvar.get_stkoff() == stack_offset
    ]
    if len(candidates) != 1:
        return {
            "status": "failed",
            "selector": selector,
            "reason": "unexpected_local_candidates",
            "stack_offset": stack_offset,
            "candidate_count": len(candidates),
            "available": [
                {
                    "name": lvar.name,
                    "stack_offset": lvar.get_stkoff(),
                    "width": lvar.width,
                    "type": str(lvar.type()),
                }
                for lvar in stack_locals
            ],
        }

    lvar = candidates[0]
    if lvar.name == expected_name and type_name in str(lvar.type()):
        return {
            "status": "unchanged",
            "selector": selector,
            "name": lvar.name,
            "type": str(lvar.type()),
        }

    local_type = ida_typeinf.tinfo_t()
    if not local_type.get_named_type(None, type_name, ida_typeinf.BTF_STRUCT):
        return {
            "status": "failed",
            "selector": selector,
            "reason": "missing_local_type",
            "type": type_name,
        }

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
            "selector": selector,
            "reason": "modify_user_lvar_info_failed",
        }

    ida_hexrays.mark_cfunc_dirty(address, True)
    verified_cfunc = ida_hexrays.decompile(address)
    verified = [
        candidate
        for candidate in verified_cfunc.get_lvars()
        if candidate.is_stk_var()
        and candidate.get_stkoff() == stack_offset
        and candidate.name == expected_name
        and type_name in str(candidate.type())
    ]
    if len(verified) != 1:
        return {
            "status": "failed",
            "selector": selector,
            "reason": "local_readback_failed",
            "stack_offset": stack_offset,
            "candidate_count": len(verified),
        }

    return {
        "status": "applied",
        "selector": selector,
        "before_name": lvar.name,
        "before_type": str(lvar.type()),
        "name": verified[0].name,
        "type": str(verified[0].type()),
    }


def _sync_types(header_path: pathlib.Path) -> int:
    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE)

    if parse_errors:
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "header": str(header_path),
                    "parse_errors": parse_errors,
                    "phase": "header_parse",
                },
                indent=2,
            )
        )
        return 1

    applied = 0
    unchanged = 0
    renamed = 0
    names_unchanged = 0
    data_items_applied = 0
    data_items_unchanged = 0
    missing = []
    failed = []

    cleared_data_items = [
        _clear_stale_data_item(address, size, name, data_type)
        for address, size, name, data_type in STALE_DATA_ITEM_SPECS
    ]
    failed.extend(
        {"stale_data_item": result}
        for result in cleared_data_items
        if result.get("status") == "failed"
    )

    data_items = [
        _ensure_data_item(address, size) for address, size in TRUSTED_DATA_ITEMS
    ]
    data_items_applied = sum(
        result.get("status") == "applied" for result in data_items
    )
    data_items_unchanged = sum(
        result.get("status") == "unchanged" for result in data_items
    )
    failed.extend(
        {"data_item": result}
        for result in data_items
        if result.get("status") == "failed"
    )
    if failed:
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "header": str(header_path),
                    "parse_errors": parse_errors,
                    "phase": "data_item_guard",
                    "cleared_data_items": cleared_data_items,
                    "data_items": data_items,
                    "failed": failed,
                },
                indent=2,
            )
        )
        return 1

    for address, name in TRUSTED_NAMES:
        if idc.get_name(address) == name:
            names_unchanged += 1
            continue
        if not idc.set_name(address, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
            failed.append({"address": hex(address), "selector": name, "reason": "rename_failed"})
            continue
        renamed += 1

    for selector, declaration in TRUSTED_DECLARATIONS:
        address, _name = _resolve_function(selector)
        if address is None:
            missing.append({"selector": selector, "reason": "missing_symbol"})
            continue

        if ida_funcs.get_func(address) is None:
            missing.append(
                {"selector": selector, "address": hex(address), "reason": "missing_function"}
            )
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

    struct_lvars = [
        _sync_struct_lvar(selector, stack_offset, expected_name, type_name)
        for selector, stack_offset, expected_name, type_name in TRUSTED_STRUCT_LVARS
    ]
    failed_struct_lvars = [
        result for result in struct_lvars if result.get("status") == "failed"
    ]
    failed.extend(
        {"selector": result.get("selector"), "struct_lvar": result}
        for result in failed_struct_lvars
    )

    input_controller_interior_names = [
        _clear_input_controller_interior_name(address, expected_name)
        for address, expected_name in INPUT_CONTROLLER_INTERIOR_NAMES
    ]
    failed.extend(
        {"input_controller_interior_name": result}
        for result in input_controller_interior_names
        if result.get("status") == "failed"
    )

    for address in INPUT_CONTROLLER_DIRTY_FUNCTIONS:
        if ida_funcs.get_func(address) is not None:
            ida_hexrays.mark_cfunc_dirty(address, True)

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
                "data_items_applied": data_items_applied,
                "data_items_unchanged": data_items_unchanged,
                "cleared_data_items": cleared_data_items,
                "data_items": data_items,
                "struct_lvars": struct_lvars,
                "input_controller_interior_names": input_controller_interior_names,
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
        print("usage: apply_input_state_types.py <header-path>", file=sys.stderr)
        ida_pro.qexit(2)
        return

    header_path = pathlib.Path(argv[1]).resolve()
    ida_pro.qexit(_sync_types(header_path))


if __name__ == "__main__":
    main()
