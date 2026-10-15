// get_archive_data_end @ 0x431aa0

#include "archive_index.h"
#include "rshell.h"

void* get_archive_data_end()
{
    return (char*)g_archive_data_base + RSHELL_SCRATCH_REGION_SIZE;
}
