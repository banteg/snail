// load_file_bytes_from_archive_or_fs @ 0x4312d0 (cdecl)

#include <direct.h>

#include "archive_index.h"
#include "loading_bar.h"

int get_stream_length_preserve_position(FILE* file);
void* allocate_tracked_memory(int size, char* name);
void xor_archive_bytes_in_place(int start_offset, char* bytes, int count);
int report_messagef(char* format, ...);

char* __cdecl load_file_bytes_from_archive_or_fs(
    char* file_name, char* buffer, int* out_size)
{
    char current_directory[512];
    ArchiveIndex* archive_index;
    int count;
    int entry_index;
    char** entry_path;
    char* requested_path;
    FILE* file;
    int byte_count;
    char* result;
    char* allocated;

    g_loading_bar.update_loading_screen();

    requested_path = file_name;
    archive_index = g_archive_index_records;
    if (archive_index != 0) {
        count = archive_index->count;
        entry_index = 0;
        if (count > 0) {
            entry_path = &archive_index->entries[0].path;
            do {
                char* archive_cursor = *entry_path;
                char* request_cursor = requested_path;

                while (*archive_cursor != 0) {
                    char request_char = *request_cursor;
                    if (request_char == 0) {
                        break;
                    }

                    if (request_char >= 'a' && request_char <= 'z') {
                        request_char = request_char - 32;
                    }

                    if (*archive_cursor != request_char) {
                        break;
                    }

                    ++request_cursor;
                    ++archive_cursor;
                }

                if (*archive_cursor == 0 && *request_cursor == 0) {
                    goto found_archive_entry;
                }

                ++entry_index;
                entry_path += 3;
            } while (entry_index < count);
        }
    }

    file = fopen(requested_path, "rb");
    if (file == 0) {
        getcwd(current_directory, 512);
        report_messagef("WARNING:Cannot find file : %s (from %s)\n",
            requested_path, current_directory);
        return 0;
    }
    goto filesystem_success;

found_archive_entry:
    if (out_size != 0) {
        *out_size = g_archive_index_records->entries[entry_index].byte_count;
    }

    if (buffer == (char*)-1) {
        return (char*)g_archive_index_records->entries[entry_index].data_offset;
    }

    if (buffer == 0) {
        allocated = (char*)allocate_tracked_memory(
            g_archive_index_records->entries[entry_index].byte_count,
            requested_path);
        int current_offset = ftell(g_archive_file);
        fseek(g_archive_file,
            g_archive_index_records->entries[entry_index].data_offset - current_offset,
            SEEK_CUR);
        fread(allocated,
            1,
            g_archive_index_records->entries[entry_index].byte_count,
            g_archive_file);
        xor_archive_bytes_in_place(
            g_archive_index_records->entries[entry_index].data_offset,
            allocated,
            g_archive_index_records->entries[entry_index].byte_count);
        return allocated;
    } else {
        int current_offset = ftell(g_archive_file);
        fseek(g_archive_file,
            g_archive_index_records->entries[entry_index].data_offset - current_offset,
            SEEK_CUR);
        fread(buffer,
            1,
            g_archive_index_records->entries[entry_index].byte_count,
            g_archive_file);
        xor_archive_bytes_in_place(
            g_archive_index_records->entries[entry_index].data_offset,
            buffer,
            g_archive_index_records->entries[entry_index].byte_count);
        return buffer;
    }

filesystem_success:
    byte_count = get_stream_length_preserve_position(file);
    result = buffer;
    if (result == 0 || result == (char*)-1) {
        result = (char*)allocate_tracked_memory(byte_count, requested_path);
    }

    fread(result, 1, byte_count, file);
    fclose(file);

    if (out_size != 0) {
        *out_size = byte_count;
    }

    return result;
}
