// Authored cRSubGarbage view, cross-checked by spawn, Smoke, AI, collision,
// BOD-list, and Kill paths.
#ifndef GARBAGE_HAZARD_SLOT_H
#define GARBAGE_HAZARD_SLOT_H

#include "bod_list.h"
#include "sprite.h"
#include "sub_loc_fwd.h"

class Player;
class SubgameRuntime;

class SubGarbage : public BodNode {
public:
    SubGarbage* initialize_garbage_hazard();
    SubGarbage* update_garbage_hazard();
    SubGarbage* destroy_garbage_hazard();
    void spawn_garbage_smoke_particle(Vector3* position, Vector3* velocity, Player* player);

    Vector3 bod_position;           // +0x10, BodBase::position
    float render_arg_1c;            // +0x1c, BodBase texture-u render argument
    float render_arg_20;            // +0x20, BodBase render argument
    void* object;                   // +0x24
    Color4f color;                  // +0x28
    // RenderableBod transform rows. Kept field-by-field because VC6 rejects a
    // union containing TransformMatrix's constructors.
    Vector3 basis_right;            // +0x38
    float basis_right_w;            // +0x44
    Vector3 basis_up;               // +0x48
    float basis_up_w;               // +0x54
    Vector3 basis_forward;          // +0x58
    float basis_forward_w;          // +0x64
    Vector3 world_position;         // +0x68, RenderableBod::transform.position
    float world_position_w;         // +0x74
    char unknown_78[0x80 - 0x78];
    SubGarbage* next_active;        // +0x80
    int state;                      // +0x84
    int collision_side;             // +0x88, 1 right / 2 left
    SubgameRuntime* game;           // +0x8c
    Vector3 velocity;               // +0x90
    float radius;                   // +0x9c
    float sprite_y_offset;          // +0xa0
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
