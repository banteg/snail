// Shared sub-lazer slot view. iOS symbols name slots cRSubLazer and the pool
// cRSubLazerManager. The spawn, update, and deactivate paths all use this 0xb0
// slot; an earlier split update object was a shifted jetpack name.
// The first 0x10 bytes are the common intrusive BOD list prefix.
#ifndef SUB_LAZER_TYPES_H
#define SUB_LAZER_TYPES_H

#include "bod_list.h"
#include "player.h"
#include "sprite.h"
#include "vector3.h"

class Game;

class SubLazerSlot : public BodNode {
public:
    SubLazerSlot* initialize_sub_lazer_runtime(); // @ 0x408610
    void spawn_sub_lazer_projectile(const Vector3* origin, const Vector3* direction); // @ 0x441670
    int deactivate_sub_lazer_projectile(); // @ 0x441740
    void update_sub_lazer_projectile(); // @ 0x4417d0

    Vector3 bod_position;     // +0x10, BodBase::position
    int render_arg_1c;        // +0x1c, BodBase render argument
    float render_arg_20;      // +0x20, BodBase render argument
    void* object;             // +0x24
    Color4f color;            // +0x28
    // RenderableBod transform rows. Kept field-by-field because the slot also
    // uses the zero-offset BodNode list overlay.
    Vector3 basis_right;      // +0x38
    float basis_right_w;      // +0x44
    Vector3 basis_up;         // +0x48
    float basis_up_w;         // +0x54
    Vector3 basis_forward;    // +0x58
    float basis_forward_w;    // +0x64
    Vector3 position;         // +0x68, RenderableBod::transform.position
    float position_w;         // +0x74
    char unknown_78[0x80 - 0x78];
    int state;                // +0x80, pool free/live state
    char unknown_84[0x88 - 0x84];
    Game* owner_game;         // +0x88
    Vector3 velocity;         // +0x8c
    float sprite_bob_phase;   // +0x98
    float sprite_bob_phase_step; // +0x9c
    char unknown_a0[0xb0 - 0xa0];
};

typedef char SubLazerSlot_must_match_pool_stride[
    (sizeof(SubLazerSlot) == 0xb0) ? 1 : -1];

// The sub-lazer live/free anchor is the same list shape used by other BOD pools.
typedef BodList SubLazerListAnchor;

class SubLazerPool {
public:
    int* initialize_sub_lazer_pool(); // @ 0x441650
    void shoot_subgoldy(const float* origin, const Vector3* direction); // @ 0x441ad0

    SubLazerSlot slots[20];
};

#endif
