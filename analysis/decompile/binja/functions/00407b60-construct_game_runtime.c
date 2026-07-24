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
00407d76        struct GameRoot* game = operator_new(0x12e6ff4)
00407d7b        struct GameRoot* game_1 = game
00407d81        int32_t var_4 = 0
00407d89        if (game == 0)
00407f6d        game = nullptr
00407d99        struct GameInput* game_input_cursor = &game->game_inputs
00407d9c        int32_t i_4 = 2
00407db2        int32_t i
00407da3        initialize_bod_base(game_input_cursor)
00407da8        game_input_cursor->bod.vtable = &g_game_input_callback_table
00407dae        game_input_cursor = &game_input_cursor[1]
00407db1        i = i_4
00407db1        i_4 -= 1
00407db2        do while (i != 1)
00407db4        struct GamePlayer* player_cursor = &game->players
00407dba        int32_t i_5 = 2
00407dcd        int32_t i_1
00407dc1        initialize_game_player(player_cursor)
00407dc6        player_cursor = &player_cursor[1]
00407dcc        i_1 = i_5
00407dcc        i_5 -= 1
00407dcd        do while (i_1 != 1)
00407dd5        initialize_bod_base(&game->inactive_bod_sentinel)
00407dda        struct Viewport* viewport_cursor = &game->viewports
00407de0        int32_t i_6 = 5
00407df0        int32_t i_2
00407de7        initialize_render_camera_slot(viewport_cursor)
00407dec        viewport_cursor = &viewport_cursor[1]
00407def        i_2 = i_6
00407def        i_6 -= 1
00407df0        do while (i_2 != 1)
00407dfa        initialize_renderable_bod(&game->overlay_0)
00407e05        initialize_noop_renderable_bod(&game->overlay_0.camera)
00407e0a        game->overlay_0.bod.bod.bod.vtable = &g_overlay_callback_table
00407e18        initialize_renderable_bod(&game->overlay_1)
00407e23        initialize_noop_renderable_bod(&game->overlay_1.camera)
00407e28        game->overlay_1.bod.bod.bod.vtable = &g_overlay_callback_table
00407e36        initialize_renderable_bod(&game->overlay_2)
00407e41        initialize_noop_renderable_bod(&game->overlay_2.camera)
00407e46        game->overlay_2.bod.bod.bod.vtable = &g_overlay_callback_table
00407e54        initialize_renderable_bod(&game->root_noop_renderable)
00407e64        game->root_noop_renderable.bod.bod.vtable = &g_noop_runtime_callback_table
00407e72        initialize_bod_base(&game->border_manager)
00407e8d        initialize_array_with_constructor(&game->border_manager.borders, 0x724, 0x96, initialize_border_record)
00407e92        game->border_manager.vtable = &g_border_manager_callback_table
00407e98        struct BodBase* root_bod_cursor = &game->root_bod_catalog
00407e9e        int32_t i_7 = 0x160
00407eae        int32_t i_3
00407ea5        initialize_bod_base(root_bod_cursor)
00407eaa        root_bod_cursor = &root_bod_cursor[1]
00407ead        i_3 = i_7
00407ead        i_7 -= 1
00407eae        do while (i_3 != 1)
00407ec6        initialize_array_with_constructor(&game->directx_loader.cached_x_mesh_slots, 0xbc, 0x80, initialize_cached_x_mesh_slot)
00407ed3        initialize_bod_base(&game->backdrop)
00407eee        game->backdrop.bod.bod.vtable = &g_backdrop_callback_table
00407efc        initialize_bod_base(&game->star_manager)
00407f07        game->star_manager.bod.bod.vtable = &g_star_field_callback_table
00407f0d        initialize_bod_base(&game->root_bod_4f3c8)
00407f28        initialize_array_with_constructor(&game->logo.letters, 0x90, 0x400, initialize_intro_logo_renderable)
00407f40        initialize_array_with_constructor(&game->logo.image_donors, 0x90, 0x20, initialize_intro_logo_renderable)
00407f4b        initialize_runtime_pools_and_path_template_bank(&game->subgame)
00407f58        initialize_bod_base(&game->tip_manager)
00407f5d        game->tip_manager.bod.bod.vtable = &g_tip_manager_callback_table
00407f64        game->vtable = &g_root_runtime_callback_table
00407f6f        g_bod_base_init_count
00407f74        int32_t var_4_1 = 0xffffffff
00407f7c        g_game_base = game
00407fe5        fsbase->NtTib.ExceptionList = ExceptionList
00407ff0        return 0
