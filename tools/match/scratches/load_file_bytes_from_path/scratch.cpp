// load_file_bytes_from_path @ 0x42f490 (cdecl)

typedef struct File File;

#ifdef __cplusplus
extern "C" {
#endif
File* __cdecl fopen(char* path, char* mode);
int __cdecl fclose(File* file);
unsigned int __cdecl fread(void* buffer, unsigned int element_size, unsigned int element_count, File* file);
void* __cdecl malloc(unsigned int size);
char* __cdecl getcwd(char* buffer, int size);
#ifdef __cplusplus
}
#endif

int printf(char* format, ...);
int get_stream_length_preserve_position(File* file);

char* __cdecl load_file_bytes_from_path(char* file_name, char* buffer, int* out_size, int byte_count)
{
    char current_directory[512];
    File* file;
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
