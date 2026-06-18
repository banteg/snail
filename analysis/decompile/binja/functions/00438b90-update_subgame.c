/* tool: binary_ninja */
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
00438b99        int16_t x87control = calc_subgame_rate(game)
00438b9e        int32_t subgame_state = game->subgame_state
00438ba4        if (subgame_state u> 7)
004398fa        label_4398fa:
004398fa        update_subgame_camera(game)
004398ff        label_4398ff:
004398ff        *esp_1
004398ff        esp_1[1]
00439900        esp_1[2]
00439901        esp_1[3]
00439906        return 
00438baf        switch (subgame_state)
00438c44        case 0
00438c44        int32_t subgame_rebuild_selector = game->subgame_rebuild_selector
00438c4a        game->subgame_state = 1
00438c4f        if (subgame_rebuild_selector == 1)
00438c4f        goto label_4398fa
00438c60        if (subgame_rebuild_selector == 0 || subgame_rebuild_selector == 3)
00438d60        build_subgame_level(game, game->level_mode_arg)
00438d6c        return 
00438c6d        if (game->selected_level_record_persistent != 1)
00438c8f        game->selected_level_record_active = 0
00438ca2        hide_star_field(g_game_base + 0x4f33c)
00438c6d        goto label_438ca7
00438c6f        struct SelectedLevelRecord* selected_level_record = game->selected_level_record
00438c75        game->selected_level_record_active = 1
00438c82        build_subgame_level(game, selected_level_record->replay_level_index)
00438c8e        return 
00438ca7        case 1
00438ca7        label_438ca7:
00438ca7        int32_t var_50_4 = 0
00438ca9        int32_t var_54_1 = 0x3f800000
00438cae        random_float_below(1f)
00438cb3        int32_t ecx_9 = data_4df958
00438cb9        int32_t level_mode = game->level_mode
00438cbc        game->_pad_00[0x28] = ecx_9.b
00438cbc        game->_pad_00[0x29] = ecx_9:1.b
00438cbc        game->_pad_00[0x2a] = ecx_9:2.b
00438cbc        game->_pad_00[0x2b] = ecx_9:3.b
00438cbf        int32_t edx_3 = data_4df960
00438cc5        esp_1 = &__saved_edi
00438ccd        game->_pad_00[0x2c] = edx_3.b
00438ccd        game->_pad_00[0x2d] = edx_3:1.b
00438ccd        game->_pad_00[0x2e] = edx_3:2.b
00438ccd        game->_pad_00[0x2f] = edx_3:3.b
00438cd0        if (level_mode u> 7)
00438cd0        goto label_4398fa
00438cd6        int32_t eax_2
00438cd6        switch (level_mode)
00438ce3        case 0
00438ce3        eax_2 = update_galaxy(&game->__offset(0x1260020).d)
00438cea        if (eax_2 == 1)
00438cec        int32_t level_mode_arg = game->level_mode_arg
00438cef        game->subgame_rebuild_selector = 3
00438cf9        data_4df9bc = level_mode_arg
00438d04        build_subgame_level(game, game->level_mode_arg)
00438d10        return 
00438d14        if (eax_2 == 2)
00438d16        int32_t level_mode_arg_1 = game->level_mode_arg
00438d19        game->subgame_rebuild_selector = 1
00438d1f        data_4df9bc = level_mode_arg_1
00438d2b        build_subgame_level(game, game->level_mode_arg)
00438d37        return 
00438d9b        case 1
00438d9b        int32_t eax_5 = update_challenge_setup_screen(&game->__offset(0x125ffe0).d)
00438da2        if (eax_5 == 1)
00438da2        goto label_438da4
00438dc2        if (eax_5 != 3)
00438dc2        goto label_4398fa
00438dca        destroy_subgame(game)
00438dd8        *(g_game_base + 0x1b8) = 2
00438de6        return 
00438cd6        case 2, 3, 5, 6
00438cd6        goto label_4398fa
00438d3e        case 4
00438d3e        eax_2 = update_galaxy(&game->__offset(0x1260020).d)
00438d45        if (eax_2 == 1)
00438d47        int32_t level_mode_arg_2 = game->level_mode_arg
00438d4a        game->subgame_rebuild_selector = 2
00438d54        data_4df9bc = level_mode_arg_2
00438d60        build_subgame_level(game, game->level_mode_arg)
00438d6c        return 
00438da4        case 7
00438da4        label_438da4:
00438da4        int32_t var_50_8 = 0
00438da8        game->subgame_rebuild_selector = 2
00438db2        build_subgame_level(game, 0)
00438dbe        return 
00438d70        if (eax_2 != 3)
00438d70        goto label_4398fa
00438d78        destroy_subgame(game)
00438d86        *(g_game_base + 0x1b8) = 2
00438d94        return 
00438e09        case 2
00438e09        if (game->selected_level_record_active == 1 && *(g_game_base + 0x4f2e0) == 0)
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
00438e33        struct Color4f* var_68_2
00438e33        struct Color4f color_1[0x2]
00438e33        if (game->level_mode != 3)
00438e63        var_68_2 = set_color_rgba(&color_1, 1f, 1f, 1f, 0.400000006f)
00438e3e        struct Color4f color
00438e3e        var_68_2 = set_color_rgba(&color, 1f, 1f, 1f, 0.400000006f)
00438e53        __builtin_memcpy(&var_7c, "\x00\x00\x11\x44\x00\x00\xc0\x40\x00\x00\x80\x42\x00\x00\x80\x42\x00\x00\x00\x01", 0x14)
00438e7d        int32_t var_80
00438e7d        __builtin_memcpy(&var_80, "\x1b\x00\x00\x00\x00\x00\x90\x43\x00\x00\x20\x41\x00\x00\x80\x42\x00\x00\x80\x42\x00\x00\x00\x01", 0x18)
00438e7f        int32_t var_78
00438e7f        queue_axis_aligned_textured_quad_uv(0x1b, var_7c, var_78, 64f, 64f, 0x1000000, var_68_2, 0, 0, 0x3f800000, 0x3f800000, 1, 0)
00438e84        esp_1 = &__saved_edi
00438e9c        if (game->__offset(0x3bbba4).b == 0 && game->__offset(0x3bb884).d != 2)
00438e9e        int32_t var_50_10 = 0x3f800000
00438ea9        x87control = advance_timer_counters(&game->stopwatch, 1f)
00438ea9        esp_1 = &__saved_edi
00438eb2        if (game->level_mode == 7)
00438eba        x87control = update_tutorial(&game->tutorial)
00438ec5        update_slug_voice_manager(&game->__offset(0x35bb7c).d)
00438ece        if (game->_pad_00[8] == 1)
00438ed0        int32_t var_50_11 = 0
00438ed6        game->_pad_00[9] = 0
00438eda        game->_pad_00[8] = 0
00438ede        set_sprite_manager_paused(&g_sprite_manager, 0)
00438ede        esp_1 = &__saved_edi
00438ee3        int16_t eax_12
00438ee3        eax_12.b = game->selected_level_record_active
00438ee9        void* game_base_1 = g_game_base
00438ef1        if (eax_12.b == 0)
00438f15        label_438f15:
00438f15        eax_12.b = *(game_base_1 + 0x4f2e0)
00438f1d        if (eax_12.b == 0)
00438f3d        if ((read_pressed_text_input_key_code().b == 0xb || g_window_deactivated == 1) && *(g_game_base + 0x24) == 0)
00438f3f        game->_pad_00[9] = 1
00438f43        int32_t var_50_12 = 1
00438f4a        game->subgame_state = 3
00438f4d        set_sprite_manager_paused(&g_sprite_manager, 1)
00438f4d        esp_1 = &__saved_edi
00438f58        if (game->__offset(0x3bb884).d != 2)
00438f58        goto label_4398ff
00438f64        hide_border_init(game->__offset(0x3bb888).d)
00438f70        return 
00438f71        long double x87_r7_4 = fconvert.t(game->_pad_00[0xc].d)
00438f74        long double temp2_1 = fconvert.t(0f)
00438f74        x87_r7_4 - temp2_1
00438f7f        if ((((x87_r7_4 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp2_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00438f84        long double x87_r7_6 = fconvert.t(game->_pad_00[0x10].d) + fconvert.t(game->_pad_00[0xc].d)
00438f87        game->_pad_00[0xc].d = fconvert.s(x87_r7_6)
00438f8a        long double temp3_1 = fconvert.t(1f)
00438f8a        x87_r7_6 - temp3_1
00438f95        if ((((x87_r7_6 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp3_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp3_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00438f97        game->_pad_00[0xc] = 0
00438f97        game->_pad_00[0xd] = 0
00438f97        game->_pad_00[0xe] = 0
00438f97        game->_pad_00[0xf] = 0
00438fa0        if (game->__offset(0x3bb884).d == 2)
00438fa8        unhide_border_init(game->__offset(0x3bb888).d)
00438fb0        int32_t eax_17
00438fb0        if (game->_pad_00[0] == 0)
00438fd7        int32_t edi
00438fd7        edi.b = game->_pad_00[0x24]
00438fd7        edi:1.b = game->_pad_00[0x25]
00438fd7        edi:2.b = game->_pad_00[0x26]
00438fd7        edi:3.b = game->_pad_00[0x27]
00438fda        bool cond:3_1 = game->level_mode != 2
00438fdc        game->_pad_00[0x20] = edi.b
00438fdc        game->_pad_00[0x21] = edi:1.b
00438fdc        game->_pad_00[0x22] = edi:2.b
00438fdc        game->_pad_00[0x23] = edi:3.b
00438fdf        if (cond:3_1)
00438ff4        eax_17 = __ftol(x87control, fconvert.t(game->__offset(0x3be0e4).d)) + 0x2e
00438ff9        if (eax_17 s> edi)
00438ff9        goto label_438ffb
00438fe1        int32_t runtime_row_count_1 = game->runtime_row_count
00438fe4        game->_pad_00[0x24] = runtime_row_count_1.b
00438fe4        game->_pad_00[0x25] = runtime_row_count_1:1.b
00438fe4        game->_pad_00[0x26] = runtime_row_count_1:2.b
00438fe4        game->_pad_00[0x27] = runtime_row_count_1:3.b
00438fb2        int32_t level_mode_1 = game->level_mode
00438fb5        game->_pad_00[0x20] = 0
00438fb5        game->_pad_00[0x21] = 0
00438fb5        game->_pad_00[0x22] = 0
00438fb5        game->_pad_00[0x23] = 0
00438fba        if (level_mode_1 != 2)
00438fcf        eax_17 = __ftol(x87control, fconvert.t(game->__offset(0x3be0e4).d)) + 0x2e
00438ffb        label_438ffb:
00438ffb        game->_pad_00[0x24] = eax_17.b
00438ffb        game->_pad_00[0x25] = eax_17:1.b
00438ffb        game->_pad_00[0x26] = eax_17:2.b
00438ffb        game->_pad_00[0x27] = eax_17:3.b
00438fbc        int32_t runtime_row_count = game->runtime_row_count
00438fbf        game->_pad_00[0x24] = runtime_row_count.b
00438fbf        game->_pad_00[0x25] = runtime_row_count:1.b
00438fbf        game->_pad_00[0x26] = runtime_row_count:2.b
00438fbf        game->_pad_00[0x27] = runtime_row_count:3.b
00439001        int32_t ecx_29
00439001        ecx_29.b = game->_pad_00[0x24]
00439001        ecx_29:1.b = game->_pad_00[0x25]
00439001        ecx_29:2.b = game->_pad_00[0x26]
00439001        ecx_29:3.b = game->_pad_00[0x27]
00439004        int32_t eax_21 = game->completion_row_start + 0x14
00439009        if (ecx_29 s> eax_21)
0043900b        game->_pad_00[0x24] = eax_21.b
0043900b        game->_pad_00[0x25] = eax_21:1.b
0043900b        game->_pad_00[0x26] = eax_21:2.b
0043900b        game->_pad_00[0x27] = eax_21:3.b
0043900e        int32_t ebp
0043900e        ebp.b = game->_pad_00[0x20]
0043900e        ebp:1.b = game->_pad_00[0x21]
0043900e        ebp:2.b = game->_pad_00[0x22]
0043900e        ebp:3.b = game->_pad_00[0x23]
00439011        int32_t eax_22
00439011        eax_22.b = game->_pad_00[0x24]
00439011        eax_22:1.b = game->_pad_00[0x25]
00439011        eax_22:2.b = game->_pad_00[0x26]
00439011        eax_22:3.b = game->_pad_00[0x27]
00439016        if (ebp s< eax_22)
00439872        int32_t eax_97
00439027        int32_t ecx_30 = ebp * 0x3d
00439032        bool cond:4_1 = (game->_pad_00[(ecx_30 << 2) + 0x5ccac8] & 2) == 0
00439034        void* edi_1 = &game->_pad_00[ecx_30 << 2]
00439037        esp_1[6] = edi_1
0043903b        if (not(cond:4_1))
0043904c        if (((*(edi_1 + 0x5ccad0)).w:1.b & 2) == 0)
0043905d        void* game_base_4 = g_game_base
00439069        void* edx_6 = *(game_base_4 + 0x5ac)
00439071        if (edx_6 != 0)
0043907f        *(edx_6 + 8) = edi_1 + 0x5ccacc
00439082        void* edx_7 = *(game_base_4 + 0x5ac)
00439087        *(*(edx_7 + 8) + 0xc) = edx_7
0043908e        void* edx_9 = *(*(game_base_4 + 0x5ac) + 8)
00439091        *(game_base_4 + 0x5ac) = edx_9
00439093        *(edx_9 + 8) = 0
00439073        *(game_base_4 + 0x5ac) = edi_1 + 0x5ccacc
00439075        *(edi_1 + 0x5ccad4) = 0
00439075        *(edi_1 + 0x5ccad5) = 0
00439075        *(edi_1 + 0x5ccad6) = 0
00439075        *(edi_1 + 0x5ccad7) = 0
0043907a        *(*(game_base_4 + 0x5ac) + 0xc) = 0
00439096        int32_t eax_29
00439096        eax_29.b = *(edi_1 + 0x5ccad0)
00439096        eax_29:1.b = *(edi_1 + 0x5ccad1)
00439096        eax_29:2.b = *(edi_1 + 0x5ccad2)
00439096        eax_29:3.b = *(edi_1 + 0x5ccad3)
00439099        eax_29:1.b |= 2
0043909c        *(edi_1 + 0x5ccad0) = eax_29.b
0043909c        *(edi_1 + 0x5ccad1) = eax_29:1.b
0043909c        *(edi_1 + 0x5ccad2) = eax_29:2.b
0043909c        *(edi_1 + 0x5ccad3) = eax_29:3.b
0043904e        *(esp_1 - 4) = "List ADD"
00439053        report_errorf()
004390af        if ((*(edi_1 + 0x5ccac8) & 0x10) != 0 && (game->runtime_flags & &data_800000) != 0)
004390bd        *(esp_1 - 4) = &game->__offset(0x3bb764).d
004390be        *(esp_1 - 8) = edi_1 + 0x5ccb58
004390c1        spawn_track_parcel(game)
004390c1        esp_1 -= 4
004390c6        esp_1[4] = 0
00439863        int32_t i
004390d5        if (ebp s>= 0 && ebp s< game->runtime_row_count)
004390eb        void* edx_10 = (esp_1[4] + (ebp << 3)) * 0x15
004390f8        void* edi_3 = &game->_pad_00[edx_10 << 2]
004390fb        if (((*(game + (edx_10 << 2) + 0x3bfacc)).w:1.b & 2) == 0)
0043910a        if (((*(edi_3 + 0x3bfb08)).w:1.b & 0x40) != 0)
00439110        char eax_35 = *(edi_3 + 0x3bfb04)
0043911c        if (eax_35 == 0x1d || eax_35 == 0x1e)
00439171        if (*(edi_3 + 0x3bfaec) != 0)
00439190        if ((0x200 & *(edi_3 + 0x3bfacc)) == 0)
004391a1        *(edi_3 + 0x3bfad0) = &game->__offset(0x355cb4).d
004391a4        int32_t ebx_4
004391a4        ebx_4.b = game->__offset(0x355cc0).b
004391a4        ebx_4:1.b = game->__offset(0x355cc1).b
004391a4        ebx_4:2.b = game->__offset(0x355cc2).b
004391a4        ebx_4:3.b = game->__offset(0x355cc3).b
004391a7        *(edi_3 + 0x3bfad4) = ebx_4
004391aa        game->__offset(0x355cc0).b = (edi_3 + 0x3bfac8).b
004391aa        game->__offset(0x355cc1).b = (edi_3 + 0x3bfac8):1.b
004391aa        game->__offset(0x355cc2).b = (edi_3 + 0x3bfac8):2.b
004391aa        game->__offset(0x355cc3).b = (edi_3 + 0x3bfac8):3.b
004391ad        void* ecx_38 = *(edi_3 + 0x3bfad4)
004391b2        if (ecx_38 != 0)
004391b4        *(ecx_38 + 8) = (edi_3 + 0x3bfac8).b
004391b4        *(ecx_38 + 9) = (edi_3 + 0x3bfac8):1.b
004391b4        *(ecx_38 + 0xa) = (edi_3 + 0x3bfac8):2.b
004391b4        *(ecx_38 + 0xb) = (edi_3 + 0x3bfac8):3.b
004391b7        *(edi_3 + 0x3bfacc) |= 0x200
00439192        *(esp_1 - 4) = "List ADDafter"
00439197        report_errorf()
004391bc        int32_t eax_40 = ebp & 0x80000007
004391c1        if (eax_40 s< 0)
004391c7        eax_40 = ((eax_40 - 1) | 0xfffffff8) + 1
004391c8        void* ebx_5 = esp_1[6]
004391cc        esp_1[5] = eax_40
004391e6        *(edi_3 + 0x3bfae8) = fconvert.s(float.t(esp_1[5]) * fconvert.t(0.125f))
004391f2        if (((*(ebx_5 + 0x5ccb7c)).w:1.b & 2) == 0)
00439203        *(ebx_5 + 0x5ccb80) = &game->__offset(0x355b64).d
00439206        int32_t edx_12
00439206        edx_12.b = game->__offset(0x355b70).b
00439206        edx_12:1.b = game->__offset(0x355b71).b
00439206        edx_12:2.b = game->__offset(0x355b72).b
00439206        edx_12:3.b = game->__offset(0x355b73).b
00439209        *(ebx_5 + 0x5ccb84) = edx_12
0043920c        game->__offset(0x355b70).b = (ebx_5 + 0x5ccb78).b
0043920c        game->__offset(0x355b71).b = (ebx_5 + 0x5ccb78):1.b
0043920c        game->__offset(0x355b72).b = (ebx_5 + 0x5ccb78):2.b
0043920c        game->__offset(0x355b73).b = (ebx_5 + 0x5ccb78):3.b
0043920f        void* ecx_40 = *(ebx_5 + 0x5ccb84)
00439214        if (ecx_40 != 0)
00439216        *(ecx_40 + 8) = (ebx_5 + 0x5ccb78).b
00439216        *(ecx_40 + 9) = (ebx_5 + 0x5ccb78):1.b
00439216        *(ecx_40 + 0xa) = (ebx_5 + 0x5ccb78):2.b
00439216        *(ecx_40 + 0xb) = (ebx_5 + 0x5ccb78):3.b
00439219        int32_t ecx_41 = *(ebx_5 + 0x5ccb7c)
0043921c        ecx_41:1.b |= 2
0043921f        *(ebx_5 + 0x5ccb7c) = ecx_41
004391f4        *(esp_1 - 4) = "List ADDafter"
004391f9        report_errorf()
00439230        *(ebx_5 + 0x5ccb88) = *(edi_3 + 0x3bfad8)
00439235        *(ebx_5 + 0x5ccb8c) = *(edi_3 + 0x3bfadc)
0043923b        *(ebx_5 + 0x5ccb90) = *(edi_3 + 0x3bfae0)
00439137        if ((0x200 & *(edi_3 + 0x3bfacc)) == 0)
0043914b        *(edi_3 + 0x3bfad0) = &game->__offset(0x355b9c).d
0043914e        int32_t ebx_2
0043914e        ebx_2.b = game->__offset(0x355ba8).b
0043914e        ebx_2:1.b = game->__offset(0x355ba9).b
0043914e        ebx_2:2.b = game->__offset(0x355baa).b
0043914e        ebx_2:3.b = game->__offset(0x355bab).b
00439151        *(edi_3 + 0x3bfad4) = ebx_2
00439154        game->__offset(0x355ba8).b = (edi_3 + 0x3bfac8).b
00439154        game->__offset(0x355ba9).b = (edi_3 + 0x3bfac8):1.b
00439154        game->__offset(0x355baa).b = (edi_3 + 0x3bfac8):2.b
00439154        game->__offset(0x355bab).b = (edi_3 + 0x3bfac8):3.b
00439157        void* ecx_36 = *(edi_3 + 0x3bfad4)
0043915c        if (ecx_36 != 0)
0043915e        *(ecx_36 + 8) = (edi_3 + 0x3bfac8).b
0043915e        *(ecx_36 + 9) = (edi_3 + 0x3bfac8):1.b
0043915e        *(ecx_36 + 0xa) = (edi_3 + 0x3bfac8):2.b
0043915e        *(ecx_36 + 0xb) = (edi_3 + 0x3bfac8):3.b
00439161        *(edi_3 + 0x3bfacc) |= 0x200
00439139        *(esp_1 - 4) = "List ADDafter"
0043913e        report_errorf()
0043924a        (**(edi_3 + 0x3bfac8))()
0043924c        int32_t* ebx_7 = edi_3 + 0x3bfb0c
00439252        esp_1[5] = 4
004392d9        int32_t j
0043925a        void* eax_46 = *ebx_7
0043925e        if (eax_46 != 0)
0043926c        if (((*(eax_46 + 4)).w:1.b & 2) == 0)
0043927d        *(eax_46 + 8) = &game->__offset(0x355b64).d
00439280        int32_t edx_16
00439280        edx_16.b = game->__offset(0x355b70).b
00439280        edx_16:1.b = game->__offset(0x355b71).b
00439280        edx_16:2.b = game->__offset(0x355b72).b
00439280        edx_16:3.b = game->__offset(0x355b73).b
00439283        *(eax_46 + 0xc) = edx_16
00439286        game->__offset(0x355b70).b = eax_46.b
00439286        game->__offset(0x355b71).b = eax_46:1.b
00439286        game->__offset(0x355b72).b = eax_46:2.b
00439286        game->__offset(0x355b73).b = eax_46:3.b
00439289        void* ecx_45 = *(eax_46 + 0xc)
0043928e        if (ecx_45 != 0)
00439290        *(ecx_45 + 8) = eax_46.b
00439290        *(ecx_45 + 9) = eax_46:1.b
00439290        *(ecx_45 + 0xa) = eax_46:2.b
00439290        *(ecx_45 + 0xb) = eax_46:3.b
00439293        int32_t ecx_46 = *(eax_46 + 4)
00439296        ecx_46:1.b |= 2
00439299        *(eax_46 + 4) = ecx_46
0043926e        *(esp_1 - 4) = "List ADDafter"
00439273        report_errorf()
0043929c        int32_t game_base_2 = g_game_base
004392a6        *(esp_1 - 4) = &esp_1[0xf]
004392ad        int32_t* eax_48 = get_track_skirt_color(game_base_2 + 0x74618)
004392b6        int32_t* edx_18 = *ebx_7 + 0x28
004392b9        *edx_18 = *eax_48
004392be        edx_18[1] = eax_48[1]
004392c4        edx_18[2] = eax_48[2]
004392ca        edx_18[3] = eax_48[3]
004392cd        j = esp_1[5]
004392d1        ebx_7 = &ebx_7[1]
004392d5        esp_1[5] = j - 1
004392d9        do while (j != 1)
004392f8        if (*(edi_3 + 0x3bfb04) == 0x17 && (game->runtime_flags:1.b & 8) != 0 && ebp s>= game->first_block_row_count && ebp s< game->completion_row_start)
00439306        *(esp_1 - 4) = &game->__offset(0x3bb764).d
00439307        *(esp_1 - 8) = edi_3 + 0x3bfac8
0043930a        spawn_track_health_pickup(game)
00439320        if (*(edi_3 + 0x3bfb04) == 0x18 && ebp s>= game->first_block_row_count && ebp s< game->completion_row_start)
0043932e        *(esp_1 - 4) = &game->__offset(0x3bb764).d
0043932f        *(esp_1 - 8) = edi_3 + 0x3bfac8
00439348        if (*(edi_3 + 0x3bfb04) == 0x19 && ebp s>= game->first_block_row_count && ebp s< game->completion_row_start)
00439356        *(esp_1 - 4) = &game->__offset(0x3bb764).d
00439357        *(esp_1 - 8) = edi_3 + 0x3bfac8
0043935a        spawn_track_jetpack_pickup(game)
0043935f        char eax_52 = *(edi_3 + 0x3bfb04)
00439367        if (eax_52 == 0x21)
00439375        *(esp_1 - 4) = &game->__offset(0x3bb764).d
00439376        *(esp_1 - 8) = edi_3 + 0x3bfac8
0043949f        spawn_track_garbage_hazard(game)
0043949f        esp_1 = esp_1
00439399        if ((*(edi_3 + 0x3bfb08) & 0x10) == 0 && (eax_52 == 1 || eax_52 == 0x15) && (game->runtime_flags.b & 2) != 0)
0043939f        *(esp_1 - 4) = &data_4a4dbc
004393a4        *(esp_1 - 8) = 0x3f800000
004393a9        long double st0_2 = random_float_below()
004393c3        long double x87_r6_4 = (fconvert.t(1f) - fconvert.t(game->__offset(0x125ffd8).d)) * fconvert.t(0.200000003f) + fconvert.t(0.800000012f)
004393c9        x87_r6_4 - st0_2
004393cb        int16_t eax_54 = (x87_r6_4 < st0_2 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_4, st0_2) ? 1 : 0) << 0xa | (x87_r6_4 == st0_2 ? 1 : 0) << 0xe
004393d0        if ((eax_54:1.b & 1) != 0)
004393d6        struct Game* ecx_34 = esp_1[4]
004393dc        if (ecx_34 != 0)
004393de        eax_54.b = *(edi_3 + 0x3bfab0)
004393f2        if (ecx_34 == 0 || eax_54.b == 1 || eax_54.b == 0x14 || eax_54.b == 0x15 || eax_54.b == 0x20)
004393fb        if (ecx_34 != 7)
004393fd        eax_54.b = *(edi_3 + 0x3bfb58)
00439411        if ((ecx_34 == 7 || eax_54.b == 1 || eax_54.b == 0x14 || eax_54.b == 0x15 || eax_54.b == 0x20) && ebp s>= game->first_block_row_count && ebp s< game->completion_row_start && game->__offset(0x3bb884).d != 2)
00439432        long double st0_3
00439432        long double x87_r6_7
00439432        if (game->level_mode == 4)
00439434        *(esp_1 - 4) = &data_4a4db8
00439439        *(esp_1 - 8) = 0x3f800000
0043943e        st0_3 = random_float_below()
0043944f        x87_r6_7 = fconvert.t(game->base_subgame_rate) * fconvert.t(0.300000012f) + fconvert.t(0.699999988f)
00439455        x87_r6_7 - st0_3
0043945c        if (game->level_mode != 4 || (((x87_r6_7 < st0_3 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_7, st0_3) ? 1 : 0) << 0xa | (x87_r6_7 == st0_3 ? 1 : 0) << 0xe):1.b & 1) == 0)
00439463        long double st0_4
00439463        long double x87_r6_10
00439463        if (game->level_mode == 0)
00439465        *(esp_1 - 4) = &data_4a4db4
0043946a        *(esp_1 - 8) = 0x3f800000
0043946f        st0_4 = random_float_below()
00439480        x87_r6_10 = fconvert.t(game->base_subgame_rate) * fconvert.t(0.600000024f) + fconvert.t(0.400000006f)
00439486        x87_r6_10 - st0_4
0043948d        if (game->level_mode != 0 || (((x87_r6_10 < st0_4 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_10, st0_4) ? 1 : 0) << 0xa | (x87_r6_10 == st0_4 ? 1 : 0) << 0xe):1.b & 1) == 0)
0043949b        *(esp_1 - 4) = &game->__offset(0x3bb764).d
0043949c        *(esp_1 - 8) = edi_3 + 0x3bfac8
0043949f        spawn_track_garbage_hazard(game)
0043949f        esp_1 = esp_1
004394a4        char eax_61 = *(edi_3 + 0x3bfb04)
004394ac        if (eax_61 != 0x22)
004394e6        if ((*(edi_3 + 0x3bfb08) & 8) == 0 && (eax_61 == 1 || eax_61 == 0xf) && game->__offset(0x3bb884).d != 2 && (game->runtime_flags & 0x10000) != 0)
004394e8        *(esp_1 - 4) = &data_4a4db0
004394ed        *(esp_1 - 8) = 0x3f800000
004394f2        long double st0_5 = random_float_below()
0043950c        long double x87_r6_14 = (fconvert.t(1f) - fconvert.t(game->__offset(0x125ffdc).d)) * fconvert.t(0.0199999996f) + fconvert.t(0.980000019f)
00439512        x87_r6_14 - st0_5
00439523        if ((((x87_r6_14 < st0_5 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_14, st0_5) ? 1 : 0) << 0xa | (x87_r6_14 == st0_5 ? 1 : 0) << 0xe):1.b & 1) != 0 && ebp s>= game->first_block_row_count && ebp s< game->completion_row_start)
0043952b        *(esp_1 - 4) = edi_3 + 0x3bfad8
00439532        spawn_salt_hazard(&game->salt_pool)
00439532        esp_1 = &esp_1[2]
004394ba        if (ebp s>= game->first_block_row_count && ebp s< game->completion_row_start)
004394c2        *(esp_1 - 4) = edi_3 + 0x3bfad8
00439532        spawn_salt_hazard(&game->salt_pool)
00439532        esp_1 = &esp_1[2]
0043954e        if ((game->runtime_flags.b & 0x80) != 0 && *(edi_3 + 0x3bfb04) == 0x12 && ebp s>= game->first_block_row_count && ebp s< game->completion_row_start)
0043955c        *(esp_1 - 4) = &game->__offset(0x3bb764).d
0043955d        *(esp_1 - 8) = edi_3 + 0x3bfac8
00439560        spawn_slug_hazard(game)
00439565        void* ebx_8 = esp_1[6]
00439569        int16_t edx_24 = (*(ebx_8 + 0x5ccac8)).w
00439572        if ((edx_24:1.b & 2) == 0)
00439578        char ecx_60 = *(edi_3 + 0x3bfb04)
00439581        void* esp_32
00439581        if (ecx_60 != 0x23)
00439647        long double x87_r7_16
00439647        long double temp5_1
00439647        if (ecx_60 == 2 || ecx_60 == 3 || ecx_60 == 4 || ecx_60 == 5 || ecx_60 == 6 || ecx_60 == 7)
00439653        x87_r7_16 = fconvert.t(game->__offset(0x3bbae0).d) + fconvert.t(10f)
00439659        temp5_1 = fconvert.t(*(edi_3 + 0x3bfae0))
00439659        x87_r7_16 - temp5_1
00439647        if ((ecx_60 != 2 && ecx_60 != 3 && ecx_60 != 4 && ecx_60 != 5 && ecx_60 != 6 && ecx_60 != 7) || (((x87_r7_16 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_16, temp5_1) ? 1 : 0) << 0xa | (x87_r7_16 == temp5_1 ? 1 : 0) << 0xe):1.b & 1) == 0 || ebp s>= game->completion_row_start)
004397c2        if (ecx_60 == 8 || ecx_60 == 9 || ecx_60 == 0xa)
004397ce        long double x87_r7_21 = fconvert.t(game->__offset(0x3bbae0).d) + fconvert.t(10f)
004397d4        long double temp6_1 = fconvert.t(*(edi_3 + 0x3bfae0))
004397d4        x87_r7_21 - temp6_1
004397e4        if ((((x87_r7_21 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_21, temp6_1) ? 1 : 0) << 0xa | (x87_r7_21 == temp6_1 ? 1 : 0) << 0xe):1.b & 1) != 0 && ebp s< game->completion_row_start)
004397e9        void* esp_57
004397e9        if ((edx_24:1.b & 8) != 0)
004397ff        *(esp_1 - 4) = *(game + ((ebp + (ebp * 3 + 0x12414) * 0x14 + 0x615c) << 2))
004397ff        esp_57 = esp_1 - 4
0043983a        label_43983a:
0043983a        *(esp_57 - 4) = &game->__offset(0x3bb764).d
0043983b        *(esp_57 - 8) = 2
0043983b        esp_32 = esp_57 - 8
0043983b        goto label_439843
00439802        *(esp_1 - 4) = &data_4a4da8
00439807        *(esp_1 - 8) = 0x3f800000
0043980c        long double st0_7 = random_float_below()
00439811        long double temp7_1 = fconvert.t(0.699999988f)
00439811        st0_7 - temp7_1
00439830        if ((((st0_7 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(st0_7, temp7_1) ? 1 : 0) << 0xa | (st0_7 == temp7_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0 || game->level_mode == 7 || ((*(ebx_8 + 0x5ccac8)).w:1.b & 8) != 0)
00439832        *(esp_1 - 4) = 0
00439832        esp_57 = esp_1 - 4
00439832        goto label_43983a
00439676        if ((edx_24:1.b & 0x20) != 0)
00439698        *(esp_1 - 4) = *(game + ((ebp + (ebp * 3 + 0x12414) * 0x14 + 0x615c) << 2))
00439699        *(esp_1 - 8) = &game->__offset(0x3bb764).d
0043969a        *(esp_1 - 0xc) = 8
0043969c        *(esp_1 - 0x10) = edi_3 + 0x3c0a88
0043969f        spawn_track_ring_or_special_effect(game)
00439851        game->__offset(0x3bbae0).d = *(edi_3 + 0x3c0aa0)
004396b2        if ((edx_24:1.b & 8) != 0)
004396d4        *(esp_1 - 4) = *(game + ((ebp + (ebp * 3 + 0x12414) * 0x14 + 0x615c) << 2))
004396d5        *(esp_1 - 8) = &game->__offset(0x3bb764).d
004396d6        *(esp_1 - 0xc) = 6
004396d8        *(esp_1 - 0x10) = edi_3 + 0x3c0a88
004396db        spawn_track_ring_or_special_effect(game)
00439851        game->__offset(0x3bbae0).d = *(edi_3 + 0x3c0aa0)
004396ee        if ((edx_24:1.b & 0x10) != 0)
00439710        *(esp_1 - 4) = *(game + ((ebp + (ebp * 3 + 0x12414) * 0x14 + 0x615c) << 2))
00439711        *(esp_1 - 8) = &game->__offset(0x3bb764).d
00439712        *(esp_1 - 0xc) = 7
00439714        *(esp_1 - 0x10) = edi_3 + 0x3c0a88
00439717        spawn_track_ring_or_special_effect(game)
00439851        game->__offset(0x3bbae0).d = *(edi_3 + 0x3c0aa0)
0043972b        if ((game->runtime_flags.b & 8) != 0)
00439731        *(esp_1 - 4) = &data_4a4dac
00439736        *(esp_1 - 8) = 0x3f800000
0043973b        long double st0_6 = random_float_below()
00439740        long double temp8_1 = fconvert.t(0.699999988f)
00439740        st0_6 - temp8_1
00439749        int16_t eax_88 = (st0_6 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(st0_6, temp8_1) ? 1 : 0) << 0xa | (st0_6 == temp8_1 ? 1 : 0) << 0xe
00439754        if ((eax_88:1.b & 0x41) == 0 || game->level_mode == 7)
0043975a        eax_88.b = *(edi_3 + 0x3bfb04)
00439772        if (eax_88.b != 5 && eax_88.b != 6 && eax_88.b != 7)
0043977e        *(esp_1 - 4) = 0
00439780        *(esp_1 - 8) = &game->__offset(0x3bb764).d
00439787        *(esp_1 - 0xc) = 4
00439789        *(esp_1 - 0x10) = edi_3 + 0x3bfac8
0043978c        spawn_track_ring_or_special_effect(game)
00439798        if (game->__offset(0x3bbb68).d s< 0xa)
00439851        game->__offset(0x3bbae0).d = *(edi_3 + 0x3bfae0)
004397aa        game->__offset(0x3bbae0).d = fconvert.s(fconvert.t(*(edi_3 + 0x3bfae0)) + fconvert.t(35f))
0043958a        if ((edx_24:1.b & 4) == 0)
004395b2        if ((edx_24:1.b & 0x20) != 0)
004395ce        *(esp_1 - 4) = *(game + ((ebp + (ebp * 3 + 0x12414) * 0x14 + 0x615c) << 2))
004395cf        *(esp_1 - 8) = &game->__offset(0x3bb764).d
004395d0        *(esp_1 - 0xc) = 8
004395d0        esp_32 = esp_1 - 0xc
004395d2        goto label_439843
004395da        if ((edx_24:1.b & 8) != 0)
004395f6        *(esp_1 - 4) = *(game + ((ebp + (ebp * 3 + 0x12414) * 0x14 + 0x615c) << 2))
004395f7        *(esp_1 - 8) = &game->__offset(0x3bb764).d
004395f8        *(esp_1 - 0xc) = 6
004395f8        esp_32 = esp_1 - 0xc
004395fa        goto label_439843
00439602        if ((edx_24:1.b & 0x10) != 0)
00439622        *(esp_1 - 4) = *(game + ((ebp + (ebp * 3 + 0x12414) * 0x14 + 0x615c) << 2))
00439623        *(esp_1 - 8) = &game->__offset(0x3bb764).d
00439624        *(esp_1 - 0xc) = 7
00439624        esp_32 = esp_1 - 0xc
00439626        goto label_439843
004395a6        *(esp_1 - 4) = *(game + ((ebp + (ebp * 3 + 0x12414) * 0x14 + 0x615c) << 2))
004395a7        *(esp_1 - 8) = &game->__offset(0x3bb764).d
004395a8        *(esp_1 - 0xc) = 5
004395a8        esp_32 = esp_1 - 0xc
00439843        label_439843:
00439843        *(esp_32 - 4) = edi_3 + 0x3bfac8
00439846        spawn_track_ring_or_special_effect(game)
00439846        esp_1 = esp_32 + 0xc
00439851        game->__offset(0x3bbae0).d = *(edi_3 + 0x3bfae0)
0043985b        i = esp_1[4] + 1
0043985f        esp_1[4] = i
00439863        do while (i s< 8)
00439869        eax_97.b = game->_pad_00[0x24]
00439869        eax_97:1.b = game->_pad_00[0x25]
00439869        eax_97:2.b = game->_pad_00[0x26]
00439869        eax_97:3.b = game->_pad_00[0x27]
0043986c        ebp += 1
0043986f        game->_pad_00[0] = 0
00439872        do while (ebp s< eax_97)
0043987b        update_track_render_cache_rows(&game->__offset(0x5c).d)
00439884        if (game->level_mode != 4)
00439927        *(game->__offset(0x35bb88).d + 0x2cc) = 0
00439934        int32_t ecx_90 = game->__offset(0x35bb88).d
0043993a        *(esp_1 - 4) = game->__offset(0x3bba48).d
0043993b        border_add_text_number(ecx_90)
00439940        int32_t eax_105 = game->__offset(0x3bba48).d
0043994e        if (eax_105 s> game->__offset(0x355d94).d)
00439950        void* ecx_92 = game->__offset(0x35bb8c).d
00439956        game->__offset(0x355d94).d = eax_105
0043995c        *(ecx_92 + 0x2cc) = 0
00439969        int32_t ecx_93 = game->__offset(0x35bb8c).d
0043996f        *(esp_1 - 4) = game->__offset(0x355d94).d
00439970        border_add_text_number(ecx_93)
00439977        update_subgame_camera(game)
0043997c        *esp_1
0043997c        esp_1[1]
0043997d        esp_1[2]
0043997e        esp_1[3]
00439983        return 
0043988a        &game->_pad_ff25e0
00439896        *(esp_1 - 4) = &game->stopwatch
00439899        format_time_trial_string()
0043989e        int32_t ecx_81 = game->__offset(0x35bb88).d
004398a4        *(esp_1 - 4) = 0x751478
004398ab        *(esp_1 - 8) = ecx_81 + 0x2cc
004398ac        rstrcpy_checked_ascii()
004398ca        void* eax_102 = &game->_pad_00[game->level_mode_arg * 0x1fac0]
004398d3        if (*(eax_102 + 0x944150) != 1)
0043990d        hide_border_init(game->__offset(0x35bb8c).d)
00439914        update_subgame_camera(game)
00439919        *esp_1
00439919        esp_1[1]
0043991a        esp_1[2]
0043991b        esp_1[3]
00439920        return 
004398dc        *(esp_1 - 4) = eax_102 + 0x944158
004398dd        format_time_trial_string()
004398e2        int32_t ecx_85 = game->__offset(0x35bb8c).d
004398e8        *(esp_1 - 4) = 0x751478
004398ef        *(esp_1 - 8) = ecx_85 + 0x2cc
004398f0        rstrcpy_checked_ascii()
00438fb0        goto label_4398fa
00438ef3        long double x87_r7_3 = fconvert.t(game->_pad_00[0xc].d)
00438ef6        long double temp0_1 = fconvert.t(0f)
00438ef6        x87_r7_3 - temp0_1
00438efc        eax_12 = (x87_r7_3 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp0_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp0_1 ? 1 : 0) << 0xe
00438f0f        if ((eax_12:1.b & 0x40) == 0 || ((*(game->__offset(0x3bbba0).d + 4)).w:1.b & 0x40) == 0)
00438f01        goto label_438f15
00439984        eax_12.b = game->selected_level_record_persistent
0043998c        if (eax_12.b == 0)
004399b2        *(game_base_1 + 0x1bc) = *(game_base_1 + 0x1b8)
004399bd        *(g_game_base + 0x1b8) = 0x1b
00439994        *(game_base_1 + 0x1bc) = *(game_base_1 + 0x1b8)
004399a0        *(g_game_base + 0x1b8) = 0x1a
004399c7        void* game_base_3 = g_game_base
004399cd        long double x87_r7_23 = fconvert.t(*(game_base_3 + 0x4f2e4))
004399d3        long double temp1_1 = fconvert.t(1f)
004399d3        x87_r7_23 - temp1_1
004399de        if ((((x87_r7_23 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_23, temp1_1) ? 1 : 0) << 0xa | (x87_r7_23 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
004399de        goto label_4398ff
004399e7        *(game_base_3 + 0x4f2e0) = 0
004399f2        return 
00438bb6        case 3
00438bb6        game->subgame_state = 4
00438bbd        game->_pad_00[9] = 1
00438bc1        int32_t eax
00438bc1        eax.b = game->_pad_00[0x10]
00438bc1        eax:1.b = game->_pad_00[0x11]
00438bc1        eax:2.b = game->_pad_00[0x12]
00438bc1        eax:3.b = game->_pad_00[0x13]
00438bc7        game->_pad_00[0xc] = eax.b
00438bc7        game->_pad_00[0xd] = eax:1.b
00438bc7        game->_pad_00[0xe] = eax:2.b
00438bc7        game->_pad_00[0xf] = eax:3.b
00438bca        initialize_pause_menu(&game->_pad_00[0x14])
00438bd2        update_pause_menu(&game->_pad_00[0x14])
00438bde        return 
00438bd2        case 4
00438bd2        update_pause_menu(&game->_pad_00[0x14])
00438bde        return 
00438baf        case 5, 6
00438baf        goto label_4398fa
00438bec        case 7
00438bec        if (game->selected_level_record_persistent != 1)
00438c19        int32_t var_50_2 = 0
00438c1d        game->selected_level_record_active = 0
00438c24        build_subgame_level(game, 0)
00438c29        game->subgame_state = 2
00438c36        *(g_game_base + 0x56c) = 1
00438c43        return 
00438bee        int32_t var_50_1 = 0
00438bf2        game->selected_level_record_active = 1
00438bf9        build_subgame_level(game, 0)
00438bfe        game->subgame_state = 2
00438c0b        *(g_game_base + 0x56c) = 1
00438c18        return
