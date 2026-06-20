// deserialize_compact_high_score_record @ 0x440020 (thiscall, ret 0x4)

#include "high_score_record.h"
#include "high_score_screen.h"

unsigned char HighScoreRecord::deserialize_compact_high_score_record(
    CompactHighScoreRecord* compact)
{
    int score_value = compact->score;
    if (compact->checksum != ((score_value * score_value) ^ HIGH_SCORE_CHECKSUM_MASK)) {
        active = 0;
        return 0;
    }

    replay_sample_count = compact->replay_sample_count;
    replay_level_index = compact->replay_level_index;
    replay_mode_id = compact->replay_mode_id;
    replay_speed_scalar_bits = compact->replay_speed_scalar_bits;
    challenge_difficulty_scalar_bits = compact->challenge_difficulty_scalar_bits;
    rstrcpy_checked_ascii(player_name, compact->player_name);

    score = compact->score;
    timer = compact->timer;
    score_tail = compact->score_tail;
    challenge_speed_value = compact->challenge_speed_value;
    challenge_difficulty_value = compact->challenge_difficulty_value;
    garbage_scalar_bits = compact->garbage_scalar_bits;
    salt_scalar_bits = compact->salt_scalar_bits;
    source_tail = compact->source_tail;
    runtime_build_seed = compact->runtime_build_seed;
    unknown_1fab8 = compact->unknown_80;
    unknown_1fabc = compact->unknown_84;
    runtime_build_flags = compact->runtime_build_flags;
    high_score_mode_tag = compact->bank_selector;
    route_or_rank_index = compact->entry_index;
    replay_cursor = compact->replay_cursor;

    int lateral_index = 0;
    short* source_lateral = compact->lateral_samples();
    if (replay_sample_count > 0) {
        ReplayRunRecord* lateral_run = run_records;
        do {
            ++lateral_index;
            lateral_run->lateral_x = *source_lateral;
            ++source_lateral;
            ++lateral_run;
        } while (lateral_index < replay_sample_count);
    }

    int delta_z_index = 0;
    short* source_delta_z = compact->delta_z_samples(replay_sample_count);
    if (replay_sample_count > 0) {
        do {
            run_records[delta_z_index].delta_z = source_delta_z[delta_z_index];
            ++delta_z_index;
        } while (delta_z_index < replay_sample_count);
    }

    int flag_index = 0;
    unsigned char* source_flags = compact->flag_samples(replay_sample_count);
    if (replay_sample_count > 0) {
        ReplayRunRecord* flag_run = run_records;
        do {
            *(unsigned short*)&flag_run->flags = source_flags[flag_index];
            ++flag_index;
            ++flag_run;
        } while (flag_index < replay_sample_count);
    }

    active = 1;
    return 1;
}
