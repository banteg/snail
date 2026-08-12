// find_segment_path_index_by_name @ 0x429ae0 (thiscall, ret 0x4)

#include "path_manager.h"
#include "rstring.h"

extern char* g_segment_path_name_0; // data_4a3d6c
extern char g_segment_path_names_end[]; // data_4a3e68 / "TOADPAIR1"

int cRPathManager::NameCode(char* name)
{
    int index = 0;
    char** cursor = &g_segment_path_name_0;
    // The shipped bound spans 63 slots, but only 51 are populated. An unknown
    // name reaches a null tail slot before the nominal -1 exit.
    while ((int)cursor < (int)g_segment_path_names_end) {
        if (strings_equal_case_insensitive_path(name, *cursor))
            return index;
        ++cursor;
        ++index;
    }
    return -1;
}
