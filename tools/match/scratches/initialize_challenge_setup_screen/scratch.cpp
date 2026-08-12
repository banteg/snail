// initialize_challenge_setup_screen @ 0x415f50 (thiscall)

#include "border_manager.h"
#include "game_root.h"
#include "gui.h"
#include "frontend_widget_virtual_layout.h"
#include "sub_tracks.h"
#include "mouse_cursor_state.h"
#include "runtime_config.h"
#include "subgame_runtime.h"

extern char g_back_text[]; // 0x4a20ec

void cRGUI::Init()
{
    g_game->players[0].mouse_cursor.SetActive();
    game->level_definition.load_frontend_level_by_mode_and_index(
        game->level_mode,
        game->level_mode_arg);

    switch (game->level_mode) {
    case 1:
        break;
    default:
        return;
    }

    tColour difficulty_color;
    tColour speed_color;
    tColour play_color;
    tColour replay_color;
    tColour back_color;

    difficulty_slider = g_game->border_manager.GetBorder();
    difficulty_slider->Init(
        FRONTEND_WIDGET_FLAG_SLIDER
            | FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED,
        "     Select Difficulty     >",
        0x14,
        20.0f,
        80.0f,
        difficulty_color.Set(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    difficulty_slider->slider_value =
        (float)g_runtime_config.challenge_difficulty_percent * 0.0099999998f;
    difficulty_slider->slider_target_value = difficulty_slider->slider_value;
    ((FrontendWidgetVirtualLayout*)difficulty_slider)->RePosition();

    speed_slider = g_game->border_manager.GetBorder();
    speed_slider->Init(
        FRONTEND_WIDGET_FLAG_SLIDER
            | FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED,
        "       Select Speed       >",
        0x14,
        20.0f,
        145.0f,
        speed_color.Set(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    speed_slider->slider_value =
        (float)g_runtime_config.challenge_speed_percent * 0.0099999998f;
    speed_slider->slider_target_value = speed_slider->slider_value;
    speed_slider->SetBelow(difficulty_slider);
    ((FrontendWidgetVirtualLayout*)speed_slider)->RePosition();

    float play_anchor_x = 0.0f;
    if (game->sub_high_score.survival_pending_record.active == 1)
        play_anchor_x = 100.0f;

    play_button = g_game->border_manager.GetBorder();
    play_button->Init(
        FRONTEND_WIDGET_FLAG_FADE_BEFORE_ACTION
            | FRONTEND_WIDGET_FLAG_HIGHLIGHTED
            | FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED
            | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
        "Play",
        0x14,
        20.0f,
        250.0f,
        play_color.Set(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        play_anchor_x);
    play_button->SetBelow(speed_slider);

    replay_button = g_game->border_manager.GetBorder();
    replay_button->Init(
        FRONTEND_WIDGET_FLAG_FADE_BEFORE_ACTION
            | FRONTEND_WIDGET_FLAG_HIGHLIGHTED
            | FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED
            | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
        "Watch Replay",
        0x14,
        20.0f,
        70.0f,
        replay_color.Set(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        -100.0f);
    replay_button->SetBelow(speed_slider);
    if (game->sub_high_score.survival_pending_record.active != 1)
        replay_button->HideInit();

    back_button = g_game->border_manager.GetBorder();
    back_button->Init(
        FRONTEND_WIDGET_FLAG_HIGHLIGHTED
            | FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED
            | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
        g_back_text,
        0x14,
        20.0f,
        20.0f,
        back_color.Set(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    back_button->SetBelow(replay_button);
}
