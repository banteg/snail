// initialize_high_score_tables @ 0x417540 (thiscall)

#include "high_score_bank.h"

void HighScoreBank::initialize_high_score_tables()
{
    int route_or_rank_index = 0;
    SubSolution* record = postal_records;
    do {
        record->initialize_high_score_entry(0, 0, 0x3f800000, 0, 0, route_or_rank_index);
        ++route_or_rank_index;
        ++record;
    } while (route_or_rank_index < HIGH_SCORE_TOP_TEN_STORAGE_COUNT);

    route_or_rank_index = 0;
    record = survival_records;
    do {
        record->initialize_high_score_entry(0, 0, 0x3f800000, 0, 1, route_or_rank_index);
        ++route_or_rank_index;
        ++record;
    } while (route_or_rank_index < HIGH_SCORE_TOP_TEN_STORAGE_COUNT);

    route_or_rank_index = 0;
    record = time_trial_route_records;
    do {
        record->initialize_high_score_entry(0, 0, 0x3f800000, 0, 2, route_or_rank_index);
        ++route_or_rank_index;
        ++record;
    } while (route_or_rank_index < HIGH_SCORE_TIME_TRIAL_ROUTE_COUNT);

    current_result_record.initialize_high_score_entry(0, 0, 0x3f800000, 0, 0, 0);
}
