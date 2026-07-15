// load_file_bytes_fixed_size_from_archive_or_fs @ 0x431030 (cdecl)

#include <direct.h>

#include "archive_index.h"
#include "loading_bar.h"

int get_stream_length_preserve_position(FILE* file);
void* allocate_tracked_memory(int size, char* name);
void xor_archive_bytes_in_place(int start_offset, char* bytes, int count);
int report_messagef(char* format, ...);

char* __cdecl load_file_bytes_fixed_size_from_archive_or_fs(
    char* file_name, char* buffer, int byte_count)
{
    char current_directory[512];
    ArchiveIndex* archive_index;
    int count;
    int entry_index;
    char** entry_path;
    FILE* file;
    char* result;

    g_loading_bar.update_loading_screen();

    archive_index = g_archive_index_records;
    if (archive_index != 0) {
        count = archive_index->count;
        entry_index = 0;
        if (count > 0) {
            entry_path = &archive_index->entries[0].path;
            do {
                char* archive_cursor = *entry_path;
                char* request_cursor = file_name;

                while (*archive_cursor != 0) {
                    char archive_char = *archive_cursor;
                    char request_char = *request_cursor;
                    if (request_char == 0) {
                        break;
                    }

                    if (request_char >= 'a' && request_char <= 'z') {
                        request_char = request_char - 32;
                    }

                    if (archive_char != request_char) {
                        break;
                    }

                    ++request_cursor;
                    ++archive_cursor;
                }

                if (*archive_cursor == 0 && *request_cursor == 0) {
                    if (buffer == (char*)-1) {
                        return (char*)g_archive_index_records->entries[entry_index].data_offset;
                    }

                    if (buffer == 0) {
                        char* allocated = (char*)allocate_tracked_memory(byte_count, file_name);
                        int current_offset = ftell(g_archive_file);
                        fseek(g_archive_file,
                            g_archive_index_records->entries[entry_index].data_offset
                                - current_offset,
                            SEEK_CUR);
                        fread(allocated, 1, byte_count, g_archive_file);
                        xor_archive_bytes_in_place(
                            g_archive_index_records->entries[entry_index].data_offset,
                            allocated,
                            byte_count);
                        return allocated;
                    } else {
                        int current_offset = ftell(g_archive_file);
                        fseek(g_archive_file,
                            g_archive_index_records->entries[entry_index].data_offset
                                - current_offset,
                            SEEK_CUR);
                        fread(buffer, 1, byte_count, g_archive_file);
                        xor_archive_bytes_in_place(
                            g_archive_index_records->entries[entry_index].data_offset,
                            buffer,
                            byte_count);
                        return buffer;
                    }
                }

                ++entry_index;
                entry_path += 3;
            } while (entry_index < count);
        }
    }

    file = fopen(file_name, "rb");
    if (file == 0) {
        getcwd(current_directory, 512);
        report_messagef("WARNING:Cannot find file : %s (from %s)\n",
            file_name, current_directory);
        return 0;
    }

    get_stream_length_preserve_position(file);
    result = buffer;
    if (result == 0 || result == (char*)-1) {
        result = (char*)allocate_tracked_memory(byte_count, file_name);
    }

    fread(result, 1, byte_count, file);
    fclose(file);
    return result;
}
