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
        char* route_bank_base = (char*)this;
        route_bank_base += route_index * HIGH_SCORE_RECORD_STRIDE;
        float* stored_seconds = (float*)(route_bank_base + 0x2b8c90);
        if (record->total_seconds < *stored_seconds
            || *stored_seconds == 0.0f) {
            HighScoreRecord* route_record =
                (HighScoreRecord*)(route_bank_base + 0x2b8c88);
            *route_record = *record;
            route_record->route_or_rank_index = route_index;
        }
    }
}
