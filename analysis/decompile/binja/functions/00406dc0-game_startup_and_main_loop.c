/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: game_startup_and_main_loop @ 0x406dc0 */

00406dcf        int32_t edi = 0
00406dd9        if (FindWindowExA(nullptr, nullptr, "SnailMailWindowClass", nullptr) != 0)
00406de2        return 0
00406def        int32_t* esi
00406def        if (sub_44afc0(esi, nullptr) s< 0x801)
00406df1        abort_startup_with_3d_error()
00406dfd        return 0
00406e00        rebuild_game_archive_if_needed()
00406e0f        load_config_file("SnailMail.cfg", &g_runtime_config)
00406e14        uint8_t (* var_38)[0x11] = &g_runtime_config.validation_tail
00406e1e        g_runtime_config.load_valid_flag = sub_42f5b0()
00406e2a        data_4dfad8 = arg1
00406e2f        initialize_trigonometry_tables()
00406e3b        if (initialize_game_data_archive() == 0)
00406e44        return 0
00406e48        int32_t* var_34 = esi
00406e49        snapshot_current_display_mode()
00406e4e        initialize_mouse_authored_scale_from_clip_rect()
00406e53        probe_display_mode_count()
00406e62        read_current_display_resolution(0x4df858, 0x4b775c)
00406e6a        data_4df85c = 0x44200000
00406e74        data_4b7760 = 0x43f00000
00406e7e        data_4df90c = 1
00406e85        g_window_deactivated = 0
00406e8b        log_startup_timestamp()
00406e90        uint32_t (__stdcall* const ebp)() = timeGetTime
00406ea6        while (true)
00406eaa        MSG msg
00406eaa        if (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE) != 0)
00406ede        BOOL i
00406eb1        if (msg.message != 0x12)
00406ebf        TranslateMessage(&msg)
00406eca        DispatchMessageA(&msg)
00406eb3        edi = 1
00406eda        i = PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE)
00406ede        do while (i != 0)
00406ee6        if (data_4df90c != 0)
00406eec        initialize_audio_subsystem()
00406ef6        int32_t enabled = initialize_game_window_and_input_wrapper("SnailMail")
00406f00        enabled.b = g_runtime_config.fullscreen_enabled
00406f07        set_fullscreen_mode(enabled)
00406f0f        sub_406d70()
00406f19        initialize_loading_screen(&g_loading_bar)
00406f26        int32_t i_3 = mods.dp.d(sx.q(ebp()), 0x3e8)
00406f2a        if (i_3 s> 0)
00406f2c        int32_t i_2 = i_3
00406f44        int32_t i_1
00406f2e        int32_t var_38_3 = 0
00406f34        random_float_below(1f)
00406f3e        next_math_random_value()
00406f43        i_1 = i_2
00406f43        i_2 -= 1
00406f44        do while (i_1 != 1)
00406f46        construct_game_runtime()
00406f4b        set_tracked_allocation_mark()
00406f56        uint8_t eax_12
00406f56        eax_12, ebp, edi = initialize_game_assets_and_world(g_game_base)
00406f5d        if (eax_12 == 0)
00406f5f        edi = 1
00406f66        sub_412a00(1)
00406f74        initialize_game_last(g_game_base)
00406f7e        data_4df90c = 0
00406f84        data_4b7759 = 0
00406f8a        destroy_loading_screen(&g_loading_bar)
00406f98        begin_frontend_fade_in(&g_game_base->fade)
00406f9d        show_and_focus_game_window()
00406fa8        if (data_4b7759 != 0)
00406faa        sub_4134c0()
00406fba        if (g_game_base->render_skip_count == 0)
00406fbc        present_backbuffer()
00406fc1        data_4b7759 = 0
00406ffe        long double x87_r7_7
00406ffe        long double temp2_1
00406fcd        int32_t var_20_1 = 0
00406fdb        data_4dfb04 = fconvert.s(float.t(ebp().q) * fconvert.t(0.00100000005f))
00406fed        x87_r7_7 = fconvert.t(data_4dfafc) + fconvert.t(data_4dfb04) - fconvert.t(data_4dfb00)
00406ff3        temp2_1 = fconvert.t(0.00083333333333333339)
00406ff3        x87_r7_7 - temp2_1
00406ffe        do while ((((x87_r7_7 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp2_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp2_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00407006        long double x87_r7_9 = fconvert.t(data_4dfb04) - fconvert.t(data_4dfb00)
00407012        data_4dfb00 = data_4dfb04
0040701e        data_4dfafc = fconvert.s(x87_r7_9 + fconvert.t(data_4dfafc))
00407024        long double x87_r7_11 = fconvert.t(data_4dfafc)
0040702a        long double temp3_1 = fconvert.t(0.416666657f)
0040702a        x87_r7_11 - temp3_1
00407035        if ((((x87_r7_11 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_11, temp3_1) ? 1 : 0) << 0xa | (x87_r7_11 == temp3_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00407037        data_4dfafc = 0x3ed55555
00407041        long double x87_r7_12 = fconvert.t(data_4dfafc)
00407047        long double temp5_1 = fconvert.t(0f)
00407047        x87_r7_12 - temp5_1
0040704d        data_4b7758 = 0
00407053        data_4b763c = 0
00407062        if ((((x87_r7_12 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_12, temp5_1) ? 1 : 0) << 0xa | (x87_r7_12 == temp5_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0040706e        while (data_4b7758 == 0)
00407076        if (edi != 0)
00407076        break
00407088        data_4b763c = fconvert.s(fconvert.t(data_4b763c) + fconvert.t(1f))
00407094        long double x87_r7_16 = fconvert.t(data_4dfafc) - fconvert.t(0.0166666675f)
0040709a        data_4dfafc = fconvert.s(x87_r7_16)
004070a0        long double temp6_1 = fconvert.t(0f)
004070a0        x87_r7_16 - temp6_1
004070a6        long double x87_r7_17 = fconvert.t(data_4dfafc)
004070b1        if ((((x87_r7_16 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_16, temp6_1) ? 1 : 0) << 0xa | (x87_r7_16 == temp6_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
004070b3        x87_r7_17 = fneg(x87_r7_17)
004070b5        long double temp7_1 = fconvert.t(8.33333343e-06f)
004070b5        x87_r7_17 - temp7_1
004070c0        if ((((x87_r7_17 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_17, temp7_1) ? 1 : 0) << 0xa | (x87_r7_17 == temp7_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
004070d5        long double x87_r7_18 = fconvert.t(data_4dfafc)
004070db        long double temp8_1 = fconvert.t(0f)
004070db        x87_r7_18 - temp8_1
004070e6        if ((((x87_r7_18 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_18, temp8_1) ? 1 : 0) << 0xa | (x87_r7_18 == temp8_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
004070f1        g_render_queue_active = 0
004070e8        g_render_queue_active = 1
004070c2        data_4dfafc = 0
004070cc        g_render_queue_active = 1
004070f7        HWND eax_17 = GetActiveWindow()
00407106        if (eax_17 == g_main_window)
0040710f        if (data_753c70 == 1)
00407116        resume_audio_backend_if_paused(&g_audio_backend)
00407121        if (eax_17 == g_main_window || g_window_deactivated != 0)
00407121        goto label_407156
00407121        goto label_40712c
00407129        int16_t eax_20
00407129        if (g_window_deactivated != 0)
00407156        label_407156:
00407156        int32_t esi_2 = 0
0040715b        if (g_game_base->fixed_update_count s> 0)
00407162        while (true)
00407162        int32_t main_window_2 = g_main_window
00407163        update_keyboard_input()
0040716e        int32_t main_window_1 = g_main_window
0040716f        update_joystick_input()
0040717b        update_mouse(g_main_window)
00407183        update_font_wave_state()
0040718e        int32_t eax_22 = run_frame_update(g_game_base)
00407196        data_4b7759 = 1
004071a7        if (eax_22 == 1 || eax_22 == 2 || eax_22 == 3)
004071b6        edi = 1
004071b6        break
004071ae        esi_2 += 1
004071b2        if (esi_2 s>= g_game_base->fixed_update_count)
004071b2        break
004071b2        continue
0040712c        label_40712c:
0040712c        ClipCursor(nullptr)
00407132        eax_20.b = g_runtime_config.fullscreen_enabled
00407137        g_render_queue_active = 1
00407140        data_4b7759 = 1
00407147        if (eax_20.b != 0)
00407149        sub_407490()
004071bb        long double x87_r7_19 = fconvert.t(data_4dfafc)
004071c1        long double temp9_1 = fconvert.t(0f)
004071c1        x87_r7_19 - temp9_1
004071c7        eax_20 = (x87_r7_19 < temp9_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_19, temp9_1) ? 1 : 0) << 0xa | (x87_r7_19 == temp9_1 ? 1 : 0) << 0xe
004071cc        if ((eax_20:1.b & 0x41) != 0)
004071cc        break
004071d8        long double x87_r7_21 = fconvert.t(data_4b7768) * fconvert.t(data_4b7638)
004071de        data_4b7758 = 0
004071e4        long double x87_r7_22 = x87_r7_21 + fconvert.t(data_4b763c)
004071f6        data_4b7768 = fconvert.s(fconvert.t(data_4b7768) + fconvert.t(1f))
00407202        data_4b7638 = fconvert.s(x87_r7_22 / fconvert.t(data_4b7768))
00407213        if (data_4df864 != 0)
00407213        break
00407217        if (edi != 0)
00407217        break
00407222        stop_audio_backend(&g_audio_backend)
00407227        shutdown_bass_audio_window()
0040723a        save_high_scores_and_config(&g_game_base->subgame.sub_high_score, 1)
0040724d        save_high_scores_and_config(&g_game_base->subgame.sub_high_score, 2)
0040725f        save_high_scores_and_config(&g_game_base->subgame.sub_high_score, 4)
00407272        save_high_scores_and_config(&g_game_base->subgame.sub_high_score, 8)
00407285        save_high_scores_and_config(&g_game_base->subgame.sub_high_score, 0x10)
0040728a        g_game_base
00407295        free_tracked_allocations_to_mark()
004072a0        sub_48ba34(g_game_base)
004072a5        uninitialize_game_data_archive()
004072b9        save_config_file("SnailMail.cfg", &g_runtime_config, 0xc4)
004072c1        uninitialize_input_devices()
004072c6        data_4df90c = 1
004072cd        data_4df864 = 0
004072d3        restore_desktop_display_mode()
004072e1        return 0
