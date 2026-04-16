/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_twinkle @ 0x404080 */

0040408a        long double x87_r7_1 = fconvert.t(arg1[6]) + fconvert.t(arg1[7])
0040408d        long double temp0 = fconvert.t(6.28318548f)
0040408d        x87_r7_1 - temp0
00404093        arg1[6] = fconvert.s(x87_r7_1)
00404093        bool c1 = unimplemented  {fst dword [esi+0x18], st0}
0040409b        if ((((x87_r7_1 < temp0 ? 1 : 0) << 8 | (c1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_1, temp0) ? 1 : 0) << 0xa | (x87_r7_1 == temp0 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) != 0)
004040a8        long double temp1_1 = fconvert.t(0f)
004040a8        x87_r7_1 - temp1_1
004040b3        if ((((x87_r7_1 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp1_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp1_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
004040bb        arg1[6] = fconvert.s(x87_r7_1 + fconvert.t(6.28318548f))
004040a3        arg1[6] = fconvert.s(x87_r7_1 - fconvert.t(6.28318548f))
004040c2        int32_t eax_1 = *arg1
004040c5        int32_t eax_4
004040c5        if (eax_1 == 1)
004041a4        eax_4 = *(arg1[0xb] + 0x1a0)
004041b5        if ((eax_4.b & 2) != 0 && (eax_4:1.b & 0x80) == 0)
004041be        long double x87_r7_22 = fconvert.t(arg1[2]) + fconvert.t(arg1[3])
004041c1        arg1[2] = fconvert.s(x87_r7_22)
004041c4        long double temp6_1 = fconvert.t(1f)
004041c4        x87_r7_22 - temp6_1
004041ca        eax_4.w = (x87_r7_22 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_22, temp6_1) ? 1 : 0) << 0xa | (x87_r7_22 == temp6_1 ? 1 : 0) << 0xe
004041cf        if ((eax_4:1.b & 0x41) == 0)
004041d7        *arg1 = 2
004041dd        arg1[4] = 0
004041e0        __builtin_strncpy(&arg1[5], "fff?", 4)
00404200        arg1[6] = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(0.000191747604f))
00404216        long double x87_r7_28 = (float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(6.10351562e-05f)
0040421c        long double temp9_1 = fconvert.t(0f)
0040421c        x87_r7_28 - temp9_1
00404222        int32_t eax_9
00404222        eax_9.w = (x87_r7_28 < temp9_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_28, temp9_1) ? 1 : 0) << 0xa | (x87_r7_28 == temp9_1 ? 1 : 0) << 0xe
00404227        int32_t var_8_4
00404227        if ((eax_9:1.b & 1) == 0)
00404240        var_8_4 = 0
0040424a        long double x87_r7_31 = (float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(6.10351562e-05f)
00404250        long double temp11_1 = fconvert.t(0f)
00404250        x87_r7_31 - temp11_1
00404256        int32_t eax_10
00404256        eax_10.w = (x87_r7_31 < temp11_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_31, temp11_1) ? 1 : 0) << 0xa | (x87_r7_31 == temp11_1 ? 1 : 0) << 0xe
0040425b        if ((eax_10:1.b & 0x40) == 0)
0040425d        var_8_4 = 1
00404229        var_8_4 = 0xffffffff
00404265        int32_t eax_11 = next_math_random_value()
0040426e        arg1[2] = 0
00404275        void* edi_1 = arg1[0xb]
00404278        arg1[3] = 0x3f800000
004042a7        arg1[7] = fconvert.s(fconvert.t(1f) / (((float.t(eax_11) - fconvert.t(16384f)) * fconvert.t(6.10351562e-05f) + fconvert.t(5f)) * fconvert.t(60f)) * float.t(var_8_4) * fconvert.t(6.28318548f))
004042b3        long double x87_r7_40 = float.t(next_math_random_value())
004042dd        void* edi_2 = arg1[0xb]
004042e2        arg1[8] = fconvert.s(x87_r7_40 * fconvert.t(*(edi_1 + 0x248)) * fconvert.t(0.800000012f) * fconvert.t(3.05175781e-05f) + fconvert.t(*(edi_1 + 0x238)) + fconvert.t(*(edi_1 + 0x248)) * fconvert.t(0.100000001f))
0040431a        arg1[9] = fconvert.s(float.t(next_math_random_value()) * fconvert.t(*(edi_2 + 0x24c)) * fconvert.t(0.800000012f) * fconvert.t(3.05175781e-05f) + fconvert.t(*(edi_2 + 0x24c)) * fconvert.t(0.100000001f) + fconvert.t(*(edi_2 + 0x23c)))
0040431d        eax_4 = next_math_random_value()
0040433c        arg1[0xa] = fconvert.s((float.t(eax_4) - fconvert.t(16384f)) * fconvert.t(0.000732421875f) + fconvert.t(25f))
004040cc        if (eax_1 == 2)
00404162        long double x87_r7_19 = (fconvert.t(arg1[5]) - fconvert.t(arg1[4])) * fconvert.t(0.100000001f) + fconvert.t(arg1[4])
00404165        arg1[4] = fconvert.s(x87_r7_19)
00404168        long double x87_r7_20 = fconvert.t(arg1[5]) - x87_r7_19
0040416b        long double temp4 = fconvert.t(0f)
0040416b        x87_r7_20 - temp4
00404171        int32_t eax_3
00404171        eax_3.w = (x87_r7_20 < temp4 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_20, temp4) ? 1 : 0) << 0xa | (x87_r7_20 == temp4 ? 1 : 0) << 0xe | 0x3800
00404176        if ((eax_3:1.b & 1) != 0)
00404178        x87_r7_20 = fneg(x87_r7_20)
0040417a        long double temp7 = fconvert.t(0.00999999978f)
0040417a        x87_r7_20 - temp7
00404180        eax_3.w = (x87_r7_20 < temp7 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_20, temp7) ? 1 : 0) << 0xa | (x87_r7_20 == temp7 ? 1 : 0) << 0xe
00404185        if ((eax_3:1.b & 1) != 0)
00404187        arg1[5] = 0
0040418e        *arg1 = 4
004041a0        return draw_twinkle()
004040d2        eax_4 = eax_1 - 4
004040d5        if (eax_1 == 4)
004040ec        arg1[4] = fconvert.s((fconvert.t(arg1[5]) - fconvert.t(arg1[4])) * fconvert.t(0.100000001f) + fconvert.t(arg1[4]))
004040ef        draw_twinkle()
004040f7        long double x87_r7_10 = fconvert.t(arg1[5]) - fconvert.t(arg1[4])
004040fa        long double temp8_1 = fconvert.t(0f)
004040fa        x87_r7_10 - temp8_1
00404100        eax_4.w = (x87_r7_10 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_10, temp8_1) ? 1 : 0) << 0xa | (x87_r7_10 == temp8_1 ? 1 : 0) << 0xe | 0x3800
00404105        if ((eax_4:1.b & 1) != 0)
00404107        x87_r7_10 = fneg(x87_r7_10)
00404109        long double temp10_1 = fconvert.t(0.00999999978f)
00404109        x87_r7_10 - temp10_1
0040410f        eax_4.w = (x87_r7_10 < temp10_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_10, temp10_1) ? 1 : 0) << 0xa | (x87_r7_10 == temp10_1 ? 1 : 0) << 0xe
00404114        if ((eax_4:1.b & 1) != 0)
0040411c        *arg1 = 1
00404122        arg1[4] = 0
00404125        arg1[2] = 0
00404128        int32_t eax_5 = next_math_random_value()
0040414e        arg1[3] = fconvert.s(fconvert.t(1f) / ((float.t(eax_5) * fconvert.t(3.05175781e-05f) + fconvert.t(0.00999999978f)) * fconvert.t(60f)))
00404155        return eax_5
00404344        return eax_4
