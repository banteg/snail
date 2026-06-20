// update_challenge_setup_screen @ 0x416370 (thiscall)

#include "challenge_setup_screen.h"
#include "high_score_record.h"
#include "level_definition_loader.h"
#include "subgame_runtime.h"
#include "timer_counters.h"
#include "time_trial_string_formatter.h"

extern int data_4df9b8;
extern int g_completion_bonus_x_source; // data_4df958
extern int g_completion_bonus_y_source; // data_4df960

void __cdecl rstrcpy_checked_ascii(char* destination, char* source); // @ 0x44e5b0

int ChallengeSetupScreen::update_challenge_setup_screen()
{
    ((SubgameRuntime*)game)->hide_gameplay_scores();

    switch (*(int*)((char*)game + 0x40)) {
    case 4: {
        unsigned int flags = next_level_button->widget_flags;
        if ((flags & 0x20) != 0) {
            next_level_button->widget_flags = flags & ~0x20;
            ++*(int*)((char*)game + 0x44);
            ((LevelDefinitionLoader*)((char*)game + 0xa874))
                ->load_frontend_level_by_mode_and_index(
                    *(int*)((char*)game + 0x40),
                    *(int*)((char*)game + 0x44));
            rstrcpy_checked_ascii(level_name_widget->text_buffer, (char*)game + 0x1b0150);
            level_name_widget->layout_frontend_widget();
            rstrcpy_checked_ascii(
                (*(FrontendWidget**)((char*)game + 0x35bb8c))->text_buffer,
                ((TimeTrialStringFormatter*)((char*)game + 0xff25e0))
                    ->format_time_trial_string((TimerCounters*)((char*)game
                        + 0x944158
                        + *(int*)((char*)game + 0x44) * HIGH_SCORE_RECORD_STRIDE)));
        }

        flags = previous_level_button->widget_flags;
        if ((flags & 0x20) != 0) {
            previous_level_button->widget_flags = flags & ~0x20;
            --*(int*)((char*)game + 0x44);
            ((LevelDefinitionLoader*)((char*)game + 0xa874))
                ->load_frontend_level_by_mode_and_index(
                    *(int*)((char*)game + 0x40),
                    *(int*)((char*)game + 0x44));
            rstrcpy_checked_ascii(level_name_widget->text_buffer, (char*)game + 0x1b0150);
            level_name_widget->layout_frontend_widget();
            rstrcpy_checked_ascii(
                (*(FrontendWidget**)((char*)game + 0x35bb8c))->text_buffer,
                ((TimeTrialStringFormatter*)((char*)game + 0xff25e0))
                    ->format_time_trial_string((TimerCounters*)((char*)game
                        + 0x944158
                        + *(int*)((char*)game + 0x44) * HIGH_SCORE_RECORD_STRIDE)));
        }

        if (*(int*)((char*)game + 0x44) == 0) {
            previous_level_button->widget_flags |= 0x8000;
        } else {
            previous_level_button->widget_flags &= 0xffff7fff;
        }

        if (*(int*)((char*)game + 0x44) == data_4df9b8) {
            next_level_button->widget_flags |= 0x8000;
        } else {
            next_level_button->widget_flags &= 0xffff7fff;
        }

        FrontendWidget* previous_widget;
        int replay_active = *(int*)((char*)game
            + 0x944150
            + *(int*)((char*)game + 0x44) * HIGH_SCORE_RECORD_STRIDE);
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
            *(unsigned char*)((char*)game + 0xff25d0) = 1;
            *(int*)((char*)game + 0xff25d4) = (int)((char*)game
                + 0x944150
                + *(int*)((char*)game + 0x44) * HIGH_SCORE_RECORD_STRIDE);
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

        g_completion_bonus_x_source = (int)(speed_slider->slider_value * 100.0f + 0.100000001f);
        g_completion_bonus_y_source =
            (int)(difficulty_slider->slider_value * 100.0f + 0.100000001f);

        flags = replay_button->widget_flags;
        if ((flags & 0x20) != 0) {
            replay_button->widget_flags = flags & ~0x20;
            destroy_challenge_setup_screen();
            *(unsigned char*)((char*)game + 0xff25d0) = 1;
            *(int*)((char*)game + 0xff25d4) = (int)((char*)game + 0xfb3050);
            return 1;
        }
        break;
    }

    case 0: {
        unsigned int flags = next_level_button->widget_flags;
        if ((flags & 0x20) != 0) {
            next_level_button->widget_flags = flags & ~0x20;
            ++*(int*)((char*)game + 0x44);
            ((LevelDefinitionLoader*)((char*)game + 0xa874))
                ->load_frontend_level_by_mode_and_index(
                    *(int*)((char*)game + 0x40),
                    *(int*)((char*)game + 0x44));
            rstrcpy_checked_ascii(level_name_widget->text_buffer, (char*)game + 0x1b0150);
            level_name_widget->layout_frontend_widget();
        }

        flags = previous_level_button->widget_flags;
        if ((flags & 0x20) != 0) {
            previous_level_button->widget_flags = flags & ~0x20;
            --*(int*)((char*)game + 0x44);
            ((LevelDefinitionLoader*)((char*)game + 0xa874))
                ->load_frontend_level_by_mode_and_index(
                    *(int*)((char*)game + 0x40),
                    *(int*)((char*)game + 0x44));
            rstrcpy_checked_ascii(level_name_widget->text_buffer, (char*)game + 0x1b0150);
            level_name_widget->layout_frontend_widget();
        }

        if (*(int*)((char*)game + 0x44) == 0) {
            previous_level_button->widget_flags |= 0x8000;
        } else {
            previous_level_button->widget_flags &= 0xffff7fff;
        }

        if (*(int*)((char*)game + 0x44) == data_4df9b8) {
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
