/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_frontend_widget_interaction @ 0x402820 */

0040282e        *(arg1 + 0x1a4) = *(arg1 + 0x1a0)
0040283a        int32_t edx_1 = *(arg1 + 0x1a0) & 0xfffdffff
00402842        *(arg1 + 0x1a0) = edx_1
0040284d        if ((edx_1 & 0x100000) != 0)
00402871        *(arg1 + 0x184) = fconvert.s(fconvert.t(*(arg1 + 0x248)) * fconvert.t(0.100000001f) + fconvert.t(*(arg1 + 0x238)) + fconvert.t(4f) - fconvert.t(12f))
0040288f        *(arg1 + 0x188) = fconvert.s(fconvert.t(*(arg1 + 0x248)) * fconvert.t(0.800000012f) + fconvert.t(*(arg1 + 0x238)) - fconvert.t(4f))
004028ad        *(arg1 + 0x18c) = fconvert.s(fconvert.t(*(arg1 + 0x24c)) * fconvert.t(0.5f) + fconvert.t(*(arg1 + 0x23c)) - fconvert.t(6f))
004028d1        *(arg1 + 0x190) = fconvert.s(fconvert.t(*(arg1 + 0x24c)) * fconvert.t(0.5f) + fconvert.t(*(arg1 + 0x23c)) + fconvert.t(32f) - fconvert.t(6f))
004028ef        *(arg1 + 0x180) = fconvert.s((fconvert.t(*(arg1 + 0x17c)) - fconvert.t(*(arg1 + 0x180))) * fconvert.t(0.800000012f) + fconvert.t(*(arg1 + 0x180)))
004028ef        int16_t top = 0
004028f5        int32_t eax_2 = *(arg1 + 0x1a0)
004028fd        if (eax_2 == 0)
00402909        int16_t eax_3 = (*(arg1 + 4)).w
0040290c        void* ecx_1 = data_4df904 + 0x5a8
00402915        if ((eax_3:1.b & 2) != 0)
00402938        if ((eax_3.b & 0x40) != 0)
0040293f        report_errorf("List remove NEXTBOD")
00402958        return reset_tooltip(arg1 + 0x28c)
00402959        void* eax_6 = *(arg1 + 0xc)
0040295e        if (eax_6 != 0)
00402963        *(eax_6 + 8) = *(arg1 + 8)
00402966        void* eax_7 = *(arg1 + 8)
0040296b        if (eax_7 == 0)
00402978        *(ecx_1 + 4) = *(arg1 + 0xc)
00402970        *(eax_7 + 0xc) = *(arg1 + 0xc)
0040297e        *(arg1 + 0xc) = *(ecx_1 + 8)
00402981        *(ecx_1 + 8) = arg1
0040298d        int32_t eax_9
0040298d        eax_9:1.b = (*(arg1 + 4)):1.b & 0xfd
00402990        *(arg1 + 4) = eax_9
0040299e        return reset_tooltip(arg1 + 0x28c)
0040291c        report_errorf("List remove")
00402935        return reset_tooltip(arg1 + 0x28c)
004029a2        void* ecx_5
004029a2        if ((eax_2:1.b & 2) == 0)
00402a18        if ((eax_2:1.b & 4) == 0)
00402ac9        if ((eax_2:1.b & 0x10) != 0)
00403294        return eax_2
00402ad2        int32_t eax_22
00402ad2        if ((eax_2:1.b & 0x80) == 0)
00402aeb        if ((eax_2.b & 2) != 0)
00402aed        *(arg1 + 0x20c) = 0x3f800000
00402af3        int32_t ecx_7 = *(arg1 + 0x1a0)
00402b09        if ((ecx_7 & 0x2000000) != 0 && *(arg1 + 0x278) == 0)
00402b0b        void* edx_10 = data_4df904
00402b11        long double x87_r7_25 = fconvert.t(*(edx_10 + 0x29c))
00402b17        long double temp4_1 = fconvert.t(*(arg1 + 0x27c))
00402b17        x87_r7_25 - temp4_1
00402b17        top = 0
00402b1d        int32_t eax_23
00402b1d        eax_23.w = (x87_r7_25 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_25, temp4_1) ? 1 : 0) << 0xa | (x87_r7_25 == temp4_1 ? 1 : 0) << 0xe
00402b22        if ((eax_23:1.b & 0x40) == 0)
00402b3d        *(arg1 + 0x1a0) = ecx_7 | 0x4000000
00402b24        long double x87_r7_26 = fconvert.t(*(edx_10 + 0x2a0))
00402b2a        long double temp5_1 = fconvert.t(*(arg1 + 0x280))
00402b2a        x87_r7_26 - temp5_1
00402b2a        top = 0
00402b30        eax_23.w = (x87_r7_26 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_26, temp5_1) ? 1 : 0) << 0xa | (x87_r7_26 == temp5_1 ? 1 : 0) << 0xe
00402b35        if ((eax_23:1.b & 0x40) == 0)
00402b3d        *(arg1 + 0x1a0) = ecx_7 | 0x4000000
00402b4d        if ((*(arg1 + 0x1a0) & 0x80000) != 0 && is_mouse_captured(data_4df904 + 0x290) != 0 && sx.d(read_pressed_text_input_key_code()) == *(arg1 + 0x194))
00402b79        reset_tooltip(arg1 + 0x28c)
00402b7e        int32_t eax_27 = *(arg1 + 0x1a0)
00402b89        if ((eax_27 & 0x1000000) == 0)
00402ba4        sub_403f60(data_4df904 + 0xb4c, arg1, 0x20)
00402b8b        eax_27.b |= 0x20
00402b8d        *(arg1 + 0x1a0) = eax_27
00402bb4        char eax_29 = is_mouse_captured(data_4df904 + 0x290)
00402bbb        char eax_30
00402bbb        if (eax_29 != 0)
00402bc3        eax_30 = border_mouse_test(arg1)
00402bca        if (eax_29 == 0 || eax_30 == 0)
00402d0a        int32_t edx_17 = *(arg1 + 0x1a0) & 0xffdfffff
00402d12        *(arg1 + 0x1a0) = edx_17
00402d1e        if ((0x2000 & edx_17) == 0 && (edx_17.b & 4) != 0)
00402d22        unhighlight_border(arg1)
00402d27        *(arg1 + 0x224) = 0
00402d31        eax_22 = *(arg1 + 0x1a0)
00402d39        if ((eax_22.b & 4) != 0)
00402d3b        eax_22.b &= 0xfd
00402d3d        *(arg1 + 0x1a0) = eax_22
00402bd6        int32_t edx_13 = *(arg1 + 0x1a0) | 0x20000
00402bde        *(arg1 + 0x1a0) = edx_13
00402be6        if ((edx_13.b & 4) != 0)
00402be8        *(arg1 + 0x20c) = 0x3f800000
00402bf4        *(arg1 + 0x21c) = *(arg1 + 0x218)
00402c01        if ((*(arg1 + 0x1a0) & 8) != 0)
00402c03        *(arg1 + 0x224) = 0x3f800000
00402c09        int32_t eax_32 = *(arg1 + 0x1a0)
00402c15        if ((eax_32.b & 2) == 0 && (eax_32.b & 4) != 0)
00402c1c        if ((eax_32 & 0x40000) == 0)
00402c25        play_sound_effect(9)
00402c30        int32_t eax_33
00402c30        eax_33.b = (*(arg1 + 0x1a0)).b | 2
00402c32        *(arg1 + 0x1a0) = eax_33
00402c38        int32_t eax_34 = *(arg1 + 0x1a0)
00402c40        void* ecx_17
00402c40        if ((eax_34.b & 0x10) == 0)
00402ca9        ecx_17 = data_4df904
00402c42        ecx_17 = data_4df904
00402c48        edx_13.b = *(ecx_17 + 0x440ec)
00402c5c        if (edx_13.b == 0 && (*(*(ecx_17 + 0x28c) + 0x3d) & 0x40) != 0)
00402c63        if ((eax_34 & 0x1000000) == 0)
00402c78        sub_403f60(ecx_17 + 0xb4c, arg1, 0x20)
00402c65        eax_34.b |= 0x20
00402c67        *(arg1 + 0x1a0) = eax_34
00402c87        if ((*(arg1 + 0x1a0) & 0x800000) == 0)
00402c90        play_sound_effect(8)
00402c9c        if ((*(arg1 + 0x294) & 0x20) == 0)
00402ca4        reset_tooltip(arg1 + 0x28c)
00402ca9        ecx_17 = data_4df904
00402caf        int32_t eax_35 = *(arg1 + 0x1a0)
00402cc7        if ((eax_35.b & 0x40) != 0 && (*(*(ecx_17 + 0x28c) + 0x3d) & 0x80) != 0)
00402cce        if ((eax_35 & 0x1000000) == 0)
00402ce6        sub_403f60(ecx_17 + 0xb4c, arg1, 0x80)
00402cd0        eax_35.b |= 0x80
00402cd2        *(arg1 + 0x1a0) = eax_35
00402cf2        play_sound_effect(8)
00402cfd        reset_tooltip(arg1 + 0x28c)
00402ad4        *(arg1 + 0x224) = 0
00402d3b        eax_22.b = (*(arg1 + 0x1a0)).b & 0xfd
00402d3d        *(arg1 + 0x1a0) = eax_22
00402ad2        goto label_402d43
00402a24        long double x87_r7_24 = fconvert.t(*(arg1 + 0x268)) + fconvert.t(*(arg1 + 0x264))
00402a2a        *(arg1 + 0x264) = fconvert.s(x87_r7_24)
00402a30        long double temp1_1 = fconvert.t(1f)
00402a30        x87_r7_24 - temp1_1
00402a30        top = 0
00402a36        eax_2.w = (x87_r7_24 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_24, temp1_1) ? 1 : 0) << 0xa | (x87_r7_24 == temp1_1 ? 1 : 0) << 0xe
00402a3b        if ((eax_2:1.b & 0x41) != 0)
00402d43        label_402d43:
00402d43        int32_t eax_37 = *(arg1 + 0x1a0)
00402d4c        if ((eax_37:1.b & 0x80) != 0)
00402d55        *(arg1 + 0x1a0) = eax_37 & 0xffdfffff
00402d5b        unhighlight_border(arg1)
00402d60        int32_t eax_41 = *(arg1 + 0x1a0)
00402d6b        if ((eax_41 & 0x40000) == 0)
00402db9        *(arg1 + 0x210) = fconvert.s((fconvert.t(*(arg1 + 0x20c)) - fconvert.t(*(arg1 + 0x210))) * fconvert.t(0.100000001f) + fconvert.t(*(arg1 + 0x210)))
00402dd7        *(arg1 + 0x220) = fconvert.s((fconvert.t(*(arg1 + 0x21c)) - fconvert.t(*(arg1 + 0x220))) * fconvert.t(0.100000001f) + fconvert.t(*(arg1 + 0x220)))
00402def        long double x87_r7_38 = (fconvert.t(*(arg1 + 0x224)) - fconvert.t(*(arg1 + 0x228))) * fconvert.t(0.100000001f) + fconvert.t(*(arg1 + 0x228))
00402df5        *(arg1 + 0x228) = fconvert.s(x87_r7_38)
00402dfb        long double x87_r7_39 = fconvert.t(*(arg1 + 0x224)) - x87_r7_38
00402e01        long double temp2_1 = fconvert.t(0f)
00402e01        x87_r7_39 - temp2_1
00402e07        eax_41.w = (x87_r7_39 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_39, temp2_1) ? 1 : 0) << 0xa | (x87_r7_39 == temp2_1 ? 1 : 0) << 0xe | 0x3800
00402e0c        if ((eax_41:1.b & 1) != 0)
00402e0e        x87_r7_39 = fneg(x87_r7_39)
00402e10        long double temp3_1 = fconvert.t(0.100000001f)
00402e10        x87_r7_39 - temp3_1
00402e10        top = 0
00402e16        eax_41.w = (x87_r7_39 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_39, temp3_1) ? 1 : 0) << 0xa | (x87_r7_39 == temp3_1 ? 1 : 0) << 0xe
00402e1b        if ((eax_41:1.b & 1) != 0)
00402e23        *(arg1 + 0x228) = *(arg1 + 0x224)
00402d72        *(arg1 + 0x1a0) = eax_41 & 0xfffbffff
00402d7e        *(arg1 + 0x210) = *(arg1 + 0x20c)
00402d8a        *(arg1 + 0x220) = *(arg1 + 0x21c)
00402d96        *(arg1 + 0x228) = *(arg1 + 0x224)
00402e2f        if ((*(arg1 + 0x1a0) & 0x2000) != 0 && is_mouse_captured(data_4df904 + 0x290) != 0)
00402e48        border_input_text(arg1)
00402e53        if ((*(arg1 + 0x1a0) & 0x2000) == 0)
00402e61        activate_all_borders(data_4df904 + 0xb4c)
00402e6c        update_twinkle_manager(arg1 + 0x80)
00402e77        update_tooltip(arg1 + 0x28c)
00402e87        uint8_t eax_45 = (*(arg1 + 0x1a0) u>> 8).b & 1
00402e8d        int32_t ecx_34
00402e8d        int16_t x87control_1
00402e8d        ecx_34, x87control_1 = layout_frontend_widget(arg1)
00402e9b        if (((*(arg1 + 0x1a0)).w:1.b & 0x10) == 0)
00402ea7        long double x87_r7_41 = fconvert.t(1f) - fconvert.t(*(arg1 + 0x210))
00402ec1        int32_t var_18_1 = ecx_34
00402ee1        int32_t var_1c_4 = ecx_34
00402efb        int32_t var_20_1 = ecx_34
00402f15        int32_t var_24_1 = ecx_34
00402f1d        store_color4f(arg1 + 0x1ac, fconvert.s(fconvert.t(*(arg1 + 0x210)) * fconvert.t(*(arg1 + 0x1cc)) + x87_r7_41 * fconvert.t(*(arg1 + 0x1bc))), fconvert.s(fconvert.t(*(arg1 + 0x210)) * fconvert.t(*(arg1 + 0x1d0)) + x87_r7_41 * fconvert.t(*(arg1 + 0x1c0))), fconvert.s(fconvert.t(*(arg1 + 0x210)) * fconvert.t(*(arg1 + 0x1d4)) + x87_r7_41 * fconvert.t(*(arg1 + 0x1c4))), fconvert.s(fconvert.t(*(arg1 + 0x210)) * fconvert.t(*(arg1 + 0x1d8)) + x87_r7_41 * fconvert.t(*(arg1 + 0x1c8))))
00402f28        long double x87_r6_15 = fconvert.t(1f) - fconvert.t(*(arg1 + 0x210))
00402f42        struct Color4f* var_18_3 = arg1 + 0x1ac
00402f62        struct Color4f* var_1c_6 = arg1 + 0x1ac
00402f7c        struct Color4f* var_20_3 = arg1 + 0x1ac
00402f96        struct Color4f* var_24_3 = arg1 + 0x1ac
00402f9e        store_color4f(arg1 + 0x1dc, fconvert.s(fconvert.t(*(arg1 + 0x210)) * fconvert.t(*(arg1 + 0x1fc)) + x87_r6_15 * fconvert.t(*(arg1 + 0x1ec))), fconvert.s(fconvert.t(*(arg1 + 0x210)) * fconvert.t(*(arg1 + 0x200)) + x87_r6_15 * fconvert.t(*(arg1 + 0x1f0))), fconvert.s(fconvert.t(*(arg1 + 0x210)) * fconvert.t(*(arg1 + 0x204)) + x87_r6_15 * fconvert.t(*(arg1 + 0x1f4))), fconvert.s(fconvert.t(*(arg1 + 0x210)) * fconvert.t(*(arg1 + 0x208)) + x87_r6_15 * fconvert.t(*(arg1 + 0x1f8))))
00402f9e        top = 0xfffe
00402fa3        int32_t eax_47 = *(arg1 + 0x1a0)
00402fac        if ((eax_47:1.b & 0x80) != 0)
00402fba        *(arg1 + 0x1dc) = fconvert.s(fconvert.t(*(arg1 + 0x1dc)) * fconvert.t(0.5f))
00402fc8        *(arg1 + 0x1e0) = fconvert.s(fconvert.t(*(arg1 + 0x1e0)) * fconvert.t(0.5f))
00402fda        *(arg1 + 0x1e4) = fconvert.s(fconvert.t(*(arg1 + 0x1e4)) * fconvert.t(0.5f))
00402fec        *(arg1 + 0x1e8) = fconvert.s(fconvert.t(*(arg1 + 0x1e8)) * fconvert.t(0.5f))
00402ffb        *(arg1 + 0x1ac) = fconvert.s(fconvert.t(*(arg1 + 0x1ac)) * fconvert.t(0.5f))
0040300a        *(arg1 + 0x1b0) = fconvert.s(fconvert.t(*(arg1 + 0x1b0)) * fconvert.t(0.5f))
0040301c        *(arg1 + 0x1b4) = fconvert.s(fconvert.t(*(arg1 + 0x1b4)) * fconvert.t(0.5f))
0040302e        *(arg1 + 0x1b8) = fconvert.s(fconvert.t(*(arg1 + 0x1b8)) * fconvert.t(0.5f))
0040302e        top = 0xfffe
00403037        if ((eax_47:1.b & 8) == 0)
00403052        if ((eax_47 & 0x10000) == 0)
004030e0        layout_and_queue_wrapped_font_text(arg1 + 0x2cc, *(arg1 + 0x6ec), *(arg1 + 0x6f0), *(arg1 + 0x6f4), *(arg1 + 0x6f8), arg1 + 0x238, arg1 + 0x23c, arg1 + 0x248, arg1 + 0x24c, *(arg1 + 0x228), (data_4df934.d u>> 8).b & 1, *(arg1 + 0x25c), *(arg1 + 0x260), 0x1000000, arg1 + 0x1dc, 0, eax_45)
00403057        int32_t eax_48 = *(arg1 + 0x50)
0040305a        int32_t ecx_39 = *(arg1 + 0x54)
0040305d        *(arg1 + 0x238) = *(arg1 + 0x4c)
00403063        int32_t edx_21 = *(arg1 + 0x58)
00403066        *(arg1 + 0x23c) = eax_48
0040306c        *(arg1 + 0x248) = ecx_39
00403072        *(arg1 + 0x24c) = edx_21
004030ea        x87control_1 = draw_frontend_widget(arg1)
004030f4        int32_t eax_54 = *(arg1 + 0x278)
004030fc        if (eax_54 != 0)
004030ff        *(arg1 + 0x278) = eax_54 - 1
00403111        *(arg1 + 0x27c) = *(data_4df904 + 0x29c)
00403123        *(arg1 + 0x280) = *(data_4df904 + 0x2a0)
00403129        eax_2 = *(arg1 + 0x1a0)
00403134        if ((eax_2 & 0x100000) == 0)
00403294        return eax_2
0040313a        void* ecx_47 = *(arg1 + 0x71c)
00403140        int32_t eax_57 = *(ecx_47 + 0x1a0)
00403148        if ((eax_57.b & 0x20) != 0)
0040314a        eax_57.b &= 0xdf
0040314c        *(ecx_47 + 0x1a0) = eax_57
00403152        unimplemented  {fld st0, dword [esi+0x17c]}
00403158        unimplemented  {fadd dword [0x497270]}
0040315e        *(arg1 + 0x17c) = fconvert.s(unimplemented  {fst dword [esi+0x17c], st0})
00403164        long double temp6_1 = fconvert.t(0.899999976f)
00403164        unimplemented  {fcomp st0, dword [0x49726c]} f- temp6_1
00403164        bool c0_6 = unimplemented  {fcomp st0, dword [0x49726c]} f< temp6_1
00403164        bool c2_6 = is_unordered.t(unimplemented  {fcomp st0, dword [0x49726c]}, temp6_1)
00403164        bool c3_6 = unimplemented  {fcomp st0, dword [0x49726c]} f== temp6_1
00403164        unimplemented  {fcomp st0, dword [0x49726c]}
0040316a        eax_57.w = (c0_6 ? 1 : 0) << 8 | (c2_6 ? 1 : 0) << 0xa | (c3_6 ? 1 : 0) << 0xe | (top & 7) << 0xb
0040316f        if ((eax_57:1.b & 1) == 0)
00403171        *(arg1 + 0x17c) = 0x3f800000
00403177        void* ecx_48 = *(arg1 + 0x718)
0040317d        int32_t eax_58 = *(ecx_48 + 0x1a0)
00403185        if ((eax_58.b & 0x20) != 0)
00403187        eax_58.b &= 0xdf
00403189        *(ecx_48 + 0x1a0) = eax_58
0040318f        unimplemented  {fld st0, dword [esi+0x17c]}
00403195        unimplemented  {fsub st0, dword [0x497270]}
0040319b        *(arg1 + 0x17c) = fconvert.s(unimplemented  {fst dword [esi+0x17c], st0})
004031a1        long double temp8_1 = fconvert.t(0.100000001f)
004031a1        unimplemented  {fcomp st0, dword [0x497258]} f- temp8_1
004031a1        bool c0_7 = unimplemented  {fcomp st0, dword [0x497258]} f< temp8_1
004031a1        bool c2_7 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497258]}, temp8_1)
004031a1        bool c3_7 = unimplemented  {fcomp st0, dword [0x497258]} f== temp8_1
004031a1        unimplemented  {fcomp st0, dword [0x497258]}
004031a7        eax_58.w = (c0_7 ? 1 : 0) << 8 | (c2_7 ? 1 : 0) << 0xa | (c3_7 ? 1 : 0) << 0xe | (top & 7) << 0xb
004031ac        if ((eax_58:1.b & 0x41) != 0)
004031ae        *(arg1 + 0x17c) = 0
004031b8        unimplemented  {fld st0, dword [esi+0x17c]}
004031be        long double temp7_1 = fconvert.t(0f)
004031be        unimplemented  {fcomp st0, dword [0x497234]} f- temp7_1
004031be        bool c0_8 = unimplemented  {fcomp st0, dword [0x497234]} f< temp7_1
004031be        bool c2_8 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp7_1)
004031be        bool c3_8 = unimplemented  {fcomp st0, dword [0x497234]} f== temp7_1
004031be        unimplemented  {fcomp st0, dword [0x497234]}
004031c9        eax_58.w = (c0_8 ? 1 : 0) << 8 | (c2_8 ? 1 : 0) << 0xa | (c3_8 ? 1 : 0) << 0xe | (top & 7) << 0xb
004031ce        void* eax_59 = *(arg1 + 0x718)
004031d4        int32_t edx_28 = *(eax_59 + 0x1a0)
004031da        if ((eax_58:1.b & 0x40) == 0)
004031e1        edx_28 &= 0xffff7fff
004031dc        edx_28:1.b |= 0x80
004031e3        *(eax_59 + 0x1a0) = edx_28
004031f1        void* eax_61 = *(arg1 + 0x71c)
004031f7        if (*(arg1 + 0x17c) != 0x3f800000)
0040320a        *(eax_61 + 0x1a0) &= 0xffff7fff
004031ff        int32_t ecx_49
004031ff        ecx_49:1.b = (*(eax_61 + 0x1a0)):1.b | 0x80
00403202        *(eax_61 + 0x1a0) = ecx_49
0040321c        int32_t* ecx_51 = *(arg1 + 0x720) + 0x1dc
00403224        *ecx_51 = *(arg1 + 0x1dc)
00403229        ecx_51[1] = *(arg1 + 0x1e0)
0040322f        ecx_51[2] = *(arg1 + 0x1e4)
00403235        ecx_51[3] = *(arg1 + 0x1e8)
00403244        *(*(arg1 + 0x720) + 0x20c) = *(arg1 + 0x20c)
00403256        *(*(arg1 + 0x720) + 0x210) = *(arg1 + 0x210)
0040325c        unimplemented  {fld st0, dword [esi+0x17c]}
00403262        unimplemented  {fmul st0, dword [0x497268]}
00403268        unimplemented  {fadd dword [0x497258]}
00403279        int32_t var_18_6 = __ftol(x87control_1)
00403286        return sub_48b32c(*(arg1 + 0x720) + 0x2cc, "%02i%%")
00402a46        ecx_5 = data_4df904 + 0x5a8
00402a4c        int16_t eax_16 = (*(arg1 + 4)).w
00402a52        if ((eax_16:1.b & 2) != 0)
00402a65        if ((eax_16.b & 0x40) == 0)
00402a76        void* eax_17 = *(arg1 + 0xc)
00402a7b        if (eax_17 != 0)
00402a80        *(eax_17 + 8) = *(arg1 + 8)
00402a83        void* eax_18 = *(arg1 + 8)
00402a88        if (eax_18 == 0)
00402a88        goto label_402a95
00402a8d        *(eax_18 + 0xc) = *(arg1 + 0xc)
00402a90        goto label_402a9b
00402a6c        report_errorf("List remove NEXTBOD")
00402a59        report_errorf("List remove")
004029a4        eax_2:1.b &= 0xfd
004029a7        *(arg1 + 0x1a0) = eax_2
004029b2        ecx_5 = data_4df904 + 0x5a8
004029b8        int16_t eax_12 = (*(arg1 + 4)).w
004029be        if ((eax_12:1.b & 2) == 0)
004029c5        report_errorf("List remove")
004029d4        if ((eax_12.b & 0x40) == 0)
004029e8        void* eax_13 = *(arg1 + 0xc)
004029ed        if (eax_13 != 0)
004029f2        *(eax_13 + 8) = *(arg1 + 8)
004029f5        void* eax_14 = *(arg1 + 8)
004029fa        if (eax_14 == 0)
00402a95        label_402a95:
00402a95        *(ecx_5 + 4) = *(arg1 + 0xc)
00402a95        goto label_402a9b
00402a03        *(eax_14 + 0xc) = *(arg1 + 0xc)
00402a9b        label_402a9b:
00402a9b        *(arg1 + 0xc) = *(ecx_5 + 8)
00402a9e        *(ecx_5 + 8) = arg1
00402aa4        int32_t eax_20
00402aa4        eax_20:1.b = (*(arg1 + 4)):1.b & 0xfd
00402aa7        *(arg1 + 4) = eax_20
004029db        report_errorf("List remove NEXTBOD")
00402ab0        int32_t eax_21 = reset_tooltip(arg1 + 0x28c)
00402ab5        *(arg1 + 0x1a0) = 0
00402ac5        return eax_21
