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

    completion_count = compact->replay_sample_count;
    initial_level_mode_arg = compact->replay_level_index;
    level_mode = compact->replay_mode_id;
    level_arg_tail = compact->replay_speed_scalar_bits;
    difficulty_scalar_bits = compact->challenge_difficulty_scalar_bits;
    rstrcpy_checked_ascii(player_name, compact->player_name);

    score = compact->score;
    timer = compact->timer;
    score_tail = compact->score_tail;
    completion_bonus_x_source = compact->challenge_speed_value;
    completion_bonus_y_source = compact->challenge_difficulty_value;
    timer_snapshot_a = compact->garbage_scalar_bits;
    timer_snapshot_b = compact->salt_scalar_bits;
    source_tail = compact->source_tail;
    runtime_seed = compact->runtime_build_seed;
    *(int*)unknown_1fab8 = compact->unknown_80;
    *(int*)(unknown_1fab8 + 4) = compact->unknown_84;
    runtime_flags_snapshot = compact->runtime_build_flags;
    high_score_mode_tag = compact->bank_selector;
    route_or_rank_index = compact->entry_index;
    replay_cursor = compact->replay_cursor;

    int lateral_index = 0;
    short* source_lateral =
        (short*)((char*)compact + COMPACT_HIGH_SCORE_RECORD_HEADER_BYTES);
    if (completion_count > 0) {
        ReplayRunRecord* lateral_run = run_records;
        do {
            ++lateral_index;
            *(short*)lateral_run->unknown_00 = *source_lateral;
            ++source_lateral;
            ++lateral_run;
        } while (lateral_index < completion_count);
    }

    int secondary_index = 0;
    int secondary_count = completion_count;
    short* source_secondary =
        (short*)((char*)compact + COMPACT_HIGH_SCORE_RECORD_HEADER_BYTES
            + secondary_count * sizeof(short));
    if (secondary_count > 0) {
        short* secondary_destination = (short*)run_records + 1;
        do {
            ++secondary_index;
            *secondary_destination = *source_secondary;
            secondary_destination += 3;
            ++source_secondary;
        } while (secondary_index < completion_count);
    }

    int flag_index = 0;
    unsigned char* source_flags =
        (unsigned char*)((char*)compact + COMPACT_HIGH_SCORE_RECORD_HEADER_BYTES
            + completion_count * 4);
    if (completion_count > 0) {
        ReplayRunRecord* flag_run = run_records;
        do {
            *(unsigned short*)&flag_run->flags = source_flags[flag_index];
            ++flag_index;
            ++flag_run;
        } while (flag_index < completion_count);
    }

    active = 1;
    return 1;
}
