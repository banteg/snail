// update_new_game_menu @ 0x417eb0 (thiscall, ret)

#include "game_root.h"
#include "new_game_menu.h"


void Intro::update_new_game_menu()
{
    unsigned int flags;

    if (read_pressed_text_input_key_code() != 0
        || (g_game->players[0].game_input->input.pressed_buttons
                & INPUT_BUTTON_PRIMARY)
            != 0) {
        replay_probe_progress = 0.0f;
        if (hide_for_replay_latch == 1) {
            postal_button->unhide_border_init();
            tutorial_button->unhide_border_init();
            time_trial_button->unhide_border_init();
            challenge_button->unhide_border_init();
            help_button->unhide_border_init();
            back_button->unhide_border_init();
            g_game->players[0].mouse_cursor.capture_mouse_cursor();
            hide_for_replay_latch = 0;
        }
    }

    flags = postal_button->widget_flags;
    if ((flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
        postal_button->widget_flags =
            flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
        destroy_new_game_menu();
        g_game->players[0].frontend_state = 10;
        g_game->players[0].redispatch_requested = 1;
        g_game->subgame.level_mode = 0;
        g_game->subgame.subgame_rebuild_selector = 2;
        return;
    }

    flags = time_trial_button->widget_flags;
    if ((flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
        time_trial_button->widget_flags =
            flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
        destroy_new_game_menu();
        g_game->players[0].frontend_state = 10;
        g_game->players[0].redispatch_requested = 1;
        g_game->subgame.level_mode = 4;
        return;
    }

    flags = tutorial_button->widget_flags;
    if ((flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
        tutorial_button->widget_flags =
            flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
        destroy_new_game_menu();
        g_game->players[0].frontend_state = 10;
        g_game->players[0].redispatch_requested = 1;
        g_game->subgame.level_mode = 7;
        g_game->subgame.tutorial.initialize_tutorial();
        g_runtime_config.new_game_tutorial_started = 1;
        return;
    }

    flags = challenge_button->widget_flags;
    if ((flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
        challenge_button->widget_flags =
            flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
        destroy_new_game_menu();
        g_game->players[0].frontend_state = 10;
        g_game->players[0].redispatch_requested = 1;
        g_game->subgame.level_mode = 1;
        return;
    }

    flags = back_button->widget_flags;
    if ((flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
        back_button->widget_flags =
            flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
        destroy_new_game_menu();
        g_game->players[0].frontend_state = 4;
        g_game->players[0].redispatch_requested = 1;
    } else {
        flags = help_button->widget_flags;
        if ((flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
            help_button->widget_flags =
                flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
            destroy_new_game_menu();
            g_game->players[0].frontend_state = 31;
            g_game->players[0].redispatch_requested = 1;
        }
    }

    float progress = replay_probe_step + replay_probe_progress;
    replay_probe_progress = progress;
    if (progress <= 1.0f)
        return;

    replay_probe_progress = 0.0f;

    int attempts = 0;
    g_game->subgame.replay_launch_record = 0;
    do {
        ++attempts;
        switch (replay_attract_bank_cursor) {
        case 0: {
            int index = (int)((float)next_math_random_value() * 0.000122070312f);
            SubSolution* record =
                &g_game->subgame.sub_high_score.postal_records[index];
            if (record->active == 1) {
                g_game->subgame.replay_launch_record = record;
                g_game->subgame.level_mode = 0;
            }
            break;
        }
        case 1: {
            int index = (int)((float)next_math_random_value() * 0.000122070312f);
            SubSolution* record =
                &g_game->subgame.sub_high_score.survival_records[index];
            if (record->active == 1) {
                g_game->subgame.replay_launch_record = record;
                g_game->subgame.level_mode = 1;
            }
            break;
        }
        case 3: {
            int index = (int)((float)next_math_random_value() * 0.00155639648f);
            SubSolution* record =
                &g_game->subgame.sub_high_score.time_trial_route_records[index];
            if (record->active == 1) {
                g_game->subgame.replay_launch_record = record;
                g_game->subgame.level_mode = 4;
            }
            break;
        }
        default:
            break;
        }

        if (++replay_attract_bank_cursor == 5)
            replay_attract_bank_cursor = 0;
    } while (g_game->subgame.replay_launch_record == 0
        && attempts < 1000);

    if (attempts < 1000) {
        hide_for_replay_latch = 1;
        g_game->players[0].frontend_state = 10;
        g_game->players[0].redispatch_requested = 1;
        g_game->subgame.replay_launch_active = 1;
        g_game->subgame.replay_launch_return_state = 2;
        g_game->subgame.replay_launch_from_frontend = 1;
        attract_reset_progress = 0.0f;
        attract_reset_step = 0.000277777784f;
        destroy_new_game_menu();
        return;
    }

    attract_reset_progress = 0.0f;
    attract_reset_step = 0.000277777784f;
}
