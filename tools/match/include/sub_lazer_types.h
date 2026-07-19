// Authored cRSubLazer and cRSubLazerManager views. The spawn, update, and kill
// paths all use one 0xb0 slot; an earlier split update object was a shifted
// jetpack name.
// RenderableBod supplies the common transform and zero-offset intrusive-list
// prefix.
#ifndef SUB_LAZER_TYPES_H
#define SUB_LAZER_TYPES_H

#include "bod_types.h"
#include "vector3.h"

class SubgameRuntime;

enum SubLazerState {
    SUB_LAZER_STATE_INACTIVE = 0,
    SUB_LAZER_STATE_ACTIVE = 1,
    SUB_LAZER_STATE_RECYCLE_PENDING = 2,
};

enum {
    SUB_LAZER_SLOT_CAPACITY = 20,
};

class SubLazer : public RenderableBod {
public:
    SubLazer* initialize_sub_lazer_runtime(); // @ 0x408610
    void spawn_sub_lazer_projectile(const Vector3* origin, const Vector3* direction); // @ 0x441670
    void deactivate_sub_lazer_projectile(); // @ 0x441740
    void update_sub_lazer_projectile(); // @ 0x4417d0

    SubLazerState state;      // +0x80
    char unknown_84[0x88 - 0x84];
    SubgameRuntime* owner_game; // +0x88, borrowed containing subgame
    Vector3 velocity;         // +0x8c
    float sprite_bob_phase;   // +0x98
    float sprite_bob_phase_step; // +0x9c
    char unknown_a0[0xb0 - 0xa0];
};

typedef SubLazer SubLazerSlot;

typedef char SubLazer_must_be_0xb0[(sizeof(SubLazer) == 0xb0) ? 1 : -1];

class SubLazerManager {
public:
    void initialize_sub_lazer_pool(); // @ 0x441650
    void shoot_subgoldy(Vector3* origin, const Vector3* direction); // @ 0x441ad0

    SubLazer slots[SUB_LAZER_SLOT_CAPACITY]; // owned storage
};

typedef SubLazerManager SubLazerPool;

typedef char SubLazerManager_must_be_0xdc0[
    (sizeof(SubLazerManager) == 0xdc0) ? 1 : -1];

#endif
