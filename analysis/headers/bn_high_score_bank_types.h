#ifndef BN_HIGH_SCORE_BANK_TYPES_H
#define BN_HIGH_SCORE_BANK_TYPES_H

typedef int int32_t;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

#define HIGH_SCORE_RECORD_STRIDE 0x1fac0
#define HIGH_SCORE_RECORD_PLAYER_NAME_SIZE 0x14
#define HIGH_SCORE_RUN_RECORD_COUNT 21600
#define HIGH_SCORE_TOP_TEN_STORAGE_COUNT 11
#define HIGH_SCORE_TIME_TRIAL_ROUTE_COUNT 51

typedef struct ScoreBucketBlock {
    int32_t values[6];
} ScoreBucketBlock;

typedef struct TimerCounters {
    float total_seconds;
    int32_t minutes;
    int32_t frames_into_second;
    int32_t display_hundredths;
    int32_t display_thousandths;
    float second_fraction;
} TimerCounters;

typedef union ScoreOrTime {
    float total_seconds;
    ScoreBucketBlock stats;
    TimerCounters timer;
} ScoreOrTime;

typedef struct ReplayRunRecord {
    uint8_t unknown_00[4];
    uint8_t flags;
    uint8_t unknown_05;
} ReplayRunRecord;

typedef struct HighScoreRecord {
    int32_t active;
    int32_t score;
    ScoreOrTime score_or_time;
    int32_t score_tail;
    int32_t source_tail;
    int32_t initial_level_mode_arg;
    int32_t level_mode;
    int32_t unknown_30;
    int32_t difficulty_scalar_bits;
    uint32_t runtime_flags_snapshot;
    int32_t high_score_mode_tag;
    int32_t route_or_rank_index;
    int32_t replay_cursor;
    int32_t level_arg_tail;
    int32_t completion_bonus_x_source;
    int32_t completion_bonus_y_source;
    char player_name[HIGH_SCORE_RECORD_PLAYER_NAME_SIZE];
    int32_t runtime_seed;
    int32_t completion_count;
    ReplayRunRecord run_records[HIGH_SCORE_RUN_RECORD_COUNT];
    int32_t timer_snapshot_a;
    int32_t timer_snapshot_b;
    uint8_t unknown_1fab8[HIGH_SCORE_RECORD_STRIDE - 0x1fab8];
} HighScoreRecord;

typedef struct HighScoreRecordView {
    HighScoreRecord* active_record_bank;
    int32_t active_record_count;
    uint8_t unknown_000008[0x17c108 - 0x08];
    HighScoreRecord name_submit_records[10];
} HighScoreRecordView;

typedef struct HighScoreBank {
    uint8_t unknown_000000[0x08];
    HighScoreRecord postal_records[HIGH_SCORE_TOP_TEN_STORAGE_COUNT];
    HighScoreRecord survival_records[HIGH_SCORE_TOP_TEN_STORAGE_COUNT];
    HighScoreRecord time_trial_route_records[HIGH_SCORE_TIME_TRIAL_ROUTE_COUNT];
    HighScoreRecord current_result_record;
    HighScoreRecord survival_pending_record;
} HighScoreBank;

#endif
