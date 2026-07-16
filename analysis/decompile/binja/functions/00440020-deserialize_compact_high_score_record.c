/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: deserialize_compact_high_score_record @ 0x440020 */

00440028        int32_t score = compact->score
0044003b        if (compact->checksum != ((score * score) ^ 0xdeadbabe))
0044003d        record->active = 0
00440044        int32_t eax_1
00440044        eax_1.b = 0
00440047        return 0
0044004e        record->replay_sample_count = compact->replay_sample_count
00440054        record->replay_level_index = compact->replay_level_index
0044005a        record->replay_mode_id = compact->replay_mode_id
00440060        record->replay_speed_scalar.bits = compact->replay_speed_scalar.bits
0044006f        record->challenge_difficulty_scalar.bits = compact->challenge_difficulty_scalar.bits
00440072        rstrcpy_checked_ascii(&record->player_name, &compact->player_name)
00440085        record->score = compact->score
0044008b        __builtin_memcpy(&record->score_or_time, &compact->score_or_time, 0x18)
00440090        record->score_tail = compact->score_tail
00440096        record->challenge_speed_value = compact->challenge_speed_value
0044009c        record->challenge_difficulty_value = compact->challenge_difficulty_value
004400a2        record->garbage_frequency.bits = compact->garbage_frequency.bits
004400ab        record->salt_frequency.bits = compact->salt_frequency.bits
004400b4        record->source_tail = compact->source_tail
004400ba        record->runtime_build_seed = compact->runtime_build_seed
004400c3        record->unknown_1fab8 = compact->unknown_80
004400cf        record->unknown_1fabc = compact->unknown_84
004400d8        record->runtime_build_flags = compact->runtime_build_flags
004400de        record->high_score_mode_tag = compact->bank_selector
004400e4        int32_t replay_sample_count_2 = record->replay_sample_count
004400e7        record->route_or_rank_index = compact->entry_index
004400ed        int32_t i = 0
004400ef        record->replay_cursor = compact->replay_cursor
004400f2        int16_t* source_lateral = &compact->replay_payload
004400fa        if (replay_sample_count_2 s> 0)
004400fc        struct ReplayRunRecord* lateral_run = &record->run_records
00440102        i += 1
00440103        lateral_run->lateral_x = *source_lateral
00440109        source_lateral = &source_lateral[1]
0044010c        lateral_run = &lateral_run[1]
00440111        do while (i s< record->replay_sample_count)
00440113        int32_t replay_sample_count = record->replay_sample_count
00440116        int32_t i_1 = 0
0044011a        int16_t* source_delta_z = &(&compact->replay_payload)[replay_sample_count << 1]
00440121        if (replay_sample_count s> 0)
00440123        int16_t* delta_z_destination = &record->run_records[0].delta_z
00440129        i_1 += 1
0044012a        *delta_z_destination = *source_delta_z
00440130        delta_z_destination = &delta_z_destination[3]
00440133        source_delta_z = &source_delta_z[1]
00440138        do while (i_1 s< record->replay_sample_count)
0044013a        int32_t replay_sample_count_1 = record->replay_sample_count
0044013d        int32_t flag_index = 0
0044014a        if (replay_sample_count_1 s> 0)
0044014c        uint8_t* flag_destination = &record->run_records[0].flags
00440154        *flag_destination = zx.w((&compact->replay_payload)[(replay_sample_count_1 << 2) + flag_index])
0044015a        flag_index += 1
0044015b        flag_destination = &flag_destination[6]
00440160        do while (flag_index s< record->replay_sample_count)
00440162        record->active = 1
00440169        int32_t eax_9
00440169        eax_9.b = 1
0044016c        return 1
