// initialize_warning @ 0x446e80 (thiscall, ret)

#include "sprite.h"

extern char* g_game_base; // data_4df904

struct FrontendWidget {
    void initialize_frontend_sprite_button(int flags, int sprite, float x, float y,
        Color4f* color, float z, int layer);
    void hide_border_init();

    char unknown_00[0x178];
    int warning_field; // +0x178
};

struct BorderManager {
    FrontendWidget* allocate_border();
};

class WarningActor {
public:
    void initialize_warning();

    int state;                 // +0x00
    float progress;            // +0x04
    float progress_step;       // +0x08
    FrontendWidget* border;    // +0x0c
};

void WarningActor::initialize_warning()
{
    Color4f color;

    border = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
    border->initialize_frontend_sprite_button(0x400802, 0x5e, 288.0f, 64.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 0.999000013f), 0.0f, 4);
    border->warning_field = 0;
    border->hide_border_init();
    progress_step = 0.0833333358f;
    progress = 0.0f;
    state = 0;
}
