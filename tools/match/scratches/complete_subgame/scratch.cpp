// complete_subgame @ 0x438700 (thiscall, ret 0x4)
// cRSubGame::Complete(bool): snapshot the finished run and route high-score writes.

#include "subgame_runtime.h"

extern unsigned char g_completion_snapshot_flags; // byte_4b2f40

void SubgameRuntime::complete_subgame(unsigned char completed)
{
    ((RunScoreStats*)&score_stats)->display_score_stats();

    current_high_score_record.run_records[replay_update_cursor].flags |= 0x08;
    ++current_high_score_record.replay_sample_count;
    ++replay_update_cursor;

    if ((g_completion_snapshot_flags & 1) == 0) {
        HighScoreRecord* record = &current_high_score_record;

        current_high_score_record.score = source_score;
        current_high_score_record.stats = source_stats;
        current_high_score_record.difficulty_scalar_bits = difficulty_scalar_bits;
        current_high_score_record.challenge_speed_value = completion_bonus_x_source;
        current_high_score_record.score_tail = source_score_tail;
        current_high_score_record.challenge_difficulty_value = completion_bonus_y_source;
        current_high_score_record.replay_speed_scalar_bits = level_arg_tail;
        current_high_score_record.garbage_scalar_bits = source_timer_a;
        current_high_score_record.salt_scalar_bits = source_timer_b;
        current_high_score_record.active = 1;
        current_high_score_record.source_tail = source_tail;
        current_high_score_record.replay_mode_id = level_mode;

        if ((level_mode != 1 || source_tail != 0)
            && !selected_level_record_active
            && completed == 1) {
            switch (level_mode) {
            case 0:
                high_score_bank.add_arcade_high_score(record, level_mode_arg);
                break;
            case 1:
                high_score_bank.add_survival_high_score(record);
                break;
            case 4:
                high_score_bank.add_time_trial_high_score(
                    record,
                    level_mode_arg,
                    time_trial_route_active);
                break;
            }
        }
    }
}
