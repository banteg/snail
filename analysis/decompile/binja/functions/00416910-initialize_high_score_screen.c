/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_high_score_screen @ 0x416910 */

0041691e        high_score->selected_bank = selected_bank
0041692b        high_score->selected_rank = selected_rank
0041692e        if (selected_rank != 0xffffffff)
00416936        high_score->entering_name = 1
00416930        high_score->entering_name = 0
00416946        hide_star_field(&g_game_base->star_manager)
00416957        hide_gameplay_scores(&g_game_base->subgame)
00416968        cache_music_file("music/mainmenu.ogg", 0, &g_blank_text)
0041696d        g_game_base
00416980        int32_t eax_2 = load_landscape_script_by_name("Menubg.txt")
0041698d        struct GameRoot* game_base_1 = g_game_base
004169a0        change_backdrop(&game_base_1->backdrop, &game_base_1->unknown_000000[eax_2 * 0x124 + 0x106c7bc], 0)
004169b6        set_border_justify_centre(&g_game_base->border_manager, 25f)
004169c6        capture_mouse_cursor(&g_game_base->players[0].mouse_cursor)
004169dc        high_score->title_widget = allocate_border(&g_game_base->border_manager)
004169df        int32_t selected_bank_1 = high_score->selected_bank
004169e5        float var_c4
004169e5        struct tColour color_2
004169e5        struct tColour color_3
004169e5        if (selected_bank_1 == 0)
00416a66        struct tColour* color_14 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00416a7f        initialize_frontend_widget(high_score->title_widget, 0, "Postal High Scores", 0x17, 0f, 64f, color_14, 2, 0f)
00416a84        struct GameRoot* game_base_2 = g_game_base
00416a8f        game_base_2->subgame.sub_high_score.active_record_bank = &game_base_2->subgame.sub_high_score.postal_records
00416a9b        g_game_base->subgame.sub_high_score.active_record_count = 0xa
00416aa5        var_c4 = 27f
004169e8        if (selected_bank_1 == 1)
00416a0a        struct tColour* color_13 = set_color_rgba(&color_3, 1f, 1f, 1f, 1f)
00416a23        initialize_frontend_widget(high_score->title_widget, 0, "Challenge High Scores", 0x17, 0f, 64f, color_13, 2, 0f)
00416a28        struct GameRoot* game_base_3 = g_game_base
00416a33        game_base_3->subgame.sub_high_score.active_record_bank = &game_base_3->subgame.sub_high_score.survival_records
00416a3e        g_game_base->subgame.sub_high_score.active_record_count = 0xa
00416aa5        var_c4 = 27f
00416ab2        if (high_score->entering_name != 0)
00416ac2        rstrcpy_checked_ascii(&high_score->title_widget->text_buffer, "Enter your name here!")
00416acd        layout_frontend_widget(high_score->title_widget)
00416ad3        int32_t ebx = 0
00416ad5        int32_t i = 0
00416ad8        int32_t var_cc = 0
00416adc        int32_t i_1 = 0
00416ae0        struct FrontendWidget* (* esi)[0xa] = &high_score->name_row_widgets
00417043        struct tColour color_1
00417043        struct tColour color_4
00416ae3        (esi - 0x7c)->replay_row_widgets[0] = 0
00416aed        int32_t ecx_17 = 0
00416af1        ecx_17.b = ebx != high_score->selected_rank
00416af5        int32_t ecx_19 = (ecx_17 - 1) & 2
00416afa        struct GameRoot* game_base_4 = g_game_base
00416b0a        if (*(game_base_4->subgame.sub_high_score.active_record_bank + i) == 1)
00416b10        int32_t selected_bank_2 = high_score->selected_bank
00416b16        if (selected_bank_2 == 0)
00416d79        float y_1 = fconvert.s(float.t(var_cc) * fconvert.t(var_c4) + fconvert.t(111f))
00416da4        (esi - 0x7c)->row_background_widgets[0] = allocate_border(&game_base_4->border_manager)
00416da7        struct tColour color_7
00416da7        struct tColour* color_20 = set_color_rgba(&color_7, 1f, 1f, 1f, 1f)
00416dc6        initialize_frontend_widget((esi - 0x7c)->row_background_widgets[0], ecx_19 | 0x20000000, "                                               ", 0x16, 0f, y_1, color_20, 1, -228f)
00416e00        (esi - 0x7c)->rank_row_widgets[0] = allocate_border(&g_game_base->border_manager)
00416e03        uint32_t widget_flags_3 = ecx_19 | 0x20400000
00416e09        struct tColour color_11
00416e09        struct tColour* color_21 = set_color_rgba(&color_11, 1f, 1f, 1f, 1f)
00416e21        initialize_frontend_widget((esi - 0x7c)->rank_row_widgets[0], widget_flags_3, &g_blank_text, 0x16, 0f, y_1, color_21, 1, -222f)
00416e2f        border_add_text_number((esi - 0x7c)->rank_row_widgets[0], var_cc + 1)
00416e37        layout_frontend_widget((esi - 0x7c)->rank_row_widgets[0])
00416e6f        (esi - 0x7c)->name_row_widgets[0] = allocate_border(&g_game_base->border_manager)
00416e71        struct tColour color_9
00416e71        struct tColour* color_22 = set_color_rgba(&color_9, 1f, 1f, 1f, 1f)
00416e97        initialize_frontend_widget((esi - 0x7c)->name_row_widgets[0], widget_flags_3, &g_game_base->subgame.sub_high_score.active_record_bank->player_name[i_1], 0x16, 0f, y_1, color_22, 1, -180f)
00416ea5        if (var_cc == high_score->selected_rank)
00416eb2        border_input_text_init((esi - 0x7c)->name_row_widgets[0], 0x10, &g_runtime_config.last_entered_player_name, 0x10)
00416eb7        struct FrontendWidget* eax_37 = (esi - 0x7c)->name_row_widgets[0]
00416eb9        enum FrontendWidgetFlag widget_flags_1 = eax_37->widget_flags
00416ebf        widget_flags_1:1.b |= 0x20
00416ec2        eax_37->widget_flags = widget_flags_1
00416eca        layout_frontend_widget((esi - 0x7c)->name_row_widgets[0])
00416f02        (esi - 0x7c)->score_row_widgets[0] = allocate_border(&g_game_base->border_manager)
00416f05        struct tColour color_6
00416f05        struct tColour* color_23 = set_color_rgba(&color_6, 1f, 1f, 1f, 1f)
00416f1d        initialize_frontend_widget((esi - 0x7c)->score_row_widgets[0], widget_flags_3, &g_blank_text, 0x16, 0f, y_1, color_23, 3, 160f)
00416f3a        border_add_text_number((esi - 0x7c)->score_row_widgets[0], *(&g_game_base->subgame.sub_high_score.active_record_bank->score + i_1))
00416f42        layout_frontend_widget((esi - 0x7c)->score_row_widgets[0])
00416f7a        (esi - 0x7c)->replay_row_widgets[0] = allocate_border(&g_game_base->border_manager)
00416f7d        struct tColour color_8
00416f7d        struct tColour* color_24 = set_color_rgba(&color_8, 1f, 1f, 1f, 1f)
00416f9b        initialize_frontend_widget((esi - 0x7c)->replay_row_widgets[0], ecx_19 | 0x20000014, "Replay", 0x16, 0f, y_1, color_24, 2, 125f)
00416fa3        hide_border_init((esi - 0x7c)->replay_row_widgets[0])
00416b1d        if (selected_bank_2 == 1)
00416b37        float y = fconvert.s(float.t(var_cc) * fconvert.t(var_c4) + fconvert.t(111f))
00416b5f        (esi - 0x7c)->row_background_widgets[0] = allocate_border(&game_base_4->border_manager)
00416b62        struct tColour* color_15 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00416b82        initialize_frontend_widget((esi - 0x7c)->row_background_widgets[0], ecx_19 | 0x20000000, "                                           ", 0x16, 0f, y, color_15, 1, -228f)
00416bb9        (esi - 0x7c)->rank_row_widgets[0] = allocate_border(&g_game_base->border_manager)
00416bbc        uint32_t widget_flags_2 = ecx_19 | 0x20400000
00416bc2        struct tColour* color_16 = set_color_rgba(&color_3, 1f, 1f, 1f, 1f)
00416bda        initialize_frontend_widget((esi - 0x7c)->rank_row_widgets[0], widget_flags_2, &g_blank_text, 0x16, 0f, y, color_16, 1, -222f)
00416be8        border_add_text_number((esi - 0x7c)->rank_row_widgets[0], var_cc + 1)
00416bf0        layout_frontend_widget((esi - 0x7c)->rank_row_widgets[0])
00416c28        (esi - 0x7c)->name_row_widgets[0] = allocate_border(&g_game_base->border_manager)
00416c2a        struct tColour color_10
00416c2a        struct tColour* color_17 = set_color_rgba(&color_10, 1f, 1f, 1f, 1f)
00416c51        initialize_frontend_widget((esi - 0x7c)->name_row_widgets[0], widget_flags_2, &g_game_base->subgame.sub_high_score.active_record_bank->player_name[i_1], 0x16, 0f, y, color_17, 1, -180f)
00416c5f        if (var_cc == high_score->selected_rank)
00416c6c        border_input_text_init((esi - 0x7c)->name_row_widgets[0], 0x10, &g_runtime_config.last_entered_player_name, 0x10)
00416c71        struct FrontendWidget* eax_19 = (esi - 0x7c)->name_row_widgets[0]
00416c73        enum FrontendWidgetFlag widget_flags = eax_19->widget_flags
00416c79        widget_flags:1.b |= 0x20
00416c7c        eax_19->widget_flags = widget_flags
00416c84        layout_frontend_widget((esi - 0x7c)->name_row_widgets[0])
00416cb8        (esi - 0x7c)->score_row_widgets[0] = allocate_border(&g_game_base->border_manager)
00416cbb        struct tColour color_5
00416cbb        struct tColour* color_18 = set_color_rgba(&color_5, 1f, 1f, 1f, 1f)
00416cd3        initialize_frontend_widget((esi - 0x7c)->score_row_widgets[0], widget_flags_2, &g_blank_text, 0x16, 0f, y, color_18, 3, 125f)
00416cf0        border_add_text_number((esi - 0x7c)->score_row_widgets[0], *(&g_game_base->subgame.sub_high_score.active_record_bank->score + i_1))
00416cf8        layout_frontend_widget((esi - 0x7c)->score_row_widgets[0])
00416d2f        (esi - 0x7c)->replay_row_widgets[0] = allocate_border(&g_game_base->border_manager)
00416d32        struct tColour color_12
00416d32        struct tColour* color_19 = set_color_rgba(&color_12, 1f, 1f, 1f, 1f)
00416d50        initialize_frontend_widget((esi - 0x7c)->replay_row_widgets[0], ecx_19 | 0x20000014, "Replay", 0x16, 0f, y, color_19, 2, 170f)
00416d5a        if (high_score->entering_name != 0)
00416fa3        hide_border_init((esi - 0x7c)->replay_row_widgets[0])
00416fa8        ebx = var_cc
00416faf        if ((ebx.b & 1) != 0)
00416fc9        struct tColour* eax_43 = set_color_rgba(&color_4, 0.329411775f, 0.184313729f, 0.419607848f, 0.699999988f)
00416fd3        struct tColour* ecx_80 = &(esi - 0x7c)->row_background_widgets[0]->idle_fill_color
00416fe8        ecx_80->r = eax_43->r
00416ff2        ecx_80->g = eax_43->g
00416ff8        ecx_80->b = eax_43->b
00416ffb        float a = eax_43->a
00416ffe        ecx_80->a.b = a.b
00416ffe        ecx_80->a:1.b = a:1.b
00416ffe        ecx_80->a:2.b = a:2.b
00416ffe        ecx_80->a:3.b = a:3.b
00417005        struct tColour* eax_44 = set_color_rgba(&color_1, 0.329411775f, 0.184313729f, 0.419607848f, 0.699999988f)
0041700f        struct tColour* ecx_83 = &(esi - 0x7c)->replay_row_widgets[0]->idle_fill_color
00417015        ecx_83->r = eax_44->r
0041701a        ecx_83->g = eax_44->g
00417020        ecx_83->b = eax_44->b
00417023        float a_1 = eax_44->a
00417026        ecx_83->a.b = a_1.b
00417026        ecx_83->a:1.b = a_1:1.b
00417026        ecx_83->a:2.b = a_1:2.b
00417026        ecx_83->a:3.b = a_1:3.b
0041702d        ebx += 1
0041702e        i = i_1 + 0x1fac0
00417033        esi = &(*esi)[1]
0041703b        var_cc = ebx
0041703f        i_1 = i
00417043        do while (i s< 0x13cb80)
00417060        float y_2 = fconvert.s(fconvert.t(var_c4) * fconvert.t(10f) + fconvert.t(111f))
00417064        if (high_score->entering_name != 0)
0041709a        high_score->cancel_name_button = allocate_border(&g_game_base->border_manager)
0041709d        struct tColour* color_25 = set_color_rgba(&color_1, 1f, 1f, 1f, 1f)
004170b9        initialize_frontend_widget(high_score->cancel_name_button, 0x20000014, "Cancel", 0x17, 0f, y_2, color_25, 2, -110f)
004170c3        set_frontend_widget_shortcut_key(high_score->cancel_name_button, 0xb)
004170f8        high_score->submit_name_button = allocate_border(&g_game_base->border_manager)
004170fb        struct tColour* color_26 = set_color_rgba(&color_1, 1f, 1f, 1f, 1f)
00417113        initialize_frontend_widget(high_score->submit_name_button, 0x20000014, "Submit", 0x17, 0f, y_2, color_26, 2, 55f)
0041711d        set_frontend_widget_shortcut_key(high_score->submit_name_button, 5)
0041712a        return
0041715c        high_score->back_button = allocate_border(&g_game_base->border_manager)
0041715f        struct tColour* color_27 = set_color_rgba(&color_1, 1f, 1f, 1f, 1f)
0041717b        initialize_frontend_widget(high_score->back_button, 0x20000014, "Back", 0x17, 0f, y_2, color_27, 2, -132f)
00417191        high_score->bank_toggle_button = allocate_border(&g_game_base->border_manager)
00417194        int32_t selected_bank_3 = high_score->selected_bank
0041719a        struct tColour* color
0041719a        if (selected_bank_3 == 0)
004171d0        int32_t __saved_ebx_2 = 0x42040000
004171d5        int32_t __saved_edi_3 = 2
004171f4        color = set_color_rgba(&color_4, 1f, 1f, 1f, 1f)
004171f6        int32_t var_ec_12 = 0
004171f8        int32_t var_f0_12 = 0x17
00417207        initialize_frontend_widget(high_score->bank_toggle_button, 0x20000014, "Challenge Scores", 0x17, 0f, y_2, color, 2, 33f)
0041719d        if (selected_bank_3 == 1)
0041719f        int32_t __saved_ebx_1 = 0x42040000
004171a4        int32_t __saved_edi_2 = 2
004171c3        color = set_color_rgba(&color_1, 1f, 1f, 1f, 1f)
004171c5        int32_t var_ec_11 = 0
004171c7        int32_t var_f0_11 = 0x17
00417207        initialize_frontend_widget(high_score->bank_toggle_button, 0x20000014, "Postal Scores", 0x17, 0f, y_2, color, 2, 33f)
00417214        return
