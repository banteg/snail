// update_invincible_shell @ 0x444b50 (thiscall, ret)
// Fade/spin controller for the invincible snail-shell presentation.

#include "game_root.h"
#include "invincible.h"
#include "snail_skin.h"

extern GameRoot* g_game; // data_4df904

void Invincible::update_invincible_shell()
{
    switch (state) {
    case INVINCIBLE_STATE_INACTIVE:
        if ((g_game->subgame.player.movement_flags & 0x80) != 0) {
            start_invincible_shell();
        } else {
            g_game->subgame.player.presentation.invincible_shell.list_flags &=
                0xffffffdf;
        }
        return;

    case INVINCIBLE_STATE_FADING_IN:
        fade_progress += fade_step;
        if (fade_progress > 1.0f) {
            fade_progress = 1.0f;
            state = INVINCIBLE_STATE_ACTIVE;
        }
        if ((g_game->subgame.player.movement_flags & 0x80) == 0)
            state = INVINCIBLE_STATE_FADING_OUT;
        break;

    case INVINCIBLE_STATE_ACTIVE:
        if ((g_game->subgame.player.movement_flags & 0x80) == 0)
            state = INVINCIBLE_STATE_FADING_OUT;
        break;

    case INVINCIBLE_STATE_FADING_OUT:
        fade_progress -= fade_step;
        if (fade_progress < 0.0f) {
            fade_progress = 0.0f;
            state = INVINCIBLE_STATE_INACTIVE;
            g_game->subgame.player.presentation.snail_skin.change_snail_skin(
                SNAIL_SKIN_SLOT_DEFAULT, 0.0f);
            return;
        }
        if ((g_game->subgame.player.movement_flags & 0x80) != 0)
            state = INVINCIBLE_STATE_FADING_IN;
        break;
    }

    spin_phase += spin_phase_step;
    if (spin_phase > 1.0f)
        spin_phase -= 1.0f;

    g_game->subgame.player.presentation.snail_skin.change_snail_skin(
        SNAIL_SKIN_SLOT_INVINCIBLE, 0.0f);
    color.set_color_white();
    color.a = fade_progress * 0.80000001f;

    float angle = spin_phase * 6.2831855f;
    transform = g_game->subgame.player.presentation.transform;
    transform.rotate_matrix_local_y(angle);
}
