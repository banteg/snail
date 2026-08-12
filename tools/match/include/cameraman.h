// Authored cRCameraman, exact 0xd8-byte follow-camera owner.
#ifndef CAMERAMAN_H
#define CAMERAMAN_H

#include "player_fwd.h"
#include "transform_matrix.h"

class cRSubGame;

class cRCameraman {
public:
    // VC6 folds this empty owner constructor into the shared body at
    // 0x408600. The cRSubGame constructor passes cRSubGoldy::cameraman exactly.
    cRCameraman* noop_runtime_slot_constructor();
    void initialize_cameraman(); // @ 0x446160, cRCameraman::Init
    void update_cameraman(); // @ 0x4461d0, cRCameraman::AI

    TransformMatrix live_matrix; // +0x00
    TransformMatrix desired_matrix; // +0x40
    TransformMatrix previous_desired_matrix; // +0x80
    cRSubGoldy* player; // +0xc0
    cRSubGame* game; // +0xc4, non-owning backlink
    float fov_degrees; // +0xc8
    unsigned char force_camera_update; // +0xcc, copied into the subgame camera snap gate
    char unknown_cd[3];
    float attachment_lift_envelope; // +0xd0
    float smoothed_attachment_lift_envelope; // +0xd4
};

typedef cRCameraman Cameraman;
typedef char Cameraman_must_be_0xd8[(sizeof(cRCameraman) == 0xd8) ? 1 : -1];

#endif
