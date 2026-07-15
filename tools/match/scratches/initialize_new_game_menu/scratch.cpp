// initialize_new_game_menu @ 0x417bc0 (thiscall)

#include "backdrop.h"
#include "border_manager.h"
#include "game_root.h"
#include "landscape_manager.h"

extern GameRoot* g_game; // data_4df904
extern char g_main_menu_music_path[]; // 0x4a2128
extern char g_menu_background_script_path[]; // 0x4a347c
extern char g_blank_text[]; // 0x4dfb08
extern char g_help_text[]; // 0x4a38b4
extern char g_challenge_mode_text[]; // 0x4a38bc
extern char g_time_trial_text[]; // 0x4a38cc
extern char g_postal_mode_text[]; // 0x4a38d8
extern char g_tutorial_text[]; // 0x4a38e4
extern char g_back_text[]; // 0x4a20ec

char cache_music_file(char* path, int unused, char* unused_default_path); // @ 0x432d50

void Intro::initialize_new_game_menu()
{
    tColour color;

    g_game->star_manager.hide_star_field();
    cache_music_file(g_main_menu_music_path, 0, g_blank_text);
    int script_index = g_game->subgame.landscape_manager
                           .load_landscape_script_by_name(g_menu_background_script_path);
    g_game->backdrop.change_backdrop(
        &g_game->subgame.landscape_manager.scripts[script_index], 0);
    g_game->border_manager.set_border_justify_centre(25.0f);
    g_game->render_skip_countdown = 2;

    tutorial_button = g_game->border_manager.allocate_border();
    tutorial_button->initialize_frontend_widget(
        0x40000014,
        g_tutorial_text,
        0x14,
        20.0f,
        80.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);

    postal_button = g_game->border_manager.allocate_border();
    postal_button->initialize_frontend_widget(
        0x40000014,
        g_postal_mode_text,
        0x14,
        20.0f,
        20.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    postal_button->stack_widget_below(tutorial_button);

    time_trial_button = g_game->border_manager.allocate_border();
    time_trial_button->initialize_frontend_widget(
        0x40000014,
        g_time_trial_text,
        0x14,
        20.0f,
        20.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    time_trial_button->stack_widget_below(postal_button);

    challenge_button = g_game->border_manager.allocate_border();
    challenge_button->initialize_frontend_widget(
        0x14,
        g_challenge_mode_text,
        0x14,
        20.0f,
        20.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    challenge_button->stack_widget_below(time_trial_button);

    help_button = g_game->border_manager.allocate_border();
    help_button->initialize_frontend_widget(
        0x40000014,
        g_help_text,
        0x14,
        0.0f,
        350.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        -220.0f);

    back_button = g_game->border_manager.allocate_border();
    back_button->initialize_frontend_widget(
        0x14,
        g_back_text,
        0x14,
        20.0f,
        350.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    back_button->stack_widget_below(challenge_button);

    if (g_runtime_config.new_game_tutorial_started == 0) {
        postal_button->widget_flags |= FRONTEND_WIDGET_FLAG_DISABLED;
        time_trial_button->widget_flags |= FRONTEND_WIDGET_FLAG_DISABLED;
        challenge_button->widget_flags |= FRONTEND_WIDGET_FLAG_DISABLED;
    }
}
