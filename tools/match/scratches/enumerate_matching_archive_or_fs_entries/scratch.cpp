// enumerate_matching_archive_or_fs_entries @ 0x431740 (cdecl, C mode)

#include "archive_index.h"

typedef struct FindData {
    unsigned int attrib; // +0x00
    int time_create;     // +0x04
    int time_access;     // +0x08
    int time_write;      // +0x0c
    int size;            // +0x10
    char name[260];      // +0x14
} FindData;

extern int g_enumerated_entry_count; // data_503320

char* __cdecl getcwd(char* buffer, int size);
int __cdecl chdir(char* path);
int __cdecl findfirst(char* pattern, FindData* data);
int __cdecl findnext(int handle, FindData* data);

char ascii_upper_if_lowercase(char value);
void rstrcpy_checked_ascii(char* destination, char* source);
int set_current_directory_with_drive_fallback(char* path);

void __cdecl enumerate_matching_archive_or_fs_entries(
    char* directory, char* pattern, int* out_count, char* names)
{
    FindData find_data;
    char original_directory[512];
    int entry_index;
    int entry_offset;
    int handle;
    ArchiveIndex* archive_index;

    archive_index = g_archive_index_records;
    g_enumerated_entry_count = 0;

    if (archive_index != 0) {
        entry_index = 0;
        entry_offset = 0;
        if (archive_index->count > 0) {
            do {
                char* archive_cursor = *(char**)((char*)archive_index + entry_offset + 4);
                char* directory_cursor = directory;
                char archive_char = *archive_cursor;

                while (archive_char != 0) {
                    char directory_char = *directory_cursor;
                    if (directory_char == 0) {
                        break;
                    }

                    if (directory_char >= 'a' && directory_char <= 'z') {
                        directory_char = directory_char - 32;
                    }

                    if (archive_char != directory_char) {
                        break;
                    }

                    archive_char = archive_cursor[1];
                    ++directory_cursor;
                    ++archive_cursor;
                }

                if (*archive_cursor == '/' && *directory_cursor == 0) {
                    char* basename = archive_cursor + 1;
                    int pattern_index = 0;
                    int name_index = 0;
                    char first_name_char = *basename;

                    if (first_name_char != 0) {
                        do {
                            char pattern_char = pattern[pattern_index];
                            char upper_name;
                            char upper_pattern;
                            if (pattern_char == 0) {
                                break;
                            }

                            upper_name = ascii_upper_if_lowercase(basename[name_index]);
                            upper_pattern = ascii_upper_if_lowercase(pattern_char);
                            if (upper_name != upper_pattern) {
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
                        rstrcpy_checked_ascii(
                            names + (g_enumerated_entry_count << 7), basename);
                        g_enumerated_entry_count += 1;
                    }
                }

                entry_index += 1;
                entry_offset += sizeof(ArchiveEntry);
            } while (entry_index < archive_index->count);
        }

        *out_count = g_enumerated_entry_count;
        return;
    }

    getcwd(original_directory, sizeof(original_directory));
    if (set_current_directory_with_drive_fallback(directory) == 1) {
        *out_count = g_enumerated_entry_count;
        return;
    }

    handle = findfirst(pattern, &find_data);
    if (handle != -1) {
        rstrcpy_checked_ascii(names + (g_enumerated_entry_count << 7), find_data.name);
        g_enumerated_entry_count += 1;

        while (findnext(handle, &find_data) != -1) {
            rstrcpy_checked_ascii(names + (g_enumerated_entry_count << 7), find_data.name);
            g_enumerated_entry_count += 1;
        }
    }

    *out_count = g_enumerated_entry_count;
    chdir(original_directory);
}
