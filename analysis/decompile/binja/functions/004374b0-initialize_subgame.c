/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_subgame @ 0x4374b0 */

004374b3        int32_t i_3 = 0xc80
004374be        struct FringeObject** eax = &game->runtime_cells[0][0].fringe_front
004374df        int32_t i
004374c4        int32_t j_1 = 8
004374dc        int32_t j
004374c9        struct FringeObject** edi_1 = eax
004374cd        eax = &eax[0x15]
004374d0        j = j_1
004374d0        j_1 -= 1
004374d1        (edi_1 - 0x3bfb0c)->runtime_cells[0][0].fringe_front = nullptr
004374d3        (edi_1 - 0x3bfb0c)->runtime_cells[0][0].fringe_right = nullptr
004374d6        (edi_1 - 0x3bfb0c)->runtime_cells[0][0].fringe_left = nullptr
004374d9        (edi_1 - 0x3bfb0c)->runtime_cells[0][0].fringe_back = nullptr
004374dc        do while (j != 1)
004374de        i = i_3
004374de        i_3 -= 1
004374df        do while (i != 1)
004374e1        int32_t subgame_rebuild_selector = game->subgame_rebuild_selector
004374f1        if (subgame_rebuild_selector == 2 || subgame_rebuild_selector == 1)
004374fe        cache_music_file("music/mainmenu.ogg", 0, &g_blank_text)
00437503        g_game_base
00437516        int32_t eax_2 = load_landscape_script_by_name("Menubg.txt")
00437522        struct GameRoot* game_base_1 = g_game_base
00437535        change_backdrop(&game_base_1->backdrop, &game_base_1->unknown_000000[eax_2 * 0x124 + 0x106c7bc], 0)
0043754b        set_border_justify_centre(&g_game_base->border_manager, 0x41c80000)
00437550        int32_t level_mode = game->level_mode
00437555        struct SubSolution (* eax_6)[0x33]
00437555        if (level_mode == 0)
0043757e        eax_6 = &game->sub_high_score.postal_records
00437584        label_437584:
00437584        game->sub_high_score.active_record_bank = eax_6
0043758d        game->active_level_score = (eax_6 - 0x944150)->sub_high_score.time_trial_route_records[0].score
004375a1        __builtin_memcpy(&game->active_level_timer, eax_6 + 8, 0x18)
00437558        if (level_mode == 1)
00437567        eax_6 = &game->sub_high_score.survival_records
0043756d        game->sub_high_score.active_record_bank = eax_6
00437576        game->active_level_score = (eax_6 - 0x944150)->sub_high_score.time_trial_route_records[0].score
004375a1        __builtin_memcpy(&game->active_level_timer, eax_6 + 8, 0x18)
0043755d        if (level_mode == 4)
0043755f        eax_6 = &game->sub_high_score.time_trial_route_records
00437565        goto label_437584
004375a9        if (game->selected_level_record_persistent != 0)
004375b4        game->rate_or_level_arg.base_rate = game->selected_level_record->replay_speed_scalar_bits
004375bd        game->subgame_pause_gate = 0
004375c0        game->resume_requested = 0
004375c3        game->pause_fade = 0f
004375c6        game->pause_fade_step = 0.0333333351f
004375d2        game->subgame_state = 0
004375d5        game->times_up.state = 0
0043760b        game->top_score_widget = allocate_border(&g_game_base->border_manager)
00437611        struct tColour color
00437611        struct tColour* color_1 = set_color_rgba(&color, 1f, 1f, 1f, 0.0299999993f)
00437633        initialize_frontend_widget(game->top_score_widget, &__dos_header.e_cblp, "0", 0x14, 400f, 14f, color_1, 3, 300f)
00437643        game->top_score_widget->font_scale = 1.5f
00437653        game->top_score_widget->texture_layer = 7
0043765f        game->top_score_widget->text_buffer.raw[0] = 0
0043766a        if (game->level_mode == 0)
0043769c        game->lives_icon_widget = allocate_border(&g_game_base->border_manager)
004376a2        struct tColour* eax_12 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
004376bb        initialize_frontend_sprite_button(game->lives_icon_widget, 0x400800, 0x7a, 0f, 58f, eax_12, 0f, 4)
004376c6        hide_border_init(game->lives_icon_widget)
004376d1        game->lives_icon_widget->sprite_shadow_offset = 0f
00437702        game->lives_text_widget = allocate_border(&g_game_base->border_manager)
00437708        struct tColour* color_2 = set_color_rgba(&color, 1f, 1f, 1f, 0.0299999993f)
0043772a        initialize_frontend_widget(game->lives_text_widget, &__dos_header.e_cblp, "0", 0x14, 47f, 80f, color_2, 0, 0f)
00437735        hide_border_init(game->lives_text_widget)
00437740        int32_t i_1 = 0
00437742        int32_t i_2 = 0
00437746        struct FrontendWidget* (* esi_2)[0x9] = &game->life_stock_widgets
0043774c        __builtin_strncpy(&game->lives_text_widget->font_scale, "333?", 4)
00437781        (esi_2 - 0x35bb98)->life_stock_widgets[0] = allocate_border(&g_game_base->border_manager)
00437783        int32_t* eax_17
00437783        int32_t ecx_23
00437783        eax_17, ecx_23 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00437792        int32_t var_40_1 = ecx_23
004377ab        initialize_frontend_sprite_button((esi_2 - 0x35bb98)->life_stock_widgets[0], 0x400800, 0x7b, fconvert.s(float.t(i_2) * fconvert.t(24f) + fconvert.t(13f)), 430f, eax_17, 0f, 4)
004377b2        (esi_2 - 0x35bb98)->life_stock_widgets[0]->sprite_shadow_offset = 0f
004377ba        hide_border_init((esi_2 - 0x35bb98)->life_stock_widgets[0])
004377bf        i_1 += 1
004377c0        esi_2 = &(*esi_2)[1]
004377c6        i_2 = i_1
004377ca        do while (i_1 s< 9)
004377d1        int32_t level_mode_1 = game->level_mode
004377dc        if (game->sub_high_score.current_result_record.replay_mode_id != level_mode_1)
00437818        if (level_mode_1 != 4)
00437830        border_add_text_number(game->top_score_widget, 0)
0043781e        zero_timer_counters(&color)
004377f0        format_time_trial_string(&game->time_trial, &color)
00437802        rstrcpy_checked_ascii(&game->top_score_widget->text_buffer, 0x751478)
004377e1        if (level_mode_1 != 4)
00437830        border_add_text_number(game->top_score_widget, game->sub_high_score.current_result_record.score)
004377f0        format_time_trial_string(&game->time_trial, &game->sub_high_score.current_result_record.score_or_time)
00437802        rstrcpy_checked_ascii(&game->top_score_widget->text_buffer, 0x751478)
00437865        game->bottom_score_widget = allocate_border(&g_game_base->border_manager)
0043786b        struct tColour* color_3 = set_color_rgba(&color, 1f, 1f, 1f, 0.0299999993f)
0043788d        initialize_frontend_widget(game->bottom_score_widget, &__dos_header.e_cblp, "0", 0x14, 40f, 14f, color_3, 3, -71f)
00437898        game->bottom_score_widget->font_scale = 1.5f
004378a8        game->bottom_score_widget->texture_layer = 7
004378b4        game->bottom_score_widget->text_buffer.raw[0] = 0
004378c2        switch (game->level_mode)
004378d6        case 0
004378d6        border_add_text_number(game->bottom_score_widget, game->active_level_score)
004378ea        case 1
004378ea        border_add_text_number(game->bottom_score_widget, game->active_level_score)
00437921        case 2, 3
00437921        hide_border_init(game->bottom_score_widget)
0043792c        hide_border_init(game->top_score_widget)
004378fe        case 4
004378fe        format_time_trial_string(&game->time_trial, &game->active_level_timer)
00437911        rstrcpy_checked_ascii(&game->bottom_score_widget->text_buffer, 0x751478)
00437931        struct GameRoot* game_base_2 = g_game_base
00437941        if (game_base_2->__offset(0x4f2e0).b != 0 || game->level_mode == 7)
00437949        hide_border_init(game->bottom_score_widget)
00437954        hide_border_init(game->top_score_widget)
00437959        game_base_2 = g_game_base
00437964        if (game_base_2->players[0].high_score_entry_pending != 0)
00437964        return
0043796a        game_base_2->players[0].high_score_entry_pending = 0
00437980        g_game_base->players[0].selected_high_score_rank = 0
00437986        load_builtin_segment_definitions(&game->level_definition_scratch, &data_4a63d0)
00437991        set_matrix_identity(&game->player.body.transform)
004379a2        game->player.movement_mode_selector = 0
004379a8        game->player.game = game
004379ae        int32_t eax_25
004379ae        eax_25.b = game->player.body.transform.position.x.b
004379ae        eax_25:1.b = game->player.body.transform.position.x:1.b
004379ae        eax_25:2.b = game->player.body.transform.position.x:2.b
004379ae        eax_25:3.b = game->player.body.transform.position.x:3.b
004379b0        game->player.attachment_exit_pending = 0
004379b6        game->player.cached_camera_target_world.x = eax_25
004379b8        game->player.boost_one_tick = 0
004379c1        game->player.lives = 0
004379c7        game->player.cached_camera_target_world.y = game->player.body.transform.position.y
004379ca        float ecx_48
004379ca        ecx_48.b = game->player.body.transform.position.z.b
004379ca        ecx_48:1.b = game->player.body.transform.position.z:1.b
004379cd        game->player.cached_camera_target_world.z = ecx_48
004379df        game->player.body.bod.bod.list_flags &= 0xffffffdf
004379e5        initialize_warning(&game->player.warning)
004379ea        int32_t subgame_rebuild_selector_1 = game->subgame_rebuild_selector
004379fb        if (subgame_rebuild_selector_1 != 0 && subgame_rebuild_selector_1 != 3)
00437a07        if (game->selected_level_record_persistent == 0)
00437a18        switch (game->level_mode)
00437a22        case 0
00437a22        if (subgame_rebuild_selector_1 == 1)
00437a27        int32_t edx_16 = game->level_mode_arg + 1
00437a28        game->level_mode_arg = edx_16
00437a35        if (edx_16 s> g_runtime_config.highest_galaxy_route_index)
00437a46        g_runtime_config.highest_galaxy_route_index = edx_16
00437a4b        save_config_file("SnailMail.cfg", &g_runtime_config, 0xc4)
00437a56        g_runtime_config.landscape_backdrop_variant_selector = game->level_mode_arg
00437a22        goto label_437a62
00437a7c        case 1
00437a7c        initialize_challenge_setup_screen(&game->gui)
00437a83        reset_subgame(game)
00437a8f        return
00437a62        case 4
00437a62        label_437a62:
00437a62        initialize_galaxy(&game->galaxy)
00437a69        reset_subgame(game)
00437a75        return
00437a92        case 7
00437a92        game->subgame_state = 0
00437a95        reset_subgame(game)
00437aa1        return
00437aa7        report_errorf("Unknown game mode")
00437ab1        reset_subgame(game)
00437abd        return
00437ac7        game->rate_or_level_arg.base_rate = game->selected_level_record->replay_speed_scalar_bits
00437acc        reset_subgame(game)
00437ad8        return
