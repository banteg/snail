// initialize_challenge_setup_screen @ 0x415f50 (thiscall)

#include "border_manager.h"
#include "game_root.h"
#include "gui.h"
#include "frontend_widget_virtual_layout.h"
#include "sub_tracks.h"
#include "mouse_cursor_state.h"
#include "runtime_config.h"
#include "subgame_runtime.h"

extern GameRoot* g_game; // data_4df904
extern char g_back_text[]; // 0x4a20ec

void GUI::initialize_challenge_setup_screen()
{
    g_game->players[0].mouse_cursor.capture_mouse_cursor();
    game->level_definition.load_frontend_level_by_mode_and_index(
        game->level_mode,
        game->level_mode_arg);

    int mode = game->level_mode;
    --mode;
    if (mode != 0)
        return;

    tColour difficulty_color;
    tColour speed_color;
    tColour play_color;
    tColour replay_color;
    tColour back_color;

    difficulty_slider = g_game->border_manager.allocate_border();
    difficulty_slider->initialize_frontend_widget(
        FRONTEND_WIDGET_FLAG_SLIDER
            | FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED,
        "     Select Difficulty     >",
        0x14,
        20.0f,
        80.0f,
        difficulty_color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    difficulty_slider->slider_value =
        (float)g_runtime_config.completion_bonus_y_source * 0.0099999998f;
    difficulty_slider->slider_target_value = difficulty_slider->slider_value;
    ((FrontendWidgetVirtualLayout*)difficulty_slider)->layout_frontend_widget();

    speed_slider = g_game->border_manager.allocate_border();
    speed_slider->initialize_frontend_widget(
        FRONTEND_WIDGET_FLAG_SLIDER
            | FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED,
        "       Select Speed       >",
        0x14,
        20.0f,
        145.0f,
        speed_color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    speed_slider->slider_value =
        (float)g_runtime_config.completion_bonus_x_source * 0.0099999998f;
    speed_slider->slider_target_value = speed_slider->slider_value;
    speed_slider->stack_widget_below(difficulty_slider);
    ((FrontendWidgetVirtualLayout*)speed_slider)->layout_frontend_widget();

    float play_anchor_x = 0.0f;
    if (game->sub_high_score.survival_pending_record.active == 1)
        play_anchor_x = 100.0f;

    play_button = g_game->border_manager.allocate_border();
    play_button->initialize_frontend_widget(
        FRONTEND_WIDGET_FLAG_FADE_BEFORE_ACTION
            | FRONTEND_WIDGET_FLAG_HIGHLIGHTED
            | FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED
            | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
        "Play",
        0x14,
        20.0f,
        250.0f,
        play_color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        play_anchor_x);
    play_button->stack_widget_below(speed_slider);

    replay_button = g_game->border_manager.allocate_border();
    replay_button->initialize_frontend_widget(
        FRONTEND_WIDGET_FLAG_FADE_BEFORE_ACTION
            | FRONTEND_WIDGET_FLAG_HIGHLIGHTED
            | FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED
            | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
        "Watch Replay",
        0x14,
        20.0f,
        70.0f,
        replay_color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        -100.0f);
    replay_button->stack_widget_below(speed_slider);
    if (game->sub_high_score.survival_pending_record.active != 1)
        replay_button->hide_border_init();

    back_button = g_game->border_manager.allocate_border();
    back_button->initialize_frontend_widget(
        FRONTEND_WIDGET_FLAG_HIGHLIGHTED
            | FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED
            | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
        g_back_text,
        0x14,
        20.0f,
        20.0f,
        back_color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    back_button->stack_widget_below(replay_button);
}
