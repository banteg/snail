// find_archive_entry @ 0x431250 (cdecl, ret)

#include "archive_index.h"

static __inline unsigned char fold_archive_request(char value)
{
    if (value >= 'a' && value <= 'z')
        return value - ('a' - 'A');
    return value;
}

ArchiveEntry* find_archive_entry(char* path)
{
    ArchiveIndex* index = g_archive_index_records;
    int count;
    int entry_index;
    char* requested_path;
    ArchiveEntry* entry;
    int found_entry = 0;

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

    do {
        char* requested_cursor = requested_path;
        char* archive_cursor = entry->path;
        while (*archive_cursor != 0) {
            char requested_char = *requested_cursor;
            if (requested_char == 0) {
                break;
            }

            requested_char = (char)fold_archive_request(requested_char);

            if (*archive_cursor != requested_char) {
                break;
            }

            ++requested_cursor;
            ++archive_cursor;
        }

        if (*archive_cursor == 0 && *requested_cursor == 0) {
            found_entry = 1;
            break;
        }
        ++entry_index;
        ++entry;
    } while (entry_index < count);

    if (found_entry == 0)
        goto not_found;
    return &g_archive_index_records->entries[entry_index];

not_found:
    return 0;
}
