// show_times_up_message @ 0x445e90 (thiscall, ret)

#include "times_up_controller.h"

extern char* g_game_base; // data_4df904

struct BorderManager {
    FrontendWidget* allocate_border();
};

void TimesUpController::show_times_up_message()
{
    if (state == 0) {
        Color4f color;

        border = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
        border->initialize_frontend_widget(0x400002, "Time's Up", 0x14, 0.0f, 200.0f,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 0.0299999993f), 2, 0.0f);
        progress = 0.0f;
        progress_step = 0.00555555569f;
        state = 1;
    }
}
