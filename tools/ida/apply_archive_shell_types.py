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
        "get_stream_length_preserve_position",
        "int __cdecl get_stream_length_preserve_position(File* file);",
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
]

TRUSTED_NAMES = [
    (0x53C7E8, "g_music_memory_buffer"),
    (0x53C7EC, "g_archive_data_base"),
    (0x53C7F0, "g_archive_file"),
    (0x53C7F4, "g_archive_startup_flag"),
    (0x53C7F8, "g_archive_index_records"),
]

TRUSTED_DATA_DECLARATIONS = [
    (0x53C7E8, "g_music_memory_buffer", "char* g_music_memory_buffer;"),
    (0x53C7EC, "g_archive_data_base", "void* g_archive_data_base;"),
    (0x53C7F0, "g_archive_file", "File* g_archive_file;"),
    (0x53C7F4, "g_archive_startup_flag", "unsigned char g_archive_startup_flag;"),
    (0x53C7F8, "g_archive_index_records", "ArchiveIndex* g_archive_index_records;"),
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


def _data_declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\s*(?=;)", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


def _sync_types(header_path: pathlib.Path) -> int:
    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE)

    applied = 0
    unchanged = 0
    renamed = 0
    names_unchanged = 0
    data_applied = 0
    data_unchanged = 0
    missing = []
    failed = []

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
                "data_applied": data_applied,
                "data_unchanged": data_unchanged,
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
