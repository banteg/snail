// get_archive_data_end @ 0x431aa0

extern void* g_archive_data_base; // data_53c7ec / RShellScratch

void* get_archive_data_end()
{
    return (char*)g_archive_data_base + 0x200000;
}
