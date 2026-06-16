// Shared garbage hazard slot view, cross-checked by spawn smoke, update,
// contact-target append, collision, BOD-list, and destroy paths. Game stays a
// scratch-local context view.
#ifndef GARBAGE_HAZARD_SLOT_H
#define GARBAGE_HAZARD_SLOT_H

#include "bod_list.h"
#include "sprite.h"

class Game;
class Player;
struct TrackRowCell;

class GarbageHazardSlot : public BodNode {
public:
    GarbageHazardSlot* initialize_garbage_hazard();
    GarbageHazardSlot* update_garbage_hazard();
    GarbageHazardSlot* destroy_garbage_hazard();
    void spawn_garbage_smoke_particle(Vector3* position, Vector3* velocity, Player* player);

    char unknown_10[0x38 - 0x10];
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
    GarbageHazardSlot* next_active; // +0x80
    int state;                      // +0x84
    int collision_side;             // +0x88, 1 right / 2 left
    Game* game;                     // +0x8c
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
typedef char GarbageHazardSlot_must_be_0xc4[
    (sizeof(GarbageHazardSlot) == 0xc4) ? 1 : -1];

typedef BodList GarbageHazardListAnchor;

class GarbageHazardPool {
public:
    GarbageHazardSlot* active_head; // +0x00, game +0x359140
    GarbageHazardSlot slots[50];    // +0x04, game +0x359144
};

typedef char GarbageHazardPool_must_be_0x264c[
    (sizeof(GarbageHazardPool) == 0x264c) ? 1 : -1];

#endif
