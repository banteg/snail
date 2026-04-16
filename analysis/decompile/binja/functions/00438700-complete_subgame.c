/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: complete_subgame @ 0x438700 */

0043870a        display_score_stats(&game->__offset(0x3bb764).d)
00438715        int32_t eax_1 = game->runtime_track_index * 3
00438718        game->_pad_00[(eax_1 << 1) + 0xfd2b84] |= 8
00438734        int32_t ecx_2 = game->runtime_track_index + 1
00438735        game->__offset(0xfd2b7c).d += 1
0043873b        game->runtime_track_index = ecx_2
0043874d        if ((1 & data_4b2f40) != 0)
0043874d        return 
00438759        int32_t eax_3 = game->__offset(0x3bba64).d
00438761        game->__offset(0xfd2b14).d = game->__offset(0x3bba48).d
00438778        __builtin_memcpy(&game->__offset(0xfd2b18).d, &game->stopwatch, 0x18)
0043877a        float challenge_difficulty_scalar = game->challenge_difficulty_scalar
0043877d        int32_t ecx_4 = game->_pad_00[0x28].d
00438780        game->__offset(0xfd2b30).d = eax_3
00438789        game->__offset(0xfd2b60).d = game->_pad_00[0x2c].d
0043878f        int32_t eax_5 = game->_pad_00[0x30].d
00438792        game->__offset(0xfd2b44).d = challenge_difficulty_scalar
00438798        int32_t esi_2 = game->__offset(0x125ffd8).d
0043879e        game->__offset(0xfd2b58).d = eax_5
004387a4        int32_t level_mode = game->level_mode
004387a7        game->__offset(0xff25c0).d = esi_2
004387ad        int32_t esi_3 = game->__offset(0x125ffdc).d
004387b9        game->__offset(0xfd2b5c).d = ecx_4
004387bf        int32_t ecx_5 = game->__offset(0x3bba68).d
004387c5        game->__offset(0xff25c4).d = esi_3
004387ce        game->__offset(0xfd2b10).d = 1
004387d1        game->__offset(0xfd2b34).d = ecx_5
004387d7        game->__offset(0xfd2b3c).d = level_mode
004387e2        if (level_mode == 1 && ecx_5 == 0)
004387de        return 
004387e4        ecx_5.b = game->selected_level_record_active
004387f2        if (ecx_5.b != 0 || outcome.b != 1)
004387f2        return 
004387f7        if (level_mode == 0)
00438839        add_arcade_high_score(&game->__offset(0x68b4c8).d, &game->__offset(0xfd2b10).d, game->level_mode_arg)
00438839        return 
004387fa        if (level_mode == 1)
00438824        add_survival_high_score(&game->__offset(0x68b4c8).d, &game->__offset(0xfd2b10).d)
0043882b        return 
004387ff        if (level_mode == 4)
00438801        ecx_5.b = game->__offset(0x3bbba4).b
00438813        add_time_trial_high_score(&game->__offset(0x68b4c8).d, &game->__offset(0xfd2b10).d, game->level_mode_arg, ecx_5.b)
00438840        return
