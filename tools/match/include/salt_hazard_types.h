// Shared salt hazard list-anchor and pool-slot views. The pool stride is 0x98;
// update_salt_hazard intentionally reads progress/step at +0x98/+0x9c as
// off-stride overlap, so those fields do not belong to SaltHazardSlot.
#ifndef SALT_HAZARD_TYPES_H
#define SALT_HAZARD_TYPES_H

#include "vector3.h"

struct Game;

class SaltHazardSlot {
public:
    void update_salt_hazard();    // @ 0x4417d0
    int deactivate_salt_hazard(); // @ 0x441740

    int unknown_00;
    unsigned int list_flags;   // +0x04, 0x200 = linked, 0x40 = iteration guard
    SaltHazardSlot* list_prev; // +0x08
    SaltHazardSlot* list_next; // +0x0c
    char unknown_10[0x68 - 0x10];
    Vector3 position;          // +0x68, live-matrix position row
    char unknown_74[0x80 - 0x74];
    int state;                 // +0x80
    char unknown_84[0x88 - 0x84];
    Game* owner_game;          // +0x88
    Vector3 velocity;          // +0x8c (z low byte poked by spawn)
};

typedef char SaltHazardSlot_must_match_pool_stride[
    (sizeof(SaltHazardSlot) == 0x98) ? 1 : -1];

struct SaltListAnchor {
    char unknown_00[4];
    SaltHazardSlot* first;    // +0x04
    SaltHazardSlot* free_top; // +0x08
};

class SaltHazardPool {
public:
    int* initialize_salt_hazard_pool();              // @ 0x441540
    int spawn_salt_hazard(const Vector3* position);  // @ 0x441560

    SaltHazardSlot slots[40];
};

#endif
