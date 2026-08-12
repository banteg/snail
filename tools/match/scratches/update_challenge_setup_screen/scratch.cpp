// update_challenge_setup_screen @ 0x416370 (thiscall)

#include "gui.h"
#include "rstring.h"
#include "sub_solution.h"
#include "sub_tracks.h"
#include "runtime_config.h"
#include "subgame_runtime.h"
#include "game_time.h"
#include "time_trial.h"

int cRGUI::AI()
{
    game->HideScores();

    switch (game->level_mode) {
    case 4: {
        unsigned int flags = next_level_button->widget_flags;
        if ((flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
            next_level_button->widget_flags =
                flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
            ++game->level_mode_arg;
            game->level_definition.load_frontend_level_by_mode_and_index(
                game->level_mode,
                game->level_mode_arg);
            Rstrcpy(
                level_name_widget->text_buffer,
                game->level_definition.level_display_name);
            level_name_widget->layout_frontend_widget();
            Rstrcpy(
                game->bottom_score_widget->text_buffer,
                game->time_trial.format_time_trial_string(
                    &game->sub_high_score
                         .time_trial_route_records[game->level_mode_arg]
                         .timer));
        }

        flags = previous_level_button->widget_flags;
        if ((flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
            previous_level_button->widget_flags =
                flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
            --game->level_mode_arg;
            game->level_definition.load_frontend_level_by_mode_and_index(
                game->level_mode,
                game->level_mode_arg);
            Rstrcpy(
                level_name_widget->text_buffer,
                game->level_definition.level_display_name);
            level_name_widget->layout_frontend_widget();
            Rstrcpy(
                game->bottom_score_widget->text_buffer,
                game->time_trial.format_time_trial_string(
                    &game->sub_high_score
                         .time_trial_route_records[game->level_mode_arg]
                         .timer));
        }

        if (game->level_mode_arg == 0) {
            previous_level_button->widget_flags |= FRONTEND_WIDGET_FLAG_DISABLED;
        } else {
            previous_level_button->widget_flags &= ~FRONTEND_WIDGET_FLAG_DISABLED;
        }

        if (game->level_mode_arg == g_runtime_config.highest_galaxy_route_index) {
            next_level_button->widget_flags |= FRONTEND_WIDGET_FLAG_DISABLED;
        } else {
            next_level_button->widget_flags &= ~FRONTEND_WIDGET_FLAG_DISABLED;
        }

        int replay_active = game->sub_high_score
            .time_trial_route_records[game->level_mode_arg]
            .active;
        if (replay_active != 1) {
            replay_button->HideInit();
            back_button->SetBelow(play_button);
        } else {
            replay_button->UnHideInit();
            back_button->SetBelow(replay_button);
        }

        flags = back_button->widget_flags;
        if ((flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
            back_button->widget_flags =
                flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
            UnInit();
            return 3;
        }

        flags = play_button->widget_flags;
        if ((flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
            play_button->widget_flags =
                flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
            UnInit();
            return 1;
        }

        flags = replay_button->widget_flags;
        if ((flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
            replay_button->widget_flags =
                flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
            UnInit();
            game->selected_level_record_active = 1;
            game->selected_level_record =
                &game->sub_high_score
                     .time_trial_route_records[game->level_mode_arg];
            return 1;
        }
        break;
    }

    case 1: {
        unsigned int flags = back_button->widget_flags;
        if ((flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
            back_button->widget_flags =
                flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
            UnInit();
            return 3;
        }

        flags = play_button->widget_flags;
        if ((flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
            play_button->widget_flags =
                flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
            UnInit();
            return 1;
        }

        g_runtime_config.challenge_speed_percent =
            (int)(speed_slider->slider_value * 100.0f + 0.100000001f);
        g_runtime_config.challenge_difficulty_percent =
            (int)(difficulty_slider->slider_value * 100.0f + 0.100000001f);

        flags = replay_button->widget_flags;
        if ((flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
            replay_button->widget_flags =
                flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
            UnInit();
            game->selected_level_record_active = 1;
            game->selected_level_record =
                &game->sub_high_score.survival_pending_record;
            return 1;
        }
        break;
    }

    case 0: {
        unsigned int flags = next_level_button->widget_flags;
        if ((flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
            next_level_button->widget_flags =
                flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
            ++game->level_mode_arg;
            game->level_definition.load_frontend_level_by_mode_and_index(
                game->level_mode,
                game->level_mode_arg);
            Rstrcpy(
                level_name_widget->text_buffer,
                game->level_definition.level_display_name);
            level_name_widget->layout_frontend_widget();
        }

        flags = previous_level_button->widget_flags;
        if ((flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
            previous_level_button->widget_flags =
                flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
            --game->level_mode_arg;
            game->level_definition.load_frontend_level_by_mode_and_index(
                game->level_mode,
                game->level_mode_arg);
            Rstrcpy(
                level_name_widget->text_buffer,
                game->level_definition.level_display_name);
            level_name_widget->layout_frontend_widget();
        }

        if (game->level_mode_arg == 0) {
            previous_level_button->widget_flags |= FRONTEND_WIDGET_FLAG_DISABLED;
        } else {
            previous_level_button->widget_flags &= ~FRONTEND_WIDGET_FLAG_DISABLED;
        }

        if (game->level_mode_arg == g_runtime_config.highest_galaxy_route_index) {
            next_level_button->widget_flags |= FRONTEND_WIDGET_FLAG_DISABLED;
        } else {
            next_level_button->widget_flags &= ~FRONTEND_WIDGET_FLAG_DISABLED;
        }

        flags = back_button->widget_flags;
        if ((flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
            back_button->widget_flags =
                flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
            UnInit();
            return 3;
        }

        flags = play_button->widget_flags;
        if ((flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
            play_button->widget_flags =
                flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
            UnInit();
            return 1;
        }
        break;
    }
    }

    return 0;
}
