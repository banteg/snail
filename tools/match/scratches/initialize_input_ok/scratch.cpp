// initialize_input_ok @ 0x403560 (thiscall)

#include "border_manager.h"
#include "game_root.h"
#include "input_ok_state.h"

extern GameRoot* g_game; // data_4df904

void InputOkState::initialize_input_ok()
{
    FrontendWidget* widget =
        g_game->border_manager.allocate_border();
    FrontendWidget* source = source_widget;
    ok_widget = widget;
    widget->initialize_frontend_widget(
        0x14,
        "OK",
        source->widget_type,
        0.0f,
        0.0f,
        &source->idle_fill_color,
        0,
        0.0f);
    update_input_ok();
}
