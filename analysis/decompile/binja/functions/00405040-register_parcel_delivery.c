/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: register_parcel_delivery @ 0x405040 */

00405043        int32_t result = controller->delivered_parcel_count
0040504b        if (result != controller->parcel_target_count)
0040505d        add_subgoldy_score(data_4df904 + 0x42fd7c, 4, 0)
0040506d        controller->delivered_parcel_count += 1
00405070        play_sound_effect(0x2d)
00405078        result = controller->parcel_target_count
0040507d        if (controller->delivered_parcel_count == result)
0040507f        result = controller->bonus_enabled
00405084        if (result != 0)
00405098        add_subgoldy_score(data_4df904 + 0x42fd7c, 5, controller->bonus_score)
004050a4        result = play_sound_effect(0x31)
004050a9        controller->state = 3
004050b1        return result
