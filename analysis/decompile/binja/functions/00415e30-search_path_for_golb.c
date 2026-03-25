/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: search_path_for_golb @ 0x415e30 */

00415e39        int32_t i = 0
00415e3f        int32_t ecx = *arg1
00415e41        float var_20_1
00415e41        __builtin_strncpy(&var_20_1, "(knN", 8)
00415e4b        if (ecx s<= 0)
00415eed        return nullptr
00415e57        float* esi_1 = &arg1[4]
00415edc        void* result
00415e67        long double x87_r7_4 = fconvert.t(esi_1[-1]) - fconvert.t(arg2[1])
00415e6e        float var_c = fconvert.s(fconvert.t(esi_1[-2]) - fconvert.t(*arg2))
00415e7f        float var_8_1 = fconvert.s(x87_r7_4)
00415e83        float var_10_1 = fconvert.s(fconvert.t(*esi_1) - fconvert.t(arg2[2]))
00415e87        long double x87_r7_7 = fconvert.t(var_10_1)
00415e8b        long double temp1_1 = fconvert.t(0f)
00415e8b        x87_r7_7 - temp1_1
00415e95        float var_4_1 = var_10_1
00415e99        float eax_1
00415e99        eax_1.w = (x87_r7_7 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp1_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp1_1 ? 1 : 0) << 0xe
00415e9e        if ((eax_1:1.b & 0x41) == 0)
00415ea0        long double x87_r7_8 = fconvert.t(var_10_1)
00415ea4        long double temp2_1 = fconvert.t(30f)
00415ea4        x87_r7_8 - temp2_1
00415eaa        eax_1.w = (x87_r7_8 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp2_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp2_1 ? 1 : 0) << 0xe
00415eaf        if ((eax_1:1.b & 1) != 0)
00415eb5        long double st0_1 = vector_magnitude(&var_c)
00415eba        long double temp3_1 = fconvert.t(var_20_1)
00415eba        st0_1 - temp3_1
00415ebe        eax_1.w = (st0_1 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(st0_1, temp3_1) ? 1 : 0) << 0xa | (st0_1 == temp3_1 ? 1 : 0) << 0xe | 0x3800
00415ec3        if ((eax_1:1.b & 1) != 0)
00415ec5        var_20_1 = fconvert.s(st0_1)
00415ecc        result = &esi_1[-3]
00415ed6        i += 1
00415ed7        esi_1 = &esi_1[6]
00415edc        do while (i s< *arg1)
00415ee2        return result
