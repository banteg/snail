// Golb (player shot) path-follow structures, partial.
// Offsets per analysis/decompile/*/00421770-*.c and 00415e30-*.c
#ifndef GOLB_H
#define GOLB_H

#include "vector3.h"

// stride 0x18 sample bank entry; only the position triple is typed so far
struct GolbPathSample {
    float unknown_00;
    float x; // +0x04
    float y; // +0x08
    float z; // +0x0c
    float unknown_10;
    float unknown_14;
};

class GolbPathBank {
public:
    void initialize_enemy_manager(); // @ 0x415e20
    GolbPathSample* search_path_for_golb(const Vector3* position); // @ 0x415e30

    int count;                  // +0x00
    GolbPathSample samples[1];  // +0x04
};

struct AttachmentSampleMatrixView;

// Attachment path template fields touched by Golb path-follow helpers.
struct GolbPathTemplate {
    char unknown_00[0x38];
    int kind;                         // +0x38
    unsigned char is_mirrored_x;      // +0x3c
    char unknown_3d[0x40 - 0x3d];
    int side_exit_mode;               // +0x40
    int segment_count;                // +0x44
    char unknown_48[0x50 - 0x48];
    float width_or_scale;             // +0x50
    int width_cells;                  // +0x54
    AttachmentSampleMatrixView* primary_samples;   // +0x58
    AttachmentSampleMatrixView* secondary_samples; // +0x5c
};

struct GolbPathSourceCell {
    char unknown_00[0x10];
    Vector3 anchor_position; // +0x10
    char unknown_1c[0x38 - 0x1c];
    GolbPathTemplate* path_template; // +0x38
};

struct GolbShot;

class GolbPathFollowState {
public:
    int initialize_path_follow_golb(
        GolbPathSourceCell* source_cell,
        const Vector3* position,
        GolbShot* shot_); // @ 0x421770
    int calc_path_length_z(float path_factor, Vector3* position, Vector3* velocity); // @ 0x4217b0

    unsigned char active;     // +0x00
    char unknown_01[3];
    GolbPathTemplate* template_record; // +0x04
    GolbPathSourceCell* source_cell;   // +0x08
    int sample_index;          // +0x0c
    float progress;            // +0x10
    float vertical_offset;     // +0x14
    Vector3 output_position;   // +0x18
    GolbShot* shot;            // +0x24
};

#endif
