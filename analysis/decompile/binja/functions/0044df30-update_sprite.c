/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_sprite @ 0x44df30 */

0044df30        int32_t edx_5 = *(arg1 + 4)
0044df37        int32_t result
0044df37        if ((edx_5:1.b & 8) != 0)
0044df39        result.b = data_790f30
0044df40        if ((edx_5:1.b & 8) == 0 || result.b == 0)
0044df49        if ((edx_5.b & 8) != 0)
0044dfb9        *(arg1 + 4) = edx_5 & 0xfffffff7
0044dfc0        label_44dfc0:
0044dfc0        int32_t eax_1
0044dfc0        eax_1.b = (*(arg1 + 4)).b & 0xf7
0044dfc5        *(arg1 + 4) = eax_1
0044dfcf        *(arg1 + 0x3c) = *(arg1 + 0x48)
0044dfd4        *(arg1 + 0x40) = *(arg1 + 0x4c)
0044dfdb        *(arg1 + 0x44) = *(arg1 + 0x50)
0044dfe3        *(arg1 + 0x48) = fconvert.s(fconvert.t(*(arg1 + 0x54)) + fconvert.t(*(arg1 + 0x48)))
0044dfeb        *(arg1 + 0x4c) = fconvert.s(fconvert.t(*(arg1 + 0x58)) + fconvert.t(*(arg1 + 0x4c)))
0044dff4        *(arg1 + 0x50) = fconvert.s(fconvert.t(*(arg1 + 0x5c)) + fconvert.t(*(arg1 + 0x50)))
0044dffd        *(arg1 + 0x58) = fconvert.s(fconvert.t(*(arg1 + 0x78)) + fconvert.t(*(arg1 + 0x58)))
0044e009        *(arg1 + 0x7c) = fconvert.s(fconvert.t(*(arg1 + 0x80)) + fconvert.t(*(arg1 + 0x7c)))
0044e00c        long double x87_r7_17 = fconvert.t(*(arg1 + 0x74))
0044e00f        long double temp1_1 = fconvert.t(0f)
0044e00f        x87_r7_17 - temp1_1
0044e015        float* eax_2
0044e015        eax_2.w = (x87_r7_17 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_17, temp1_1) ? 1 : 0) << 0xa | (x87_r7_17 == temp1_1 ? 1 : 0) << 0xe
0044e01a        result = *(arg1 + 4)
0044e01d        if ((eax_2:1.b & 0x41) != 0)
0044e024        result:1.b &= 0xfd
0044e01f        result:1.b |= 2
0044e027        int32_t result_1 = result
0044e029        *(arg1 + 4) = result
0044e032        if ((result_1 & 0x2000) != 0)
0044e03e        long double x87_r7_19 = fconvert.t(*(arg1 + 0xb0)) + fconvert.t(*(arg1 + 0xac))
0044e044        long double temp5_1 = fconvert.t(1f)
0044e044        x87_r7_19 - temp5_1
0044e04a        *(arg1 + 0xac) = fconvert.s(x87_r7_19)
0044e04a        bool c1_2 = unimplemented  {fst dword [ecx+0xac], st0}
0044e050        result.w = (x87_r7_19 < temp5_1 ? 1 : 0) << 8 | (c1_2 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_19, temp5_1) ? 1 : 0) << 0xa | (x87_r7_19 == temp5_1 ? 1 : 0) << 0xe | 0x3800
0044e055        if ((result:1.b & 0x41) == 0)
0044e06d        int32_t edx_3 = *(arg1 + 0xa4) + *(arg1 + 0xa8)
0044e06f        int32_t eax_4 = *(arg1 + 0xa0)
0044e07b        *(arg1 + 0xac) = fconvert.s(x87_r7_19 - fconvert.t(1f))
0044e081        *(arg1 + 0xa4) = edx_3
0044e087        if ((result_1 & 0x4000) != 0)
0044e08e        if (edx_3 == eax_4)
0044e091        *(arg1 + 0xa8) = 0xffffffff
0044e097        *(arg1 + 0xa4) = eax_4 - 1
0044e0a3        if (*(arg1 + 0xa4) == 0xffffffff)
0044e0a5        *(arg1 + 0xa4) = 0
0044e0af        *(arg1 + 0xa8) = 1
0044e0bd        if (edx_3 == eax_4)
0044e0bf        *(arg1 + 0xa4) = 0
0044e0dd        return set_sprite_texture_ref(arg1, *(arg1 + 0x9c), *(arg1 + 0xa4))
0044df4e        long double x87_r7_2 = fconvert.t(*(arg1 + 0x6c)) + fconvert.t(*(arg1 + 0x68))
0044df51        long double temp0_1 = fconvert.t(1f)
0044df51        x87_r7_2 - temp0_1
0044df57        *(arg1 + 0x68) = fconvert.s(x87_r7_2)
0044df57        bool c1_1 = unimplemented  {fst dword [ecx+0x68], st0}
0044df5a        result.w = (x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe | 0x3800
0044df5f        if ((result:1.b & 0x41) != 0)
0044df61        long double temp2_1 = fconvert.t(0f)
0044df61        x87_r7_2 - temp2_1
0044df67        result.w = (x87_r7_2 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp2_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp2_1 ? 1 : 0) << 0xe
0044df6c        if ((result:1.b & 1) == 0)
0044df6e        long double x87_r7_3 = fconvert.t(*(arg1 + 0x74))
0044df71        long double temp3_1 = fconvert.t(0f)
0044df71        x87_r7_3 - temp3_1
0044df77        result.w = (x87_r7_3 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp3_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp3_1 ? 1 : 0) << 0xe
0044df7c        if ((result:1.b & 0x40) == 0)
0044df81        long double x87_r7_5 = fconvert.t(*(arg1 + 0x74)) + fconvert.t(*(arg1 + 0x70))
0044df84        *(arg1 + 0x70) = fconvert.s(x87_r7_5)
0044df87        long double temp4_1 = fconvert.t(1f)
0044df87        x87_r7_5 - temp4_1
0044df8d        result.w = (x87_r7_5 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp4_1) ? 1 : 0) << 0xa | (x87_r7_5 == temp4_1 ? 1 : 0) << 0xe
0044df92        if ((result:1.b & 0x41) == 0)
0044df94        *(arg1 + 0x74) = 0
0044df7c        goto label_44dfc0
0044dfa2        *(arg1 + 0x68) = 0x3f800000
0044dfa9        if ((edx_5:1.b & 1) == 0)
0044dfb5        return kill_sprite(arg1)
0044e0e1        return result
