/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_high_score_entry @ 0x417a70 */

00417a7d        arg1[0x1a] = arg2
00417a80        arg1[0x1b] = 0
00417a83        arg1[1] = 0
00417a86        zero_timer_counters()
00417a93        arg1[0xa] = arg3
00417a96        arg1[0x12] = arg4
00417aa8        sub_44e5b0(&arg1[0x15], data_4df904 + 0x1a4)
00417ab9        arg1[0xf] = arg6
00417abc        arg1[0x10] = arg7
00417ac2        *arg1 = 0
00417ac4        arg1[0xe] = arg5
00417ac7        arg1[0x11] = 0
00417aca        int16_t* result = arg1 + 0x72
00417acd        int32_t i_1 = 0x5460
00417ae1        int32_t i
00417ad2        result[-1] = 0
00417ad6        *result = 0
00417ad9        result[1] = 0
00417add        result = &result[3]
00417ae0        i = i_1
00417ae0        i_1 -= 1
00417ae1        do while (i != 1)
00417ae5        return result
