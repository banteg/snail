/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_new_game_menu @ 0x417eb0 */

00417eb0        struct Intro* intro_1 = intro
00417ed6        int16_t x87control
00417ed6        if (read_pressed_text_input_key_code().b != 0 || ((g_game_base->players[0].game_input->input.pressed_buttons).w:1.b & 0x40) != 0)
00417edd        bool cond:1_1 = intro->hide_for_replay_latch != 1
00417edf        intro->replay_probe_progress = 0f
00417ee2        if (not(cond:1_1))
00417ee7        unhide_border_init(intro->postal_button)
00417eef        unhide_border_init(intro->tutorial_button)
00417ef7        unhide_border_init(intro->time_trial_button)
00417eff        unhide_border_init(intro->challenge_button)
00417f07        unhide_border_init(intro->help_button)
00417f0f        unhide_border_init(intro->back_button)
00417f20        x87control = capture_mouse_cursor(&g_game_base->players[0].mouse_cursor)
00417f25        intro->hide_for_replay_latch = 0
00417f2d        struct FrontendWidget* postal_button = intro->postal_button
00417f30        enum FrontendWidgetFlag widget_flags = postal_button->widget_flags
00417f38        if ((widget_flags.b & 0x20) != 0)
00417f3a        widget_flags.b &= 0xdf
00417f3c        postal_button->widget_flags = widget_flags
00417f44        destroy_main_menu()
00417f50        g_game_base->players[0].frontend_state = 0xa
00417f60        g_game_base->players[0].redispatch_requested = 1
00417f6c        g_game_base->subgame.level_mode = 0
00417f79        g_game_base->subgame.subgame_rebuild_selector = 2
00417f84        return
00417f85        struct FrontendWidget* time_trial_button = intro->time_trial_button
00417f88        enum FrontendWidgetFlag widget_flags_1 = time_trial_button->widget_flags
00417f90        if ((widget_flags_1.b & 0x20) != 0)
00417f92        widget_flags_1.b &= 0xdf
00417f94        time_trial_button->widget_flags = widget_flags_1
00417f9c        destroy_main_menu()
00417faa        g_game_base->players[0].frontend_state = 0xa
00417fba        g_game_base->players[0].redispatch_requested = 1
00417fc6        g_game_base->subgame.level_mode = 4
00417fd1        return
00417fd2        struct FrontendWidget* tutorial_button = intro->tutorial_button
00417fd5        enum FrontendWidgetFlag widget_flags_2 = tutorial_button->widget_flags
00417fdd        if ((widget_flags_2.b & 0x20) != 0)
00417fdf        widget_flags_2.b &= 0xdf
00417fe1        tutorial_button->widget_flags = widget_flags_2
00417fe9        destroy_main_menu()
00417ff4        g_game_base->players[0].frontend_state = 0xa
00418004        g_game_base->players[0].redispatch_requested = 1
0041800f        g_game_base->subgame.level_mode = 7
00418025        initialize_tutorial(&g_game_base->subgame.tutorial)
0041802c        g_runtime_config.new_game_tutorial_started = 1
00418035        return
00418036        struct FrontendWidget* challenge_button = intro->challenge_button
00418039        enum FrontendWidgetFlag widget_flags_3 = challenge_button->widget_flags
00418041        if ((widget_flags_3.b & 0x20) != 0)
00418043        widget_flags_3.b &= 0xdf
00418045        challenge_button->widget_flags = widget_flags_3
0041804d        destroy_main_menu()
0041805b        g_game_base->players[0].frontend_state = 0xa
0041806a        g_game_base->players[0].redispatch_requested = 1
00418076        g_game_base->subgame.level_mode = 1
0041807e        return
0041807f        struct FrontendWidget* back_button = intro->back_button
00418082        enum FrontendWidgetFlag widget_flags_4 = back_button->widget_flags
0041808a        if ((widget_flags_4.b & 0x20) == 0)
004180b8        struct FrontendWidget* help_button = intro->help_button
004180bb        struct GameRoot* widget_flags_5 = help_button->widget_flags
004180c3        if ((widget_flags_5.b & 0x20) != 0)
004180c5        widget_flags_5.b &= 0xdf
004180c7        help_button->widget_flags = widget_flags_5
004180cf        destroy_main_menu()
004180da        g_game_base->players[0].frontend_state = 0x1f
004180ea        g_game_base->players[0].redispatch_requested = 1
0041808c        widget_flags_4.b &= 0xdf
0041808e        back_button->widget_flags = widget_flags_4
00418096        destroy_main_menu()
004180a1        g_game_base->players[0].frontend_state = 4
004180b0        g_game_base->players[0].redispatch_requested = 1
004180f3        long double x87_r7_1 = fconvert.t(intro->replay_probe_step) + fconvert.t(intro->replay_probe_progress)
004180f6        intro->replay_probe_progress = fconvert.s(x87_r7_1)
004180f9        long double temp0 = fconvert.t(1f)
004180f9        x87_r7_1 - temp0
00418104        if ((((x87_r7_1 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0) ? 1 : 0) << 0xa | (x87_r7_1 == temp0 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
00418104        return
0041810a        intro->replay_probe_progress = 0f
00418112        int32_t i = 0
00418114        g_game_base->subgame.selected_level_record = nullptr
0041811a        int32_t replay_attract_bank_cursor = intro->replay_attract_bank_cursor
0041811c        i += 1
0041811f        if (replay_attract_bank_cursor == 0)
004181fb        int32_t eax_22
004181fb        eax_22, x87control = ftol(x87control, float.t(next_math_random_value()) * fconvert.t(0.000122070312f))
00418210        struct GameRoot* game_base_3 = g_game_base
00418229        if (game_base_3->subgame.sub_high_score.postal_records[eax_22].active == 1)
0041822b        game_base_3->subgame.selected_level_record = &game_base_3->subgame.sub_high_score.postal_records[eax_22]
00418236        g_game_base->subgame.level_mode = 0
00418126        if (replay_attract_bank_cursor == 1)
004181a5        int32_t eax_18
004181a5        eax_18, x87control = ftol(x87control, float.t(next_math_random_value()) * fconvert.t(0.000122070312f))
004181ba        struct GameRoot* game_base_2 = g_game_base
004181d3        if (game_base_2->subgame.sub_high_score.survival_records[eax_18].active == 1)
004181d5        game_base_2->subgame.selected_level_record = &game_base_2->subgame.sub_high_score.survival_records[eax_18]
004181e0        g_game_base->subgame.level_mode = 1
0041812b        if (replay_attract_bank_cursor == 3)
00418144        int32_t eax_14
00418144        eax_14, x87control = ftol(x87control, float.t(next_math_random_value()) * fconvert.t(0.00155639648f))
00418159        struct GameRoot* game_base_1 = g_game_base
00418172        if (game_base_1->subgame.sub_high_score.time_trial_route_records[eax_14].active == 1)
00418178        game_base_1->subgame.selected_level_record = &game_base_1->subgame.sub_high_score.time_trial_route_records[eax_14]
00418183        g_game_base->subgame.level_mode = 4
0041823e        int32_t ecx_38 = intro->replay_attract_bank_cursor + 1
00418241        intro->replay_attract_bank_cursor = ecx_38
00418246        if (ecx_38 == 5)
00418248        intro->replay_attract_bank_cursor = 0
00418256        if (g_game_base->subgame.selected_level_record != 0)
0041827a        if (i s>= 0x3e8)
0041827a        break
0041827c        intro->hide_for_replay_latch = 1
00418285        g_game_base->players[0].frontend_state = 0xa
00418294        g_game_base->players[0].redispatch_requested = 1
004182a0        g_game_base->subgame.selected_level_record_active = 1
004182ae        g_game_base->subgame.selected_level_record_cursor = 2
004182bd        g_game_base->subgame.selected_level_record_persistent = 1
004182c3        intro->attract_reset_progress = 0f
004182c6        intro->attract_reset_step = 0.000277777785f
004182cd        destroy_main_menu()
004182d7        return
0041825e        do while (i s< 0x3e8)
00418264        intro->attract_reset_progress = 0f
00418267        intro->attract_reset_step = 0.000277777785f
00418273        return
