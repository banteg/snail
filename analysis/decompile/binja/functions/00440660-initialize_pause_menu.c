/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_pause_menu @ 0x440660 */

00440692        pause->end_game_widget = allocate_border(&g_game_base->border_manager)
00440695        struct tColour color
00440695        struct tColour* color_1 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
004406ae        initialize_frontend_widget(pause->end_game_widget, 0x14, "End Game", 0x14, 0f, 145f, color_1, 2, 0f)
004406b8        set_frontend_widget_shortcut_key(pause->end_game_widget, 0xb)
004406ea        pause->options_widget = allocate_border(&g_game_base->border_manager)
004406ec        struct tColour* color_2 = set_color_rgba(&color, 1f, 1f, 1f, 0.0299999993f)
00440704        initialize_frontend_widget(pause->options_widget, 0x14, "Options", 0x14, 0f, 190f, color_2, 2, 0f)
0044070d        set_frontend_widget_shortcut_key(pause->options_widget, 0x6f)
00440714        layout_frontend_widget(pause->options_widget)
0044071f        stack_widget_below(pause->options_widget, pause->end_game_widget)
00440750        pause->resume_widget = allocate_border(&g_game_base->border_manager)
00440753        struct tColour* color_3 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0044076c        initialize_frontend_widget(pause->resume_widget, 0x14, "Resume", 0x14, 0f, 320f, color_3, 2, 0f)
00440776        set_frontend_widget_shortcut_key(pause->resume_widget, 5)
00440781        stack_widget_below(pause->resume_widget, pause->options_widget)
00440792        capture_mouse_cursor(&g_game_base->players[0].mouse_cursor)
0044079b        return
