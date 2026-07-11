// complete_subgame @ 0x438700 (thiscall, ret 0x4)
// cRSubGame::Complete(bool): snapshot the finished run and route high-score writes.

#include "cheat_state.h"
#include "subgame_runtime.h"

void SubgameRuntime::complete_subgame(unsigned char completed)
{
    player.display_score_stats();

    current_high_score_record.run_records[replay_update_cursor].flags |= 0x08;
    ++current_high_score_record.replay_sample_count;
    ++replay_update_cursor;

    if ((g_cheat_state.flags & 1) == 0) {
        SubSolution* record = &current_high_score_record;

        current_high_score_record.score = player.total_score;
        current_high_score_record.timer = player.stopwatch;
        current_high_score_record.challenge_difficulty_scalar_bits = difficulty_scalar_bits;
        current_high_score_record.challenge_speed_value = completion_bonus_x_source;
        current_high_score_record.score_tail = player.score_tail;
        current_high_score_record.challenge_difficulty_value = completion_bonus_y_source;
        current_high_score_record.replay_speed_scalar_bits = level_arg_tail;
        current_high_score_record.garbage_frequency_bits = garbage_frequency_bits;
        current_high_score_record.salt_frequency_bits = salt_frequency_bits;
        current_high_score_record.active = 1;
        current_high_score_record.source_tail = player.startup_track_index;
        current_high_score_record.replay_mode_id = level_mode;

        if ((level_mode != 1 || player.startup_track_index != 0)
            && !selected_level_record_active
            && completed == 1) {
            switch (level_mode) {
            case 0:
                sub_high_score.add_arcade_high_score(record, level_mode_arg);
                break;
            case 1:
                sub_high_score.add_survival_high_score(record);
                break;
            case 4:
                sub_high_score.add_time_trial_high_score(
                    record,
                    level_mode_arg,
                    player.completion_handoff_active);
                break;
            }
        }
    }
}
