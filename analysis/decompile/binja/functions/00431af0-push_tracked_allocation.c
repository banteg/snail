/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: push_tracked_allocation @ 0x431af0 */

00431af9        arg1[*arg1 * 3 + 4] = arg3
00431b07        arg1[(*arg1 + 1) * 3] = arg2
00431b0c        int32_t result_1 = *arg1 + 1
00431b0d        int32_t result = result_1
00431b0f        *arg1 = result_1
00431b16        if (result s> 0x3a98)
00431b1d        result = report_errorf("Memory Stack Full")
00431b23        return result
