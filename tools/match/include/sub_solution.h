// Authored cRSubSolution replay/high-score entry and its compact persistence
// header. The 0x1fac0-byte object is owned by cRSubHighScore banks and by the
// active SubgameRuntime run snapshot.
#ifndef SUB_SOLUTION_H
#define SUB_SOLUTION_H

#include "score_buckets.h"
#include "game_time.h"

const int SUB_SOLUTION_STRIDE = 0x1fac0;
const int SUB_SOLUTION_PLAYER_NAME_SIZE = 0x14;
const int SUB_SOLUTION_HEADER_BYTES = 0x88;
const int SUB_SOLUTION_CHECKSUM_MASK = 0xdeadbabe;

struct ScoreBucketBlock {
    int values[SUBGOLDY_SCORE_BUCKET_COUNT];
};

struct ReplayRunRecord {
    short lateral_x; // +0x00
    short delta_z; // +0x02, fixed-point z delta scaled by 32.0
    unsigned short flags; // +0x04, compact persistence stores the low byte only
};

typedef char ReplayRunRecord_must_be_0x06[
    (sizeof(ReplayRunRecord) == 0x06) ? 1 : -1];

const int SUB_SOLUTION_RUN_RECORD_COUNT = 21600;
const int SUB_SOLUTION_RUN_RECORD_BYTES =
    SUB_SOLUTION_RUN_RECORD_COUNT * sizeof(ReplayRunRecord);

struct SubSolutionHeader {
    int byte_count; // +0x00
    int score; // +0x04
    union {
        char score_payload[0x18]; // +0x08
        ScoreBucketBlock stats; // +0x08
        Time timer; // +0x08, authored cRTime value
    };
    int score_tail; // +0x20
    int source_tail; // +0x24
    int checksum; // +0x28
    int replay_level_index; // +0x2c
    int replay_mode_id; // +0x30
    char reserved_34[0x38 - 0x34];
    unsigned int runtime_build_flags; // +0x38
    int bank_selector; // +0x3c
    int entry_index; // +0x40
    int replay_cursor; // +0x44
    union {
        int replay_speed_scalar_bits; // +0x48
        float replay_speed_scalar; // +0x48
    };
    int challenge_speed_value; // +0x4c
    int challenge_difficulty_value; // +0x50
    union {
        int challenge_difficulty_scalar_bits; // +0x54
        float challenge_difficulty_scalar; // +0x54
    };
    char reserved_58[0x5c - 0x58];
    char player_name[SUB_SOLUTION_PLAYER_NAME_SIZE]; // +0x5c
    int runtime_build_seed; // +0x70
    int replay_sample_count; // +0x74
    union {
        int garbage_frequency_bits; // +0x78
        float garbage_frequency; // +0x78
    };
    union {
        int salt_frequency_bits; // +0x7c
        float salt_frequency; // +0x7c
    };
    int unknown_80; // +0x80
    int unknown_84; // +0x84
    char replay_payload[1]; // +0x88, variable: int16 lateral_x, int16 delta_z, byte flags

    short* lateral_samples()
    {
        return (short*)replay_payload;
    }

    short* delta_z_samples(int sample_count)
    {
        return (short*)(replay_payload + sample_count * sizeof(short));
    }

    unsigned char* flag_samples(int sample_count)
    {
        return (unsigned char*)(replay_payload + sample_count * 4);
    }
};

class SubSolution {
public:
    void initialize_high_score_entry(
        int runtime_build_seed,
        int replay_level_index,
        int replay_speed_scalar_bits,
        unsigned int runtime_build_flags,
        int high_score_mode_tag,
        int route_or_rank_index); // @ 0x417a70, cRSubSolution::ReSet
    unsigned char deserialize_compact_high_score_record(
        SubSolutionHeader* compact); // @ 0x440020, cRSubSolution::Load
    int serialize_compact_high_score_record(
        SubSolutionHeader* compact); // @ 0x440170, cRSubSolution::Save

    int active; // +0x00
    int score; // +0x04
    union {
        float total_seconds; // +0x08, time-trial ordering key
        ScoreBucketBlock stats; // +0x08
        Time timer; // +0x08, authored cRTime value
    };
    int score_tail; // +0x20
    int source_tail; // +0x24
    int replay_level_index; // +0x28
    int replay_mode_id; // +0x2c, copied to the subgame launch mode
    int unknown_30; // +0x30
    union {
        int challenge_difficulty_scalar_bits; // +0x34
        float challenge_difficulty_scalar; // +0x34
    };
    unsigned int runtime_build_flags; // +0x38
    int high_score_mode_tag; // +0x3c, set by add_*_high_score
    int route_or_rank_index; // +0x40, level/route arg before insert or top-ten rank
    int replay_cursor; // +0x44, cleared before persistence
    union {
        int replay_speed_scalar_bits; // +0x48
        float replay_speed_scalar; // +0x48
    };
    int challenge_speed_value; // +0x4c
    int challenge_difficulty_value; // +0x50
    char player_name[SUB_SOLUTION_PLAYER_NAME_SIZE]; // +0x54
    int runtime_build_seed; // +0x68
    int replay_sample_count; // +0x6c
    ReplayRunRecord run_records[SUB_SOLUTION_RUN_RECORD_COUNT]; // +0x70
    union {
        int garbage_frequency_bits; // +0x1fab0
        float garbage_frequency; // +0x1fab0
    };
    union {
        int salt_frequency_bits; // +0x1fab4
        float salt_frequency; // +0x1fab4
    };
    int unknown_1fab8; // +0x1fab8
    int unknown_1fabc; // +0x1fabc
};

typedef char SubSolution_must_be_0x1fac0[
    (sizeof(SubSolution) == SUB_SOLUTION_STRIDE) ? 1 : -1];

#endif
