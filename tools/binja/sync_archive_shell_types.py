#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_data_var_updates,
    apply_proto_updates,
    apply_symbol_updates,
    emit_summary,
    types_declare,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_archive_shell_types.h"

DATA_SYMBOL_UPDATES = (
    ("0x5088b0", "g_registered_sound_sample_names"),
    ("0x5108b0", "g_registered_sound_sample_count"),
    ("0x5108b4", "g_tracked_allocation_total_bytes"),
    ("0x5108b8", "g_text_input_repeat_accumulator"),
    ("0x5108c0", "g_tracked_allocation_stack"),
    ("0x53c7e8", "g_music_memory_buffer"),
    ("0x53c7ec", "g_archive_data_base"),
    ("0x53c7f0", "g_archive_file"),
    ("0x53c7f4", "g_archive_startup_flag"),
    ("0x53c7f8", "g_archive_index_records"),
)

FUNCTION_SYMBOL_UPDATES = (
    ("0x432d40", "reset_registered_sound_sample_count"),
    ("0x432f10", "register_sound_sample"),
    ("0x432fc0", "find_registered_sound_sample_id_by_name"),
    ("0x48b72d", "malloc"),
    ("0x48c211", "findfirst"),
    ("0x48c2db", "findnext"),
)

DATA_VAR_UPDATES = (
    ("0x5088b0", "RegisteredSoundSampleName[256]"),
    ("0x5108b0", "int32_t"),
    ("0x5108b4", "int32_t"),
    ("0x5108b8", "float"),
    ("0x5108c0", "TrackedAllocationStack"),
    ("0x53c7e8", "char*"),
    ("0x53c7ec", "void*"),
    ("0x53c7f0", "File*"),
    ("0x53c7f4", "uint8_t"),
    ("0x53c7f8", "ArchiveIndex*"),
)

PROTO_UPDATES = (
    (
        "reset_registered_sound_sample_count",
        "void __cdecl reset_registered_sound_sample_count()",
    ),
    (
        "register_sound_sample",
        "int32_t __cdecl register_sound_sample(char* path, int32_t normalization_class)",
    ),
    (
        "find_registered_sound_sample_id_by_name",
        "int32_t __cdecl find_registered_sound_sample_id_by_name(char* sample_name)",
    ),
    (
        "malloc",
        "void* __cdecl malloc(uint32_t size)",
    ),
    (
        "findfirst",
        "int32_t __cdecl findfirst(char* pattern, FileSearchData* find_data)",
    ),
    (
        "findnext",
        "int32_t __cdecl findnext(int32_t handle, FileSearchData* find_data)",
    ),
    (
        "get_stream_length_preserve_position",
        "int32_t __cdecl get_stream_length_preserve_position(File* file)",
    ),
    (
        "get_tracked_allocation_size",
        "int32_t __thiscall get_tracked_allocation_size(TrackedAllocationStack* stack, void* pointer)",
    ),
    (
        "push_tracked_allocation",
        "void __thiscall push_tracked_allocation(TrackedAllocationStack* stack, char* label, void* pointer, int32_t guarded_size)",
    ),
    (
        "pop_tracked_allocation",
        "int32_t __thiscall pop_tracked_allocation(TrackedAllocationStack* stack, void* pointer)",
    ),
    (
        "free_tracked_allocations_to_mark",
        "void __cdecl free_tracked_allocations_to_mark()",
    ),
    (
        "set_tracked_allocation_mark",
        "void __cdecl set_tracked_allocation_mark()",
    ),
    (
        "initialize_game_data_archive",
        "uint8_t __cdecl initialize_game_data_archive()",
    ),
    (
        "uninitialize_game_data_archive",
        "int32_t __cdecl uninitialize_game_data_archive()",
    ),
    (
        "archive_or_file_exists",
        "uint8_t __cdecl archive_or_file_exists(char* path, uint8_t force_filesystem)",
    ),
    (
        "find_archive_entry",
        "ArchiveEntry* __cdecl find_archive_entry(char* path)",
    ),
    (
        "load_file_bytes_fixed_size_from_archive_or_fs",
        "void* __cdecl load_file_bytes_fixed_size_from_archive_or_fs(char* path, void* buffer, int32_t byte_count)",
    ),
    (
        "load_file_bytes_from_archive_or_fs",
        "void* __cdecl load_file_bytes_from_archive_or_fs(char* path, void* buffer, int32_t* out_size)",
    ),
    (
        "load_file_bytes",
        "void* __cdecl load_file_bytes(char* path, int32_t* out_size)",
    ),
    (
        "enumerate_matching_archive_or_fs_entries",
        "void __cdecl enumerate_matching_archive_or_fs_entries(char* directory, char* pattern, int32_t* out_count, EnumeratedEntryName* names)",
    ),
    (
        "load_archive_index",
        "uint8_t __cdecl load_archive_index(char* path)",
    ),
    (
        "is_archive_index_loaded",
        "uint8_t __cdecl is_archive_index_loaded()",
    ),
    (
        "get_archive_data_base",
        "void* __cdecl get_archive_data_base()",
    ),
    (
        "get_archive_data_end",
        "void* __cdecl get_archive_data_end()",
    ),
    (
        "allocate_tracked_memory",
        "void* __cdecl allocate_tracked_memory(int32_t size, char* name)",
    ),
    (
        "free_tracked_memory",
        "void __cdecl free_tracked_memory(void* pointer)",
    ),
    (
        "xor_decode_buffer_with_index",
        "char* __cdecl xor_decode_buffer_with_index(char* bytes, int32_t byte_count)",
    ),
    (
        "write_file_bytes",
        "int32_t __cdecl write_file_bytes(char* path, void* bytes, int32_t byte_count)",
    ),
    (
        "save_config_file",
        "char* __cdecl save_config_file(char* path, void* bytes, int32_t byte_count)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the narrow RShell archive/file ownership slice to Binary Ninja."
    )
    parser.add_argument("--target", default=DEFAULT_TARGET, help="Binary Ninja target selector.")
    parser.add_argument(
        "--header",
        type=Path,
        default=DEFAULT_HEADER_PATH,
        help="Narrow Binary Ninja type header.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations: list[dict[str, object]] = []
    operations.append(
        types_declare(REPO_ROOT, target=args.target, header_path=header_path)
    )
    operations.extend(
        apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=DATA_SYMBOL_UPDATES,
            kind="data",
        )
    )
    operations.extend(
        apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=FUNCTION_SYMBOL_UPDATES,
            kind="function",
        )
    )
    operations.extend(
        apply_data_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=DATA_VAR_UPDATES,
        )
    )
    operations.extend(
        apply_proto_updates(REPO_ROOT, target=args.target, updates=PROTO_UPDATES)
    )
    return emit_summary(
        repo_root=REPO_ROOT,
        target=args.target,
        header_path=header_path,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
