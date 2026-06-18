// Shared high-score/replay record prefix and stride.
#ifndef HIGH_SCORE_RECORD_H
#define HIGH_SCORE_RECORD_H

#include "score_stats.h"
#include "timer_counters.h"

const int HIGH_SCORE_RECORD_STRIDE = 0x1fac0;
const int HIGH_SCORE_RECORD_PLAYER_NAME_SIZE = 0x14;

struct ScoreBucketBlock {
    int values[SUBGOLDY_SCORE_BUCKET_COUNT];
};

struct ReplayRunRecord {
    char unknown_00[4];
    unsigned char flags; // +0x04
    char unknown_05;
};

typedef char ReplayRunRecord_must_be_0x06[
    (sizeof(ReplayRunRecord) == 0x06) ? 1 : -1];

const int HIGH_SCORE_RUN_RECORD_COUNT = 21600;
const int HIGH_SCORE_RUN_RECORD_BYTES =
    HIGH_SCORE_RUN_RECORD_COUNT * sizeof(ReplayRunRecord);

class HighScoreRecord {
public:
    void initialize_high_score_entry(
        int runtime_seed,
        int initial_level_mode_arg,
        int level_arg_tail_value,
        unsigned int runtime_flags_snapshot,
        int high_score_mode_tag,
        int route_or_rank_index); // @ 0x417a70

    int active; // +0x00
    int score; // +0x04
    union {
        float total_seconds; // +0x08, time-trial ordering key
        ScoreBucketBlock stats; // +0x08
        TimerCounters timer; // +0x08
    };
    int score_tail; // +0x20
    int source_tail; // +0x24
    int initial_level_mode_arg; // +0x28, captured when the run record is seeded
    int level_mode; // +0x2c, copied to the subgame launch mode
    int unknown_30; // +0x30
    int difficulty_scalar_bits; // +0x34, raw challenge-difficulty snapshot
    unsigned int runtime_flags_snapshot; // +0x38
    int high_score_mode_tag; // +0x3c, set by add_*_high_score
    int route_or_rank_index; // +0x40, level/route arg before insert or top-ten rank
    int replay_cursor; // +0x44, cleared before persistence
    int level_arg_tail; // +0x48
    int completion_bonus_x_source; // +0x4c
    int completion_bonus_y_source; // +0x50
    char player_name[HIGH_SCORE_RECORD_PLAYER_NAME_SIZE]; // +0x54
    int runtime_seed; // +0x68
    int completion_count; // +0x6c
    ReplayRunRecord run_records[HIGH_SCORE_RUN_RECORD_COUNT]; // +0x70
    int timer_snapshot_a; // +0x1fab0
    int timer_snapshot_b; // +0x1fab4
    char unknown_1fab8[HIGH_SCORE_RECORD_STRIDE - 0x1fab8];
};

typedef char HighScoreRecord_must_be_0x1fac0[
    (sizeof(HighScoreRecord) == HIGH_SCORE_RECORD_STRIDE) ? 1 : -1];

#endif
