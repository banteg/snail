// load_file_bytes @ 0x431520 (cdecl)

#include "rshell.h"

void* load_file_bytes(char* file_name, int* out_size)
{
    return load_file_bytes_from_archive_or_fs(file_name, 0, out_size);
}
