// initialize_high_score_entry @ 0x417a70 (thiscall, ret 0x18)

#include "game_root.h"
#include "high_score_screen.h"

void SubSolution::initialize_high_score_entry(
    int runtime_build_seed_value,
    int replay_level_index_value,
    int replay_speed_scalar_bits_value,
    unsigned int runtime_build_flags_value,
    int high_score_mode_value,
    int route_or_rank_index_value)
{
    runtime_build_seed = runtime_build_seed_value;
    replay_sample_count = 0;
    score = 0;
    timer.zero_timer_counters();
    replay_level_index = replay_level_index_value;
    replay_speed_scalar_bits = replay_speed_scalar_bits_value;
    rstrcpy_checked_ascii(player_name, ((GameRoot*)g_game_base)->players[0].player_name);
    active = 0;
    runtime_build_flags = runtime_build_flags_value;
    high_score_mode_tag = high_score_mode_value;
    route_or_rank_index = route_or_rank_index_value;
    replay_cursor = 0;

    short* run_words = (short*)run_records + 1;
    int count = SUB_SOLUTION_RUN_RECORD_COUNT;
    do {
        run_words[-1] = 0;
        run_words[0] = 0;
        run_words[1] = 0;
        run_words += 3;
        --count;
    } while (count != 0);
}
