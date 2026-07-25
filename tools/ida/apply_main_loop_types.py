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
    (
        "read_current_display_resolution",
        "int *__cdecl read_current_display_resolution("
        "int *out_width, int *out_height);",
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

CURRENT_FRAME_UPDATE_ADDRESS = 0x4B763C
STALE_CURRENT_FRAME_UPDATE_SIZE = 0xC
CURRENT_FRAME_UPDATE_SPLIT_ITEMS = (
    (
        CURRENT_FRAME_UPDATE_ADDRESS,
        0x4,
        "g_current_frame_update_steps",
        "float g_current_frame_update_steps;",
        "float",
        "float",
    ),
    (
        0x4B7640,
        0x2,
        "g_right_mouse_button_state",
        "uint8_t g_right_mouse_button_state[2];",
        "uint8_t[2]",
        "byte",
    ),
    (
        0x4B7644,
        0x4,
        "g_estimated_texture_vram_bytes",
        "int g_estimated_texture_vram_bytes;",
        "int",
        "dword",
    ),
)

WIDENED_SCALAR_DATA_ITEMS = (
    (0x4B775C, 0x4, "g_current_display_height", ("uint8_t",), "dword"),
    (0x4B7760, 0x4, "g_authored_view_height", (None,), "float"),
    (0x4DF858, 0x4, "g_current_display_width", ("uint8_t",), "dword"),
    (0x4DF85C, 0x4, "g_authored_view_width", (None,), "float"),
)

MAIN_LOOP_SCALAR_DATA_ITEMS = (
    (
        0x4B7236,
        0x1,
        "g_render_queue_active",
        "uint8_t g_render_queue_active;",
        "uint8_t",
    ),
    (
        0x4B7638,
        0x4,
        "g_mean_update_steps_per_frame",
        "float g_mean_update_steps_per_frame;",
        "float",
    ),
    (
        0x4B7654,
        0x1,
        "g_window_deactivated",
        "uint8_t g_window_deactivated;",
        "uint8_t",
    ),
    (
        0x4B7758,
        0x1,
        "g_fixed_update_abort_requested",
        "uint8_t g_fixed_update_abort_requested;",
        "uint8_t",
    ),
    (
        0x4B7759,
        0x1,
        "g_frame_render_requested",
        "uint8_t g_frame_render_requested;",
        "uint8_t",
    ),
    (
        0x4B775C,
        0x4,
        "g_current_display_height",
        "int g_current_display_height;",
        "int",
    ),
    (
        0x4B7760,
        0x4,
        "g_authored_view_height",
        "float g_authored_view_height;",
        "float",
    ),
    (
        0x4B7768,
        0x4,
        "g_main_loop_frame_count",
        "float g_main_loop_frame_count;",
        "float",
    ),
    (
        0x4DF858,
        0x4,
        "g_current_display_width",
        "int g_current_display_width;",
        "int",
    ),
    (
        0x4DF85C,
        0x4,
        "g_authored_view_width",
        "float g_authored_view_width;",
        "float",
    ),
    (
        0x4DF860,
        0x4,
        "g_pending_window_deactivate",
        "int g_pending_window_deactivate;",
        "int",
    ),
    (
        0x4DF864,
        0x1,
        "g_main_loop_exit_requested",
        "uint8_t g_main_loop_exit_requested;",
        "uint8_t",
    ),
    (
        0x4DF90C,
        0x1,
        "g_game_initialization_pending",
        "uint8_t g_game_initialization_pending;",
        "uint8_t",
    ),
    (
        0x4DFAFC,
        0x4,
        "g_frame_time_accumulator",
        "float g_frame_time_accumulator;",
        "float",
    ),
    (
        0x4DFB00,
        0x4,
        "g_previous_frame_timestamp_seconds",
        "float g_previous_frame_timestamp_seconds;",
        "float",
    ),
    (
        0x4DFB04,
        0x4,
        "g_current_frame_timestamp_seconds",
        "float g_current_frame_timestamp_seconds;",
        "float",
    ),
)

DEPENDENT_DECOMPILE_FUNCTIONS = (
    "initialize_audio_subsystem",
    "shutdown_bass_audio_window",
    "handle_game_window_activate",
    "handle_game_window_deactivate",
    "game_window_proc",
    "show_and_focus_game_window",
    "convert_mouse_screen_xy",
    "initialize_mouse_input",
    "initialize_direct3d_renderer_defaults",
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


def _expected_data_kind(size: int, expected_type: str) -> str:
    if expected_type == "float":
        return "float"
    if size in (1, 2):
        return "byte"
    return "dword"


def _data_kind_matches(address: int, kind: str) -> bool:
    flags = ida_bytes.get_flags(address)
    if kind == "float":
        return ida_bytes.is_float(flags)
    if kind == "byte":
        return ida_bytes.is_byte(flags)
    return ida_bytes.is_dword(flags)


def _create_data_kind(address: int, size: int, kind: str) -> bool:
    if kind == "float":
        return ida_bytes.create_float(address, size, True)
    if kind == "byte":
        return ida_bytes.create_byte(address, size, True)
    return ida_bytes.create_dword(address, size, True)


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


def _sync_current_frame_update_boundary() -> dict[str, object]:
    expected_boundaries = tuple(
        (address, size)
        for address, size, _name, _declaration, _expected_type, _kind
        in CURRENT_FRAME_UPDATE_SPLIT_ITEMS
    )
    already_split = all(
        ida_bytes.get_item_head(address) == address
        and ida_bytes.get_item_size(address) == size
        for address, size in expected_boundaries
    )
    if already_split:
        return {
            "status": "unchanged",
            "boundaries": [
                {"address": hex(address), "size": size}
                for address, size in expected_boundaries
            ],
        }

    stale_head = ida_bytes.get_item_head(CURRENT_FRAME_UPDATE_ADDRESS)
    stale_size = ida_bytes.get_item_size(stale_head)
    stale_name = idc.get_name(stale_head)
    stale_type = _normalize_type_text(idc.get_type(stale_head))
    stale_extent = all(
        ida_bytes.get_item_head(address) == CURRENT_FRAME_UPDATE_ADDRESS
        for address in range(
            CURRENT_FRAME_UPDATE_ADDRESS,
            CURRENT_FRAME_UPDATE_ADDRESS + STALE_CURRENT_FRAME_UPDATE_SIZE,
        )
    )
    if (
        stale_head != CURRENT_FRAME_UPDATE_ADDRESS
        or stale_size != STALE_CURRENT_FRAME_UPDATE_SIZE
        or stale_name != "g_current_frame_update_steps"
        or stale_type != "float[3]"
        or not stale_extent
    ):
        return {
            "status": "failed",
            "reason": "unexpected_current_frame_update_boundary",
            "observed_head": hex(stale_head),
            "observed_size": stale_size,
            "observed_name": stale_name,
            "observed_type": stale_type,
            "stale_extent": stale_extent,
        }

    if not ida_bytes.del_items(
        CURRENT_FRAME_UPDATE_ADDRESS,
        ida_bytes.DELIT_SIMPLE,
        STALE_CURRENT_FRAME_UPDATE_SIZE,
    ):
        return {
            "status": "failed",
            "reason": "delete_stale_current_frame_update_item_failed",
        }

    for address, size, _name, _declaration, _expected_type, kind in (
        CURRENT_FRAME_UPDATE_SPLIT_ITEMS
    ):
        created = _create_data_kind(address, size, kind)
        if not created:
            return {
                "status": "failed",
                "reason": "create_current_frame_split_item_failed",
                "address": hex(address),
                "size": size,
                "kind": kind,
            }

    observed_boundaries = [
        {
            "address": hex(address),
            "head": hex(ida_bytes.get_item_head(address)),
            "size": ida_bytes.get_item_size(address),
        }
        for address, _size in expected_boundaries
    ]
    if any(
        int(entry["head"], 0) != address or entry["size"] != size
        for entry, (address, size) in zip(
            observed_boundaries,
            expected_boundaries,
            strict=True,
        )
    ):
        return {
            "status": "failed",
            "reason": "current_frame_split_verification_failed",
            "observed_boundaries": observed_boundaries,
        }

    return {
        "status": "applied",
        "removed_extent": "0x4b763c..0x4b7648",
        "boundaries": observed_boundaries,
    }


def _sync_widened_scalar_boundaries() -> dict[str, object]:
    results = []
    failed = []

    for address, size, expected_name, accepted_stale_types, target_kind in (
        WIDENED_SCALAR_DATA_ITEMS
    ):
        item_head = ida_bytes.get_item_head(address)
        item_size = ida_bytes.get_item_size(item_head)
        if item_head == address and item_size == size:
            results.append(
                {
                    "status": "unchanged",
                    "address": hex(address),
                    "size": size,
                    "kind": (
                        target_kind
                        if _data_kind_matches(address, target_kind)
                        else "stale"
                    ),
                }
            )
            continue

        observed_name = idc.get_name(item_head)
        observed_type = _normalize_type_text(idc.get_type(item_head))
        tail = []
        for tail_address in range(address + 1, address + size):
            tail_head = ida_bytes.get_item_head(tail_address)
            tail.append(
                {
                    "address": hex(tail_address),
                    "head": hex(tail_head),
                    "size": ida_bytes.get_item_size(tail_head),
                    "name": idc.get_name(tail_address),
                    "type": _normalize_type_text(idc.get_type(tail_address)),
                    "unknown": ida_bytes.is_unknown(
                        ida_bytes.get_flags(tail_address)
                    ),
                }
            )
        tail_is_unowned = all(
            int(entry["head"], 0) == int(entry["address"], 0)
            and entry["size"] == 1
            and entry["name"] == ""
            and entry["type"] is None
            and entry["unknown"] is True
            for entry in tail
        )
        if (
            item_head != address
            or item_size != 1
            or observed_name != expected_name
            or observed_type not in accepted_stale_types
            or not tail_is_unowned
        ):
            failure = {
                "status": "failed",
                "reason": "unexpected_widened_scalar_boundary",
                "address": hex(address),
                "expected_size": size,
                "observed_head": hex(item_head),
                "observed_size": item_size,
                "expected_name": expected_name,
                "observed_name": observed_name,
                "accepted_stale_types": accepted_stale_types,
                "observed_type": observed_type,
                "tail": tail,
            }
            results.append(failure)
            failed.append(failure)
            continue

        if not _create_data_kind(address, size, target_kind):
            failure = {
                "status": "failed",
                "reason": "create_widened_scalar_failed",
                "address": hex(address),
                "expected_size": size,
                "target_kind": target_kind,
            }
            results.append(failure)
            failed.append(failure)
            continue

        observed_head = ida_bytes.get_item_head(address)
        observed_size = ida_bytes.get_item_size(observed_head)
        if (
            observed_head != address
            or observed_size != size
            or not _data_kind_matches(address, target_kind)
        ):
            failure = {
                "status": "failed",
                "reason": "widened_scalar_verification_failed",
                "address": hex(address),
                "expected_size": size,
                "expected_kind": target_kind,
                "observed_head": hex(observed_head),
                "observed_size": observed_size,
            }
            results.append(failure)
            failed.append(failure)
            continue
        results.append(
            {
                "status": "applied",
                "address": hex(address),
                "size": observed_size,
                "kind": target_kind,
            }
        )

    return {
        "status": (
            "failed"
            if failed
            else "applied"
            if any(entry["status"] == "applied" for entry in results)
            else "unchanged"
        ),
        "results": results,
    }


def _sync_main_loop_scalar_data_items() -> dict[str, object]:
    changed = False
    results = []
    failed = []
    trusted_items = (
        *CURRENT_FRAME_UPDATE_SPLIT_ITEMS,
        *(
            (
                *item,
                _expected_data_kind(item[1], item[4]),
            )
            for item in MAIN_LOOP_SCALAR_DATA_ITEMS
        ),
    )

    for address, size, name, declaration, expected_type, expected_kind in (
        trusted_items
    ):
        observed_head = ida_bytes.get_item_head(address)
        observed_size = ida_bytes.get_item_size(observed_head)
        if observed_head != address or observed_size != size:
            failure = {
                "status": "failed",
                "reason": "unexpected_main_loop_scalar_boundary",
                "address": hex(address),
                "expected_size": size,
                "observed_head": hex(observed_head),
                "observed_size": observed_size,
            }
            results.append(failure)
            failed.append(failure)
            continue

        item_changed = False
        if not _data_kind_matches(address, expected_kind):
            if not _create_data_kind(address, size, expected_kind):
                failure = {
                    "status": "failed",
                    "reason": "set_main_loop_scalar_data_kind_failed",
                    "address": hex(address),
                    "size": size,
                    "expected_kind": expected_kind,
                }
                results.append(failure)
                failed.append(failure)
                continue
            item_changed = True
        if idc.get_name(address) != name:
            if not idc.set_name(
                address,
                name,
                ida_name.SN_NOWARN | ida_name.SN_FORCE,
            ):
                failure = {
                    "status": "failed",
                    "reason": "rename_main_loop_scalar_failed",
                    "address": hex(address),
                    "name": name,
                }
                results.append(failure)
                failed.append(failure)
                continue
            item_changed = True
        if _normalize_type_text(idc.get_type(address)) != expected_type:
            if not idc.SetType(address, declaration):
                failure = {
                    "status": "failed",
                    "reason": "set_main_loop_scalar_type_failed",
                    "address": hex(address),
                    "declaration": declaration,
                }
                results.append(failure)
                failed.append(failure)
                continue
            item_changed = True

        observed_head = ida_bytes.get_item_head(address)
        observed_size = ida_bytes.get_item_size(observed_head)
        observed_name = idc.get_name(address)
        observed_type = _normalize_type_text(idc.get_type(address))
        if (
            observed_head != address
            or observed_size != size
            or not _data_kind_matches(address, expected_kind)
            or observed_name != name
            or observed_type != expected_type
        ):
            failure = {
                "status": "failed",
                "reason": "main_loop_scalar_verification_failed",
                "address": hex(address),
                "expected_size": size,
                "expected_kind": expected_kind,
                "expected_name": name,
                "expected_type": expected_type,
                "observed_head": hex(observed_head),
                "observed_size": observed_size,
                "observed_name": observed_name,
                "observed_type": observed_type,
            }
            results.append(failure)
            failed.append(failure)
            continue

        changed = changed or item_changed
        results.append(
            {
                "status": "applied" if item_changed else "unchanged",
                "address": hex(address),
                "size": observed_size,
                "kind": expected_kind,
                "name": observed_name,
                "type": observed_type,
            }
        )

    return {
        "status": "failed" if failed else "applied" if changed else "unchanged",
        "results": results,
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
    current_frame_boundary = _sync_current_frame_update_boundary()
    if current_frame_boundary.get("status") == "failed":
        failed.append({"current_frame_boundary": current_frame_boundary})
    widened_scalar_boundaries = _sync_widened_scalar_boundaries()
    if widened_scalar_boundaries.get("status") == "failed":
        failed.append(
            {"widened_scalar_boundaries": widened_scalar_boundaries}
        )
    scalar_data_items = _sync_main_loop_scalar_data_items()
    if scalar_data_items.get("status") == "failed":
        failed.append({"scalar_data_items": scalar_data_items})

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
                "current_frame_boundary": current_frame_boundary,
                "widened_scalar_boundaries": widened_scalar_boundaries,
                "scalar_data_items": scalar_data_items,
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
