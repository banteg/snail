// initialize_invincible_shell @ 0x444ac0 (thiscall, ret)
#include "snail_skin.h"

extern char* g_game_base; // data_4df904

class InvincibleShellController {
public:
    void initialize_invincible_shell();

    char unknown_00[0x80];
    int state;                 // +0x80
    float spin_phase;          // +0x84
    float spin_phase_step;     // +0x88
    float fade_progress;       // +0x8c
    float fade_step;           // +0x90
};

void InvincibleShellController::initialize_invincible_shell()
{
    state = 0;
    ((SnailSkinTransition*)(g_game_base + 0x434038))->change_snail_skin(0, 0.0f);
}
