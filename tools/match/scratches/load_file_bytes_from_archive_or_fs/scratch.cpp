// load_file_bytes_from_archive_or_fs @ 0x4312d0 (cdecl)

typedef struct File File;

typedef struct ArchiveEntry {
    char* path;      // +0x00
    int data_offset; // +0x04
    int byte_count;  // +0x08
} ArchiveEntry;

typedef struct ArchiveIndex {
    int count;               // +0x00
    ArchiveEntry entries[1]; // +0x04
} ArchiveIndex;

struct LoadingScreen {
    void update_loading_screen();
};

extern LoadingScreen g_loading_screen;      // data_503290
extern ArchiveIndex* g_archive_index_records; // data_53c7f8
extern File* g_archive_file;                // data_53c7f0

extern "C" {
File* __cdecl fopen(char* path, char* mode);
int __cdecl fclose(File* file);
int __cdecl fseek(File* file, int offset, int origin);
int __cdecl ftell(File* file);
unsigned int __cdecl fread(void* buffer, unsigned int element_size, unsigned int element_count, File* file);
char* __cdecl getcwd(char* buffer, int size);
}

int get_stream_length_preserve_position(File* file);
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
    File* file;
    int byte_count;
    char* result;
    int entry_offset;
    int count_offset;
    char* allocated;

    g_loading_screen.update_loading_screen();

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
                char archive_char = *archive_cursor;

                while (archive_char != 0) {
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

                    archive_char = archive_cursor[1];
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
        *out_size =
            *(int*)((char*)g_archive_index_records + ((entry_index * 3 + 3) << 2));
    }

    if (buffer == (char*)-1) {
        return (char*)*(int*)((char*)g_archive_index_records
            + (entry_index * sizeof(ArchiveEntry)) + 8);
    }

    if (buffer == 0) {
        count_offset = (entry_index * 3 + 3) << 2;
        entry_offset = entry_index * sizeof(ArchiveEntry);
        allocated = (char*)allocate_tracked_memory(
            *(int*)((char*)g_archive_index_records + count_offset),
            requested_path);
        fseek(g_archive_file,
            *(int*)((char*)g_archive_index_records + entry_offset + 8)
                - ftell(g_archive_file),
            1);
        fread(allocated,
            1,
            *(int*)((char*)g_archive_index_records + count_offset),
            g_archive_file);
        xor_archive_bytes_in_place(
            *(int*)((char*)g_archive_index_records + entry_offset + 8),
            allocated,
            *(int*)((char*)g_archive_index_records + count_offset));
        return allocated;
    } else {
        entry_offset = entry_index * sizeof(ArchiveEntry);
        count_offset = (entry_index * 3 + 3) << 2;
        fseek(g_archive_file,
            *(int*)((char*)g_archive_index_records + entry_offset + 8)
                - ftell(g_archive_file),
            1);
        fread(buffer,
            1,
            *(int*)((char*)g_archive_index_records + count_offset),
            g_archive_file);
        xor_archive_bytes_in_place(
            *(int*)((char*)g_archive_index_records + entry_offset + 8),
            buffer,
            *(int*)((char*)g_archive_index_records + count_offset));
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
