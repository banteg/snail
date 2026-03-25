/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: explode_slug_hazard @ 0x43f680 */

0043f689        int32_t result_1 = 0x46
0043f89e        int32_t result
0043f89e        bool cond:0_1
0043f6ac        float var_3c_2 = fconvert.s(float.t(next_math_random_value()) * fconvert.t(6.10351572e-06f) + fconvert.t(0.200000003f))
0043f6df        float var_40_2 = fconvert.s(float.t(next_math_random_value()) * fconvert.t(3.05175781e-05f) * fconvert.t(0.75f) + fconvert.t(0.25f))
0043f6e3        int32_t* eax_3 = allocate_sprite(&data_790f30, 1, 0x81, 0xffffffff, 0xffffffff)
0043f6e8        long double x87_r7_8 = fconvert.t(var_40_2)
0043f6f0        int32_t edx_1 = eax_3[1]
0043f6f3        eax_3[0x1a] = 0
0043f6fc        eax_3[1] = edx_1 | 0x802
0043f6ff        eax_3[0x22] = fconvert.s(x87_r7_8 + x87_r7_8)
0043f730        long double x87_r7_15 = fconvert.t(1f) / ((float.t(next_math_random_value()) * fconvert.t(1.52587891e-05f) + fconvert.t(0.600000024f)) * fconvert.t(60f)) * fconvert.t(*(*(arg1 + 0x88) + 0x38))
0043f733        eax_3[0x1c] = 0
0043f736        eax_3[0x1d] = 0
0043f739        eax_3[0x1b] = fconvert.s(x87_r7_15)
0043f745        int32_t var_54_1 = 0x1fff
0043f75c        set_color_grayscale(&eax_3[0xb], fconvert.s(float.t(next_math_random_value()) * fconvert.t(9.1552738e-06f) + fconvert.t(0.699999988f)))
0043f76b        eax_3[0x18] = fconvert.s(fconvert.t(var_40_2) * fconvert.t(0.300000012f))
0043f778        eax_3[0x19] = fconvert.s(fconvert.t(var_40_2) * fconvert.t(1.20000005f))
0043f781        long double x87_r7_23 = fconvert.t(*(*(arg1 + 0x88) + 0x38))
0043f794        eax_3[0x1e] = fconvert.s(x87_r7_23 * x87_r7_23 * fconvert.t(-0.00999999978f) * fconvert.t(2.20000005f))
0043f7b6        float var_18_1 = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(var_3c_2) * fconvert.t(6.10351562e-05f))
0043f7ba        int32_t eax_8 = next_math_random_value()
0043f7c3        void* ebx_1 = *(arg1 + 0x88)
0043f7fa        long double x87_r7_35 = float.t(next_math_random_value()) * fconvert.t(var_3c_2) * fconvert.t(3.05175781e-05f) + fconvert.t(*(ebx_1 + 0x3bbb7c))
0043f800        long double x87_r6_7 = fconvert.t(*(ebx_1 + 0x38))
0043f81c        eax_3[0x15] = fconvert.s(x87_r6_7 * fconvert.t(var_18_1))
0043f82a        eax_3[0x16] = fconvert.s(fconvert.t(fconvert.s(float.t(eax_8) * (fconvert.t(var_3c_2) + fconvert.t(0.300000012f)) * fconvert.t(3.05175781e-05f))) * x87_r6_7)
0043f837        eax_3[0x17] = fconvert.s(x87_r7_35 * x87_r6_7)
0043f84a        long double x87_r7_39 = float.t(next_math_random_value()) * fconvert.t(0.000305175781f)
0043f87a        float var_20_1 = fconvert.s(fconvert.t(fconvert.s(x87_r7_39 * fconvert.t(eax_3[0x16]))) + fconvert.t(*(arg1 + 0x6c)))
0043f882        long double x87_r7_41 = x87_r7_39 * fconvert.t(eax_3[0x17]) + fconvert.t(*(arg1 + 0x70))
0043f885        eax_3[0x12] = fconvert.s(fconvert.t(fconvert.s(x87_r7_39 * fconvert.t(eax_3[0x15]))) + fconvert.t(*(arg1 + 0x68)))
0043f887        eax_3[0x13] = var_20_1
0043f892        eax_3[0x14] = fconvert.s(x87_r7_41)
0043f899        result = result_1 - 1
0043f899        cond:0_1 = result_1 != 1
0043f89a        result_1 = result
0043f89e        do while (cond:0_1)
0043f8ab        return result
