// Authored cRSubGarbage view, cross-checked by constructor, spawn, Smoke, AI,
// collision, BOD-list, and Kill paths. Each slot derives from the shared
// RenderableBod prefix and remains linked through its inherited BodNode.
#ifndef GARBAGE_HAZARD_SLOT_H
#define GARBAGE_HAZARD_SLOT_H

#include "bod_types.h"
#include "sub_loc_fwd.h"
#include "vector3.h"

class Player;
class Sprite;
class SubgameRuntime;

class SubGarbage : public RenderableBod {
public:
    SubGarbage* initialize_garbage_hazard();
    SubGarbage* update_garbage_hazard();
    SubGarbage* destroy_garbage_hazard();
    void spawn_garbage_smoke_particle(Vector3* position, Vector3* velocity, Player* player);

    char unknown_78[0x80 - 0x78];
    SubGarbage* next_active;        // +0x80
    int state;                      // +0x84
    int collision_side;             // +0x88, 1 right / 2 left
    SubgameRuntime* game;           // +0x8c
    Vector3 velocity;               // +0x90
    float radius;                   // +0x9c
    float attachment_facing_angle;  // +0xa0, projection output added to player heading
    int unknown_a4;                 // +0xa4
    float burst_rate_step;          // +0xa8
    float smoke_timer;              // +0xac
    float smoke_timer_step;         // +0xb0
    Sprite* sprite;                 // +0xb4
    TrackRowCell* source_cell;       // +0xb8
    unsigned char hidden;            // +0xbc
    char unknown_bd[0xc0 - 0xbd];
    Player* player;                 // +0xc0
};
typedef SubGarbage GarbageHazardSlot;

typedef char SubGarbage_must_be_0xc4[
    (sizeof(SubGarbage) == 0xc4) ? 1 : -1];

class SubGarbagePool {
public:
    SubGarbage* active_head; // +0x00, game +0x359140, borrowed chain head
    SubGarbage slots[50];    // +0x04, game +0x359144
};

typedef SubGarbagePool GarbageHazardPool;

typedef char SubGarbagePool_must_be_0x264c[
    (sizeof(SubGarbagePool) == 0x264c) ? 1 : -1];

#endif
