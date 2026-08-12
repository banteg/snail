// cRInputOK::Init @ 0x403560 (thiscall)

#include "border_manager.h"
#include "game_root.h"
#include "input_ok_state.h"


void cRInputOK::Init()
{
    cRBorder* widget =
        g_game->border_manager.GetBorder();
    cRBorder* source = source_widget;
    ok_widget = widget;
    widget->initialize_frontend_widget(
        FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED
            | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
        "OK",
        source->widget_type,
        0.0f,
        0.0f,
        &source->idle_fill_color,
        0,
        0.0f);
    AI();
}
