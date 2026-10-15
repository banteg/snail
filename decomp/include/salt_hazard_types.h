// Authored cRSalt/cRSaltManager views. Each inline manager slot derives from
// RenderableBod and is 0x98 bytes.
#ifndef SALT_HAZARD_TYPES_H
#define SALT_HAZARD_TYPES_H

#include "bod_list.h"
#include "bod_types.h"
#include "vector3.h"

class cRSubGame;

enum SaltState {
    SALT_STATE_INACTIVE = 0,
    SALT_STATE_ACTIVE = 1,
    SALT_STATE_RECYCLE_PENDING = 2,
};

class cRSalt : public RenderableBod {
public:
    cRSalt(); // @ 0x408630
    void AI(); // @ 0x441c10

    SaltState state;            // +0x80
    char unknown_84[0x88 - 0x84];
    cRSubGame* owner_game; // +0x88
    float fade_alpha;           // +0x8c
    float spawn_velocity_y;     // +0x90
    unsigned char collision_armed; // +0x94
    char unknown_95[0x98 - 0x95];
};

// Compatibility vocabulary retained for existing Windows-analysis callers.
typedef cRSalt Salt;
typedef cRSalt SaltHazardSlot;

typedef char cRSalt_must_be_0x98[(sizeof(cRSalt) == 0x98) ? 1 : -1];
typedef char Salt_must_be_0x98[(sizeof(Salt) == 0x98) ? 1 : -1];

class cRSaltManager {
public:
    void Init(); // @ 0x441540
    void Add(tVector& position); // @ 0x441560

    cRSalt slots[40];
};

typedef cRSaltManager SaltManager;
typedef cRSaltManager SaltHazardPool;

typedef char cRSaltManager_must_be_0x17c0[
    (sizeof(cRSaltManager) == 0x17c0) ? 1 : -1];
typedef char SaltManager_must_be_0x17c0[
    (sizeof(SaltManager) == 0x17c0) ? 1 : -1];

#endif
