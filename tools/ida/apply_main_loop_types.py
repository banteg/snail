import json
import pathlib
import re
import sys

import ida_bytes
import ida_funcs
import ida_hexrays
import ida_name
import ida_pro
import idc


TRUSTED_DECLARATIONS = (
    (
        "game_startup_and_main_loop",
        "int __stdcall game_startup_and_main_loop("
        "void *hInstance, void *hPrevInstance, "
        "char *lpCmdLine, int nShowCmd);",
    ),
)

MOUSE_WHEEL_DELTA_ADDRESS = 0x4DFAD0
APPLICATION_INSTANCE_ADDRESS = 0x4DFAD8
STALE_COMBINED_SIZE = 0xC
TRUSTED_DATA_ITEMS = (
    (
        MOUSE_WHEEL_DELTA_ADDRESS,
        0x8,
        "g_mouse_wheel_delta",
        "int g_mouse_wheel_delta[2];",
        "int[2]",
    ),
    (
        APPLICATION_INSTANCE_ADDRESS,
        0x4,
        "g_application_instance",
        "void *g_application_instance;",
        "void *",
    ),
)
DEPENDENT_DECOMPILE_FUNCTIONS = (
    "initialize_audio_subsystem",
    "shutdown_bass_audio_window",
)


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
    unnamed = re.sub(
        rf"\b{re.escape(selector)}\s*(?=\()",
        "",
        declaration,
        count=1,
    )
    return _normalize_type_text(unnamed) or ""


def _sync_application_instance_boundary() -> dict[str, object]:
    mouse_head = ida_bytes.get_item_head(MOUSE_WHEEL_DELTA_ADDRESS)
    mouse_size = ida_bytes.get_item_size(mouse_head)
    instance_head = ida_bytes.get_item_head(APPLICATION_INSTANCE_ADDRESS)
    instance_size = ida_bytes.get_item_size(instance_head)
    stale_type = _normalize_type_text(idc.get_type(mouse_head))
    stale_name = idc.get_name(mouse_head)

    already_split = (
        mouse_head == MOUSE_WHEEL_DELTA_ADDRESS
        and mouse_size == 0x8
        and instance_head == APPLICATION_INSTANCE_ADDRESS
        and instance_size == 0x4
    )
    stale_combined_item = (
        mouse_head == MOUSE_WHEEL_DELTA_ADDRESS
        and mouse_size == STALE_COMBINED_SIZE
        and instance_head == MOUSE_WHEEL_DELTA_ADDRESS
        and instance_size == STALE_COMBINED_SIZE
        and stale_name == "g_mouse_wheel_delta"
        and stale_type == "int[3]"
    )
    if not already_split and not stale_combined_item:
        return {
            "status": "failed",
            "reason": "unexpected_application_instance_boundary",
            "mouse_head": hex(mouse_head),
            "mouse_size": mouse_size,
            "instance_head": hex(instance_head),
            "instance_size": instance_size,
            "observed_name": stale_name,
            "observed_type": stale_type,
        }

    changed = False
    if stale_combined_item:
        if not ida_bytes.del_items(
            MOUSE_WHEEL_DELTA_ADDRESS,
            ida_bytes.DELIT_SIMPLE,
            STALE_COMBINED_SIZE,
        ):
            return {"status": "failed", "reason": "delete_combined_item_failed"}
        for address, size, _name, _declaration, _expected_type in TRUSTED_DATA_ITEMS:
            if not ida_bytes.create_dword(address, size, True):
                return {
                    "status": "failed",
                    "reason": "create_split_item_failed",
                    "address": hex(address),
                    "size": size,
                }
        changed = True

    for address, size, name, declaration, expected_type in TRUSTED_DATA_ITEMS:
        if idc.get_name(address) != name:
            if not idc.set_name(address, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                return {
                    "status": "failed",
                    "reason": "rename_data_item_failed",
                    "address": hex(address),
                    "name": name,
                }
            changed = True
        if _normalize_type_text(idc.get_type(address)) != expected_type:
            if not idc.SetType(address, declaration):
                return {
                    "status": "failed",
                    "reason": "set_data_type_failed",
                    "address": hex(address),
                    "declaration": declaration,
                }
            changed = True

        observed_head = ida_bytes.get_item_head(address)
        observed_size = ida_bytes.get_item_size(observed_head)
        observed_type = _normalize_type_text(idc.get_type(address))
        if (
            observed_head != address
            or observed_size != size
            or idc.get_name(address) != name
            or observed_type != expected_type
        ):
            return {
                "status": "failed",
                "reason": "data_boundary_verification_failed",
                "address": hex(address),
                "expected_size": size,
                "observed_head": hex(observed_head),
                "observed_size": observed_size,
                "observed_name": idc.get_name(address),
                "observed_type": observed_type,
            }

    return {
        "status": "applied" if changed else "unchanged",
        "mouse_wheel_extent": "0x4dfad0..0x4dfad8",
        "application_instance": hex(APPLICATION_INSTANCE_ADDRESS),
    }


def _sync_types(header_path: pathlib.Path) -> int:
    # The legacy IDA type library in this database resolves HINSTANCE as a
    # 16-bit handle. The trusted IDA declaration therefore spells the proven
    # 32-bit WinMain slots as void*/char* while the shared header and Binary
    # Ninja replay retain the authored Win32 aliases.
    parse_errors = 0
    applied = 0
    unchanged = 0
    invalidated = []
    missing = []
    failed = []

    data_boundary = _sync_application_instance_boundary()
    if data_boundary.get("status") == "failed":
        failed.append({"data_boundary": data_boundary})

    for selector, declaration in TRUSTED_DECLARATIONS:
        address = idc.get_name_ea_simple(selector)
        if address == idc.BADADDR or ida_funcs.get_func(address) is None:
            missing.append({"selector": selector, "reason": "missing_function"})
            continue

        expected = _declaration_to_observed_type(selector, declaration)
        current = _normalize_type_text(idc.get_type(address))
        if current == expected:
            unchanged += 1
        elif not idc.SetType(address, declaration):
            failed.append({"selector": selector, "reason": "set_type_failed"})
            continue
        else:
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

        ida_hexrays.mark_cfunc_dirty(address, True)
        invalidated.append({"selector": selector, "address": hex(address)})

    for selector in DEPENDENT_DECOMPILE_FUNCTIONS:
        address = idc.get_name_ea_simple(selector)
        if address == idc.BADADDR or ida_funcs.get_func(address) is None:
            missing.append({"selector": selector, "reason": "missing_dependent_function"})
            continue
        ida_hexrays.mark_cfunc_dirty(address, True)
        invalidated.append({"selector": selector, "address": hex(address)})

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "parse_errors": parse_errors,
                "data_boundary": data_boundary,
                "applied": applied,
                "unchanged": unchanged,
                "invalidated": invalidated,
                "missing": missing,
                "failed": failed,
            },
            indent=2,
        )
    )
    return 1 if parse_errors or missing or failed else 0


def main() -> None:
    argv = list(idc.ARGV)
    if len(argv) < 2:
        print("usage: apply_main_loop_types.py <header-path>", file=sys.stderr)
        ida_pro.qexit(2)
        return

    header_path = pathlib.Path(argv[1]).resolve()
    ida_pro.qexit(_sync_types(header_path))


if __name__ == "__main__":
    main()
