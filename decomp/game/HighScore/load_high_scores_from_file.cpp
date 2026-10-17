// load_high_scores_from_file @ 0x4175e0 (thiscall, ret 0x4)

#include "rshell.h"
#include "sub_high_score.h"

void cRSubHighScore::load_high_scores_from_file(char* file_name)
{
    if (archive_or_file_exists(file_name, 1)) {
        int byte_count;
        char* cursor = load_file_bytes(file_name, &byte_count);
        char* end = cursor + byte_count;
        xor_decode_buffer_with_index(cursor, byte_count);

        while (cursor < end) {
            SubSolutionHeader* compact = (SubSolutionHeader*)cursor;
            switch (compact->bank_selector) {
            case 0:
                postal_records[compact->entry_index]
                    .Load(compact);
                break;
            case 1:
                survival_records[compact->entry_index]
                    .Load(compact);
                break;
            case 2:
                time_trial_route_records[compact->entry_index]
                    .Load(compact);
                break;
            }
            cursor += compact->byte_count;
        }
    }
}
