// find_segment_path_index_by_name @ 0x429ae0 (thiscall, ret 0x4)

#include "path_manager.h"

int strings_equal_case_insensitive_path(char* left, char* right);

extern char* g_segment_path_name_0; // data_4a3d6c
extern char g_segment_path_names_end[]; // data_4a3e68 / "TOADPAIR1"

int PathManager::find_segment_path_index_by_name(char* name)
{
    int index = 0;
    char** cursor = &g_segment_path_name_0;
    while ((int)cursor < (int)g_segment_path_names_end) {
        if (strings_equal_case_insensitive_path(name, *cursor))
            return index;
        ++cursor;
        ++index;
    }
    return -1;
}
