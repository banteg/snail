// clean_duplicate_vertices @ 0x419f80 (thiscall)

#include "duplicate_vertices.h"

int DuplicateVertices::clean_duplicate_vertices(int unused)
{
    int result = active_count;

    for (int outer = 0; outer < result; ++outer) {
        for (int inner = outer; inner < active_count; ++inner) {
            if (records[inner].source_vertex == records[outer].compare_vertex) {
                records[inner].live_flag = 0;
            }
        }
        result = active_count;
    }

    return result;
}
