// initialize_main_menu @ 0x419b50 (thiscall)

#include "backdrop.h"
#include "border_runtime.h"
#include "completion_screen.h"
#include "landscape_script_bank.h"

extern char* g_game_base; // data_4df904
extern char g_main_menu_music_path[]; // 0x4a2128
extern char g_menu_background_script_path[]; // 0x4a347c
extern char g_blank_text[]; // 0x4dfb08
extern char g_exit_text[]; // 0x4a20f4
extern char g_new_game_text[]; // 0x4a3b74
extern char g_high_scores_text[]; // 0x4a3b68
extern char g_options_text[]; // 0x4a3b60
extern char g_credits_text[]; // 0x4a3b58

char cache_music_file(char* path, int unused, char* unused_default_path); // @ 0x432d50

void MainMenu::initialize_main_menu()
{
    Color4f color;

    ((CompletionGameView*)g_game_base)->star_field.hide_star_field();
    cache_music_file(g_main_menu_music_path, 0, g_blank_text);
    int script_index =
        ((LandscapeScriptBank*)(g_game_base + 0x106c218))
            ->load_landscape_script_by_name(g_menu_background_script_path);
    ((Backdrop*)(g_game_base + 0x4ec10))
        ->change_backdrop(
            (LandscapeScriptRecord*)(g_game_base + 0x106c7bc +
                script_index * sizeof(LandscapeScriptRecord)),
            0);
    ((BorderRuntime*)(g_game_base + 0xb4c))->set_border_justify_centre(0x41c80000);
    ((CompletionGameView*)g_game_base)->render_skip_countdown = 2;

    new_game_widget = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
    new_game_widget->initialize_frontend_widget(
        0x14,
        g_new_game_text,
        0x14,
        20.0f,
        90.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);

    high_scores_widget = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
    high_scores_widget->initialize_frontend_widget(
        0x14,
        g_high_scores_text,
        0x14,
        20.0f,
        20.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    high_scores_widget->stack_widget_below(new_game_widget);

    options_widget = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
    options_widget->initialize_frontend_widget(
        0x14,
        g_options_text,
        0x14,
        20.0f,
        20.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    options_widget->stack_widget_below(high_scores_widget);

    options_widget = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
    options_widget->initialize_frontend_widget(
        0x14,
        g_options_text,
        0x14,
        20.0f,
        20.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    options_widget->stack_widget_below(high_scores_widget);

    credits_widget = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
    credits_widget->initialize_frontend_widget(
        0x40000014,
        g_credits_text,
        0x14,
        20.0f,
        20.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    credits_widget->stack_widget_below(options_widget);

    exit_widget = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
    exit_widget->initialize_frontend_widget(
        0x14,
        g_exit_text,
        0x14,
        20.0f,
        390.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    exit_widget->stack_widget_below(credits_widget);
}
