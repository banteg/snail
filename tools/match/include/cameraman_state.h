// Gameplay camera runtime state, partial.
#ifndef CAMERAMAN_STATE_H
#define CAMERAMAN_STATE_H

#include "transform_matrix.h"

class Player;
class SubgameRuntime;

class CameramanState {
public:
    void initialize_cameraman(); // @ 0x446160
    void update_cameraman();     // @ 0x4461d0

    TransformMatrix live_matrix;             // +0x00
    TransformMatrix desired_matrix;          // +0x40
    TransformMatrix previous_desired_matrix; // +0x80
    Player* player;                          // +0xc0
    SubgameRuntime* game;                    // +0xc4
    float fov_degrees;                       // +0xc8
    unsigned char unresolved_cc;             // +0xcc
    char unknown_cd[3];
    float attachment_lift_envelope;          // +0xd0
    float smoothed_attachment_lift_envelope; // +0xd4
};

#endif
