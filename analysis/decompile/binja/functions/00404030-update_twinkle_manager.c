/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_twinkle_manager @ 0x404030 */

0040403b        if (manager->active_state != 1)
0040403b        return
00404043        int32_t i = 0
00404047        if (manager->twinkle_count s<= 0)
00404047        return
0040404a        struct TwinkleManager* twinkle = manager
0040404e        update_twinkle(twinkle)
00404059        i += 1
0040405a        twinkle = &twinkle->twinkles[1]
0040405f        do while (i s< manager->twinkle_count)
00404064        return
