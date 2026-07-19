/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: build_subgame_level @ 0x437eb0 */

00437eb0        struct SubgameRuntime* game_1 = game
00437ec1        unhide_star_field(&g_game_base->star_manager)
00437ece        if (game->level_mode != 7)
00437ed7        unhide_gameplay_scores(game)
00437ed0        hide_gameplay_scores(game)
00437eef        int16_t x87control
00437eef        int32_t eax_3 = ftol(x87control, float.t(next_math_random_value()) * fconvert.t(0.000122070312f))
00437ef9        if (eax_3 u<= 4)
00437efb        char* path
00437efb        switch (eax_3)
00437f02        case 0
00437f02        void* __saved_ebp_1 = &g_blank_text
00437f07        int32_t var_18_1 = 0
00437f08        path = "music/1.ogg"
00437f0f        case 1
00437f0f        void* __saved_ebp_2 = &g_blank_text
00437f14        int32_t var_18_2 = 0
00437f15        path = "music/2.ogg"
00437f29        case 2, 4
00437f29        void* __saved_ebp_4 = &g_blank_text
00437f2e        int32_t var_18_4 = 0
00437f2f        path = "music/3.ogg"
00437f1c        case 3
00437f1c        void* __saved_ebp_3 = &g_blank_text
00437f21        int32_t var_18_3 = 0
00437f22        path = "music/4.ogg"
00437f34        cache_music_file(path, 0, &g_blank_text)
00437f3c        game->next_slug_voice_trigger_z = 50f
00437f4c        game->slug_voice_trigger_spacing_z = 100f
00437f56        initialize_enemy_manager(&game->enemy_manager)
00437f61        initialize_damage_gauge(&game->player.damage_gauge)
00437f77        initialize_sub_lazer_pool(&game->sub_lazers)
00437f82        initialize_salt_hazard_pool(&game->salt_hazards)
00437f8c        reset_voice_manager(&g_voice_manager)
00437fa0        int32_t __saved_ebp_16
00437fa0        int32_t edx
00437fa0        __saved_ebp_16, edx = load_frontend_level_by_mode_and_index(&game->level_definition, game->level_mode, level_index)
00437fb7        if (game->selected_level_record_active != 0 || game->selected_level_record_persistent != 0)
00438065        game->rate_or_level_arg.base_rate = game->selected_level_record->replay_speed_scalar.bits
00438071        game->level_mode = game->selected_level_record->replay_mode_id
0043807d        game->completion_bonus_y_source = game->selected_level_record->challenge_difficulty_value
00438089        game->completion_bonus_x_source = game->selected_level_record->challenge_speed_value
0043809b        game->challenge_difficulty_scalar = fconvert.s(float.t(game->selected_level_record->challenge_difficulty_value) * fconvert.t(0.00999999978f))
00437fbd        int32_t level_mode = game->level_mode
00437fc3        if (level_mode == 3)
00437fcb        game->rate_or_level_arg.base_rate = g_runtime_config.default_challenge_speed_slider
00437fdf        if (level_mode == 0 || level_mode == 4 || level_mode == 7)
00438030        if (game->level_definition.selected_speed.bits != 0xbf800000)
00438057        game->rate_or_level_arg.base_rate = fconvert.s(fconvert.t(game->level_definition.selected_speed.bits) * fconvert.t(0.00999999978f) * fconvert.t(0.900000036f) + fconvert.t(0.200000003f))
0043803a        game->rate_or_level_arg.base_rate = fconvert.s(calc_slider_to_rate(0f))
00437fe4        if (level_mode == 1)
00437fec        int32_t __saved_ebp_6 = __saved_ebp_16
00437ffd        game->rate_or_level_arg.base_rate = fconvert.s(calc_slider_to_rate(fconvert.s(float.t(g_runtime_config.completion_bonus_x_source) * fconvert.t(0.00999999978f))))
0043809b        game->challenge_difficulty_scalar = fconvert.s(float.t(g_runtime_config.completion_bonus_y_source) * fconvert.t(0.00999999978f))
0043800e        if (level_mode == 2)
00438021        game->rate_or_level_arg.base_rate = fconvert.s(calc_slider_to_rate(g_runtime_config.default_challenge_speed_slider))
004380b0        if (game->selected_level_record_active != 0 || game->selected_level_record_persistent != 0)
0043812a        struct SubSolution* selected_level_record = game->selected_level_record
00438130        float edx_5
00438130        edx_5.b = selected_level_record->garbage_frequency.bits.b
00438130        edx_5:1.b = selected_level_record->garbage_frequency.bits.__offset(0x1).b
00438130        edx_5:2.b = selected_level_record->garbage_frequency.bits.__offset(0x2).b
00438130        edx_5:3.b = selected_level_record->garbage_frequency.bits.__offset(0x3).b
00438136        game->garbage_frequency = edx_5
00438148        game->salt_frequency = game->selected_level_record->salt_frequency.bits
004380b2        int32_t level_mode_1 = game->level_mode
004380cb        if (level_mode_1 == 2 || level_mode_1 == 3 || level_mode_1 == 0 || level_mode_1 == 4 || level_mode_1 == 7)
00438110        game->garbage_frequency = fconvert.s(fconvert.t(game->level_definition.garbage_frequency) * fconvert.t(0.00999999978f))
00438122        game->salt_frequency = fconvert.s(fconvert.t(game->level_definition.salt_frequency) * fconvert.t(0.00999999978f))
004380d0        if (level_mode_1 == 1)
004380e4        game->garbage_frequency = fconvert.s(float.t(g_runtime_config.completion_bonus_y_source) * fconvert.t(0.00999999978f) * fconvert.t(0.800000012f))
004380fc        game->salt_frequency = fconvert.s(float.t(g_runtime_config.completion_bonus_y_source) * fconvert.t(0.00999999978f) * fconvert.t(0.800000012f))
00438154        initialize_track_parcel_slots(&game->parcel_manager)
00438166        if (g_game_base->intro.hide_for_replay_latch == 1)
0043816e        hide_border_init(game->top_score_widget)
00438179        hide_border_init(game->bottom_score_widget)
00438181        int16_t x87control_1 = rebuild_track_runtime_from_segments(game, level_index)
0043818d        if (game->level_definition.track_texture_set != 5)
00438255        activate_landscape_entry(&game->landscape_manager, game->level_definition.landscape_script_index)
00438193        int32_t __saved_ebp_10 = 0
004381a1        int32_t eax_9 = ftol(x87control_1, random_float_below(4f))
004381a9        int32_t script_index
004381a9        if (eax_9 u> 3)
00438200        script_index = level_index
004381ab        switch (eax_9)
004381b2        case 0
004381f9        script_index = load_landscape_script_by_name(&g_game_base->subgame.landscape_manager, "SpaceBluesWhorl.txt")
004381ca        case 1
004381ca        script_index = load_landscape_script_by_name(&g_game_base->subgame.landscape_manager, "SpaceGreenWarp.txt")
004381e2        case 2
004381e2        script_index = load_landscape_script_by_name(&g_game_base->subgame.landscape_manager, "SpacePurple.txt")
004381e9        case 3
004381f9        script_index = load_landscape_script_by_name(&g_game_base->subgame.landscape_manager, "SpaceRed.txt")
0043820b        activate_landscape_entry(&game->landscape_manager, script_index)
00438210        int32_t __saved_ebp_13 = 0
00438216        long double st0_5 = random_float_below(1f)
0043821b        long double temp1_1 = fconvert.t(0.5f)
0043821b        st0_5 - temp1_1
00438229        if ((((st0_5 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(st0_5, temp1_1) ? 1 : 0) << 0xa | (st0_5 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
00438240        g_game_base->backdrop.pending_flip = 0
00438231        g_game_base->backdrop.pending_flip = 1
00438273        if ((0x200 & game->banners.slots[0].bod.bod.list_flags) == 0)
00438284        game->banners.slots[0].bod.bod.list_prev = &game->track_body_list_head
0043828a        game->banners.slots[0].bod.bod.list_next = game->track_body_list_head.bod.list_next
0043828d        game->track_body_list_head.bod.list_next = &game->banners
00438290        struct BodNode* list_next = game->banners.slots[0].bod.bod.list_next
00438295        if (list_next != 0)
00438297        list_next->list_prev.b = (&game->banners).b
00438297        list_next->list_prev:1.b = (&game->banners):1.b
0043829a        game->banners.slots[0].bod.bod.list_flags |= 0x200
0043827a        report_errorf("List ADDafter")
0043829d        game->banners.slots[0].bod.position.z = 0f
004382a3        game->banners.slots[0].bod.position.y = 0f
004382a9        game->banners.slots[0].bod.position.x = 0
004382bf        game->banners.slots[0].owner_player = &game->player
004382c8        game->banners.slots[0].bod.position.z = fconvert.s(float.t(game->first_block_row_count))
004382d9        game->banners.slots[0].bod.bod.list_flags &= 0xffffffdf
004382df        game->banners.slots[0].bod.color.a = 0.999000013f
004382ef        if ((0x200 & game->banners.slots[1].bod.bod.list_flags) == 0)
00438300        game->banners.slots[1].bod.bod.list_prev = &game->track_body_list_head
00438306        game->banners.slots[1].bod.bod.list_next = game->track_body_list_head.bod.list_next
00438309        game->track_body_list_head.bod.list_next = &game->banners.slots[1].bod.bod
0043830c        struct BodNode* list_next_1 = game->banners.slots[1].bod.bod.list_next
00438311        if (list_next_1 != 0)
00438313        list_next_1->list_prev.b = (&game->banners.slots[1].bod.bod).b
00438313        list_next_1->list_prev:1.b = (&game->banners.slots[1].bod.bod):1.b
00438316        game->banners.slots[1].bod.bod.list_flags |= 0x200
004382f6        report_errorf("List ADDafter")
00438319        game->banners.slots[1].bod.position.z = 0f
0043831f        game->banners.slots[1].bod.position.y = 0f
00438325        game->banners.slots[1].bod.position.x = 0
0043832b        uint32_t list_flags = game->banners.slots[1].bod.bod.list_flags
0043833a        list_flags.b &= 0xdf
0043833c        game->banners.slots[1].owner_player = &game->player
00438342        game->banners.slots[1].bod.bod.list_flags = list_flags
00438348        game->banners.slots[1].bod.position.z = fconvert.s(float.t(game->completion_row_start))
0043834e        game->banners.slots[1].bod.color.a = 0.999000013f
00438354        game->track_state_latch = 0
0043835a        game->replay_update_cursor = 0
00438360        game->times_up.state = 0
00438366        game->subgame_state = 2
00438378        g_game_base->render_skip_count = 1
00438389        release_mouse_cursor(&g_game_base->players[0].mouse_cursor)
00438391        game->player.movement_mode_selector = 1
00438397        game->player.steering_mode_selector = 0
0043839d        initialize_subgoldy(&game->player, 1)
004383b5        if ((0x200 & game->player.presentation.jetpack_channel.body.bod.bod.list_flags) == 0)
004383cc        struct BodNode** active_first_ref_jetpack = &g_game_base->active_bod_list.first
004383d2        struct BodNode* active_first_jetpack
004383d2        active_first_jetpack.b = *active_first_ref_jetpack
004383d2        active_first_jetpack:1.b = *(active_first_ref_jetpack + 1)
004383d2        active_first_jetpack:2.b = *(active_first_ref_jetpack + 2)
004383d2        active_first_jetpack:3.b = *(active_first_ref_jetpack + 3)
004383d6        if (active_first_jetpack != 0)
004383e4        active_first_jetpack->list_prev = &game->player.presentation.jetpack_channel
004383e7        struct BodNode* active_first_link_jetpack
004383e7        active_first_link_jetpack.b = *active_first_ref_jetpack
004383e7        active_first_link_jetpack:1.b = *(active_first_ref_jetpack + 1)
004383e7        active_first_link_jetpack:2.b = *(active_first_ref_jetpack + 2)
004383e7        active_first_link_jetpack:3.b = *(active_first_ref_jetpack + 3)
004383ec        active_first_link_jetpack->list_prev->list_next = active_first_link_jetpack
004383ef        struct BodNode* active_first_reload_jetpack
004383ef        active_first_reload_jetpack.b = *active_first_ref_jetpack
004383ef        active_first_reload_jetpack:1.b = *(active_first_ref_jetpack + 1)
004383ef        active_first_reload_jetpack:2.b = *(active_first_ref_jetpack + 2)
004383ef        active_first_reload_jetpack:3.b = *(active_first_ref_jetpack + 3)
004383f6        struct BodNode* active_new_first_jetpack = active_first_reload_jetpack->list_prev
004383f9        *active_first_ref_jetpack = active_new_first_jetpack.b
004383f9        *(active_first_ref_jetpack + 1) = active_new_first_jetpack:1.b
004383f9        *(active_first_ref_jetpack + 2) = active_new_first_jetpack:2.b
004383f9        *(active_first_ref_jetpack + 3) = active_new_first_jetpack:3.b
004383fb        active_new_first_jetpack->list_prev = nullptr
004383d8        *active_first_ref_jetpack = (&game->player.presentation.jetpack_channel).b
004383d8        *(active_first_ref_jetpack + 1) = (&game->player.presentation.jetpack_channel):1.b
004383d8        *(active_first_ref_jetpack + 2) = (&game->player.presentation.jetpack_channel):2.b
004383d8        *(active_first_ref_jetpack + 3) = (&game->player.presentation.jetpack_channel):3.b
004383da        game->player.presentation.jetpack_channel.body.bod.bod.list_prev = nullptr
004383dd        struct BodNode* active_first_empty_jetpack
004383dd        active_first_empty_jetpack.b = *active_first_ref_jetpack
004383dd        active_first_empty_jetpack:1.b = *(active_first_ref_jetpack + 1)
004383dd        active_first_empty_jetpack:2.b = *(active_first_ref_jetpack + 2)
004383dd        active_first_empty_jetpack:3.b = *(active_first_ref_jetpack + 3)
004383df        active_first_empty_jetpack->list_next = nullptr
004383fe        game->player.presentation.jetpack_channel.body.bod.bod.list_flags |= 0x200
004383bc        report_errorf("List ADD")
0043840f        if ((0x200 & game->player.presentation.weapon_channels[0].body.bod.bod.list_flags) == 0)
00438425        struct BodNode** active_first_ref_weapon_0 = &g_game_base->active_bod_list.first
0043842a        struct BodNode* active_first_weapon_0 = *active_first_ref_weapon_0
0043842e        if (active_first_weapon_0 != 0)
0043843c        active_first_weapon_0->list_prev = &game->player.presentation.weapon_channels
0043843f        struct BodNode* active_first_link_weapon_0 = *active_first_ref_weapon_0
00438444        active_first_link_weapon_0->list_prev->list_next = active_first_link_weapon_0
0043844e        struct BodNode* active_new_first_weapon_0 = (*active_first_ref_weapon_0)->list_prev
00438451        *active_first_ref_weapon_0 = active_new_first_weapon_0
00438453        active_new_first_weapon_0->list_prev = nullptr
00438430        *active_first_ref_weapon_0 = &game->player.presentation.weapon_channels
00438432        game->player.__offset(0x2fd8).b = nullptr
00438432        game->player.__offset(0x2fd9).b = 0
00438437        (*active_first_ref_weapon_0)->list_next = nullptr
00438456        game->player.presentation.weapon_channels[0].body.bod.bod.list_flags |= 0x200
00438416        report_errorf("List ADD")
00438467        if ((0x200 & game->player.presentation.weapon_channels[1].body.bod.bod.list_flags) == 0)
0043847d        struct BodNode** active_first_ref_weapon_1 = &g_game_base->active_bod_list.first
00438482        struct BodNode* active_first_weapon_1 = *active_first_ref_weapon_1
00438486        if (active_first_weapon_1 != 0)
00438494        active_first_weapon_1->list_prev = &game->player.presentation.weapon_channels[1]
00438497        struct BodNode* active_first_link_weapon_1 = *active_first_ref_weapon_1
0043849c        active_first_link_weapon_1->list_prev->list_next = active_first_link_weapon_1
004384a6        struct BodNode* active_new_first_weapon_1 = (*active_first_ref_weapon_1)->list_prev
004384a9        *active_first_ref_weapon_1 = active_new_first_weapon_1
004384ab        active_new_first_weapon_1->list_prev = nullptr
00438488        *active_first_ref_weapon_1 = &game->player.presentation.weapon_channels[1]
0043848a        game->player.presentation.weapon_channels[1].body.bod.bod.list_prev.b = nullptr
0043848a        game->player.presentation.weapon_channels[1].body.bod.bod.list_prev:1.b = 0
0043848f        (*active_first_ref_weapon_1)->list_next = nullptr
004384ae        game->player.presentation.weapon_channels[1].body.bod.bod.list_flags |= 0x200
0043846e        report_errorf("List ADD")
004384bf        if ((0x200 & game->player.presentation.weapon_channels[2].body.bod.bod.list_flags) == 0)
004384d5        struct BodNode** active_first_ref_weapon_2 = &g_game_base->active_bod_list.first
004384da        struct BodNode* active_first_weapon_2 = *active_first_ref_weapon_2
004384de        if (active_first_weapon_2 != 0)
004384ec        active_first_weapon_2->list_prev = &game->player.presentation.weapon_channels[2]
004384ef        struct BodNode* active_first_link_weapon_2 = *active_first_ref_weapon_2
004384f4        active_first_link_weapon_2->list_prev->list_next = active_first_link_weapon_2
004384fe        struct BodNode* active_new_first_weapon_2 = (*active_first_ref_weapon_2)->list_prev
00438501        *active_first_ref_weapon_2 = active_new_first_weapon_2
00438503        active_new_first_weapon_2->list_prev = nullptr
004384e0        *active_first_ref_weapon_2 = &game->player.presentation.weapon_channels[2]
004384e2        game->player.presentation.weapon_channels[2].body.bod.bod.list_prev.b = nullptr
004384e2        game->player.presentation.weapon_channels[2].body.bod.bod.list_prev:1.b = 0
004384e7        (*active_first_ref_weapon_2)->list_next = nullptr
00438506        game->player.presentation.weapon_channels[2].body.bod.bod.list_flags |= 0x200
004384c6        report_errorf("List ADD")
00438517        if ((0x200 & game->player.presentation.invincible_shell.body.bod.bod.list_flags) == 0)
0043852d        struct BodNode** active_first_ref_invincible_shell = &g_game_base->active_bod_list.first
00438532        struct BodNode* active_first_invincible_shell = *active_first_ref_invincible_shell
00438536        if (active_first_invincible_shell != 0)
00438544        active_first_invincible_shell->list_prev = &game->player.presentation.invincible_shell
00438547        struct BodNode* active_first_link_invincible_shell = *active_first_ref_invincible_shell
0043854c        active_first_link_invincible_shell->list_prev->list_next = active_first_link_invincible_shell
00438556        struct BodNode* active_new_first_invincible_shell = (*active_first_ref_invincible_shell)->list_prev
00438559        *active_first_ref_invincible_shell = active_new_first_invincible_shell
0043855b        active_new_first_invincible_shell->list_prev = nullptr
00438538        *active_first_ref_invincible_shell = &game->player.presentation.invincible_shell
0043853a        game->player.presentation.invincible_shell.body.bod.bod.list_prev.b = nullptr
0043853a        game->player.presentation.invincible_shell.body.bod.bod.list_prev:1.b = 0
0043853f        (*active_first_ref_invincible_shell)->list_next = nullptr
0043855e        game->player.presentation.invincible_shell.body.bod.bod.list_flags |= 0x200
0043851e        report_errorf("List ADD")
00438561        uint32_t list_flags_1 = game->player.presentation.invincible_shell.body.bod.bod.list_flags
00438567        list_flags_1.b |= 0x80
0043856a        game->player.presentation.invincible_shell.body.bod.bod.list_flags = list_flags_1
0043857e        if ((0x200 & game->player.presentation.body.bod.bod.list_flags) == 0)
00438594        struct BodNode** active_first_ref_presentation = &g_game_base->active_bod_list.first
00438599        struct BodNode* active_first_presentation = *active_first_ref_presentation
0043859d        if (active_first_presentation != 0)
004385ab        active_first_presentation->list_prev = &game->player.presentation
004385ae        struct BodNode* active_first_link_presentation = *active_first_ref_presentation
004385b3        active_first_link_presentation->list_prev->list_next = active_first_link_presentation
004385bd        struct BodNode* active_new_first_presentation = (*active_first_ref_presentation)->list_prev
004385c0        *active_first_ref_presentation = active_new_first_presentation
004385c2        active_new_first_presentation->list_prev = nullptr
0043859f        *active_first_ref_presentation = &game->player.presentation
004385a1        game->player.presentation.body.bod.bod.list_prev.b = nullptr
004385a1        game->player.presentation.body.bod.bod.list_prev:1.b = 0
004385a6        (*active_first_ref_presentation)->list_next = nullptr
004385c5        game->player.presentation.body.bod.bod.list_flags |= 0x200
00438585        report_errorf("List ADD")
004385cb        if ((game->player.body.bod.bod.list_flags & 0x200) == 0)
004385e1        struct BodNode** active_first_ref_player = &g_game_base->active_bod_list.first
004385e6        struct BodNode* active_first_player = *active_first_ref_player
004385ea        if (active_first_player != 0)
004385f8        active_first_player->list_prev.b = (&game->player).b
004385f8        active_first_player->list_prev:1.b = (&game->player):1.b
004385fb        struct BodNode* active_first_link_player = *active_first_ref_player
004385fd        struct BodNode* active_new_first_player
004385fd        active_new_first_player.b = active_first_link_player->list_prev.b
004385fd        active_new_first_player:1.b = active_first_link_player->list_prev:1.b
00438600        active_new_first_player->list_next = active_first_link_player
00438603        struct BodNode* active_first_reload_player = *active_first_ref_player
00438605        struct BodNode* active_new_first_player_reloaded
00438605        active_new_first_player_reloaded.b = active_first_reload_player->list_prev.b
00438605        active_new_first_player_reloaded:1.b = active_first_reload_player->list_prev:1.b
00438608        *active_first_ref_player = active_new_first_player_reloaded
0043860a        active_new_first_player_reloaded->list_prev.b = nullptr
0043860a        active_new_first_player_reloaded->list_prev:1.b = 0
004385ec        *active_first_ref_player = &game->player
004385ee        game->player.body.bod.bod.list_prev = nullptr
004385f3        (*active_first_ref_player)->list_next = nullptr
0043860d        game->player.body.bod.bod.list_flags |= 0x200
004385d2        report_errorf("List ADD")
00438616        initialize_slug_voice_manager(&game->slug_voice_manager)
0043862f        if ((0x200 & game->barrier.bod.bod.list_flags) == 0)
00438640        game->barrier.bod.bod.list_prev = &game->barrier_sub_lazer_list_head
00438646        game->barrier.bod.bod.list_next = game->barrier_sub_lazer_list_head.bod.list_next
00438649        game->barrier_sub_lazer_list_head.bod.list_next = &game->barrier
0043864c        struct BodNode* list_next_2 = game->barrier.bod.bod.list_next
00438651        if (list_next_2 != 0)
00438653        list_next_2->list_prev.b = (&game->barrier).b
00438653        list_next_2->list_prev:1.b = (&game->barrier):1.b
00438656        game->barrier.bod.bod.list_flags |= 0x200
00438636        report_errorf("List ADDafter")
0043865c        game->barrier.owner_player = &game->player
00438665        if (game->level_mode == 0)
00438673        int32_t __saved_ebp_15 = game->level_definition.parcel_count
00438680        sprintf(&game->lives_text_widget->text_buffer, "0/%i")
0043868e        unhide_border_init(game->lives_icon_widget)
00438699        unhide_border_init(game->lives_text_widget)
004386aa        set_input_controller_pointer_authored_xy(0, 320f, 240f)
004386b7        set_input_controller_pointer_authored_xy(1, 320f, 240f)
004386c1        game->player.track_z_offset = 320f
004386c7        game->player.track_z_anchor = 320f
004386cd        game->scan_reset = 1
004386d0        calc_subgame_rate(game)
004386d9        return
