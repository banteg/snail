// initialize_high_score_entry @ 0x417a70 (thiscall, ret 0x18)

#include "high_score_screen.h"

void HighScoreRecord::initialize_high_score_entry(
    int runtime_seed_value,
    int initial_level_mode_arg_value,
    int level_arg_tail_value,
    unsigned int runtime_flags_value,
    int high_score_mode_value,
    int route_or_rank_index_value)
{
    runtime_seed = runtime_seed_value;
    completion_count = 0;
    score = 0;
    timer.zero_timer_counters();
    initial_level_mode_arg = initial_level_mode_arg_value;
    level_arg_tail = level_arg_tail_value;
    rstrcpy_checked_ascii(player_name, ((HighScoreGameView*)g_game_base)->pending_player_name);
    high_score_mode_tag = high_score_mode_value;
    route_or_rank_index = route_or_rank_index_value;
    active = 0;
    runtime_flags_snapshot = runtime_flags_value;
    replay_cursor = 0;

    short* run_words = (short*)run_records + 1;
    int count = HIGH_SCORE_RUN_RECORD_COUNT;
    do {
        run_words[-1] = 0;
        run_words[0] = 0;
        run_words[1] = 0;
        run_words += 3;
        --count;
    } while (count != 0);
}
