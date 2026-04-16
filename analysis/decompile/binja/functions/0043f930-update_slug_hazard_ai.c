/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_slug_hazard_ai @ 0x43f930 */

0043f93a        void* result = *(arg1 + 0x88)
0043f943        if (*(result + 9) == 0)
0043f949        result = *(arg1 + 0x80)
0043f952        if (result u> 4)
0043fccd        label_43fccd:
0043fccd        unimplemented  {fld st0, dword [eax+0x370]}
0043fcd3        unimplemented  {fadd dword [esi+0x98]}
0043fcd9        *(*(arg1 + 0xac) + 0x7c) = fconvert.s(unimplemented  {fstp dword [ecx+0x7c], st0})
0043fcd9        unimplemented  {fstp dword [ecx+0x7c], st0}
0043fce9        if (*(*(arg1 + 0xc0) + 0x384) == 1)
0043fcf1        unimplemented  {fld st0, dword [ecx+0x3a0]}
0043fcf7        unimplemented  {fadd dword [eax+0x7c]}
0043fcfa        *(*(arg1 + 0xac) + 0x7c) = fconvert.s(unimplemented  {fstp dword [eax+0x7c], st0})
0043fcfa        unimplemented  {fstp dword [eax+0x7c], st0}
0043fcff        return update_slug_voice_ai(arg1)
0043f958        void* ecx_19
0043f958        switch (result)
0043f96d        case 1
0043f96d        if (*(arg1 + 0xcc) != 0 && data_4b7236 != 0)
0043f96f        int32_t ecx = *(arg1 + 0xd4)
0043f975        *(arg1 + 0xcc) = 0
0043f97b        *(arg1 + 0xd0) = ecx
0043f981        long double x87_r7_1 = fconvert.t(*(arg1 + 0xd0))
0043f987        long double temp1_1 = fconvert.t(0f)
0043f987        x87_r7_1 - temp1_1
0043f98d        result.w = (x87_r7_1 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp1_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp1_1 ? 1 : 0) << 0xe
0043f992        int32_t eax
0043f992        if ((result:1.b & 0x40) != 0)
0043fa56        *(arg1 + 0xe4) = fconvert.s(fconvert.t(*(arg1 + 0xe8)) + fconvert.t(*(arg1 + 0xe4)))
0043fa5c        long double x87_r7_6 = fconvert.t(*(arg1 + 0xe8))
0043fa62        long double temp3_1 = fconvert.t(0f)
0043fa62        x87_r7_6 - temp3_1
0043fa68        result.w = (x87_r7_6 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp3_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp3_1 ? 1 : 0) << 0xe
0043fa6d        if ((result:1.b & 0x41) != 0)
0043fa8f        set_sprite_texture_ref(*(arg1 + 0xac), 0x77, 0)
0043fa9a        *(*(arg1 + 0xac) + 0x28) = 0
0043fa77        set_sprite_texture_ref(*(arg1 + 0xac), 0x76, 0)
0043fa82        *(*(arg1 + 0xac) + 0x28) = 0
0043faba        store_color4f(*(arg1 + 0xac) + 0x2c, 1f, 1f, 1f, 1f)
0043fabf        long double x87_r6_1 = fconvert.t(*(arg1 + 0xe4))
0043fac5        long double temp10_1 = fconvert.t(0f)
0043fac5        x87_r6_1 - temp10_1
0043facb        eax.w = (x87_r6_1 < temp10_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_1, temp10_1) ? 1 : 0) << 0xa | (x87_r6_1 == temp10_1 ? 1 : 0) << 0xe | 0x3800
0043fad0        if ((eax:1.b & 1) == 0)
0043faf0        long double x87_r6_3 = fconvert.t(*(arg1 + 0xe4))
0043faf6        long double temp13_1 = fconvert.t(1f)
0043faf6        x87_r6_3 - temp13_1
0043fafc        eax.w = (x87_r6_3 < temp13_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_3, temp13_1) ? 1 : 0) << 0xa | (x87_r6_3 == temp13_1 ? 1 : 0) << 0xe | 0x3800
0043fb01        if ((eax:1.b & 0x41) == 0)
0043fb03        *(arg1 + 0xe4) = 0x3f800000
0043fb0d        *(arg1 + 0xe8) = 0xbe2aaaab
0043fad2        *(arg1 + 0xe4) = 0
0043fae3        int80_t st0_1
0043fae3        st0_1, eax = advance_blink_random(data_4df904 + 0x74618)
0043fae8        *(arg1 + 0xe8) = fconvert.s(st0_1)
0043f99e        long double x87_r7_3 = fconvert.t(*(arg1 + 0xd4)) + fconvert.t(*(arg1 + 0xd0))
0043f9a4        *(arg1 + 0xd0) = fconvert.s(x87_r7_3)
0043f9aa        long double temp4_1 = fconvert.t(1f)
0043f9aa        x87_r7_3 - temp4_1
0043f9b0        result.w = (x87_r7_3 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp4_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp4_1 ? 1 : 0) << 0xe
0043f9b5        if ((result:1.b & 0x41) != 0)
0043fa18        *(*(arg1 + 0xac) + 0x28) = 5
0043fa25        set_sprite_texture_ref(*(arg1 + 0xac), 0x78, 0)
0043fa3f        store_color4f(*(arg1 + 0xac) + 0x2c, 1f, 0f, 0f, 0.99000001f)
0043f9b7        void* edx_1 = *(arg1 + 0xac)
0043f9bd        *(arg1 + 0xd0) = 0
0043f9c3        *(arg1 + 0xe4) = 0x3f800000
0043f9cd        *(arg1 + 0xe8) = 0xbe2aaaab
0043f9d7        *(edx_1 + 0x28) = 0
0043f9f7        store_color4f(*(arg1 + 0xac) + 0x2c, 1f, 1f, 1f, 1f)
0043fa05        set_sprite_texture_ref(*(arg1 + 0xac), 0x77, 0)
0043fb20        long double x87_r6_5 = fconvert.t(*(*(arg1 + 0xc0) + 0x70)) + fconvert.t(1f)
0043fb26        long double temp11_1 = fconvert.t(*(arg1 + 0x70))
0043fb26        x87_r6_5 - temp11_1
0043fb29        eax.w = (x87_r6_5 < temp11_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_5, temp11_1) ? 1 : 0) << 0xa | (x87_r6_5 == temp11_1 ? 1 : 0) << 0xe | 0x3800
0043fb36        if ((eax:1.b & 0x41) == 0 && *(arg1 + 0xd9) == 0)
0043fb38        *(arg1 + 0xd9) = 1
0043fb4c        long double x87_r6_7 = float.t(next_math_random_value()) * fconvert.t(3.05175781e-05f)
0043fb52        long double temp15_1 = fconvert.t(0.600000024f)
0043fb52        x87_r6_7 - temp15_1
0043fb58        eax.w = (x87_r6_7 < temp15_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_7, temp15_1) ? 1 : 0) << 0xa | (x87_r6_7 == temp15_1 ? 1 : 0) << 0xe | 0x3800
0043fb5d        int16_t x87control
0043fb5d        if ((eax:1.b & 0x41) == 0)
0043fb81        play_slug_voice(arg1, 0x1e - __ftol(x87control, float.t(next_math_random_value()) * fconvert.t(-0.000122070312f)))
0043fb86        void* ecx_15 = *(arg1 + 0xc0)
0043fb8c        long double x87_r6_10 = fconvert.t(*(arg1 + 0x70))
0043fb8f        long double temp14_1 = fconvert.t(*(ecx_15 + 0x70))
0043fb8f        x87_r6_10 - temp14_1
0043fb92        eax.w = (x87_r6_10 < temp14_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_10, temp14_1) ? 1 : 0) << 0xa | (x87_r6_10 == temp14_1 ? 1 : 0) << 0xe | 0x3800
0043fb9f        if ((eax:1.b & 1) != 0 && *(arg1 + 0xb4) == 0)
0043fba1        *(arg1 + 0xb4) = 1
0043fbaf        if (*(arg1 + 0xc4) == 1)
0043fbb4        long double x87_r6_12 = fconvert.t(*(ecx_15 + 0x70)) + fconvert.t(16f)
0043fbba        long double temp17_1 = fconvert.t(*(arg1 + 0x70))
0043fbba        x87_r6_12 - temp17_1
0043fbbd        eax.w = (x87_r6_12 < temp17_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_12, temp17_1) ? 1 : 0) << 0xa | (x87_r6_12 == temp17_1 ? 1 : 0) << 0xe | 0x3800
0043fbc2        if ((eax:1.b & 0x41) == 0)
0043fbcf        *(arg1 + 0xc4) = 0
0043fbd5        play_voice_manager(0x751498, 2, 1, 0xffffffff)
0043fbe5        int32_t* eax_6 = *(arg1 + 0xac) + 0x48
0043fbea        *eax_6 = *(arg1 + 0x68)
0043fbef        eax_6[1] = *(arg1 + 0x6c)
0043fbf5        eax_6[2] = *(arg1 + 0x70)
0043fbf8        void* ecx_18 = *(arg1 + 0xc0)
0043fbfe        long double x87_r6_13 = fconvert.t(*(arg1 + 0x70))
0043fc01        long double temp16_1 = fconvert.t(*(ecx_18 + 0x2980))
0043fc01        x87_r6_13 - temp16_1
0043fc07        eax_6.w = (x87_r6_13 < temp16_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_13, temp16_1) ? 1 : 0) << 0xa | (x87_r6_13 == temp16_1 ? 1 : 0) << 0xe | 0x3800
0043fc0c        if ((eax_6:1.b & 1) == 0)
0043fc8d        long double x87_r6_14 = fconvert.t(*(ecx_18 + 0x374))
0043fc93        long double temp18_1 = fconvert.t(0f)
0043fc93        x87_r6_14 - temp18_1
0043fc99        eax_6.w = (x87_r6_14 < temp18_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_14, temp18_1) ? 1 : 0) << 0xa | (x87_r6_14 == temp18_1 ? 1 : 0) << 0xe | 0x3800
0043fc9e        if ((eax_6:1.b & 0x41) == 0)
0043fca2        kill_slug_hazard(arg1)
0043fcbc        sub_415ef0(*(arg1 + 0x88) + 0x1270fd4, arg1 + 0x68, 2f, 1, arg1)
0043fcbc        goto label_43fccd
0043fc0e        int16_t eax_7 = (*(arg1 + 4)).w
0043fc11        *(arg1 + 0x80) = 0
0043fc20        ecx_19 = data_4df904 + 0x5a8
0043fc26        if ((eax_7:1.b & 2) == 0)
0043fc2d        report_errorf("List remove")
0043fc46        return kill_sprite(*(arg1 + 0xac))
0043fc49        if ((eax_7.b & 0x40) != 0)
0043fc50        report_errorf("List remove NEXTBOD")
0043fc69        return kill_sprite(*(arg1 + 0xac))
0043fc6a        void* eax_10 = *(arg1 + 0xc)
0043fc6f        if (eax_10 != 0)
0043fc74        *(eax_10 + 8) = *(arg1 + 8)
0043fc77        void* eax_11 = *(arg1 + 8)
0043fc7c        if (eax_11 == 0)
0043fc7c        goto label_43ffdf
0043fc85        *(eax_11 + 0xc) = *(arg1 + 0xc)
0043fc88        goto label_43ffe5
0043fe46        case 2
0043fe46        int32_t var_24_4 = 0
0043fe4c        *(arg1 + 0x80) = 3
0043fe5b        float var_10_1 = fconvert.s(random_float_below(0.300000012f))
0043fe5f        int32_t var_2c_1 = 0
0043fe70        void* var_34_1 = &data_4a4e70
0043fe7a        float var_14_3 = fconvert.s(random_float_below(0.200000003f) + fconvert.t(0.100000001f))
0043fea6        *(arg1 + 0x8c) = fconvert.s(random_signed_float_below(0.100000001f))
0043feac        *(arg1 + 0x90) = var_14_3
0043feb3        *(arg1 + 0x94) = var_10_1
0043feb6        int32_t eax_26 = *(arg1 + 0x84)
0043febf        if (eax_26 == 1)
0043fec1        long double x87_r7_20 = fconvert.t(*(arg1 + 0x8c))
0043fec3        long double temp2_1 = fconvert.t(0f)
0043fec3        x87_r7_20 - temp2_1
0043fec9        long double x87_r7_21 = fconvert.t(*(arg1 + 0x8c))
0043fecb        eax_26.w = (x87_r7_20 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_20, temp2_1) ? 1 : 0) << 0xa | (x87_r7_20 == temp2_1 ? 1 : 0) << 0xe | 0x3800
0043fed0        if ((eax_26:1.b & 1) != 0)
0043fed2        x87_r7_21 = fneg(x87_r7_21)
0043fef0        *(arg1 + 0x8c) = fconvert.s(x87_r7_21)
0043fed9        if (eax_26 == 2)
0043fedb        long double x87_r7_22 = fconvert.t(*(arg1 + 0x8c))
0043fedd        long double temp7_1 = fconvert.t(0f)
0043fedd        x87_r7_22 - temp7_1
0043fee3        long double x87_r7_23 = fconvert.t(*(arg1 + 0x8c))
0043fee5        eax_26.w = (x87_r7_22 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_22, temp7_1) ? 1 : 0) << 0xa | (x87_r7_22 == temp7_1 ? 1 : 0) << 0xe | 0x3800
0043feea        if ((eax_26:1.b & 1) != 0)
0043feec        x87_r7_23 = fneg(x87_r7_23)
0043fef0        *(arg1 + 0x8c) = fconvert.s(fneg(x87_r7_23))
0043fef2        long double x87_r7_24 = fconvert.t(*(arg1 + 0x8c))
0043fef4        long double temp6_1 = fconvert.t(0f)
0043fef4        x87_r7_24 - temp6_1
0043fefa        eax_26.w = (x87_r7_24 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_24, temp6_1) ? 1 : 0) << 0xa | (x87_r7_24 == temp6_1 ? 1 : 0) << 0xe
0043feff        int32_t var_14_4
0043feff        if ((eax_26:1.b & 1) == 0)
0043ff0b        long double x87_r7_25 = fconvert.t(*(arg1 + 0x8c))
0043ff0d        long double temp9_1 = fconvert.t(0f)
0043ff0d        x87_r7_25 - temp9_1
0043ff13        var_14_4 = 0
0043ff17        eax_26.w = (x87_r7_25 < temp9_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_25, temp9_1) ? 1 : 0) << 0xa | (x87_r7_25 == temp9_1 ? 1 : 0) << 0xe
0043ff1c        if ((eax_26:1.b & 0x40) == 0)
0043ff1e        var_14_4 = 1
0043ff01        var_14_4 = 0xffffffff
0043ff2a        void* eax_27 = *(arg1 + 0x88)
0043ff30        *(arg1 + 0x9c) = 0
0043ff3e        *(arg1 + 0x8c) = fconvert.s(float.t(var_14_4) * fconvert.t(0.200000003f) + fconvert.t(*(arg1 + 0x8c)))
0043ff43        long double x87_r7_30 = fconvert.t(*(eax_27 + 0x38)) * fconvert.t(0.00833333377f)
0043ff49        *(arg1 + 0xa4) = 0
0043ff4f        *(arg1 + 0xa0) = fconvert.s(x87_r7_30)
0043ff5e        *(arg1 + 0xa8) = fconvert.s(fconvert.t(*(eax_27 + 0x38)) * fconvert.t(0.166666672f))
0043feff        goto label_43ff64
0043ff64        case 3
0043ff64        label_43ff64:
0043ff64        int16_t eax_28 = (*(arg1 + 4)).w
0043ff67        *(arg1 + 0x80) = 0
0043ff73        ecx_19 = data_4df904 + 0x5a8
0043ff7c        if ((eax_28:1.b & 2) == 0)
0043ff83        report_errorf("List remove")
0043ff9c        return kill_sprite(*(arg1 + 0xac))
0043ff9f        if ((eax_28.b & 0x40) != 0)
0043ffa6        report_errorf("List remove NEXTBOD")
0043ffbf        return kill_sprite(*(arg1 + 0xac))
0043ffc0        void* eax_31 = *(arg1 + 0xc)
0043ffc5        if (eax_31 != 0)
0043ffca        *(eax_31 + 8) = *(arg1 + 8)
0043ffcd        void* eax_32 = *(arg1 + 8)
0043ffd2        if (eax_32 == 0)
0043ffdf        label_43ffdf:
0043ffdf        *(ecx_19 + 4) = *(arg1 + 0xc)
0043ffdf        goto label_43ffe5
0043ffd7        *(eax_32 + 0xc) = *(arg1 + 0xc)
0043ffe5        label_43ffe5:
0043ffe5        *(arg1 + 0xc) = *(ecx_19 + 8)
0043ffe8        *(ecx_19 + 8) = arg1
0043ffee        void* ecx_40 = *(arg1 + 0xac)
0043fff4        int32_t eax_34
0043fff4        eax_34:1.b = (*(arg1 + 4)):1.b & 0xfd
0043fff7        *(arg1 + 4) = eax_34
00440005        return kill_sprite(ecx_40)
0043fd11        case 4
0043fd11        long double x87_r7_8 = fconvert.t(*(arg1 + 0xbc)) + fconvert.t(*(arg1 + 0xb8))
0043fd17        long double temp0_1 = fconvert.t(6.28318548f)
0043fd17        x87_r7_8 - temp0_1
0043fd1d        *(arg1 + 0xb8) = fconvert.s(x87_r7_8)
0043fd1d        bool c1_1 = unimplemented  {fst dword [esi+0xb8], st0}
0043fd23        result.w = (x87_r7_8 < temp0_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_8, temp0_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp0_1 ? 1 : 0) << 0xe | 0x3800
0043fd28        if ((result:1.b & 0x41) == 0)
0043fd30        *(arg1 + 0xb8) = fconvert.s(x87_r7_8 - fconvert.t(6.28318548f))
0043fd46        long double x87_r7_12 = sine(*(arg1 + 0xb8)) * fconvert.t(3f)
0043fd4c        void* ecx_28 = *(arg1 + 0xc0)
0043fd55        *(arg1 + 0x68) = fconvert.s(x87_r7_12)
0043fd58        long double x87_r7_13 = fconvert.t(*(arg1 + 0x70))
0043fd5b        long double temp5_1 = fconvert.t(*(ecx_28 + 0x70))
0043fd5b        x87_r7_13 - temp5_1
0043fd6b        if ((((x87_r7_13 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_13, temp5_1) ? 1 : 0) << 0xa | (x87_r7_13 == temp5_1 ? 1 : 0) << 0xe):1.b & 1) != 0 && *(arg1 + 0xb4) == 0)
0043fd6d        *(arg1 + 0xb4) = 1
0043fd7d        int32_t* edx_10 = *(arg1 + 0xac) + 0x48
0043fd80        *edx_10 = *(arg1 + 0x68)
0043fd85        edx_10[1] = *(arg1 + 0x6c)
0043fd8b        edx_10[2] = *(arg1 + 0x70)
0043fd8e        void* ecx_30 = *(arg1 + 0xc0)
0043fd94        long double x87_r7_14 = fconvert.t(*(arg1 + 0x70))
0043fd97        long double temp8_1 = fconvert.t(*(ecx_30 + 0x2980))
0043fd97        x87_r7_14 - temp8_1
0043fd9d        int32_t eax_16
0043fd9d        eax_16.w = (x87_r7_14 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_14, temp8_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp8_1 ? 1 : 0) << 0xe
0043fda2        if ((eax_16:1.b & 1) == 0)
0043fe23        long double x87_r7_15 = fconvert.t(*(ecx_30 + 0x374))
0043fe29        long double temp12_1 = fconvert.t(0f)
0043fe29        x87_r7_15 - temp12_1
0043fe2f        eax_16.w = (x87_r7_15 < temp12_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_15, temp12_1) ? 1 : 0) << 0xa | (x87_r7_15 == temp12_1 ? 1 : 0) << 0xe
0043fe34        if ((eax_16:1.b & 0x41) == 0)
0043fe3c        kill_slug_hazard(arg1)
0043fe34        goto label_43fccd
0043fda4        int16_t eax_17 = (*(arg1 + 4)).w
0043fda7        *(arg1 + 0x80) = 0
0043fdb3        ecx_19 = data_4df904 + 0x5a8
0043fdbc        if ((eax_17:1.b & 2) == 0)
0043fdc3        report_errorf("List remove")
0043fddc        return kill_sprite(*(arg1 + 0xac))
0043fddf        if ((eax_17.b & 0x40) != 0)
0043fde6        report_errorf("List remove NEXTBOD")
0043fdff        return kill_sprite(*(arg1 + 0xac))
0043fe00        void* eax_20 = *(arg1 + 0xc)
0043fe05        if (eax_20 != 0)
0043fe0a        *(eax_20 + 8) = *(arg1 + 8)
0043fe0d        void* eax_21 = *(arg1 + 8)
0043fe12        if (eax_21 == 0)
0043fe12        goto label_43ffdf
0043fe1b        *(eax_21 + 0xc) = *(arg1 + 0xc)
0043fe1e        goto label_43ffe5
0043fd0a        return result
