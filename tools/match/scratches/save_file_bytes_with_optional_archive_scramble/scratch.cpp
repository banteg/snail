// save_file_bytes_with_optional_archive_scramble @ 0x4052a0 (cdecl)

typedef struct File File;

#ifdef __cplusplus
extern "C" {
#endif
File* __cdecl fopen(char* path, char* mode);
int __cdecl fclose(File* file);
unsigned int __cdecl fwrite(void* buffer, unsigned int element_size, unsigned int element_count, File* file);
char* __cdecl getcwd(char* buffer, int size);
#ifdef __cplusplus
}
#endif

int printf(char* format, ...);
void scramble_archive_bytes_in_place(char* bytes, int size);

int __cdecl save_file_bytes_with_optional_archive_scramble(char* file_name, void* bytes, int byte_count, char should_scramble)
{
    char current_directory[512];
    File* file;

    if (should_scramble != 0) {
        scramble_archive_bytes_in_place((char*)bytes, byte_count);
    }

    file = fopen(file_name, "wb");
    if (file == 0) {
        getcwd(current_directory, 512);
        return printf("ERROR:Cannot save file : %s (from %s)\n", file_name, current_directory);
    }

    printf("Saving file :%s %i bytes\n", file_name, byte_count);
    fwrite(bytes, 1, byte_count, file);
    return fclose(file);
}
