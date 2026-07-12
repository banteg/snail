typedef unsigned char uint8_t;
typedef int int32_t;

typedef struct File File;

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

int32_t __cdecl get_stream_length_preserve_position(File* file);

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

extern char* g_music_memory_buffer;
extern void* g_archive_data_base;
extern File* g_archive_file;
extern uint8_t g_archive_startup_flag;
extern ArchiveIndex* g_archive_index_records;
