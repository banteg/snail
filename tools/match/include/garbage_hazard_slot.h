// Shared garbage hazard slot view, cross-checked by spawn smoke, update,
// contact-target append, collision, and destroy paths. Game stays a
// scratch-local context view.
#ifndef GARBAGE_HAZARD_SLOT_H
#define GARBAGE_HAZARD_SLOT_H

#include "contact_target.h"
#include "sprite.h"

class Game;
class Player;
struct TrackRowCell;

class GarbageHazardSlot : public ContactTargetObject {
public:
    GarbageHazardSlot* update_garbage_hazard();
    GarbageHazardSlot* destroy_garbage_hazard();
    char spawn_garbage_smoke_particle(Vector3* position, Vector3* velocity, Player* player);

    GarbageHazardSlot* list_prev;   // +0x08
    GarbageHazardSlot* list_next;   // +0x0c
    char unknown_10[0x68 - 0x10];
    Vector3 world_position;         // +0x68
    char unknown_74[0x80 - 0x74];
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

#endif
