// load_file_bytes_from_path @ 0x42f490 (cdecl)

#include <direct.h>
#include <stdio.h>
#include <stdlib.h>

int get_stream_length_preserve_position(FILE* file);

char* __cdecl load_file_bytes_from_path(char* file_name, char* buffer, int* out_size, int byte_count)
{
    char current_directory[512];
    FILE* file;
    char* bytes;

    file = fopen(file_name, "rb");
    if (file == 0) {
        getcwd(current_directory, 512);
        printf("WARNING:Cannot find file : %s (from %s)\n", file_name, current_directory);
        return 0;
    }

    if (byte_count == 0) {
        byte_count = get_stream_length_preserve_position(file);
    }

    bytes = buffer;
    if (bytes == 0) {
        bytes = (char*)malloc(byte_count);
    }

    fread(bytes, 1, byte_count, file);
    fclose(file);
    if (out_size != 0) {
        *out_size = byte_count;
    }

    return bytes;
}
