/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: register_parcel_delivery @ 0x405040 */

0040504b        if (completion->delivered_parcel_count == completion->parcel_target_count)
0040504b        return
0040505d        add_subgoldy_score(&g_game_base->subgame.player, 4, 0)
0040506d        completion->delivered_parcel_count += 1
00405070        play_sound_effect(0x2d)
0040507d        if (completion->delivered_parcel_count != completion->parcel_target_count)
0040507d        return
00405084        if (completion->bonus_enabled != 0)
00405098        add_subgoldy_score(&g_game_base->subgame.player, 5, completion->bonus_score)
004050a4        play_sound_effect(0x31)
004050a9        completion->state = COMPLETION_STATE_SUMMARY_PENDING
004050b1        return
