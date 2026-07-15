/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_challenge_setup_screen @ 0x415f50 */

00415f61        capture_mouse_cursor(&g_game_base->players[0].mouse_cursor)
00415f66        struct SubgameRuntime* game = gui->game
00415f76        load_frontend_level_by_mode_and_index(&game->level_definition, game->level_mode, game->level_mode_arg)
00415f81        if (gui->game->level_mode != 1)
00415f81        return
00415fb4        gui->difficulty_slider = allocate_border(&g_game_base->border_manager)
00415fb7        struct tColour color
00415fb7        struct tColour* color_5 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00415fd6        initialize_frontend_widget(gui->difficulty_slider, 0x100004, "     Select Difficulty     >", 0x14, 20f, 80f, color_5, 2, 0f)
00415fea        gui->difficulty_slider->slider_position_target = fconvert.s(float.t(g_runtime_config.completion_bonus_y_source) * fconvert.t(0.00999999978f))
00415ff0        struct FrontendWidget* difficulty_slider = gui->difficulty_slider
00415ff9        difficulty_slider->slider_position_current = difficulty_slider->slider_position_target
00416004        (*gui->difficulty_slider->list_kind)()
00416032        gui->speed_slider = allocate_border(&g_game_base->border_manager)
00416035        struct tColour color_1
00416035        struct tColour* color_6 = set_color_rgba(&color_1, 1f, 1f, 1f, 1f)
00416054        initialize_frontend_widget(gui->speed_slider, 0x100004, "       Select Speed       >", 0x14, 20f, 145f, color_6, 2, 0f)
00416068        gui->speed_slider->slider_position_target = fconvert.s(float.t(g_runtime_config.completion_bonus_x_source) * fconvert.t(0.00999999978f))
0041606e        struct FrontendWidget* speed_slider = gui->speed_slider
00416077        speed_slider->slider_position_current = speed_slider->slider_position_target
00416084        stack_widget_below(gui->speed_slider, gui->difficulty_slider)
0041608e        (*gui->speed_slider->list_kind)()
00416092        float anchor_x = 0f
004160a1        if (gui->game->sub_high_score.survival_pending_record.active == 1)
004160a3        anchor_x = 100f
004160db        gui->play_button = allocate_border(&g_game_base->border_manager)
004160de        struct tColour color_2
004160de        struct tColour* color_7 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
004160fd        initialize_frontend_widget(gui->play_button, 0x40000016, "Play", 0x14, 20f, 250f, color_7, 2, anchor_x)
00416109        stack_widget_below(gui->play_button, gui->speed_slider)
0041613e        gui->replay_button = allocate_border(&g_game_base->border_manager)
00416141        struct tColour color_3
00416141        struct tColour* color_8 = set_color_rgba(&color_3, 1f, 1f, 1f, 1f)
00416160        initialize_frontend_widget(gui->replay_button, 0x40000016, "Watch Replay", 0x14, 20f, 70f, color_8, 2, -100f)
0041616c        stack_widget_below(gui->replay_button, gui->speed_slider)
0041617a        if (gui->game->sub_high_score.survival_pending_record.active != 1)
0041617f        hide_border_init(gui->replay_button)
004161b1        gui->back_button = allocate_border(&g_game_base->border_manager)
004161b4        struct tColour color_4
004161b4        struct tColour* color_9 = set_color_rgba(&color_4, 1f, 1f, 1f, 1f)
004161d0        initialize_frontend_widget(gui->back_button, 0x16, "Back", 0x14, 20f, 20f, color_9, 2, 0f)
004161dc        stack_widget_below(gui->back_button, gui->replay_button)
004161e5        return
