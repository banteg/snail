// uninitialize_game_data_archive @ 0x430ef0 (cdecl)

struct File;

extern int g_archive_data_base; // data_53c7ec
extern File* g_archive_file; // data_53c7f0
extern int g_archive_index_records; // data_53c7f8

int free_tracked_memory(void* pointer);
extern "C" int __cdecl fclose(File* file);

int uninitialize_game_data_archive()
{
    free_tracked_memory((void*)g_archive_data_base);
    int result = g_archive_index_records;
    if (g_archive_index_records != 0) {
        result = fclose(g_archive_file);
    }
    g_archive_index_records = 0;
    return result;
}
