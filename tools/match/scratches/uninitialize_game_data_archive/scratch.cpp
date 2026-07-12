// uninitialize_game_data_archive @ 0x430ef0 (cdecl)

#include "archive_index.h"

extern void* g_archive_data_base; // data_53c7ec / RShellScratch

void free_tracked_memory(void* pointer);
extern "C" int __cdecl fclose(File* file);

int uninitialize_game_data_archive()
{
    free_tracked_memory(g_archive_data_base);
    int result = (int)g_archive_index_records;
    if (g_archive_index_records != 0) {
        result = fclose(g_archive_file);
    }
    g_archive_index_records = 0;
    return result;
}
