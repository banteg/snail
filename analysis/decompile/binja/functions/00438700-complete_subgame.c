/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: complete_subgame @ 0x438700 */

0043870a        display_score_stats(&game->player)
00438715        int32_t eax_1 = game->replay_update_cursor * 3
00438718        (&game->current_high_score_record.run_records[0].flags)[eax_1 << 1] |= 8
00438735        game->current_high_score_record.replay_sample_count += 1
0043873b        game->replay_update_cursor += 1
0043874d        if ((1 & data_4b2f40) != 0)
0043874d        return
00438759        int32_t score_tail = game->player.score_tail
00438761        game->current_high_score_record.score = game->player.total_score
00438778        __builtin_memcpy(&game->current_high_score_record.score_or_time, &game->player.stopwatch, 0x18)
00438780        game->current_high_score_record.score_tail = score_tail
00438789        game->current_high_score_record.challenge_difficulty_value = game->completion_bonus_y_source
00438792        game->current_high_score_record.challenge_difficulty_scalar_bits = game->challenge_difficulty_scalar
0043879e        game->current_high_score_record.replay_speed_scalar_bits = game->rate_or_level_arg.base_rate
004387a4        int32_t level_mode = game->level_mode
004387a7        game->current_high_score_record.garbage_frequency = game->garbage_frequency
004387b9        game->current_high_score_record.challenge_speed_value = game->completion_bonus_x_source
004387bf        int32_t startup_track_index = game->player.startup_track_index
004387c5        game->current_high_score_record.salt_frequency = game->salt_frequency
004387ce        game->current_high_score_record.active = 1
004387d1        game->current_high_score_record.source_tail = startup_track_index
004387d7        game->current_high_score_record.replay_mode_id = level_mode
004387e2        if (level_mode == 1 && startup_track_index == 0)
004387de        return
004387e4        startup_track_index.b = game->selected_level_record_active
004387f2        if (startup_track_index.b != 0 || completed != 1)
004387f2        return
004387f7        if (level_mode == 0)
00438839        add_arcade_high_score(&game->sub_high_score.active_record_bank, &game->current_high_score_record, game->level_mode_arg)
00438839        return
004387fa        if (level_mode == 1)
00438824        add_survival_high_score(&game->sub_high_score.active_record_bank, &game->current_high_score_record)
0043882b        return
004387ff        if (level_mode == 4)
00438801        startup_track_index.b = game->player.completion_handoff_active
00438813        add_time_trial_high_score(&game->sub_high_score, &game->current_high_score_record.active, game->level_mode_arg, startup_track_index.b)
00438840        return
