/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: draw_frontend_widget @ 0x401130 */

0040115d        int32_t* result
0040115d        result.b = data_4b7236
00401164        if (result.b != 0)
0040116a        result = *(arg1 + 0x1a0)
00401173        if ((result:1.b & 0x10) == 0)
00401180        int32_t var_70_1
00401180        int32_t ebx_1
00401180        if ((data_4df934 & 0x80) != 0)
0040119a        var_70_1 = 3
004011a2        ebx_1 = 3
00401182        ebx_1 = 0
00401184        int32_t var_24_1 = 0x3f800000
0040118c        int32_t var_14_1 = 0x3f800000
00401194        var_70_1 = 0
004011ac        float edx_1 = *(arg1 + 0x24c)
004011b7        float var_68_1 = *(arg1 + 0x248)
004011bf        float ecx_4
004011bf        if ((result & 0x100000) != 0)
004011c5        long double x87_r7_1 = fconvert.t(*(arg1 + 0x180))
004011d7        long double temp1_1 = fconvert.t(0f)
004011d7        x87_r7_1 - temp1_1
004011dd        int32_t edx_2 = *(arg1 + 0x1e0)
004011e0        int32_t var_40 = *(arg1 + 0x1dc)
004011e4        int32_t var_3c_1 = edx_2
004011e8        ecx_4 = *(arg1 + 0x1e4)
004011eb        float var_38_1 = ecx_4
004011f2        result.w = (x87_r7_1 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp1_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp1_1 ? 1 : 0) << 0xe
004011f4        int32_t var_34_1 = *(arg1 + 0x1e8)
004011fb        if ((result:1.b & 0x41) == 0)
00401229        int32_t* var_b0_1 = &var_40
00401239        int32_t* var_b4_1 = &var_40
00401247        int32_t* var_b8_1 = &var_40
00401259        result, ecx_4 = queue_axis_aligned_textured_quad_uv(0x25, fconvert.s(fconvert.t(var_68_1) * fconvert.t(0.5f) + fconvert.t(*(arg1 + 0x240)) - fconvert.t(128f)), fconvert.s(fconvert.t(*(arg1 + 0x244)) + fconvert.t(50f)), fconvert.s(fconvert.t(*(arg1 + 0x180)) * fconvert.t(256f)), 32f, 0x1000000, &var_40, 0, 0, fconvert.s(x87_r7_1), 0x3f800000, ebx_1, 0)
00401261        long double x87_r7_10 = fconvert.t(*(arg1 + 0x180))
0040126b        long double temp2_1 = fconvert.t(1f)
0040126b        x87_r7_10 - temp2_1
00401271        result.w = (x87_r7_10 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_10, temp2_1) ? 1 : 0) << 0xa | (x87_r7_10 == temp2_1 ? 1 : 0) << 0xe
00401276        if ((result:1.b & 1) != 0)
004012ad        float var_b0_3 = ecx_4
004012bd        float var_b4_3 = ecx_4
004012cb        float var_b8_3 = ecx_4
004012eb        result, ecx_4 = queue_axis_aligned_textured_quad_uv(0x24, fconvert.s(fconvert.t(var_68_1) * fconvert.t(0.5f) + fconvert.t(*(arg1 + 0x240)) - fconvert.t(128f) + fconvert.t(*(arg1 + 0x180)) * fconvert.t(256f)), fconvert.s(fconvert.t(*(arg1 + 0x244)) + fconvert.t(50f)), fconvert.s((fconvert.t(1f) - fconvert.t(*(arg1 + 0x180))) * fconvert.t(256f)), 32f, 0x1000000, &var_40, fconvert.s(x87_r7_10), 0, 0x3f800000, 0x3f800000, ebx_1, 0)
004012f3        result.b = *(arg1 + 0x5c)
004012f8        if (result.b != 0)
004012fe        void* eax_1 = data_4df904
00401303        long double x87_r7_21 = fconvert.t(0f)
00401309        ecx_4.b = *(eax_1 + 0x440ec)
00401319        if (ecx_4.b != 0 && arg1 == *(eax_1 + 0x440f8))
00401329        float var_8c_1 = ecx_4
0040132d        long double st0_1
0040132d        st0_1, eax_1 = sine(fconvert.s(fconvert.t(*(eax_1 + 0x440f0)) * fconvert.t(3.14159274f)))
00401332        eax_1.b = *(arg1 + 0x5d)
00401338        x87_r7_21 = st0_1 * fconvert.t(3f)
00401340        if (eax_1.b == 0)
00401342        x87_r7_21 = x87_r7_21 * fconvert.t(-1f)
00401348        int32_t ecx_6 = *(arg1 + 0x274)
00401356        long double x87_r6_4 = fconvert.t(*(arg1 + 0x258)) * fconvert.t(0.5f)
00401383        int32_t var_ac_1 = ecx_6
00401384        eax_1.b = *(arg1 + 0x1a0)
0040138c        float var_ac_2 = fconvert.s(fconvert.t(*(arg1 + 0x254)) + fconvert.t(*(arg1 + 0x258)))
0040139b        int32_t var_b0_5 = ecx_6
0040139c        float var_b0_6 = fconvert.s(fconvert.t(*(arg1 + 0x250)) + fconvert.t(*(arg1 + 0x258)))
004013a7        int32_t var_b4_5 = ecx_6
004013a8        float var_b4_6 = fconvert.s(fconvert.t(*(arg1 + 0x244)) - x87_r6_4)
004013b3        int32_t var_b8_5 = ecx_6
004013b6        float var_b8_6 = fconvert.s(x87_r7_21 + fconvert.t(*(arg1 + 0x240)) - x87_r6_4)
004013bb        if ((eax_1.b & 2) == 0)
004013e7        return queue_axis_aligned_textured_quad_uv(*(arg1 + 0x270), var_b8_6, var_b4_6, var_b0_6, var_ac_2, 0x1000000, arg1 + 0x1dc, 0, 0, 0x3f800000, 0x3f800000, ecx_6, 0)
004013d0        return queue_axis_aligned_textured_quad_uv(*(arg1 + 0x60), var_b8_6, var_b4_6, var_b0_6, var_ac_2, 0x1000000, arg1 + 0x1dc, 0, 0, 0x3f800000, 0x3f800000, ecx_6, 0)
004013e8        result = *(arg1 + 0x1a0)
004013f1        void var_50
004013f1        if ((result:1.b & 8) != 0)
004013f7        int32_t ecx_7 = *(arg1 + 0x274)
00401405        long double x87_r7_29 = fconvert.t(*(arg1 + 0x258)) * fconvert.t(0.5f)
00401432        int32_t var_ac_3 = ecx_7
00401448        int32_t var_b0_7 = ecx_7
00401454        int32_t var_b4_7 = ecx_7
00401460        int32_t var_b8_7 = ecx_7
00401467        queue_axis_aligned_textured_quad_uv(*(arg1 + 0x270), fconvert.s(fconvert.t(*(arg1 + 0x240)) - x87_r7_29), fconvert.s(fconvert.t(*(arg1 + 0x244)) - x87_r7_29), fconvert.s(fconvert.t(*(arg1 + 0x258)) + fconvert.t(*(arg1 + 0x250))), fconvert.s(fconvert.t(*(arg1 + 0x254)) + fconvert.t(*(arg1 + 0x258))), 0x1000000, arg1 + 0x1dc, 0, 0, 0x3f800000, 0x3f800000, ecx_7, 0)
0040146c        long double x87_r7_31 = fconvert.t(*(arg1 + 0x178))
00401472        long double temp3_1 = fconvert.t(0f)
00401472        x87_r7_31 - temp3_1
0040147b        result.w = (x87_r7_31 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_31, temp3_1) ? 1 : 0) << 0xa | (x87_r7_31 == temp3_1 ? 1 : 0) << 0xe
00401480        if ((result:1.b & 0x41) == 0)
004014a4        float var_54_1 = fconvert.s(fconvert.t(*(arg1 + 0x258)) * fconvert.t(0.5f))
004014b7        int32_t* eax_7
004014b7        int32_t ecx_9
004014b7        eax_7, ecx_9 = set_color_rgba(&var_50, 0, 0, 0, 0x3f666666)
004014ce        int32_t var_ac_5 = ecx_9
004014de        int32_t var_b0_9 = ecx_9
004014ee        int32_t var_b4_9 = ecx_9
00401502        int32_t var_b8_9 = ecx_9
00401511        result = queue_axis_aligned_textured_quad_uv(*(arg1 + 0x270), fconvert.s(fconvert.t(*(arg1 + 0x178)) + fconvert.t(*(arg1 + 0x240)) - fconvert.t(var_54_1)), fconvert.s(fconvert.t(*(arg1 + 0x178)) + fconvert.t(*(arg1 + 0x244)) - fconvert.t(var_54_1)), fconvert.s(fconvert.t(*(arg1 + 0x258)) + fconvert.t(*(arg1 + 0x250))), fconvert.s(fconvert.t(*(arg1 + 0x254)) + fconvert.t(*(arg1 + 0x258))), 0x1000000, eax_7, 0, 0, 0x3f800000, 0x3f800000, 2, 0)
00401523        if ((*(arg1 + 0x1a0) & &__dos_header) == 0)
00401529        result.b = *(arg1 + 0x234)
00401531        float var_78_1
00401531        float var_74_1
00401531        float var_6c_2
00401531        float var_68_2
00401531        float var_64_1
00401531        float var_60_3
00401531        float var_5c_1
00401531        if (result.b == 0)
0040158c        long double x87_r7_52 = fconvert.t(*(arg1 + 0x220))
00401592        long double temp4_1 = fconvert.t(*(arg1 + 0x230))
00401592        x87_r7_52 - temp4_1
00401598        result.w = (x87_r7_52 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_52, temp4_1) ? 1 : 0) << 0xa | (x87_r7_52 == temp4_1 ? 1 : 0) << 0xe
0040159d        if ((result:1.b & 1) == 0)
00401619        var_74_1 = *(arg1 + 0x240)
00401621        var_78_1 = *(arg1 + 0x244)
0040162b        var_68_2 = var_68_1
0040162f        var_6c_2 = edx_1
00401633        var_64_1 = *(arg1 + 0x220)
00401637        var_60_3 = 0.200000003f
0040163f        var_5c_1 = 0.800000012f
004015a5        long double x87_r7_54 = fconvert.t(*(arg1 + 0x230)) - fconvert.t(*(arg1 + 0x220))
004015b1        var_64_1 = *(arg1 + 0x230)
004015b5        *(arg1 + 0x22c) = fconvert.s(x87_r7_54)
004015c3        var_74_1 = fconvert.s(x87_r7_54 + fconvert.t(*(arg1 + 0x240)))
004015cf        var_78_1 = fconvert.s(x87_r7_54 + fconvert.t(*(arg1 + 0x244)))
004015d3        long double x87_r7_55 = x87_r7_54 + x87_r7_54
004015db        var_68_2 = fconvert.s(fconvert.t(var_68_1) - x87_r7_55)
004015e5        var_6c_2 = fconvert.s(fconvert.t(edx_1) - x87_r7_55)
004015f5        var_60_3 = fconvert.s(fconvert.t(var_64_1) * fconvert.t(0.0078125f))
00401603        var_5c_1 = fconvert.s(fconvert.t(1f) - fconvert.t(var_60_3))
00401539        long double x87_r7_45 = fconvert.t(*(arg1 + 0x240)) + fconvert.t(4f)
0040153f        var_64_1 = 4f
00401547        var_60_3 = 0.100000001f
0040154f        __builtin_strncpy(&var_5c_1, "fff?", 4)
00401557        var_74_1 = fconvert.s(x87_r7_45)
00401567        var_78_1 = fconvert.s(fconvert.t(*(arg1 + 0x244)) + fconvert.t(3f))
00401575        var_68_2 = fconvert.s(fconvert.t(var_68_1) - fconvert.t(8f))
00401583        var_6c_2 = fconvert.s(fconvert.t(edx_1) - fconvert.t(6f))
0040165e        float var_58_1 = fconvert.s(fconvert.t(var_78_1) - fconvert.t(var_64_1))
0040167a        float var_54_2 = fconvert.s(fconvert.t(var_74_1) - fconvert.t(var_64_1))
0040168c        queue_axis_aligned_textured_quad_uv(*(arg1 + 0x48), var_54_2, var_58_1, var_64_1, var_64_1, 0x1000000, arg1 + 0x1ac, 0, 0, var_60_3, var_60_3, ebx_1, 0)
00401698        float ebx_2 = var_5c_1
004016a1        int32_t var_cc
004016a1        __builtin_strncpy(&var_cc, "fff?", 4)
004016c0        queue_axis_aligned_textured_quad_uv(*(arg1 + 0x48), var_74_1, var_58_1, var_68_2, var_64_1, 0x1000000, arg1 + 0x1ac, var_60_3, 0, var_cc, var_60_3, ebx_1, 0)
004016e6        float var_5c_2 = fconvert.s(fconvert.t(var_68_2) + fconvert.t(var_74_1))
004016f4        int32_t var_a0_2
004016f4        __builtin_strncpy(&var_a0_2, "fff?", 4)
00401703        queue_axis_aligned_textured_quad_uv(*(arg1 + 0x48), var_5c_2, var_58_1, var_64_1, var_64_1, 0x1000000, arg1 + 0x1ac, var_a0_2, 0, 0x3f800000, var_60_3, var_70_1, 0)
00401737        queue_axis_aligned_textured_quad_uv(*(arg1 + 0x48), var_54_2, var_78_1, var_64_1, var_6c_2, 0x1000000, arg1 + 0x1ac, 0, var_60_3, var_60_3, ebx_2, var_70_1, 0)
00401771        queue_axis_aligned_textured_quad_uv(*(arg1 + 0x48), var_74_1, var_78_1, var_68_2, var_6c_2, 0x1000000, arg1 + 0x1ac, var_60_3, var_60_3, ebx_2, ebx_2, var_70_1, 0)
004017a5        queue_axis_aligned_textured_quad_uv(*(arg1 + 0x48), var_5c_2, var_78_1, var_64_1, var_6c_2, 0x1000000, arg1 + 0x1ac, ebx_2, var_60_3, 0x3f800000, ebx_2, var_70_1, 0)
004017cf        float var_60_4 = fconvert.s(fconvert.t(var_6c_2) + fconvert.t(var_78_1))
004017eb        queue_axis_aligned_textured_quad_uv(*(arg1 + 0x48), var_54_2, var_60_4, var_64_1, var_64_1, 0x1000000, arg1 + 0x1ac, 0, ebx_2, var_60_3, 0x3f800000, var_70_1, 0)
0040181f        queue_axis_aligned_textured_quad_uv(*(arg1 + 0x48), var_74_1, var_60_4, var_68_2, var_64_1, 0x1000000, arg1 + 0x1ac, var_60_3, ebx_2, ebx_2, 0x3f800000, var_70_1, 0)
00401859        queue_axis_aligned_textured_quad_uv(*(arg1 + 0x48), var_5c_2, var_60_4, var_64_1, var_64_1, 0x1000000, arg1 + 0x1ac, ebx_2, ebx_2, 0x3f800000, 0x3f800000, var_70_1, 0)
0040185e        result = data_4df904
0040187a        if (result[0x1103b].b != 0 && arg1 == result[0x1103e])
0040188d        set_color_white()
004018ac        int32_t var_30
004018ac        int32_t* var_8c_3 = &var_30
004018bb        int32_t var_2c
004018bb        int32_t var_28
004018bb        sub_44dbb0(&var_50, var_30, var_2c, var_28, fconvert.s(fconvert.t(1f) - fconvert.t(*(data_4df904 + 0x440f0))))
004018ef        float var_54_3 = fconvert.s((fconvert.t(*(data_4df904 + 0x440f0)) * fconvert.t(0.699999988f) + fconvert.t(1f)) * fconvert.t(var_64_1))
00401901        float var_58_2 = fconvert.s(fconvert.t(var_78_1) - fconvert.t(var_54_3))
00401912        float var_5c_3 = fconvert.s(fconvert.t(var_74_1) - fconvert.t(var_54_3))
0040191d        queue_axis_aligned_textured_quad_uv(0x63, var_5c_3, var_58_2, var_54_3, var_54_3, 0x1000000, &var_50, 0, 0, var_60_3, var_60_3, 3, 0)
0040194a        queue_axis_aligned_textured_quad_uv(0x63, var_74_1, var_58_2, var_68_2, var_54_3, 0x1000000, &var_50, var_60_3, 0, ebx_2, var_60_3, 3, 0)
00401973        queue_axis_aligned_textured_quad_uv(0x63, var_5c_2, var_58_2, var_54_3, var_54_3, 0x1000000, &var_50, ebx_2, 0, 0x3f800000, var_60_3, 3, 0)
004019a0        queue_axis_aligned_textured_quad_uv(0x63, var_5c_3, var_78_1, var_54_3, var_6c_2, 0x1000000, &var_50, 0, var_60_3, var_60_3, ebx_2, 3, 0)
004019cc        queue_axis_aligned_textured_quad_uv(0x63, var_5c_2, var_78_1, var_54_3, var_6c_2, 0x1000000, &var_50, ebx_2, var_60_3, 0x3f800000, ebx_2, 3, 0)
004019f9        queue_axis_aligned_textured_quad_uv(0x63, var_5c_3, var_60_4, var_54_3, var_54_3, 0x1000000, &var_50, 0, ebx_2, var_60_3, 0x3f800000, 3, 0)
00401a29        queue_axis_aligned_textured_quad_uv(0x63, var_74_1, var_60_4, var_68_2, var_54_3, 0x1000000, &var_50, var_60_3, ebx_2, ebx_2, 0x3f800000, 3, 0)
00401a51        return queue_axis_aligned_textured_quad_uv(0x63, var_5c_2, var_60_4, var_54_3, var_54_3, 0x1000000, &var_50, ebx_2, ebx_2, 0x3f800000, 0x3f800000, 3, 0)
00401a60        return result
