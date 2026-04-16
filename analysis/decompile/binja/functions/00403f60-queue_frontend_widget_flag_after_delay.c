/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: queue_frontend_widget_flag_after_delay @ 0x403f60 */

00403f63        char result = *(arg1 + 0x435a0)
00403f6b        if (result == 0)
00403f7c        if ((*(arg2 + 0x1a0) & 0x40000000) != 0)
00403f88        result = begin_frontend_fade_out(data_4df904 + 0x24, 0)
00403f91        *(arg1 + 0x435ac) = arg2
00403f97        *(arg1 + 0x435a0) = 1
00403f9e        *(arg1 + 0x435a4) = 0
00403fa8        *(arg1 + 0x435a8) = 0x3daaaaab
00403fb2        *(arg1 + 0x4359c) = arg3
00403fba        return result
