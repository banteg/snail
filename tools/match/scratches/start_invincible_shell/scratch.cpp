// start_invincible_shell @ 0x444ae0 (thiscall, ret)

#include "audio_system.h"
#include "invincible_shell.h"

extern char* g_game_base; // data_4df904

void InvincibleShellController::start_invincible_shell()
{
    int current_state = state;
    if (current_state != 0) {
        if (current_state == 3) {
            state = 1;
        }
        return;
    }

    state = 1;
    spin_phase = 0.0f;
    spin_phase_step = 0.0333333351f;
    fade_progress = 0.0f;
    fade_step = 0.0333333351f;
    *(unsigned int*)(g_game_base + 0x433f98) |= 0x20;
    g_audio_backend.play_registered_sound_sample_scaled(0x30, 1.0f);
}
