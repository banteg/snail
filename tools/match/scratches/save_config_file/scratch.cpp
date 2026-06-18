// save_config_file @ 0x42f540 (cdecl)

struct File;

extern "C" File* __cdecl fopen(char* path, char* mode);
extern "C" int __cdecl fclose(File* file);
extern "C" unsigned int __cdecl fwrite(void* buffer, unsigned int element_size, unsigned int element_count, File* file);
extern "C" char* __cdecl getcwd(char* buffer, int size);

char* __cdecl save_config_file(char* file_name, void* bytes, int byte_count)
{
    char current_directory[512];

    File* file = fopen(file_name, "wb");
    if (file == 0) {
        return getcwd(current_directory, 512);
    }

    fwrite(bytes, 1, byte_count, file);
    return (char*)fclose(file);
}
