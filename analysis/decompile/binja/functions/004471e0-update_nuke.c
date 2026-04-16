/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_nuke @ 0x4471e0 */

004471e0        int32_t i_1 = arg1
004471e2        int32_t* edi = arg1
004471e4        int32_t result_1 = *edi
004471e6        void* result = result_1
004471e9        if (result_1 != 0)
004471ef        void* result_2 = result
004471ef        result -= 1
004471f0        if (result_2 == 1)
004471fc        edi[3] = fconvert.s(fconvert.t(edi[2]) + fconvert.t(edi[3]))
00447202        long double x87_r7_4 = fconvert.t(edi[5]) + fconvert.t(edi[4])
00447205        long double temp2_1 = fconvert.t(6.28318548f)
00447205        x87_r7_4 - temp2_1
0044720b        edi[4] = fconvert.s(x87_r7_4)
0044720b        bool c1_1 = unimplemented  {fst dword [edi+0x10], st0}
0044720e        result.w = (x87_r7_4 < temp2_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_4, temp2_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp2_1 ? 1 : 0) << 0xe | 0x3800
00447213        if ((result:1.b & 0x41) == 0)
0044721b        edi[4] = fconvert.s(x87_r7_4 - fconvert.t(6.28318548f))
00447224        int32_t i = 0
00447227        i_1 = 0
0044722b        int32_t* esi_1 = &edi[6]
00447243        long double x87_r7_10 = float.t(i_1) * fconvert.t(0.0399999991f) * fconvert.t(6.28318548f) + fconvert.t(edi[4])
00447246        *(*esi_1 + 0x50) = edi[3]
00447249        float var_4 = fconvert.s(x87_r7_10)
00447260        *(*esi_1 + 0x48) = fconvert.s(sine(var_4) * fconvert.t(7f))
00447268        long double x87_r7_14 = cosine(var_4) * fconvert.t(7f)
0044726e        result = *esi_1
00447273        i += 1
00447274        esi_1 = &esi_1[1]
0044727a        i_1 = i
0044727e        *(result + 0x4c) = fconvert.s(x87_r7_14)
00447281        do while (i s< 0x19)
00447288        return result
