// initialize_new_game_menu @ 0x417bc0 (thiscall)

#include "backdrop.h"
#include "border_runtime.h"
#include "game_root.h"
#include "landscape_script_bank.h"

extern char* g_game_base; // data_4df904
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

class NewGameBorderManager {
public:
    FrontendWidget* allocate_border();
};

void NewGameMenu::initialize_new_game_menu()
{
    Color4f color;

    ((GameRoot*)g_game_base)->star_field.hide_star_field();
    cache_music_file(g_main_menu_music_path, 0, g_blank_text);
    int script_index =
        ((LandscapeScriptBank*)(g_game_base + 0x106c218))
            ->load_landscape_script_by_name(g_menu_background_script_path);
    ((Backdrop*)(g_game_base + 0x4ec10))
        ->change_backdrop(
            (LandscapeScriptRecord*)(g_game_base + 0x106c7bc +
                script_index * sizeof(LandscapeScriptRecord)),
            0);
    ((BorderRuntime*)(g_game_base + 0xb4c))
        ->set_border_justify_centre(0x41c80000);
    ((GameRoot*)g_game_base)->render_skip_countdown = 2;

    tutorial_button = ((NewGameBorderManager*)(g_game_base + 0xb4c))->allocate_border();
    tutorial_button->initialize_frontend_widget(
        0x40000014,
        g_tutorial_text,
        0x14,
        20.0f,
        80.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);

    postal_button = ((NewGameBorderManager*)(g_game_base + 0xb4c))->allocate_border();
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

    time_trial_button = ((NewGameBorderManager*)(g_game_base + 0xb4c))->allocate_border();
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

    challenge_button = ((NewGameBorderManager*)(g_game_base + 0xb4c))->allocate_border();
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

    help_button = ((NewGameBorderManager*)(g_game_base + 0xb4c))->allocate_border();
    help_button->initialize_frontend_widget(
        0x40000014,
        g_help_text,
        0x14,
        0.0f,
        350.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        -220.0f);

    back_button = ((NewGameBorderManager*)(g_game_base + 0xb4c))->allocate_border();
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

    if (g_new_game_tutorial_started == 0) {
        postal_button->widget_flags |= 0x8000;
        time_trial_button->widget_flags |= 0x8000;
        challenge_button->widget_flags |= 0x8000;
    }
}
