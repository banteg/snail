/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_logo_row @ 0x419a90 */

00419a99        *(arg1 + 0x68) = fconvert.s(fconvert.t(*(arg1 + 0x80)) + fconvert.t(*(arg1 + 0x68)))
00419aa5        *(arg1 + 0x6c) = fconvert.s(fconvert.t(*(arg1 + 0x84)) + fconvert.t(*(arg1 + 0x6c)))
00419ab1        *(arg1 + 0x70) = fconvert.s(fconvert.t(*(arg1 + 0x88)) + fconvert.t(*(arg1 + 0x70)))
00419ab4        long double x87_r7_5 = fconvert.t(*(arg1 + 0x70))
00419ab7        long double temp0 = fconvert.t(8f)
00419ab7        x87_r7_5 - temp0
00419ac2        if ((((x87_r7_5 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp0) ? 1 : 0) << 0xa | (x87_r7_5 == temp0 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
00419ae4        *(arg1 + 0x34) = 0x3f7fbe77
00419adf        *(arg1 + 0x34) = fconvert.s((fconvert.t(1f) - (fconvert.t(*(arg1 + 0x70)) - fconvert.t(8f)) * fconvert.t(0.125f)) * fconvert.t(0.999000013f))
00419aeb        void* eax_1 = *(arg1 + 0x24)
00419aee        *(eax_1 + 0x10) |= 0x10
00419af2        long double x87_r7_11 = fconvert.t(*(arg1 + 0x70))
00419af5        long double temp1 = fconvert.t(16f)
00419af5        x87_r7_11 - temp1
00419afb        eax_1.w = (x87_r7_11 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_11, temp1) ? 1 : 0) << 0xa | (x87_r7_11 == temp1 ? 1 : 0) << 0xe
00419b00        if ((eax_1:1.b & 0x41) != 0)
00419b02        long double x87_r7_12 = fconvert.t(*(arg1 + 0x70))
00419b05        long double temp2_1 = fconvert.t(-4f)
00419b05        x87_r7_12 - temp2_1
00419b0b        eax_1.w = (x87_r7_12 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_12, temp2_1) ? 1 : 0) << 0xa | (x87_r7_12 == temp2_1 ? 1 : 0) << 0xe
00419b10        if ((eax_1:1.b & 1) == 0)
00419b15        int32_t eax_2
00419b15        eax_2.b = (*(arg1 + 4)).b | 0x20
00419b17        *(arg1 + 4) = eax_2
00419b1a        return eax_2
00419b1e        int32_t eax_3
00419b1e        eax_3.b = (*(arg1 + 4)).b & 0xdf
00419b20        *(arg1 + 4) = eax_3
00419b23        return eax_3
