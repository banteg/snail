/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: render_camera @ 0x411fa0 */

00411fae        int32_t eax
00411fae        int16_t x87control
00411fae        int16_t x87control_1
00411fae        eax, x87control_1 = __ftol(x87control, fconvert.t(arg1))
00411fba        int32_t var_98 = eax
00411fbe        int32_t eax_1
00411fbe        int16_t x87control_2
00411fbe        eax_1, x87control_2 = __ftol(x87control_1, fconvert.t(arg2))
00411fca        long double x87_r7_3 = fconvert.t(arg3) * fconvert.t(640f)
00411fd0        int32_t var_94 = eax_1
00411fd4        struct ColorBGRA8 out = fconvert.s(x87_r7_3)
00411fd8        int32_t eax_2
00411fd8        int16_t x87control_3
00411fd8        eax_2, x87control_3 = __ftol(x87control_2, x87_r7_3)
00411fe4        long double x87_r7_5 = fconvert.t(arg4) * fconvert.t(480f)
00411fea        int32_t var_90 = eax_2
00411fee        float var_c4 = fconvert.s(x87_r7_5)
00411ff7        int32_t var_8c = __ftol(x87control_3, x87_r7_5)
00411ffb        int32_t* eax_4 = data_502fec
00412004        int32_t var_88 = 0
0041200c        int32_t var_84 = 0x3f800000
00412018        (*(*eax_4 + 0xa0))(eax_4, &var_98)
00412039        data_5031cc = 0x3e99999a
00412043        data_5031d0 = 0x42500000
0041204d        data_5031d4 = fconvert.s(fconvert.t(arg5) * fconvert.t(0.0174532924f))
0041205b        float ecx_1 = data_5031d4
00412061        data_50316c = fconvert.s(fconvert.t(out) / fconvert.t(var_c4))
0041206f        float var_80[0x10]
0041206f        build_perspective_projection_matrix(&var_80, ecx_1, data_50316c, 0.300000012f, 52f)
00412074        int32_t* eax_6 = data_502fec
00412083        (*(*eax_6 + 0x94))(eax_6, 3, &var_80)
00412097        data_503260 = arg9
0041209f        long double x87_r7_11 = fconvert.t(*(arg6 + 0x20)) + fconvert.t(*(arg6 + 0x30))
004120a5        int32_t edx = *(arg6 + 0x34)
004120a8        int32_t eax_8 = *(arg6 + 0x38)
004120ab        float var_a4 = *(arg6 + 0x30)
004120af        float ecx_4 = *(arg6 + 0x10)
004120b2        int32_t var_a0 = edx
004120b6        float var_bc = fconvert.s(x87_r7_11)
004120bd        long double x87_r7_13 = fconvert.t(*(arg6 + 0x24)) + fconvert.t(*(arg6 + 0x34))
004120c0        int32_t edx_1 = *(arg6 + 0x14)
004120c3        int32_t var_9c = eax_8
004120c7        int32_t eax_9 = *(arg6 + 0x18)
004120ca        float var_b0 = ecx_4
004120ce        int32_t var_ac = edx_1
004120d6        float var_b8 = fconvert.s(x87_r7_13)
004120e0        int32_t var_a8 = eax_9
004120f5        float var_b4 = fconvert.s(fconvert.t(*(arg6 + 0x28)) + fconvert.t(*(arg6 + 0x38)))
004120fb        float var_40[0x10]
004120fb        build_camera_view_matrix(&var_40, &var_a4, &var_bc, &var_b0)
00412100        int32_t* eax_10 = data_502fec
00412112        (*(*eax_10 + 0x94))(eax_10, 2, &var_40)
00412118        int32_t* eax_11 = data_502fec
00412124        (*(*eax_11 + 0xc8))(eax_11, 7, 1)
0041212a        int32_t* eax_12 = data_502fec
00412136        (*(*eax_12 + 0xc8))(eax_12, 0xe, 1)
0041213c        int32_t* eax_13 = data_502fec
00412148        (*(*eax_13 + 0xc8))(eax_13, 0x17, 4)
00412157        void* eax_15
00412157        if (arg8 != 0)
0041215d        eax_15 = data_4df904
00412167        int32_t var_d4_2
00412167        int32_t var_d0_8
00412167        int32_t* eax_21
00412167        int32_t edx_11
00412167        if (arg8 == 0 || *(eax_15 + 4) == 0)
00412217        eax_21 = data_502fec
0041221c        var_d0_8 = 0
0041221e        var_d4_2 = 0x1c
00412220        edx_11 = *eax_21
0041216d        int32_t ecx_7 = *(eax_15 + 8)
00412170        int32_t edx_5 = *(eax_15 + 0xc)
00412173        int32_t* eax_16 = data_502fec
00412187        (*(*eax_16 + 0xc8))(eax_16, 0x1c, 1)
004121a4        pack_color_rgba_u8(&out, data_4df904 + 0x14)
004121a9        int32_t* eax_17 = data_502fec
004121ae        out.a = 0
004121b3        int32_t edx_8
004121b3        edx_8.b = out.b
004121b3        edx_8:1.b = out.g
004121b3        edx_8:2.b = out.r
004121b3        edx_8:3.b = out.a
004121bd        (*(*eax_17 + 0xc8))(eax_17, 0x22, edx_8)
004121c3        int32_t* eax_18 = data_502fec
004121d2        (*(*eax_18 + 0xc8))(eax_18, 0x8c, 3)
004121d8        int32_t* eax_19 = data_502fec
004121e7        (*(*eax_19 + 0xc8))(eax_19, 0x24, ecx_7)
004121ed        int32_t* eax_20 = data_502fec
004121fc        (*(*eax_20 + 0xc8))(eax_20, 0x25, edx_5)
00412208        eax_21 = data_502fec
00412210        edx_11 = *eax_21
00412212        var_d0_8 = *(data_4df904 + 0x10)
00412213        var_d4_2 = 0x26
00412223        (*(edx_11 + 0xc8))(eax_21, var_d4_2, var_d0_8)
00412230        data_5031b8 = arg6
00412236        data_503218 = arg7
0041223b        data_503174 = 0
0041224c        return arg7
