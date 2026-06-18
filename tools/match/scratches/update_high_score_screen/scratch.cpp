// update_high_score_screen @ 0x417260 (thiscall, ret)

#include "high_score_screen.h"

int HighScoreScreen::update_high_score_screen()
{
    int result;

    if (entering_name != 0) {
        FrontendWidget* selected_name = name_row_widgets[selected_rank];
        unsigned int selected_flags = selected_name->widget_flags;
        if ((selected_flags & 0x4000) != 0) {
            selected_flags &= ~0x4000;
            selected_name->widget_flags = selected_flags;

            destroy_high_score_screen();
            g_sprite_manager.kill_game_sprites();

            HighScoreGameView* game = (HighScoreGameView*)g_game_base;
            int rank = selected_rank;
            FrontendWidget* name_widget = name_row_widgets[rank];
            HighScoreRecord* record =
                (HighScoreRecord*)((char*)game->high_score_records.active_record_bank
                    + rank * HIGH_SCORE_RECORD_STRIDE);
            rstrcpy_checked_ascii(record->player_name, name_widget->text_buffer);
            rstrcpy_checked_ascii(game->pending_player_name, name_widget->text_buffer);
            rstrcpy_checked_ascii(g_last_entered_player_name, name_widget->text_buffer);
            return exit_high_score_screen();
        }

        FrontendWidget* cancel = cancel_name_button;
        unsigned int cancel_flags = cancel->widget_flags;
        if ((cancel_flags & 0x20) != 0) {
            cancel_flags &= ~0x20;
            cancel->widget_flags = cancel_flags;
            name_row_widgets[selected_rank]->widget_flags |= 0x8000000;
        }

        FrontendWidget* submit = submit_name_button;
        result = submit->widget_flags;
        if ((result & 0x20) != 0) {
            result &= ~0x20;
            submit->widget_flags = result;

            destroy_high_score_screen();
            g_sprite_manager.kill_game_sprites();
            ((HighScoreGameView*)g_game_base)
                ->high_score_records.commit_high_score_entry_into_top_ten(
                    selected_rank);
            return exit_high_score_screen();
        }
    } else {
        FrontendWidget* toggle = bank_toggle_button;
        unsigned int toggle_flags = toggle->widget_flags;
        if ((toggle_flags & 0x20) != 0) {
            toggle_flags &= ~0x20;
            toggle->widget_flags = toggle_flags;

            destroy_high_score_screen();

            int bank = selected_bank;
            if (bank == 0)
                selected_bank = 1;
            else if (bank == 1)
                selected_bank = 0;

            g_high_score_selected_bank = selected_bank;
            return initialize_high_score_screen(selected_bank, -1);
        }

        FrontendWidget* back = back_button;
        unsigned int back_flags = back->widget_flags;
        if ((back_flags & 0x20) != 0) {
            back_flags &= ~0x20;
            back->widget_flags = back_flags;

            int current_mode = mode;
            if (current_mode == 1) {
                HighScoreGameView* game = (HighScoreGameView*)g_game_base;
                game->frontend_next_state = 10;
                game->frontend_state_dirty = 1;
                destroy_high_score_screen();
                return 0;
            }

            if (current_mode == 0)
                ((HighScoreGameView*)g_game_base)->frontend_next_state = 4;

            return destroy_high_score_screen();
        }

        HighScoreGameView* game = (HighScoreGameView*)g_game_base;
        int i = 0;
        result = game->high_score_records.active_record_count;
        if (result > 0) {
            int record_offset = 0;
            FrontendWidget** replay_widget = replay_row_widgets;
            do {
                HighScoreRecord* record =
                    (HighScoreRecord*)((char*)game->high_score_records.active_record_bank
                        + record_offset);
                if (record->active == 1) {
                    FrontendWidget* widget = *replay_widget;
                    if (widget != 0) {
                        unsigned int widget_flags = widget->widget_flags;
                        if ((widget_flags & 0x20) != 0) {
                            widget_flags &= ~0x20;
                            widget->widget_flags = widget_flags;

                            HighScoreGameView* launch_game = (HighScoreGameView*)g_game_base;
                            launch_game->frontend_next_state = 10;
                            launch_game->frontend_state_dirty = 1;
                            destroy_high_score_screen();

                            launch_game = (HighScoreGameView*)g_game_base;
                            launch_game->replay_launch_record =
                                (HighScoreRecord*)
                                    ((char*)launch_game->high_score_records.active_record_bank
                                        + record_offset);
                            ((HighScoreGameView*)g_game_base)->replay_launch_active = 1;
                            ((HighScoreGameView*)g_game_base)->replay_launch_from_frontend = 1;
                            ((HighScoreGameView*)g_game_base)->replay_launch_return_state = 18;

                            launch_game = (HighScoreGameView*)g_game_base;
                            launch_game->selected_subgame_mode =
                                launch_game->replay_launch_record->replay_mode_id;
                        }
                    }
                }

                ++i;
                record_offset += HIGH_SCORE_RECORD_STRIDE;
                ++replay_widget;
                result = game->high_score_records.active_record_count;
            } while (i < result);
        }
    }

    return result;
}
