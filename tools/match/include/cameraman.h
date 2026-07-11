// Authored cRCameraman, exact 0xd8-byte follow-camera owner.
#ifndef CAMERAMAN_H
#define CAMERAMAN_H

#include "transform_matrix.h"

class Player;
class SubgameRuntime;

class Cameraman {
public:
    void initialize_cameraman(); // @ 0x446160, cRCameraman::Init
    void update_cameraman(); // @ 0x4461d0, cRCameraman::AI

    TransformMatrix live_matrix; // +0x00
    TransformMatrix desired_matrix; // +0x40
    TransformMatrix previous_desired_matrix; // +0x80
    Player* player; // +0xc0
    SubgameRuntime* game; // +0xc4, non-owning backlink
    float fov_degrees; // +0xc8
    unsigned char unresolved_cc; // +0xcc
    char unknown_cd[3];
    float attachment_lift_envelope; // +0xd0
    float smoothed_attachment_lift_envelope; // +0xd4
};

typedef char Cameraman_must_be_0xd8[(sizeof(Cameraman) == 0xd8) ? 1 : -1];

#endif
