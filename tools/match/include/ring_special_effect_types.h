// Ring/special-effect runtime views, partial.
#ifndef RING_SPECIAL_EFFECT_TYPES_H
#define RING_SPECIAL_EFFECT_TYPES_H

#include "vector3.h"

class Player;

class RingEffectRateSource {
public:
    char unknown_00[0x38];
    float subgame_rate; // +0x38
};

class RingOrSpecialEffectParent {
public:
    int initialize_ring_or_special_effect_particles(void* unused_rate_source); // @ 0x43e470

    void* vtable; // +0x00
    unsigned int flags; // +0x04
    RingOrSpecialEffectParent* next; // +0x08
    RingOrSpecialEffectParent* prev; // +0x0c
    char unknown_010[0x68 - 0x10];
    Vector3 position; // +0x68
    char unknown_074[0x80 - 0x74];
    int active; // +0x80
    Player* owner_player; // +0x84
    int kind; // +0x88
    void* owner_context; // +0x8c
    char unknown_090[0x1d0 - 0x90];
    RingEffectRateSource* rate_source; // +0x1d0
    char unknown_1d4[0x1e0 - 0x1d4];
    float active_phase; // +0x1e0
    float active_phase_step; // +0x1e4
    int star_shower_counter; // +0x1e8
    int star_sprite_id; // +0x1ec
};

#endif
