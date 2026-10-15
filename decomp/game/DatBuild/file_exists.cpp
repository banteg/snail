// file_exists @ 0x405140 (cdecl)

#include <stdio.h>

char __cdecl file_exists(char* path)
{
    FILE* file = fopen(path, "rb");
    if (file == 0) {
        return 0;
    }
    fclose(file);
    return 1;
}
