// Shared high-score bank layout.
#ifndef HIGH_SCORE_BANK_H
#define HIGH_SCORE_BANK_H

#include "high_score_record.h"

const int HIGH_SCORE_TOP_TEN_COUNT = 10;
const int HIGH_SCORE_TOP_TEN_STORAGE_COUNT = HIGH_SCORE_TOP_TEN_COUNT + 1;
const int HIGH_SCORE_TIME_TRIAL_ROUTE_COUNT = 51;

class HighScoreBank {
public:
    void initialize_high_score_tables(); // @ 0x417540
    void load_high_scores_from_file(char* file_name); // @ 0x4175e0
    int add_arcade_high_score(HighScoreRecord* record, int level_arg); // @ 0x4176a0
    int add_survival_high_score(HighScoreRecord* record); // @ 0x417780
    void add_time_trial_high_score(
        HighScoreRecord* record,
        int route_index,
        unsigned char route_active); // @ 0x4178b0
    char* save_high_scores_and_config(unsigned char save_mask); // @ 0x417940

    char unknown_000000[0x08];
    HighScoreRecord postal_records[HIGH_SCORE_TOP_TEN_STORAGE_COUNT]; // +0x08
    HighScoreRecord survival_records[HIGH_SCORE_TOP_TEN_STORAGE_COUNT]; // +0x15c648
    HighScoreRecord time_trial_route_records[HIGH_SCORE_TIME_TRIAL_ROUTE_COUNT]; // +0x2b8c88
    HighScoreRecord current_result_record; // +0x9080c8
    HighScoreRecord survival_pending_record; // +0x927b88
};

typedef char HighScoreBank_must_be_0x947648[
    (sizeof(HighScoreBank) == 0x947648) ? 1 : -1];

#endif
