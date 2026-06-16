// Shared sub-lazer views. SubLazerSlot is the pool-spawn object, while
// SubLazerRuntime is the renderable-body update object whose state lives at
// +0x38. Keep the two views separate: the pool free/live flag is at slot+0x80.
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
    void spawn_sub_lazer_projectile(const Vector3* origin, const Vector3* direction); // @ 0x441670

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

class SubLazerPool {
public:
    int* initialize_sub_lazer_pool(); // @ 0x441650
    void shoot_subgoldy(const float* origin, const Vector3* direction); // @ 0x441ad0

    SubLazerSlot slots[20];
};

struct SubLazerRuntime {
    void update_sub_lazer_projectile(); // @ 0x43efb0

    int unknown_00;
    unsigned int list_flags;     // +0x04
    SubLazerRuntime* list_prev;  // +0x08
    SubLazerRuntime* list_next;  // +0x0c
    char unknown_10[0x14 - 0x10];
    float bob_base_y;            // +0x14
    float position_z;            // +0x18
    char unknown_1c[0x38 - 0x1c];
    int state;                   // +0x38: 1 live, 2 remove
    Player* owner;               // +0x3c
    char unknown_40[0x44 - 0x40];
    SubLazerGameView* owner_game; // +0x44
    char unknown_48[0x64 - 0x48];
    Sprite* sprite;              // +0x64
    char unknown_68[0x6c - 0x68];
    float bob_phase;             // +0x6c
    float bob_phase_step;        // +0x70
};

#endif
