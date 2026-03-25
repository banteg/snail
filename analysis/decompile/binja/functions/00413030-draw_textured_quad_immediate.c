/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: draw_textured_quad_immediate @ 0x413030 */

00413030        int32_t* eax_36 = data_502fec
00413041        (*(*eax_36 + 0xc8))(eax_36, 0x16, 1)
0041304c        sub_414500(arg1)
00413056        sub_412e50(arg17)
00413070        int32_t var_4
00413070        sub_44dbf0(&var_4, arg16)
0041307e        int32_t* eax_1 = *(data_502fe0 + 8)
0041308c        float* var_8
0041308c        int32_t ecx_5 = (*(*eax_1 + 0x2c))(eax_1, 0, 0x60, &var_8, 0)
0041308f        long double x87_r7 = fconvert.t(arg18)
00413093        long double temp0 = fconvert.t(0f)
00413093        x87_r7 - temp0
00413099        long double x87_r7_1 = fconvert.t(arg10)
004130a2        if ((((x87_r7 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp0) ? 1 : 0) << 0xa | (x87_r7 == temp0 ? 1 : 0) << 0xe | 0x3800):1.b & 0x40) == 0)
004132b1        long double x87_r7_27 = x87_r7_1 * fconvert.t(0.5f)
004132b7        int32_t var_14_2 = ecx_5
004132be        arg2 = fconvert.s(x87_r7_27 + fconvert.t(arg2))
004132c6        long double x87_r6_12 = fconvert.t(arg11) * fconvert.t(0.5f)
004132d4        arg3 = fconvert.s(x87_r6_12 + fconvert.t(arg3))
004132d8        long double x87_r6_14 = fconvert.t(fconvert.s(x87_r6_12))
004132fd        arg11 = fconvert.s(square_root(fconvert.s(x87_r6_14 * x87_r6_14 + x87_r7_27 * x87_r7_27)) * fconvert.t(1.41400003f))
0041330b        arg10 = fconvert.s(sine(arg18) * fconvert.t(arg11))
00413314        long double x87_r7_34 = cosine(arg18) * fconvert.t(arg11)
00413327        *var_8 = fconvert.s(fconvert.t(arg10) + fconvert.t(arg2))
00413333        var_8[1] = fconvert.s(x87_r7_34 + fconvert.t(arg3))
0041333e        var_8[2] = 0
00413345        var_8[4] = fconvert.s(fconvert.t(arg12))
00413350        var_8[5] = fconvert.s(fconvert.t(arg13))
00413361        var_8[3] = var_4
00413368        var_8[6] = fconvert.s(fconvert.t(arg2) - x87_r7_34)
00413377        var_8[7] = fconvert.s(fconvert.t(arg10) + fconvert.t(arg3))
00413382        var_8[8] = 0
00413389        var_8[0xa] = fconvert.s(fconvert.t(arg14))
00413394        var_8[0xb] = fconvert.s(fconvert.t(arg13))
004133a7        var_8[9] = var_4
004133ae        var_8[0xc] = fconvert.s(fconvert.t(arg2) - fconvert.t(arg10))
004133bb        var_8[0xd] = fconvert.s(fconvert.t(arg3) - x87_r7_34)
004133c2        var_8[0xe] = 0
004133cd        var_8[0x10] = fconvert.s(fconvert.t(arg14))
004133d8        var_8[0x11] = fconvert.s(fconvert.t(arg15))
004133e7        var_8[0xf] = var_4
004133ee        var_8[0x12] = fconvert.s(x87_r7_34 + fconvert.t(arg2))
004133fd        var_8[0x13] = fconvert.s(fconvert.t(arg3) - fconvert.t(arg10))
00413408        var_8[0x14] = 0
0041340f        var_8[0x16] = fconvert.s(fconvert.t(arg12))
0041341a        var_8[0x17] = fconvert.s(fconvert.t(arg15))
00413425        var_8[0x15] = var_4
004130a8        long double temp1_1 = fconvert.t(0f)
004130a8        x87_r7_1 - temp1_1
004130ae        long double x87_r7_2 = fconvert.t(arg2)
004130b7        if ((((x87_r7_1 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp1_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp1_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x40) == 0)
004131b9        *var_8 = fconvert.s(x87_r7_2)
004131c3        var_8[1] = fconvert.s(fconvert.t(arg3))
004131ce        var_8[2] = 0
004131d5        var_8[4] = fconvert.s(fconvert.t(arg12))
004131e0        var_8[5] = fconvert.s(fconvert.t(arg13))
004131ef        long double x87_r7_22 = fconvert.t(arg2) + fconvert.t(arg10)
004131f3        var_8[3] = var_4
004131fc        var_8[6] = fconvert.s(x87_r7_22)
00413207        var_8[7] = fconvert.s(fconvert.t(arg3))
00413212        var_8[8] = 0
00413219        var_8[0xa] = fconvert.s(fconvert.t(arg14))
00413224        var_8[0xb] = fconvert.s(fconvert.t(arg13))
0041322f        var_8[9] = var_4
00413236        var_8[0xc] = fconvert.s(x87_r7_22)
0041323d        long double x87_r7_24 = fconvert.t(arg3) + fconvert.t(arg11)
00413247        var_8[0xd] = fconvert.s(x87_r7_24)
00413252        var_8[0xe] = 0
00413259        var_8[0x10] = fconvert.s(fconvert.t(arg14))
00413264        var_8[0x11] = fconvert.s(fconvert.t(arg15))
00413273        var_8[0xf] = var_4
0041327a        var_8[0x12] = fconvert.s(fconvert.t(arg2))
00413281        var_8[0x13] = fconvert.s(x87_r7_24)
0041328c        var_8[0x14] = 0
00413293        var_8[0x16] = fconvert.s(fconvert.t(arg12))
0041329e        var_8[0x17] = fconvert.s(fconvert.t(arg15))
004132a9        var_8[0x15] = var_4
004130c1        *var_8 = fconvert.s(x87_r7_2)
004130cb        var_8[1] = fconvert.s(fconvert.t(arg3))
004130d6        var_8[2] = 0
004130dd        var_8[4] = fconvert.s(fconvert.t(arg12))
004130e8        var_8[5] = fconvert.s(fconvert.t(arg13))
004130f7        var_8[3] = var_4
004130fe        var_8[6] = fconvert.s(fconvert.t(arg4))
00413109        var_8[7] = fconvert.s(fconvert.t(arg5))
00413114        var_8[8] = 0
0041311b        var_8[0xa] = fconvert.s(fconvert.t(arg14))
00413126        var_8[0xb] = fconvert.s(fconvert.t(arg13))
00413135        var_8[9] = var_4
0041313c        var_8[0xc] = fconvert.s(fconvert.t(arg6))
00413147        var_8[0xd] = fconvert.s(fconvert.t(arg7))
00413152        var_8[0xe] = 0
00413159        var_8[0x10] = fconvert.s(fconvert.t(arg14))
00413164        var_8[0x11] = fconvert.s(fconvert.t(arg15))
00413173        var_8[0xf] = var_4
0041317a        var_8[0x12] = fconvert.s(fconvert.t(arg8))
00413185        var_8[0x13] = fconvert.s(fconvert.t(arg9))
00413190        var_8[0x14] = 0
00413197        var_8[0x16] = fconvert.s(fconvert.t(arg12))
004131a2        var_8[0x17] = fconvert.s(fconvert.t(arg15))
004131ad        var_8[0x15] = var_4
0041342d        int32_t* eax_32 = *(data_502fe0 + 8)
00413433        (*(*eax_32 + 0x30))(eax_32)
0041343c        int32_t* eax_33 = data_502fec
0041344b        (*(*eax_33 + 0x14c))(eax_33, 0, *(data_502fe0 + 8), 0x18)
00413451        int32_t* eax_34 = data_502fec
0041345e        (*(*eax_34 + 0x130))(eax_34, 0x142)
00413464        int32_t* eax_35 = data_502fec
00413471        int32_t result = (*(*eax_35 + 0x118))(eax_35, 6, 0, 2)
00413486        int32_t edx_33 = data_503170 + 1
00413487        data_4f7450 += 2
00413490        data_503170 = edx_33
00413497        if (result == 0)
004134aa        data_4f7454 += 1
004134b3        return result
0041349e        report_errorf("Draw Primitive Failed")
004134a9        return 0
