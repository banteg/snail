// update_challenge_setup_screen @ 0x416370 (thiscall)

#include "challenge_setup_screen.h"
#include "high_score_record.h"
#include "sub_tracks.h"
#include "runtime_config.h"
#include "subgame_runtime.h"
#include "timer_counters.h"
#include "time_trial_string_formatter.h"


void __cdecl rstrcpy_checked_ascii(char* destination, char* source); // @ 0x44e5b0

int ChallengeSetupScreen::update_challenge_setup_screen()
{
    game->hide_gameplay_scores();

    switch (game->level_mode) {
    case 4: {
        unsigned int flags = next_level_button->widget_flags;
        if ((flags & 0x20) != 0) {
            next_level_button->widget_flags = flags & ~0x20;
            ++game->level_mode_arg;
            game->level_definition.load_frontend_level_by_mode_and_index(
                game->level_mode,
                game->level_mode_arg);
            rstrcpy_checked_ascii(
                level_name_widget->text_buffer,
                game->level_definition.level_display_name);
            level_name_widget->layout_frontend_widget();
            rstrcpy_checked_ascii(
                game->bottom_score_widget->text_buffer,
                game->time_trial_formatter()->format_time_trial_string(
                    &game->high_score_bank
                         .time_trial_route_records[game->level_mode_arg]
                         .timer));
        }

        flags = previous_level_button->widget_flags;
        if ((flags & 0x20) != 0) {
            previous_level_button->widget_flags = flags & ~0x20;
            --game->level_mode_arg;
            game->level_definition.load_frontend_level_by_mode_and_index(
                game->level_mode,
                game->level_mode_arg);
            rstrcpy_checked_ascii(
                level_name_widget->text_buffer,
                game->level_definition.level_display_name);
            level_name_widget->layout_frontend_widget();
            rstrcpy_checked_ascii(
                game->bottom_score_widget->text_buffer,
                game->time_trial_formatter()->format_time_trial_string(
                    &game->high_score_bank
                         .time_trial_route_records[game->level_mode_arg]
                         .timer));
        }

        if (game->level_mode_arg == 0) {
            previous_level_button->widget_flags |= 0x8000;
        } else {
            previous_level_button->widget_flags &= 0xffff7fff;
        }

        if (game->level_mode_arg == g_runtime_config.highest_galaxy_route_index) {
            next_level_button->widget_flags |= 0x8000;
        } else {
            next_level_button->widget_flags &= 0xffff7fff;
        }

        FrontendWidget* previous_widget;
        int replay_active = game->high_score_bank
            .time_trial_route_records[game->level_mode_arg]
            .active;
        if (replay_active != 1) {
            replay_button->hide_border_init();
            previous_widget = play_button;
        } else {
            replay_button->unhide_border_init();
            previous_widget = replay_button;
        }
        back_button->stack_widget_below(previous_widget);

        flags = back_button->widget_flags;
        if ((flags & 0x20) != 0) {
            back_button->widget_flags = flags & ~0x20;
            destroy_challenge_setup_screen();
            return 3;
        }

        flags = play_button->widget_flags;
        if ((flags & 0x20) != 0) {
            play_button->widget_flags = flags & ~0x20;
            destroy_challenge_setup_screen();
            return 1;
        }

        flags = replay_button->widget_flags;
        if ((flags & 0x20) != 0) {
            replay_button->widget_flags = flags & ~0x20;
            destroy_challenge_setup_screen();
            game->selected_level_record_active = 1;
            game->selected_level_record =
                &game->high_score_bank
                     .time_trial_route_records[game->level_mode_arg];
            return 1;
        }
        break;
    }

    case 1: {
        unsigned int flags = back_button->widget_flags;
        if ((flags & 0x20) != 0) {
            back_button->widget_flags = flags & ~0x20;
            destroy_challenge_setup_screen();
            return 3;
        }

        flags = play_button->widget_flags;
        if ((flags & 0x20) != 0) {
            play_button->widget_flags = flags & ~0x20;
            destroy_challenge_setup_screen();
            return 1;
        }

        g_runtime_config.completion_bonus_x_source =
            (int)(speed_slider->slider_value * 100.0f + 0.100000001f);
        g_runtime_config.completion_bonus_y_source =
            (int)(difficulty_slider->slider_value * 100.0f + 0.100000001f);

        flags = replay_button->widget_flags;
        if ((flags & 0x20) != 0) {
            replay_button->widget_flags = flags & ~0x20;
            destroy_challenge_setup_screen();
            game->selected_level_record_active = 1;
            game->selected_level_record =
                &game->high_score_bank.survival_pending_record;
            return 1;
        }
        break;
    }

    case 0: {
        unsigned int flags = next_level_button->widget_flags;
        if ((flags & 0x20) != 0) {
            next_level_button->widget_flags = flags & ~0x20;
            ++game->level_mode_arg;
            game->level_definition.load_frontend_level_by_mode_and_index(
                game->level_mode,
                game->level_mode_arg);
            rstrcpy_checked_ascii(
                level_name_widget->text_buffer,
                game->level_definition.level_display_name);
            level_name_widget->layout_frontend_widget();
        }

        flags = previous_level_button->widget_flags;
        if ((flags & 0x20) != 0) {
            previous_level_button->widget_flags = flags & ~0x20;
            --game->level_mode_arg;
            game->level_definition.load_frontend_level_by_mode_and_index(
                game->level_mode,
                game->level_mode_arg);
            rstrcpy_checked_ascii(
                level_name_widget->text_buffer,
                game->level_definition.level_display_name);
            level_name_widget->layout_frontend_widget();
        }

        if (game->level_mode_arg == 0) {
            previous_level_button->widget_flags |= 0x8000;
        } else {
            previous_level_button->widget_flags &= 0xffff7fff;
        }

        if (game->level_mode_arg == g_runtime_config.highest_galaxy_route_index) {
            next_level_button->widget_flags |= 0x8000;
        } else {
            next_level_button->widget_flags &= 0xffff7fff;
        }

        flags = back_button->widget_flags;
        if ((flags & 0x20) != 0) {
            back_button->widget_flags = flags & ~0x20;
            destroy_challenge_setup_screen();
            return 3;
        }

        flags = play_button->widget_flags;
        if ((flags & 0x20) != 0) {
            play_button->widget_flags = flags & ~0x20;
            destroy_challenge_setup_screen();
            return 1;
        }
        break;
    }
    }

    return 0;
}
