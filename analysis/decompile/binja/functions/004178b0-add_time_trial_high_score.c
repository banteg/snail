/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: add_time_trial_high_score @ 0x4178b0 */

004178b4        int32_t result
004178b4        result.b = arg4
004178c6        *(arg2 + 0x3c) = 2
004178cd        *(arg2 + 0x40) = arg3
004178d0        *(arg2 + 0x44) = 0
004178d3        if (result.b == 0)
004178d5        *(arg2 + 8) = 0
004178e7        __builtin_memcpy(arg1 + 0x9080c8, arg2, 0x1fac0)
004178e9        if (result.b != 0)
004178f2        long double x87_r7_1 = fconvert.t(*(arg2 + 8))
00417901        void* ebp_1 = arg1 + arg3 * 0x1fac0
00417903        long double temp1_1 = fconvert.t(*(ebp_1 + 0x2b8c90))
00417903        x87_r7_1 - temp1_1
00417909        result.w = (x87_r7_1 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp1_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp1_1 ? 1 : 0) << 0xe
0041790e        if ((result:1.b & 1) != 0)
00417930        __builtin_memcpy(ebp_1 + 0x2b8c88, arg2, 0x1fac0)
00417932        *(ebp_1 + 0x2b8cc8) = arg3
00417910        long double x87_r7_2 = fconvert.t(*(ebp_1 + 0x2b8c90))
00417916        long double temp2_1 = fconvert.t(0f)
00417916        x87_r7_2 - temp2_1
0041791c        result.w = (x87_r7_2 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp2_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp2_1 ? 1 : 0) << 0xe
00417921        if ((result:1.b & 0x40) != 0)
00417930        __builtin_memcpy(ebp_1 + 0x2b8c88, arg2, 0x1fac0)
00417932        *(ebp_1 + 0x2b8cc8) = arg3
0041793c        return result
