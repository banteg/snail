// initialize_warning @ 0x446e80 (thiscall, ret)

#include "game_root.h"
#include "warning.h"

extern GameRoot* g_game; // data_4df904

void Warning::initialize_warning()
{
    tColour color;

    border = g_game->border_manager.allocate_border();
    border->initialize_frontend_sprite_button(0x400802, 0x5e, 288.0f, 64.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 0.999000013f), 0.0f, 4);
    border->sprite_shadow_offset = 0.0f;
    border->hide_border_init();
    phase_step = 0.0833333358f;
    phase = 0.0f;
    state = WARNING_STATE_INACTIVE;
}
