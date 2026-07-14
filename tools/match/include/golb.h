// Golb (player shot) path-follow structures, partial. iOS Path.o keeps this
// live projectile traversal family as cRPathFollowGolb; its state borrows the
// shared authored Path and SubLoc owners rather than private prefix views.
#ifndef GOLB_H
#define GOLB_H

#include "bod_types.h"
#include "sprite.h"
#include "track_attachment_types.h"
#include "vapour.h"
#include "vector3.h"

class Player;
class SubgameRuntime;
class GolbShot;

// Kind/state overlay for the projectile lane at GolbShot+0x198..+0x1bf.
// Kind 2 retains a borrowed contact target here until teardown releases it.
struct GolbShotHomingStateOverlay {
    ContactTargetObject* homing_target_object; // +0x00
    Vector3 homing_target; // +0x04
    GolbShot* rocket_owner_shot; // +0x10, kind-2 embedded-body backlink
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
        SubLoc* source_cell,
        const Vector3* position,
        GolbShot* shot_); // @ 0x421770
    int calc_path_length_z(float path_factor, Vector3* position, Vector3* velocity); // @ 0x4217b0

    unsigned char active;     // +0x00
    char unknown_01[3];
    Path* template_record;       // +0x04, borrowed authored cRPath
    SubLoc* source_cell;        // +0x08, borrowed runtime-grid cell
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
    void create_golb(Player* player, int spawn_selector, int emitter_index); // @ 0x415280
    Sprite* spawn_golb_trail_sprite(Vector3* position); // @ 0x415bb0
    void spawn_golb_smoke(Vector3* position); // @ 0x415c60
    void spawn_golb_impact_sprite(Vector3* position); // @ 0x415d80

    union {
        struct {
            RenderableBod primary_body;  // +0x000
            // Kind-1 also treats this subobject as the Vapour body prefix.
            RenderableBod secondary_body; // +0x080
            char unknown_100[0x114 - 0x100];
            GolbShot* vapour_owner_shot; // +0x114, kind-1 embedded-body backlink
            RenderableBod tertiary_body; // +0x118
        };
        struct {
            char unknown_000[0x080];
            Vapour vapour; // +0x080, kind-1 trail renderer/BOD-compatible view
            char unknown_114[0x150 - 0x114];
            TransformMatrix live_matrix; // +0x150
        };
    };
    ContactTargetObject* homing_target_object; // +0x198, reserved target owner
    Vector3 homing_target;           // +0x19c
    GolbShot* rocket_owner_shot;     // +0x1a8, kind-2 embedded-body backlink
    float homing_blend;              // +0x1ac
    float homing_blend_step;         // +0x1b0
    float spin;                      // +0x1b4
    float spin_step;                 // +0x1b8
    unsigned char skip_one_tick;     // +0x1bc
    unsigned char slug_bounce_armed; // +0x1bd
    char unknown_1be[2];
    int kind;                    // +0x1c0
    // Path interpolation writes the basis rows and raw projectile position
    // into one transform. The next 0x40-byte owner retains the previous
    // rendered position; only that position row is proven live so far.
    TransformMatrix flight_transform;          // +0x1c4
    TransformMatrix previous_flight_transform; // +0x204
    int state;                   // +0x244
    union {
        void* render_body_owner; // +0x248, kind-specific body/sprite owner
        Sprite* render_sprite;   // +0x248, kind-0 sprite owner
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

typedef char GolbShot_must_be_0x2e8[(sizeof(GolbShot) == 0x2e8) ? 1 : -1];

#endif
