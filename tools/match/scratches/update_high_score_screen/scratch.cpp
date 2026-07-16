// update_high_score_screen @ 0x417260 (thiscall, ret)

#include "game_root.h"
#include "high_score.h"

extern GameRoot* g_game; // data_4df904

void HighScore::update_high_score_screen()
{
    int result;

    if (entering_name != 0) {
        FrontendWidget* selected_name = name_row_widgets[selected_rank];
        unsigned int selected_flags = selected_name->widget_flags;
        if ((selected_flags & FRONTEND_WIDGET_FLAG_TEXT_INPUT_COMPLETE) != 0) {
            selected_flags &= ~FRONTEND_WIDGET_FLAG_TEXT_INPUT_COMPLETE;
            selected_name->widget_flags = selected_flags;

            destroy_high_score_screen();
            g_sprite_manager.kill_game_sprites();

            int rank = selected_rank;
            rstrcpy_checked_ascii(
                ((SubSolution*)((char*)g_game->subgame.sub_high_score.active_record_bank
                    + rank * SUB_SOLUTION_STRIDE))->player_name,
                name_row_widgets[rank]->text_buffer);
            rstrcpy_checked_ascii(
                g_game->players[0].player_name,
                name_row_widgets[selected_rank]->text_buffer);
            rstrcpy_checked_ascii(
                g_runtime_config.last_entered_player_name,
                name_row_widgets[selected_rank]->text_buffer);
            exit_high_score_screen();
            return;
        }

        FrontendWidget* submit = submit_name_button;
        unsigned int submit_flags = submit->widget_flags;
        if ((submit_flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
            submit_flags &= ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
            submit->widget_flags = submit_flags;
            name_row_widgets[selected_rank]->widget_flags |=
                FRONTEND_WIDGET_FLAG_TEXT_INPUT_SUBMIT_REQUESTED;
        }

        FrontendWidget* cancel = cancel_name_button;
        result = cancel->widget_flags;
        if ((result & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
            result &= ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
            cancel->widget_flags = result;

            destroy_high_score_screen();
            g_sprite_manager.kill_game_sprites();
            g_game->subgame.sub_high_score.mini_delete_high_score_entry(
                selected_rank);
            exit_high_score_screen();
            return;
        }
    } else {
        FrontendWidget* toggle = bank_toggle_button;
        unsigned int toggle_flags = toggle->widget_flags;
        if ((toggle_flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
            toggle_flags &= ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
            toggle->widget_flags = toggle_flags;

            destroy_high_score_screen();

            switch (selected_bank) {
            case 0:
                selected_bank = 1;
                break;
            case 1:
                selected_bank = 0;
                break;
            }

            g_runtime_config.high_score_selected_bank = selected_bank;
            initialize_high_score_screen(selected_bank, -1);
            return;
        }

        FrontendWidget* back = back_button;
        unsigned int back_flags = back->widget_flags;
        if ((back_flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
            back_flags &= ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
            back->widget_flags = back_flags;

            int current_mode = mode;
            if (current_mode == 1) {
                g_game->players[0].frontend_state = 10;
                g_game->players[0].redispatch_requested = 1;
                destroy_high_score_screen();
                return;
            }

            if (current_mode == 0)
                g_game->players[0].frontend_state = 4;

            destroy_high_score_screen();
            return;
        }

        int i = 0;
        result = g_game->subgame.sub_high_score.active_record_count;
        if (result > 0) {
            int record_offset = 0;
            FrontendWidget** replay_widget = replay_row_widgets;
            do {
                SubSolution* record =
                    (SubSolution*)((char*)g_game->subgame.sub_high_score.active_record_bank
                        + record_offset);
                if (record->active == 1) {
                    FrontendWidget* widget = *replay_widget;
                    if (widget != 0) {
                        unsigned int widget_flags = widget->widget_flags;
                        if ((widget_flags
                                & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED)
                            != 0) {
                            widget_flags &=
                                ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
                            widget->widget_flags = widget_flags;

                            g_game->players[0].frontend_state = 10;
                            g_game->players[0].redispatch_requested = 1;
                            destroy_high_score_screen();

                            GameRoot* launch_game = g_game;
                            launch_game->subgame.replay_launch_record =
                                (SubSolution*)
                                    ((char*)launch_game->subgame.sub_high_score.active_record_bank
                                        + record_offset);
                            g_game->subgame.replay_launch_active = 1;
                            g_game->subgame.replay_launch_from_frontend = 1;
                            g_game->subgame.replay_launch_return_state = 18;

                            launch_game = g_game;
                            launch_game->subgame.level_mode =
                                launch_game->subgame.replay_launch_record->replay_mode_id;
                        }
                    }
                }

                ++i;
                ++replay_widget;
                record_offset += SUB_SOLUTION_STRIDE;
                result = g_game->subgame.sub_high_score.active_record_count;
            } while (i < result);
        }
    }

}
