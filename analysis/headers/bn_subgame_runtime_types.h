#ifndef BN_SUBGAME_RUNTIME_TYPES_H
#define BN_SUBGAME_RUNTIME_TYPES_H

typedef int int32_t;
typedef short int16_t;
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
    int16_t lateral_x;
    int16_t delta_z;
    uint8_t flags;
    uint8_t reserved_05;
} ReplayRunRecord;

typedef struct HighScoreRecord {
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
    char player_name[HIGH_SCORE_RECORD_PLAYER_NAME_SIZE];
    int32_t runtime_build_seed;
    int32_t replay_sample_count;
    ReplayRunRecord run_records[HIGH_SCORE_RUN_RECORD_COUNT];
    int32_t garbage_scalar_bits;
    int32_t salt_scalar_bits;
    int32_t unknown_1fab8;
    int32_t unknown_1fabc;
} HighScoreRecord;

typedef struct HighScoreBank {
    HighScoreRecord* active_record_bank;
    int32_t active_record_count;
    HighScoreRecord postal_records[HIGH_SCORE_TOP_TEN_STORAGE_COUNT];
    HighScoreRecord survival_records[HIGH_SCORE_TOP_TEN_STORAGE_COUNT];
    HighScoreRecord time_trial_route_records[HIGH_SCORE_TIME_TRIAL_ROUTE_COUNT];
    HighScoreRecord current_result_record;
    HighScoreRecord survival_pending_record;
} HighScoreBank;

typedef union RuntimeRateOrLevelArg {
    float base_rate;
    int32_t level_arg_tail;
} RuntimeRateOrLevelArg;

typedef union ChallengeDifficultyOrBits {
    float challenge_difficulty_scalar;
    int32_t difficulty_scalar_bits;
} ChallengeDifficultyOrBits;

typedef struct SubgameRuntime {
    uint8_t unknown_000000[0x02];
    uint8_t track_mirror_enabled;
    uint8_t unknown_000003;
    int32_t track_mirror_repeat_count;
    uint8_t unknown_000008;
    uint8_t subgame_pause_gate;
    uint8_t unknown_00000a[0x28 - 0x0a];
    int32_t completion_bonus_x_source;
    int32_t completion_bonus_y_source;
    RuntimeRateOrLevelArg rate_or_level_arg;
    ChallengeDifficultyOrBits challenge_difficulty;
    float subgame_rate;
    int32_t subgame_state;
    int32_t level_mode;
    int32_t level_mode_arg;
    float base_subgame_rate;
    uint32_t runtime_flags;
    int32_t first_block_row_count;
    int32_t runtime_row_count;
    int32_t completion_row_start;
    uint8_t unknown_00005c[0xa874 - 0x5c];
    int32_t level_segment_count;
    uint8_t unknown_00a878[0x1b0140 - 0xa878];
    float track_skirt_r;
    float track_skirt_g;
    float track_skirt_b;
    uint8_t unknown_1b014c[0x3bb764 - 0x1b014c];
    uint8_t score_stats_anchor;
    uint8_t unknown_3bb765[0x3bb7d4 - 0x3bb765];
    float completion_progress_z;
    uint8_t unknown_3bb7d8[0x3bba48 - 0x3bb7d8];
    int32_t source_score;
    ScoreBucketBlock source_stats;
    int32_t source_score_tail;
    int32_t source_tail;
    uint8_t unknown_3bba6c[0x3bbae4 - 0x3bba6c];
    int32_t parcel_sprite_owner;
    uint8_t unknown_3bbae8[0x3bbb28 - 0x3bbae8];
    int32_t bonus_rate_state;
    uint8_t unknown_3bbb2c[0x3bbb48 - 0x3bbb2c];
    float bonus_rate_phase;
    uint8_t unknown_3bbb4c[0x3bbba4 - 0x3bbb4c];
    uint8_t time_trial_route_active;
    uint8_t unknown_3bbba5[0x3bdec0 - 0x3bbba5];
    int32_t nuke_rate_state;
    uint8_t unknown_3bdec4[0x3be0c0 - 0x3bdec4];
    float nuke_rate_progress;
    uint8_t unknown_3be0c4[0x68b4c8 - 0x3be0c4];
    HighScoreBank high_score_bank;
    HighScoreRecord current_high_score_record;
    uint8_t selected_level_record_active;
    uint8_t selected_level_record_persistent;
    uint8_t unknown_ff25d2[0xff25d4 - 0xff25d2];
    void* selected_level_record;
    int32_t selected_level_record_cursor;
    int32_t replay_update_cursor;
    uint8_t unknown_ff25e0[0x125ffd8 - 0xff25e0];
    int32_t source_timer_a;
    int32_t source_timer_b;
} SubgameRuntime;

#endif
