/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: serialize_compact_high_score_record @ 0x440170 */

00440178        int32_t replay_sample_count = record->replay_sample_count
0044017b        record->active = 1
00440181        compact->replay_sample_count = replay_sample_count
00440187        compact->replay_level_index = record->replay_level_index
0044018d        compact->replay_mode_id = record->replay_mode_id
00440194        compact->replay_speed_scalar.bits = record->replay_speed_scalar.bits
004401a3        compact->challenge_difficulty_scalar.bits = record->challenge_difficulty_scalar.bits
004401a6        rstrcpy_checked_ascii(&compact->player_name, &record->player_name)
004401b9        __builtin_memcpy(&compact->score_or_time, &record->score_or_time, 0x18)
004401be        compact->score_tail = record->score_tail
004401c4        compact->challenge_speed_value = record->challenge_speed_value
004401ca        compact->challenge_difficulty_value = record->challenge_difficulty_value
004401d3        compact->garbage_frequency.bits = record->garbage_frequency.bits
004401dc        compact->salt_frequency.bits = record->salt_frequency.bits
004401e2        compact->source_tail = record->source_tail
004401e8        compact->score = record->score
004401eb        int32_t score = record->score
004401f9        compact->checksum = (score * score) ^ 0xdeadbabe
004401ff        compact->runtime_build_seed = record->runtime_build_seed
00440208        compact->unknown_80 = record->unknown_1fab8
00440214        compact->unknown_84 = record->unknown_1fabc
0044021d        compact->runtime_build_flags = record->runtime_build_flags
00440223        compact->bank_selector = record->high_score_mode_tag
00440229        compact->entry_index = record->route_or_rank_index
0044022f        compact->replay_cursor = record->replay_cursor
00440235        int32_t i = 0
00440237        int16_t* out_lateral = &compact->replay_payload
0044023f        if (record->replay_sample_count s> 0)
00440241        struct ReplayRunRecord* lateral_run = &record->run_records
00440247        i += 1
00440248        *out_lateral = lateral_run->lateral_x
0044024e        lateral_run = &lateral_run[1]
00440251        out_lateral = &out_lateral[1]
00440256        do while (i s< record->replay_sample_count)
00440258        int32_t replay_sample_count_1 = record->replay_sample_count
0044025b        int32_t i_1 = 0
0044025f        int16_t* out_delta_z = &(&compact->replay_payload)[replay_sample_count_1 << 1]
00440266        if (replay_sample_count_1 s> 0)
00440268        int16_t* delta_z_source = &record->run_records[0].delta_z
0044026e        i_1 += 1
0044026f        *out_delta_z = *delta_z_source
00440275        delta_z_source = &delta_z_source[3]
00440278        out_delta_z = &out_delta_z[1]
0044027d        do while (i_1 s< record->replay_sample_count)
0044027f        int32_t replay_sample_count_2 = record->replay_sample_count
00440282        int32_t i_2 = 0
0044028d        if (replay_sample_count_2 s> 0)
0044028f        uint8_t* flag_source = &record->run_records[0].flags
00440292        uint8_t ecx_8 = *flag_source
00440294        flag_source = &flag_source[6]
00440297        (&compact->replay_payload)[(replay_sample_count_2 << 2) + i_2] = ecx_8
0044029d        i_2 += 1
004402a0        do while (i_2 s< record->replay_sample_count)
004402a2        int32_t replay_sample_count_3 = record->replay_sample_count
004402ae        compact->byte_count = replay_sample_count_3 * 5 + 0x88
004402b3        return replay_sample_count_3 * 5 + 0x88
