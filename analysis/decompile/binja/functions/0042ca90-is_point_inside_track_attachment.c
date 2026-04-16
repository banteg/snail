/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: is_point_inside_track_attachment @ 0x42ca90 */

0042ca9f        float ecx = *(arg5 + 0x10)
0042caa1        int32_t edi = *(arg1 + 0x44)
0042caa4        int32_t i = edi - 1
0042caa9        float edx = *(arg5 + 0x14)
0042cab3        float var_1c = *(arg5 + 0x18)
0042cab7        int32_t result
0042cab7        if (edi - 1 s>= 0)
0042cac9        int32_t esi_2 = i * 0xa8
0042cacc        int32_t ecx_1 = *(arg1 + 0x5c)
0042caf1        float var_4_1 = fconvert.s(fconvert.t(var_1c) + fconvert.t(*(esi_2 + ecx_1 + 0x38)))
0042cb09        long double x87_r7_5 = fconvert.t(arg3) - fconvert.t(fconvert.s(fconvert.t(edx) + fconvert.t(*(esi_2 + ecx_1 + 0x34))))
0042cb0d        float var_30 = fconvert.s(fconvert.t(arg2) - (fconvert.t(ecx) + fconvert.t(*(esi_2 + ecx_1 + 0x30))))
0042cb11        float var_14_1 = fconvert.s(x87_r7_5)
0042cb29        float var_10_1 = fconvert.s(fconvert.t(arg4) - fconvert.t(var_4_1))
0042cb35        rotate_vector_by_matrix(&var_30, esi_2 + ecx_1 + 0x40)
0042cb3a        int32_t ecx_4 = *(arg1 + 0x54)
0042cb3f        int32_t eax_7
0042cb3f        int32_t edx_3
0042cb3f        edx_3:eax_7 = sx.q(ecx_4)
0042cb4e        long double x87_r7_9 = float.t(neg.d((eax_7 - edx_3) s>> 1)) - fconvert.t(0.300000012f)
0042cb54        long double temp2_1 = fconvert.t(var_30)
0042cb54        x87_r7_9 - temp2_1
0042cb58        result.w = (x87_r7_9 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp2_1) ? 1 : 0) << 0xa | (x87_r7_9 == temp2_1 ? 1 : 0) << 0xe
0042cb5d        if ((result:1.b & 1) != 0)
0042cb61        int32_t eax_11
0042cb61        int32_t edx_4
0042cb61        edx_4:eax_11 = sx.q(ecx_4)
0042cb6e        long double x87_r7_11 = float.t((eax_11 - edx_4) s>> 1) + fconvert.t(0.300000012f)
0042cb74        long double temp3_1 = fconvert.t(var_30)
0042cb74        x87_r7_11 - temp3_1
0042cb78        result.w = (x87_r7_11 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_11, temp3_1) ? 1 : 0) << 0xa | (x87_r7_11 == temp3_1 ? 1 : 0) << 0xe
0042cb7d        if ((result:1.b & 0x41) == 0)
0042cb7f        long double x87_r7_12 = fconvert.t(var_14_1)
0042cb83        long double temp4_1 = fconvert.t(-0.300000012f)
0042cb83        x87_r7_12 - temp4_1
0042cb89        result.w = (x87_r7_12 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_12, temp4_1) ? 1 : 0) << 0xa | (x87_r7_12 == temp4_1 ? 1 : 0) << 0xe
0042cb8e        if ((result:1.b & 1) == 0)
0042cb90        long double x87_r7_13 = fconvert.t(var_14_1)
0042cb94        long double temp5_1 = fconvert.t(0.300000012f)
0042cb94        x87_r7_13 - temp5_1
0042cb9a        result.w = (x87_r7_13 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_13, temp5_1) ? 1 : 0) << 0xa | (x87_r7_13 == temp5_1 ? 1 : 0) << 0xe
0042cb9f        if ((result:1.b & 1) != 0)
0042cba1        long double x87_r7_14 = fconvert.t(var_10_1)
0042cba5        long double temp6_1 = fconvert.t(0f)
0042cba5        x87_r7_14 - temp6_1
0042cbab        result.w = (x87_r7_14 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_14, temp6_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp6_1 ? 1 : 0) << 0xe
0042cbb0        if ((result:1.b & 0x41) == 0)
0042cbb5        long double x87_r7_15 = fconvert.t(var_10_1)
0042cbb9        long double temp7_1 = fconvert.t(*(esi_2 + *(arg1 + 0x5c) + 0x8c))
0042cbb9        x87_r7_15 - temp7_1
0042cbc0        result.w = (x87_r7_15 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_15, temp7_1) ? 1 : 0) << 0xa | (x87_r7_15 == temp7_1 ? 1 : 0) << 0xe
0042cbc5        if ((result:1.b & 1) != 0)
0042cbe3        result.b = 1
0042cbe9        return result
0042cbc7        i -= 1
0042cbc8        esi_2 -= 0xa8
0042cbd0        do while (i s>= 0)
0042cbd8        result.b = 0
0042cbde        return result
