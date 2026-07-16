/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_galaxy @ 0x4092f0 */

00409308        hide_gameplay_scores(galaxy->level_progress_base)
00409312        int32_t i = 0
00409316        if (g_runtime_config.highest_galaxy_route_index s>= 0)
00409318        struct GalaxyRouteSlot (* slot)[0x65] = &galaxy->route_slots
0040931d        update_galaxy_route_record(slot)
00409327        i += 1
00409328        slot = &(*slot)[1]
00409330        do while (i s<= g_runtime_config.highest_galaxy_route_index)
00409351        struct tColour color_1
00409351        if (galaxy->route_state == 1 && ((galaxy->bounds_frame_widget->widget_flags).w:1.b & 0x10) == 0)
0040936f        store_color4f(&color_1, 1f, 1f, 1f, 0.999000013f)
0040937a        struct FrontendWidget* bounds_frame_widget_1 = galaxy->bounds_frame_widget
00409389        long double x87_r7_1 = fconvert.t(bounds_frame_widget_1->authored_left)
00409392        void* ecx_8 = galaxy->selected_index * 0x2a0 + galaxy
00409394        long double temp0_1 = fconvert.t(*(ecx_8 + 0x1c))
00409394        x87_r7_1 - temp0_1
0040939c        float y1 = *(ecx_8 + 0x20)
004093b2        float y0
004093b2        float x1
004093b2        long double x87_r7_5
004093b2        if ((((x87_r7_1 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp0_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
004093d3        void* var_5c_2 = ecx_8
004093da        x1 = fconvert.s(fconvert.t(bounds_frame_widget_1->authored_width) + fconvert.t(bounds_frame_widget_1->authored_left) + fconvert.t(6f))
004093e0        x87_r7_5 = fconvert.t(*(ecx_8 + 0x1c)) - fconvert.t(16f)
004093e6        y0 = y1
004093bd        void* var_5c_1 = ecx_8
004093be        x1 = fconvert.s(fconvert.t(bounds_frame_widget_1->authored_left) - fconvert.t(6f))
004093c4        x87_r7_5 = fconvert.t(*(ecx_8 + 0x1c)) + fconvert.t(16f)
004093ca        y0 = y1
004093e7        void* var_64_1 = ecx_8
004093f2        draw_galaxy_line(galaxy, 0x99, fconvert.s(x87_r7_5), y0, x1, y1, 4f, &color_1)
004093fc        float i_1 = 1.40129846e-45f
00409400        struct tColour color
00409400        if (g_runtime_config.highest_galaxy_route_index s>= 1)
00409412        int32_t ecx_11 = i_1 i* 0x2a0
00409419        void* edi = ecx_11 + galaxy
00409415        galaxy->route_slots[i_1]
00409432        color_1.r = galaxy->route_names[*(&galaxy->:0x10.67872[0]:4.668 + ecx_11)].color.r
00409439        color_1.g = galaxy->route_names[*(&galaxy->:0x10.67872[0]:4.668 + ecx_11)].color.g
0040943d        int32_t b = galaxy->route_names[*(&galaxy->:0x10.67872[0]:4.668 + ecx_11)].color.b
00409440        color_1.b = b
00409447        color_1.r = 0x3f800000
0040944f        color_1.a = galaxy->route_names[*(&galaxy->:0x10.67872[0]:4.668 + ecx_11)].color.a
00409453        color_1.g = 0x3f800000
0040945b        color_1.b = 0x3f800000
00409463        color_1.a = 0x3f7d70a4
0040946b        int32_t b_1
0040946b        if (i_1 == 0)
0040946e        int32_t var_54_1 = 0xf
00409470        int32_t var_58_2 = 0x3f800000
00409475        int32_t var_5c_3 = 0x3f800000
0040948c        struct tColour* color_2
0040948c        color_2, b = set_color_rgba(&color, 1f, i_1, i_1, 0.99000001f)
0040949b        int32_t var_6c_2 = 0x1000000
004094a0        int32_t var_70_2 = 0x42000000
004094a5        int32_t var_74_1 = 0x42000000
004094aa        int32_t b_2 = b
004094fc        b_1 = b
00409505        queue_axis_aligned_textured_quad_uv(0x97, fconvert.s(fconvert.t(galaxy->route_slots[0].record.map_x) - fconvert.t(16f)), fconvert.s(fconvert.t(galaxy->route_slots[0].record.map_y) - fconvert.t(16f)), 32f, 32f, 0x1000000, color_2, i_1, i_1, 1f, 1f, 0xf, i_1)
004094be        if (galaxy->route_mode != 1 || i_1 s<= galaxy->selected_index)
004094c5        int32_t var_54_2 = 0xf
004094cd        int32_t var_58_3 = 0x3f800000
004094d2        int32_t var_5c_4 = 0x3f800000
004094e0        int32_t var_6c_3 = 0x1000000
004094e5        int32_t var_70_3 = 0x42000000
004094ea        int32_t var_74_2 = 0x42000000
004094ef        int32_t b_3 = b
004094fc        b_1 = b
00409505        queue_axis_aligned_textured_quad_uv(0x97, fconvert.s(fconvert.t(*(edi + 0x1c)) - fconvert.t(16f)), fconvert.s(fconvert.t(*(edi + 0x20)) - fconvert.t(16f)), 32f, 32f, 0x1000000, &color_1, 0f, 0f, 1f, 1f, 0xf, 0f)
0040950d        long double x87_r7_16 = fconvert.t(*(edi + 0x28))
00409510        long double temp1_1 = fconvert.t(0f)
00409510        x87_r7_16 - temp1_1
0040951b        if ((((x87_r7_16 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_16, temp1_1) ? 1 : 0) << 0xa | (x87_r7_16 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0040951d        int32_t ecx_14 = *(edi + 0x28)
00409534        color_1.a = ecx_14
00409553        int32_t var_78_2 = ecx_14
00409560        int32_t var_7c_2 = ecx_14
00409569        queue_axis_aligned_textured_quad_uv(0x96, fconvert.s(fconvert.t(*(edi + 0x1c)) - fconvert.t(32f)), fconvert.s(fconvert.t(*(edi + 0x20)) - fconvert.t(32f)), 64f, 64f, 0x1000000, &color_1, 0f, 0f, 1f, 1f, 0xf, 0f)
00409576        i_1 += 1
00409579        do while (i_1 s<= g_runtime_config.highest_galaxy_route_index)
00409583        set_color_white(&color_1)
0040958d        color_1.a = 0x3e4ccccd
00409597        int32_t i_2 = 1
00409599        if (g_runtime_config.highest_galaxy_route_index s> 1)
0040959b        float* edi_1 = &galaxy->route_slots[2].record.map_x
004095a7        if (i_2 s< galaxy->selected_index)
004095ad        color_1.a = 0x3f4ccccd
004095c1        int32_t var_54_3 = 0x40800000
00409605        draw_galaxy_line(galaxy, 0x9a, (edi_1 - 0x55c)->route_slots[1].record.map_x, (edi_1 - 0x55c)->route_slots[1].record.map_y, (edi_1 - 0x55c)->route_slots[2].record.map_x, (edi_1 - 0x55c)->route_slots[2].record.map_y, 4f, &color_1)
004095d5        if (galaxy->route_mode != 1)
004095db        color_1.a = 0x3e4ccccd
004095ef        int32_t var_54_4 = 0x40800000
00409605        draw_galaxy_line(galaxy, 0x9a, (edi_1 - 0x55c)->route_slots[1].record.map_x, (edi_1 - 0x55c)->route_slots[1].record.map_y, (edi_1 - 0x55c)->route_slots[2].record.map_x, (edi_1 - 0x55c)->route_slots[2].record.map_y, 4f, &color_1)
0040960f        i_2 += 1
00409610        edi_1 = &edi_1[0xa8]
00409618        do while (i_2 s< g_runtime_config.highest_galaxy_route_index)
0040961e        set_color_white(&color_1)
00409623        int32_t i_3 = 0
00409625        float* ebp = &galaxy->route_names[0].map_x
0040965a        struct tColour* var_78_4 = &color_1
0040966d        struct tColour* var_7c_4 = &color_1
00409672        queue_axis_aligned_textured_quad_uv(i_3 + 0x8b, fconvert.s(fconvert.t((ebp - 0x109c4)->route_names[0].map_x) - fconvert.t(128f)), fconvert.s(fconvert.t((ebp - 0x109c4)->route_names[0].map_y) - fconvert.t(128f)), 256f, 256f, 0x1000000, &color_1, 0f, 0f, 1f, 1f, 0xf, 0f)
0040967a        i_3 += 1
0040967b        ebp = &ebp[0x28]
00409684        do while (i_3 s< 0xa)
0040968b        int32_t i_5 = 1
00409690        int32_t selected_index = 0xffffffff
00409693        struct GameInput* game_input = g_game_base->players[0].game_input
00409699        float authored_x = game_input->input.authored_x
0040969c        float authored_y = game_input->input.authored_y
004096a6        bool cond:3 = galaxy->route_state != 1
004096ac        galaxy->hover_state = 0
004096b6        if (not(cond:3))
004096bc        struct FrontendWidget* bounds_frame_widget = galaxy->bounds_frame_widget
004096c5        long double x87_r7_26 = fconvert.t(bounds_frame_widget->authored_left) - fconvert.t(bounds_frame_widget->current_padding)
004096cb        long double temp2_1 = fconvert.t(authored_x)
004096cb        x87_r7_26 - temp2_1
004096d4        if ((((x87_r7_26 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_26, temp2_1) ? 1 : 0) << 0xa | (x87_r7_26 == temp2_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
004096e3        long double x87_r7_29 = fconvert.t(bounds_frame_widget->authored_width) + fconvert.t(bounds_frame_widget->current_padding) + fconvert.t(bounds_frame_widget->authored_left)
004096e6        long double temp3_1 = fconvert.t(authored_x)
004096e6        x87_r7_29 - temp3_1
004096ef        if ((((x87_r7_29 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_29, temp3_1) ? 1 : 0) << 0xa | (x87_r7_29 == temp3_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
004096f4        long double x87_r7_31 = fconvert.t(bounds_frame_widget->authored_top) - fconvert.t(bounds_frame_widget->current_padding)
004096fa        long double temp4_1 = fconvert.t(authored_y)
004096fa        x87_r7_31 - temp4_1
00409703        if ((((x87_r7_31 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_31, temp4_1) ? 1 : 0) << 0xa | (x87_r7_31 == temp4_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0040970b        long double x87_r7_34 = fconvert.t(bounds_frame_widget->authored_height) + fconvert.t(bounds_frame_widget->authored_top) + fconvert.t(bounds_frame_widget->current_padding)
00409711        long double temp6_1 = fconvert.t(authored_y)
00409711        x87_r7_34 - temp6_1
0040971a        if ((((x87_r7_34 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_34, temp6_1) ? 1 : 0) << 0xa | (x87_r7_34 == temp6_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0040971c        galaxy->hover_state = 1
0040972a        int32_t i_4 = 1
0040972c        if (g_runtime_config.highest_galaxy_route_index s>= 1)
0040972e        float* ecx_22 = &galaxy->route_slots[1].record.highlight_target
0040973a        if (i_4 != galaxy->selected_index)
00409744        (ecx_22 - 0x2cc)->:0x2cc.b = 0
00409744        (ecx_22 - 0x2cc)->:0x2cd.b = 0
00409744        (ecx_22 - 0x2cc)->:0x2ce.b = 0
00409744        (ecx_22 - 0x2cc)->:0x2cf.b = 0
0040973c        (ecx_22 - 0x2cc)->:0x2cc.b = 0
0040973c        (ecx_22 - 0x2cc)->:0x2cd.b = 0
0040973c        (ecx_22 - 0x2cc)->:0x2ce.b = 0x80
0040973c        (ecx_22 - 0x2cc)->:0x2cf.b = 0x3f
00409750        i_4 += 1
00409751        ecx_22 = &ecx_22[0xa8]
00409759        do while (i_4 s<= g_runtime_config.highest_galaxy_route_index)
0040975e        if (galaxy->route_mode == 1)
00409775        (&galaxy->route_slots[0].record.highlight_target)[galaxy->selected_index * 0xa8] = 0x3f800000
0040978a        if (galaxy->hover_state == 0)
00409793        struct Vec3 vector
00409793        if (galaxy->route_state == 1)
00409799        galaxy->selected_index
004097ba        int32_t edx_9 = (&galaxy->route_slots[0].record.map_z)[galaxy->:0x10f80.d * 0xa8]
004097bd        color.r = fconvert.s(fconvert.t((&galaxy->route_slots[0].record.map_x)[galaxy->:0x10f80.d * 0xa8]) - fconvert.t(authored_x))
004097cc        color.b = edx_9
004097d0        vector.x = color.r
004097d4        vector.z = edx_9
004097d8        color.g = fconvert.s(fconvert.t((&galaxy->route_slots[0].record.map_y)[galaxy->:0x10f80.d * 0xa8]) - fconvert.t(authored_y))
004097e0        vector.y = color.g
004097e8        long double st0_1 = normalize_vector(&vector)
004097ed        long double temp5_1 = fconvert.t(17f)
004097ed        st0_1 - temp5_1
00409802        if ((((st0_1 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(st0_1, temp5_1) ? 1 : 0) << 0xa | (st0_1 == temp5_1 ? 1 : 0) << 0xe):1.b & 1) != 0 && galaxy->hover_state == 0)
00409804        selected_index = galaxy->selected_index
0040980a        galaxy->hover_state = 2
00409823        (&galaxy->route_slots[0].record.highlight_target)[selected_index * 0xa8] = 0x3f800000
00409832        if (g_runtime_config.highest_galaxy_route_index s>= 1)
00409838        float* edi_2 = &galaxy->route_slots[1].record.highlight_target
00409845        float map_z = (edi_2 - 0x2cc)->route_slots[1].record.map_z
00409848        color.b = map_z
0040984c        color.r = fconvert.s(fconvert.t((edi_2 - 0x2cc)->route_slots[1].record.map_x) - fconvert.t(authored_x))
0040985b        vector.z = map_z
00409863        vector.x = color.r
00409867        color.g = fconvert.s(fconvert.t((edi_2 - 0x2cc)->route_slots[1].record.map_y) - fconvert.t(authored_y))
0040986f        vector.y = color.g
00409873        long double st0_2 = normalize_vector(&vector)
00409878        long double temp7_1 = fconvert.t(17f)
00409878        st0_2 - temp7_1
0040988d        if ((((st0_2 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(st0_2, temp7_1) ? 1 : 0) << 0xa | (st0_2 == temp7_1 ? 1 : 0) << 0xe):1.b & 1) != 0 && galaxy->hover_state == 0)
0040988f        galaxy->hover_state = 2
00409899        selected_index = i_5
0040989b        (edi_2 - 0x2cc)->route_slots[1].record.highlight_target = 1f
004098af        if (galaxy->route_state != 1 || i_5 != galaxy->selected_index)
004098b9        (edi_2 - 0x2cc)->route_slots[1].record.highlight_target = 0f
004098b1        (edi_2 - 0x2cc)->route_slots[1].record.highlight_target = 1f
004098c4        i_5 += 1
004098c5        edi_2 = &edi_2[0xa8]
004098cd        do while (i_5 s<= g_runtime_config.highest_galaxy_route_index)
004098d8        struct GameRoot* game_base_3 = g_game_base
004098e6        if (game_base_3->border_manager.delayed_widget_active == 0)
004098ec        struct FrontendWidget* exit_or_back_widget = galaxy->exit_or_back_widget
004098f2        int32_t eax_45
004098f2        eax_45.b = exit_or_back_widget->widget_flags.b
004098f2        eax_45:1.b = exit_or_back_widget->widget_flags:1.b
004098f2        eax_45:2.b = exit_or_back_widget->widget_flags:2.b
004098f2        eax_45:3.b = exit_or_back_widget->widget_flags:3.b
004098fa        if ((eax_45.b & 0x20) != 0)
004098fc        eax_45.b &= 0xdf
004098fe        exit_or_back_widget->widget_flags.b = eax_45.b
004098fe        exit_or_back_widget->widget_flags:1.b = eax_45:1.b
004098fe        exit_or_back_widget->widget_flags:2.b = eax_45:2.b
004098fe        exit_or_back_widget->widget_flags:3.b = eax_45:3.b
00409909        if (galaxy->route_mode != 1)
00409947        destroy_galaxy(galaxy)
00409958        return 3
0040990b        struct GameRoot* game_base_1 = g_game_base
0040991a        game_base_1->exit_controller.previous_frontend_state = game_base_1->players[0].frontend_state
00409925        g_game_base->exit_controller.state = 0xb
0040992f        struct GameRoot* game_base_2 = g_game_base
00409937        game_base_2->players[0].frontend_state.b = 8
00409937        game_base_2->players[0].frontend_state:1.b = 0
00409937        game_base_2->players[0].frontend_state:2.b = 0
00409937        game_base_2->players[0].frontend_state:3.b = 0
00409944        return 0
00409959        int32_t route_state = galaxy->route_state
0040995e        int32_t eax_50
0040995e        struct FrontendWidget* play_or_deliver_widget
0040995e        if (route_state == 1)
00409960        play_or_deliver_widget = galaxy->play_or_deliver_widget
00409966        eax_50.b = play_or_deliver_widget->widget_flags.b
00409966        eax_50:1.b = play_or_deliver_widget->widget_flags:1.b
00409966        eax_50:2.b = play_or_deliver_widget->widget_flags:2.b
00409966        eax_50:3.b = play_or_deliver_widget->widget_flags:3.b
0040996e        if (route_state == 1 && (eax_50.b & 0x20) != 0)
00409970        eax_50.b &= 0xdf
00409972        play_or_deliver_widget->widget_flags.b = eax_50.b
00409972        play_or_deliver_widget->widget_flags:1.b = eax_50:1.b
00409972        play_or_deliver_widget->widget_flags:2.b = eax_50:2.b
00409972        play_or_deliver_widget->widget_flags:3.b = eax_50:3.b
0040997a        destroy_galaxy(galaxy)
0040998b        galaxy->level_progress_base->level_mode_arg = galaxy->selected_index
0040998e        struct SubgameRuntime* level_progress_base = galaxy->level_progress_base
004099a2        load_frontend_level_by_mode_and_index(&level_progress_base->level_definition, level_progress_base->level_mode, level_progress_base->level_mode_arg)
004099a7        struct SubgameRuntime* level_progress_base_3 = galaxy->level_progress_base
004099be        if (level_progress_base_3->level_mode == 0 && level_progress_base_3->subgame_rebuild_selector == 1)
004099d0        return 2
00409a5a        return 1
004099d1        struct FrontendWidget* replay_widget = galaxy->replay_widget
004099d7        int32_t eax_54
004099d7        eax_54.b = replay_widget->widget_flags.b
004099d7        eax_54:1.b = replay_widget->widget_flags:1.b
004099d7        eax_54:2.b = replay_widget->widget_flags:2.b
004099d7        eax_54:3.b = replay_widget->widget_flags:3.b
004099df        if ((eax_54.b & 0x20) != 0)
004099e1        eax_54.b &= 0xdf
004099e3        replay_widget->widget_flags.b = eax_54.b
004099e3        replay_widget->widget_flags:1.b = eax_54:1.b
004099e3        replay_widget->widget_flags:2.b = eax_54:2.b
004099e3        replay_widget->widget_flags:3.b = eax_54:3.b
004099eb        destroy_galaxy(galaxy)
004099fc        galaxy->level_progress_base->level_mode_arg = galaxy->selected_index
004099ff        struct SubgameRuntime* level_progress_base_1 = galaxy->level_progress_base
00409a13        load_frontend_level_by_mode_and_index(&level_progress_base_1->level_definition, level_progress_base_1->level_mode, level_progress_base_1->level_mode_arg)
00409a1e        galaxy->level_progress_base->selected_level_record_active = 1
00409a25        struct SubgameRuntime* level_progress_base_2 = galaxy->level_progress_base
00409a4b        level_progress_base_2->selected_level_record = &level_progress_base_2->sub_high_score.time_trial_route_records[galaxy->selected_index]
00409a5a        return 1
00409a69        if (game_base_3->fade.state == 0 && galaxy->route_mode != 1)
00409a6b        int32_t hover_state = galaxy->hover_state
00409a73        if (hover_state != 1)
00409a88        if (hover_state != 2 || (game_base_3->players[0].game_input->input.pressed_buttons & INPUT_BUTTON_PRIMARY) == 0)
00409ad4        if (hover_state == 0 && (game_base_3->players[0].game_input->input.pressed_buttons & INPUT_BUTTON_PRIMARY) != 0 && route_state == 1 && g_runtime_config.highest_galaxy_route_index s> 1)
00409ad8        close_galaxy_route(galaxy)
00409ae4        play_sound_effect(8)
00409a90        if (selected_index != galaxy->selected_index)
00409a95        if (route_state == 1)
00409a99        close_galaxy_route(galaxy)
00409aa1        open_galaxy_route(galaxy, selected_index)
00409ae4        play_sound_effect(8)
00409aaa        if (route_state == 0)
00409aaf        open_galaxy_route(galaxy, selected_index)
00409ae4        play_sound_effect(8)
00409af2        return 0
