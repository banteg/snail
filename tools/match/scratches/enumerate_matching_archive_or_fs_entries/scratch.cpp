// enumerate_matching_archive_or_fs_entries @ 0x431740 (cdecl, C mode)

#include "archive_index.h"

#include <direct.h>
#include <io.h>

extern int g_enumerated_entry_count; // data_503320

char ascii_upper_if_lowercase(char value);
void rstrcpy_checked_ascii(char* destination, char* source);
int set_current_directory_with_drive_fallback(char* path);

void __cdecl enumerate_matching_archive_or_fs_entries(
    char* directory, char* pattern, int* out_count, DirectoryEntryName* names)
{
    struct _finddata_t find_data;
    char original_directory[512];
    int entry_index;
    long handle;
    ArchiveIndex* archive_index;

    archive_index = g_archive_index_records;
    g_enumerated_entry_count = 0;

    if (archive_index != 0) {
        entry_index = 0;
        if (archive_index->count > 0) {
            int entry_offset = 0;
            do {
                char* directory_cursor = directory;
                char* archive_cursor = *(char**)((char*)archive_index + entry_offset + 4);

                while (*archive_cursor != 0) {
                    char directory_char = *directory_cursor;
                    if (directory_char == 0) {
                        break;
                    }

                    if (directory_char >= 'a' && directory_char <= 'z') {
                        directory_char = directory_char - 32;
                    }

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
                    char first_name_char = *basename;

                    if (first_name_char != 0) {
                        do {
                            char pattern_char = pattern[pattern_index];
                            char upper_name;
                            if (pattern_char == 0) {
                                break;
                            }

                            upper_name = ascii_upper_if_lowercase(basename[name_index]);
                            if (upper_name != ascii_upper_if_lowercase(pattern_char)) {
                                if (pattern[pattern_index] != '*') {
                                    break;
                                }
                            }

                            if (pattern[pattern_index] == '*'
                                && basename[name_index] == pattern[pattern_index + 1]) {
                                ++pattern_index;
                            }

                            ++name_index;
                            if (pattern[pattern_index] != '*') {
                                ++pattern_index;
                            }
                        } while (basename[name_index] != 0);
                    }

                    if (basename[name_index] == 0) {
                        rstrcpy_checked_ascii(names[g_enumerated_entry_count], basename);
                        g_enumerated_entry_count += 1;
                    }
                }

                entry_index += 1;
                entry_offset += sizeof(ArchiveEntry);
                archive_index = g_archive_index_records;
            } while (entry_index < archive_index->count);
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
        rstrcpy_checked_ascii(names[g_enumerated_entry_count], find_data.name);
        g_enumerated_entry_count += 1;

        while (_findnext(handle, &find_data) != -1) {
            rstrcpy_checked_ascii(names[g_enumerated_entry_count], find_data.name);
            g_enumerated_entry_count += 1;
        }
    }

    *out_count = g_enumerated_entry_count;
    _chdir(original_directory);
}
