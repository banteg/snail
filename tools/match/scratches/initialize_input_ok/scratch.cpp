// initialize_input_ok @ 0x403560 (thiscall)

#include "border_manager.h"
#include "input_ok_state.h"

extern char* g_game_base; // data_4df904

FrontendWidget* InputOkState::initialize_input_ok()
{
    FrontendWidget* widget =
        (FrontendWidget*)((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
    FrontendWidget* source = source_widget;
    ok_widget = widget;
    widget->initialize_frontend_widget(
        0x14,
        "OK",
        *(int*)((char*)source + 0x7c),
        0.0f,
        0.0f,
        (Color4f*)((char*)source + 0x1bc),
        0,
        0.0f);
    return update_input_ok();
}
