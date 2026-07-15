/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_new_game_menu @ 0x417bc0 */

00417bd1        hide_star_field(&g_game_base->star_manager)
00417be2        cache_music_file("music/mainmenu.ogg", 0, &g_blank_text)
00417be7        g_game_base
00417bfb        int32_t eax = load_landscape_script_by_name("Menubg.txt")
00417c08        struct GameRoot* game_base_1 = g_game_base
00417c1b        change_backdrop(&game_base_1->backdrop, &game_base_1->unknown_000000[eax * 0x124 + 0x106c7bc], 0)
00417c30        set_border_justify_centre(&g_game_base->border_manager, 0x41c80000)
00417c3b        g_game_base->render_skip_count = 2
00417c72        intro->tutorial_button = allocate_border(&g_game_base->border_manager)
00417c75        struct tColour color
00417c75        struct tColour* color_1 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00417c94        initialize_frontend_widget(intro->tutorial_button, 0x40000014, "Tutorial", 0x14, 20f, 80f, color_1, 2, 0f)
00417cc5        intro->postal_button = allocate_border(&g_game_base->border_manager)
00417cc8        struct tColour* color_2 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00417ce7        initialize_frontend_widget(intro->postal_button, 0x40000014, "Postal Mode", 0x14, 20f, 20f, color_2, 2, 0f)
00417cf3        stack_widget_below(intro->postal_button, intro->tutorial_button)
00417d12        intro->time_trial_button = allocate_border(&g_game_base->border_manager)
00417d28        struct tColour* color_3 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00417d47        initialize_frontend_widget(intro->time_trial_button, 0x40000014, "Time Trial", 0x14, 20f, 20f, color_3, 2, 0f)
00417d53        stack_widget_below(intro->time_trial_button, intro->postal_button)
00417d85        intro->challenge_button = allocate_border(&g_game_base->border_manager)
00417d88        struct tColour* color_4 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00417da4        initialize_frontend_widget(intro->challenge_button, 0x14, "Challenge Mode", 0x14, 20f, 20f, color_4, 2, 0f)
00417db0        stack_widget_below(intro->challenge_button, intro->time_trial_button)
00417de4        intro->help_button = allocate_border(&g_game_base->border_manager)
00417de7        struct tColour* color_5 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00417e03        initialize_frontend_widget(intro->help_button, 0x40000014, "Help", 0x14, 0f, 350f, color_5, 2, -220f)
00417e35        intro->back_button = allocate_border(&g_game_base->border_manager)
00417e38        struct tColour* color_6 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00417e54        initialize_frontend_widget(intro->back_button, 0x14, "Back", 0x14, 20f, 350f, color_6, 2, 0f)
00417e60        stack_widget_below(intro->back_button, intro->challenge_button)
00417e6c        if (g_runtime_config.new_game_tutorial_started != 0)
00417e6c        return
00417e6e        struct FrontendWidget* postal_button = intro->postal_button
00417e7e        postal_button->widget_flags |= FRONTEND_WIDGET_FLAG_DISABLED
00417e84        struct FrontendWidget* time_trial_button = intro->time_trial_button
00417e8f        time_trial_button->widget_flags |= FRONTEND_WIDGET_FLAG_DISABLED
00417e95        struct FrontendWidget* challenge_button = intro->challenge_button
00417e98        challenge_button->widget_flags |= FRONTEND_WIDGET_FLAG_DISABLED
00417ea2        return
