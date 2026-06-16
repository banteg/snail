// Shared salt hazard list-anchor and pool-slot views. The pool stride is 0x98.
#ifndef SALT_HAZARD_TYPES_H
#define SALT_HAZARD_TYPES_H

#include "bod_list.h"
#include "bod_types.h"
#include "vector3.h"

class Game;

class SaltHazardSlot : public BodNode {
public:
    SaltHazardSlot* initialize_salt_hazard_runtime(); // @ 0x408630
    void update_salt_hazard();    // @ 0x441c10

    char unknown_10[0x24 - 0x10];
    void* object;              // +0x24
    Color4f color;             // +0x28, updater drives alpha
    // RenderableBod transform rows. Kept field-by-field because the slot also
    // uses the zero-offset BodNode list overlay.
    Vector3 basis_right;       // +0x38
    float basis_right_w;       // +0x44
    Vector3 basis_up;          // +0x48
    float basis_up_w;          // +0x54
    Vector3 basis_forward;     // +0x58
    float basis_forward_w;     // +0x64
    Vector3 position;          // +0x68, RenderableBod::transform.position
    float position_w;          // +0x74
    char unknown_78[0x80 - 0x78];
    int state;                 // +0x80
    char unknown_84[0x88 - 0x84];
    Game* owner_game;          // +0x88
    Vector3 velocity;          // +0x8c, spawn-time velocity; updater reuses +0x8c as fade alpha
};

typedef char SaltHazardSlot_must_match_pool_stride[
    (sizeof(SaltHazardSlot) == 0x98) ? 1 : -1];

typedef BodList SaltListAnchor;

class SaltHazardPool {
public:
    int* initialize_salt_hazard_pool();              // @ 0x441540
    int spawn_salt_hazard(const Vector3* position);  // @ 0x441560

    SaltHazardSlot slots[40];
};

#endif
