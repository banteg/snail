/* load_archive_index @ 0x4319c0 (cdecl, C mode) */

#include "archive_index.h"

char archive_or_file_exists(char* path, char force_filesystem);
char* load_file_bytes_fixed_size_from_archive_or_fs(char* path, char* out_buffer, unsigned int byte_count);
void xor_archive_bytes_in_place(int start_offset, char* bytes, int count);
void* allocate_tracked_memory(int size, char* name);

char __cdecl load_archive_index(char* path)
{
    char header[0x7c];
    int byte_count;
    SerializedArchiveIndex* serialized_index;
    int i;

    g_archive_index_records = 0;
    if (archive_or_file_exists(path, 0) == 0) {
        g_archive_index_records = 0;
        return 1;
    }

    load_file_bytes_fixed_size_from_archive_or_fs(path, header, sizeof(header));
    xor_archive_bytes_in_place(0, header, sizeof(header));

    byte_count =
        ((SerializedArchiveIndex*)header)->entries[0].data_offset;
    serialized_index = (SerializedArchiveIndex*)allocate_tracked_memory(
        byte_count, "Dat File Header");

    load_file_bytes_fixed_size_from_archive_or_fs(
        path, (char*)serialized_index, byte_count);
    xor_archive_bytes_in_place(0, (char*)serialized_index, byte_count);
    g_archive_index_records = (ArchiveIndex*)serialized_index;

    i = 0;
    if (serialized_index->count > 0) {
        do {
            g_archive_index_records->entries[i].path +=
                (int)g_archive_index_records;
            ++i;
        } while (i < g_archive_index_records->count);
    }

    g_archive_file = fopen(path, "rb");
    return 1;
}
