/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_damage_gauge @ 0x440fd0 */

00440fd3        int32_t esi
00440fd3        int32_t var_1c = esi
00440fd3        int32_t* esp_1 = &var_1c
00440fd6        void* ecx = data_4df904
00440fdc        int32_t eax
00440fdc        eax.b = *(ecx + 0x74621)
00440fe4        if (eax.b == 0)
00440ff9        controller->display_fill = fconvert.s((fconvert.t(controller->fill) - fconvert.t(controller->display_fill)) * fconvert.t(0.200000003f) + fconvert.t(controller->display_fill))
00440ffc        long double x87_r7_5 = fconvert.t(controller->hit_flash_progress)
00440fff        long double temp1_1 = fconvert.t(0f)
00440fff        x87_r7_5 - temp1_1
00441005        eax.w = (x87_r7_5 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp1_1) ? 1 : 0) << 0xa | (x87_r7_5 == temp1_1 ? 1 : 0) << 0xe
0044100a        if ((eax:1.b & 0x41) == 0)
0044100f        long double x87_r7_7 = fconvert.t(controller->hit_flash_step) + fconvert.t(controller->hit_flash_progress)
00441012        controller->hit_flash_progress = fconvert.s(x87_r7_7)
00441015        long double temp4_1 = fconvert.t(1f)
00441015        x87_r7_7 - temp4_1
0044101b        eax.w = (x87_r7_7 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp4_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp4_1 ? 1 : 0) << 0xe
00441020        if ((eax:1.b & 0x41) == 0)
00441022        controller->hit_flash_progress = 0f
00441029        int32_t state = controller->state
0044102e        if (state == 0)
0044116c        if (controller->fill != 0x3f800000)
004411ad        ecx = data_4df904
0044116e        ecx = data_4df904
00441174        eax.b = *(ecx + 0x430199)
0044117c        if (eax.b == 0)
0044117e        eax.b = *(ecx + 0x4301bc)
00441186        if (eax.b == 0)
00441188        controller->state = 1
0044118e        controller->warning_transition_progress = 0f
00441195        controller->warning_transition_step = 0.166666672f
004411a8        start_warning(data_4df904 + 0x430170)
004411ad        ecx = data_4df904
00441035        int32_t var_24
00441035        float var_20
00441035        if (state == 1)
00441114        ecx.b = *(data_4df904 + 0x4301bc)
0044111c        if (ecx.b != 0)
0044111e        controller->warning_transition_progress = 1f
00441128        long double x87_r7_12 = fconvert.t(controller->warning_transition_step) + fconvert.t(controller->warning_transition_progress)
0044112b        controller->warning_transition_progress = fconvert.s(x87_r7_12)
0044112e        long double temp9_1 = fconvert.t(1f)
0044112e        x87_r7_12 - temp9_1
00441134        eax.w = (x87_r7_12 < temp9_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_12, temp9_1) ? 1 : 0) << 0xa | (x87_r7_12 == temp9_1 ? 1 : 0) << 0xe
00441139        if ((eax:1.b & 1) != 0)
004411ad        ecx = data_4df904
0044113b        ecx = data_4df904
0044114b        if (*(ecx + 0x42fde8) == 0x3efae148)
0044114d        var_20 = nanf
0044114f        var_24 = 0
00441151        int32_t var_28_2 = 0xe
00441158        controller->state = 2
0044115e        play_voice_manager(0x751498, 0xe, var_24, var_20)
0044115e        esp_1 = &var_1c
004411ad        ecx = data_4df904
0044103c        if (state != 2)
004411ad        ecx = data_4df904
00441042        void* eax_2 = data_4df904
00441047        var_20 = 0.200000003f
0044104c        var_24 = 1
00441054        change_snail_skin(eax_2 + 0x434038, var_24, var_20)
00441059        var_20 = 1.40129846e-45f
0044105b        var_24 = 0xbada740e
00441062        apply_damage_gauge_delta(controller, var_24)
00441062        esp_1 = &var_20
00441067        controller->skin_hold_ticks = 5
0044106e        ecx = data_4df904
00441074        int16_t eax_3
00441074        eax_3.b = *(ecx + 0x4301bc)
0044107c        if (eax_3.b != 0)
0044107e        var_24 = 0
00441080        int32_t var_28_1 = 0xbbda740e
00441087        apply_damage_gauge_delta(controller, -0.00666666683f)
00441087        esp_1 = &var_24
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
004411c1        if ((eax:1.b & 0x41) != 0)
004411cd        long double x87_r7_14 = fconvert.t(controller->display_fill)
004411d0        long double temp2_1 = fconvert.t(0.00999999978f)
004411d0        x87_r7_14 - temp2_1
004411d6        eax.w = (x87_r7_14 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_14, temp2_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp2_1 ? 1 : 0) << 0xe
004411db        if ((eax:1.b & 1) == 0)
004411f6        esp_1[2] = fconvert.s(fconvert.t(351f) - fconvert.t(controller->display_fill) * fconvert.t(308f))
004411dd        esp_1[2] = 0x43c60000
004411c3        esp_1[2] = 0
004411fa        eax.b = *(ecx + 0x74621)
00441202        if (eax.b == 0)
0044120a        controller->pulse_progress = fconvert.s(fconvert.t(controller->pulse_step) + fconvert.t(controller->pulse_progress))
0044120d        long double x87_r7_20 = fconvert.t(controller->pulse_progress)
00441210        long double temp6 = fconvert.t(1f)
00441210        x87_r7_20 - temp6
00441216        eax.w = (x87_r7_20 < temp6 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_20, temp6) ? 1 : 0) << 0xa | (x87_r7_20 == temp6 ? 1 : 0) << 0xe
0044121b        if ((eax:1.b & 0x41) == 0)
00441226        controller->pulse_progress = fconvert.s(fconvert.t(controller->pulse_progress) - fconvert.t(1f))
00441229        long double x87_r7_23 = fconvert.t(controller->display_fill)
0044122c        long double temp8 = fconvert.t(0.899999976f)
0044122c        x87_r7_23 - temp8
00441232        eax.w = (x87_r7_23 < temp8 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_23, temp8) ? 1 : 0) << 0xa | (x87_r7_23 == temp8 ? 1 : 0) << 0xe
0044123c        if ((eax:1.b & 0x41) == 0 || controller->state != 0)
00441242        long double x87_r7_24 = fconvert.t(controller->display_fill)
00441245        long double temp10_1 = fconvert.t(0.899999976f)
00441245        x87_r7_24 - temp10_1
0044124b        eax.w = (x87_r7_24 < temp10_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_24, temp10_1) ? 1 : 0) << 0xa | (x87_r7_24 == temp10_1 ? 1 : 0) << 0xe
00441250        if ((eax:1.b & 0x41) != 0)
0044126c        long double x87_r7_28 = fconvert.t(controller->display_fill)
0044126f        long double temp12_1 = fconvert.t(0.100000001f)
0044126f        x87_r7_28 - temp12_1
00441275        eax.w = (x87_r7_28 < temp12_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_28, temp12_1) ? 1 : 0) << 0xa | (x87_r7_28 == temp12_1 ? 1 : 0) << 0xe
0044127a        if ((eax:1.b & 1) == 0)
0044128b        esp_1[1] = 0x3f800000
00441285        esp_1[1] = fconvert.s(fconvert.t(controller->display_fill) * fconvert.t(10f))
00441255        if (controller->state != 0)
0044128b        esp_1[1] = 0x3f800000
00441266        esp_1[1] = fconvert.s((fconvert.t(controller->display_fill) - fconvert.t(0.899999976f)) * fconvert.t(10f))
00441296        long double x87_r7_32 = fconvert.t(controller->pulse_progress) * fconvert.t(6.28318548f)
0044129c        *(esp_1 - 4) = ecx
0044129d        *(esp_1 - 4) = fconvert.s(x87_r7_32)
004412b2        long double x87_r7_35 = (sine() + fconvert.t(1f)) * fconvert.t(0.5f)
004412b8        *(esp_1 - 4) = 0
004412ba        *(esp_1 - 8) = 3
004412bc        *(esp_1 - 0xc) = 0x3f460000
004412c1        *(esp_1 - 0x10) = 0x3f800000
004412c6        long double x87_r7_36 = x87_r7_35 * fconvert.t(esp_1[1])
004412ca        *(esp_1 - 0x14) = 0
004412cc        *(esp_1 - 0x18) = 0
004412d8        esp_1[1] = fconvert.s(fconvert.t(esp_1[1]) - x87_r7_36 * fconvert.t(0.5f))
004412e0        *(esp_1 - 0x1c) = esp_1[1]
004412e1        *(esp_1 - 0x20) = 0x3f800000
004412e6        *(esp_1 - 0x24) = 0x3f800000
004412eb        *(esp_1 - 0x28) = 0x3f800000
004412f5        *(esp_1 - 0x1c) = set_color_rgba(&esp_1[3])
004412f6        *(esp_1 - 0x20) = 0x1000000
004412fb        *(esp_1 - 0x24) = 0x43c60000
00441300        *(esp_1 - 0x28) = 0x42800000
00441305        *(esp_1 - 0x2c) = 0x428c0000
0044130a        *(esp_1 - 0x30) = 0x440c0000
0044130f        *(esp_1 - 0x34) = 0x5b
00441311        queue_axis_aligned_textured_quad_uv()
0044131d        long double x87_r7_40 = fconvert.t(esp_1[2]) * fconvert.t(0.001953125f)
00441323        *(esp_1 - 4) = 0
00441325        *(esp_1 - 8) = 3
0044132b        esp_1[1] = fconvert.s(x87_r7_40)
0044132f        int32_t esi_2 = esp_1[1]
00441333        *(esp_1 - 0xc) = esi_2
00441334        *(esp_1 - 0x10) = 0x3f800000
00441339        *(esp_1 - 0x14) = 0
0044133b        *(esp_1 - 0x18) = 0
0044133d        *(esp_1 - 0x1c) = 0x3f800000
00441342        *(esp_1 - 0x20) = 0x3f800000
00441347        *(esp_1 - 0x24) = 0x3f800000
0044134c        *(esp_1 - 0x28) = 0x3f800000
00441356        *(esp_1 - 0x1c) = set_color_rgba(&esp_1[3])
00441357        int32_t eax_6 = esp_1[2]
0044135b        *(esp_1 - 0x20) = 0x1000000
00441360        *(esp_1 - 0x24) = eax_6
00441361        *(esp_1 - 0x28) = 0x42800000
00441366        *(esp_1 - 0x2c) = 0x428c0000
0044136b        *(esp_1 - 0x30) = 0x440c0000
00441370        *(esp_1 - 0x34) = 0x59
00441372        queue_axis_aligned_textured_quad_uv()
0044137e        *(esp_1 - 4) = 0
00441380        *(esp_1 - 8) = 3
00441382        *(esp_1 - 0xc) = 0x3f460000
00441387        *(esp_1 - 0x10) = 0x3f800000
0044138c        *(esp_1 - 0x14) = esi_2
0044138d        *(esp_1 - 0x18) = 0
0044138f        *(esp_1 - 0x1c) = 0x3f800000
00441394        *(esp_1 - 0x20) = 0x3f800000
00441399        *(esp_1 - 0x24) = 0x3f800000
0044139e        *(esp_1 - 0x28) = 0x3f800000
004413a3        int32_t eax_7
004413a3        int32_t ecx_12
004413a3        eax_7, ecx_12 = set_color_rgba(&esp_1[3])
004413ae        long double x87_r7_42 = fconvert.t(396f) - fconvert.t(esp_1[2])
004413b2        *(esp_1 - 0x1c) = eax_7
004413b3        *(esp_1 - 0x20) = 0x1000000
004413b8        *(esp_1 - 0x24) = ecx_12
004413b9        *(esp_1 - 0x24) = fconvert.s(x87_r7_42)
004413bc        long double x87_r7_43 = fconvert.t(esp_1[2])
004413c6        *(esp_1 - 0x28) = 0x42800000
004413cb        *(esp_1 - 0x2c) = ecx_12
004413cc        *(esp_1 - 0x2c) = fconvert.s(x87_r7_43 + fconvert.t(70f))
004413cf        *(esp_1 - 0x30) = 0x440c0000
004413d4        *(esp_1 - 0x34) = 0x5a
004413d6        int32_t result = queue_axis_aligned_textured_quad_uv()
004413de        *esp_1
004413e2        return result
