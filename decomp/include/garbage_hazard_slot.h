// Authored cRSubGarbage view, cross-checked by constructor, spawn, Smoke, AI,
// collision, BOD-list, and Kill paths. Each slot derives from the shared
// RenderableBod prefix and remains linked through its inherited BodNode.
#ifndef GARBAGE_HAZARD_SLOT_H
#define GARBAGE_HAZARD_SLOT_H

#include "bod_types.h"
#include "player_fwd.h"
#include "sprite_fwd.h"
#include "sub_loc_fwd.h"
#include "vector3.h"

class cRSubGame;

enum SubGarbageState {
    SUB_GARBAGE_STATE_INACTIVE = 0,
    SUB_GARBAGE_STATE_ACTIVE = 1,
    SUB_GARBAGE_STATE_BURST_PENDING = 2,
    SUB_GARBAGE_STATE_BURST = 3,
};

enum SubGarbageCollisionSide {
    SUB_GARBAGE_COLLISION_SIDE_RIGHT = 1,
    SUB_GARBAGE_COLLISION_SIDE_LEFT = 2,
};

enum {
    SUB_GARBAGE_SLOT_CAPACITY = 50,
};

class cRSubGarbage : public RenderableBod {
public:
    cRSubGarbage(); // @ 0x408550
    void Smoke(
        tVector& position, tVector& velocity, cRSubGoldy* owner_player); // @ 0x43d5a0
    cRSubGarbage* Kill(); // @ 0x43f130; Windows preserves the pointer result
    void AI(); // @ 0x43f200

    cRSubGarbage* next_active; // +0x80, borrowed link within the owning pool
    SubGarbageState state; // +0x84
    SubGarbageCollisionSide collision_side; // +0x88
    cRSubGame* owner_game; // +0x8c, borrowed containing subgame
    Vector3 velocity;               // +0x90
    float radius;                   // +0x9c
    float attachment_facing_angle; // +0xa0, projection output added to player heading
    float burst_progress;           // +0xa4, write-only in the retained AI
    float burst_progress_step;      // +0xa8, write-only in the retained AI
    float smoke_timer;              // +0xac
    float smoke_timer_step;         // +0xb0
    cRSprite* sprite; // +0xb4, borrowed cRSpriteManager handle
    cRSubLoc* source_cell; // +0xb8, borrowed runtime-grid cell
    unsigned char hidden; // +0xbc
    char unknown_bd[0xc0 - 0xbd];
    cRSubGoldy* owner_player; // +0xc0, borrowed embedded cRSubGoldy
};

// Compatibility vocabulary retained for existing Windows-analysis callers.
typedef cRSubGarbage SubGarbage;
typedef cRSubGarbage GarbageHazardSlot;

typedef char cRSubGarbage_must_be_0xc4[
    (sizeof(cRSubGarbage) == 0xc4) ? 1 : -1];
typedef char SubGarbage_must_be_0xc4[
    (sizeof(SubGarbage) == 0xc4) ? 1 : -1];

class SubGarbagePool {
public:
    cRSubGarbage* active_head; // +0x00, borrowed pointer into slots
    cRSubGarbage slots[SUB_GARBAGE_SLOT_CAPACITY]; // +0x04, owned storage
};

typedef SubGarbagePool GarbageHazardPool;

typedef char SubGarbagePool_must_be_0x264c[
    (sizeof(SubGarbagePool) == 0x264c) ? 1 : -1];

#endif
