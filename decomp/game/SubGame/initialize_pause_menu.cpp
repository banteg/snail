// initialize_pause_menu @ 0x440660 (thiscall, ret)

#include "border_manager.h"
#include "game_root.h"
#include "pause_menu.h"
#include "mouse_cursor_state.h"

extern char g_resume_text[]; // 0x4a4f2c
extern char g_end_game_text[]; // 0x4a4f34
extern char g_options_text[]; // 0x4a3b60

void cRSubPause::Init()
{
    tColour color;

    end_game_widget = g_game->border_manager.GetBorder();
    end_game_widget->Init(
        FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED
            | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
        g_end_game_text, 0x14, 0.0f, 145.0f,
        color.Set(1.0f, 1.0f, 1.0f, 1.0f), 2, 0.0f);
    end_game_widget->SetKeyLeft(11);

    options_widget = g_game->border_manager.GetBorder();
    options_widget->Init(
        FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED
            | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
        g_options_text, 0x14, 0.0f, 190.0f,
        color.Set(1.0f, 1.0f, 1.0f, 0.029999999f), 2, 0.0f);
    options_widget->SetKeyLeft(111);
    options_widget->RePosition();
    options_widget->SetBelow(end_game_widget);

    resume_widget = g_game->border_manager.GetBorder();
    resume_widget->Init(
        FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED
            | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
        g_resume_text, 0x14, 0.0f, 320.0f,
        color.Set(1.0f, 1.0f, 1.0f, 1.0f), 2, 0.0f);
    resume_widget->SetKeyLeft(5);
    resume_widget->SetBelow(options_widget);

    g_game->players[0].mouse_cursor.SetActive();
}
