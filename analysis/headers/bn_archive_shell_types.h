typedef unsigned char uint8_t;
typedef int int32_t;
typedef unsigned int uint32_t;

typedef struct File File;

typedef struct FileSearchData {
    uint32_t attributes;
    int32_t time_created;
    int32_t time_accessed;
    int32_t time_written;
    uint32_t size;
    char name[260];
} FileSearchData;

typedef struct TrackedAllocationRecord {
    void* pointer;
    int32_t guarded_size;
    int32_t unknown;
} TrackedAllocationRecord;

typedef struct TrackedAllocationStack {
    int32_t depth;
    int32_t bookmark_depth;
    int32_t unknown;
    TrackedAllocationRecord records[1];
} TrackedAllocationStack;

void* __cdecl malloc(uint32_t size);
File* __cdecl fopen(char* path, char* mode);
uint32_t __cdecl fwrite(
    void* bytes,
    uint32_t element_size,
    uint32_t element_count,
    File* stream);
int32_t __cdecl fclose(File* stream);
char* __cdecl getcwd(char* buffer, int32_t max_length);
int32_t __cdecl chdir(char* path);
int32_t __cdecl findfirst(char* pattern, FileSearchData* find_data);
int32_t __cdecl findnext(int32_t handle, FileSearchData* find_data);
int32_t __cdecl set_current_directory_with_drive_fallback(char* path);

int32_t __thiscall get_tracked_allocation_size(
    TrackedAllocationStack* stack, void* pointer);
void __thiscall push_tracked_allocation(
    TrackedAllocationStack* stack,
    char* label,
    void* pointer,
    int32_t guarded_size);
int32_t __thiscall pop_tracked_allocation(
    TrackedAllocationStack* stack, void* pointer);
void __cdecl free_tracked_allocations_to_mark(void);
void __cdecl set_tracked_allocation_mark(void);

typedef struct ArchiveEntry {
    char* path;
    int32_t data_offset;
    int32_t byte_count;
} ArchiveEntry;

typedef struct ArchiveIndex {
    int32_t count;
    ArchiveEntry entries[1];
} ArchiveIndex;

typedef char EnumeratedEntryName[128];

typedef enum RegisteredSoundLimits {
    RSHELL_SOUND_MAX = 256,
    RSHELL_SOUND_NAME_BYTES = 128
} RegisteredSoundLimits;

typedef char RegisteredSoundSampleName[RSHELL_SOUND_NAME_BYTES];
typedef char CachedMusicPath[256];

/*
 * Recovered AudioBackend prefix used by exact member-function scratches.
 * Binary Ninja's data replay retains the three proven interior scalar aliases
 * until its aggregate data-variable migration is independently validated.
 */
typedef struct AudioBackend {
    uint8_t music_stream_active;
    uint8_t unknown_01[3];
    int32_t unknown_04;
    float unknown_08;
    float music_normalization_scale;
    float sfx_normalization_scale;
    float voice_normalization_scale;
    uint8_t is_paused;
} AudioBackend;

typedef uint32_t BassHandle;
typedef unsigned __int64 BassQword;
typedef void (__stdcall* BassSyncProc)(
    BassHandle sync_handle,
    BassHandle channel,
    uint32_t data,
    uint32_t user);
typedef uint32_t (__stdcall* BassSetConfigFn)(
    uint32_t option, uint32_t value);
typedef uint32_t (__stdcall* BassErrorGetCodeFn)(void);
typedef int32_t (__stdcall* BassInitFn)(
    uint32_t device,
    uint32_t frequency,
    uint32_t flags,
    void* hwnd,
    const void* direct_sound_guid);
typedef int32_t (__stdcall* BassFreeFn)(void);
typedef int32_t (__stdcall* BassUpdateFn)(void);
typedef int32_t (__stdcall* BassStartFn)(void);
typedef int32_t (__stdcall* BassStopFn)(void);
typedef int32_t (__stdcall* BassPauseFn)(void);
typedef BassHandle (__stdcall* BassSampleLoadFn)(
    int32_t from_memory,
    const void* path_or_bytes,
    uint32_t offset,
    uint32_t byte_count,
    uint32_t max_instances,
    uint32_t flags);
typedef BassHandle (__stdcall* BassSamplePlayExFn)(
    BassHandle sample_handle,
    uint32_t start,
    int32_t frequency,
    int32_t volume,
    int32_t pan,
    int32_t loop);
typedef int32_t (__stdcall* BassSampleStopFn)(BassHandle sample_handle);
typedef BassHandle (__stdcall* BassStreamCreateFileFn)(
    int32_t from_memory,
    const void* path_or_bytes,
    uint32_t offset,
    uint32_t byte_count,
    uint32_t flags);
typedef void (__stdcall* BassStreamFreeFn)(BassHandle stream_handle);
typedef int32_t (__stdcall* BassStreamPreBufFn)(BassHandle stream_handle);
typedef int32_t (__stdcall* BassStreamPlayFn)(
    BassHandle stream_handle, int32_t flush, uint32_t flags);
typedef float (__stdcall* BassChannelBytes2SecondsFn)(
    BassHandle channel_handle, BassQword position);
typedef uint32_t (__stdcall* BassChannelIsActiveFn)(
    BassHandle channel_handle);
typedef int32_t (__stdcall* BassChannelStopFn)(BassHandle channel_handle);
typedef BassQword (__stdcall* BassChannelGetPositionFn)(
    BassHandle channel_handle);
typedef uint32_t (__stdcall* BassChannelGetLevelFn)(
    BassHandle channel_handle);
typedef uint32_t (__stdcall* BassChannelGetDataFn)(
    BassHandle channel_handle, void* buffer, uint32_t byte_count);
typedef BassHandle (__stdcall* BassChannelSetSyncFn)(
    BassHandle channel_handle,
    uint32_t sync_type,
    BassQword parameter,
    BassSyncProc callback,
    uint32_t user);
typedef int32_t (__stdcall* BassChannelRemoveSyncFn)(
    BassHandle channel_handle, BassHandle sync_handle);
typedef void* (__stdcall* Win32LoadLibraryAFn)(const char* library_name);
typedef void* (__stdcall* Win32GetProcAddressFn)(
    void* module, const char* export_name);
typedef int32_t (__stdcall* Win32FreeLibraryFn)(void* module);

int32_t __cdecl get_stream_length_preserve_position(File* file);

void __cdecl reset_registered_sound_sample_count(void);
char __cdecl cache_music_file(
    char* path, int32_t unused, char* unused_default_path);
int32_t __cdecl play_registered_warning_sample(int32_t sample_id);
int32_t __cdecl stop_registered_warning_sample(int32_t sample_handle);
void __cdecl play_sound_effect_backend(
    int32_t sample_id, float gain, float pitch, float pan);
void __cdecl play_voice_backend(
    int32_t sample_id, float gain, float pitch, float pan);
int32_t __cdecl register_sound_sample(char* path, int32_t normalization_class);
int32_t __cdecl find_registered_sound_sample_id_by_name(char* sample_name);
int32_t __cdecl shutdown_bass_audio_window(void);

char __thiscall initialize_bass_audio_backend(
    AudioBackend* backend, void* hwnd);
void __thiscall uninitialize_bass_audio_backend(AudioBackend* backend);
int32_t __thiscall ensure_music_stream_from_path(
    AudioBackend* backend, char* path, char play_mode);
char __thiscall prepare_music_stream_reload_if_path_changed(
    AudioBackend* backend, char* path);
int32_t __thiscall play_music_stream_from_bytes(
    AudioBackend* backend,
    char* path,
    char* bytes,
    int32_t byte_count,
    char play_mode);
void __thiscall stop_music_stream(AudioBackend* backend);
int32_t __thiscall load_registered_sound_sample_from_path(
    AudioBackend* backend,
    char* path,
    int32_t sample_id,
    int32_t normalization_class);
void __thiscall load_registered_sound_sample_from_bytes(
    AudioBackend* backend,
    char* bytes,
    int32_t byte_count,
    int32_t sample_id,
    int32_t normalization_class);
void __thiscall play_registered_sound_sample_scaled(
    AudioBackend* backend, int32_t sample_id, float volume);
int32_t __thiscall stop_sound_sample_handle(
    AudioBackend* backend, int32_t sample_handle);
void __thiscall stop_registered_sound_sample(
    AudioBackend* backend, int32_t sample_id);
bool __thiscall is_registered_sound_sample_playing(
    AudioBackend* backend, int32_t sample_id);
int32_t __thiscall play_registered_sound_sample_default(
    AudioBackend* backend, int32_t sample_id);
void __thiscall play_registered_sound_sample_backend(
    AudioBackend* backend, int32_t sample_id, float volume, float pitch);
void __thiscall play_registered_sound_sample_scaled_panned(
    AudioBackend* backend,
    int32_t sample_id,
    float volume,
    float pitch,
    float pan);
int32_t __thiscall set_global_sample_volume_config(
    AudioBackend* backend, float volume);
int32_t __thiscall set_global_stream_volume_config(
    AudioBackend* backend, float volume);
int32_t __thiscall stop_audio_backend(AudioBackend* backend);
void __thiscall resume_audio_backend_if_paused(AudioBackend* backend);
char __thiscall pause_audio_backend_if_running(AudioBackend* backend);
void __thiscall set_audio_normalization_scales(
    AudioBackend* backend,
    float music_scale,
    float sfx_scale,
    float voice_scale);

uint8_t __cdecl initialize_game_data_archive(void);
int32_t __cdecl uninitialize_game_data_archive(void);
uint8_t __cdecl archive_or_file_exists(char* path, uint8_t force_filesystem);
ArchiveEntry* __cdecl find_archive_entry(char* path);
void* __cdecl load_file_bytes_fixed_size_from_archive_or_fs(
    char* path, void* buffer, int32_t byte_count);
void* __cdecl load_file_bytes_from_archive_or_fs(
    char* path, void* buffer, int32_t* out_size);
void* __cdecl load_file_bytes(char* path, int32_t* out_size);
void __cdecl enumerate_matching_archive_or_fs_entries(
    char* directory,
    char* pattern,
    int32_t* out_count,
    EnumeratedEntryName* names);
uint8_t __cdecl load_archive_index(char* path);
uint8_t __cdecl is_archive_index_loaded(void);
void* __cdecl get_archive_data_base(void);
void* __cdecl get_archive_data_end(void);
void* __cdecl allocate_tracked_memory(int32_t size, char* name);
void __cdecl free_tracked_memory(void* pointer);
char* __cdecl xor_decode_buffer_with_index(char* bytes, int32_t byte_count);
int32_t __cdecl write_file_bytes(char* path, void* bytes, int32_t byte_count);
char* __cdecl save_config_file(char* path, void* bytes, int32_t byte_count);

extern char* g_music_memory_buffer;
extern void* g_archive_data_base;
extern File* g_archive_file;
extern uint8_t g_archive_startup_flag;
extern ArchiveIndex* g_archive_index_records;
extern CachedMusicPath g_cached_music_path;
extern BassChannelBytes2SecondsFn g_bass_channel_bytes2_seconds;
extern BassChannelRemoveSyncFn g_bass_channel_remove_sync;
extern BassStartFn g_bass_start;
extern BassStreamPreBufFn g_bass_stream_prebuf;
extern BassErrorGetCodeFn g_bass_error_get_code;
extern BassHandle g_active_music_stream_sync;
extern BassUpdateFn g_bass_update;
extern BassStreamPlayFn g_bass_stream_play;
extern BassSamplePlayExFn g_bass_sample_play_ex;
extern BassSampleLoadFn g_bass_sample_load;
extern BassFreeFn g_bass_free;
extern BassChannelStopFn g_bass_channel_stop;
extern BassStreamCreateFileFn g_bass_stream_create_file;
extern BassStopFn g_bass_stop;
extern BassInitFn g_bass_init;
extern BassChannelGetDataFn g_bass_channel_get_data;
extern BassSetConfigFn g_bass_set_config;
extern BassHandle g_active_music_stream;
extern void* g_bass_module;
extern BassSampleStopFn g_bass_sample_stop;
extern BassChannelGetPositionFn g_bass_channel_get_position;
extern BassChannelIsActiveFn g_bass_channel_is_active;
extern BassStreamFreeFn g_bass_stream_free;
extern BassChannelGetLevelFn g_bass_channel_get_level;
extern BassPauseFn g_bass_pause;
extern BassChannelSetSyncFn g_bass_channel_set_sync;
extern Win32GetProcAddressFn GetProcAddress;
extern Win32LoadLibraryAFn LoadLibraryA;
extern Win32FreeLibraryFn FreeLibrary;
extern RegisteredSoundSampleName g_registered_sound_sample_names[RSHELL_SOUND_MAX];
extern int32_t g_registered_sound_sample_count;
extern int32_t g_registered_sound_sample_handles[RSHELL_SOUND_MAX];
extern float g_stream_volume_scale;
extern float g_audio_backend_sfx_normalization_scale;
extern float g_audio_backend_voice_normalization_scale;
extern AudioBackend g_audio_backend;
extern int32_t g_tracked_allocation_total_bytes;
extern float g_text_input_repeat_accumulator;
extern TrackedAllocationStack g_tracked_allocation_stack;
