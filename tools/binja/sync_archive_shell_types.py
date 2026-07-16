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
    ("0x7516a0", "g_cached_music_path"),
    ("0x7517a0", "g_bass_channel_play"),
    ("0x7527b4", "g_bass_sample_play_ex"),
    ("0x7537cc", "g_bass_sample_load"),
    ("0x7537d8", "g_bass_free"),
    ("0x7537e0", "g_registered_sound_sample_handles"),
    ("0x753c58", "g_audio_backend"),
    ("0x753c64", "g_stream_volume_scale"),
    ("0x753c68", "g_audio_backend_sfx_normalization_scale"),
    ("0x753c6c", "g_audio_backend_voice_normalization_scale"),
)

FUNCTION_SYMBOL_UPDATES = (
    ("0x407b00", "shutdown_bass_audio_window"),
    ("0x432d40", "reset_registered_sound_sample_count"),
    ("0x432d50", "cache_music_file"),
    ("0x432dd0", "play_registered_warning_sample"),
    ("0x432de0", "stop_registered_warning_sample"),
    ("0x432df0", "play_sound_effect_backend"),
    ("0x432e80", "play_voice_backend"),
    ("0x432f10", "register_sound_sample"),
    ("0x432fc0", "find_registered_sound_sample_id_by_name"),
    ("0x449460", "initialize_bass_audio_backend"),
    ("0x4496d0", "uninitialize_bass_audio_backend"),
    ("0x449720", "ensure_music_stream_from_path"),
    ("0x4497e0", "prepare_music_stream_reload_if_path_changed"),
    ("0x449820", "play_music_stream_from_bytes"),
    ("0x4498d0", "stop_music_stream"),
    ("0x449920", "load_registered_sound_sample_from_path"),
    ("0x449960", "load_registered_sound_sample_from_bytes"),
    ("0x4499a0", "play_registered_sound_sample_scaled"),
    ("0x449a10", "stop_sound_sample_handle"),
    ("0x449a20", "stop_registered_sound_sample"),
    ("0x449a40", "is_registered_sound_sample_playing"),
    ("0x449a60", "play_registered_sound_sample_default"),
    ("0x449a80", "play_registered_sound_sample_backend"),
    ("0x449ae0", "play_registered_sound_sample_scaled_panned"),
    ("0x449b50", "set_global_sample_volume_config"),
    ("0x449b70", "set_global_stream_volume_config"),
    ("0x449b90", "stop_audio_backend"),
    ("0x449ba0", "resume_audio_backend_if_paused"),
    ("0x449bc0", "pause_audio_backend_if_running"),
    ("0x449be0", "set_audio_normalization_scales"),
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
    ("0x7516a0", "CachedMusicPath"),
    ("0x7517a0", "BassChannelPlayFn"),
    ("0x7527b4", "BassSamplePlayExFn"),
    ("0x7537cc", "BassSampleLoadFn"),
    ("0x7537d8", "BassFreeFn"),
    ("0x7537e0", "int32_t[256]"),
    ("0x753c64", "float"),
    ("0x753c68", "float"),
    ("0x753c6c", "float"),
)

PROTO_UPDATES = (
    (
        "shutdown_bass_audio_window",
        "int32_t __cdecl shutdown_bass_audio_window()",
    ),
    (
        "reset_registered_sound_sample_count",
        "void __cdecl reset_registered_sound_sample_count()",
    ),
    (
        "cache_music_file",
        "char __cdecl cache_music_file(char* path, int32_t unused, char* unused_default_path)",
    ),
    (
        "play_registered_warning_sample",
        "int32_t __cdecl play_registered_warning_sample(int32_t sample_id)",
    ),
    (
        "stop_registered_warning_sample",
        "int32_t __cdecl stop_registered_warning_sample(int32_t sample_handle)",
    ),
    (
        "play_sound_effect_backend",
        "void __cdecl play_sound_effect_backend(int32_t sample_id, float gain, float pitch, float pan)",
    ),
    (
        "play_voice_backend",
        "void __cdecl play_voice_backend(int32_t sample_id, float gain, float pitch, float pan)",
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
        "initialize_bass_audio_backend",
        "char __thiscall initialize_bass_audio_backend(AudioBackend* backend, void* hwnd)",
    ),
    (
        "uninitialize_bass_audio_backend",
        "void __thiscall uninitialize_bass_audio_backend(AudioBackend* backend)",
    ),
    (
        "ensure_music_stream_from_path",
        "int32_t __thiscall ensure_music_stream_from_path(AudioBackend* backend, char* path, char play_mode)",
    ),
    (
        "prepare_music_stream_reload_if_path_changed",
        "char __thiscall prepare_music_stream_reload_if_path_changed(AudioBackend* backend, char* path)",
    ),
    (
        "play_music_stream_from_bytes",
        "int32_t __thiscall play_music_stream_from_bytes(AudioBackend* backend, char* path, char* bytes, int32_t byte_count, char play_mode)",
    ),
    (
        "stop_music_stream",
        "void __thiscall stop_music_stream(AudioBackend* backend)",
    ),
    (
        "load_registered_sound_sample_from_path",
        "int32_t __thiscall load_registered_sound_sample_from_path(AudioBackend* backend, char* path, int32_t sample_id, int32_t normalization_class)",
    ),
    (
        "load_registered_sound_sample_from_bytes",
        "void __thiscall load_registered_sound_sample_from_bytes(AudioBackend* backend, char* bytes, int32_t byte_count, int32_t sample_id, int32_t normalization_class)",
    ),
    (
        "play_registered_sound_sample_scaled",
        "void __thiscall play_registered_sound_sample_scaled(AudioBackend* backend, int32_t sample_id, float volume)",
    ),
    (
        "stop_sound_sample_handle",
        "int32_t __thiscall stop_sound_sample_handle(AudioBackend* backend, int32_t sample_handle)",
    ),
    (
        "stop_registered_sound_sample",
        "void __thiscall stop_registered_sound_sample(AudioBackend* backend, int32_t sample_id)",
    ),
    (
        "is_registered_sound_sample_playing",
        "bool __thiscall is_registered_sound_sample_playing(AudioBackend* backend, int32_t sample_id)",
    ),
    (
        "play_registered_sound_sample_default",
        "int32_t __thiscall play_registered_sound_sample_default(AudioBackend* backend, int32_t sample_id)",
    ),
    (
        "play_registered_sound_sample_backend",
        "void __thiscall play_registered_sound_sample_backend(AudioBackend* backend, int32_t sample_id, float volume, float pitch)",
    ),
    (
        "play_registered_sound_sample_scaled_panned",
        "void __thiscall play_registered_sound_sample_scaled_panned(AudioBackend* backend, int32_t sample_id, float volume, float pitch, float pan)",
    ),
    (
        "set_global_sample_volume_config",
        "int32_t __thiscall set_global_sample_volume_config(AudioBackend* backend, float volume)",
    ),
    (
        "set_global_stream_volume_config",
        "int32_t __thiscall set_global_stream_volume_config(AudioBackend* backend, float volume)",
    ),
    (
        "stop_audio_backend",
        "int32_t __thiscall stop_audio_backend(AudioBackend* backend)",
    ),
    (
        "resume_audio_backend_if_paused",
        "void __thiscall resume_audio_backend_if_paused(AudioBackend* backend)",
    ),
    (
        "pause_audio_backend_if_running",
        "char __thiscall pause_audio_backend_if_running(AudioBackend* backend)",
    ),
    (
        "set_audio_normalization_scales",
        "void __thiscall set_audio_normalization_scales(AudioBackend* backend, float music_scale, float sfx_scale, float voice_scale)",
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
        description="Apply the narrow RShell archive/audio ownership slice to Binary Ninja."
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
