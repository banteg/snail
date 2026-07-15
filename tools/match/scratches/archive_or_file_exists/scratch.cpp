// archive_or_file_exists @ 0x430fd0 (cdecl)

#include "archive_index.h"

ArchiveEntry* find_archive_entry(char* path);
int report_warningf(char* format, ...);

char __cdecl archive_or_file_exists(char* path, char force_filesystem)
{
    if (g_archive_index_records == 0 || force_filesystem != 0) {
        FILE* file = fopen(path, "rb");
        if (file == 0)
            return 0;
        fclose(file);
        return 1;
    }

    if (find_archive_entry(path) == 0) {
        report_warningf("Missing Dat File %s", path);
        return 0;
    }

    return 1;
}
