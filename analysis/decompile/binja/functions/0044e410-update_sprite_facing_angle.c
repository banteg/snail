/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_sprite_facing_angle @ 0x44e410 */

0044e41c        int16_t result
0044e41c        float var_c
0044e41c        if (((*(arg1 + 4)).w:1.b & 4) == 0)
0044e4e1        long double x87_r7_14 = fconvert.t(*(arg1 + 0x4c)) - fconvert.t(*(arg1 + 0x40))
0044e4e8        var_c = fconvert.s(fconvert.t(*(arg1 + 0x48)) - fconvert.t(*(arg1 + 0x3c)))
0044e4ff        float var_8_2 = fconvert.s(x87_r7_14)
0044e50f        float var_4_3 = fconvert.s(fconvert.t(*(arg1 + 0x50)) - fconvert.t(*(arg1 + 0x44)))
0044e513        int32_t* eax_6 = rotate_vector_by_matrix(&var_c, arg2)
0044e524        int32_t var_4_4 = eax_6[2]
0044e528        long double st0_2
0044e528        st0_2, result = atan2_positive(*eax_6, eax_6[1])
0044e536        *(arg1 + 0x7c) = fconvert.s(st0_2 + fconvert.t(7.06858349f))
0044e422        long double x87_r7 = fconvert.t(*(arg1 + 0x8c))
0044e428        long double temp1_1 = fconvert.t(0f)
0044e428        x87_r7 - temp1_1
0044e433        if ((((x87_r7 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp1_1) ? 1 : 0) << 0xa | (x87_r7 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
0044e442        long double x87_r7_4 = fconvert.t(*(arg1 + 0x4c)) - fconvert.t(*(arg1 + 0x40))
0044e449        var_c = fconvert.s(fconvert.t(*(arg1 + 0x48)) - fconvert.t(*(arg1 + 0x3c)))
0044e460        float var_8_1 = fconvert.s(x87_r7_4)
0044e470        float var_4_1 = fconvert.s(fconvert.t(*(arg1 + 0x50)) - fconvert.t(*(arg1 + 0x44)))
0044e474        int32_t* eax_2 = rotate_vector_by_matrix(&var_c, arg2)
0044e485        int32_t var_4_2 = eax_2[2]
0044e48e        long double x87_r7_8 = atan2_positive(*eax_2, eax_2[1]) + fconvert.t(7.06858349f)
0044e497        *(arg1 + 0x8c) = 0x3a83126f
0044e4a1        *(arg1 + 0x7c) = fconvert.s(x87_r7_8)
0044e4aa        long double x87_r7_10 = fconvert.t(*(arg1 + 0x90)) + fconvert.t(*(arg1 + 0x8c))
0044e4b0        *(arg1 + 0x8c) = fconvert.s(x87_r7_10)
0044e4b6        long double temp2_1 = fconvert.t(1f)
0044e4b6        x87_r7_10 - temp2_1
0044e4bc        result = (x87_r7_10 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_10, temp2_1) ? 1 : 0) << 0xa | (x87_r7_10 == temp2_1 ? 1 : 0) << 0xe
0044e4c1        if ((result:1.b & 0x41) == 0)
0044e4c3        *(arg1 + 0x8c) = 0
0044e53d        return result
