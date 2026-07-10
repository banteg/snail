// Shared NukeController view, cross-checked by initialize_nuke, update_nuke,
// and uninit_nuke.
#ifndef NUKE_CONTROLLER_H
#define NUKE_CONTROLLER_H

#include "sprite.h"

class Player;

class NukeController {
public:
    void initialize_nuke(); // @ 0x447110
    void update_nuke();    // @ 0x4471e0
    void uninit_nuke();   // @ 0x4470e0

    int state; // +0x00
    Player* owner_player; // +0x04, non-owning backlink to containing Player
    float orbit_center_z_step; // +0x08
    float orbit_center_z; // +0x0c
    float orbit_phase; // +0x10
    float orbit_phase_step; // +0x14
    Sprite* sprite_slots[25]; // +0x18
};

#endif
