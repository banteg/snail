// Golb (player shot) path-follow structures, partial.
// iOS Path.o keeps this live projectile traversal family as cRPathFollowGolb.
// Offsets per analysis/decompile/*/00421770-*.c.
#ifndef GOLB_H
#define GOLB_H

#include "bod_types.h"
#include "player.h"
#include "sprite.h"
#include "vector3.h"

class SubgameRuntime;
class GolbShot;

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

// Kind/state overlay for the projectile lane at GolbShot+0x198..+0x1bf.
// Kind 2 retains a borrowed contact target here until teardown releases it.
struct GolbShotHomingStateOverlay {
    ContactTargetObject* homing_target_object; // +0x00
    Vector3 homing_target; // +0x04
    char unknown_10[0x14 - 0x10];
    float homing_blend; // +0x14
    float homing_blend_step; // +0x18
    float spin; // +0x1c
    float spin_step; // +0x20
    unsigned char skip_one_tick; // +0x24
    unsigned char slug_bounce_armed; // +0x25
    char unknown_26[0x28 - 0x26];
};

typedef char GolbShotHomingStateOverlay_must_be_0x28[
    (sizeof(GolbShotHomingStateOverlay) == 0x28) ? 1 : -1];

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

typedef char GolbPathFollowState_must_be_0x28[
    (sizeof(GolbPathFollowState) == 0x28) ? 1 : -1];

// Shot sprite/list view shared by the Golb helpers. update_golb_ai still keeps
// some raw collision lanes, but the projectile owner layout is shared here.
class GolbShot {
public:
    GolbShot* initialize_golb_shot(); // @ 0x408690
    void kill_golb(); // @ 0x414670
    void update_golb_ai(); // @ 0x414820
    int create_golb(Player* player, int spawn_selector, int emitter_index); // @ 0x415280
    Sprite* spawn_golb_trail_sprite(Vector3* position); // @ 0x415bb0
    void spawn_golb_smoke(Vector3* position); // @ 0x415c60
    void spawn_golb_impact_sprite(Vector3* position); // @ 0x415d80

    union {
        struct {
            RenderableBod primary_body;  // +0x000
            char unknown_078[0x080 - 0x078];
            // Kind-1 also treats this subobject as the Vapour body prefix.
            RenderableBod secondary_body; // +0x080
            char unknown_0f8[0x118 - 0x0f8];
            RenderableBod tertiary_body; // +0x118
        };
        struct {
            char unknown_000[0x080];
            char vapour[0x150 - 0x080]; // +0x080, Vapour object view
            TransformMatrix live_matrix; // +0x150
        };
    };
    char unknown_190[0x198 - 0x190];
    ContactTargetObject* homing_target_object; // +0x198, reserved target owner
    Vector3 homing_target;           // +0x19c
    char unknown_1a8[4];
    float homing_blend;              // +0x1ac
    float homing_blend_step;         // +0x1b0
    float spin;                      // +0x1b4
    float spin_step;                 // +0x1b8
    unsigned char skip_one_tick;     // +0x1bc
    unsigned char slug_bounce_armed; // +0x1bd
    char unknown_1be[2];
    int kind;                    // +0x1c0
    Vector3 basis_right_scratch;  // +0x1c4
    char unknown_1d0[0x1d4 - 0x1d0];
    Vector3 basis_up_scratch;     // +0x1d4
    char unknown_1e0[0x1e4 - 0x1e0];
    Vector3 basis_forward_scratch; // +0x1e4
    char unknown_1f0[0x1f4 - 0x1f0];
    Vector3 position;             // +0x1f4
    char unknown_200[0x234 - 0x200];
    Vector3 previous_output;      // +0x234
    char unknown_240[0x244 - 0x240];
    int state;                   // +0x244
    union {
        void* render_body_owner; // +0x248, kind-specific body/sprite owner
        void* owner_body;        // +0x248, update_golb_ai body-position view
    };
    Vector3 velocity;            // +0x24c
    Vector3 direction;           // +0x258
    float path_factor;           // +0x264
    float lifetime;              // +0x268
    float lifetime_step;         // +0x26c
    SubgameRuntime* game;        // +0x270
    union {
        void* object_ref;        // +0x274, copied into spawned sprites
        int emitter_index;       // +0x274, create_golb caller-facing identity
    };
    union {
        Player* owner_player;  // +0x278
        Player* player;        // +0x278, update_golb_ai bounds/collision view
    };
    TransformMatrix source_matrix; // +0x27c
    GolbPathFollowState path_follow; // +0x2bc
    float path_entry_z_latch; // +0x2e4
};

#endif
