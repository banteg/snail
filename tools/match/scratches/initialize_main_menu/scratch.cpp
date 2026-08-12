// initialize_main_menu @ 0x419b50 (thiscall)

#include "backdrop.h"
#include "border_manager.h"
#include "game_root.h"
#include "landscape_manager.h"

extern char g_main_menu_music_path[]; // 0x4a2128
extern char g_menu_background_script_path[]; // 0x4a347c
extern char g_blank_text[]; // 0x4dfb08
extern char g_exit_text[]; // 0x4a20f4
extern char g_new_game_text[]; // 0x4a3b74
extern char g_high_scores_text[]; // 0x4a3b68
extern char g_options_text[]; // 0x4a3b60
extern char g_credits_text[]; // 0x4a3b58

char cache_music_file(char* path, int unused, char* unused_default_path); // @ 0x432d50

void cRMainMenu::Init()
{
    tColour color;

    g_game->star_manager.Hide();
    cache_music_file(g_main_menu_music_path, 0, g_blank_text);
    int script_index = g_game->subgame.landscape_manager
                           .Import(g_menu_background_script_path);
    g_game->backdrop.Change(
        &g_game->subgame.landscape_manager.scripts[script_index], 0);
    g_game->border_manager.SetJustifyCentre(25.0f);
    g_game->render_skip_countdown = 2;

    new_game_widget = g_game->border_manager.GetBorder();
    new_game_widget->Init(
        FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED
            | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
        g_new_game_text,
        0x14,
        20.0f,
        90.0f,
        color.Set(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);

    high_scores_widget = g_game->border_manager.GetBorder();
    high_scores_widget->Init(
        FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED
            | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
        g_high_scores_text,
        0x14,
        20.0f,
        20.0f,
        color.Set(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    high_scores_widget->SetBelow(new_game_widget);

    options_widget = g_game->border_manager.GetBorder();
    options_widget->Init(
        FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED
            | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
        g_options_text,
        0x14,
        20.0f,
        20.0f,
        color.Set(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    options_widget->SetBelow(high_scores_widget);

    options_widget = g_game->border_manager.GetBorder();
    options_widget->Init(
        FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED
            | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
        g_options_text,
        0x14,
        20.0f,
        20.0f,
        color.Set(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    options_widget->SetBelow(high_scores_widget);

    credits_widget = g_game->border_manager.GetBorder();
    credits_widget->Init(
        FRONTEND_WIDGET_FLAG_FADE_BEFORE_ACTION
            | FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED
            | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
        g_credits_text,
        0x14,
        20.0f,
        20.0f,
        color.Set(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    credits_widget->SetBelow(options_widget);

    exit_widget = g_game->border_manager.GetBorder();
    exit_widget->Init(
        FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED
            | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
        g_exit_text,
        0x14,
        20.0f,
        390.0f,
        color.Set(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    exit_widget->SetBelow(credits_widget);
}
