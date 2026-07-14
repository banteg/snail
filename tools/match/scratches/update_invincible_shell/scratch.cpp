// update_invincible_shell @ 0x444b50 (thiscall, ret)
// Fade/spin controller for the invincible snail-shell presentation.

#include "game_root.h"
#include "invincible.h"
#include "snail_skin.h"

extern GameRoot* g_game; // data_4df904

void Invincible::update_invincible_shell()
{
    switch (state) {
    case 0:
        if ((g_game->subgame.player.movement_flags & 0x80) != 0) {
            start_invincible_shell();
        } else {
            g_game->subgame.player.presentation.invincible_shell.list_flags &=
                0xffffffdf;
        }
        return;

    case 1:
        fade_progress += fade_step;
        if (fade_progress > 1.0f) {
            fade_progress = 1.0f;
            state = 2;
        }
        if ((g_game->subgame.player.movement_flags & 0x80) == 0)
            state = 3;
        break;

    case 2:
        if ((g_game->subgame.player.movement_flags & 0x80) == 0)
            state = 3;
        break;

    case 3:
        fade_progress -= fade_step;
        if (fade_progress < 0.0f) {
            fade_progress = 0.0f;
            state = 0;
            g_game->subgame.player.presentation.snail_skin.change_snail_skin(
                0, 0.0f);
            return;
        }
        if ((g_game->subgame.player.movement_flags & 0x80) != 0)
            state = 1;
        break;
    }

    spin_phase += spin_phase_step;
    if (spin_phase > 1.0f)
        spin_phase -= 1.0f;

    g_game->subgame.player.presentation.snail_skin.change_snail_skin(2, 0.0f);
    color.set_color_white();
    color.a = fade_progress * 0.80000001f;

    float angle = spin_phase * 6.2831855f;
    transform = g_game->subgame.player.presentation.live_matrix;
    transform.rotate_matrix_world_y(angle);
}
