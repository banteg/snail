// Authored cRInvincible, exact 0xa4-byte spinning shell visual owner.
#ifndef INVINCIBLE_H
#define INVINCIBLE_H

#include "sprite.h"
#include "transform_matrix.h"

class Invincible {
public:
    void initialize_invincible_shell(); // @ 0x444ac0, cRInvincible::Init
    void start_invincible_shell(); // @ 0x444ae0, cRInvincible::Start
    void update_invincible_shell(); // @ 0x444b50, cRInvincible::AI

    // BOD-node-compatible prefix linked by build_subgame_level. The owner
    // remains embedded in the authored Snail owner.
    void* vtable; // +0x00, update_invincible_shell callback
    char unknown_04[0x28 - 0x04];
    Color4f color; // +0x28
    TransformMatrix transform; // +0x38, live snail matrix followed by yaw spin
    char unknown_78[0x80 - 0x78];
    int state; // +0x80
    float spin_phase; // +0x84
    float spin_phase_step; // +0x88
    float fade_progress; // +0x8c
    float fade_step; // +0x90
    char unknown_94[0x98 - 0x94];
    float cutscene_roll_progress; // +0x98
    float cutscene_roll_step; // +0x9c
    unsigned char channel_release_steps_active; // +0xa0
    char unknown_a1[0xa4 - 0xa1];
};

typedef char Invincible_must_be_0xa4[(sizeof(Invincible) == 0xa4) ? 1 : -1];

#endif
