// enumerate_matching_archive_or_fs_entries @ 0x431740 (cdecl)

#include "archive_index.h"
#include "rshell.h"
#include "rstring.h"

#include <direct.h>
#include <io.h>

extern int g_enumerated_entry_count; // data_503320

void __cdecl enumerate_matching_archive_or_fs_entries(
    char* directory, char* pattern, int* out_count, DirectoryEntryName* names)
{
    struct _finddata_t find_data;
    char original_directory[512];
    long handle;

    g_enumerated_entry_count = 0;

    if (g_archive_index_records != 0) {
        for (int entry_index = 0; entry_index < g_archive_index_records->count;
             ++entry_index) {
            char* directory_cursor = directory;
            char* archive_cursor =
                g_archive_index_records->entries[entry_index].path;

            while (*archive_cursor != 0) {
                char directory_char = *directory_cursor;
                if (directory_char == 0) {
                    break;
                }

                directory_char = (char)fold_archive_request(directory_char);

                if (*archive_cursor != directory_char) {
                    break;
                }

                ++directory_cursor;
                ++archive_cursor;
            }

            if (*archive_cursor == '/' && *directory_cursor == 0) {
                char* basename = archive_cursor + 1;
                int name_index = 0;
                int pattern_index = 0;
                while (basename[name_index] != 0) {
                    char pattern_char = pattern[pattern_index];
                    if (pattern_char == 0) {
                        break;
                    }

                    char upper_name = RstrASC(basename[name_index]);
                    if (upper_name != RstrASC(pattern_char) && pattern[pattern_index] != '*') {
                        break;
                    }

                    if (pattern[pattern_index] == '*'
                        && basename[name_index] == pattern[pattern_index + 1]) {
                        ++pattern_index;
                    }

                    ++name_index;
                    if (pattern[pattern_index] != '*') {
                        ++pattern_index;
                    }
                }

                if (basename[name_index] == 0) {
                    Rstrcpy(names[g_enumerated_entry_count], basename);
                    g_enumerated_entry_count += 1;
                }
            }
        }

        *out_count = g_enumerated_entry_count;
        return;
    }

    _getcwd(original_directory, sizeof(original_directory));
    if (set_current_directory_with_drive_fallback(directory) == 1) {
        *out_count = g_enumerated_entry_count;
        return;
    }

    handle = _findfirst(pattern, &find_data);
    if (handle != -1) {
        Rstrcpy(names[g_enumerated_entry_count], find_data.name);
        g_enumerated_entry_count += 1;

        while (_findnext(handle, &find_data) != -1) {
            Rstrcpy(names[g_enumerated_entry_count], find_data.name);
            g_enumerated_entry_count += 1;
        }
    }

    *out_count = g_enumerated_entry_count;
    _chdir(original_directory);
}
