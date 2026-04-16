/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_path_follow_golb @ 0x421770 */

00421774        *arg1 = 1
00421777        int32_t edx = *(arg2 + 0x38)
0042177a        *(arg1 + 8) = arg2
0042177d        *(arg1 + 4) = edx
00421784        *(arg1 + 0xc) = 0
0042178e        long double x87_r7_1 = fconvert.t(*(arg3 + 8)) - fconvert.t(*(arg2 + 0x18))
00421795        *(arg1 + 0x24) = arg4
00421798        *(arg1 + 0x10) = fconvert.s(x87_r7_1)
004217a4        *(arg1 + 0x14) = fconvert.s(fconvert.t(*(arg3 + 4)) - fconvert.t(0.49000001f))
004217a7        return arg4
