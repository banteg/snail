// Authored cRSalt/cRSaltManager views. Each inline manager slot derives from
// RenderableBod and is 0x98 bytes.
#ifndef SALT_HAZARD_TYPES_H
#define SALT_HAZARD_TYPES_H

#include "bod_list.h"
#include "bod_types.h"
#include "vector3.h"

class SubgameRuntime;

class Salt : public RenderableBod {
public:
    Salt* initialize_salt_hazard_runtime(); // @ 0x408630
    void update_salt_hazard();    // @ 0x441c10
    float& fade_alpha() { return velocity.x; } // +0x8c overlay in update_salt_hazard
    unsigned char& collision_armed() { return *(unsigned char*)&velocity.z; } // +0x94

    char unknown_78[0x80 - 0x78];
    int state;                 // +0x80
    char unknown_84[0x88 - 0x84];
    SubgameRuntime* owner_game; // +0x88
    Vector3 velocity;          // +0x8c, spawn motion/fade/collision overlay
};

typedef Salt SaltHazardSlot;

typedef char Salt_must_be_0x98[(sizeof(Salt) == 0x98) ? 1 : -1];

typedef BodList SaltListAnchor;

class SaltManager {
public:
    int* initialize_salt_hazard_pool();              // @ 0x441540
    int spawn_salt_hazard(const Vector3* position);  // @ 0x441560

    Salt slots[40];
};

typedef SaltManager SaltHazardPool;

typedef char SaltManager_must_be_0x17c0[
    (sizeof(SaltManager) == 0x17c0) ? 1 : -1];

#endif
