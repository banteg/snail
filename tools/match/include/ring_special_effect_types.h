// Ring/special-effect runtime views, partial.
#ifndef RING_SPECIAL_EFFECT_TYPES_H
#define RING_SPECIAL_EFFECT_TYPES_H

#include "vector3.h"

class Player;

class RingOrSpecialEffectParent {
public:
    char unknown_000[0x68];
    Vector3 position; // +0x68
    char unknown_074[0x84 - 0x74];
    Player* owner_player; // +0x84
    int kind; // +0x88
    char unknown_08c[0x1e8 - 0x8c];
    int star_shower_counter; // +0x1e8
    int star_sprite_id; // +0x1ec
};

#endif
