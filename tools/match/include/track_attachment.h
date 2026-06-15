// Attachment-follow runtime structures, partial.
// Offsets per analysis/decompile/*/00420c40-*.c, 0042c770-*.c, 00420cb0-*.c.
// UNIFIED (2026-06-12): the "FollowState global at game+0x430100" is the
// Player's embedded follow sub-struct at player+0x384 (player block at
// game+0x42fd7c; 0x42fd7c + 0x384 = 0x430100). Accesses past the struct
// (+0x8c/+0x90/+0x94/+0x99 relative) are adjacent Player fields:
// velocity.x/y/z (+0x410/+0x414/+0x418), attachment_exit_pending (+0x41d).
#ifndef TRACK_ATTACHMENT_H
#define TRACK_ATTACHMENT_H

#include "vector_types.h"
#include "player.h"

struct TransformMatrix;

struct AttachmentTransform {
    Vector4 basis_right;             // +0x00
    Vector4 basis_up;                // +0x10
    Vector4 basis_forward;           // +0x20
    Vector4 position;                // +0x30
};

struct AttachmentSample {            // stride 0xa8
    AttachmentTransform transform;   // +0x00
    float inverse_matrix[12];        // +0x40, local-frame rotation
    char unknown_70[0x80 - 0x70];
    Vector3 delta_dir_to_next;       // +0x80
    float delta_length;              // +0x8c, segment length (the swept-entry
                                     // "depth limit" gate is z < this)
    float center_x;                  // +0x90
    float rotation_scalar_94;        // +0x94
    float rotation_scalar_98;        // +0x98
    float lateral_scale;             // +0x9c
    float special_scalar;            // +0xa0, kind-42 scale/radius source
    float lateral_source;            // +0xa4
};

struct TrackRowCell;

struct AttachmentPathTemplate {
    void try_enter_track_attachment_from_swept_motion(
        float px, float py, float pz,
        float sweep_x, float sweep_y, float sweep_z,
        TrackRowCell* cell); // @ 0x42c770
    int compute_kind42_attachment_transform(
        float radius, float x, float y, TransformMatrix* transform, float* out_angle);

    char unknown_00[0x38];
    int kind;                        // +0x38
    unsigned char is_mirrored_x;     // +0x3c
    char unknown_3d[0x40 - 0x3d];
    int side_exit_mode;              // +0x40
    int segment_count;               // +0x44
    unsigned int unknown_48;         // +0x48
    float segment_count_f;           // +0x4c
    float width_or_scale;            // +0x50
    int width_cells;                 // +0x54, integer half-span source
    AttachmentSample* primary_samples; // +0x58
    AttachmentSample* secondary_samples; // +0x5c
    char unknown_60[0x98 - 0x60];
    float installed_heading_delta;   // +0x98
    unsigned char special_runtime_flag_9c; // +0x9c
    char unknown_9d[0xa8 - 0x9d];

    void get_path_position_at_node(float* payload, int node, int row_index, float* out);
};

struct TrackRowCell {
    char unknown_00[0x10];
    Vector3 anchor_position;            // +0x10 (z at +0x18)
    char unknown_1c[0x38 - 0x1c];
    AttachmentPathTemplate* attachment_template_record; // +0x38
    unsigned char tile_id;              // +0x3c
    unsigned char tile_flags_3d;        // +0x3d
    char unknown_3e[0x40 - 0x3e];
    int lane_word;                      // +0x40, low 3 bits are lane

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
extern char g_player_squidge_offset[]; // 0x4340c0 = g_player_block + 0x4344

#endif
