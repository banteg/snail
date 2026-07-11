// initialize_completion_screen @ 0x404920 (thiscall, ret 0x8)

#include "completion.h"
#include "game_root.h"
#include <string.h>

void Completion::initialize_completion_screen(
    int new_delivered_count,
    unsigned char new_perfect_delivery)
{
    GameRoot* game = (GameRoot*)g_game_base;
    int mode = game->subgame.level_mode;

    if (mode == 0) {
        if (new_perfect_delivery != 0)
            bonus_score = 50000;
        else
            bonus_score = 0;
    } else if (mode == 1) {
        int x_source;
        int y_source;
        if (((GameRoot*)g_game_base)->subgame.replay_launch_active != 0) {
            SubSolution* record =
                ((GameRoot*)g_game_base)->subgame.replay_launch_record;
            x_source = record->challenge_speed_value;
            y_source = record->challenge_difficulty_value;
        } else {
            x_source = g_runtime_config.completion_bonus_x_source;
            y_source = g_runtime_config.completion_bonus_y_source;
        }

        int y_index = y_source / 20;
        int x_index = x_source / 20;
        if (y_index < 0)
            y_index = 0;
        else if (y_index > 5)
            y_index = 5;
        if (x_index < 0)
            x_index = 0;
        else if (x_index > 5)
            x_index = 5;
        if (y_index == 5 && x_index == 5)
            bonus_score = 500000;
        else
            bonus_score =
                g_completion_bonus_y_table[y_index] + g_completion_bonus_x_table[x_index];
    }

    int bonus = bonus_score;
    delivered_count = new_delivered_count;
    perfect_delivery = new_perfect_delivery;
    total_score = game->subgame.player.total_score + new_delivered_count * 100 + bonus;

    title_widget = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
    Color4f color;
    title_widget->initialize_frontend_widget(0x20400002, "Delivery Complete!",
        20, 0.0f, 80.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 0.0f);

    delivered_count_widget = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
    if (delivered_count == 1) {
        delivered_count_widget->initialize_frontend_widget(0x20400002,
            " 0 Package Delivered", 20, 0.0f, 160.0f,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 0.0f);
    } else {
        delivered_count_widget->initialize_frontend_widget(0x20400002,
            "00 Packages Delivered", 20, 0.0f, 160.0f,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 0.0f);
    }

    bonus_icon_widget = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
    bonus_icon_widget->initialize_frontend_sprite_button(0x400800, 122,
        100.0f, 146.0f,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, 4);
    bonus_icon_widget->warning_field = 0;

    bonus_summary_widget = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
    mode = game->subgame.level_mode;
    if (mode == 0) {
        bonus_summary_widget->initialize_frontend_widget(0x20400002,
            "PERFECT SCORE!>50,000 Bonus Points", 20, 0.0f, 302.0f,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 0.0f);
    } else if (mode == 1) {
        bonus_summary_widget->initialize_frontend_widget(0x20400002,
            "LEVEL COMPLETE!>", 20, 0.0f, 302.0f,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 0.0f);
        bonus_summary_widget->border_add_text_number(bonus_score);
        strcat(bonus_summary_widget->text_buffer, " Bonus Points");
    }
    bonus_summary_widget->hide_border_init();
    bonus_progress = 0.0f;
    bonus_progress_step = 0.041666668f;

    continue_widget = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
    float y;
    if (perfect_delivery != 0)
        y = 400.0f;
    else
        y = 320.0f;
    continue_widget->initialize_frontend_widget(0x20400002, g_click_to_continue_text,
        20, 0.0f, y,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 0.0f);
    continue_widget->hide_border_init();

    delivered_count_progress = 0;
    delivered_count_display = 0;
    continue_state = 1;
    delivered_count_progress_limit = 0.833333313f;
    continue_visible = 1;
    delivered_count_progress_step =
        1.0f / (3.4000001f / (float)(delivered_count + 1) * 60.0f);
}
