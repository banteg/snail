/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_backdrop_texture_target @ 0x410f40 */

00410f46        long double x87_r7 = fconvert.t(1f) - fconvert.t(*(arg1 + 0x68c))
00410f52        int32_t edx = *(arg1 + 0x6b8)
00410f58        *(arg1 + 0x694) = *(arg1 + 0x698)
00410f62        *(arg1 + 0x698) = arg2
00410f68        *(arg1 + 0x6b4) = edx
00410f6e        *(arg1 + 0x68c) = fconvert.s(x87_r7)
00410f7a        long double x87_r7_2 = fconvert.t(1f) - fconvert.t(*(arg1 + 0x6ac))
00410f80        *(arg1 + 0x6b8) = arg2
00410f86        *(arg1 + 0x6ac) = fconvert.s(x87_r7_2)
00410f8c        return arg2
