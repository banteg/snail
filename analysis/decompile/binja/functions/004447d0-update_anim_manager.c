/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_anim_manager @ 0x4447d0 */

004447d0        float var_4 = arg1
004447d1        int32_t result_1 = *arg1
004447d3        int32_t i = 0
004447d6        float result = result_1
004447d9        arg1[4].b = 0
004447dc        if (result_1 != 0)
004447e2        float result_2 = result
004447e2        result -= 1
004447e3        if (result_2 == 1)
004447f0        long double x87_r7_1 = fconvert.t(*(data_4df904 + 0x74648))
0044480a        var_4 = fconvert.s((x87_r7_1 + x87_r7_1 - fconvert.t(0.200000003f) + fconvert.t(1f)) * fconvert.t(arg1[2]) + fconvert.t(arg1[1]))
0044480e        long double x87_r7_7 = fconvert.t(var_4)
00444812        long double temp2_1 = fconvert.t(1f)
00444812        x87_r7_7 - temp2_1
0044481c        arg1[1] = var_4
0044481f        result.w = (x87_r7_7 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp2_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp2_1 ? 1 : 0) << 0xe
00444823        if ((1 & result:1.b) == 0)
00444828        result.w = *arg1[3]
0044482d        if ((1 & result.b) != 0)
00444839        arg1[4].b = 1
0044483c        arg1[1] = fconvert.s(fconvert.t(var_4) - fconvert.t(1f))
00444843        if ((result.b & 4) != 0)
00444845        arg1[1] = 0x3f7fbe77
0044484c        arg1[2] = 0
0044484f        arg1[4].b = 1
00444856        if ((result.b & 2) != 0)
00444862        arg1[1] = fconvert.s(fconvert.t(2f) - fconvert.t(var_4))
0044486e        arg1[2] = fconvert.s(fconvert.t(arg1[2]) * fconvert.t(-1f))
00444871        long double x87_r7_14 = fconvert.t(arg1[1])
00444874        long double temp3_1 = fconvert.t(0f)
00444874        x87_r7_14 - temp3_1
0044487a        result.w = (x87_r7_14 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_14, temp3_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp3_1 ? 1 : 0) << 0xe
0044487f        if ((result:1.b & 1) != 0)
00444881        result = arg1[3]
00444887        if ((*result & 2) != 0)
0044488e        arg1[1] = fconvert.s(fneg(fconvert.t(arg1[1])))
0044489a        arg1[4].b = 1
0044489d        arg1[2] = fconvert.s(fconvert.t(arg1[2]) * fconvert.t(-1f))
004448a3        if ((*result & 8) != 0)
004448a5        arg1[1] = 0
004448a8        arg1[2] = 0
004448ab        arg1[4].b = 1
004448ae        long double x87_r7_19 = fconvert.t(arg1[1])
004448b1        long double temp4_1 = fconvert.t(0f)
004448b1        x87_r7_19 - temp4_1
004448b7        result.w = (x87_r7_19 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_19, temp4_1) ? 1 : 0) << 0xa | (x87_r7_19 == temp4_1 ? 1 : 0) << 0xe
004448bc        long double x87_r7_20
004448bc        if ((result:1.b & 1) == 0)
004448c6        long double x87_r7_21 = fconvert.t(arg1[1])
004448c9        long double temp5_1 = fconvert.t(0.999899983f)
004448c9        x87_r7_21 - temp5_1
004448cf        result.w = (x87_r7_21 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_21, temp5_1) ? 1 : 0) << 0xa | (x87_r7_21 == temp5_1 ? 1 : 0) << 0xe
004448d4        if ((result:1.b & 0x41) != 0)
004448de        x87_r7_20 = fconvert.t(arg1[1])
004448d6        x87_r7_20 = fconvert.t(0.999899983f)
004448be        x87_r7_20 = fconvert.t(0f)
004448e1        arg1[1] = fconvert.s(x87_r7_20)
004448ec        if (arg1[4].b != 0 && arg1[0xf] s> 0)
004448f1        result = &arg1[5]
004448f8        if (arg1[5] != 0xffffffff)
00444909        void* esi_3 = arg1[0x10]
00444912        *(esi_3 + 4) |= 0x20
0044491d        int32_t* esi_6 = (*result << 7) + arg1[0x11] + 0x24
00444923        void* edi_3 = *(*esi_6 + 0xbc)
00444929        arg1[1] = 0
0044492c        arg1[3] = edi_3
00444932        arg1[2] = *(edi_3 + 0x10)
0044493a        *(arg1[0x10] + 0x24) = *esi_6
004448fa        void* esi_2 = arg1[0x10]
004448fd        arg1[1] = 0
00444900        arg1[2] = 0
00444903        *(esi_2 + 4) &= 0xffffffdf
00444941        int32_t ebx_4 = arg1[0xf] - 1
00444944        arg1[0xf] = ebx_4
00444949        if (ebx_4 s> 0)
0044494e        i += 1
0044494f        *result = *(result i+ 4)
00444954        result += 4
00444959        do while (i s< arg1[0xf])
0044495e        return result
