// Attachment-follow runtime structures, partial.
// Offsets per analysis/decompile/*/00420c40-*.c, 0042c770-*.c, 00420cb0-*.c.
// UNIFIED (2026-06-12): the "FollowState global at game+0x430100" is the
// Player's embedded follow sub-struct at player+0x384 (player block at
// game+0x42fd7c; 0x42fd7c + 0x384 = 0x430100). Accesses past the struct
// (+0x8c/+0x90/+0x94/+0x99 relative) are adjacent Player fields:
// velocity.x/y/z (+0x410/+0x414/+0x418), attachment_exit_pending (+0x41d).
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

    int get_track_cell_row_index();
};

class FollowState {
public:
    AttachmentPathTemplate* begin_track_attachment_follow_state(
        TrackRowCell* source_cell, const Vector3* world_position, Player* player); // @ 0x420c40
    void update_track_attachment_follow_state(
        float rate, Vector3* out_position, Vector3* motion); // @ 0x420cb0

    unsigned char active;        // +0x00
    char unknown_01[3];
    AttachmentPathTemplate* template_record; // +0x04
    TrackRowCell* source_cell;   // +0x08
    int sample_index;            // +0x0c
    float progress;              // +0x10
    float vertical_offset;       // +0x14
    // slot order pinned by the update_track_attachment_follow_state scratch;
    // orientation_b (+0x1c) = player+0x3a0, cross-confirmed by
    // begin_post_follow_carryover's follow_orientation_b read.
    float orientation_a;         // +0x18 (zeroed by the swept entry)
    float orientation_b;         // +0x1c (zeroed by the swept entry)
    float orientation_c;         // +0x20
    float orientation_d;         // +0x24
    float orientation_e;         // +0x28
    Vector3 output_position;     // +0x2c
    Player* player;              // +0x38 back-reference (player+0x3bc)
    char unknown_3c[0x8c - 0x3c];
    // adjacent Player fields, reachable from the follow base because the
    // struct is embedded at player+0x384 (see header comment):
    float player_velocity_x;     // +0x8c = player+0x410
    float player_velocity_y;     // +0x90 = player+0x414
    float player_velocity_z;     // +0x94 = player+0x418
    char unknown_98;             // +0x98 = player+0x41c boost byte (dead: never set)
    unsigned char attachment_exit_pending; // +0x99 = player+0x41d
};

// data_4df904: relocatable game-allocation base; structures below live at
// fixed VA offsets added to it. volatile: native code re-reads it around
// every store through derived pointers.
extern char* volatile g_game_base;
extern char g_row_heading_table[]; // 0x64118c, 61 dwords per row
extern char g_follow_state_block[]; // 0x430100 = g_player_block + 0x384
extern char g_player_block[];       // 0x42fd7c
extern char g_player_position_offset[]; // 0x42fde4 = g_player_block + 0x68
extern char g_player_velocity_offset[]; // 0x43018c = g_player_block + 0x410

#endif
