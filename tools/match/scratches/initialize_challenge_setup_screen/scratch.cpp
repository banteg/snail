// initialize_challenge_setup_screen @ 0x415f50 (thiscall)

#include "border_manager.h"
#include "challenge_setup_screen.h"
#include "frontend_widget_virtual_layout.h"
#include "level_definition_loader.h"
#include "mouse_cursor_state.h"

extern char* g_game_base; // data_4df904
extern int g_completion_bonus_x_source; // data_4df958
extern int g_completion_bonus_y_source; // data_4df960
extern char g_back_text[]; // 0x4a20ec

int ChallengeSetupScreen::initialize_challenge_setup_screen()
{
    ((MouseCursorState*)(g_game_base + 0x290))->capture_mouse_cursor();
    ((LevelDefinitionLoader*)game->level_definition_loader_storage)
        ->load_frontend_level_by_mode_and_index(
            game->selected_subgame_mode,
            game->selected_level_index);

    int mode = game->selected_subgame_mode;
    --mode;
    if (mode != 0)
        return mode;

    Color4f difficulty_color;
    Color4f speed_color;
    Color4f play_color;
    Color4f replay_color;
    Color4f back_color;

    difficulty_slider = (FrontendWidget*)((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
    difficulty_slider->initialize_frontend_widget(
        0x100004,
        "     Select Difficulty     >",
        0x14,
        20.0f,
        80.0f,
        difficulty_color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    difficulty_slider->slider_value = (float)g_completion_bonus_y_source * 0.0099999998f;
    difficulty_slider->slider_target_value = difficulty_slider->slider_value;
    ((FrontendWidgetVirtualLayout*)difficulty_slider)->layout_frontend_widget();

    speed_slider = (FrontendWidget*)((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
    speed_slider->initialize_frontend_widget(
        0x100004,
        "       Select Speed       >",
        0x14,
        20.0f,
        145.0f,
        speed_color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    speed_slider->slider_value = (float)g_completion_bonus_x_source * 0.0099999998f;
    speed_slider->slider_target_value = speed_slider->slider_value;
    speed_slider->stack_widget_below(difficulty_slider);
    ((FrontendWidgetVirtualLayout*)speed_slider)->layout_frontend_widget();

    float play_anchor_x = 0.0f;
    if (game->selected_replay_available == 1)
        play_anchor_x = 100.0f;

    play_button = (FrontendWidget*)((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
    play_button->initialize_frontend_widget(
        0x40000016,
        "Play",
        0x14,
        20.0f,
        250.0f,
        play_color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        play_anchor_x);
    play_button->stack_widget_below(speed_slider);

    replay_button = (FrontendWidget*)((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
    replay_button->initialize_frontend_widget(
        0x40000016,
        "Watch Replay",
        0x14,
        20.0f,
        70.0f,
        replay_color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        -100.0f);
    replay_button->stack_widget_below(speed_slider);
    if (game->selected_replay_available != 1)
        replay_button->hide_border_init();

    back_button = (FrontendWidget*)((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
    back_button->initialize_frontend_widget(
        0x16,
        g_back_text,
        0x14,
        20.0f,
        20.0f,
        back_color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    return (int)back_button->stack_widget_below(replay_button);
}
