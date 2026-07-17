#ifndef IDA_HIGH_SCORE_BANK_TYPES_H
#define IDA_HIGH_SCORE_BANK_TYPES_H

typedef int int32_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

#define SUB_SOLUTION_STRIDE 0x1fac0
#define SUB_SOLUTION_PLAYER_NAME_SIZE 0x14
#define SUB_SOLUTION_RUN_RECORD_COUNT 21600
#define SUB_SOLUTION_HEADER_BYTES 0x88
#define SUB_HIGH_SCORE_TOP_TEN_STORAGE_COUNT 11
#define SUB_HIGH_SCORE_TIME_TRIAL_ROUTE_COUNT 51

typedef struct ScoreBucketBlock {
    int32_t values[6];
} ScoreBucketBlock;

typedef struct Time {
    float total_seconds;
    int32_t minutes;
    int32_t seconds;
    int32_t display_hundredths;
    int32_t display_thousandths;
    float second_fraction;
} Time;

typedef union ScoreOrTime {
    float total_seconds;
    ScoreBucketBlock stats;
    Time timer;
} ScoreOrTime;

typedef union SubSolutionScalar {
    int32_t bits;
    float value;
} SubSolutionScalar;

typedef struct ReplayRunRecord {
    int16_t lateral_x;
    int16_t delta_z;
    uint16_t flags;
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
    SubSolutionScalar challenge_difficulty_scalar;
    uint32_t runtime_build_flags;
    int32_t high_score_mode_tag;
    int32_t route_or_rank_index;
    int32_t replay_cursor;
    SubSolutionScalar replay_speed_scalar;
    int32_t challenge_speed_value;
    int32_t challenge_difficulty_value;
    char player_name[SUB_SOLUTION_PLAYER_NAME_SIZE];
    int32_t runtime_build_seed;
    int32_t replay_sample_count;
    ReplayRunRecord run_records[SUB_SOLUTION_RUN_RECORD_COUNT];
    SubSolutionScalar garbage_frequency;
    SubSolutionScalar salt_frequency;
    int32_t unknown_1fab8;
    int32_t unknown_1fabc;
} SubSolution;

/*
 * Stable 0x88-byte prefix of the variable-length cRSubSolutionHeader record.
 * The payload packs lateral int16s, delta-z int16s, then the low byte of each
 * expanded flags word; byte_count is therefore 0x88 + replay_sample_count * 5.
 */
typedef struct CompactHighScoreRecord {
    int32_t byte_count;
    int32_t score;
    ScoreOrTime score_or_time;
    int32_t score_tail;
    int32_t source_tail;
    int32_t checksum;
    int32_t replay_level_index;
    int32_t replay_mode_id;
    char reserved_34[0x4];
    uint32_t runtime_build_flags;
    int32_t bank_selector;
    int32_t entry_index;
    int32_t replay_cursor;
    SubSolutionScalar replay_speed_scalar;
    int32_t challenge_speed_value;
    int32_t challenge_difficulty_value;
    SubSolutionScalar challenge_difficulty_scalar;
    char reserved_58[0x4];
    char player_name[SUB_SOLUTION_PLAYER_NAME_SIZE];
    int32_t runtime_build_seed;
    int32_t replay_sample_count;
    SubSolutionScalar garbage_frequency;
    SubSolutionScalar salt_frequency;
    int32_t unknown_80;
    int32_t unknown_84;
    uint8_t replay_payload[1];
} CompactHighScoreRecord;

typedef struct SubHighScore {
    SubSolution* active_record_bank;
    int32_t active_record_count;
    SubSolution postal_records[SUB_HIGH_SCORE_TOP_TEN_STORAGE_COUNT];
    SubSolution survival_records[SUB_HIGH_SCORE_TOP_TEN_STORAGE_COUNT];
    SubSolution time_trial_route_records[SUB_HIGH_SCORE_TIME_TRIAL_ROUTE_COUNT];
    SubSolution current_result_record;
    SubSolution survival_pending_record;
} SubHighScore;

/* Analysis-only SubHighScore-relative view for AddArcade's native
 * `bank + rank * sizeof(SubSolution)` cursor. The prefix aliases the bank and
 * record aliases postal_records[rank]; this is not additional storage. */
typedef struct SubHighScorePostalRankCursor {
    uint8_t bank_prefix[0x8];
    SubSolution record;
} SubHighScorePostalRankCursor;

/* Analysis-only SubHighScore-relative view for AddSurvival's native
 * `bank + rank * sizeof(SubSolution)` cursor. The prefix aliases the bank and
 * record aliases survival_records[rank]; this is not additional storage. */
typedef struct SubHighScoreSurvivalRankCursor {
    uint8_t bank_prefix[0x15c648];
    SubSolution record;
} SubHighScoreSurvivalRankCursor;

/* Analysis-only SubHighScore-relative view for AddTimeTrial's native
 * `bank + route_index * sizeof(SubSolution)` cursor. The prefix aliases the
 * enclosing bank and record aliases time_trial_route_records[route_index];
 * this is not additional storage. */
typedef struct SubHighScoreTimeTrialRouteCursor {
    uint8_t bank_prefix[0x2b8c88];
    SubSolution record;
} SubHighScoreTimeTrialRouteCursor;

uint8_t __thiscall deserialize_compact_high_score_record(
    SubSolution* record,
    CompactHighScoreRecord* compact
);
int32_t __thiscall serialize_compact_high_score_record(
    SubSolution* record,
    CompactHighScoreRecord* compact
);

#endif
