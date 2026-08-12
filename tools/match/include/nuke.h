// Authored cRNuke collision-ring effect, exact 0x7c-byte Windows owner.
#ifndef NUKE_H
#define NUKE_H

#include "player_fwd.h"
#include "sprite.h"

enum {
    NUKE_SPRITE_SLOT_COUNT = 25,
};

enum NukeState {
    NUKE_STATE_INACTIVE = 0,
    NUKE_STATE_ACTIVE = 1,
};

class cRNuke {
public:
    void Init();   // @ 0x447110
    void AI();     // @ 0x4471e0
    void UnInit(); // @ 0x4470e0

    NukeState state; // +0x00
    cRSubGoldy* owner_player; // +0x04, non-owning backlink to containing cRSubGoldy
    float orbit_center_z_step; // +0x08
    float orbit_center_z; // +0x0c
    float orbit_phase; // +0x10
    float orbit_phase_step; // +0x14
    cRSprite* sprite_slots[NUKE_SPRITE_SLOT_COUNT]; // +0x18
};

typedef cRNuke Nuke;
typedef char Nuke_must_be_0x7c[(sizeof(cRNuke) == 0x7c) ? 1 : -1];

#endif
