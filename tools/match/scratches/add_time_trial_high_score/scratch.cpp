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
        HighScoreRecord* route_record = &time_trial_route_records[route_index];
        if (record->total_seconds < route_record->total_seconds
            || route_record->total_seconds == 0.0f) {
            *route_record = *record;
            route_record->route_or_rank_index = route_index;
        }
    }
}
