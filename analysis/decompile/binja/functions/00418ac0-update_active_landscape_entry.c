/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_active_landscape_entry @ 0x418ac0 */

00418ac0        void* result = data_4df904
00418acd        if (*(result + 0x74621) == 0)
00418acf        int32_t result_1 = *(arg1 + 0x80)
00418ad5        result = result_1
00418ad8        if (result_1 != 0)
00418ada        void* result_2 = result
00418ada        result -= 1
00418adb        if (result_2 == 1)
00418add        void* edx_1 = *(arg1 + 0x24)
00418ae1        void* esi_1 = *(arg1 + 0x8c)
00418aed        long double x87_r7_2 = fconvert.t(*(edx_1 + 0xb8)) + fconvert.t(*(arg1 + 0x70))
00418af3        long double x87_r6_2 = fconvert.t(*(esi_1 + 0x70)) - fconvert.t(10f)
00418af9        x87_r6_2 - x87_r7_2
00418afb        result.w = (x87_r6_2 < x87_r7_2 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_2, x87_r7_2) ? 1 : 0) << 0xa | (x87_r6_2 == x87_r7_2 ? 1 : 0) << 0xe
00418b00        if ((result:1.b & 0x41) == 0)
00418b11        *(arg1 + 0x70) = fconvert.s(fconvert.t(*(arg1 + 0x88)) * fconvert.t(3f) + fconvert.t(*(arg1 + 0x70)))
00418b20        long double x87_r7_7 = fconvert.t(*(edx_1 + 0xac)) + fconvert.t(*(arg1 + 0x70))
00418b26        long double x87_r6_4 = fconvert.t(*(data_4df904 + 0xc)) + fconvert.t(*(esi_1 + 0x70))
00418b2a        x87_r6_4 - x87_r7_7
00418b2c        result.w = (x87_r6_4 < x87_r7_7 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_4, x87_r7_7) ? 1 : 0) << 0xa | (x87_r6_4 == x87_r7_7 ? 1 : 0) << 0xe
00418b2e        bool cond:0_1 = (result:1.b & 1) == 0
00418b31        result = *(arg1 + 4)
00418b34        if (not(cond:0_1))
00418b36        result.b &= 0xdf
00418b38        *(arg1 + 4) = result
00418b3b        return result
00418b3c        result.b |= 0x20
00418b3e        *(arg1 + 4) = result
00418b41        return result
