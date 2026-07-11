#ifndef IDA_HIGH_SCORE_BANK_TYPES_H
#define IDA_HIGH_SCORE_BANK_TYPES_H

typedef int int32_t;
typedef short int16_t;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

#define SUB_SOLUTION_STRIDE 0x1fac0
#define SUB_SOLUTION_PLAYER_NAME_SIZE 0x14
#define SUB_SOLUTION_RUN_RECORD_COUNT 21600
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
    int16_t lateral_x;
    int16_t delta_z;
    uint8_t flags;
    uint8_t reserved_05;
} ReplayRunRecord;

typedef struct SubSolution {
    int32_t active;
    int32_t score;
    ScoreOrTime score_or_time;
    int32_t score_tail;
    int32_t source_tail;
    int32_t replay_level_index;
    int32_t replay_mode_id;
    int32_t unknown_30;
    int32_t challenge_difficulty_scalar_bits;
    uint32_t runtime_build_flags;
    int32_t high_score_mode_tag;
    int32_t route_or_rank_index;
    int32_t replay_cursor;
    int32_t replay_speed_scalar_bits;
    int32_t challenge_speed_value;
    int32_t challenge_difficulty_value;
    char player_name[SUB_SOLUTION_PLAYER_NAME_SIZE];
    int32_t runtime_build_seed;
    int32_t replay_sample_count;
    ReplayRunRecord run_records[SUB_SOLUTION_RUN_RECORD_COUNT];
    float garbage_frequency;
    float salt_frequency;
    int32_t unknown_1fab8;
    int32_t unknown_1fabc;
} SubSolution;

typedef struct HighScoreBank {
    SubSolution* active_record_bank;
    int32_t active_record_count;
    SubSolution postal_records[HIGH_SCORE_TOP_TEN_STORAGE_COUNT];
    SubSolution survival_records[HIGH_SCORE_TOP_TEN_STORAGE_COUNT];
    SubSolution time_trial_route_records[HIGH_SCORE_TIME_TRIAL_ROUTE_COUNT];
    SubSolution current_result_record;
    SubSolution survival_pending_record;
} HighScoreBank;

#endif
