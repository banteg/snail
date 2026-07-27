#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_data_var_removals,
    apply_data_var_updates,
    apply_int_display_updates,
    apply_proto_updates,
    apply_split_user_var_update,
    apply_symbol_removals,
    apply_symbol_updates,
    apply_user_var_updates,
    emit_summary,
    remove_user_var_updates,
    types_declare,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_archive_shell_types.h"

DATA_SYMBOL_UPDATES = (
    ("0x503320", "g_enumerated_entry_count"),
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
    ("0x75162c", "g_bass_channel_bytes2_seconds"),
    ("0x75165c", "g_bass_channel_remove_sync"),
    ("0x751660", "g_bass_start"),
    ("0x751670", "g_bass_stream_prebuf"),
    ("0x751674", "g_bass_error_get_code"),
    ("0x751680", "g_active_music_stream_sync"),
    ("0x751698", "g_bass_update"),
    ("0x7516a0", "g_cached_music_path"),
    ("0x7517a0", "g_bass_stream_play"),
    ("0x7527b4", "g_bass_sample_play_ex"),
    ("0x7537cc", "g_bass_sample_load"),
    ("0x7537d8", "g_bass_free"),
    ("0x7537e0", "g_registered_sound_sample_handles"),
    ("0x753be4", "g_bass_channel_stop"),
    ("0x753bf8", "g_bass_stream_create_file"),
    ("0x753bfc", "g_bass_stop"),
    ("0x753c08", "g_bass_init"),
    ("0x753c18", "g_bass_channel_get_data"),
    ("0x753c1c", "g_bass_set_config"),
    ("0x753c20", "g_active_music_stream"),
    ("0x753c58", "g_audio_backend"),
    ("0x753c90", "g_bass_module"),
    ("0x753c94", "g_bass_sample_stop"),
    ("0x753c98", "g_bass_channel_get_position"),
    ("0x753ca8", "g_bass_channel_is_active"),
    ("0x753cb0", "g_bass_stream_free"),
    ("0x753cbc", "g_bass_channel_get_level"),
    ("0x753cc0", "g_bass_pause"),
    ("0x753cc4", "g_bass_channel_set_sync"),
)

FUNCTION_SYMBOL_UPDATES = (
    ("0x405140", "file_exists"),
    ("0x4051b0", "load_file_bytes_allocating"),
    ("0x4052a0", "save_file_bytes_with_optional_archive_scramble"),
    ("0x405340", "delete_file_path"),
    ("0x405350", "toggle_archive_high_bit_in_place"),
    ("0x407b00", "shutdown_bass_audio_window"),
    ("0x42f0a0", "load_png_image"),
    ("0x431dc0", "strings_equal_case_insensitive"),
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
    ("0x44e600", "find_case_insensitive_substring"),
    ("0x48b3a7", "fclose"),
    ("0x48b41d", "fopen"),
    ("0x48b430", "fseek"),
    ("0x48b4bc", "ftell"),
    ("0x48b614", "printf"),
    ("0x48b645", "fread"),
    ("0x48b72d", "malloc"),
    ("0x48b7a1", "fwrite"),
    ("0x48b8d5", "free"),
    ("0x48c18b", "chdir"),
    ("0x48c211", "findfirst"),
    ("0x48c2db", "findnext"),
    ("0x496946", "getcwd"),
)

DATA_VAR_UPDATES = (
    ("0x49701c", "Win32GetProcAddressFn"),
    ("0x497020", "Win32LoadLibraryAFn"),
    ("0x497024", "Win32FreeLibraryFn"),
    ("0x503320", "int32_t"),
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
    ("0x75162c", "BassChannelBytes2SecondsFn"),
    ("0x75165c", "BassChannelRemoveSyncFn"),
    ("0x751660", "BassStartFn"),
    ("0x751670", "BassStreamPreBufFn"),
    ("0x751674", "BassErrorGetCodeFn"),
    ("0x751680", "BassHandle"),
    ("0x751698", "BassUpdateFn"),
    ("0x7516a0", "CachedMusicPath"),
    ("0x7517a0", "BassStreamPlayFn"),
    ("0x7527b4", "BassSamplePlayExFn"),
    ("0x7537cc", "BassSampleLoadFn"),
    ("0x7537d8", "BassFreeFn"),
    ("0x7537e0", "int32_t[256]"),
    ("0x753be4", "BassChannelStopFn"),
    ("0x753bf8", "BassStreamCreateFileFn"),
    ("0x753bfc", "BassStopFn"),
    ("0x753c08", "BassInitFn"),
    ("0x753c18", "BassChannelGetDataFn"),
    ("0x753c1c", "BassSetConfigFn"),
    ("0x753c20", "BassHandle"),
    ("0x753c58", "AudioBackend"),
    ("0x753c90", "void*"),
    ("0x753c94", "BassSampleStopFn"),
    ("0x753c98", "BassChannelGetPositionFn"),
    ("0x753ca8", "BassChannelIsActiveFn"),
    ("0x753cb0", "BassStreamFreeFn"),
    ("0x753cbc", "BassChannelGetLevelFn"),
    ("0x753cc0", "BassPauseFn"),
    ("0x753cc4", "BassChannelSetSyncFn"),
)

LEGACY_AUDIO_BACKEND_DATA_VAR_REMOVALS = (
    ("0x753c64", "float"),
    ("0x753c68", "float"),
    ("0x753c6c", "float"),
)

LEGACY_AUDIO_BACKEND_DATA_VAR_REPLACEMENTS = (
    ("0x753c64", "AudioBackend"),
    ("0x753c68", "AudioBackend"),
    ("0x753c6c", "AudioBackend"),
)

LEGACY_AUDIO_BACKEND_SYMBOL_REMOVALS = (
    ("0x753c64", "g_stream_volume_scale"),
    ("0x753c68", "g_audio_backend_sfx_normalization_scale"),
    ("0x753c6c", "g_audio_backend_voice_normalization_scale"),
)

PROTO_UPDATES = (
    (
        "strings_equal_case_insensitive",
        "bool __cdecl strings_equal_case_insensitive(char* left, char* prefix)",
    ),
    (
        "find_case_insensitive_substring",
        "char* __cdecl find_case_insensitive_substring(char* pattern, char* searched)",
    ),
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
        "printf",
        "int32_t __cdecl printf(char* format, ...)",
    ),
    (
        "free",
        "void __cdecl free(void* pointer)",
    ),
    (
        "fopen",
        "File* __cdecl fopen(char* path, char* mode)",
    ),
    (
        "fread",
        "uint32_t __cdecl fread(void* bytes, uint32_t element_size, uint32_t element_count, File* stream)",
    ),
    (
        "fwrite",
        "uint32_t __cdecl fwrite(void* bytes, uint32_t element_size, uint32_t element_count, File* stream)",
    ),
    (
        "fseek",
        "int32_t __cdecl fseek(File* stream, int32_t offset, int32_t origin)",
    ),
    (
        "ftell",
        "int32_t __cdecl ftell(File* stream)",
    ),
    (
        "fclose",
        "int32_t __cdecl fclose(File* stream)",
    ),
    (
        "getcwd",
        "char* __cdecl getcwd(char* buffer, int32_t max_length)",
    ),
    (
        "chdir",
        "int32_t __cdecl chdir(char* path)",
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
        "classify_archive_entry_extension",
        "ArchiveEntryExtensionClass __cdecl classify_archive_entry_extension(uint8_t* path, uint8_t* stem_out)",
    ),
    (
        "rebuild_game_archive_if_needed",
        "void __cdecl rebuild_game_archive_if_needed()",
    ),
    (
        "load_png_image",
        "int32_t __cdecl load_png_image(char* png_path, uint8_t** out_pixels, int32_t* out_width, int32_t* out_height, int32_t* out_channels, uint8_t* background_rgb, int32_t file_offset)",
    ),
    (
        "file_exists",
        "uint8_t __cdecl file_exists(char* path)",
    ),
    (
        "load_file_bytes_allocating",
        "void* __cdecl load_file_bytes_allocating(char* path, int32_t* out_size)",
    ),
    (
        "save_file_bytes_with_optional_archive_scramble",
        "int32_t __cdecl save_file_bytes_with_optional_archive_scramble(char* path, void* bytes, int32_t byte_count, uint8_t should_scramble)",
    ),
    (
        "delete_file_path",
        "int32_t __cdecl delete_file_path(char* path)",
    ),
    (
        "toggle_archive_high_bit_in_place",
        "char* __cdecl toggle_archive_high_bit_in_place(char* bytes, int32_t byte_count)",
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


# These stale direct overrides predate the CRT prototypes below. Reanalysis
# proved that one EAX identity spans unrelated enumerator values, while one ESI
# identity is an unused pre-prototype artifact rather than the tracked buffer.
STALE_ARCHIVE_CURSOR_USER_VAR_REMOVALS = (
    (
        "enumerate_matching_archive_or_fs_entries",
        "RegisterVariableSourceType",
        49,
        66,
        "archive_index",
        "ArchiveIndex*",
    ),
    (
        "load_file_bytes_from_archive_or_fs",
        "RegisterVariableSourceType",
        210,
        69,
        "tracked_memory",
        "void*",
    ),
)


# Split the two concrete ArchiveIndex loads and their loop phi away from the
# directory byte, basename byte, and pattern-pointer lifetimes that reuse EAX.
ARCHIVE_INDEX_SPLIT_DEFINITIONS = (
    ("0x431740", "mlil", "RegisterVariableSourceType", 524288, 66),
    ("0x431771", "mlil_ssa", "RegisterVariableSourceType", 49, 66),
    ("0x43184c", "mlil", "RegisterVariableSourceType", 268, 66),
)
ARCHIVE_INDEX_SPLIT_TARGET_VAR = (
    "RegisterVariableSourceType",
    524288,
    66,
)


# Exact SSA lifetimes recovered after applying the CRT prototypes. These names
# do not infer new storage: they distinguish the ArchiveIndex owner, its current
# 12-byte ArchiveEntry cursor, borrowed path cursors, stream handles, allocation
# results, byte counts, archive positions, and caller-owned output buffers.
ARCHIVE_CURSOR_USER_VAR_UPDATES = (
    (
        "enumerate_matching_archive_or_fs_entries",
        "RegisterVariableSourceType",
        53,
        72,
        "directory_cursor",
        "char*",
    ),
    (
        "enumerate_matching_archive_or_fs_entries",
        "RegisterVariableSourceType",
        60,
        67,
        "archive_path_cursor",
        "char*",
    ),
    (
        "enumerate_matching_archive_or_fs_entries",
        "RegisterVariableSourceType",
        64,
        68,
        "archive_path_char",
        "char",
    ),
    (
        "enumerate_matching_archive_or_fs_entries",
        "RegisterVariableSourceType",
        149,
        66,
        "folded_basename_char",
        "char",
    ),
    (
        "enumerate_matching_archive_or_fs_entries",
        "RegisterVariableSourceType",
        120,
        71,
        "basename_cursor",
        "char*",
    ),
    (
        "enumerate_matching_archive_or_fs_entries",
        "RegisterVariableSourceType",
        123,
        73,
        "basename_index",
        "int32_t",
    ),
    (
        "enumerate_matching_archive_or_fs_entries",
        "RegisterVariableSourceType",
        125,
        72,
        "pattern_index",
        "int32_t",
    ),
    (
        "enumerate_matching_archive_or_fs_entries",
        "RegisterVariableSourceType",
        304,
        69,
        "pattern_char",
        "char",
    ),
    (
        "enumerate_matching_archive_or_fs_entries",
        "RegisterVariableSourceType",
        235,
        72,
        "archive_names",
        "EnumeratedEntryName*",
    ),
    (
        "enumerate_matching_archive_or_fs_entries",
        "RegisterVariableSourceType",
        425,
        73,
        "filesystem_names",
        "EnumeratedEntryName*",
    ),
    (
        "enumerate_matching_archive_or_fs_entries",
        "StackVariableSourceType",
        31,
        -796,
        "archive_entry_index",
        "int32_t",
    ),
    (
        "enumerate_matching_archive_or_fs_entries",
        "StackVariableSourceType",
        45,
        -800,
        "archive_entry_offset",
        "int32_t",
    ),
    (
        "enumerate_matching_archive_or_fs_entries",
        "StackVariableSourceType",
        0,
        -512,
        "cwd_buffer",
        "char[512]",
    ),
    (
        "load_file_bytes_from_archive_or_fs",
        "RegisterVariableSourceType",
        20,
        69,
        "archive_index",
        "ArchiveIndex*",
    ),
    (
        "load_file_bytes_from_archive_or_fs",
        "RegisterVariableSourceType",
        39,
        73,
        "archive_entry_index",
        "int32_t",
    ),
    (
        "load_file_bytes_from_archive_or_fs",
        "RegisterVariableSourceType",
        49,
        69,
        "archive_entry_cursor",
        "ArchiveEntry*",
    ),
    (
        "load_file_bytes_from_archive_or_fs",
        "RegisterVariableSourceType",
        62,
        68,
        "archive_path_cursor",
        "char*",
    ),
    (
        "load_file_bytes_from_archive_or_fs",
        "RegisterVariableSourceType",
        54,
        72,
        "requested_path_cursor",
        "char*",
    ),
    (
        "load_file_bytes_from_archive_or_fs",
        "RegisterVariableSourceType",
        52,
        67,
        "archive_path_char",
        "char",
    ),
    (
        "load_file_bytes_from_archive_or_fs",
        "RegisterVariableSourceType",
        62,
        66,
        "requested_path_char",
        "char",
    ),
    (
        "load_file_bytes_from_archive_or_fs",
        "RegisterVariableSourceType",
        119,
        66,
        "filesystem_file",
        "File*",
    ),
    (
        "load_file_bytes_from_archive_or_fs",
        "RegisterVariableSourceType",
        124,
        72,
        "filesystem_stream",
        "File*",
    ),
    (
        "load_file_bytes_from_archive_or_fs",
        "RegisterVariableSourceType",
        263,
        72,
        "allocation_byte_count_offset",
        "int32_t",
    ),
    (
        "load_file_bytes_from_archive_or_fs",
        "RegisterVariableSourceType",
        271,
        66,
        "tracked_memory",
        "void*",
    ),
    (
        "load_file_bytes_from_archive_or_fs",
        "RegisterVariableSourceType",
        284,
        66,
        "allocation_archive_position",
        "int32_t",
    ),
    (
        "load_file_bytes_from_archive_or_fs",
        "RegisterVariableSourceType",
        388,
        66,
        "caller_archive_position",
        "int32_t",
    ),
    (
        "load_file_bytes_from_archive_or_fs",
        "RegisterVariableSourceType",
        442,
        73,
        "caller_byte_count_offset",
        "int32_t",
    ),
    (
        "load_file_bytes_from_archive_or_fs",
        "RegisterVariableSourceType",
        494,
        66,
        "filesystem_byte_count",
        "int32_t",
    ),
    (
        "load_file_bytes_from_archive_or_fs",
        "RegisterVariableSourceType",
        499,
        69,
        "filesystem_output_buffer",
        "void*",
    ),
    (
        "load_file_bytes_from_archive_or_fs",
        "StackVariableSourceType",
        0,
        -512,
        "cwd_buffer",
        "char[512]",
    ),
)


# Exact owners in the archive bootstrap, fixed-size read, and lookup family.
# The index loader deliberately keeps the allocated serialized owner separate
# from the live ArchiveIndex view installed while its path offsets are rebased.
ARCHIVE_SERVICE_USER_VAR_UPDATES = (
    (
        "initialize_game_data_archive",
        "RegisterVariableSourceType",
        51,
        66,
        "archive_ready",
        "uint8_t",
    ),
    (
        "initialize_game_data_archive",
        "RegisterVariableSourceType",
        116,
        66,
        "slot_axis_y_cursor",
        "float*",
    ),
    (
        "initialize_game_data_archive",
        "StackVariableSourceType",
        0,
        -16,
        "clip_rect",
        "RECT",
    ),
    (
        "load_archive_index",
        "StackVariableSourceType",
        0,
        -124,
        "serialized_header",
        "SerializedArchiveHeader",
    ),
    (
        "load_archive_index",
        "RegisterVariableSourceType",
        82,
        73,
        "index_byte_count",
        "int32_t",
    ),
    (
        "load_archive_index",
        "RegisterVariableSourceType",
        92,
        66,
        "allocated_serialized_index",
        "SerializedArchiveIndex*",
    ),
    (
        "load_archive_index",
        "RegisterVariableSourceType",
        97,
        72,
        "serialized_index",
        "SerializedArchiveIndex*",
    ),
    (
        "load_archive_index",
        "RegisterVariableSourceType",
        116,
        66,
        "archive_index",
        "ArchiveIndex*",
    ),
    (
        "load_archive_index",
        "RegisterVariableSourceType",
        128,
        68,
        "entry_index",
        "int32_t",
    ),
    (
        "load_archive_index",
        "RegisterVariableSourceType",
        134,
        67,
        "entry_byte_offset",
        "int32_t",
    ),
    (
        "load_archive_index",
        "RegisterVariableSourceType",
        136,
        72,
        "serialized_path_offset",
        "int32_t",
    ),
    (
        "load_archive_index",
        "RegisterVariableSourceType",
        143,
        72,
        "rebased_path",
        "char*",
    ),
    (
        "load_archive_index",
        "RegisterVariableSourceType",
        165,
        66,
        "archive_stream",
        "File*",
    ),
    (
        "load_file_bytes_fixed_size_from_archive_or_fs",
        "RegisterVariableSourceType",
        20,
        66,
        "archive_index",
        "ArchiveIndex*",
    ),
    (
        "load_file_bytes_fixed_size_from_archive_or_fs",
        "RegisterVariableSourceType",
        33,
        67,
        "archive_entry_count",
        "int32_t",
    ),
    (
        "load_file_bytes_fixed_size_from_archive_or_fs",
        "RegisterVariableSourceType",
        35,
        71,
        "archive_entry_index",
        "int32_t",
    ),
    (
        "load_file_bytes_fixed_size_from_archive_or_fs",
        "RegisterVariableSourceType",
        49,
        73,
        "archive_entry_cursor",
        "ArchiveEntry*",
    ),
    (
        "load_file_bytes_fixed_size_from_archive_or_fs",
        "RegisterVariableSourceType",
        69,
        68,
        "archive_path_cursor",
        "char*",
    ),
    (
        "load_file_bytes_fixed_size_from_archive_or_fs",
        "RegisterVariableSourceType",
        54,
        69,
        "requested_path",
        "char*",
    ),
    (
        "load_file_bytes_fixed_size_from_archive_or_fs",
        "RegisterVariableSourceType",
        61,
        72,
        "requested_path_cursor",
        "char*",
    ),
    (
        "load_file_bytes_fixed_size_from_archive_or_fs",
        "RegisterVariableSourceType",
        52,
        67,
        "archive_path_char",
        "char",
    ),
    (
        "load_file_bytes_fixed_size_from_archive_or_fs",
        "RegisterVariableSourceType",
        69,
        66,
        "requested_path_char",
        "char",
    ),
    (
        "load_file_bytes_fixed_size_from_archive_or_fs",
        "RegisterVariableSourceType",
        125,
        73,
        "archive_output_buffer",
        "void*",
    ),
    (
        "load_file_bytes_fixed_size_from_archive_or_fs",
        "RegisterVariableSourceType",
        175,
        66,
        "allocated_buffer",
        "void*",
    ),
    (
        "load_file_bytes_fixed_size_from_archive_or_fs",
        "RegisterVariableSourceType",
        189,
        66,
        "allocation_archive_position",
        "int32_t",
    ),
    (
        "load_file_bytes_fixed_size_from_archive_or_fs",
        "RegisterVariableSourceType",
        284,
        66,
        "caller_archive_position",
        "int32_t",
    ),
    (
        "load_file_bytes_fixed_size_from_archive_or_fs",
        "RegisterVariableSourceType",
        392,
        66,
        "filesystem_file",
        "File*",
    ),
    (
        "load_file_bytes_fixed_size_from_archive_or_fs",
        "RegisterVariableSourceType",
        397,
        72,
        "filesystem_stream",
        "File*",
    ),
    (
        "load_file_bytes_fixed_size_from_archive_or_fs",
        "RegisterVariableSourceType",
        459,
        73,
        "filesystem_output_buffer",
        "void*",
    ),
    (
        "load_file_bytes_fixed_size_from_archive_or_fs",
        "RegisterVariableSourceType",
        466,
        69,
        "filesystem_byte_count",
        "int32_t",
    ),
    (
        "load_file_bytes_fixed_size_from_archive_or_fs",
        "RegisterVariableSourceType",
        494,
        66,
        "allocated_filesystem_buffer",
        "void*",
    ),
    (
        "load_file_bytes_fixed_size_from_archive_or_fs",
        "StackVariableSourceType",
        0,
        -512,
        "cwd_buffer",
        "char[512]",
    ),
    (
        "find_archive_entry",
        "RegisterVariableSourceType",
        5,
        73,
        "archive_index",
        "ArchiveIndex*",
    ),
    (
        "find_archive_entry",
        "RegisterVariableSourceType",
        15,
        66,
        "archive_entry_count",
        "int32_t",
    ),
    (
        "find_archive_entry",
        "RegisterVariableSourceType",
        17,
        69,
        "archive_entry_index",
        "int32_t",
    ),
    (
        "find_archive_entry",
        "RegisterVariableSourceType",
        27,
        71,
        "requested_path",
        "char*",
    ),
    (
        "find_archive_entry",
        "RegisterVariableSourceType",
        31,
        73,
        "archive_entry_cursor",
        "ArchiveEntry*",
    ),
    (
        "find_archive_entry",
        "RegisterVariableSourceType",
        44,
        68,
        "archive_path_cursor",
        "char*",
    ),
    (
        "find_archive_entry",
        "RegisterVariableSourceType",
        36,
        72,
        "requested_path_cursor",
        "char*",
    ),
    (
        "find_archive_entry",
        "RegisterVariableSourceType",
        34,
        67,
        "archive_path_char",
        "char",
    ),
    (
        "find_archive_entry",
        "RegisterVariableSourceType",
        44,
        66,
        "requested_path_char",
        "char",
    ),
    (
        "find_archive_entry",
        "StackVariableSourceType",
        21,
        -4,
        "entry_count_snapshot",
        "int32_t",
    ),
)


# Exact archive-rebuild lifetimes after correcting load_png_image to the
# seven-stack-argument cdecl proven by its sole callsite and callee body. The
# serialized source allocation remains distinct from the rebuilt output owner;
# field cursors intentionally stay scalar pointers where the native loop walks
# one word inside each 12-byte record.
ARCHIVE_REBUILD_USER_VAR_UPDATES = (
    (
        "classify_archive_entry_extension",
        "RegisterVariableSourceType",
        17,
        66,
        "path_cursor",
        "uint8_t*",
    ),
    (
        "classify_archive_entry_extension",
        "RegisterVariableSourceType",
        4,
        68,
        "stem_cursor",
        "uint8_t*",
    ),
    (
        "classify_archive_entry_extension",
        "RegisterVariableSourceType",
        8,
        67,
        "current_char",
        "uint8_t",
    ),
    (
        "classify_archive_entry_extension",
        "RegisterVariableSourceType",
        41,
        66,
        "extension_cursor",
        "uint8_t*",
    ),
    (
        "rebuild_game_archive_if_needed",
        "RegisterVariableSourceType",
        62,
        69,
        "rebuilt_index",
        "SerializedArchiveIndex*",
    ),
    (
        "rebuild_game_archive_if_needed",
        "RegisterVariableSourceType",
        78,
        66,
        "source_index",
        "SerializedArchiveIndex*",
    ),
    (
        "rebuild_game_archive_if_needed",
        "RegisterVariableSourceType",
        131,
        71,
        "initial_payload_offset",
        "int32_t",
    ),
    (
        "rebuild_game_archive_if_needed",
        "RegisterVariableSourceType",
        143,
        71,
        "payload_cursor",
        "char*",
    ),
    (
        "rebuild_game_archive_if_needed",
        "RegisterVariableSourceType",
        168,
        69,
        "source_byte_count_cursor",
        "int32_t*",
    ),
    (
        "rebuild_game_archive_if_needed",
        "RegisterVariableSourceType",
        171,
        67,
        "source_to_rebuilt_delta",
        "int32_t",
    ),
    (
        "rebuild_game_archive_if_needed",
        "RegisterVariableSourceType",
        188,
        73,
        "entry_path",
        "char*",
    ),
    (
        "rebuild_game_archive_if_needed",
        "RegisterVariableSourceType",
        454,
        73,
        "y",
        "int32_t",
    ),
    (
        "rebuild_game_archive_if_needed",
        "RegisterVariableSourceType",
        465,
        67,
        "source_pixel_offset",
        "int32_t",
    ),
    (
        "rebuild_game_archive_if_needed",
        "RegisterVariableSourceType",
        482,
        66,
        "destination_pixel_offset",
        "int32_t",
    ),
    (
        "rebuild_game_archive_if_needed",
        "RegisterVariableSourceType",
        584,
        71,
        "payload_end",
        "char*",
    ),
    (
        "rebuild_game_archive_if_needed",
        "RegisterVariableSourceType",
        591,
        67,
        "alignment_remainder",
        "int32_t",
    ),
    (
        "rebuild_game_archive_if_needed",
        "StackVariableSourceType",
        157,
        -556,
        "rebuilt_data_offset_cursor",
        "int32_t*",
    ),
    (
        "rebuild_game_archive_if_needed",
        "StackVariableSourceType",
        74,
        -552,
        "rebuilt_index_saved",
        "SerializedArchiveIndex*",
    ),
    (
        "rebuild_game_archive_if_needed",
        "StackVariableSourceType",
        91,
        -544,
        "source_index_saved",
        "SerializedArchiveIndex*",
    ),
    (
        "rebuild_game_archive_if_needed",
        "StackVariableSourceType",
        436,
        -536,
        "x",
        "int32_t",
    ),
    (
        "rebuild_game_archive_if_needed",
        "StackVariableSourceType",
        173,
        -532,
        "source_to_rebuilt_delta_saved",
        "int32_t",
    ),
    (
        "rebuild_game_archive_if_needed",
        "StackVariableSourceType",
        147,
        -528,
        "entry_index",
        "int32_t",
    ),
    (
        "rebuild_game_archive_if_needed",
        "StackVariableSourceType",
        0,
        -524,
        "dam_size",
        "int32_t",
    ),
    (
        "rebuild_game_archive_if_needed",
        "StackVariableSourceType",
        192,
        -520,
        "entry_path_saved",
        "char*",
    ),
    (
        "rebuild_game_archive_if_needed",
        "StackVariableSourceType",
        0,
        -516,
        "png_background_rgb",
        "uint32_t",
    ),
    (
        "rebuild_game_archive_if_needed",
        "StackVariableSourceType",
        0,
        -512,
        "entry_stem",
        "uint8_t[512]",
    ),
    (
        "rebuild_game_archive_if_needed",
        "StackVariableSourceType",
        0,
        -560,
        "png_pixels",
        "uint8_t*",
    ),
    (
        "rebuild_game_archive_if_needed",
        "StackVariableSourceType",
        0,
        -548,
        "png_width",
        "int32_t",
    ),
    (
        "rebuild_game_archive_if_needed",
        "StackVariableSourceType",
        0,
        -540,
        "png_height",
        "int32_t",
    ),
    (
        "rebuild_game_archive_if_needed",
        "StackVariableSourceType",
        0,
        -564,
        "png_channels",
        "int32_t",
    ),
)


ARCHIVE_SERVICE_INT_DISPLAY_UPDATES = (
    (
        "initialize_game_data_archive",
        "0x430e8e",
        "68 00 00 40 00",
        0x400000,
        0xFFFFFFFF,
        "UnsignedHexadecimalDisplayType",
        'allocate_tracked_memory(0x400000, "Scratch Pad")',
        "allocate_tracked_memory(&__dos_header",
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
        apply_data_var_removals(
            REPO_ROOT,
            target=args.target,
            removals=LEGACY_AUDIO_BACKEND_DATA_VAR_REMOVALS,
            replacements=LEGACY_AUDIO_BACKEND_DATA_VAR_REPLACEMENTS,
        )
    )
    operations.extend(
        apply_symbol_removals(
            REPO_ROOT,
            target=args.target,
            removals=LEGACY_AUDIO_BACKEND_SYMBOL_REMOVALS,
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
    operations.extend(
        remove_user_var_updates(
            REPO_ROOT,
            target=args.target,
            removals=STALE_ARCHIVE_CURSOR_USER_VAR_REMOVALS,
        )
    )
    operations.extend(
        apply_split_user_var_update(
            REPO_ROOT,
            target=args.target,
            identifier="enumerate_matching_archive_or_fs_entries",
            definitions=ARCHIVE_INDEX_SPLIT_DEFINITIONS,
            target_var=ARCHIVE_INDEX_SPLIT_TARGET_VAR,
            variable_name="archive_index",
            variable_type="ArchiveIndex*",
        )
    )
    operations.extend(
        apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=ARCHIVE_CURSOR_USER_VAR_UPDATES,
        )
    )
    operations.extend(
        apply_int_display_updates(
            REPO_ROOT,
            target=args.target,
            updates=ARCHIVE_SERVICE_INT_DISPLAY_UPDATES,
        )
    )
    operations.extend(
        apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=ARCHIVE_SERVICE_USER_VAR_UPDATES,
        )
    )
    operations.extend(
        apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=ARCHIVE_REBUILD_USER_VAR_UPDATES,
        )
    )
    return emit_summary(
        repo_root=REPO_ROOT,
        target=args.target,
        header_path=header_path,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
