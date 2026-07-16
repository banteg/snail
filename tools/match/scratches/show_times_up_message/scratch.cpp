// show_times_up_message @ 0x445e90 (thiscall, ret)

#include "game_root.h"
#include "times_up.h"

extern GameRoot* g_game; // data_4df904

void TimesUp::show_times_up_message()
{
    if (state == TIMES_UP_STATE_INACTIVE) {
        tColour color;

        border = g_game->border_manager.allocate_border();
        border->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_FRAMELESS | FRONTEND_WIDGET_FLAG_HIGHLIGHTED,
            "Time's Up", 0x14, 0.0f, 200.0f,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 0.0299999993f), 2, 0.0f);
        progress = 0.0f;
        progress_step = 0.00555555569f;
        state = TIMES_UP_STATE_DISPLAYING;
    }
}
