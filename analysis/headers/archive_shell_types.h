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

typedef int32_t (__stdcall* BassChannelPlayFn)(
    int32_t stream, int32_t restart, int32_t flags);
typedef int32_t (__stdcall* BassSamplePlayExFn)(
    int32_t sample_handle,
    int32_t start,
    int32_t frequency,
    int32_t volume,
    int32_t pan,
    int32_t loop);
typedef int32_t (__stdcall* BassSampleLoadFn)(
    int32_t from_memory,
    char* path_or_bytes,
    int32_t offset,
    int32_t byte_count,
    int32_t max_instances,
    int32_t flags);
typedef int32_t (__stdcall* BassFreeFn)(void);

int32_t __cdecl get_stream_length_preserve_position(File* file);

/* RShell-owned music and registered-sample entry points. */
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

/* RShellInit() */
uint8_t __cdecl initialize_game_data_archive(void);
int32_t __cdecl uninitialize_game_data_archive(void);

/* RShellFindFile(char*, bool) */
uint8_t __cdecl archive_or_file_exists(char* path, uint8_t force_filesystem);
ArchiveEntry* __cdecl find_archive_entry(char* path);

/* RShellLoadFileHeader(char*, void*, int) */
void* __cdecl load_file_bytes_fixed_size_from_archive_or_fs(
    char* path, void* buffer, int32_t byte_count);

/* RShellLoadFile(char*, void*, int*) and its two-argument overload */
void* __cdecl load_file_bytes_from_archive_or_fs(
    char* path, void* buffer, int32_t* out_size);
void* __cdecl load_file_bytes(char* path, int32_t* out_size);

/* RShellReadDirectory(char*, char*, int*, char (*)[128]) */
void __cdecl enumerate_matching_archive_or_fs_entries(
    char* directory,
    char* pattern,
    int32_t* out_count,
    EnumeratedEntryName* names);

/* RShellDatInit(char*) */
uint8_t __cdecl load_archive_index(char* path);

uint8_t __cdecl is_archive_index_loaded(void);

/* RShellMemoryScratch() and RShellMemoryScratch2() */
void* __cdecl get_archive_data_base(void);
void* __cdecl get_archive_data_end(void);

/* RShellMemoryMalloc(int, char*) and RShellMemoryFree(void*) */
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
extern BassChannelPlayFn g_bass_channel_play;
extern BassSamplePlayExFn g_bass_sample_play_ex;
extern BassSampleLoadFn g_bass_sample_load;
extern BassFreeFn g_bass_free;
extern RegisteredSoundSampleName g_registered_sound_sample_names[RSHELL_SOUND_MAX];
extern int32_t g_registered_sound_sample_count;
extern int32_t g_registered_sound_sample_handles[RSHELL_SOUND_MAX];
extern float g_stream_volume_scale;
extern float g_audio_backend_sfx_normalization_scale;
extern float g_audio_backend_voice_normalization_scale;
extern int32_t g_tracked_allocation_total_bytes;
extern float g_text_input_repeat_accumulator;
extern TrackedAllocationStack g_tracked_allocation_stack;
