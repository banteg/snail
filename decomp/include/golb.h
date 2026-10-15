// Golb (player shot) path-follow structures, partial. iOS Path.o keeps this
// live projectile traversal family as cRPathFollowGolb; its state borrows the
// shared authored cRPath and cRSubLoc owners rather than private prefix views.
#ifndef GOLB_H
#define GOLB_H

#include "bod_types.h"
#include "player_fwd.h"
#include "sprite.h"
#include "track_attachment_types.h"
#include "vapour.h"
#include "vector3.h"

class cRSubGame;
class cRSubGolb;
typedef cRSubGolb GolbShot;

// Kind/state overlay for the projectile lane at GolbShot+0x198..+0x1bf.
// Kind 2 retains a borrowed contact target here until teardown releases it.
struct GolbShotHomingStateOverlay {
    ContactTargetObject* homing_target_object; // +0x00
    Vector3 homing_target; // +0x04
    cRSubGolb* rocket_owner_shot; // +0x10, kind-2 embedded-body backlink
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

class cRPathFollowGolb {
public:
    void Init(
        cRSubLoc* source_cell,
        tVector& position,
        cRSubGolb* shot_); // @ 0x421770
    int Traverse(float path_factor, tVector& position, tVector* velocity); // @ 0x4217b0

    unsigned char active;     // +0x00
    char unknown_01[3];
    cRPath* template_record;       // +0x04, borrowed authored cRPath
    cRSubLoc* source_cell;        // +0x08, borrowed runtime-grid cell
    int sample_index;          // +0x0c
    float progress;            // +0x10
    float vertical_offset;     // +0x14
    Vector3 output_position;   // +0x18
    cRSubGolb* shot;           // +0x24
};

typedef cRPathFollowGolb GolbPathFollowState;
typedef char GolbPathFollowState_must_be_0x28[
    (sizeof(cRPathFollowGolb) == 0x28) ? 1 : -1];

// Authored cRGolbRocket is a fieldless cRBodPos specialization whose AI body
// folds into the shared one-byte Windows no-op.
class cRGolbRocket : public RenderableBod {
public:
    void noop_runtime_ai(); // folded @ 0x407b50; cRGolbRocket::AI()
};
typedef char GolbRocket_must_be_0x80[
    (sizeof(cRGolbRocket) == 0x80) ? 1 : -1];
typedef cRGolbRocket GolbRocket;

// Windows and the mobile cRSubGoldy constructor agree that each shot is a
// zero-offset cRBodPos specialization, followed by its platform-specific
// presentation children. update_golb_ai still keeps some raw collision lanes,
// but the projectile owner layout is shared here.
class cRSubGolb : public RenderableBod {
public:
    cRSubGolb* initialize_golb_shot(); // @ 0x408690
    void Kill(); // @ 0x414670, iOS/Android cRSubGolb::Kill()
    void AI(); // @ 0x414820
    void Create(cRSubGoldy* player, int spawn_selector, int shot_slot_index); // @ 0x415280
    // Windows retains pointer arguments and returns its allocated Jet sprite;
    // Android preserves the authored by-value method names.
    cRSprite* Jet(Vector3* position); // @ 0x415bb0
    void Smoke(Vector3* position); // @ 0x415c60
    void Explode(Vector3* position); // @ 0x415d80; mobile passes tVector by value

    cRVapour vapour; // +0x080, complete kind-1 trail renderer
    cRSubGolb* vapour_owner_shot; // +0x114, kind-1 embedded-body backlink
    cRGolbRocket tertiary_body; // +0x118, authored cRGolbRocket owner
    ContactTargetObject* homing_target_object; // +0x198, reserved target owner
    Vector3 homing_target;           // +0x19c
    cRSubGolb* rocket_owner_shot;    // +0x1a8, kind-2 embedded-body backlink
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
    cRSprite* render_sprite;       // +0x248, kind-0 sprite owner
    Vector3 velocity;            // +0x24c
    Vector3 direction;           // +0x258
    float path_factor;           // +0x264
    float lifetime;              // +0x268
    float lifetime_step;         // +0x26c
    cRSubGame* game;        // +0x270
    int shot_slot_index;         // +0x274, index copied into trail Sprite::object_ref
    union {
        cRSubGoldy* owner_player;  // +0x278
        cRSubGoldy* player;        // +0x278, update_golb_ai bounds/collision view
    };
    TransformMatrix source_matrix; // +0x27c
    cRPathFollowGolb path_follow; // +0x2bc
    float path_entry_z_latch; // +0x2e4
};

typedef char GolbShot_must_be_0x2e8[(sizeof(cRSubGolb) == 0x2e8) ? 1 : -1];

#endif
