// initialize_completion_screen @ 0x404920 (thiscall, ret 0x8)

#include "completion.h"
#include "game_root.h"
#include <string.h>


void Completion::initialize_completion_screen(
    int new_delivered_count,
    unsigned char new_perfect_delivery)
{
    int mode = g_game->subgame.level_mode;

    if (mode == 0) {
        if (new_perfect_delivery != 0)
            bonus_score = 50000;
        else
            bonus_score = 0;
    } else if (mode == 1) {
        int speed_source;
        int difficulty_index;
        if (g_game->subgame.replay_launch_active != 0) {
            SubSolution* record = g_game->subgame.replay_launch_record;
            difficulty_index = record->challenge_difficulty_value / 20;
            speed_source = record->challenge_speed_value;
        } else {
            difficulty_index =
                g_runtime_config.challenge_difficulty_percent / 20;
            speed_source = g_runtime_config.challenge_speed_percent;
        }

        speed_source /= 20;
        if (difficulty_index < 0)
            difficulty_index = 0;
        else if (difficulty_index > COMPLETION_BONUS_TABLE_CAPACITY - 1)
            difficulty_index = COMPLETION_BONUS_TABLE_CAPACITY - 1;
        if (speed_source < 0)
            speed_source = 0;
        else if (speed_source > COMPLETION_BONUS_TABLE_CAPACITY - 1)
            speed_source = COMPLETION_BONUS_TABLE_CAPACITY - 1;
        if (difficulty_index == COMPLETION_BONUS_TABLE_CAPACITY - 1
            && speed_source == COMPLETION_BONUS_TABLE_CAPACITY - 1)
            bonus_score = 500000;
        else
            bonus_score = g_completion_bonus_difficulty_table[difficulty_index]
                + g_completion_bonus_speed_table[speed_source];
    }

    int bonus = bonus_score;
    delivered_count = new_delivered_count;
    perfect_delivery = new_perfect_delivery;
    total_score = g_game->subgame.player.total_score
        + new_delivered_count * 100 + bonus;

    title_widget = g_game->border_manager.allocate_border();
    tColour color;
    title_widget->initialize_frontend_widget(
        FRONTEND_WIDGET_FLAG_ALLOW_OFFSCREEN | FRONTEND_WIDGET_FLAG_FRAMELESS
            | FRONTEND_WIDGET_FLAG_HIGHLIGHTED,
        "Delivery Complete!",
        20, 0.0f, 80.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 0.0f);

    delivered_count_widget = g_game->border_manager.allocate_border();
    if (delivered_count == 1) {
        delivered_count_widget->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_ALLOW_OFFSCREEN | FRONTEND_WIDGET_FLAG_FRAMELESS
                | FRONTEND_WIDGET_FLAG_HIGHLIGHTED,
            " 0 Package Delivered", 20, 0.0f, 160.0f,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 0.0f);
    } else {
        delivered_count_widget->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_ALLOW_OFFSCREEN | FRONTEND_WIDGET_FLAG_FRAMELESS
                | FRONTEND_WIDGET_FLAG_HIGHLIGHTED,
            "00 Packages Delivered", 20, 0.0f, 160.0f,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 0.0f);
    }

    bonus_icon_widget = g_game->border_manager.allocate_border();
    bonus_icon_widget->initialize_frontend_sprite_button(
        FRONTEND_WIDGET_FLAG_FRAMELESS | FRONTEND_WIDGET_FLAG_SPRITE_MODE, 122,
        100.0f, 146.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, 4);
    bonus_icon_widget->sprite_shadow_offset = 0.0f;

    bonus_summary_widget = g_game->border_manager.allocate_border();
    mode = g_game->subgame.level_mode;
    if (mode == 0) {
        bonus_summary_widget->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_ALLOW_OFFSCREEN | FRONTEND_WIDGET_FLAG_FRAMELESS
                | FRONTEND_WIDGET_FLAG_HIGHLIGHTED,
            "PERFECT SCORE!>50,000 Bonus Points", 20, 0.0f, 302.0f,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 0.0f);
    } else if (mode == 1) {
        bonus_summary_widget->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_ALLOW_OFFSCREEN | FRONTEND_WIDGET_FLAG_FRAMELESS
                | FRONTEND_WIDGET_FLAG_HIGHLIGHTED,
            "LEVEL COMPLETE!>", 20, 0.0f, 302.0f,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 0.0f);
        bonus_summary_widget->border_add_text_number(bonus_score);
        strcat(bonus_summary_widget->text_buffer, " Bonus Points");
    }
    bonus_summary_widget->hide_border_init();
    bonus_progress = 0.0f;
    bonus_progress_step = 0.041666668f;

    continue_widget = g_game->border_manager.allocate_border();
    if (perfect_delivery != 0) {
        continue_widget->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_ALLOW_OFFSCREEN | FRONTEND_WIDGET_FLAG_FRAMELESS
                | FRONTEND_WIDGET_FLAG_HIGHLIGHTED,
            g_click_to_continue_text, 20, 0.0f, 400.0f,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 0.0f);
    } else {
        continue_widget->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_ALLOW_OFFSCREEN | FRONTEND_WIDGET_FLAG_FRAMELESS
                | FRONTEND_WIDGET_FLAG_HIGHLIGHTED,
            g_click_to_continue_text, 20, 0.0f, 320.0f,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 0.0f);
    }
    continue_widget->hide_border_init();

    delivered_count_progress = 0;
    delivered_count_display = 0;
    continue_state = COMPLETION_STATE_STAGING_PARCELS;
    delivered_count_progress_limit = 0.833333313f;
    continue_visible = 1;
    delivered_count_progress_step =
        1.0f / (3.4000001f / (float)(delivered_count + 1) * 60.0f);
}
