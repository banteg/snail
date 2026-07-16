/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_high_score_entry @ 0x417a70 */

00417a7d        record->runtime_build_seed = runtime_build_seed
00417a80        record->replay_sample_count = 0
00417a83        record->score = 0
00417a86        zero_timer_counters(&record->score_or_time)
00417a93        record->replay_level_index = replay_level_index
00417a96        record->replay_speed_scalar.bits = replay_speed_scalar_bits
00417aa8        rstrcpy_checked_ascii(&record->player_name, &g_game_base->players[0].player_name)
00417ab9        record->high_score_mode_tag = high_score_mode_tag
00417abc        record->route_or_rank_index = route_or_rank_index
00417ac2        record->active = 0
00417ac4        record->runtime_build_flags = runtime_build_flags
00417ac7        record->replay_cursor = 0
00417aca        int16_t* eax_3 = &record->run_records[0].delta_z
00417acd        int32_t i_1 = 0x5460
00417ae1        int32_t i
00417ad2        (eax_3 - 0x72)->run_records[0].lateral_x = 0
00417ad6        (eax_3 - 0x72)->run_records[0].delta_z = 0
00417ad9        (eax_3 - 0x72)->run_records[0].flags = 0
00417ad9        (eax_3 - 0x72)->run_records[0].reserved_05 = 0
00417add        eax_3 = &eax_3[3]
00417ae0        i = i_1
00417ae0        i_1 -= 1
00417ae1        do while (i != 1)
00417ae5        return
