// Authored cRNuke collision-ring effect, exact 0x7c-byte Windows owner.
#ifndef NUKE_H
#define NUKE_H

#include "sprite.h"

class Player;

class Nuke {
public:
    void initialize_nuke(); // @ 0x447110, cRNuke::Init
    void update_nuke(); // @ 0x4471e0, cRNuke::AI
    void uninit_nuke(); // @ 0x4470e0, cRNuke::UnInit

    int state; // +0x00
    Player* owner_player; // +0x04, non-owning backlink to containing Player
    float orbit_center_z_step; // +0x08
    float orbit_center_z; // +0x0c
    float orbit_phase; // +0x10
    float orbit_phase_step; // +0x14
    Sprite* sprite_slots[25]; // +0x18
};

typedef char Nuke_must_be_0x7c[(sizeof(Nuke) == 0x7c) ? 1 : -1];

#endif
