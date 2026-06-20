// serialize_compact_high_score_record @ 0x440170 (thiscall, ret 0x4)

#include "high_score_record.h"
#include "high_score_screen.h"

int HighScoreRecord::serialize_compact_high_score_record(CompactHighScoreRecord* compact)
{
    int sample_count = replay_sample_count;
    active = 1;
    compact->replay_sample_count = sample_count;
    compact->replay_level_index = replay_level_index;
    compact->replay_mode_id = replay_mode_id;
    compact->replay_speed_scalar_bits = replay_speed_scalar_bits;
    compact->challenge_difficulty_scalar_bits = challenge_difficulty_scalar_bits;
    rstrcpy_checked_ascii(compact->player_name, player_name);

    compact->timer = timer;
    compact->score_tail = score_tail;
    compact->challenge_speed_value = challenge_speed_value;
    compact->challenge_difficulty_value = challenge_difficulty_value;
    compact->garbage_scalar_bits = garbage_scalar_bits;
    compact->salt_scalar_bits = salt_scalar_bits;
    compact->source_tail = source_tail;
    compact->score = score;
    compact->checksum = (score * score) ^ HIGH_SCORE_CHECKSUM_MASK;
    compact->runtime_build_seed = runtime_build_seed;
    compact->unknown_80 = unknown_1fab8;
    compact->unknown_84 = unknown_1fabc;
    compact->runtime_build_flags = runtime_build_flags;
    compact->bank_selector = high_score_mode_tag;
    compact->entry_index = route_or_rank_index;
    compact->replay_cursor = replay_cursor;

    int lateral_index = 0;
    short* out_lateral = compact->lateral_samples();
    if (replay_sample_count > 0) {
        do {
            out_lateral[lateral_index] = run_records[lateral_index].lateral_x;
            ++lateral_index;
        } while (lateral_index < replay_sample_count);
    }

    int delta_z_index = 0;
    short* out_delta_z = compact->delta_z_samples(replay_sample_count);
    if (replay_sample_count > 0) {
        do {
            out_delta_z[delta_z_index] = run_records[delta_z_index].delta_z;
            ++delta_z_index;
        } while (delta_z_index < replay_sample_count);
    }

    int flag_index = 0;
    unsigned char* out_flags = compact->flag_samples(replay_sample_count);
    if (replay_sample_count > 0) {
        ReplayRunRecord* flag_run = run_records;
        do {
            out_flags[flag_index] = flag_run->flags;
            ++flag_run;
            ++flag_index;
        } while (flag_index < replay_sample_count);
    }

    int byte_count = replay_sample_count * 5 + COMPACT_HIGH_SCORE_RECORD_HEADER_BYTES;
    compact->byte_count = byte_count;
    return byte_count;
}
