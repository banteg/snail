// initialize_warning @ 0x446e80 (thiscall, ret)

#include "game_root.h"
#include "warning.h"


void cRWarning::Init()
{
    tColour color;

    border = g_game->border_manager.GetBorder();
    border->Init(
        FRONTEND_WIDGET_FLAG_FRAMELESS | FRONTEND_WIDGET_FLAG_SPRITE_MODE
            | FRONTEND_WIDGET_FLAG_HIGHLIGHTED,
        0x5e, 288.0f, 64.0f,
        color.Set(1.0f, 1.0f, 1.0f, 0.999000013f), 0.0f, 4);
    border->sprite_shadow_offset = 0.0f;
    border->hide_border_init();
    phase_step = 0.0833333358f;
    phase = 0.0f;
    state = WARNING_STATE_INACTIVE;
}
