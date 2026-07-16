// update_click_start @ 0x442290 (thiscall, ret)

#include "player.h"
#include "audio_system.h"
#include "game_root.h"
#include "input_state.h"


void set_math_random_seed(int seed);
void* set_input_controller_pointer_authored_xy(int slot, float authored_x, float authored_y);

void ClickStart::update_click_start()
{
    if (g_game->subgame.subgame_pause_gate != 0)
        return;

    FrontendWidget* widget = prompt;
    if (hide_prompt != 0)
        widget->hide_border_init();
    else
        widget->unhide_border_init();

    ClickStartState current_state = state;
    switch (current_state) {
    case CLICK_START_STATE_INACTIVE:
    case CLICK_START_STATE_UNKNOWN_1:
        goto done;
    case CLICK_START_STATE_WAITING_FOR_START:
        goto waiting_for_start;
    case CLICK_START_STATE_START_PENDING:
        goto begin_teardown;
    case CLICK_START_STATE_TEARDOWN:
        goto teardown;
    default:
        goto done;
    }

waiting_for_start: {
        g_game->backdrop.unknown_660 = 1;
        if (g_game->subgame.replay_update_cursor > 8)
            g_game->subgame.replay_update_cursor = 8;

        if (g_game->subgame.replay_launch_active != 0) {
            int replay_index = g_game->subgame.replay_update_cursor;
            SubSolution* replay_record = g_game->subgame.replay_launch_record;
            if ((replay_record->run_records[replay_index].flags & 0x20) != 0)
                goto start_subgame;
        }

        if (g_game->subgame.replay_launch_active != 0)
            return;
        if (hide_prompt != 0)
            return;
        if ((g_game->players[0].game_input->input.pressed_buttons & 0x4000) == 0)
            return;

start_subgame:
        owner_player->startup_track_index = g_game->subgame.replay_update_cursor;
        state = CLICK_START_STATE_START_PENDING;

        if (g_game->subgame.replay_launch_active == 0) {
            g_game->subgame.current_high_score_record
                .run_records[g_game->subgame.replay_update_cursor]
                .flags |= 0x20;
            g_game->subgame.current_high_score_record
                .run_records[g_game->subgame.replay_update_cursor]
                .flags &= 0xfffe;
            g_game->subgame.current_high_score_record.source_tail =
                g_game->subgame.replay_update_cursor;
        }

        set_input_controller_pointer_authored_xy(0, 320.0f, 240.0f);
        set_input_controller_pointer_authored_xy(1, 320.0f, 240.0f);
        g_sound_effect_manager.play_sound_effect(8);
        return;
    }

begin_teardown:
        set_math_random_seed(g_game->subgame.current_high_score_record.runtime_build_seed);
        state = CLICK_START_STATE_TEARDOWN;
        teardown_progress = 0.0f;
        teardown_progress_step = 0.0166666675f;
        g_game->border_manager.kill_border(prompt);

teardown: {
        transform.position.y = teardown_progress * 16.0f + transform.position.y;
        teardown_progress = teardown_progress_step + teardown_progress;

        g_game->active_bod_list.remove_bod(this);
        state = CLICK_START_STATE_INACTIVE;
        return;
    }

done:
    return;
}
