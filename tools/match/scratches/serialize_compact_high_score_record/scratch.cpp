// serialize_compact_high_score_record @ 0x440170 (thiscall, ret 0x4)

#include "high_score_record.h"
#include "high_score_screen.h"

int HighScoreRecord::serialize_compact_high_score_record(CompactHighScoreRecord* compact)
{
    int sample_count = completion_count;
    active = 1;
    compact->replay_sample_count = sample_count;
    compact->replay_level_index = initial_level_mode_arg;
    compact->replay_mode_id = level_mode;
    compact->replay_speed_scalar_bits = level_arg_tail;
    compact->challenge_difficulty_scalar_bits = difficulty_scalar_bits;
    rstrcpy_checked_ascii(compact->player_name, player_name);

    compact->timer = timer;
    compact->score_tail = score_tail;
    compact->challenge_speed_value = completion_bonus_x_source;
    compact->challenge_difficulty_value = completion_bonus_y_source;
    compact->garbage_scalar_bits = timer_snapshot_a;
    compact->salt_scalar_bits = timer_snapshot_b;
    compact->source_tail = source_tail;
    compact->score = score;
    compact->checksum = (score * score) ^ HIGH_SCORE_CHECKSUM_MASK;
    compact->runtime_build_seed = runtime_seed;
    compact->unknown_80 = *(int*)unknown_1fab8;
    compact->unknown_84 = *(int*)(unknown_1fab8 + 4);
    compact->runtime_build_flags = runtime_flags_snapshot;
    compact->bank_selector = high_score_mode_tag;
    compact->entry_index = route_or_rank_index;
    compact->replay_cursor = replay_cursor;

    int lateral_index = 0;
    int lateral_count = completion_count;
    short* out_lateral =
        (short*)((char*)compact + COMPACT_HIGH_SCORE_RECORD_HEADER_BYTES);
    if (lateral_count > 0) {
        short* source_lateral = (short*)run_records;
        do {
            ++lateral_index;
            *out_lateral = *source_lateral;
            source_lateral += 3;
            ++out_lateral;
        } while (lateral_index < completion_count);
    }

    int secondary_index = 0;
    int secondary_count = completion_count;
    short* out_secondary =
        (short*)((char*)compact + COMPACT_HIGH_SCORE_RECORD_HEADER_BYTES
            + secondary_count * sizeof(short));
    if (secondary_count > 0) {
        short* source_secondary = (short*)run_records + 1;
        do {
            ++secondary_index;
            *out_secondary = *source_secondary;
            source_secondary += 3;
            ++out_secondary;
        } while (secondary_index < completion_count);
    }

    int flag_index = 0;
    unsigned char* out_flags =
        (unsigned char*)((char*)compact + COMPACT_HIGH_SCORE_RECORD_HEADER_BYTES
            + completion_count * 4);
    if (completion_count > 0) {
        ReplayRunRecord* flag_run = run_records;
        do {
            out_flags[flag_index] = flag_run->flags;
            ++flag_run;
            ++flag_index;
        } while (flag_index < completion_count);
    }

    int byte_count = completion_count * 5 + COMPACT_HIGH_SCORE_RECORD_HEADER_BYTES;
    compact->byte_count = byte_count;
    return byte_count;
}
