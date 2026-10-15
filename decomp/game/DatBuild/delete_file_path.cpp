// delete_file_path @ 0x405340 (cdecl)

#include <stdio.h>

void __cdecl delete_file_path(char* path)
{
    remove(path);
}
