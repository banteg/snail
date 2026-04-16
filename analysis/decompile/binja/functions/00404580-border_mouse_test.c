/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: border_mouse_test @ 0x404580 */

00404580        char* result
00404580        result.b = *(arg1 + 0x5c)
00404583        void* edx = data_4df904
0040458e        if (result.b == 0)
004046af        long double x87_r7_17 = fconvert.t(*(arg1 + 0x238)) - fconvert.t(*(arg1 + 0x21c))
004046b5        long double temp0_1 = fconvert.t(*(edx + 0x29c))
004046b5        x87_r7_17 - temp0_1
004046bb        result.w = (x87_r7_17 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_17, temp0_1) ? 1 : 0) << 0xa | (x87_r7_17 == temp0_1 ? 1 : 0) << 0xe
004046c0        if ((result:1.b & 1) != 0)
004046ce        long double x87_r7_20 = fconvert.t(*(arg1 + 0x248)) + fconvert.t(*(arg1 + 0x21c)) + fconvert.t(*(arg1 + 0x238))
004046d4        long double temp2_1 = fconvert.t(*(edx + 0x29c))
004046d4        x87_r7_20 - temp2_1
004046da        result.w = (x87_r7_20 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_20, temp2_1) ? 1 : 0) << 0xa | (x87_r7_20 == temp2_1 ? 1 : 0) << 0xe
004046df        if ((result:1.b & 0x41) == 0)
004046e7        long double x87_r7_22 = fconvert.t(*(arg1 + 0x23c)) - fconvert.t(*(arg1 + 0x21c))
004046ed        long double temp4_1 = fconvert.t(*(edx + 0x2a0))
004046ed        x87_r7_22 - temp4_1
004046f3        result.w = (x87_r7_22 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_22, temp4_1) ? 1 : 0) << 0xa | (x87_r7_22 == temp4_1 ? 1 : 0) << 0xe
004046f8        if ((result:1.b & 1) != 0)
00404706        long double x87_r7_25 = fconvert.t(*(arg1 + 0x24c)) + fconvert.t(*(arg1 + 0x23c)) + fconvert.t(*(arg1 + 0x21c))
0040470c        long double temp6_1 = fconvert.t(*(edx + 0x2a0))
0040470c        x87_r7_25 - temp6_1
00404712        result.w = (x87_r7_25 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_25, temp6_1) ? 1 : 0) << 0xa | (x87_r7_25 == temp6_1 ? 1 : 0) << 0xe
00404717        if ((result:1.b & 0x41) == 0)
00404719        result.b = 1
0040471e        return result
00404594        long double x87_r7 = fconvert.t(*(edx + 0x29c))
0040459a        long double temp1_1 = fconvert.t(*(arg1 + 0x240))
0040459a        x87_r7 - temp1_1
004045a0        result.w = (x87_r7 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp1_1) ? 1 : 0) << 0xa | (x87_r7 == temp1_1 ? 1 : 0) << 0xe
004045a5        if ((result:1.b & 1) == 0)
004045b1        long double x87_r7_2 = fconvert.t(*(arg1 + 0x250)) + fconvert.t(*(arg1 + 0x240))
004045b7        long double temp3_1 = fconvert.t(*(edx + 0x29c))
004045b7        x87_r7_2 - temp3_1
004045bd        result.w = (x87_r7_2 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp3_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp3_1 ? 1 : 0) << 0xe
004045c2        if ((result:1.b & 0x41) == 0)
004045c8        long double x87_r7_3 = fconvert.t(*(edx + 0x2a0))
004045ce        long double temp5_1 = fconvert.t(*(arg1 + 0x244))
004045ce        x87_r7_3 - temp5_1
004045d4        result.w = (x87_r7_3 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp5_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp5_1 ? 1 : 0) << 0xe
004045d9        if ((result:1.b & 1) == 0)
004045e5        long double x87_r7_5 = fconvert.t(*(arg1 + 0x254)) + fconvert.t(*(arg1 + 0x244))
004045eb        long double temp7_1 = fconvert.t(*(edx + 0x2a0))
004045eb        x87_r7_5 - temp7_1
004045f1        result.w = (x87_r7_5 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp7_1) ? 1 : 0) << 0xa | (x87_r7_5 == temp7_1 ? 1 : 0) << 0xe
004045f6        if ((result:1.b & 0x41) == 0)
00404616        float var_8_1 = fconvert.s((fconvert.t(*(edx + 0x29c)) - fconvert.t(*(arg1 + 0x240))) / fconvert.t(*(arg1 + 0x250)))
00404631        float var_4_1 = fconvert.s((fconvert.t(*(edx + 0x2a0)) - fconvert.t(*(arg1 + 0x244))) / fconvert.t(*(arg1 + 0x254)))
00404635        void* eax_1 = get_sprite_texture_ref(*(arg1 + 0x64))
0040463e        int32_t esi_1
0040463e        esi_1.w = *(eax_1 + 0xc)
0040464e        int32_t eax_2
0040464e        int16_t x87control
0040464e        int16_t x87control_1
0040464e        eax_2, x87control_1 = __ftol(x87control, float.t(esi_1) * fconvert.t(var_8_1))
00404655        int32_t edi_1 = eax_2
00404657        int32_t ebx_1
00404657        ebx_1.w = *(eax_1 + 0xe)
00404667        int32_t eax_3 = __ftol(x87control_1, float.t(ebx_1) * fconvert.t(var_4_1))
0040466e        if (edi_1 s< 0)
00404670        edi_1 = 0
00404679        if (edi_1 s> esi_1 - 1)
0040467b        edi_1 = esi_1 - 1
0040467f        if (eax_3 s< 0)
00404681        eax_3 = 0
0040468a        if (eax_3 s> ebx_1 - 1)
0040468c        eax_3 = ebx_1 - 1
004046a1        if (*((esi_1 * eax_3 + edi_1 + 6) * 3 + eax_1) == 0)
004046a3        result.b = 1
004046a8        return result
0040471f        result.b = 0
00404724        return result
