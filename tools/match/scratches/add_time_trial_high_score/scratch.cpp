// add_time_trial_high_score @ 0x4178b0 (thiscall, ret 0xc)

#include "high_score_bank.h"

void HighScoreBank::add_time_trial_high_score(
    HighScoreRecord* record,
    int route_index,
    unsigned char route_active)
{
    record->high_score_mode_tag = 2;
    record->route_or_rank_index = route_index;
    record->replay_cursor = 0;
    if (!route_active) {
        record->total_seconds = 0.0f;
    }

    current_result_record = *record;

    if (route_active) {
        int route_offset = route_index * HIGH_SCORE_RECORD_STRIDE;
        if (record->total_seconds
                < *(float*)((char*)this + route_offset + 0x2b8c90)
            || *(float*)((char*)this + route_offset + 0x2b8c90) == 0.0f) {
            HighScoreRecord* route_record =
                (HighScoreRecord*)((char*)this + route_offset + 0x2b8c88);
            *route_record = *record;
            route_record->route_or_rank_index = route_index;
        }
    }
}
