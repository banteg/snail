/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: construct_game_runtime @ 0x407b60 */

00407b60        int32_t var_4_2 = 0xffffffff
00407b62        int32_t (* var_8)() = sub_496a7b
00407b6d        TEB* fsbase
00407b6d        struct _EXCEPTION_REGISTRATION_RECORD* ExceptionList = fsbase->NtTib.ExceptionList
00407b6e        fsbase->NtTib.ExceptionList = &ExceptionList
00407b75        int32_t ecx
00407b75        int32_t var_10 = ecx
00407d76        void*** esi = sub_48ba3f(0x12e6ff4)
00407d7b        void*** var_10_1 = esi
00407d81        int32_t var_4 = 0
00407d89        if (esi == 0)
00407f6d        esi = nullptr
00407d99        void*** bod = &esi[0x11]
00407d9c        int32_t i_4 = 2
00407db2        int32_t i
00407da3        initialize_bod_base(bod)
00407da8        *bod = &g_game_input_callback_table
00407dae        bod = &bod[0x1c]
00407db1        i = i_4
00407db1        i_4 -= 1
00407db2        do while (i != 1)
00407db4        struct GamePlayer* player = &esi[0x49]
00407dba        int32_t i_5 = 2
00407dcd        int32_t i_1
00407dc1        initialize_game_player(player)
00407dc6        player = &player[1]
00407dcc        i_1 = i_5
00407dcc        i_5 -= 1
00407dcd        do while (i_1 != 1)
00407dd5        initialize_bod_base(&esi[0x15c])
00407dda        void* edi_1 = &esi[0x16d]
00407de0        int32_t i_6 = 5
00407df0        int32_t i_2
00407de7        initialize_render_camera_slot(edi_1)
00407dec        edi_1 += 0x28
00407def        i_2 = i_6
00407def        i_6 -= 1
00407df0        do while (i_2 != 1)
00407dfa        initialize_renderable_bod(&esi[0x19f])
00407e05        initialize_noop_renderable_bod(&esi[0x1bf])
00407e0a        esi[0x19f] = &g_overlay_callback_table
00407e18        initialize_renderable_bod(&esi[0x1f2])
00407e23        initialize_noop_renderable_bod(&esi[0x212])
00407e28        esi[0x1f2] = &g_overlay_callback_table
00407e36        initialize_renderable_bod(&esi[0x245])
00407e41        initialize_noop_renderable_bod(&esi[0x265])
00407e46        esi[0x245] = &g_overlay_callback_table
00407e54        initialize_renderable_bod(&esi[0x298])
00407e64        esi[0x298] = &g_noop_runtime_callback_table
00407e72        initialize_bod_base(&esi[0x2d3])
00407e8d        initialize_array_with_constructor(&esi[0x474], 0x724, 0x96, initialize_border_record)
00407e92        esi[0x2d3] = &g_border_manager_callback_table
00407e98        struct BodBase* bod_1 = &esi[0x11040]
00407e9e        int32_t i_7 = 0x160
00407eae        int32_t i_3
00407ea5        initialize_bod_base(bod_1)
00407eaa        bod_1 = &bod_1[1]
00407ead        i_3 = i_7
00407ead        i_7 -= 1
00407eae        do while (i_3 != 1)
00407ec6        initialize_array_with_constructor(&esi[0x12382], 0xbc, 0x80, initialize_cached_x_mesh_slot)
00407ed3        initialize_bod_base(&esi[0x13b04])
00407eee        esi[0x13b04] = &g_backdrop_callback_table
00407efc        initialize_bod_base(&esi[0x13ccf])
00407f07        esi[0x13ccf] = &g_star_field_callback_table
00407f0d        initialize_bod_base(&esi[0x13cf2])
00407f28        initialize_array_with_constructor(&esi[0x13d06], 0x90, 0x400, initialize_intro_logo_renderable)
00407f40        initialize_array_with_constructor(&esi[0x1cd06], 0x90, 0x20, initialize_intro_logo_renderable)
00407f4b        initialize_runtime_pools_and_path_template_bank(&esi[0x1d186])
00407f58        initialize_bod_base(&esi[0x4b9bd6])
00407f5d        esi[0x4b9bd6] = &g_tip_manager_callback_table
00407f64        *esi = &g_root_runtime_callback_table
00407f6f        data_50331c
00407f74        int32_t var_4_1 = 0xffffffff
00407f7c        g_game_base = esi
00407fe5        fsbase->NtTib.ExceptionList = ExceptionList
00407ff0        return 0
