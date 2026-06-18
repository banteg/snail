#ifndef BN_SELECTED_LEVEL_RECORD_TYPES_H
#define BN_SELECTED_LEVEL_RECORD_TYPES_H

/*
 * Narrow Binary Ninja type-import slice for the selected replay/high-score
 * entry consumed by update_subgoldy, initialize_subgame, and update_subgame.
 */

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef int int32_t;
typedef short int16_t;

typedef struct Vec4 {
    float x;
    float y;
    float z;
    float w;
} Vec4;

typedef struct TransformMatrix {
    Vec4 basis_right;
    Vec4 basis_up;
    Vec4 basis_forward;
    Vec4 position;
} TransformMatrix;

typedef struct SelectedLevelReplaySample {
    int16_t lateral_x;
    int16_t delta_z;
    uint8_t flags;
    uint8_t _pad_05;
} SelectedLevelReplaySample;

typedef struct SelectedLevelRecord {
    uint32_t active;
    uint32_t score;
    uint8_t _pad_08[0x20];
    uint32_t replay_level_index;
    uint32_t replay_mode_id;
    uint8_t _pad_30[0x08];
    uint32_t runtime_build_flags;
    uint8_t _pad_3c[0x0c];
    float replay_speed_scalar;
    uint32_t challenge_speed_value;
    uint32_t challenge_difficulty_value;
    char name[0x14];
    uint32_t runtime_build_seed;
    uint32_t replay_sample_count;
    SelectedLevelReplaySample replay_samples[1];
} SelectedLevelRecord;

#endif
