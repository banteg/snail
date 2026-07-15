// save_config_file @ 0x42f540 (cdecl)

#include <direct.h>
#include <stdio.h>

char* __cdecl save_config_file(char* file_name, void* bytes, int byte_count)
{
    char current_directory[512];

    FILE* file = fopen(file_name, "wb");
    if (file == 0) {
        return getcwd(current_directory, 512);
    }

    fwrite(bytes, 1, byte_count, file);
    return (char*)fclose(file);
}
