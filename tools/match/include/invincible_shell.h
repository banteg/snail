// Invincibility shell controller view, partial.
#ifndef INVINCIBLE_SHELL_H
#define INVINCIBLE_SHELL_H

#include "sprite.h"
#include "transform_matrix.h"

class InvincibleShellController {
public:
    void initialize_invincible_shell(); // @ 0x444ac0
    void start_invincible_shell(); // @ 0x444ae0
    void update_invincible_shell(); // @ 0x444b50

    // BOD-node-compatible prefix linked by build_subgame_level. The shell
    // remains embedded in PlayerPresentationController.
    char unknown_00[0x28];
    Color4f color; // +0x28
    TransformMatrix transform; // +0x38, copied from the live snail matrix then yaw-spun
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

typedef char InvincibleShellController_must_be_0xa4[
    (sizeof(InvincibleShellController) == 0xa4) ? 1 : -1];

#endif
