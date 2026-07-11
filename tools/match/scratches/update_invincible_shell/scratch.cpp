// update_invincible_shell @ 0x444b50 (thiscall, ret)
// Fade/spin controller for the invincible snail-shell presentation.

#include "invincible.h"
#include "snail_skin.h"

extern char* g_game_base; // data_4df904

void Invincible::update_invincible_shell()
{
    switch (state) {
    case 0:
        if ((*(unsigned int*)(g_game_base + 0x4300b4) & 0x80) != 0) {
            start_invincible_shell();
        } else {
            *(unsigned int*)(g_game_base + 0x433f98) &= 0xffffffdf;
        }
        return;

    case 1:
        fade_progress += fade_step;
        if (fade_progress > 1.0f) {
            fade_progress = 1.0f;
            state = 2;
        }
        if ((*(unsigned int*)(g_game_base + 0x4300b4) & 0x80) == 0)
            state = 3;
        break;

    case 2:
        if ((*(unsigned int*)(g_game_base + 0x4300b4) & 0x80) == 0)
            state = 3;
        break;

    case 3:
        fade_progress -= fade_step;
        if (fade_progress < 0.0f) {
            fade_progress = 0.0f;
            state = 0;
            ((SnailSkin*)(g_game_base + 0x434038))->change_snail_skin(0, 0.0f);
            return;
        }
        if ((*(unsigned int*)(g_game_base + 0x4300b4) & 0x80) != 0)
            state = 1;
        break;
    }

    spin_phase += spin_phase_step;
    if (spin_phase > 1.0f)
        spin_phase -= 1.0f;

    ((SnailSkin*)(g_game_base + 0x434038))->change_snail_skin(2, 0.0f);
    color.set_color_white();
    color.a = fade_progress * 0.80000001f;

    float angle = spin_phase * 6.2831855f;
    transform = *(TransformMatrix*)(g_game_base + 0x432738);
    transform.rotate_matrix_world_y(angle);
}
