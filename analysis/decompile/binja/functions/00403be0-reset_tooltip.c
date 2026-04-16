/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: reset_tooltip @ 0x403be0 */

00403be3        int32_t state = tooltip->state
00403be6        int32_t result = state - 2
00403be9        if (state == 2)
00403c0a        tooltip->state = 1
00403beb        int32_t result_1 = result
00403beb        result -= 1
00403bec        if (result_1 == 1)
00403bf1        data_4df904
00403bfe        result = kill_border(tooltip->tooltip_widget)
00403c03        tooltip->tooltip_widget = nullptr
00403c0a        tooltip->state = 1
00403c12        return result
