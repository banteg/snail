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
import idc


TRUSTED_NAMES = (
    (0x449C10, "initialize_global_font3d_bods_thunk"),
    (0x449C20, "initialize_global_font3d_bods"),
    (0x449C40, "initialize_global_font_queue_colors_thunk"),
    (0x449C50, "initialize_global_font_queue_colors"),
    (0x449E90, "measure_font_text_width"),
    (0x449F50, "register_font_texture_sheet"),
    (0x44A360, "draw_font_text_instance"),
    (0x44AE10, "initialize_font3d_objects"),
    (0x753CE8, "g_font_text_buffer"),
    (0x7544E8, "g_font_queue"),
    (0x7754E8, "g_font3d_bods"),
    (0x7770E8, "g_font3d_scales"),
    (0x7772E8, "g_font_wave_phase_a"),
    (0x7772EC, "g_font_wave_phase_b"),
    (0x7772F0, "g_font_text_cursor"),
    (0x7772F4, "g_font_wave_step_b"),
    (0x7772F8, "g_font_sheets"),
    (0x777B20, "g_registered_font_count"),
    (0x777B24, "g_font_queue_count"),
    (0x777B28, "g_font_wave_step_a"),
)

TRUSTED_FUNCTION_DECLARATIONS = (
    (
        "initialize_global_font3d_bods_thunk",
        "void __cdecl initialize_global_font3d_bods_thunk();",
    ),
    (
        "initialize_global_font3d_bods",
        "void __cdecl initialize_global_font3d_bods();",
    ),
    (
        "initialize_global_font_queue_colors_thunk",
        "void __cdecl initialize_global_font_queue_colors_thunk();",
    ),
    (
        "initialize_global_font_queue_colors",
        "void __cdecl initialize_global_font_queue_colors();",
    ),
    (
        "measure_font_text_width",
        "float __cdecl measure_font_text_width(char *text, int32_t font_id, float scale);",
    ),
    (
        "register_font_texture_sheet",
        "int32_t __cdecl register_font_texture_sheet(char *texture_path, int32_t font_kind, float width_scale, float height_scale);",
    ),
    (
        "draw_font_text_instance",
        "void __cdecl draw_font_text_instance(cFontPrintBuffer *entry);",
    ),
    (
        "initialize_font3d_objects",
        "void __cdecl initialize_font3d_objects(int16_t font_id);",
    ),
)

TRUSTED_DATA_DECLARATIONS = (
    (0x753CE8, "g_font_text_buffer", "char g_font_text_buffer[0x800];"),
    (0x7544E8, "g_font_queue", "cFontPrintBuffer g_font_queue[0x400];"),
    (0x7754E8, "g_font3d_bods", "BodBase g_font3d_bods[0x80];"),
    (0x7770E8, "g_font3d_scales", "float g_font3d_scales[0x80];"),
    (0x7772E8, "g_font_wave_phase_a", "float g_font_wave_phase_a;"),
    (0x7772EC, "g_font_wave_phase_b", "float g_font_wave_phase_b;"),
    (0x7772F0, "g_font_text_cursor", "char *g_font_text_cursor;"),
    (0x7772F4, "g_font_wave_step_b", "float g_font_wave_step_b;"),
    (0x7772F8, "g_font_sheets", "FontSheet g_font_sheets[1];"),
    (0x777B20, "g_registered_font_count", "int32_t g_registered_font_count;"),
    (0x777B24, "g_font_queue_count", "int32_t g_font_queue_count;"),
    (0x777B28, "g_font_wave_step_a", "float g_font_wave_step_a;"),
)

DIRTY_FUNCTIONS = (
    0x449E90,
    0x449F50,
    0x44A360,
    0x44AE10,
)


def _normalize_type_text(value: str | None) -> str | None:
    if value is None:
        return None
    normalized = value.strip().removesuffix(";")
    normalized = re.sub(r"\s+", " ", normalized)
    normalized = normalized.replace("signed __int16", "short")
    normalized = normalized.replace("__int16", "short")
    normalized = re.sub(r"\s*\(\s*", "(", normalized)
    normalized = re.sub(r"\s*\)\s*", ")", normalized)
    normalized = re.sub(r"\s*,\s*", ", ", normalized)
    normalized = re.sub(r"\s*\*\s*", " *", normalized)
    normalized = re.sub(r"\(\s*", "(", normalized)
    normalized = re.sub(r"\s*\)", ")", normalized)
    normalized = re.sub(r"\s+\[", "[", normalized)
    normalized = re.sub(
        r"\[(0x[0-9a-fA-F]+|\d+)\]",
        lambda match: f"[{int(match.group(1), 0)}]",
        normalized,
    )
    return normalized.strip()


def _declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\s*(?=\()", "", declaration, count=1)
    if unnamed == declaration:
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
        if idc.get_name(address) == name:
            names_unchanged += 1
            continue
        if not idc.set_name(address, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
            failed.append(
                {"address": hex(address), "selector": name, "reason": "rename_failed"}
            )
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

    for address in DIRTY_FUNCTIONS:
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
                "missing": missing,
                "failed": failed,
            },
            indent=2,
        )
    )
    return 1 if parse_errors or failed or missing else 0


def main() -> None:
    argv = list(idc.ARGV)
    if len(argv) != 2:
        print("usage: apply_font_system_types.py <header-path>", file=sys.stderr)
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
