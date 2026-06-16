// Shared sub-lazer slot view. The spawn, update, and deactivate paths all use
// this 0xb0 slot; an earlier split update object was a shifted jetpack name.
#ifndef SUB_LAZER_TYPES_H
#define SUB_LAZER_TYPES_H

#include "player.h"
#include "sprite.h"
#include "vector3.h"

class Game;
struct SubLazerGameView {
    char unknown_00[0x09];
    unsigned char paused; // +0x09
};

class SubLazerSlot {
public:
    SubLazerSlot* initialize_sub_lazer_runtime(); // @ 0x408610
    void spawn_sub_lazer_projectile(const Vector3* origin, const Vector3* direction); // @ 0x441670
    int deactivate_sub_lazer_projectile(); // @ 0x441740
    void update_sub_lazer_projectile(); // @ 0x4417d0

    int unknown_00;
    unsigned int list_flags;  // +0x04
    SubLazerSlot* list_prev;  // +0x08
    SubLazerSlot* list_next;  // +0x0c
    char unknown_10[0x68 - 0x10];
    Vector3 position;         // +0x68, live-matrix position row
    char unknown_74[0x80 - 0x74];
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

struct SubLazerListAnchor {
    char unknown_00[4];
    SubLazerSlot* first;    // +0x04
    SubLazerSlot* free_top; // +0x08
};

class SubLazerPool {
public:
    int* initialize_sub_lazer_pool(); // @ 0x441650
    void shoot_subgoldy(const float* origin, const Vector3* direction); // @ 0x441ad0

    SubLazerSlot slots[20];
};

#endif
