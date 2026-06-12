// is_archive_index_loaded @ 0x431a80 (cdecl, ret)

extern int g_archive_index_records; // data_53c7f8

char is_archive_index_loaded()
{
    char result = g_archive_index_records != 0;
    return result;
}
