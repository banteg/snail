// Attachment-follow runtime structures, partial.
// Offsets per analysis/decompile/*/00420c40-*.c, 0042c770-*.c, 00420cb0-*.c.
// The shared FollowState instance lives at game+0x430100; the Player at
// game+0x42fd7c.
#ifndef TRACK_ATTACHMENT_H
#define TRACK_ATTACHMENT_H

#include "player.h"

struct AttachmentSample {            // stride 0xa8
    char unknown_00[0x14];
    float active;                    // +0x14, sample participates when > 0
    char unknown_18[0x30 - 0x18];
    Vector3 offset;                  // +0x30
    char unknown_3c[0x40 - 0x3c];
    float matrix[12];                // +0x40, local-frame rotation
    char unknown_70[0x8c - 0x70];
    float delta_length;              // +0x8c, segment length (the swept-entry
                                     // "depth limit" gate is z < this)
    char unknown_90[0x94 - 0x90];
    float rotation_scalar_94;        // +0x94
    float rotation_scalar_98;        // +0x98
    char unknown_9c[0xa8 - 0x9c];
};

struct TrackRowCell;

struct AttachmentPathTemplate {
    void try_enter_track_attachment_from_swept_motion(
        float px, float py, float pz,
        float sweep_x, float sweep_y, float sweep_z,
        TrackRowCell* cell); // @ 0x42c770

    char unknown_00[0x44];
    int sample_count;                // +0x44
    char unknown_48[0x54 - 0x48];
    int width_cells;                 // +0x54, integer half-span source
    char unknown_58[0x5c - 0x58];
    AttachmentSample* samples;       // +0x5c
    char unknown_60[0x98 - 0x60];
    float installed_heading_delta;   // +0x98
};

struct TrackRowCell {
    char unknown_00[0x10];
    Vector3 anchor_position;            // +0x10 (z at +0x18)
    char unknown_1c[0x38 - 0x1c];
    AttachmentPathTemplate* attachment_template_record; // +0x38

    int get_row_index(); // get_track_cell_row_index, thiscall
};

class FollowState {
public:
    AttachmentPathTemplate* begin_track_attachment_follow_state(
        TrackRowCell* source_cell, const Vector3* world_position, Player* player); // @ 0x420c40
    void update_track_attachment_follow_state(
        float rate, int* sample_index, Vector3* position); // @ 0x420cb0

    unsigned char active;        // +0x00
    char unknown_01[3];
    AttachmentPathTemplate* template_record; // +0x04
    TrackRowCell* source_cell;   // +0x08
    int sample_index;            // +0x0c
    float progress;              // +0x10
    float vertical_offset;       // +0x14
    Vector3 output_position;     // +0x18 (x/y zeroed by the swept entry)
    float orientation_a;         // +0x24 (exact a..e order pending boss match)
    float orientation_b;         // +0x28
    float orientation_c;         // +0x2c
    float orientation_d;         // +0x30
    float orientation_e;         // +0x34
    Player* player;              // +0x38
    char unknown_3c[0x90 - 0x3c];
    float squidge_scratch;       // +0x90
    float update_rate;           // +0x94
    char unknown_98;             // +0x98
    unsigned char live_flag;     // +0x99
};

// data_4df904: relocatable game-allocation base; structures below live at
// fixed VA offsets added to it. volatile: native code re-reads it around
// every store through derived pointers.
extern char* volatile g_game_base;
extern char g_row_heading_table[]; // 0x64118c, 61 dwords per row
extern char g_follow_state_block[]; // 0x430100
extern char g_player_block[];       // 0x42fd7c

#endif
