/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: destroy_completion_screen @ 0x406060 */

00406063        data_4df904
00406073        kill_border(*(arg1 + 0x10))
00406078        data_4df904
00406087        kill_border(*(arg1 + 0x14))
0040608f        data_4df904
0040609c        kill_border(*(arg1 + 0x18))
004060ac        int32_t result = unhide_all_borders(data_4df904 + 0xb4c)
004060bb        *(data_4df904 + 0x1b8) = *(arg1 + 8)
004060c1        return result
