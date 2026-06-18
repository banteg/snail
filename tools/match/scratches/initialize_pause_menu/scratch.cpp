// initialize_pause_menu @ 0x440660 (thiscall, ret)

#include "completion_screen.h"
#include "mouse_cursor_state.h"

extern char* g_game_base; // data_4df904

void PauseMenu::initialize_pause_menu()
{
    Color4f color;

    end_game_widget = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
    end_game_widget->initialize_frontend_widget(
        0x14, "End Game", 0x14, 0.0f, 145.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 0.0f);
    end_game_widget->set_frontend_widget_shortcut_key(11);

    options_widget = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
    options_widget->initialize_frontend_widget(
        0x14, "Options", 0x14, 0.0f, 190.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 0.029999999f), 2, 0.0f);
    options_widget->set_frontend_widget_shortcut_key(111);
    options_widget->layout_frontend_widget();
    options_widget->stack_widget_below(end_game_widget);

    resume_widget = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
    resume_widget->initialize_frontend_widget(
        0x14, "Resume", 0x14, 0.0f, 320.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 0.0f);
    resume_widget->set_frontend_widget_shortcut_key(5);
    resume_widget->stack_widget_below(options_widget);

    ((MouseCursorState*)(g_game_base + 0x290))->capture_mouse_cursor();
}
