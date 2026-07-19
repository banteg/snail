// Authored cRSalt/cRSaltManager views. Each inline manager slot derives from
// RenderableBod and is 0x98 bytes.
#ifndef SALT_HAZARD_TYPES_H
#define SALT_HAZARD_TYPES_H

#include "bod_list.h"
#include "bod_types.h"
#include "vector3.h"

class SubgameRuntime;

enum SaltState {
    SALT_STATE_INACTIVE = 0,
    SALT_STATE_ACTIVE = 1,
    SALT_STATE_RECYCLE_PENDING = 2,
};

class Salt : public RenderableBod {
public:
    Salt* initialize_salt_hazard_runtime(); // @ 0x408630
    void update_salt_hazard(); // @ 0x441c10

    SaltState state;            // +0x80
    char unknown_84[0x88 - 0x84];
    SubgameRuntime* owner_game; // +0x88
    float fade_alpha;           // +0x8c
    float spawn_velocity_y;     // +0x90
    unsigned char collision_armed; // +0x94
    char unknown_95[0x98 - 0x95];
};

typedef Salt SaltHazardSlot;

typedef char Salt_must_be_0x98[(sizeof(Salt) == 0x98) ? 1 : -1];

typedef BodList SaltListAnchor;

class SaltManager {
public:
    void initialize_salt_hazard_pool();              // @ 0x441540
    int spawn_salt_hazard(const Vector3* position);  // @ 0x441560

    Salt slots[40];
};

typedef SaltManager SaltHazardPool;

typedef char SaltManager_must_be_0x17c0[
    (sizeof(SaltManager) == 0x17c0) ? 1 : -1];

#endif
