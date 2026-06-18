// load_file_bytes_into_optional_buffer @ 0x4051d0 (cdecl)

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

char* __cdecl load_file_bytes_into_optional_buffer(char* file_name, char* buffer, int* out_size)
{
    char current_directory[512];
    File* file;
    int byte_count;
    char* bytes;

    file = fopen(file_name, "rb");
    if (file == 0) {
        getcwd(current_directory, 512);
        printf("WARNING:Cannot find file : %s (from %s)\n", file_name, current_directory);
        return 0;
    }

    byte_count = get_stream_length_preserve_position(file);
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
