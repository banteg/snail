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


SYNC_FAILURE_SENTINEL = "ARCHIVE_SHELL_SYNC_FAILED"


TRUSTED_DECLARATIONS = [
    (
        "shutdown_bass_audio_window",
        "int __cdecl shutdown_bass_audio_window(void);",
    ),
    (
        "reset_registered_sound_sample_count",
        "void __cdecl reset_registered_sound_sample_count(void);",
    ),
    (
        "cache_music_file",
        "char __cdecl cache_music_file(char* path, int unused, char* unused_default_path);",
    ),
    (
        "play_registered_warning_sample",
        "int __cdecl play_registered_warning_sample(int sample_id);",
    ),
    (
        "stop_registered_warning_sample",
        "int __cdecl stop_registered_warning_sample(int sample_handle);",
    ),
    (
        "play_sound_effect_backend",
        "void __cdecl play_sound_effect_backend(int sample_id, float gain, float pitch, float pan);",
    ),
    (
        "play_voice_backend",
        "void __cdecl play_voice_backend(int sample_id, float gain, float pitch, float pan);",
    ),
    (
        "register_sound_sample",
        "int __cdecl register_sound_sample(char* path, int normalization_class);",
    ),
    (
        "find_registered_sound_sample_id_by_name",
        "int __cdecl find_registered_sound_sample_id_by_name(char* sample_name);",
    ),
    (
        "initialize_bass_audio_backend",
        "char __thiscall initialize_bass_audio_backend(AudioBackend* backend, void* hwnd);",
    ),
    (
        "uninitialize_bass_audio_backend",
        "void __thiscall uninitialize_bass_audio_backend(AudioBackend* backend);",
    ),
    (
        "ensure_music_stream_from_path",
        "int __thiscall ensure_music_stream_from_path(AudioBackend* backend, char* path, char play_mode);",
    ),
    (
        "prepare_music_stream_reload_if_path_changed",
        "char __thiscall prepare_music_stream_reload_if_path_changed(AudioBackend* backend, char* path);",
    ),
    (
        "play_music_stream_from_bytes",
        "int __thiscall play_music_stream_from_bytes(AudioBackend* backend, char* path, char* bytes, int byte_count, char play_mode);",
    ),
    (
        "stop_music_stream",
        "void __thiscall stop_music_stream(AudioBackend* backend);",
    ),
    (
        "load_registered_sound_sample_from_path",
        "int __thiscall load_registered_sound_sample_from_path(AudioBackend* backend, char* path, int sample_id, int normalization_class);",
    ),
    (
        "load_registered_sound_sample_from_bytes",
        "void __thiscall load_registered_sound_sample_from_bytes(AudioBackend* backend, char* bytes, int byte_count, int sample_id, int normalization_class);",
    ),
    (
        "play_registered_sound_sample_scaled",
        "void __thiscall play_registered_sound_sample_scaled(AudioBackend* backend, int sample_id, float volume);",
    ),
    (
        "stop_sound_sample_handle",
        "int __thiscall stop_sound_sample_handle(AudioBackend* backend, int sample_handle);",
    ),
    (
        "stop_registered_sound_sample",
        "void __thiscall stop_registered_sound_sample(AudioBackend* backend, int sample_id);",
    ),
    (
        "is_registered_sound_sample_playing",
        "bool __thiscall is_registered_sound_sample_playing(AudioBackend* backend, int sample_id);",
    ),
    (
        "play_registered_sound_sample_default",
        "int __thiscall play_registered_sound_sample_default(AudioBackend* backend, int sample_id);",
    ),
    (
        "play_registered_sound_sample_backend",
        "void __thiscall play_registered_sound_sample_backend(AudioBackend* backend, int sample_id, float volume, float pitch);",
    ),
    (
        "play_registered_sound_sample_scaled_panned",
        "void __thiscall play_registered_sound_sample_scaled_panned(AudioBackend* backend, int sample_id, float volume, float pitch, float pan);",
    ),
    (
        "set_global_sample_volume_config",
        "int __thiscall set_global_sample_volume_config(AudioBackend* backend, float volume);",
    ),
    (
        "set_global_stream_volume_config",
        "int __thiscall set_global_stream_volume_config(AudioBackend* backend, float volume);",
    ),
    (
        "stop_audio_backend",
        "int __thiscall stop_audio_backend(AudioBackend* backend);",
    ),
    (
        "resume_audio_backend_if_paused",
        "void __thiscall resume_audio_backend_if_paused(AudioBackend* backend);",
    ),
    (
        "pause_audio_backend_if_running",
        "char __thiscall pause_audio_backend_if_running(AudioBackend* backend);",
    ),
    (
        "set_audio_normalization_scales",
        "void __thiscall set_audio_normalization_scales(AudioBackend* backend, float music_scale, float sfx_scale, float voice_scale);",
    ),
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
        "free_tracked_allocations_to_mark",
        "void __cdecl free_tracked_allocations_to_mark(void);",
    ),
    (
        "set_tracked_allocation_mark",
        "void __cdecl set_tracked_allocation_mark(void);",
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
    (0x407B00, "shutdown_bass_audio_window"),
    (0x432D40, "reset_registered_sound_sample_count"),
    (0x432D50, "cache_music_file"),
    (0x432DD0, "play_registered_warning_sample"),
    (0x432DE0, "stop_registered_warning_sample"),
    (0x432DF0, "play_sound_effect_backend"),
    (0x432E80, "play_voice_backend"),
    (0x432F10, "register_sound_sample"),
    (0x432FC0, "find_registered_sound_sample_id_by_name"),
    (0x449460, "initialize_bass_audio_backend"),
    (0x4496D0, "uninitialize_bass_audio_backend"),
    (0x449720, "ensure_music_stream_from_path"),
    (0x4497E0, "prepare_music_stream_reload_if_path_changed"),
    (0x449820, "play_music_stream_from_bytes"),
    (0x4498D0, "stop_music_stream"),
    (0x449920, "load_registered_sound_sample_from_path"),
    (0x449960, "load_registered_sound_sample_from_bytes"),
    (0x4499A0, "play_registered_sound_sample_scaled"),
    (0x449A10, "stop_sound_sample_handle"),
    (0x449A20, "stop_registered_sound_sample"),
    (0x449A40, "is_registered_sound_sample_playing"),
    (0x449A60, "play_registered_sound_sample_default"),
    (0x449A80, "play_registered_sound_sample_backend"),
    (0x449AE0, "play_registered_sound_sample_scaled_panned"),
    (0x449B50, "set_global_sample_volume_config"),
    (0x449B70, "set_global_stream_volume_config"),
    (0x449B90, "stop_audio_backend"),
    (0x449BA0, "resume_audio_backend_if_paused"),
    (0x449BC0, "pause_audio_backend_if_running"),
    (0x449BE0, "set_audio_normalization_scales"),
    (0x5088B0, "g_registered_sound_sample_names"),
    (0x5108B0, "g_registered_sound_sample_count"),
    (0x5108B4, "g_tracked_allocation_total_bytes"),
    (0x5108B8, "g_text_input_repeat_accumulator"),
    (0x5108C0, "g_tracked_allocation_stack"),
    (0x53C7E8, "g_music_memory_buffer"),
    (0x53C7EC, "g_archive_data_base"),
    (0x53C7F0, "g_archive_file"),
    (0x53C7F4, "g_archive_startup_flag"),
    (0x53C7F8, "g_archive_index_records"),
    (0x75162C, "g_bass_channel_bytes2_seconds"),
    (0x75165C, "g_bass_channel_remove_sync"),
    (0x751660, "g_bass_start"),
    (0x751670, "g_bass_stream_prebuf"),
    (0x751674, "g_bass_error_get_code"),
    (0x751680, "g_active_music_stream_sync"),
    (0x751698, "g_bass_update"),
    (0x7516A0, "g_cached_music_path"),
    (0x7517A0, "g_bass_stream_play"),
    (0x7527B4, "g_bass_sample_play_ex"),
    (0x7537CC, "g_bass_sample_load"),
    (0x7537D8, "g_bass_free"),
    (0x7537E0, "g_registered_sound_sample_handles"),
    (0x753BE4, "g_bass_channel_stop"),
    (0x753BF8, "g_bass_stream_create_file"),
    (0x753BFC, "g_bass_stop"),
    (0x753C08, "g_bass_init"),
    (0x753C18, "g_bass_channel_get_data"),
    (0x753C1C, "g_bass_set_config"),
    (0x753C20, "g_active_music_stream"),
    (0x753C58, "g_audio_backend"),
    (0x753C90, "g_bass_module"),
    (0x753C94, "g_bass_sample_stop"),
    (0x753C98, "g_bass_channel_get_position"),
    (0x753CA8, "g_bass_channel_is_active"),
    (0x753CB0, "g_bass_stream_free"),
    (0x753CBC, "g_bass_channel_get_level"),
    (0x753CC0, "g_bass_pause"),
    (0x753CC4, "g_bass_channel_set_sync"),
]

TRUSTED_DATA_DECLARATIONS = [
    (0x49701C, "GetProcAddress", "Win32GetProcAddressFn GetProcAddress;"),
    (0x497020, "LoadLibraryA", "Win32LoadLibraryAFn LoadLibraryA;"),
    (0x497024, "FreeLibrary", "Win32FreeLibraryFn FreeLibrary;"),
    (
        0x5088B0,
        "g_registered_sound_sample_names",
        "RegisteredSoundSampleName g_registered_sound_sample_names[256];",
    ),
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
    (0x7516A0, "g_cached_music_path", "char g_cached_music_path[256];"),
    (
        0x75162C,
        "g_bass_channel_bytes2_seconds",
        "BassChannelBytes2SecondsFn g_bass_channel_bytes2_seconds;",
    ),
    (
        0x75165C,
        "g_bass_channel_remove_sync",
        "BassChannelRemoveSyncFn g_bass_channel_remove_sync;",
    ),
    (0x751660, "g_bass_start", "BassStartFn g_bass_start;"),
    (0x751670, "g_bass_stream_prebuf", "BassStreamPreBufFn g_bass_stream_prebuf;"),
    (
        0x751674,
        "g_bass_error_get_code",
        "BassErrorGetCodeFn g_bass_error_get_code;",
    ),
    (0x751680, "g_active_music_stream_sync", "BassHandle g_active_music_stream_sync;"),
    (0x751698, "g_bass_update", "BassUpdateFn g_bass_update;"),
    (0x7517A0, "g_bass_stream_play", "BassStreamPlayFn g_bass_stream_play;"),
    (
        0x7527B4,
        "g_bass_sample_play_ex",
        "BassSamplePlayExFn g_bass_sample_play_ex;",
    ),
    (0x7537CC, "g_bass_sample_load", "BassSampleLoadFn g_bass_sample_load;"),
    (0x7537D8, "g_bass_free", "BassFreeFn g_bass_free;"),
    (
        0x7537E0,
        "g_registered_sound_sample_handles",
        "int g_registered_sound_sample_handles[256];",
    ),
    (0x753BE4, "g_bass_channel_stop", "BassChannelStopFn g_bass_channel_stop;"),
    (
        0x753BF8,
        "g_bass_stream_create_file",
        "BassStreamCreateFileFn g_bass_stream_create_file;",
    ),
    (0x753BFC, "g_bass_stop", "BassStopFn g_bass_stop;"),
    (0x753C08, "g_bass_init", "BassInitFn g_bass_init;"),
    (
        0x753C18,
        "g_bass_channel_get_data",
        "BassChannelGetDataFn g_bass_channel_get_data;",
    ),
    (0x753C1C, "g_bass_set_config", "BassSetConfigFn g_bass_set_config;"),
    (0x753C20, "g_active_music_stream", "BassHandle g_active_music_stream;"),
    (0x753C58, "g_audio_backend", "AudioBackend g_audio_backend;"),
    (0x753C90, "g_bass_module", "void* g_bass_module;"),
    (0x753C94, "g_bass_sample_stop", "BassSampleStopFn g_bass_sample_stop;"),
    (
        0x753C98,
        "g_bass_channel_get_position",
        "BassChannelGetPositionFn g_bass_channel_get_position;",
    ),
    (
        0x753CA8,
        "g_bass_channel_is_active",
        "BassChannelIsActiveFn g_bass_channel_is_active;",
    ),
    (0x753CB0, "g_bass_stream_free", "BassStreamFreeFn g_bass_stream_free;"),
    (
        0x753CBC,
        "g_bass_channel_get_level",
        "BassChannelGetLevelFn g_bass_channel_get_level;",
    ),
    (0x753CC0, "g_bass_pause", "BassPauseFn g_bass_pause;"),
    (
        0x753CC4,
        "g_bass_channel_set_sync",
        "BassChannelSetSyncFn g_bass_channel_set_sync;",
    ),
]

TRUSTED_SCALAR_DATA_ITEMS = [
    (0x49701C, 4),
    (0x497020, 4),
    (0x497024, 4),
    (0x5108B0, 4),
    (0x5108B4, 4),
    (0x5108B8, 4),
    (0x75162C, 4),
    (0x75165C, 4),
    (0x751660, 4),
    (0x751670, 4),
    (0x751674, 4),
    (0x751680, 4),
    (0x751698, 4),
    (0x7517A0, 4),
    (0x7527B4, 4),
    (0x7537CC, 4),
    (0x7537D8, 4),
    (0x753BE4, 4),
    (0x753BF8, 4),
    (0x753BFC, 4),
    (0x753C08, 4),
    (0x753C18, 4),
    (0x753C1C, 4),
    (0x753C20, 4),
    (0x753C90, 4),
    (0x753C94, 4),
    (0x753C98, 4),
    (0x753CA8, 4),
    (0x753CB0, 4),
    (0x753CBC, 4),
    (0x753CC0, 4),
    (0x753CC4, 4),
]

TRUSTED_EXTENT_DATA_ITEMS = [
    (
        0x753C58,
        0x1C,
        "g_audio_backend",
        None,
    ),
    (
        0x7516A0,
        0x100,
        "g_cached_music_path",
        None,
    ),
    (
        0x5088B0,
        0x8000,
        "g_registered_sound_sample_names",
        "char[32768]",
    ),
    (
        0x7537E0,
        0x400,
        "g_registered_sound_sample_handles",
        "int[257]",
    ),
]

STALE_DATA_ITEM_SPECS = [
    (0x5108B0, 0x10, "g_registered_sound_sample_count", "int[4]"),
    (0x7516A0, 0x2140, "g_cached_music_path", "char[8512]"),
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

REGISTERED_SOUND_SPLIT_LVAR_SPECS = [
    (
        "register_sound_sample",
        "path",
        "char *",
        24,
        0x432F2B,
        "sample_size",
        "int sample_size;",
    ),
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
    normalized = re.sub(r"\s*\[\s*", "[", normalized)
    normalized = re.sub(r"\s*\]\s*", "]", normalized)
    normalized = re.sub(r"\(\s*", "(", normalized)
    normalized = re.sub(r"\s*\)", ")", normalized)
    normalized = normalized.replace("(void)", "()")
    return normalized.strip()


def _declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\s*(?=\()", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


def _data_declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(
        rf"\b{re.escape(selector)}\s*(?=\[|;)", "", declaration, count=1
    )
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


def _ensure_extent_data_item(
    address: int,
    size: int,
    expected_stale_name: str,
    expected_stale_type: str | None,
) -> dict[str, object]:
    item_head = ida_bytes.get_item_head(address)
    item_size = ida_bytes.get_item_size(item_head)
    if item_head == address and item_size == size:
        return {
            "status": "unchanged",
            "address": hex(address),
            "item_size": item_size,
        }

    # Refuse to widen anything except the exact one-byte typed head recovered
    # from the old database. create_byte(..., force=True) replaces that head and
    # claims the complete non-overlapping extent in one operation.
    if item_head != address or item_size != 1:
        return {
            "status": "failed",
            "reason": "unexpected_extent_data_item",
            "address": hex(address),
            "expected_size": size,
            "observed_head": hex(item_head),
            "observed_size": item_size,
        }

    observed_name = idc.get_name(item_head)
    observed_type = _normalize_type_text(idc.get_type(item_head))
    normalized_expected_type = _normalize_type_text(expected_stale_type)
    if (
        observed_name != expected_stale_name
        or observed_type != normalized_expected_type
    ):
        return {
            "status": "failed",
            "reason": "unexpected_stale_extent_data_item",
            "address": hex(address),
            "expected_name": expected_stale_name,
            "expected_type": normalized_expected_type,
            "observed_name": observed_name,
            "observed_type": observed_type,
        }

    if not ida_bytes.create_byte(address, size, True):
        return {
            "status": "failed",
            "reason": "create_extent_data_item_failed",
            "address": hex(address),
            "expected_size": size,
        }

    verified_head = ida_bytes.get_item_head(address)
    verified_size = ida_bytes.get_item_size(verified_head)
    if verified_head != address or verified_size != size:
        return {
            "status": "failed",
            "reason": "extent_data_item_readback_failed",
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


def _sync_split_lvar(
    selector: str,
    source_name: str,
    source_type: str,
    stack_offset: int,
    split_definition_address: int,
    expected_name: str,
    declaration: str,
) -> dict[str, object]:
    address = _resolve_function(selector)
    if address is None:
        return {"status": "failed", "reason": "missing_function", "selector": selector}

    local_type = ida_typeinf.tinfo_t()
    if not ida_typeinf.parse_decl(
        local_type,
        None,
        declaration,
        ida_typeinf.PT_SIL,
    ):
        return {
            "status": "failed",
            "reason": "parse_split_local_type_failed",
            "selector": selector,
            "declaration": declaration,
        }

    expected_type = _normalize_type_text(str(local_type))
    normalized_source_type = _normalize_type_text(source_type)
    cfunc = ida_hexrays.decompile(address)
    existing = [
        lvar
        for lvar in cfunc.get_lvars()
        if not lvar.is_arg_var
        and lvar.name == expected_name
        and _normalize_type_text(str(lvar.type())) == expected_type
        and lvar.defea == split_definition_address
    ]
    if len(existing) == 1:
        return {
            "status": "unchanged",
            "selector": selector,
            "name": existing[0].name,
            "type": str(existing[0].type()),
            "definition_address": hex(existing[0].defea),
        }
    if existing:
        return {
            "status": "failed",
            "reason": "unexpected_existing_split_local_candidates",
            "selector": selector,
            "candidate_count": len(existing),
        }

    sources = [
        lvar
        for lvar in cfunc.get_lvars()
        if lvar.is_arg_var
        and lvar.is_stk_var()
        and lvar.get_stkoff() == stack_offset
        and lvar.name == source_name
        and _normalize_type_text(str(lvar.type())) == normalized_source_type
    ]
    if len(sources) != 1:
        return {
            "status": "failed",
            "reason": "unexpected_split_source_candidates",
            "selector": selector,
            "source_name": source_name,
            "stack_offset": stack_offset,
            "candidate_count": len(sources),
        }

    source = sources[0]
    info = ida_hexrays.lvar_saved_info_t()
    info.ll = ida_hexrays.lvar_locator_t(
        source.location,
        split_definition_address,
    )
    info.name = expected_name
    info.type = local_type
    info.set_split_lvar()
    if not ida_hexrays.modify_user_lvar_info(
        address,
        ida_hexrays.MLI_NAME | ida_hexrays.MLI_TYPE | ida_hexrays.MLI_SET_FLAGS,
        info,
    ):
        return {
            "status": "failed",
            "reason": "modify_split_lvar_info_failed",
            "selector": selector,
            "expected_name": expected_name,
        }

    ida_hexrays.mark_cfunc_dirty(address, True)
    verified_cfunc = ida_hexrays.decompile(address)
    verified = [
        lvar
        for lvar in verified_cfunc.get_lvars()
        if not lvar.is_arg_var
        and lvar.name == expected_name
        and _normalize_type_text(str(lvar.type())) == expected_type
        and lvar.defea == split_definition_address
    ]
    if len(verified) != 1:
        return {
            "status": "failed",
            "reason": "split_local_readback_failed",
            "selector": selector,
            "expected_name": expected_name,
            "definition_address": hex(split_definition_address),
            "candidate_count": len(verified),
        }

    return {
        "status": "applied",
        "selector": selector,
        "source_name": source.name,
        "source_type": str(source.type()),
        "name": verified[0].name,
        "type": str(verified[0].type()),
        "definition_address": hex(verified[0].defea),
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
    extent_data_items_applied = 0
    extent_data_items_unchanged = 0
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

    extent_data_items = [
        _ensure_extent_data_item(address, size, stale_name, stale_type)
        for address, size, stale_name, stale_type in TRUSTED_EXTENT_DATA_ITEMS
    ]
    extent_data_items_applied = sum(
        result.get("status") == "applied" for result in extent_data_items
    )
    extent_data_items_unchanged = sum(
        result.get("status") == "unchanged" for result in extent_data_items
    )
    failed.extend(
        {"extent_data_item": result}
        for result in extent_data_items
        if result.get("status") == "failed"
    )
    if failed:
        print(SYNC_FAILURE_SENTINEL)
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "header": str(header_path),
                    "parse_errors": parse_errors,
                    "phase": "data_item_guard",
                    "cleared_data_items": cleared_data_items,
                    "scalar_data_items": scalar_data_items,
                    "extent_data_items": extent_data_items,
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

    split_lvar_results = [
        _sync_split_lvar(
            selector,
            source_name,
            source_type,
            stack_offset,
            split_definition_address,
            expected_name,
            declaration,
        )
        for (
            selector,
            source_name,
            source_type,
            stack_offset,
            split_definition_address,
            expected_name,
            declaration,
        ) in REGISTERED_SOUND_SPLIT_LVAR_SPECS
    ]
    failed.extend(
        {
            "selector": result.get("selector"),
            "split_lvar": result,
        }
        for result in split_lvar_results
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

    sync_failed = bool(parse_errors or failed or missing)
    if sync_failed:
        print(SYNC_FAILURE_SENTINEL)
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
                "extent_data_items_applied": extent_data_items_applied,
                "extent_data_items_unchanged": extent_data_items_unchanged,
                "cleared_data_items": cleared_data_items,
                "scalar_data_items": scalar_data_items,
                "extent_data_items": extent_data_items,
                "cleared_lvar_overrides": cleared_lvar_overrides,
                "split_lvars": split_lvar_results,
                "lvars": lvar_results,
                "missing": missing,
                "failed": failed,
            },
            indent=2,
        )
    )

    if sync_failed:
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
