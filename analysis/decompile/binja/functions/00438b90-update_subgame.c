/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_subgame @ 0x438b90 */

00438b93        int32_t __saved_ebx_1
00438b93        int32_t __saved_ebx = __saved_ebx_1
00438b94        int32_t __saved_ebp_1
00438b94        int32_t __saved_ebp = __saved_ebp_1
00438b95        int32_t __saved_esi_1
00438b95        int32_t __saved_esi = __saved_esi_1
00438b96        int32_t __saved_edi_2
00438b96        int32_t __saved_edi_1 = __saved_edi_2
00438b96        int32_t __saved_edi
00438b96        int32_t* esp_1 = &__saved_edi
00438b97        char* game = arg1
00438b99        int16_t x87control = calc_subgame_rate(arg1)
00438b9e        int32_t eax = *(game + 0x3c)
00438ba4        float eax_25
00438ba4        if (eax u> 7)
004398fa        label_4398fa:
004398fa        eax_25 = update_subgame_camera(game)
004398ff        label_4398ff:
004398ff        *esp_1
004398ff        esp_1[1]
00439900        esp_1[2]
00439901        esp_1[3]
00439906        return eax_25
00438baf        switch (eax)
00438c44        case 0
00438c44        int32_t eax_5 = *(game + 0x1270fc8)
00438c4a        *(game + 0x3c) = 1
00438c4f        if (eax_5 == 1)
00438c4f        goto label_4398fa
00438c60        if (eax_5 == 0 || eax_5 == 3)
00438d6c        return build_subgame_level(game, *(game + 0x44))
00438c6d        if (game[0xff25d1] == 1)
00438c6f        void* eax_6 = *(game + 0xff25d4)
00438c75        game[0xff25d0] = 1
00438c8e        return build_subgame_level(game, *(eax_6 + 0x28))
00438c8f        game[0xff25d0] = 0
00438ca2        hide_star_field(data_4df904 + 0x4f33c)
00438c6d        goto label_438ca7
00438ca7        case 1
00438ca7        label_438ca7:
00438ca7        int32_t var_50_4 = 0
00438ca9        int32_t var_54_1 = 0x3f800000
00438cae        random_float_below(1f)
00438cb9        int32_t eax_8 = *(game + 0x40)
00438cbc        *(game + 0x28) = data_4df958
00438cc5        esp_1 = &__saved_edi
00438ccd        *(game + 0x2c) = data_4df960
00438cd0        if (eax_8 u> 7)
00438cd0        goto label_4398fa
00438cd6        int32_t eax_9
00438cd6        switch (eax_8)
00438ce3        case 0
00438ce3        eax_9 = update_galaxy(&game[0x1260020])
00438cea        if (eax_9 == 1)
00438cec        int32_t eax_10 = *(game + 0x44)
00438cef        *(game + 0x1270fc8) = 3
00438cf9        data_4df9bc = eax_10
00438d10        return build_subgame_level(game, *(game + 0x44))
00438d14        if (eax_9 == 2)
00438d16        int32_t edx_4 = *(game + 0x44)
00438d19        *(game + 0x1270fc8) = 1
00438d1f        data_4df9bc = edx_4
00438d37        return build_subgame_level(game, *(game + 0x44))
00438d9b        case 1
00438d9b        int32_t eax_17 = update_challenge_setup_screen(&game[0x125ffe0])
00438da2        if (eax_17 == 1)
00438da2        goto label_438da4
00438dc2        if (eax_17 != 3)
00438dc2        goto label_4398fa
00438dca        int32_t eax_19 = destroy_subgame(game)
00438dd8        *(data_4df904 + 0x1b8) = 2
00438de6        return eax_19
00438cd6        case 2, 3, 5, 6
00438cd6        goto label_4398fa
00438d3e        case 4
00438d3e        eax_9 = update_galaxy(&game[0x1260020])
00438d45        if (eax_9 == 1)
00438d47        int32_t edx_5 = *(game + 0x44)
00438d4a        *(game + 0x1270fc8) = 2
00438d54        data_4df9bc = edx_5
00438d6c        return build_subgame_level(game, *(game + 0x44))
00438da4        case 7
00438da4        label_438da4:
00438da4        int32_t var_50_8 = 0
00438da8        *(game + 0x1270fc8) = 2
00438dbe        return build_subgame_level(game, 0)
00438d70        if (eax_9 != 3)
00438d70        goto label_4398fa
00438d78        int32_t eax_16 = destroy_subgame(game)
00438d86        *(data_4df904 + 0x1b8) = 2
00438d94        return eax_16
00438de7        case 2
00438de7        eax.b = game[0xff25d0]
00438e09        if (eax.b == 1 && *(data_4df904 + 0x4f2e0) == 0)
00438e0e        int32_t var_50_9 = 0
00438e0f        int32_t var_54_2 = 1
00438e11        int32_t var_58_1 = 0x3f800000
00438e16        int32_t var_5c_1 = 0x3f800000
00438e1b        int32_t var_60_1 = 0
00438e1c        int32_t var_64_1 = 0
00438e1d        int32_t var_68_1 = 0x3ecccccd
00438e22        int32_t var_6c_1 = 0x3f800000
00438e29        int32_t var_70_1 = 0x3f800000
00438e2e        int32_t var_74_1 = 0x3f800000
00438e33        int32_t var_7c
00438e33        int32_t* var_68_2
00438e33        struct Color4f color_1[0x2]
00438e33        if (*(game + 0x40) != 3)
00438e63        var_68_2 = set_color_rgba(&color_1, 1f, 1f, 1f, 0.400000006f)
00438e3e        struct Color4f color
00438e3e        var_68_2 = set_color_rgba(&color, 1f, 1f, 1f, 0.400000006f)
00438e53        __builtin_memcpy(&var_7c, "\x00\x00\x11\x44\x00\x00\xc0\x40\x00\x00\x80\x42\x00\x00\x80\x42\x00\x00\x00\x01", 0x14)
00438e7d        int32_t var_80
00438e7d        __builtin_memcpy(&var_80, "\x1b\x00\x00\x00\x00\x00\x90\x43\x00\x00\x20\x41\x00\x00\x80\x42\x00\x00\x80\x42\x00\x00\x00\x01", 0x18)
00438e7f        int32_t var_78
00438e7f        queue_axis_aligned_textured_quad_uv(0x1b, var_7c, var_78, 64f, 64f, 0x1000000, var_68_2, 0, 0, 0x3f800000, 0x3f800000, 1, 0)
00438e84        esp_1 = &__saved_edi
00438e87        eax.b = game[0x3bbba4]
00438e9c        if (eax.b == 0 && *(game + 0x3bb884) != 2)
00438e9e        int32_t var_50_10 = 0x3f800000
00438ea9        x87control = advance_timer_counters(&game[0x3bba4c], 1f)
00438ea9        esp_1 = &__saved_edi
00438eb2        if (*(game + 0x40) == 7)
00438eba        x87control = update_tutorial(&game[0xa858])
00438ec5        update_slug_voice_manager(&game[0x35bb7c])
00438ece        if (game[8] == 1)
00438ed0        int32_t var_50_11 = 0
00438ed6        game[9] = 0
00438eda        game[8] = 0
00438ede        sub_44e540(&data_790f30, 0)
00438ede        esp_1 = &__saved_edi
00438ee3        int16_t eax_23
00438ee3        eax_23.b = game[0xff25d0]
00438ee9        void* ecx_26 = data_4df904
00438ef1        long double x87_r7_3
00438ef1        long double temp0_1
00438ef1        if (eax_23.b != 0)
00438ef3        x87_r7_3 = fconvert.t(*(game + 0xc))
00438ef6        temp0_1 = fconvert.t(0f)
00438ef6        x87_r7_3 - temp0_1
00438f0f        if (eax_23.b == 0 || (((x87_r7_3 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp0_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp0_1 ? 1 : 0) << 0xe):1.b & 0x40) == 0 || ((*(*(game + 0x3bbba0) + 4)).w:1.b & 0x40) == 0)
00438f15        eax_23.b = *(ecx_26 + 0x4f2e0)
00438f1d        if (eax_23.b == 0)
00438f3d        if ((read_pressed_text_input_key_code().b == 0xb || data_4b7654 == 1) && *(data_4df904 + 0x24) == 0)
00438f3f        game[9] = 1
00438f43        int32_t var_50_12 = 1
00438f4a        *(game + 0x3c) = 3
00438f4d        eax_25 = sub_44e540(&data_790f30, 1)
00438f4d        esp_1 = &__saved_edi
00438f58        if (*(game + 0x3bb884) == 2)
00438f70        return hide_border_init(*(game + 0x3bb888))
00438f58        goto label_4398ff
00438f71        long double x87_r7_4 = fconvert.t(*(game + 0xc))
00438f74        long double temp2_1 = fconvert.t(0f)
00438f74        x87_r7_4 - temp2_1
00438f7a        void* eax_24
00438f7a        eax_24.w = (x87_r7_4 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp2_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp2_1 ? 1 : 0) << 0xe
00438f7f        if ((eax_24:1.b & 0x41) == 0)
00438f84        long double x87_r7_6 = fconvert.t(*(game + 0x10)) + fconvert.t(*(game + 0xc))
00438f87        *(game + 0xc) = fconvert.s(x87_r7_6)
00438f8a        long double temp3_1 = fconvert.t(1f)
00438f8a        x87_r7_6 - temp3_1
00438f90        eax_24.w = (x87_r7_6 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp3_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp3_1 ? 1 : 0) << 0xe
00438f95        if ((eax_24:1.b & 0x41) == 0)
00438f97        *(game + 0xc) = 0
00438fa0        if (*(game + 0x3bb884) == 2)
00438fa8        unhide_border_init(*(game + 0x3bb888))
00438fb0        if (*game == 0)
00438fd7        int32_t edi_3 = *(game + 0x24)
00438fda        bool cond:3_1 = *(game + 0x40) != 2
00438fdc        *(game + 0x20) = edi_3
00438fdf        if (cond:3_1)
00438ff4        int32_t eax_29 = __ftol(x87control, fconvert.t(*(game + 0x3be0e4))) + 0x2e
00438ff9        if (eax_29 s> edi_3)
00438ffb        *(game + 0x24) = eax_29
00438fe4        *(game + 0x24) = *(game + 0x54)
00438fb2        int32_t eax_27 = *(game + 0x40)
00438fb5        *(game + 0x20) = 0
00438fba        if (eax_27 != 2)
00438ffb        *(game + 0x24) = __ftol(x87control, fconvert.t(*(game + 0x3be0e4))) + 0x2e
00438fbf        *(game + 0x24) = *(game + 0x54)
00439004        int32_t eax_33 = *(game + 0x58) + 0x14
00439009        if (*(game + 0x24) s> eax_33)
0043900b        *(game + 0x24) = eax_33
0043900e        int32_t ebp = *(game + 0x20)
00439016        if (ebp s< *(game + 0x24))
00439872        bool cond:6_1
00439027        int32_t ecx_31 = ebp * 0x3d
0043902b        int32_t eax_36
0043902b        eax_36.b = game[(ecx_31 << 2) + 0x5ccac8]
00439034        void* edi_4 = &game[ecx_31 << 2]
00439037        esp_1[6] = edi_4
0043903b        if ((eax_36.b & 2) != 0)
0043904c        if (((*(edi_4 + 0x5ccad0)).w:1.b & 2) == 0)
0043905d        void* edx_9 = data_4df904
00439069        void* edx_10 = *(edx_9 + 0x5ac)
00439071        if (edx_10 != 0)
0043907f        *(edx_10 + 8) = edi_4 + 0x5ccacc
00439082        void* edx_11 = *(edx_9 + 0x5ac)
00439087        *(*(edx_11 + 8) + 0xc) = edx_11
0043908e        void* edx_13 = *(*(edx_9 + 0x5ac) + 8)
00439091        *(edx_9 + 0x5ac) = edx_13
00439093        *(edx_13 + 8) = 0
00439073        *(edx_9 + 0x5ac) = edi_4 + 0x5ccacc
00439075        *(edi_4 + 0x5ccad4) = 0
0043907a        *(*(edx_9 + 0x5ac) + 0xc) = 0
00439099        int32_t eax_40
00439099        eax_40:1.b = (*(edi_4 + 0x5ccad0)):1.b | 2
0043909c        *(edi_4 + 0x5ccad0) = eax_40
0043904e        *(esp_1 - 4) = "List ADD"
00439053        report_errorf()
004390af        if ((*(edi_4 + 0x5ccac8) & 0x10) != 0 && (*(game + 0x4c) & 0x800000) != 0)
004390bd        *(esp_1 - 4) = &game[0x3bb764]
004390be        *(esp_1 - 8) = edi_4 + 0x5ccb58
004390c1        spawn_track_parcel(game)
004390c1        esp_1 -= 4
004390c6        esp_1[4] = 0
00439863        int32_t i
004390d5        if (ebp s>= 0 && ebp s< *(game + 0x54))
004390eb        void* edx_14 = (esp_1[4] + (ebp << 3)) * 0x15
004390f8        void* edi_6 = &game[edx_14 << 2]
004390fb        if (((*(game + (edx_14 << 2) + 0x3bfacc)).w:1.b & 2) == 0)
0043910a        if (((*(edi_6 + 0x3bfb08)).w:1.b & 0x40) != 0)
00439110        int16_t eax_45
00439110        eax_45.b = *(edi_6 + 0x3bfb04)
0043911c        if (eax_45.b == 0x1d || eax_45.b == 0x1e)
00439171        if (*(edi_6 + 0x3bfaec) != 0)
00439190        if ((0x200 & *(edi_6 + 0x3bfacc)) == 0)
004391a1        *(edi_6 + 0x3bfad0) = &game[0x355cb4]
004391a7        *(edi_6 + 0x3bfad4) = *(game + 0x355cc0)
004391aa        *(game + 0x355cc0) = edi_6 + 0x3bfac8
004391ad        void* ecx_39 = *(edi_6 + 0x3bfad4)
004391b2        if (ecx_39 != 0)
004391b4        *(ecx_39 + 8) = edi_6 + 0x3bfac8
004391b7        *(edi_6 + 0x3bfacc) |= 0x200
00439192        *(esp_1 - 4) = "List ADDafter"
00439197        report_errorf()
004391bc        int32_t eax_50 = ebp & 0x80000007
004391c1        if (eax_50 s< 0)
004391c7        eax_50 = ((eax_50 - 1) | 0xfffffff8) + 1
004391c8        void* ebx_5 = esp_1[6]
004391cc        esp_1[5] = eax_50
004391e6        *(edi_6 + 0x3bfae8) = fconvert.s(float.t(esp_1[5]) * fconvert.t(0.125f))
004391f2        if (((*(ebx_5 + 0x5ccb7c)).w:1.b & 2) == 0)
00439203        *(ebx_5 + 0x5ccb80) = &game[0x355b64]
00439209        *(ebx_5 + 0x5ccb84) = *(game + 0x355b70)
0043920c        *(game + 0x355b70) = ebx_5 + 0x5ccb78
0043920f        void* ecx_41 = *(ebx_5 + 0x5ccb84)
00439214        if (ecx_41 != 0)
00439216        *(ecx_41 + 8) = ebx_5 + 0x5ccb78
0043921c        int32_t ecx_42
0043921c        ecx_42:1.b = (*(ebx_5 + 0x5ccb7c)):1.b | 2
0043921f        *(ebx_5 + 0x5ccb7c) = ecx_42
004391f4        *(esp_1 - 4) = "List ADDafter"
004391f9        report_errorf()
00439230        *(ebx_5 + 0x5ccb88) = *(edi_6 + 0x3bfad8)
00439235        *(ebx_5 + 0x5ccb8c) = *(edi_6 + 0x3bfadc)
0043923b        *(ebx_5 + 0x5ccb90) = *(edi_6 + 0x3bfae0)
00439137        if ((0x200 & *(edi_6 + 0x3bfacc)) == 0)
0043914b        *(edi_6 + 0x3bfad0) = &game[0x355b9c]
00439151        *(edi_6 + 0x3bfad4) = *(game + 0x355ba8)
00439154        *(game + 0x355ba8) = edi_6 + 0x3bfac8
00439157        void* ecx_37 = *(edi_6 + 0x3bfad4)
0043915c        if (ecx_37 != 0)
0043915e        *(ecx_37 + 8) = edi_6 + 0x3bfac8
00439161        *(edi_6 + 0x3bfacc) |= 0x200
00439139        *(esp_1 - 4) = "List ADDafter"
0043913e        report_errorf()
0043924a        (**(edi_6 + 0x3bfac8))()
0043924c        int32_t* ebx_7 = edi_6 + 0x3bfb0c
00439252        esp_1[5] = 4
004392d9        int32_t j
0043925a        void* eax_56 = *ebx_7
0043925e        if (eax_56 != 0)
0043926c        if (((*(eax_56 + 4)).w:1.b & 2) == 0)
0043927d        *(eax_56 + 8) = &game[0x355b64]
00439283        *(eax_56 + 0xc) = *(game + 0x355b70)
00439286        *(game + 0x355b70) = eax_56
00439289        void* ecx_46 = *(eax_56 + 0xc)
0043928e        if (ecx_46 != 0)
00439290        *(ecx_46 + 8) = eax_56
00439296        int32_t ecx_47
00439296        ecx_47:1.b = (*(eax_56 + 4)):1.b | 2
00439299        *(eax_56 + 4) = ecx_47
0043926e        *(esp_1 - 4) = "List ADDafter"
00439273        report_errorf()
0043929c        int32_t ecx_48 = data_4df904
004392a6        *(esp_1 - 4) = &esp_1[0xf]
004392ad        int32_t* eax_58 = get_track_skirt_color(ecx_48 + 0x74618)
004392b6        int32_t* edx_22 = *ebx_7 + 0x28
004392b9        *edx_22 = *eax_58
004392be        edx_22[1] = eax_58[1]
004392c4        edx_22[2] = eax_58[2]
004392ca        edx_22[3] = eax_58[3]
004392cd        j = esp_1[5]
004392d1        ebx_7 = &ebx_7[1]
004392d5        esp_1[5] = j - 1
004392d9        do while (j != 1)
004392f8        void* eax_60
004392f8        char* ecx_35
004392f8        if (*(edi_6 + 0x3bfb04) == 0x17 && ((*(game + 0x4c)):1.b & 8) != 0 && ebp s>= *(game + 0x50) && ebp s< *(game + 0x58))
00439306        *(esp_1 - 4) = &game[0x3bb764]
00439307        *(esp_1 - 8) = edi_6 + 0x3bfac8
0043930a        eax_60, ecx_35 = spawn_track_health_pickup(game)
00439320        if (*(edi_6 + 0x3bfb04) == 0x18 && ebp s>= *(game + 0x50) && ebp s< *(game + 0x58))
0043932e        *(esp_1 - 4) = &game[0x3bb764]
0043932f        *(esp_1 - 8) = edi_6 + 0x3bfac8
00439348        if (*(edi_6 + 0x3bfb04) == 0x19 && ebp s>= *(game + 0x50) && ebp s< *(game + 0x58))
00439356        *(esp_1 - 4) = &game[0x3bb764]
00439357        *(esp_1 - 8) = edi_6 + 0x3bfac8
0043935a        eax_60, ecx_35 = spawn_track_jetpack_pickup(game)
0043935f        eax_60.b = *(edi_6 + 0x3bfb04)
00439367        if (eax_60.b == 0x21)
00439375        *(esp_1 - 4) = &game[0x3bb764]
00439376        *(esp_1 - 8) = edi_6 + 0x3bfac8
0043949f        eax_60, ecx_35 = spawn_track_garbage_hazard(game)
0043949f        esp_1 = esp_1
00439399        if ((*(edi_6 + 0x3bfb08) & 0x10) == 0 && (eax_60.b == 1 || eax_60.b == 0x15) && (game[0x4c] & 2) != 0)
0043939f        *(esp_1 - 4) = &data_4a4dbc
004393a4        *(esp_1 - 8) = 0x3f800000
004393a9        long double st0_2
004393a9        st0_2, eax_60, ecx_35 = random_float_below()
004393c3        long double x87_r6_4 = (fconvert.t(1f) - fconvert.t(*(game + 0x125ffd8))) * fconvert.t(0.200000003f) + fconvert.t(0.800000012f)
004393c9        x87_r6_4 - st0_2
004393cb        eax_60.w = (x87_r6_4 < st0_2 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_4, st0_2) ? 1 : 0) << 0xa | (x87_r6_4 == st0_2 ? 1 : 0) << 0xe
004393d0        if ((eax_60:1.b & 1) != 0)
004393d6        ecx_35 = esp_1[4]
004393dc        if (ecx_35 != 0)
004393de        eax_60.b = *(edi_6 + 0x3bfab0)
004393f2        if (ecx_35 == 0 || eax_60.b == 1 || eax_60.b == 0x14 || eax_60.b == 0x15 || eax_60.b == 0x20)
004393fb        if (ecx_35 != 7)
004393fd        eax_60.b = *(edi_6 + 0x3bfb58)
00439411        if ((ecx_35 == 7 || eax_60.b == 1 || eax_60.b == 0x14 || eax_60.b == 0x15 || eax_60.b == 0x20) && ebp s>= *(game + 0x50) && ebp s< *(game + 0x58) && *(game + 0x3bb884) != 2)
00439432        if (*(game + 0x40) == 4)
00439434        *(esp_1 - 4) = &data_4a4db8
00439439        *(esp_1 - 8) = 0x3f800000
0043943e        long double st0_3
0043943e        st0_3, eax_60, ecx_35 = random_float_below()
0043944f        long double x87_r6_7 = fconvert.t(*(game + 0x48)) * fconvert.t(0.300000012f) + fconvert.t(0.699999988f)
00439455        x87_r6_7 - st0_3
00439457        eax_60.w = (x87_r6_7 < st0_3 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_7, st0_3) ? 1 : 0) << 0xa | (x87_r6_7 == st0_3 ? 1 : 0) << 0xe
0043945c        if (*(game + 0x40) != 4 || (eax_60:1.b & 1) == 0)
00439463        if (*(game + 0x40) == 0)
00439465        *(esp_1 - 4) = &data_4a4db4
0043946a        *(esp_1 - 8) = 0x3f800000
0043946f        long double st0_4
0043946f        st0_4, eax_60, ecx_35 = random_float_below()
00439480        long double x87_r6_10 = fconvert.t(*(game + 0x48)) * fconvert.t(0.600000024f) + fconvert.t(0.400000006f)
00439486        x87_r6_10 - st0_4
00439488        eax_60.w = (x87_r6_10 < st0_4 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_10, st0_4) ? 1 : 0) << 0xa | (x87_r6_10 == st0_4 ? 1 : 0) << 0xe
0043948d        if (*(game + 0x40) != 0 || (eax_60:1.b & 1) == 0)
0043949b        *(esp_1 - 4) = &game[0x3bb764]
0043949c        *(esp_1 - 8) = edi_6 + 0x3bfac8
0043949f        eax_60, ecx_35 = spawn_track_garbage_hazard(game)
0043949f        esp_1 = esp_1
004394a4        eax_60.b = *(edi_6 + 0x3bfb04)
004394ac        if (eax_60.b != 0x22)
004394e6        if ((*(edi_6 + 0x3bfb08) & 8) == 0 && (eax_60.b == 1 || eax_60.b == 0xf) && *(game + 0x3bb884) != 2 && (*(game + 0x4c) & 0x10000) != 0)
004394e8        *(esp_1 - 4) = &data_4a4db0
004394ed        *(esp_1 - 8) = 0x3f800000
004394f2        long double st0_5
004394f2        st0_5, eax_60, ecx_35 = random_float_below()
0043950c        long double x87_r6_14 = (fconvert.t(1f) - fconvert.t(*(game + 0x125ffdc))) * fconvert.t(0.0199999996f) + fconvert.t(0.980000019f)
00439512        x87_r6_14 - st0_5
00439514        eax_60.w = (x87_r6_14 < st0_5 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_14, st0_5) ? 1 : 0) << 0xa | (x87_r6_14 == st0_5 ? 1 : 0) << 0xe
00439523        if ((eax_60:1.b & 1) != 0 && ebp s>= *(game + 0x50) && ebp s< *(game + 0x58))
0043952b        *(esp_1 - 4) = edi_6 + 0x3bfad8
00439532        eax_60, ecx_35 = spawn_salt_hazard(&game[0x3578c0])
00439532        esp_1 = esp_1
004394ba        if (ebp s>= *(game + 0x50) && ebp s< *(game + 0x58))
004394c2        *(esp_1 - 4) = edi_6 + 0x3bfad8
00439532        eax_60, ecx_35 = spawn_salt_hazard(&game[0x3578c0])
00439532        esp_1 = esp_1
0043954e        if ((game[0x4c] & 0x80) != 0 && *(edi_6 + 0x3bfb04) == 0x12 && ebp s>= *(game + 0x50) && ebp s< *(game + 0x58))
0043955c        *(esp_1 - 4) = &game[0x3bb764]
0043955d        *(esp_1 - 8) = edi_6 + 0x3bfac8
00439560        eax_60, ecx_35 = spawn_slug_hazard(game)
00439565        void* ebx_8 = esp_1[6]
00439569        int16_t edx_28 = (*(ebx_8 + 0x5ccac8)).w
00439572        if ((edx_28:1.b & 2) == 0)
00439578        ecx_35.b = *(edi_6 + 0x3bfb04)
00439581        void* esp_32
00439581        if (ecx_35.b != 0x23)
00439647        if (ecx_35.b == 2 || ecx_35.b == 3 || ecx_35.b == 4 || ecx_35.b == 5 || ecx_35.b == 6 || ecx_35.b == 7)
00439653        long double x87_r7_16 = fconvert.t(*(game + 0x3bbae0)) + fconvert.t(10f)
00439659        long double temp5_1 = fconvert.t(*(edi_6 + 0x3bfae0))
00439659        x87_r7_16 - temp5_1
0043965f        eax_60.w = (x87_r7_16 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_16, temp5_1) ? 1 : 0) << 0xa | (x87_r7_16 == temp5_1 ? 1 : 0) << 0xe
00439647        if ((ecx_35.b != 2 && ecx_35.b != 3 && ecx_35.b != 4 && ecx_35.b != 5 && ecx_35.b != 6 && ecx_35.b != 7) || (eax_60:1.b & 1) == 0 || ebp s>= *(game + 0x58))
004397c2        if (ecx_35.b == 8 || ecx_35.b == 9 || ecx_35.b == 0xa)
004397ce        long double x87_r7_21 = fconvert.t(*(game + 0x3bbae0)) + fconvert.t(10f)
004397d4        long double temp6_1 = fconvert.t(*(edi_6 + 0x3bfae0))
004397d4        x87_r7_21 - temp6_1
004397da        eax_60.w = (x87_r7_21 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_21, temp6_1) ? 1 : 0) << 0xa | (x87_r7_21 == temp6_1 ? 1 : 0) << 0xe
004397e4        if ((eax_60:1.b & 1) != 0 && ebp s< *(game + 0x58))
004397e9        void* esp_57
004397e9        if ((edx_28:1.b & 8) != 0)
004397ff        *(esp_1 - 4) = *(game + ((ebp + (ebp * 3 + 0x12414) * 0x14 + 0x615c) << 2))
004397ff        esp_57 = esp_1 - 4
0043983a        label_43983a:
0043983a        *(esp_57 - 4) = &game[0x3bb764]
0043983b        *(esp_57 - 8) = 2
0043983b        esp_32 = esp_57 - 8
0043983b        goto label_439843
00439802        *(esp_1 - 4) = &data_4a4da8
00439807        *(esp_1 - 8) = 0x3f800000
0043980c        long double st0_7 = random_float_below()
00439811        long double temp7_1 = fconvert.t(0.699999988f)
00439811        st0_7 - temp7_1
00439830        if ((((st0_7 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(st0_7, temp7_1) ? 1 : 0) << 0xa | (st0_7 == temp7_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0 || *(game + 0x40) == 7 || ((*(ebx_8 + 0x5ccac8)).w:1.b & 8) != 0)
00439832        *(esp_1 - 4) = 0
00439832        esp_57 = esp_1 - 4
00439832        goto label_43983a
00439676        if ((edx_28:1.b & 0x20) != 0)
00439698        *(esp_1 - 4) = *(game + ((ebp + (ebp * 3 + 0x12414) * 0x14 + 0x615c) << 2))
00439699        *(esp_1 - 8) = &game[0x3bb764]
0043969a        *(esp_1 - 0xc) = 8
0043969c        *(esp_1 - 0x10) = edi_6 + 0x3c0a88
0043969f        spawn_track_ring_or_special_effect(game)
00439851        *(game + 0x3bbae0) = *(edi_6 + 0x3c0aa0)
004396b2        if ((edx_28:1.b & 8) != 0)
004396d4        *(esp_1 - 4) = *(game + ((ebp + (ebp * 3 + 0x12414) * 0x14 + 0x615c) << 2))
004396d5        *(esp_1 - 8) = &game[0x3bb764]
004396d6        *(esp_1 - 0xc) = 6
004396d8        *(esp_1 - 0x10) = edi_6 + 0x3c0a88
004396db        spawn_track_ring_or_special_effect(game)
00439851        *(game + 0x3bbae0) = *(edi_6 + 0x3c0aa0)
004396ee        if ((edx_28:1.b & 0x10) != 0)
00439710        *(esp_1 - 4) = *(game + ((ebp + (ebp * 3 + 0x12414) * 0x14 + 0x615c) << 2))
00439711        *(esp_1 - 8) = &game[0x3bb764]
00439712        *(esp_1 - 0xc) = 7
00439714        *(esp_1 - 0x10) = edi_6 + 0x3c0a88
00439717        spawn_track_ring_or_special_effect(game)
00439851        *(game + 0x3bbae0) = *(edi_6 + 0x3c0aa0)
0043972b        if ((game[0x4c] & 8) != 0)
00439731        *(esp_1 - 4) = &data_4a4dac
00439736        *(esp_1 - 8) = 0x3f800000
0043973b        long double st0_6 = random_float_below()
00439740        long double temp8_1 = fconvert.t(0.699999988f)
00439740        st0_6 - temp8_1
00439754        if ((((st0_6 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(st0_6, temp8_1) ? 1 : 0) << 0xa | (st0_6 == temp8_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0 || *(game + 0x40) == 7)
0043975a        int16_t eax_86
0043975a        eax_86.b = *(edi_6 + 0x3bfb04)
00439772        if (eax_86.b != 5 && eax_86.b != 6 && eax_86.b != 7)
0043977e        *(esp_1 - 4) = 0
00439780        *(esp_1 - 8) = &game[0x3bb764]
00439787        *(esp_1 - 0xc) = 4
00439789        *(esp_1 - 0x10) = edi_6 + 0x3bfac8
0043978c        spawn_track_ring_or_special_effect(game)
00439798        if (*(game + 0x3bbb68) s< 0xa)
00439851        *(game + 0x3bbae0) = *(edi_6 + 0x3bfae0)
004397aa        *(game + 0x3bbae0) = fconvert.s(fconvert.t(*(edi_6 + 0x3bfae0)) + fconvert.t(35f))
0043958a        if ((edx_28:1.b & 4) == 0)
004395b2        if ((edx_28:1.b & 0x20) != 0)
004395ce        *(esp_1 - 4) = *(game + ((ebp + (ebp * 3 + 0x12414) * 0x14 + 0x615c) << 2))
004395cf        *(esp_1 - 8) = &game[0x3bb764]
004395d0        *(esp_1 - 0xc) = 8
004395d0        esp_32 = esp_1 - 0xc
004395d2        goto label_439843
004395da        if ((edx_28:1.b & 8) != 0)
004395f6        *(esp_1 - 4) = *(game + ((ebp + (ebp * 3 + 0x12414) * 0x14 + 0x615c) << 2))
004395f7        *(esp_1 - 8) = &game[0x3bb764]
004395f8        *(esp_1 - 0xc) = 6
004395f8        esp_32 = esp_1 - 0xc
004395fa        goto label_439843
00439602        if ((edx_28:1.b & 0x10) != 0)
00439622        *(esp_1 - 4) = *(game + ((ebp + (ebp * 3 + 0x12414) * 0x14 + 0x615c) << 2))
00439623        *(esp_1 - 8) = &game[0x3bb764]
00439624        *(esp_1 - 0xc) = 7
00439624        esp_32 = esp_1 - 0xc
00439626        goto label_439843
004395a6        *(esp_1 - 4) = *(game + ((ebp + (ebp * 3 + 0x12414) * 0x14 + 0x615c) << 2))
004395a7        *(esp_1 - 8) = &game[0x3bb764]
004395a8        *(esp_1 - 0xc) = 5
004395a8        esp_32 = esp_1 - 0xc
00439843        label_439843:
00439843        *(esp_32 - 4) = edi_6 + 0x3bfac8
00439846        spawn_track_ring_or_special_effect(game)
00439846        esp_1 = esp_32 + 0xc
00439851        *(game + 0x3bbae0) = *(edi_6 + 0x3bfae0)
0043985b        i = esp_1[4] + 1
0043985f        esp_1[4] = i
00439863        do while (i s< 8)
0043986c        ebp += 1
0043986d        cond:6_1 = ebp s< *(game + 0x24)
0043986f        *game = 0
00439872        do while (cond:6_1)
0043987b        sub_433b30(&game[0x5c])
00439884        if (*(game + 0x40) != 4)
00439927        *(*(game + 0x35bb88) + 0x2cc) = 0
00439934        int32_t ecx_91 = *(game + 0x35bb88)
0043993a        *(esp_1 - 4) = *(game + 0x3bba48)
0043993b        border_add_text_number(ecx_91)
00439940        int32_t eax_103 = *(game + 0x3bba48)
0043994e        if (eax_103 s> *(game + 0x355d94))
00439950        void* ecx_93 = *(game + 0x35bb8c)
00439956        *(game + 0x355d94) = eax_103
0043995c        *(ecx_93 + 0x2cc) = 0
00439969        int32_t ecx_94 = *(game + 0x35bb8c)
0043996f        *(esp_1 - 4) = *(game + 0x355d94)
00439970        border_add_text_number(ecx_94)
00439977        float eax_104 = update_subgame_camera(game)
0043997c        *esp_1
0043997c        esp_1[1]
0043997d        esp_1[2]
0043997e        esp_1[3]
00439983        return eax_104
00439896        *(esp_1 - 4) = &game[0x3bba4c]
00439899        format_time_trial_string()
0043989e        int32_t ecx_82 = *(game + 0x35bb88)
004398a4        *(esp_1 - 4) = 0x751478
004398ab        *(esp_1 - 8) = ecx_82 + 0x2cc
004398ac        sub_44e5b0()
004398ca        void* eax_99 = &game[*(game + 0x44) * 0x1fac0]
004398d3        if (*(eax_99 + 0x944150) != 1)
0043990d        hide_border_init(*(game + 0x35bb8c))
00439914        float eax_101 = update_subgame_camera(game)
00439919        *esp_1
00439919        esp_1[1]
0043991a        esp_1[2]
0043991b        esp_1[3]
00439920        return eax_101
004398dc        *(esp_1 - 4) = eax_99 + 0x944158
004398dd        format_time_trial_string()
004398e2        int32_t ecx_86 = *(game + 0x35bb8c)
004398e8        *(esp_1 - 4) = 0x751478
004398ef        *(esp_1 - 8) = ecx_86 + 0x2cc
004398f0        sub_44e5b0()
00438fb0        goto label_4398fa
00439984        eax_23.b = game[0xff25d1]
0043998c        if (eax_23.b == 0)
004399b2        *(ecx_26 + 0x1bc) = *(ecx_26 + 0x1b8)
004399bd        *(data_4df904 i+ 0x1b8) = 0x1b
00439994        *(ecx_26 + 0x1bc) = *(ecx_26 + 0x1b8)
004399a0        *(data_4df904 + 0x1b8) = 0x1a
004399c7        void* ecx_97 = data_4df904
004399cd        long double x87_r7_23 = fconvert.t(*(ecx_97 + 0x4f2e4))
004399d3        long double temp1_1 = fconvert.t(1f)
004399d3        x87_r7_23 - temp1_1
004399d9        eax_25.w = (x87_r7_23 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_23, temp1_1) ? 1 : 0) << 0xa | (x87_r7_23 == temp1_1 ? 1 : 0) << 0xe
004399de        if ((eax_25:1.b & 0x41) == 0)
004399de        goto label_4398ff
004399e7        *(ecx_97 + 0x4f2e0) = 0
004399f2        return eax_25
00438bb6        case 3
00438bb6        *(game + 0x3c) = 4
00438bbd        game[9] = 1
00438bc7        *(game + 0xc) = *(game + 0x10)
00438bca        initialize_pause_menu(&game[0x14])
00438bde        return update_pause_menu(&game[0x14])
00438bde        case 4
00438bde        return update_pause_menu(&game[0x14])
00438baf        case 5, 6
00438baf        goto label_4398fa
00438bdf        case 7
00438bdf        eax.b = game[0xff25d1]
00438bec        if (eax.b != 1)
00438c19        int32_t var_50_2 = 0
00438c1d        game[0xff25d0] = 0
00438c24        int32_t eax_4
00438c24        void* esi_1
00438c24        int32_t edi_2
00438c24        eax_4, esi_1, edi_2 = build_subgame_level(game, 0)
00438c29        *(esi_1 + 0x3c) = 2
00438c36        *(data_4df904 + 0x56c) = edi_2
00438c43        return eax_4
00438bee        int32_t var_50_1 = 0
00438bf2        game[0xff25d0] = 1
00438bf9        int32_t eax_3
00438bf9        void* esi
00438bf9        int32_t edi_1
00438bf9        eax_3, esi, edi_1 = build_subgame_level(game, 0)
00438bfe        *(esi + 0x3c) = 2
00438c0b        *(data_4df904 + 0x56c) = edi_1
00438c18        return eax_3
