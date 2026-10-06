// is_archive_index_loaded @ 0x431a80 (cdecl, ret)

#include "archive_index.h"

char is_archive_index_loaded()
{
    char result = g_archive_index_records != 0;
    return result;
}
