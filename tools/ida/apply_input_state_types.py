import json
import pathlib
import re
import sys

import ida_bytes
import ida_funcs
import ida_name
import ida_pro
import idc


TRUSTED_NAMES = [
    (0x4972F0, "g_game_input_callback_table"),
    (0x44BBB0, "initialize_mouse_authored_scale_from_clip_rect"),
    (0x44BBD0, "update_mouse_authored_scale"),
    (0x44BC20, "resolve_uncaptured_cursor_sensitivity_scale"),
    (0x44BC50, "update_mouse"),
    (0x44C050, "set_hide_system_cursor_flag"),
    (0x44C060, "click_mouse_screen"),
    (0x44C100, "convert_mouse_screen_xy"),
    (0x44C2C0, "release_mouse_input"),
    (0x44C310, "initialize_mouse_input"),
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
        "initialize_input",
        "int __thiscall initialize_input(InputState *state);",
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
        "float *__cdecl copy_active_input_controller_state(int controller_slot, int *out_buttons, float *out_axis_x, float *out_axis_y, float *out_authored_x, float *out_authored_y, float *out_pointer_value, float *out_pointer_x, float *out_pointer_y);",
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
]

TRUSTED_DATA_DECLARATIONS = [
    (0x4972F0, "g_game_input_callback_table", "void *g_game_input_callback_table;"),
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
]

TRUSTED_DATA_ITEMS = [
    (0x4972F0, 4),
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
    normalized = re.sub(r"\s*\[\s*", "[", normalized)
    normalized = re.sub(r"\s*\]", "]", normalized)
    return normalized.strip()


def _declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\s*(?=\()", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


def _data_declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\b", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


def _ensure_data_item(address: int, size: int) -> str:
    flags = ida_bytes.get_flags(address)
    if ida_bytes.is_head(flags) and ida_bytes.get_item_size(address) == size:
        return "already_current"

    if size == 1:
        created = ida_bytes.create_byte(address, size, True)
    else:
        created = ida_bytes.create_dword(address, size, True)
    if not created:
        return "create_failed"

    flags = ida_bytes.get_flags(address)
    if not ida_bytes.is_head(flags) or ida_bytes.get_item_size(address) != size:
        return "verification_failed"
    return "verified"


def _sync_types(header_path: pathlib.Path) -> int:
    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE)

    applied = 0
    unchanged = 0
    renamed = 0
    names_unchanged = 0
    data_items_applied = 0
    data_items_unchanged = 0
    missing = []
    failed = []

    for address, size in TRUSTED_DATA_ITEMS:
        status = _ensure_data_item(address, size)
        if status == "already_current":
            data_items_unchanged += 1
        elif status == "verified":
            data_items_applied += 1
        else:
            failed.append(
                {
                    "address": hex(address),
                    "size": size,
                    "reason": f"data_item_{status}",
                }
            )

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
