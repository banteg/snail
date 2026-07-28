/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: complete_subgame @ 0x438700 */

0043870a        display_score_stats(&game->player)
00438715        int32_t eax_1 = game->replay_update_cursor * 3
00438718        (&game->current_high_score_record.run_records[0].flags)[eax_1].b |= 8
00438734        int32_t ecx_2 = game->replay_update_cursor + 1
00438735        game->current_high_score_record.replay_sample_count += 1
0043873b        game->replay_update_cursor = ecx_2
0043874d        if ((1 & g_cheat_state.flags.b) != 0)
0043874d        return
00438759        int32_t score_tail = game->player.score_tail
00438761        game->current_high_score_record.score = game->player.total_score
00438778        __builtin_memcpy(&game->current_high_score_record.score_or_time, &game->player.stopwatch, 0x18)
0043877a        float challenge_difficulty_scalar = game->challenge_difficulty_scalar
0043877d        int32_t challenge_speed_value = game->challenge_speed_value
00438780        game->current_high_score_record.score_tail = score_tail
00438789        game->current_high_score_record.challenge_difficulty_value = game->challenge_difficulty_value
0043878f        union SubSolutionScalar base_rate = game->rate_or_level_arg.base_rate
00438792        game->current_high_score_record.challenge_difficulty_scalar.bits = challenge_difficulty_scalar
00438798        float garbage_frequency = game->garbage_frequency
0043879e        game->current_high_score_record.replay_speed_scalar.bits = base_rate
004387a4        int32_t level_mode = game->level_mode
004387a7        game->current_high_score_record.garbage_frequency.bits = garbage_frequency
004387ad        float salt_frequency = game->salt_frequency
004387b9        game->current_high_score_record.challenge_speed_value = challenge_speed_value
004387bf        int32_t replay_start_cursor = game->player.replay_start_cursor
004387c5        game->current_high_score_record.salt_frequency.bits = salt_frequency
004387ce        game->current_high_score_record.active = 1
004387d1        game->current_high_score_record.replay_start_cursor = replay_start_cursor
004387d7        game->current_high_score_record.replay_mode_id = level_mode
004387e2        if (level_mode == 1 && replay_start_cursor == 0)
004387de        return
004387e4        replay_start_cursor.b = game->selected_level_record_active
004387f2        if (replay_start_cursor.b != 0 || completed != 1)
004387f2        return
004387f7        if (level_mode == 0)
00438839        add_arcade_high_score(&game->sub_high_score, &game->current_high_score_record, game->level_mode_arg)
00438839        return
004387fa        if (level_mode == 1)
00438824        add_survival_high_score(&game->sub_high_score, &game->current_high_score_record)
0043882b        return
004387ff        if (level_mode == 4)
00438801        replay_start_cursor.b = game->player.completion_handoff_active
00438813        add_time_trial_high_score(&game->sub_high_score, &game->current_high_score_record, game->level_mode_arg, replay_start_cursor.b)
00438840        return
