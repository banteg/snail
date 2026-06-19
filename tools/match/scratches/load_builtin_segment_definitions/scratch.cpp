// load_builtin_segment_definitions @ 0x448060 (thiscall, ret 0x4)

#include "segment_catalog_types.h"

char* LevelSegmentSlotStore::load_builtin_segment_definitions(
    BuiltinSegmentDefinition** builtins)
{
    count = 0;
    slots[102].row_base = 1000;

    char* result = builtins[0]->glyph_rows[0];
    if (*result != 0) {
        do {
            int slot_index = count;
            char* first_row = builtins[slot_index]->glyph_rows[0];
            int row_count = 0;
            while (first_row[row_count] != 0)
                ++row_count;

            slots[slot_index].row_count = row_count;
            builtins[count]->row_count = row_count;

            int grid_offset = 0;
            int row_index = 0;
            do {
                int active_slot = count;
                int column = 0;
                char* source_row = builtins[active_slot]->glyph_rows[row_index];
                char glyph = *source_row;
                do {
                    int destination = 0x4220 * active_slot + grid_offset + column;
                    ++column;
                    *((char*)&slots[0] + destination + 0x14) = glyph;
                    active_slot = count;
                    source_row = builtins[active_slot]->glyph_rows[row_index];
                    glyph = source_row[column];
                } while (glyph != 0);
                ++row_index;
                grid_offset += 0x100;
            } while (row_index < 8);

            int active_slot = count;
            slots[active_slot].source_name = builtins[active_slot]->source_name;

            active_slot = count;
            slots[active_slot].path_index = builtins[active_slot]->path_index;

            int next_index = count + 1;
            count = next_index;
            result = builtins[next_index]->glyph_rows[0];
        } while (*result != 0);
    }

    return result;
}
