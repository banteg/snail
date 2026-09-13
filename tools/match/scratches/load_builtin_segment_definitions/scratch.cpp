// cRSubTracks::Init(cRSubSegmentRaw**) @ 0x448060 (thiscall, ret 0x4)

#include "sub_tracks.h"

// Keep the caller's row count while measuring the borrowed glyph string.
static __forceinline void measure_glyph_row(char* row, int& count)
{
    count = 0;
    if (*row != 0) {
        do {
            ++count;
        } while (row[count] != 0);
    }
}

void cRSubTracks::Init(
    cRSubSegmentRaw** raw_segments)
{
    SubSegment* slots = segment_slots;

    segment_count = 0;
    random_length = 1000;

    if (*raw_segments[0]->glyph_rows[0] != 0) {
        do {
            int slot_index = segment_count;
            int row_count;
            measure_glyph_row(raw_segments[slot_index]->glyph_rows[0], row_count);

            slots[slot_index].row_count = row_count;
            raw_segments[segment_count]->row_count = row_count;

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
            } while (row_index < 8);

            int active_slot = segment_count;
            slots[active_slot].source_name = raw_segments[active_slot]->source_name;

            active_slot = segment_count;
            slots[active_slot].path_index = raw_segments[active_slot]->path_index;

            ++segment_count;
        } while (*raw_segments[segment_count]->glyph_rows[0] != 0);
    }
}
