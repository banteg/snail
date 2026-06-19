// find_archive_entry @ 0x431250 (cdecl, ret)

#include "archive_index.h"

ArchiveEntry* find_archive_entry(char* path)
{
    ArchiveIndex* index = g_archive_index_records;
    int count;
    int entry_index;
    char* requested_path;
    ArchiveEntry* entry;

    if (index == 0) {
        goto not_found;
    }

    count = index->count;
    entry_index = 0;
    if (count <= 0) {
        goto not_found;
    }

    requested_path = path;
    entry = index->entries;

scan_entry:
    {
        char* requested_cursor = requested_path;
        char* archive_cursor = entry->path;
        char archive_char;

        archive_char = *archive_cursor;

        while (archive_char != 0) {
            char requested_char = *requested_cursor;
            if (requested_char == 0) {
                break;
            }

            if (requested_char >= 'a' && requested_char <= 'z') {
                requested_char = requested_char - 32;
            }

            if (archive_char != requested_char) {
                break;
            }

            archive_char = archive_cursor[1];
            ++requested_cursor;
            ++archive_cursor;
        }

        if (*archive_cursor == 0 && *requested_cursor == 0) {
            goto found;
        }
    }

    ++entry_index;
    ++entry;
    if (entry_index < count) {
        goto scan_entry;
    }

not_found:
    return 0;

found:
    return &g_archive_index_records->entries[entry_index];
}
