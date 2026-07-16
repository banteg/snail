/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_subgame @ 0x438b90 */

00438b99        int16_t x87control = calc_subgame_rate(game)
00438b9e        int32_t subgame_state = game->subgame_state
00438ba4        if (subgame_state u> 7)
004398fa        update_subgame_camera(game)
00439906        return
00438baf        switch (subgame_state)
00438c44        case 0
00438c44        int32_t subgame_rebuild_selector = game->subgame_rebuild_selector
00438c4a        game->subgame_state = 1
00438c4f        if (subgame_rebuild_selector == 1)
004398fa        update_subgame_camera(game)
00439906        return
00438c60        if (subgame_rebuild_selector == 0 || subgame_rebuild_selector == 3)
00438d60        build_subgame_level(game, game->level_mode_arg)
00438d6c        return
00438c6d        if (game->selected_level_record_persistent != 1)
00438c8f        game->selected_level_record_active = 0
00438ca2        hide_star_field(&g_game_base->star_manager)
00438c6d        goto label_438ca7
00438c6f        struct SubSolution* selected_level_record = game->selected_level_record
00438c75        game->selected_level_record_active = 1
00438c82        build_subgame_level(game, selected_level_record->replay_level_index)
00438c8e        return
00438ca7        case 1
00438ca7        label_438ca7:
00438ca7        int32_t var_50_2 = 0
00438cae        random_float_below(1f)
00438cb9        int32_t level_mode = game->level_mode
00438cbc        game->completion_bonus_x_source = g_runtime_config.completion_bonus_x_source
00438ccd        game->completion_bonus_y_source = g_runtime_config.completion_bonus_y_source
00438cd0        if (level_mode u> 7)
004398fa        update_subgame_camera(game)
00439906        return
00438cd6        int32_t eax_2
00438cd6        switch (level_mode)
00438ce3        case 0
00438ce3        eax_2 = update_galaxy(&game->galaxy)
00438cea        if (eax_2 == 1)
00438cec        int32_t level_mode_arg = game->level_mode_arg
00438cef        game->subgame_rebuild_selector = 3
00438cf9        g_runtime_config.landscape_backdrop_variant_selector = level_mode_arg
00438d04        build_subgame_level(game, game->level_mode_arg)
00438d10        return
00438d14        if (eax_2 == 2)
00438d16        int32_t level_mode_arg_1 = game->level_mode_arg
00438d19        game->subgame_rebuild_selector = 1
00438d1f        g_runtime_config.landscape_backdrop_variant_selector = level_mode_arg_1
00438d2b        build_subgame_level(game, game->level_mode_arg)
00438d37        return
00438d9b        case 1
00438d9b        int32_t eax_5 = update_challenge_setup_screen(&game->gui)
00438da2        if (eax_5 == 1)
00438da2        goto label_438da8
00438dc2        if (eax_5 != 3)
004398fa        update_subgame_camera(game)
00439906        return
00438dca        destroy_subgame(game)
00438dd8        g_game_base->players[0].frontend_state = 2
00438de6        return
004398fa        case 2, 3, 5, 6
004398fa        update_subgame_camera(game)
00439906        return
00438d3e        case 4
00438d3e        eax_2 = update_galaxy(&game->galaxy)
00438d45        if (eax_2 == 1)
00438d47        int32_t level_mode_arg_2 = game->level_mode_arg
00438d4a        game->subgame_rebuild_selector = 2
00438d54        g_runtime_config.landscape_backdrop_variant_selector = level_mode_arg_2
00438d60        build_subgame_level(game, game->level_mode_arg)
00438d6c        return
00438da8        case 7
00438da8        label_438da8:
00438da8        game->subgame_rebuild_selector = 2
00438db2        build_subgame_level(game, 0)
00438dbe        return
00438d70        if (eax_2 != 3)
004398fa        update_subgame_camera(game)
00439906        return
00438d78        destroy_subgame(game)
00438d86        g_game_base->players[0].frontend_state = 2
00438d94        return
00438e09        case 2
00438e09        if (game->selected_level_record_active == 1 && g_game_base->intro.hide_for_replay_latch == 0)
00438e33        float x
00438e33        struct tColour* color
00438e33        if (game->level_mode != 3)
00438e63        struct tColour color_2
00438e63        color = set_color_rgba(&color_2, 1f, 1f, 1f, 0.400000006f)
00438e78        __builtin_memcpy(&x, "\x00\x00\x90\x43\x00\x00\x20\x41\x00\x00\x80\x42\x00\x00\x80\x42\x00\x00\x00\x01", 0x14)
00438e3e        struct tColour color_1
00438e3e        color = set_color_rgba(&color_1, 1f, 1f, 1f, 0.400000006f)
00438e53        __builtin_memcpy(&x, "\x00\x00\x11\x44\x00\x00\xc0\x40\x00\x00\x80\x42\x00\x00\x80\x42\x00\x00\x00\x01", 0x14)
00438e7f        float y
00438e7f        queue_axis_aligned_textured_quad_uv(0x1b, x, y, 64f, 64f, 0x1000000, color, 0f, 0f, 1f, 1f, 1, 0f)
00438e9c        if (game->player.completion_handoff_active == 0 && game->player.click_start.state != CLICK_START_STATE_WAITING_FOR_START)
00438ea9        x87control = advance_timer_counters(&game->player.stopwatch, 1f)
00438eb2        if (game->level_mode == 7)
00438eba        x87control = update_tutorial(&game->tutorial)
00438ec5        update_slug_voice_manager(&game->slug_voice_manager)
00438ece        if (game->resume_requested == 1)
00438ed6        game->subgame_pause_gate = 0
00438eda        game->resume_requested = 0
00438ede        set_sprite_manager_paused(&g_sprite_manager, 0)
00438ee3        int16_t eax_12
00438ee3        eax_12.b = game->selected_level_record_active
00438ee9        struct GameRoot* game_base_1 = g_game_base
00438ef1        if (eax_12.b == 0)
00438f15        label_438f15:
00438f15        eax_12.b = game_base_1->intro.hide_for_replay_latch
00438f1d        if (eax_12.b == 0)
00438f3d        if ((read_pressed_text_input_key_code().b == 0xb || g_window_deactivated == 1) && g_game_base->fade.state == 0)
00438f3f        game->subgame_pause_gate = 1
00438f4a        game->subgame_state = 3
00438f4d        set_sprite_manager_paused(&g_sprite_manager, 1)
00438f58        if (game->player.click_start.state != CLICK_START_STATE_WAITING_FOR_START)
00439906        return
00438f64        hide_border_init(game->player.click_start.prompt)
00438f70        return
00438f71        long double x87_r7_4 = fconvert.t(game->pause_fade)
00438f74        long double temp2_1 = fconvert.t(0f)
00438f74        x87_r7_4 - temp2_1
00438f7f        if ((((x87_r7_4 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp2_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00438f84        long double x87_r7_6 = fconvert.t(game->pause_fade_step) + fconvert.t(game->pause_fade)
00438f87        game->pause_fade = fconvert.s(x87_r7_6)
00438f8a        long double temp3_1 = fconvert.t(1f)
00438f8a        x87_r7_6 - temp3_1
00438f95        if ((((x87_r7_6 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp3_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp3_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00438f97        game->pause_fade = 0f
00438fa0        if (game->player.click_start.state == CLICK_START_STATE_WAITING_FOR_START)
00438fa8        unhide_border_init(game->player.click_start.prompt)
00438fb0        if (game->scan_reset == 0)
00438fd7        int32_t runtime_row_scan_end = game->runtime_row_scan_end
00438fda        bool cond:3_1 = game->level_mode != 2
00438fdc        game->runtime_row_scan_begin = runtime_row_scan_end
00438fdf        if (cond:3_1)
00438ff4        int32_t eax_17 = ftol(x87control, fconvert.t(game->player.interaction_max_z)) + 0x2e
00438ff9        if (eax_17 s> runtime_row_scan_end)
00438ffb        game->runtime_row_scan_end = eax_17
00438fe4        game->runtime_row_scan_end = game->runtime_row_count
00438fb2        int32_t level_mode_1 = game->level_mode
00438fb5        game->runtime_row_scan_begin = 0
00438fba        if (level_mode_1 != 2)
00438ffb        game->runtime_row_scan_end = ftol(x87control, fconvert.t(game->player.interaction_max_z)) + 0x2e
00438fbf        game->runtime_row_scan_end = game->runtime_row_count
00439004        int32_t eax_21 = game->completion_row_start + 0x14
00439009        if (game->runtime_row_scan_end s> eax_21)
0043900b        game->runtime_row_scan_end = eax_21
0043900e        int32_t runtime_row_scan_begin = game->runtime_row_scan_begin
00439016        if (runtime_row_scan_begin s< game->runtime_row_scan_end)
00439872        bool cond:6_1
00439027        int32_t ecx_31 = runtime_row_scan_begin * 0x3d
00439034        void* edi_1 = game + (ecx_31 << 2)
0043903b        if ((*(&game->runtime_rows + (ecx_31 << 2)) & 2) != 0)
0043904c        if (((*(edi_1 + 0x5ccad0)).w:1.b & 2) == 0)
0043905d        struct GameRoot* game_base_3 = g_game_base
00439069        struct FrameBodBase* first = game_base_3->active_bod_list.first
00439071        if (first != 0)
0043907f        first->bod.list_prev = edi_1 + 0x5ccacc
00439082        void* first_1 = game_base_3->active_bod_list.first
00439087        *(*(first_1 + 8) + 0xc) = first_1
0043908e        void* list_prev = game_base_3->active_bod_list.first->bod.list_prev
00439091        game_base_3->active_bod_list.first = list_prev
00439093        *(list_prev + 8) = 0
00439073        game_base_3->active_bod_list.first = edi_1 + 0x5ccacc
00439075        (edi_1 + 0x5ccacc)->bod.list_prev.b = nullptr
00439075        (edi_1 + 0x5ccacc)->bod.list_prev:1.b = 0
0043907a        game_base_3->active_bod_list.first->bod.list_next = 0
00439096        uint32_t list_flags = (edi_1 + 0x5ccacc)->bod.list_flags
00439099        list_flags:1.b |= 2
0043909c        (edi_1 + 0x5ccacc)->bod.list_flags = list_flags
00439053        report_errorf("List ADD")
004390af        if ((*(edi_1 + &data_5ccac8) & 0x10) != 0 && (game->runtime_flags & &data_800000) != 0)
004390c1        spawn_track_parcel(game, edi_1 + &data_5ccb58, &game->player)
004390c6        float var_3c_1 = 0f
00439863        bool cond:5_1
004390d5        if (runtime_row_scan_begin s>= 0 && runtime_row_scan_begin s< game->runtime_row_count)
004390eb        int32_t edx_8 = (var_3c_1 i+ (runtime_row_scan_begin << 3)) i* 0x15
004390f8        void* edi_3 = game + (edx_8 << 2)
004390fb        if ((((&game->runtime_cells[0][0].bod.list_flags)[edx_8]).w:1.b & 2) == 0)
0043910a        if (((*(edi_3 + 0x3bfb08)).w:1.b & 0x40) != 0)
00439110        char eax_34 = *(edi_3 + 0x3bfb04)
0043911c        if (eax_34 == 0x1d || eax_34 == 0x1e)
00439171        if (*(edi_3 + 0x3bfaec) != 0)
00439190        if ((0x200 & *(edi_3 + 0x3bfacc)) == 0)
004391a1        (edi_3 + 0x3bfac8)->list_prev = &game->special_track_cell_list_head
004391a7        (edi_3 + 0x3bfac8)->list_next = game->special_track_cell_list_head.bod.list_next
004391aa        game->special_track_cell_list_head.bod.list_next = edi_3 + 0x3bfac8
004391ad        struct BodNode* list_next_1 = (edi_3 + 0x3bfac8)->list_next
004391b2        if (list_next_1 != 0)
004391b4        list_next_1->list_prev.b = (edi_3 + 0x3bfac8).b
004391b4        list_next_1->list_prev:1.b = (edi_3 + 0x3bfac8):1.b
004391b7        (edi_3 + 0x3bfac8)->list_flags |= 0x200
00439197        report_errorf("List ADDafter")
004391bc        int32_t eax_39 = runtime_row_scan_begin & 0x80000007
004391c1        if (eax_39 s< 0)
004391c7        eax_39 = ((eax_39 - 1) | 0xfffffff8) + 1
004391e6        *(edi_3 + 0x3bfae8) = fconvert.s(float.t(eax_39) * fconvert.t(0.125f))
004391f2        if ((((edi_1 + 0x5ccb78)->list_flags).w:1.b & 2) == 0)
00439203        (edi_1 + 0x5ccb78)->list_prev = &game->fringe_attachment_list_head
00439209        (edi_1 + 0x5ccb78)->list_next = game->fringe_attachment_list_head.bod.list_next
0043920c        game->fringe_attachment_list_head.bod.list_next = edi_1 + 0x5ccb78
0043920f        struct BodNode* list_next_2 = (edi_1 + 0x5ccb78)->list_next
00439214        if (list_next_2 != 0)
00439216        list_next_2->list_prev.b = (edi_1 + 0x5ccb78).b
00439216        list_next_2->list_prev:1.b = (edi_1 + 0x5ccb78):1.b
00439219        uint32_t list_flags_1 = (edi_1 + 0x5ccb78)->list_flags
0043921c        list_flags_1:1.b |= 2
0043921f        (edi_1 + 0x5ccb78)->list_flags = list_flags_1
004391f9        report_errorf("List ADDafter")
00439230        *(edi_1 + 0x5ccb88) = *(edi_3 + 0x3bfad8)
00439235        *(edi_1 + 0x5ccb8c) = *(edi_3 + 0x3bfadc)
0043923b        *(edi_1 + 0x5ccb90) = *(edi_3 + 0x3bfae0)
00439137        if ((0x200 & *(edi_3 + 0x3bfacc)) == 0)
0043914b        (edi_3 + 0x3bfac8)->list_prev = &game->track_body_list_head
00439151        (edi_3 + 0x3bfac8)->list_next = game->track_body_list_head.bod.list_next
00439154        game->track_body_list_head.bod.list_next = edi_3 + 0x3bfac8
00439157        struct BodNode* list_next = (edi_3 + 0x3bfac8)->list_next
0043915c        if (list_next != 0)
0043915e        list_next->list_prev.b = (edi_3 + 0x3bfac8).b
0043915e        list_next->list_prev:1.b = (edi_3 + 0x3bfac8):1.b
00439161        (edi_3 + 0x3bfac8)->list_flags |= 0x200
0043913e        report_errorf("List ADDafter")
0043924a        (**(edi_3 + 0x3bfac8))()
0043924c        int32_t* ebx_8 = edi_3 + 0x3bfb0c
00439252        uint32_t var_38_2 = 4
004392d9        bool cond:8_1
0043925a        struct BodNode* eax_45 = *ebx_8
0043925e        if (eax_45 != 0)
0043926c        if (((eax_45->list_flags).w:1.b & 2) == 0)
0043927d        eax_45->list_prev = &game->fringe_attachment_list_head
00439283        eax_45->list_next = game->fringe_attachment_list_head.bod.list_next
00439286        game->fringe_attachment_list_head.bod.list_next = eax_45
00439289        struct BodNode* list_next_3 = eax_45->list_next
0043928e        if (list_next_3 != 0)
00439290        list_next_3->list_prev.b = eax_45.b
00439290        list_next_3->list_prev:1.b = eax_45:1.b
00439293        uint32_t list_flags_2 = eax_45->list_flags
00439296        list_flags_2:1.b |= 2
00439299        eax_45->list_flags = list_flags_2
00439273        report_errorf("List ADDafter")
004392ad        struct tColour out
004392ad        struct tColour* eax_46 = get_track_skirt_color(&g_game_base->subgame, &out)
004392b6        float* edx_16 = *ebx_8 + 0x28
004392b9        *edx_16 = eax_46->r
004392be        edx_16[1] = eax_46->g
004392c4        edx_16[2] = eax_46->b
004392ca        edx_16[3] = eax_46->a
004392d1        ebx_8 = &ebx_8[1]
004392d4        cond:8_1 = var_38_2 != 1
004392d5        var_38_2 -= 1
004392d9        do while (cond:8_1)
004392f8        if (*(edi_3 + 0x3bfb04) == 0x17 && (game->runtime_flags:1.b & 8) != 0 && runtime_row_scan_begin s>= game->first_block_row_count && runtime_row_scan_begin s< game->completion_row_start)
0043930a        spawn_track_health_pickup(game, edi_3 + 0x3bfac8, &game->player)
00439320        if (*(edi_3 + 0x3bfb04) == 0x18 && runtime_row_scan_begin s>= game->first_block_row_count && runtime_row_scan_begin s< game->completion_row_start)
0043932e        uint32_t var_50_9 = &game->player.body.bod.bod.vtable
0043932f        void* var_54_3 = edi_3 + 0x3bfac8
00439348        if (*(edi_3 + 0x3bfb04) == 0x19 && runtime_row_scan_begin s>= game->first_block_row_count && runtime_row_scan_begin s< game->completion_row_start)
0043935a        spawn_track_jetpack_pickup(game, edi_3 + 0x3bfac8, &game->player)
0043935f        char eax_51 = *(edi_3 + 0x3bfb04)
00439367        if (eax_51 == 0x21)
0043949f        spawn_track_garbage_hazard(game, edi_3 + 0x3bfac8, &game->player)
00439399        if ((*(edi_3 + 0x3bfb08) & 0x10) == 0 && (eax_51 == 1 || eax_51 == 0x15) && (game->runtime_flags.b & 2) != 0)
0043939f        void* var_50_12 = &data_4a4dbc
004393a9        long double st0_2 = random_float_below(1f)
004393c3        long double x87_r6_4 = (fconvert.t(1f) - fconvert.t(game->garbage_frequency)) * fconvert.t(0.200000003f) + fconvert.t(0.800000012f)
004393c9        x87_r6_4 - st0_2
004393cb        int16_t eax_53 = (x87_r6_4 < st0_2 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_4, st0_2) ? 1 : 0) << 0xa | (x87_r6_4 == st0_2 ? 1 : 0) << 0xe
004393d0        if ((eax_53:1.b & 1) != 0)
004393dc        if (var_3c_1 != 0)
004393de        eax_53.b = *(edi_3 + 0x3bfab0)
004393f2        if (var_3c_1 == 0 || eax_53.b == 1 || eax_53.b == 0x14 || eax_53.b == 0x15 || eax_53.b == 0x20)
004393fb        if (var_3c_1 != 7)
004393fd        eax_53.b = *(edi_3 + 0x3bfb58)
00439411        if ((var_3c_1 == 7 || eax_53.b == 1 || eax_53.b == 0x14 || eax_53.b == 0x15 || eax_53.b == 0x20) && runtime_row_scan_begin s>= game->first_block_row_count && runtime_row_scan_begin s< game->completion_row_start && game->player.click_start.state != CLICK_START_STATE_WAITING_FOR_START)
00439432        long double st0_3
00439432        long double x87_r6_7
00439432        if (game->level_mode == 4)
00439434        void* var_50_13 = &data_4a4db8
0043943e        st0_3 = random_float_below(1f)
0043944f        x87_r6_7 = fconvert.t(game->base_subgame_rate) * fconvert.t(0.300000012f) + fconvert.t(0.699999988f)
00439455        x87_r6_7 - st0_3
0043945c        if (game->level_mode != 4 || (((x87_r6_7 < st0_3 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_7, st0_3) ? 1 : 0) << 0xa | (x87_r6_7 == st0_3 ? 1 : 0) << 0xe):1.b & 1) == 0)
00439463        long double st0_4
00439463        long double x87_r6_10
00439463        if (game->level_mode == 0)
00439465        void* var_50_14 = &data_4a4db4
0043946f        st0_4 = random_float_below(1f)
00439480        x87_r6_10 = fconvert.t(game->base_subgame_rate) * fconvert.t(0.600000024f) + fconvert.t(0.400000006f)
00439486        x87_r6_10 - st0_4
0043948d        if (game->level_mode != 0 || (((x87_r6_10 < st0_4 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_10, st0_4) ? 1 : 0) << 0xa | (x87_r6_10 == st0_4 ? 1 : 0) << 0xe):1.b & 1) == 0)
0043949f        spawn_track_garbage_hazard(game, edi_3 + 0x3bfac8, &game->player)
004394a4        char eax_60 = *(edi_3 + 0x3bfb04)
004394ac        if (eax_60 != 0x22)
004394e6        if ((*(edi_3 + 0x3bfb08) & 8) == 0 && (eax_60 == 1 || eax_60 == 0xf) && game->player.click_start.state != CLICK_START_STATE_WAITING_FOR_START && (game->runtime_flags & 0x10000) != 0)
004394e8        void* var_50_16 = &data_4a4db0
004394f2        long double st0_5 = random_float_below(1f)
0043950c        long double x87_r6_14 = (fconvert.t(1f) - fconvert.t(game->salt_frequency)) * fconvert.t(0.0199999996f) + fconvert.t(0.980000019f)
00439512        x87_r6_14 - st0_5
00439523        if ((((x87_r6_14 < st0_5 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_14, st0_5) ? 1 : 0) << 0xa | (x87_r6_14 == st0_5 ? 1 : 0) << 0xe):1.b & 1) != 0 && runtime_row_scan_begin s>= game->first_block_row_count && runtime_row_scan_begin s< game->completion_row_start)
00439532        spawn_salt_hazard(&game->salt_hazards, edi_3 + 0x3bfad8)
004394ba        if (runtime_row_scan_begin s>= game->first_block_row_count && runtime_row_scan_begin s< game->completion_row_start)
00439532        spawn_salt_hazard(&game->salt_hazards, edi_3 + 0x3bfad8)
0043954e        if ((game->runtime_flags.b & 0x80) != 0 && *(edi_3 + 0x3bfb04) == 0x12 && runtime_row_scan_begin s>= game->first_block_row_count && runtime_row_scan_begin s< game->completion_row_start)
00439560        spawn_slug_hazard(game, edi_3 + 0x3bfac8, &game->player)
00439569        int16_t edx_22 = (*(edi_1 + &data_5ccac8)).w
00439572        if ((edx_22:1.b & 2) == 0)
00439578        char ecx_56 = *(edi_3 + 0x3bfb04)
00439581        int32_t requested_kind
00439581        struct Player* player
00439581        float ring_speed
00439581        if (ecx_56 != 0x23)
00439647        long double x87_r7_16
00439647        long double temp5_1
00439647        if (ecx_56 == 2 || ecx_56 == 3 || ecx_56 == 4 || ecx_56 == 5 || ecx_56 == 6 || ecx_56 == 7)
00439653        x87_r7_16 = fconvert.t(game->player.last_ring_spawn_z) + fconvert.t(10f)
00439659        temp5_1 = fconvert.t(*(edi_3 + 0x3bfae0))
00439659        x87_r7_16 - temp5_1
00439647        if ((ecx_56 != 2 && ecx_56 != 3 && ecx_56 != 4 && ecx_56 != 5 && ecx_56 != 6 && ecx_56 != 7) || (((x87_r7_16 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_16, temp5_1) ? 1 : 0) << 0xa | (x87_r7_16 == temp5_1 ? 1 : 0) << 0xe):1.b & 1) == 0 || runtime_row_scan_begin s>= game->completion_row_start)
004397c2        if (ecx_56 == 8 || ecx_56 == 9 || ecx_56 == 0xa)
004397ce        long double x87_r7_21 = fconvert.t(game->player.last_ring_spawn_z) + fconvert.t(10f)
004397d4        long double temp6_1 = fconvert.t(*(edi_3 + 0x3bfae0))
004397d4        x87_r7_21 - temp6_1
004397e4        if ((((x87_r7_21 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_21, temp6_1) ? 1 : 0) << 0xa | (x87_r7_21 == temp6_1 ? 1 : 0) << 0xe):1.b & 1) != 0 && runtime_row_scan_begin s< game->completion_row_start)
004397e9        if ((edx_22:1.b & 8) != 0)
004397ff        ring_speed = *(game + ((runtime_row_scan_begin + (runtime_row_scan_begin * 3 + 0x12414) * 0x14 + 0x615c) << 2))
0043983a        label_43983a:
0043983a        player = &game->player
0043983b        requested_kind = 2
0043983b        goto label_439846
00439802        void* var_50_22 = &data_4a4da8
0043980c        long double st0_7 = random_float_below(1f)
00439811        long double temp7_1 = fconvert.t(0.699999988f)
00439811        st0_7 - temp7_1
00439830        if ((((st0_7 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(st0_7, temp7_1) ? 1 : 0) << 0xa | (st0_7 == temp7_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0 || game->level_mode == 7 || ((*(edi_1 + &data_5ccac8)).w:1.b & 8) != 0)
00439832        ring_speed = 0f
00439832        goto label_43983a
00439676        if ((edx_22:1.b & 0x20) != 0)
0043969f        spawn_track_ring_or_special_effect(game, edi_3 + 0x3c0a88, 8, &game->player, *(game + ((runtime_row_scan_begin + (runtime_row_scan_begin * 3 + 0x12414) * 0x14 + 0x615c) << 2)))
00439851        game->player.last_ring_spawn_z = *(edi_3 + 0x3c0aa0)
004396b2        if ((edx_22:1.b & 8) != 0)
004396db        spawn_track_ring_or_special_effect(game, edi_3 + 0x3c0a88, 6, &game->player, *(game + ((runtime_row_scan_begin + (runtime_row_scan_begin * 3 + 0x12414) * 0x14 + 0x615c) << 2)))
00439851        game->player.last_ring_spawn_z = *(edi_3 + 0x3c0aa0)
004396ee        if ((edx_22:1.b & 0x10) != 0)
00439717        spawn_track_ring_or_special_effect(game, edi_3 + 0x3c0a88, 7, &game->player, *(game + ((runtime_row_scan_begin + (runtime_row_scan_begin * 3 + 0x12414) * 0x14 + 0x615c) << 2)))
00439851        game->player.last_ring_spawn_z = *(edi_3 + 0x3c0aa0)
0043972b        if ((game->runtime_flags.b & 8) != 0)
00439731        void* var_50_21 = &data_4a4dac
0043973b        long double st0_6 = random_float_below(1f)
00439740        long double temp8_1 = fconvert.t(0.699999988f)
00439740        st0_6 - temp8_1
00439749        int16_t eax_87 = (st0_6 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(st0_6, temp8_1) ? 1 : 0) << 0xa | (st0_6 == temp8_1 ? 1 : 0) << 0xe
00439754        if ((eax_87:1.b & 0x41) == 0 || game->level_mode == 7)
0043975a        eax_87.b = *(edi_3 + 0x3bfb04)
00439772        if (eax_87.b != 5 && eax_87.b != 6 && eax_87.b != 7)
0043978c        spawn_track_ring_or_special_effect(game, edi_3 + 0x3bfac8, 4, &game->player, 0f)
00439798        if (game->player.lives s< 0xa)
00439851        game->player.last_ring_spawn_z = *(edi_3 + 0x3bfae0)
004397aa        game->player.last_ring_spawn_z = fconvert.s(fconvert.t(*(edi_3 + 0x3bfae0)) + fconvert.t(35f))
0043958a        if ((edx_22:1.b & 4) == 0)
004395b2        if ((edx_22:1.b & 0x20) != 0)
004395ce        ring_speed = *(game + ((runtime_row_scan_begin + (runtime_row_scan_begin * 3 + 0x12414) * 0x14 + 0x615c) << 2))
004395cf        player = &game->player
004395d0        requested_kind = 8
004395d2        goto label_439846
004395da        if ((edx_22:1.b & 8) != 0)
004395f6        ring_speed = *(game + ((runtime_row_scan_begin + (runtime_row_scan_begin * 3 + 0x12414) * 0x14 + 0x615c) << 2))
004395f7        player = &game->player
004395f8        requested_kind = 6
004395fa        goto label_439846
00439602        if ((edx_22:1.b & 0x10) != 0)
00439622        ring_speed = *(game + ((runtime_row_scan_begin + (runtime_row_scan_begin * 3 + 0x12414) * 0x14 + 0x615c) << 2))
00439623        player = &game->player
00439624        requested_kind = 7
00439626        goto label_439846
004395a6        ring_speed = *(game + ((runtime_row_scan_begin + (runtime_row_scan_begin * 3 + 0x12414) * 0x14 + 0x615c) << 2))
004395a7        player = &game->player
004395a8        requested_kind = 5
00439846        label_439846:
00439846        spawn_track_ring_or_special_effect(game, edi_3 + 0x3bfac8, requested_kind, player, ring_speed)
00439851        game->player.last_ring_spawn_z = *(edi_3 + 0x3bfae0)
0043985c        cond:5_1 = var_3c_1 i+ 1 s< 8
0043985f        var_3c_1 += 1
00439863        do while (cond:5_1)
0043986c        runtime_row_scan_begin += 1
0043986d        cond:6_1 = runtime_row_scan_begin s< game->runtime_row_scan_end
0043986f        game->scan_reset = 0
00439872        do while (cond:6_1)
0043987b        update_track_render_cache_rows(&game->segment_cache)
00439884        if (game->level_mode != 4)
00439927        game->top_score_widget->text_buffer.raw[0] = 0
0043993b        border_add_text_number(game->top_score_widget, game->player.total_score)
00439940        int32_t total_score = game->player.total_score
0043994e        if (total_score s> game->active_level_score)
00439950        struct FrontendWidget* bottom_score_widget = game->bottom_score_widget
00439956        game->active_level_score = total_score
0043995c        bottom_score_widget->text_buffer.raw[0] = 0
00439970        border_add_text_number(game->bottom_score_widget, game->active_level_score)
00439977        update_subgame_camera(game)
00439983        return
00439899        format_time_trial_string(&game->time_trial, &game->player.stopwatch)
004398ac        rstrcpy_checked_ascii(&game->top_score_widget->text_buffer, 0x751478)
004398ca        void* eax_102 = game->level_mode_arg * 0x1fac0 + game
004398d3        if (*(eax_102 + 0x944150) != 1)
0043990d        hide_border_init(game->bottom_score_widget)
00439914        update_subgame_camera(game)
00439920        return
004398dd        format_time_trial_string(&game->time_trial, eax_102 + 0x944158)
004398f0        rstrcpy_checked_ascii(&game->bottom_score_widget->text_buffer, 0x751478)
004398fa        update_subgame_camera(game)
00439906        return
00438ef3        long double x87_r7_3 = fconvert.t(game->pause_fade)
00438ef6        long double temp0_1 = fconvert.t(0f)
00438ef6        x87_r7_3 - temp0_1
00438efc        eax_12 = (x87_r7_3 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp0_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp0_1 ? 1 : 0) << 0xe
00438f0f        if ((eax_12:1.b & 0x40) == 0 || ((game->player.control_source->control_flags_a).w:1.b & 0x40) == 0)
00438f01        goto label_438f15
00439984        eax_12.b = game->selected_level_record_persistent
0043998c        if (eax_12.b == 0)
004399b2        game_base_1->players[0].saved_frontend_state = game_base_1->players[0].frontend_state
004399bd        *(g_game_base + 0x1b8) = 0x1b
00439994        game_base_1->players[0].saved_frontend_state = game_base_1->players[0].frontend_state
004399a0        g_game_base->players[0].frontend_state = 0x1a
004399c7        struct GameRoot* game_base_2 = g_game_base
004399cd        long double x87_r7_23 = fconvert.t(game_base_2->intro.attract_reset_progress)
004399d3        long double temp1_1 = fconvert.t(1f)
004399d3        x87_r7_23 - temp1_1
004399de        if ((((x87_r7_23 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_23, temp1_1) ? 1 : 0) << 0xa | (x87_r7_23 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00439906        return
004399e7        game_base_2->intro.hide_for_replay_latch = 0
004399f2        return
00438bb6        case 3
00438bb6        game->subgame_state = 4
00438bbd        game->subgame_pause_gate = 1
00438bc7        game->pause_fade = game->pause_fade_step
00438bca        initialize_pause_menu(&game->sub_pause)
00438bd2        update_pause_menu(&game->sub_pause)
00438bde        return
00438bd2        case 4
00438bd2        update_pause_menu(&game->sub_pause)
00438bde        return
004398fa        case 5, 6
004398fa        update_subgame_camera(game)
00439906        return
00438bec        case 7
00438bec        if (game->selected_level_record_persistent != 1)
00438c1d        game->selected_level_record_active = 0
00438c24        build_subgame_level(game, 0)
00438c29        game->subgame_state = 2
00438c36        g_game_base->render_skip_count = 1
00438c43        return
00438bf2        game->selected_level_record_active = 1
00438bf9        build_subgame_level(game, 0)
00438bfe        game->subgame_state = 2
00438c0b        g_game_base->render_skip_count = 1
00438c18        return
