/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_cameraman @ 0x4461d0 */

004461e4        cameraman[0x33].b = 0
00446201        float* cameraman_1 = cameraman
00446241        void transform
00446241        __builtin_memcpy(&cameraman[0x10], initialize_matrix_from_values(&transform, 0x3f800000, 0, 0, 0, 0, 0x3f722d1f, 0x3ea5f890, 0, 0, 0xbea5f890, 0x3f722d1f, 0, fconvert.s(fconvert.t(*(cameraman[0x30] + 0x2964)) * fconvert.t(0.400000006f)), 0x3fe66666, 0xbf000000, 0x3f800000), 0x40)
00446245        orthogonalize_matrix(&cameraman[0x10])
00446250        void* ecx_2 = cameraman[0x30]
00446256        long double x87_r7_2 = float.t(*(cameraman[0x31] i+ 0x50))
00446259        long double temp1 = fconvert.t(*(ecx_2 + 0x296c))
00446259        x87_r7_2 - temp1
0044625f        int32_t eax_2
0044625f        eax_2.w = (x87_r7_2 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1 ? 1 : 0) << 0xe | 0x3800
00446264        if ((eax_2:1.b & 0x41) != 0)
00446303        cameraman[0x1d] = fconvert.s(fconvert.t(*(ecx_2 + 0x2968)) * fconvert.t(0.349999994f) + fconvert.t(cameraman[0x1d]))
00446276        long double x87_r7_5 = fconvert.t(*(ecx_2 + 0x296c)) / x87_r7_2 * fconvert.t(1.39999998f) - fconvert.t(0.400000006f)
0044627c        long double temp2_1 = fconvert.t(0f)
0044627c        x87_r7_5 - temp2_1
00446282        eax_2.w = (x87_r7_5 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp2_1) ? 1 : 0) << 0xa | (x87_r7_5 == temp2_1 ? 1 : 0) << 0xe | 0x3800
00446287        if ((eax_2:1.b & 1) == 0)
00446293        long double temp3_1 = fconvert.t(1f)
00446293        x87_r7_5 - temp3_1
00446299        eax_2.w = (x87_r7_5 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp3_1) ? 1 : 0) << 0xa | (x87_r7_5 == temp3_1 ? 1 : 0) << 0xe | 0x3800
0044629e        if ((eax_2:1.b & 0x41) == 0)
004462a2        x87_r7_5 = fconvert.t(1f)
0044628b        x87_r7_5 = fconvert.t(0f)
004462ae        long double x87_r6_2 = fconvert.t(1f) - x87_r7_5
004462b0        void* var_58_1 = ecx_2
004462c1        long double x87_r6_5 = x87_r6_2 * fconvert.t(*(ecx_2 + 0x2968)) * fconvert.t(1.14999998f) + fconvert.t(cameraman[0x1d])
004462c4        cameraman[0x1d] = fconvert.s(x87_r6_5)
004462d9        cameraman[0x1d] = fconvert.s(x87_r7_5 * fconvert.t(0.349999994f) * fconvert.t(*(ecx_2 + 0x2968)) + x87_r6_5)
004462eb        rotate_matrix_world_x(&cameraman[0x10], fconvert.s(fconvert.t(fconvert.s(x87_r6_2)) * fconvert.t(0.872499943f)))
00446306        void* ecx_4 = cameraman[0x30]
00446313        void* edx_1
00446313        if (*(ecx_4 + 0x384) == 1)
00446319        edx_1 = *(ecx_4 + 0x388)
0044631f        eax_2 = *(edx_1 + 0x38)
00446348        if (*(ecx_4 + 0x384) == 1 && (eax_2 == 0x10 || eax_2 == 8 || eax_2 == 9 || eax_2 == 0xa || eax_2 == 0x2b || eax_2 == 0x2d || eax_2 == 0x24 || eax_2 == 0xe))
00446356        long double x87_r7_18 = (fconvert.t(*(ecx_4 + 0x70)) - fconvert.t(*(*(ecx_4 + 0x38c) + 0x18))) / fconvert.t(*(edx_1 + 0x4c))
00446359        long double temp5_1 = fconvert.t(0f)
00446359        x87_r7_18 - temp5_1
0044635f        void* eax_3
0044635f        eax_3.w = (x87_r7_18 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_18, temp5_1) ? 1 : 0) << 0xa | (x87_r7_18 == temp5_1 ? 1 : 0) << 0xe | 0x3800
00446364        if ((eax_3:1.b & 1) == 0)
00446370        long double temp7_1 = fconvert.t(1f)
00446370        x87_r7_18 - temp7_1
00446376        eax_3.w = (x87_r7_18 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_18, temp7_1) ? 1 : 0) << 0xa | (x87_r7_18 == temp7_1 ? 1 : 0) << 0xe | 0x3800
0044637b        if ((eax_3:1.b & 0x41) == 0)
0044637f        x87_r7_18 = fconvert.t(1f)
00446368        x87_r7_18 = fconvert.t(0f)
0044638b        void* var_58_3 = ecx_4
0044638f        long double st0_1
0044638f        st0_1, eax_2 = cosine(fconvert.s(x87_r7_18 * fconvert.t(6.28318548f)))
004463a9        cameraman[0x34] = fconvert.s((fconvert.t(0.5f) - st0_1 * fconvert.t(0.5f)) * fconvert.t(0.349999994f))
004463b1        cameraman[0x34] = 0
004463bb        void* ecx_5 = cameraman[0x30]
004463c1        long double x87_r7_26 = fconvert.t(*(ecx_5 + 0x2dc))
004463c7        long double temp4 = fconvert.t(0f)
004463c7        x87_r7_26 - temp4
004463cd        eax_2.w = (x87_r7_26 < temp4 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_26, temp4) ? 1 : 0) << 0xa | (x87_r7_26 == temp4 ? 1 : 0) << 0xe
004463d2        if ((eax_2:1.b & 0x41) == 0)
004463e0        void* var_58_5 = ecx_5
004463ea        long double st0_2
004463ea        st0_2, eax_2 = cosine(fconvert.s(fconvert.t(*(ecx_5 + 0x2dc)) * fconvert.t(4.71238899f) + fconvert.t(1.57079637f)))
0044640a        cameraman[0x34] = fconvert.s((fconvert.t(0.5f) - st0_2 * fconvert.t(0.5f)) * fconvert.t(0.239999995f) + fconvert.t(cameraman[0x34]))
0044641c        void* ecx_6 = cameraman[0x30]
00446428        long double x87_r7_38 = (fconvert.t(cameraman[0x34]) - fconvert.t(cameraman[0x35])) * fconvert.t(0.100000001f) + fconvert.t(cameraman[0x35])
0044642e        cameraman[0x35] = fconvert.s(x87_r7_38)
0044643d        cameraman[0x1d] = fconvert.s(x87_r7_38 * fconvert.t(*(ecx_6 + 0x2968)) + fconvert.t(cameraman[0x1d]))
0044644f        cameraman[0x1c] = fconvert.s(fconvert.t(*(ecx_6 + 0x2964)) * fconvert.t(0.333333343f) + fconvert.t(cameraman[0x1c]))
0044645b        long double x87_r7_46 = fconvert.t(*(ecx_6 + 0x296c)) + fconvert.t(cameraman[0x1e]) + fconvert.t(0.400000006f)
00446461        cameraman[0x1e] = fconvert.s(x87_r7_46)
00446466        long double x87_r6_11 = x87_r7_46 - fconvert.t(cameraman[0x2e])
0044646c        long double temp6 = fconvert.t(3f)
0044646c        x87_r6_11 - temp6
00446472        eax_2.w = (x87_r6_11 < temp6 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_11, temp6) ? 1 : 0) << 0xa | (x87_r6_11 == temp6 ? 1 : 0) << 0xe | 0x3000
00446477        if ((eax_2:1.b & 0x41) != 0)
00446489        long double temp8_1 = fconvert.t(1.70000005f)
00446489        x87_r6_11 - temp8_1
0044648f        eax_2.w = (x87_r6_11 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_11, temp8_1) ? 1 : 0) << 0xa | (x87_r6_11 == temp8_1 ? 1 : 0) << 0xe | 0x3800
00446494        if ((eax_2:1.b & 1) != 0)
0044649c        cameraman[0x2e] = fconvert.s(x87_r7_46 - fconvert.t(1.70000005f))
00446481        cameraman[0x2e] = fconvert.s(x87_r7_46 - fconvert.t(3f))
004464be        long double x87_r7_54 = (fconvert.t(-2f) - (fconvert.t(*(ecx_6 + 0x2968)) - fconvert.t(0.49000001f)) * fconvert.t(5f)) * fconvert.t(0.0174499992f)
004464c4        float var_44_2 = fconvert.s(x87_r7_54)
004464c8        long double temp9 = fconvert.t(-1.22149992f)
004464c8        x87_r7_54 - temp9
004464ce        eax_2.w = (x87_r7_54 < temp9 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_54, temp9) ? 1 : 0) << 0xa | (x87_r7_54 == temp9 ? 1 : 0) << 0xe
004464d3        if ((eax_2:1.b & 1) == 0)
004464df        long double x87_r7_55 = fconvert.t(var_44_2)
004464e3        long double temp10_1 = fconvert.t(1.22149992f)
004464e3        x87_r7_55 - temp10_1
004464e9        eax_2.w = (x87_r7_55 < temp10_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_55, temp10_1) ? 1 : 0) << 0xa | (x87_r7_55 == temp10_1 ? 1 : 0) << 0xe
004464ee        if ((eax_2:1.b & 0x41) == 0)
004464f0        var_44_2 = 1.22149992f
004464d5        var_44_2 = -1.22149992f
004464ff        int32_t ecx_9 = rotate_matrix_world_x(&cameraman[0x10], var_44_2)
00446504        void* esi_1 = cameraman[0x30]
0044650a        int32_t var_58_8 = ecx_9
00446558        rotate_matrix_world_z(&cameraman[0x10], fconvert.s((fconvert.t(0.5f) - cosine(fconvert.s(fconvert.t(*(esi_1 + 0x358)) * fconvert.t(3.14159274f))) * fconvert.t(0.5f)) * fconvert.t(*(esi_1 + 0x354)) * fconvert.t(6.28318548f) + fconvert.t(*(esi_1 + 0x2964)) * fconvert.t(-8f) * fconvert.t(0.0174499992f) * fconvert.t(0.170000002f)))
0044656a        if (*(cameraman[0x30] i+ 0x384) == 1)
00446570        set_matrix_identity(&transform)
00446586        rotate_matrix_world_z(&transform, *(cameraman[0x30] i+ 0x39c))
00446592        multiply_matrix_in_place(&cameraman[0x10], &transform)
004465a6        rotate_matrix_world_z(&cameraman[0x10], *(cameraman[0x30] i+ 0x3a0))
004465ab        void* eax_5 = cameraman[0x30]
004465b9        if (*(eax_5 + 0x41d) != 0)
004465c4        rotate_matrix_world_z(&cameraman[0x10], *(eax_5 + 0x42c))
004465d8        void* ecx_21 = rotate_matrix_world_z(&cameraman[0x10], *(cameraman[0x30] i+ 0x370))
004465dd        void* eax_7 = cameraman[0x30]
004465ea        if (*(eax_7 + 0x384) == 1)
004465f0        ecx_21 = *(eax_7 + 0x388)
004465fa        long double x87_r7_75
004465fa        if (*(eax_7 + 0x384) != 1 || *(ecx_21 + 0x38) != 0x18)
00446679        x87_r7_75 = fconvert.t(110f)
00446608        long double x87_r7_66 = (fconvert.t(*(eax_7 + 0x70)) - fconvert.t(*(*(eax_7 + 0x38c) + 0x18))) / fconvert.t(*(ecx_21 + 0x4c))
0044660b        long double temp11_1 = fconvert.t(0f)
0044660b        x87_r7_66 - temp11_1
00446611        eax_7.w = (x87_r7_66 < temp11_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_66, temp11_1) ? 1 : 0) << 0xa | (x87_r7_66 == temp11_1 ? 1 : 0) << 0xe | 0x3800
00446616        if ((eax_7:1.b & 1) == 0)
00446622        long double temp12_1 = fconvert.t(1f)
00446622        x87_r7_66 - temp12_1
00446628        eax_7.w = (x87_r7_66 < temp12_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_66, temp12_1) ? 1 : 0) << 0xa | (x87_r7_66 == temp12_1 ? 1 : 0) << 0xe | 0x3800
0044662d        if ((eax_7:1.b & 0x41) == 0)
00446631        x87_r7_66 = fconvert.t(1f)
0044661a        x87_r7_66 = fconvert.t(0f)
0044663d        void* var_58_16 = ecx_21
00446641        long double st0_4
00446641        st0_4, ecx_21 = cosine(fconvert.s(x87_r7_66 * fconvert.t(6.28318548f)))
0044664c        void* var_5c_1 = ecx_21
0044664d        long double x87_r7_72 = fconvert.t(0.5f) - st0_4 * fconvert.t(0.5f)
00446657        var_5c_1.q = fconvert.d(x87_r7_72)
0044665a        char* var_60_1 = "Worm scale %f\n"
00446671        x87_r7_75 = fconvert.t(fconvert.s(x87_r7_72)) * fconvert.t(50f) + fconvert.t(110f)
00446685        void* eax_8 = cameraman[0x31]
0044668b        void* var_58_18 = ecx_21
004466a0        cameraman[0x32] = fconvert.s((x87_r7_75 - fconvert.t(cameraman[0x32])) * fconvert.t(0.300000012f) + fconvert.t(cameraman[0x32]))
004466b4        float result = linear_interpolate_matrix(cameraman, &cameraman[0x20], &cameraman[0x10], fconvert.s(fconvert.t(*(eax_8 + 0x38)) * fconvert.t(0.300000012f)))
004466c0        __builtin_memcpy(&cameraman[0x20], &cameraman[0x10], 0x40)
004466c9        return result
