// initialize_warning @ 0x446e80 (thiscall, ret)

#include "warning_actor.h"

extern char* g_game_base; // data_4df904

struct BorderManager {
    FrontendWidget* allocate_border();
};

void WarningActor::initialize_warning()
{
    Color4f color;

    border = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
    border->initialize_frontend_sprite_button(0x400802, 0x5e, 288.0f, 64.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 0.999000013f), 0.0f, 4);
    border->warning_field = 0;
    border->hide_border_init();
    phase_step = 0.0833333358f;
    phase = 0.0f;
    state = 0;
}
