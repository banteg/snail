/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_damage_gauge @ 0x440fd0 */

00440fd6        void* ecx = data_4df904
00440fdc        int32_t eax
00440fdc        eax.b = *(ecx + 0x74621)
00440fe4        if (eax.b == 0)
00440ff9        player->_pad_00[0x20].d = fconvert.s((fconvert.t(player->_pad_00[0x1c].d) - fconvert.t(player->_pad_00[0x20].d)) * fconvert.t(0.200000003f) + fconvert.t(player->_pad_00[0x20].d))
00440ffc        long double x87_r7_5 = fconvert.t(player->_pad_00[0x24].d)
00440fff        long double temp1_1 = fconvert.t(0f)
00440fff        x87_r7_5 - temp1_1
00441005        eax.w = (x87_r7_5 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp1_1) ? 1 : 0) << 0xa | (x87_r7_5 == temp1_1 ? 1 : 0) << 0xe
0044100a        if ((eax:1.b & 0x41) == 0)
0044100f        long double x87_r7_7 = fconvert.t(player->_pad_00[0x28].d) + fconvert.t(player->_pad_00[0x24].d)
00441012        player->_pad_00[0x24].d = fconvert.s(x87_r7_7)
00441015        long double temp4_1 = fconvert.t(1f)
00441015        x87_r7_7 - temp4_1
0044101b        eax.w = (x87_r7_7 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp4_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp4_1 ? 1 : 0) << 0xe
00441020        if ((eax:1.b & 0x41) == 0)
00441022        player->_pad_00[0x24] = 0
00441022        player->_pad_00[0x25] = 0
00441022        player->_pad_00[0x26] = 0
00441022        player->_pad_00[0x27] = 0
00441029        int32_t eax_1 = player->_pad_00[0].d
0044102e        if (eax_1 == 0)
0044116c        if (player->_pad_00[0x1c].d != 0x3f800000)
004411ad        ecx = data_4df904
0044116e        ecx = data_4df904
00441174        eax.b = *(ecx + 0x430199)
0044117c        if (eax.b == 0)
0044117e        eax.b = *(ecx + 0x4301bc)
00441186        if (eax.b == 0)
00441188        player->_pad_00[0] = 1
00441188        player->_pad_00[1] = 0
00441188        player->_pad_00[2] = 0
00441188        player->_pad_00[3] = 0
0044118e        player->_pad_00[0x10] = 0
0044118e        player->_pad_00[0x11] = 0
0044118e        player->_pad_00[0x12] = 0
0044118e        player->_pad_00[0x13] = 0
00441195        player->_pad_00[0x14] = 0xab
00441195        player->_pad_00[0x15] = 0xaa
00441195        player->_pad_00[0x16] = 0x2a
00441195        player->_pad_00[0x17] = 0x3e
004411a8        start_warning(data_4df904 + 0x430170)
004411ad        ecx = data_4df904
00441035        if (eax_1 == 1)
00441114        ecx.b = *(data_4df904 + 0x4301bc)
0044111c        if (ecx.b != 0)
0044111e        player->_pad_00[0x10] = 0
0044111e        player->_pad_00[0x11] = 0
0044111e        player->_pad_00[0x12] = 0x80
0044111e        player->_pad_00[0x13] = 0x3f
00441128        long double x87_r7_12 = fconvert.t(player->_pad_00[0x14].d) + fconvert.t(player->_pad_00[0x10].d)
0044112b        player->_pad_00[0x10].d = fconvert.s(x87_r7_12)
0044112e        long double temp9_1 = fconvert.t(1f)
0044112e        x87_r7_12 - temp9_1
00441134        eax.w = (x87_r7_12 < temp9_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_12, temp9_1) ? 1 : 0) << 0xa | (x87_r7_12 == temp9_1 ? 1 : 0) << 0xe
00441139        if ((eax:1.b & 1) != 0)
004411ad        ecx = data_4df904
0044113b        ecx = data_4df904
0044114b        if (*(ecx + 0x42fde8) == 0x3efae148)
00441158        player->_pad_00[0] = 2
00441158        player->_pad_00[1] = 0
00441158        player->_pad_00[2] = 0
00441158        player->_pad_00[3] = 0
0044115e        play_voice_manager(0x751498, 0xe, 0, 0xffffffff)
004411ad        ecx = data_4df904
0044103c        if (eax_1 != 2)
004411ad        ecx = data_4df904
00441054        change_snail_skin(data_4df904 + 0x434038, 1, 0.200000003f)
00441062        apply_damage_gauge_delta(player, -0.00166666671f, 1)
00441067        player->_pad_00[0x18] = 5
00441067        player->_pad_00[0x19] = 0
00441067        player->_pad_00[0x1a] = 0
00441067        player->_pad_00[0x1b] = 0
0044106e        ecx = data_4df904
00441074        int16_t eax_4
00441074        eax_4.b = *(ecx + 0x4301bc)
0044107c        if (eax_4.b != 0)
00441087        apply_damage_gauge_delta(player, -0.00666666683f, 0)
0044108c        ecx = data_4df904
00441092        long double x87_r7_8 = fconvert.t(player->_pad_00[0x1c].d)
00441095        long double temp11_1 = fconvert.t(0f)
00441095        x87_r7_8 - temp11_1
004410ac        if ((((x87_r7_8 < temp11_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp11_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp11_1 ? 1 : 0) << 0xe):1.b & 0x40) == 0 || *(ecx + 0x42fde8) != 0x3efae148)
004410ae        long double x87_r7_9 = fconvert.t(*(ecx + 0x4301c0))
004410b4        long double temp13_1 = fconvert.t(0f)
004410b4        x87_r7_9 - temp13_1
004410bf        if ((((x87_r7_9 < temp13_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp13_1) ? 1 : 0) << 0xa | (x87_r7_9 == temp13_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
004410bf        goto label_4410e2
004410c1        long double x87_r7_10 = fconvert.t(*(ecx + 0x42fe08))
004410c7        long double temp14_1 = fconvert.t(0f)
004410c7        x87_r7_10 - temp14_1
004410dc        if ((((x87_r7_10 < temp14_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_10, temp14_1) ? 1 : 0) << 0xa | (x87_r7_10 == temp14_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0 || *(ecx + 0x434064) != 0)
004410d2        goto label_4410e2
004410e2        label_4410e2:
004410e2        player->_pad_00[0] = 0
004410e2        player->_pad_00[1] = 0
004410e2        player->_pad_00[2] = 0
004410e2        player->_pad_00[3] = 0
004410f4        stop_warning(data_4df904 + 0x430170)
004410f9        data_4df904
00441105        stop_warning_sample()
004411ad        ecx = data_4df904
004411b3        long double x87_r7_13 = fconvert.t(player->_pad_00[0x20].d)
004411b6        long double temp0 = fconvert.t(0.999000013f)
004411b6        x87_r7_13 - temp0
004411bc        eax.w = (x87_r7_13 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_13, temp0) ? 1 : 0) << 0xa | (x87_r7_13 == temp0 ? 1 : 0) << 0xe
004411c1        float var_14
004411c1        if ((eax:1.b & 0x41) != 0)
004411cd        long double x87_r7_14 = fconvert.t(player->_pad_00[0x20].d)
004411d0        long double temp2_1 = fconvert.t(0.00999999978f)
004411d0        x87_r7_14 - temp2_1
004411d6        eax.w = (x87_r7_14 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_14, temp2_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp2_1 ? 1 : 0) << 0xe
004411db        if ((eax:1.b & 1) == 0)
004411f6        var_14 = fconvert.s(fconvert.t(351f) - fconvert.t(player->_pad_00[0x20].d) * fconvert.t(308f))
004411dd        var_14 = 396f
004411c3        var_14 = 0f
004411fa        eax.b = *(ecx + 0x74621)
00441202        if (eax.b == 0)
0044120a        player->_pad_00[4].d = fconvert.s(fconvert.t(player->_pad_00[8].d) + fconvert.t(player->_pad_00[4].d))
0044120d        long double x87_r7_20 = fconvert.t(player->_pad_00[4].d)
00441210        long double temp6 = fconvert.t(1f)
00441210        x87_r7_20 - temp6
00441216        eax.w = (x87_r7_20 < temp6 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_20, temp6) ? 1 : 0) << 0xa | (x87_r7_20 == temp6 ? 1 : 0) << 0xe
0044121b        if ((eax:1.b & 0x41) == 0)
00441226        player->_pad_00[4].d = fconvert.s(fconvert.t(player->_pad_00[4].d) - fconvert.t(1f))
00441229        long double x87_r7_23 = fconvert.t(player->_pad_00[0x20].d)
0044122c        long double temp8 = fconvert.t(0.899999976f)
0044122c        x87_r7_23 - temp8
00441232        eax.w = (x87_r7_23 < temp8 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_23, temp8) ? 1 : 0) << 0xa | (x87_r7_23 == temp8 ? 1 : 0) << 0xe
0044123c        struct Color4f color
0044123c        if ((eax:1.b & 0x41) == 0 || player->_pad_00[0].d != 0)
00441242        long double x87_r7_24 = fconvert.t(player->_pad_00[0x20].d)
00441245        long double temp10_1 = fconvert.t(0.899999976f)
00441245        x87_r7_24 - temp10_1
0044124b        eax.w = (x87_r7_24 < temp10_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_24, temp10_1) ? 1 : 0) << 0xa | (x87_r7_24 == temp10_1 ? 1 : 0) << 0xe
00441250        float var_18_1
00441250        if ((eax:1.b & 0x41) != 0)
0044126c        long double x87_r7_28 = fconvert.t(player->_pad_00[0x20].d)
0044126f        long double temp12_1 = fconvert.t(0.100000001f)
0044126f        x87_r7_28 - temp12_1
00441275        eax.w = (x87_r7_28 < temp12_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_28, temp12_1) ? 1 : 0) << 0xa | (x87_r7_28 == temp12_1 ? 1 : 0) << 0xe
0044127a        if ((eax:1.b & 1) == 0)
0044128b        var_18_1 = 1f
00441285        var_18_1 = fconvert.s(fconvert.t(player->_pad_00[0x20].d) * fconvert.t(10f))
00441255        if (player->_pad_00[0].d != 0)
0044128b        var_18_1 = 1f
00441266        var_18_1 = fconvert.s((fconvert.t(player->_pad_00[0x20].d) - fconvert.t(0.899999976f)) * fconvert.t(10f))
0044129c        void* var_20_1 = ecx
004412f0        struct Color4f* eax_5 = set_color_rgba(&color, 1f, 1f, 1f, fconvert.s(fconvert.t(var_18_1) - (sine(fconvert.s(fconvert.t(player->_pad_00[4].d) * fconvert.t(6.28318548f))) + fconvert.t(1f)) * fconvert.t(0.5f) * fconvert.t(var_18_1) * fconvert.t(0.5f)))
00441311        queue_axis_aligned_textured_quad_uv(0x5b, 0x440c0000, 0x428c0000, 64f, 396f, 0x1000000, eax_5, 0, 0, 0x3f800000, 0x3f460000, 3, 0)
0044132b        float var_18_3 = fconvert.s(fconvert.t(var_14) * fconvert.t(0.001953125f))
00441372        queue_axis_aligned_textured_quad_uv(0x59, 0x440c0000, 0x428c0000, 64f, var_14, 0x1000000, set_color_rgba(&color, 1f, 1f, 1f, 1f), 0, 0, 0x3f800000, var_18_3, 3, 0)
004413a3        int32_t* eax_8
004413a3        int32_t ecx_12
004413a3        eax_8, ecx_12 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
004413b8        int32_t var_40_1 = ecx_12
004413cb        int32_t var_48 = ecx_12
004413d6        queue_axis_aligned_textured_quad_uv(0x5a, 0x440c0000, fconvert.s(fconvert.t(var_14) + fconvert.t(70f)), 64f, fconvert.s(fconvert.t(396f) - fconvert.t(var_14)), 0x1000000, eax_8, 0, var_18_3, 0x3f800000, 0x3f460000, 3, 0)
004413e2        return
