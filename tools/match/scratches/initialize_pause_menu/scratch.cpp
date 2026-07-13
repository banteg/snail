// initialize_pause_menu @ 0x440660 (thiscall, ret)

#include "border_manager.h"
#include "game_root.h"
#include "pause_menu.h"
#include "mouse_cursor_state.h"

extern GameRoot* g_game; // data_4df904
extern char g_resume_text[]; // 0x4a4f2c
extern char g_end_game_text[]; // 0x4a4f34
extern char g_options_text[]; // 0x4a3b60

void PauseMenu::initialize_pause_menu()
{
    Color4f color;

    end_game_widget = g_game->border_manager.allocate_border();
    end_game_widget->initialize_frontend_widget(
        0x14, g_end_game_text, 0x14, 0.0f, 145.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 0.0f);
    end_game_widget->set_frontend_widget_shortcut_key(11);

    options_widget = g_game->border_manager.allocate_border();
    options_widget->initialize_frontend_widget(
        0x14, g_options_text, 0x14, 0.0f, 190.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 0.029999999f), 2, 0.0f);
    options_widget->set_frontend_widget_shortcut_key(111);
    options_widget->layout_frontend_widget();
    options_widget->stack_widget_below(end_game_widget);

    resume_widget = g_game->border_manager.allocate_border();
    resume_widget->initialize_frontend_widget(
        0x14, g_resume_text, 0x14, 0.0f, 320.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 0.0f);
    resume_widget->set_frontend_widget_shortcut_key(5);
    resume_widget->stack_widget_below(options_widget);

    g_game->players[0].mouse_cursor.capture_mouse_cursor();
}
