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


TRUSTED_DECLARATIONS = [
    (
        "malloc",
        "void* __cdecl malloc(unsigned int size);",
    ),
    (
        "findfirst",
        "int __cdecl findfirst(char* pattern, FileSearchData* find_data);",
    ),
    (
        "findnext",
        "int __cdecl findnext(int handle, FileSearchData* find_data);",
    ),
    (
        "fopen",
        "File* __cdecl fopen(char* path, char* mode);",
    ),
    (
        "fwrite",
        "unsigned int __cdecl fwrite(void* bytes, unsigned int element_size, unsigned int element_count, File* stream);",
    ),
    (
        "fclose",
        "int __cdecl fclose(File* stream);",
    ),
    (
        "getcwd",
        "char* __cdecl getcwd(char* buffer, int max_length);",
    ),
    (
        "chdir",
        "int __cdecl chdir(char* path);",
    ),
    (
        "set_current_directory_with_drive_fallback",
        "int __cdecl set_current_directory_with_drive_fallback(char* path);",
    ),
    (
        "get_stream_length_preserve_position",
        "int __cdecl get_stream_length_preserve_position(File* file);",
    ),
    (
        "get_tracked_allocation_size",
        "int __thiscall get_tracked_allocation_size(TrackedAllocationStack* stack, void* pointer);",
    ),
    (
        "push_tracked_allocation",
        "void __thiscall push_tracked_allocation(TrackedAllocationStack* stack, char* label, void* pointer, int guarded_size);",
    ),
    (
        "pop_tracked_allocation",
        "int __thiscall pop_tracked_allocation(TrackedAllocationStack* stack, void* pointer);",
    ),
    (
        "initialize_game_data_archive",
        "unsigned char __cdecl initialize_game_data_archive(void);",
    ),
    (
        "uninitialize_game_data_archive",
        "int __cdecl uninitialize_game_data_archive(void);",
    ),
    (
        "archive_or_file_exists",
        "unsigned char __cdecl archive_or_file_exists(char* path, unsigned char force_filesystem);",
    ),
    (
        "find_archive_entry",
        "ArchiveEntry* __cdecl find_archive_entry(char* path);",
    ),
    (
        "load_file_bytes_fixed_size_from_archive_or_fs",
        "void* __cdecl load_file_bytes_fixed_size_from_archive_or_fs(char* path, void* buffer, int byte_count);",
    ),
    (
        "load_file_bytes_from_archive_or_fs",
        "void* __cdecl load_file_bytes_from_archive_or_fs(char* path, void* buffer, int* out_size);",
    ),
    (
        "load_file_bytes",
        "void* __cdecl load_file_bytes(char* path, int* out_size);",
    ),
    (
        "enumerate_matching_archive_or_fs_entries",
        "void __cdecl enumerate_matching_archive_or_fs_entries(char* directory, char* pattern, int* out_count, EnumeratedEntryName* names);",
    ),
    (
        "load_archive_index",
        "unsigned char __cdecl load_archive_index(char* path);",
    ),
    (
        "is_archive_index_loaded",
        "unsigned char __cdecl is_archive_index_loaded(void);",
    ),
    (
        "get_archive_data_base",
        "void* __cdecl get_archive_data_base(void);",
    ),
    (
        "get_archive_data_end",
        "void* __cdecl get_archive_data_end(void);",
    ),
    (
        "allocate_tracked_memory",
        "void* __cdecl allocate_tracked_memory(int size, char* name);",
    ),
    (
        "free_tracked_memory",
        "void __cdecl free_tracked_memory(void* pointer);",
    ),
    (
        "xor_decode_buffer_with_index",
        "char* __cdecl xor_decode_buffer_with_index(char* bytes, int byte_count);",
    ),
    (
        "write_file_bytes",
        "int __cdecl write_file_bytes(char* path, void* bytes, int byte_count);",
    ),
    (
        "save_config_file",
        "char* __cdecl save_config_file(char* path, void* bytes, int byte_count);",
    ),
]

TRUSTED_NAMES = [
    (0x5108B0, "g_registered_sound_sample_count"),
    (0x5108B4, "g_tracked_allocation_total_bytes"),
    (0x5108B8, "g_text_input_repeat_accumulator"),
    (0x5108C0, "g_tracked_allocation_stack"),
    (0x53C7E8, "g_music_memory_buffer"),
    (0x53C7EC, "g_archive_data_base"),
    (0x53C7F0, "g_archive_file"),
    (0x53C7F4, "g_archive_startup_flag"),
    (0x53C7F8, "g_archive_index_records"),
]

TRUSTED_DATA_DECLARATIONS = [
    (
        0x5108B0,
        "g_registered_sound_sample_count",
        "int g_registered_sound_sample_count;",
    ),
    (
        0x5108B4,
        "g_tracked_allocation_total_bytes",
        "int g_tracked_allocation_total_bytes;",
    ),
    (
        0x5108B8,
        "g_text_input_repeat_accumulator",
        "float g_text_input_repeat_accumulator;",
    ),
    (
        0x5108C0,
        "g_tracked_allocation_stack",
        "TrackedAllocationStack g_tracked_allocation_stack;",
    ),
    (0x53C7E8, "g_music_memory_buffer", "char* g_music_memory_buffer;"),
    (0x53C7EC, "g_archive_data_base", "void* g_archive_data_base;"),
    (0x53C7F0, "g_archive_file", "File* g_archive_file;"),
    (0x53C7F4, "g_archive_startup_flag", "unsigned char g_archive_startup_flag;"),
    (0x53C7F8, "g_archive_index_records", "ArchiveIndex* g_archive_index_records;"),
]

TRUSTED_SCALAR_DATA_ITEMS = [
    (0x5108B0, 4),
    (0x5108B4, 4),
    (0x5108B8, 4),
]

STALE_DATA_ITEM_SPECS = [
    (0x5108B0, 0x10, "g_registered_sound_sample_count", "int[4]"),
]

ARCHIVE_SHELL_LVAR_SPECS = [
    ("save_config_file", "cwd_buffer", "char cwd_buffer[512];", 24, None),
    ("save_config_file", "stream", "File* stream;", None, 0x42F557),
    ("write_file_bytes", "file_name", "char file_name[256];", 28, None),
    ("write_file_bytes", "cwd_buffer", "char cwd_buffer[512];", 284, None),
    (
        "write_file_bytes",
        "original_directory",
        "char original_directory[512];",
        796,
        None,
    ),
    ("write_file_bytes", "stream", "File* stream;", None, 0x4316C8),
]

STALE_STACK_LVAR_OVERRIDE_SPECS = [
    ("save_config_file", 12, {"cwd_buffer", "v5"}),
    ("write_file_bytes", 12, {"file_name", "v8"}),
]


def _resolve_function(selector: str) -> int | None:
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR:
        return None
    return address


def _normalize_type_text(value: str | None) -> str | None:
    if value is None:
        return None
    normalized = value.strip().removesuffix(";")
    normalized = re.sub(r"\buint8_t\b", "unsigned char", normalized)
    normalized = re.sub(r"\bint32_t\b", "int", normalized)
    normalized = re.sub(r"\buint32_t\b", "unsigned int", normalized)
    normalized = normalized.replace("unsigned __int8", "unsigned char")
    normalized = re.sub(r"\s+", " ", normalized)
    normalized = re.sub(r"\s*\(\s*", "(", normalized)
    normalized = re.sub(r"\s*\)\s*", ")", normalized)
    normalized = re.sub(r"\s*,\s*", ", ", normalized)
    normalized = re.sub(r"\s*\*\s*", " *", normalized)
    normalized = re.sub(r"\(\s*", "(", normalized)
    normalized = re.sub(r"\s*\)", ")", normalized)
    normalized = normalized.replace("(void)", "()")
    return normalized.strip()


def _declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\s*(?=\()", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


def _data_declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\s*(?=;)", "", declaration, count=1)
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


def _ensure_scalar_data_item(address: int, size: int) -> dict[str, object]:
    item_head = ida_bytes.get_item_head(address)
    item_size = ida_bytes.get_item_size(item_head)
    if item_head == address and item_size == size:
        return {
            "status": "unchanged",
            "address": hex(address),
            "item_size": item_size,
        }

    # A freshly undefined byte is the only shape this replay may replace.
    # Wider or overlapping items need a separately reviewed stale-item guard.
    if item_head != address or item_size != 1:
        return {
            "status": "failed",
            "reason": "unexpected_scalar_data_item",
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
            "reason": "create_scalar_data_item_failed",
            "address": hex(address),
            "expected_size": size,
            "observed_head": hex(item_head),
            "observed_size": item_size,
        }

    verified_head = ida_bytes.get_item_head(address)
    verified_size = ida_bytes.get_item_size(verified_head)
    if verified_head != address or verified_size != size:
        return {
            "status": "failed",
            "reason": "scalar_data_item_readback_failed",
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


def _sync_lvar(
    selector: str,
    expected_name: str,
    declaration: str,
    stack_offset: int | None,
    definition_address: int | None,
) -> dict[str, object]:
    address = _resolve_function(selector)
    if address is None:
        return {"status": "failed", "reason": "missing_function", "selector": selector}

    cfunc = ida_hexrays.decompile(address)
    candidates = [
        lvar
        for lvar in cfunc.get_lvars()
        if not lvar.is_arg_var
        and (
            (
                stack_offset is not None
                and lvar.is_stk_var()
                and lvar.get_stkoff() == stack_offset
            )
            or (
                definition_address is not None
                and not lvar.is_stk_var()
                and lvar.defea == definition_address
            )
        )
    ]
    if len(candidates) != 1:
        return {
            "status": "failed",
            "reason": "unexpected_local_candidates",
            "selector": selector,
            "expected_name": expected_name,
            "stack_offset": stack_offset,
            "definition_address": (
                None if definition_address is None else hex(definition_address)
            ),
            "candidate_count": len(candidates),
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
            "reason": "parse_local_type_failed",
            "selector": selector,
            "declaration": declaration,
        }

    lvar = candidates[0]
    expected_type = _normalize_type_text(str(local_type))
    observed_type = _normalize_type_text(str(lvar.type()))
    if lvar.name == expected_name and observed_type == expected_type:
        return {
            "status": "unchanged",
            "selector": selector,
            "name": lvar.name,
            "type": str(lvar.type()),
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
            "reason": "modify_user_lvar_info_failed",
            "selector": selector,
            "expected_name": expected_name,
        }

    ida_hexrays.mark_cfunc_dirty(address, True)
    verified_cfunc = ida_hexrays.decompile(address)
    verified = [
        candidate
        for candidate in verified_cfunc.get_lvars()
        if not candidate.is_arg_var
        and candidate.name == expected_name
        and _normalize_type_text(str(candidate.type())) == expected_type
        and (
            stack_offset is None
            or (
                candidate.is_stk_var()
                and candidate.get_stkoff() == stack_offset
            )
        )
    ]
    if len(verified) != 1:
        return {
            "status": "failed",
            "reason": "local_readback_failed",
            "selector": selector,
            "expected_name": expected_name,
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


def _clear_stale_stack_lvar_override(
    selector: str,
    stack_offset: int,
    stale_names: set[str],
) -> dict[str, object]:
    address = _resolve_function(selector)
    if address is None:
        return {"status": "failed", "reason": "missing_function", "selector": selector}

    cfunc = ida_hexrays.decompile(address)
    candidates = [
        lvar
        for lvar in cfunc.get_lvars()
        if not lvar.is_arg_var
        and lvar.is_stk_var()
        and lvar.get_stkoff() == stack_offset
        and lvar.name in stale_names
    ]
    if not candidates:
        return {
            "status": "unchanged",
            "selector": selector,
            "stack_offset": stack_offset,
        }
    if len(candidates) != 1:
        return {
            "status": "failed",
            "reason": "unexpected_stale_override_candidates",
            "selector": selector,
            "stack_offset": stack_offset,
            "candidate_count": len(candidates),
        }

    lvar = candidates[0]
    locator = ida_hexrays.lvar_locator_t(lvar.location, lvar.defea)
    settings = ida_hexrays.lvar_uservec_t()
    if not ida_hexrays.restore_user_lvar_settings(settings, address):
        return {
            "status": "failed",
            "reason": "restore_user_lvar_settings_failed",
            "selector": selector,
        }

    saved_info = settings.find_info(locator)
    if saved_info is None:
        return {
            "status": "failed",
            "reason": "missing_saved_lvar_override",
            "selector": selector,
            "name": lvar.name,
        }
    if not settings.lvvec._del(saved_info):
        return {
            "status": "failed",
            "reason": "delete_saved_lvar_override_failed",
            "selector": selector,
            "name": lvar.name,
        }

    ida_hexrays.save_user_lvar_settings(address, settings)
    ida_hexrays.mark_cfunc_dirty(address, True)
    verified_settings = ida_hexrays.lvar_uservec_t()
    if not ida_hexrays.restore_user_lvar_settings(verified_settings, address):
        return {
            "status": "failed",
            "reason": "restore_verified_lvar_settings_failed",
            "selector": selector,
        }
    if verified_settings.find_info(locator) is not None:
        return {
            "status": "failed",
            "reason": "stale_lvar_override_readback_failed",
            "selector": selector,
            "name": lvar.name,
        }

    return {
        "status": "applied",
        "selector": selector,
        "stack_offset": stack_offset,
        "removed_name": lvar.name,
        "removed_type": str(lvar.type()),
    }


def _sync_types(header_path: pathlib.Path) -> int:
    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE)

    applied = 0
    unchanged = 0
    renamed = 0
    names_unchanged = 0
    data_applied = 0
    data_unchanged = 0
    scalar_data_items_applied = 0
    scalar_data_items_unchanged = 0
    applied_functions = []
    function_type_changes = []
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

    scalar_data_items = [
        _ensure_scalar_data_item(address, size)
        for address, size in TRUSTED_SCALAR_DATA_ITEMS
    ]
    scalar_data_items_applied = sum(
        result.get("status") == "applied" for result in scalar_data_items
    )
    scalar_data_items_unchanged = sum(
        result.get("status") == "unchanged" for result in scalar_data_items
    )
    failed.extend(
        {"scalar_data_item": result}
        for result in scalar_data_items
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
                    "scalar_data_items": scalar_data_items,
                    "failed": failed,
                },
                indent=2,
            )
        )
        return 1

    for address, name in TRUSTED_NAMES:
        current_name = idc.get_name(address)
        if current_name == name:
            names_unchanged += 1
            continue
        if not idc.set_name(address, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
            failed.append({"address": hex(address), "name": name, "reason": "rename_failed"})
            continue
        renamed += 1

    for address, selector, declaration in TRUSTED_DATA_DECLARATIONS:
        normalized_current = _normalize_type_text(idc.get_type(address))
        normalized_expected = _data_declaration_to_observed_type(selector, declaration)
        if normalized_current == normalized_expected:
            data_unchanged += 1
            continue
        if not idc.SetType(address, declaration):
            failed.append(
                {
                    "address": hex(address),
                    "declaration": declaration,
                    "reason": "data_type_failed",
                }
            )
            continue
        observed = idc.get_type(address)
        if _normalize_type_text(observed) != normalized_expected:
            failed.append(
                {
                    "address": hex(address),
                    "declaration": declaration,
                    "observed": observed,
                    "reason": "data_verification_failed",
                }
            )
            continue
        data_applied += 1

    for selector, declaration in TRUSTED_DECLARATIONS:
        address = _resolve_function(selector)
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
        if _normalize_type_text(observed) != expected_observed:
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
        applied_functions.append(selector)
        function_type_changes.append(
            {
                "selector": selector,
                "before": normalized_current,
                "expected": expected_observed,
                "observed": _normalize_type_text(observed),
            }
        )
        applied += 1

    cleared_lvar_overrides = [
        _clear_stale_stack_lvar_override(selector, stack_offset, stale_names)
        for selector, stack_offset, stale_names in STALE_STACK_LVAR_OVERRIDE_SPECS
    ]
    failed.extend(
        {
            "selector": result.get("selector"),
            "stale_lvar_override": result,
        }
        for result in cleared_lvar_overrides
        if result.get("status") == "failed"
    )

    lvar_results = [
        _sync_lvar(
            selector,
            expected_name,
            declaration,
            stack_offset,
            definition_address,
        )
        for (
            selector,
            expected_name,
            declaration,
            stack_offset,
            definition_address,
        ) in ARCHIVE_SHELL_LVAR_SPECS
    ]
    failed.extend(
        {
            "selector": result.get("selector"),
            "lvar": result,
        }
        for result in lvar_results
        if result.get("status") == "failed"
    )

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "parse_errors": parse_errors,
                "applied": applied,
                "applied_functions": applied_functions,
                "function_type_changes": function_type_changes,
                "unchanged": unchanged,
                "renamed": renamed,
                "names_unchanged": names_unchanged,
                "data_applied": data_applied,
                "data_unchanged": data_unchanged,
                "scalar_data_items_applied": scalar_data_items_applied,
                "scalar_data_items_unchanged": scalar_data_items_unchanged,
                "cleared_data_items": cleared_data_items,
                "scalar_data_items": scalar_data_items,
                "cleared_lvar_overrides": cleared_lvar_overrides,
                "lvars": lvar_results,
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
        print("usage: apply_archive_shell_types.py <header-path>", file=sys.stderr)
        ida_pro.qexit(2)
        return

    header_path = pathlib.Path(argv[1]).resolve()
    ida_pro.qexit(_sync_types(header_path))


if __name__ == "__main__":
    main()
