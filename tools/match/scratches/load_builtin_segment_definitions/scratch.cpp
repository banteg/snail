// load_builtin_segment_definitions @ 0x448060 (thiscall, ret 0x4)

#include "sub_tracks.h"

void SubTracks::load_builtin_segment_definitions(
    SubSegmentRaw** raw_segments)
{
    SubSegment* slots = segment_slots;

    segment_count = 0;
    random_length = 1000;

    if (*raw_segments[0]->glyph_rows[0] != 0) {
        do {
            int slot_index = segment_count;
            char* first_row = raw_segments[slot_index]->glyph_rows[0];
            int row_count = 0;
            if (*first_row != 0) {
                do {
                    ++row_count;
                } while (first_row[row_count] != 0);
            }

            slots[slot_index].row_count = row_count;
            raw_segments[segment_count]->row_count = row_count;

            int grid_offset = 0;
            int row_index = 0;
            do {
                int active_slot = segment_count;
                int column = 0;
                do {
                    slots[active_slot].glyph_rows[row_index][column] =
                        raw_segments[active_slot]->glyph_rows[row_index][column];
                    ++column;
                    active_slot = segment_count;
                } while (raw_segments[active_slot]->glyph_rows[row_index][column] != 0);
                ++row_index;
                grid_offset += 0x100;
            } while (row_index < 8);

            int active_slot = segment_count;
            slots[active_slot].source_name = raw_segments[active_slot]->source_name;

            active_slot = segment_count;
            slots[active_slot].path_index = raw_segments[active_slot]->path_index;

            ++segment_count;
        } while (*raw_segments[segment_count]->glyph_rows[0] != 0);
    }
}
