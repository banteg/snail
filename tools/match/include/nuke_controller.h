// Shared NukeController view, cross-checked by initialize_nuke, update_nuke,
// and uninit_nuke.
#ifndef NUKE_CONTROLLER_H
#define NUKE_CONTROLLER_H

#include "sprite.h"

struct Player;

class NukeController {
public:
    int initialize_nuke(); // @ 0x447110
    int update_nuke();    // @ 0x4471e0
    void uninit_nuke();   // @ 0x4470e0

    int state; // +0x00
    Player* owner_player; // +0x04
    float orbit_axis_step; // +0x08
    float orbit_axis; // +0x0c
    float phase; // +0x10
    float phase_step; // +0x14
    Sprite* sprite_slots[25]; // +0x18
};

#endif
