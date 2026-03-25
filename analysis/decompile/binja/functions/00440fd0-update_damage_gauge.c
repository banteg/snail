/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_damage_gauge @ 0x440fd0 */

00440fd6        void* ecx = data_4df904
00440fdc        void* eax
00440fdc        eax.b = *(ecx + 0x74621)
00440fe4        if (eax.b == 0)
00440ff9        controller->display_fill = fconvert.s((fconvert.t(controller->fill) - fconvert.t(controller->display_fill)) * fconvert.t(0.200000003f) + fconvert.t(controller->display_fill))
00440ffc        long double x87_r7_5 = fconvert.t(controller->hold_progress)
00440fff        long double temp1_1 = fconvert.t(0f)
00440fff        x87_r7_5 - temp1_1
00441005        eax.w = (x87_r7_5 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp1_1) ? 1 : 0) << 0xa | (x87_r7_5 == temp1_1 ? 1 : 0) << 0xe
0044100a        if ((eax:1.b & 0x41) == 0)
0044100f        long double x87_r7_7 = fconvert.t(controller->hold_step) + fconvert.t(controller->hold_progress)
00441012        controller->hold_progress = fconvert.s(x87_r7_7)
00441015        long double temp4_1 = fconvert.t(1f)
00441015        x87_r7_7 - temp4_1
0044101b        eax.w = (x87_r7_7 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp4_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp4_1 ? 1 : 0) << 0xe
00441020        if ((eax:1.b & 0x41) == 0)
00441022        controller->hold_progress = 0f
00441029        uint32_t state = controller->state
0044102e        if (state == 0)
0044116c        if (controller->fill != 0x3f800000)
004411ad        ecx = data_4df904
0044116e        ecx = data_4df904
00441174        eax.b = *(ecx + 0x430199)
0044117c        if (eax.b == 0)
0044117e        eax.b = *(ecx + 0x4301bc)
00441186        if (eax.b == 0)
00441188        controller->state = 1
0044118e        controller->transition_progress = 0f
00441195        controller->transition_step = 0.166666672f
004411a8        start_warning(data_4df904 + 0x430170)
004411ad        ecx = data_4df904
00441035        if (state == 1)
00441114        ecx.b = *(data_4df904 + 0x4301bc)
0044111c        if (ecx.b != 0)
0044111e        controller->transition_progress = 1f
00441128        long double x87_r7_12 = fconvert.t(controller->transition_step) + fconvert.t(controller->transition_progress)
0044112b        controller->transition_progress = fconvert.s(x87_r7_12)
0044112e        long double temp9_1 = fconvert.t(1f)
0044112e        x87_r7_12 - temp9_1
00441134        eax.w = (x87_r7_12 < temp9_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_12, temp9_1) ? 1 : 0) << 0xa | (x87_r7_12 == temp9_1 ? 1 : 0) << 0xe
00441139        if ((eax:1.b & 1) != 0)
004411ad        ecx = data_4df904
0044113b        ecx = data_4df904
0044114b        if (*(ecx + 0x42fde8) == 0x3efae148)
00441158        controller->state = 2
0044115e        play_voice_manager(0x751498, 0xe, 0, 0xffffffff)
004411ad        ecx = data_4df904
0044103c        if (state != 2)
004411ad        ecx = data_4df904
00441054        change_snail_skin(data_4df904 + 0x434038, 1, 0.200000003f)
00441062        apply_damage_gauge_delta(controller, -0.00166666671f, 1)
00441067        controller->transition_counter = 5
0044106e        ecx = data_4df904
00441074        int16_t eax_3
00441074        eax_3.b = *(ecx + 0x4301bc)
0044107c        if (eax_3.b != 0)
00441087        apply_damage_gauge_delta(controller, -0.00666666683f, 0)
0044108c        ecx = data_4df904
00441092        long double x87_r7_8 = fconvert.t(controller->fill)
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
004410e2        controller->state = 0
004410f4        stop_warning(data_4df904 + 0x430170)
004410f9        data_4df904
00441105        stop_warning_sample()
004411ad        ecx = data_4df904
004411b3        long double x87_r7_13 = fconvert.t(controller->display_fill)
004411b6        long double temp0 = fconvert.t(0.999000013f)
004411b6        x87_r7_13 - temp0
004411bc        eax.w = (x87_r7_13 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_13, temp0) ? 1 : 0) << 0xa | (x87_r7_13 == temp0 ? 1 : 0) << 0xe
004411c1        float var_14
004411c1        if ((eax:1.b & 0x41) != 0)
004411cd        long double x87_r7_14 = fconvert.t(controller->display_fill)
004411d0        long double temp2_1 = fconvert.t(0.00999999978f)
004411d0        x87_r7_14 - temp2_1
004411d6        eax.w = (x87_r7_14 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_14, temp2_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp2_1 ? 1 : 0) << 0xe
004411db        if ((eax:1.b & 1) == 0)
004411f6        var_14 = fconvert.s(fconvert.t(351f) - fconvert.t(controller->display_fill) * fconvert.t(308f))
004411dd        var_14 = 396f
004411c3        var_14 = 0f
004411fa        eax.b = *(ecx + 0x74621)
00441202        if (eax.b == 0)
0044120a        controller->_pad_04[0].d = fconvert.s(fconvert.t(controller->_pad_04[4].d) + fconvert.t(controller->_pad_04[0].d))
0044120d        long double x87_r7_20 = fconvert.t(controller->_pad_04[0].d)
00441210        long double temp6 = fconvert.t(1f)
00441210        x87_r7_20 - temp6
00441216        eax.w = (x87_r7_20 < temp6 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_20, temp6) ? 1 : 0) << 0xa | (x87_r7_20 == temp6 ? 1 : 0) << 0xe
0044121b        if ((eax:1.b & 0x41) == 0)
00441226        controller->_pad_04[0].d = fconvert.s(fconvert.t(controller->_pad_04[0].d) - fconvert.t(1f))
00441229        long double x87_r7_23 = fconvert.t(controller->display_fill)
0044122c        long double temp8 = fconvert.t(0.899999976f)
0044122c        x87_r7_23 - temp8
00441232        eax.w = (x87_r7_23 < temp8 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_23, temp8) ? 1 : 0) << 0xa | (x87_r7_23 == temp8 ? 1 : 0) << 0xe
0044123c        void var_10
0044123c        if ((eax:1.b & 0x41) == 0 || controller->state != 0)
00441242        long double x87_r7_24 = fconvert.t(controller->display_fill)
00441245        long double temp10_1 = fconvert.t(0.899999976f)
00441245        x87_r7_24 - temp10_1
0044124b        eax.w = (x87_r7_24 < temp10_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_24, temp10_1) ? 1 : 0) << 0xa | (x87_r7_24 == temp10_1 ? 1 : 0) << 0xe
00441250        float var_18_1
00441250        if ((eax:1.b & 0x41) != 0)
0044126c        long double x87_r7_28 = fconvert.t(controller->display_fill)
0044126f        long double temp12_1 = fconvert.t(0.100000001f)
0044126f        x87_r7_28 - temp12_1
00441275        eax.w = (x87_r7_28 < temp12_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_28, temp12_1) ? 1 : 0) << 0xa | (x87_r7_28 == temp12_1 ? 1 : 0) << 0xe
0044127a        if ((eax:1.b & 1) == 0)
0044128b        var_18_1 = 1f
00441285        var_18_1 = fconvert.s(fconvert.t(controller->display_fill) * fconvert.t(10f))
00441255        if (controller->state != 0)
0044128b        var_18_1 = 1f
00441266        var_18_1 = fconvert.s((fconvert.t(controller->display_fill) - fconvert.t(0.899999976f)) * fconvert.t(10f))
0044129c        void* var_20_1 = ecx
004412f0        int32_t* eax_4 = set_color_rgba(&var_10, 0x3f800000, 0x3f800000, 0x3f800000, fconvert.s(fconvert.t(var_18_1) - (sine(fconvert.s(fconvert.t(controller->_pad_04[0].d) * fconvert.t(6.28318548f))) + fconvert.t(1f)) * fconvert.t(0.5f) * fconvert.t(var_18_1) * fconvert.t(0.5f)))
00441311        queue_axis_aligned_textured_quad_uv(0x5b, 0x440c0000, 0x428c0000, 64f, 396f, 0x1000000, eax_4, 0, 0, 0x3f800000, 0x3f460000, 3, 0)
0044132b        float var_18_3 = fconvert.s(fconvert.t(var_14) * fconvert.t(0.001953125f))
00441372        queue_axis_aligned_textured_quad_uv(0x59, 0x440c0000, 0x428c0000, 64f, var_14, 0x1000000, set_color_rgba(&var_10, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000), 0, 0, 0x3f800000, var_18_3, 3, 0)
004413a3        int32_t* eax_7
004413a3        int32_t ecx_12
004413a3        eax_7, ecx_12 = set_color_rgba(&var_10, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
004413b8        int32_t var_40_1 = ecx_12
004413cb        int32_t var_48 = ecx_12
004413e2        return queue_axis_aligned_textured_quad_uv(0x5a, 0x440c0000, fconvert.s(fconvert.t(var_14) + fconvert.t(70f)), 64f, fconvert.s(fconvert.t(396f) - fconvert.t(var_14)), 0x1000000, eax_7, 0, var_18_3, 0x3f800000, 0x3f460000, 3, 0)
