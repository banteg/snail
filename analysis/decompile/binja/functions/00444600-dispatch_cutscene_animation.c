/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: dispatch_cutscene_animation @ 0x444600 */

00444606        if (arg3 == 0)
004446c6        *(arg1 + (*(arg1 + 0x140) << 2) + 0x118) = arg2
004446d3        int32_t eax_8 = *(arg1 + 0x140) + 1
004446d4        *(arg1 + 0x140) = eax_8
004446da        return eax_8
00444611        int32_t eax_2 = arg2 << 7
00444622        int16_t* eax_3 = *(*(eax_2 + arg1 + 0x170) + 0xbc)
0044462f        *(arg1 + 0x110) = eax_3
00444635        if (arg4 != 0xffffffff)
00444637        *eax_3 = arg4.w
0044463a        char* edx_2 = *(arg1 + 0x110)
00444643        if ((*edx_2 & 8) == 0)
00444670        void* edx_3 = *(arg1 + 0x110)
00444676        *(arg1 + 0x108) = 0
00444680        long double x87_r7_4 = fconvert.t(*(edx_3 + 0x10))
00444683        long double temp1_1 = fconvert.t(0f)
00444683        x87_r7_4 - temp1_1
00444689        long double x87_r7_5 = fconvert.t(*(edx_3 + 0x10))
0044468c        eax_3.w = (x87_r7_4 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp1_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp1_1 ? 1 : 0) << 0xe | 0x3800
00444691        if ((eax_3:1.b & 1) != 0)
00444693        x87_r7_5 = fneg(x87_r7_5)
00444695        *(arg1 + 0x10c) = fconvert.s(x87_r7_5)
00444645        long double x87_r7 = fconvert.t(*(edx_2 + 0x10))
00444648        long double temp2_1 = fconvert.t(0f)
00444648        x87_r7 - temp2_1
0044464e        long double x87_r7_1 = fconvert.t(*(edx_2 + 0x10))
00444651        eax_3.w = (x87_r7 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp2_1) ? 1 : 0) << 0xa | (x87_r7 == temp2_1 ? 1 : 0) << 0xe | 0x3800
00444656        if ((eax_3:1.b & 1) != 0)
00444658        x87_r7_1 = fneg(x87_r7_1)
0044465a        long double x87_r7_2 = fneg(x87_r7_1)
0044465c        *(arg1 + 0x10c) = fconvert.s(x87_r7_2)
00444668        *(arg1 + 0x108) = fconvert.s(x87_r7_2 + fconvert.t(1f))
0044469b        int32_t eax_4 = *(eax_2 + arg1 + 0x170)
0044469d        *(arg1 + 0x140) = 0
004446a7        *(arg1 + 0x24) = eax_4
004446aa        void* ecx = *(arg1 + 0x144)
004446b4        int32_t eax_5
004446b4        eax_5.b = (*(ecx + 4)).b | 0x20
004446b6        *(ecx + 4) = eax_5
004446b9        return eax_5
