/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_main_menu @ 0x419b50 */

00419b61        hide_star_field(&g_game_base->star_manager)
00419b72        cache_music_file("music/mainmenu.ogg", 0, &g_blank_text)
00419b77        g_game_base
00419b8b        int32_t eax = load_landscape_script_by_name("Menubg.txt")
00419b98        struct GameRoot* game_base_1 = g_game_base
00419bab        change_backdrop(&game_base_1->backdrop, &game_base_1->unknown_000000[eax * 0x124 + 0x106c7bc], 0)
00419bc0        set_border_justify_centre(&g_game_base->border_manager, 0x41c80000)
00419bcb        g_game_base->render_skip_count = 2
00419c02        *arg1 = allocate_border(&g_game_base->border_manager)
00419c04        struct tColour color
00419c04        struct tColour* color_1 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00419c1f        initialize_frontend_widget(*arg1, 0x14, "New Game", 0x14, 20f, 90f, color_1, 2, 0f)
00419c50        arg1[1] = allocate_border(&g_game_base->border_manager)
00419c53        struct tColour* color_2 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00419c6f        initialize_frontend_widget(arg1[1], 0x14, "High Scores", 0x14, 20f, 20f, color_2, 2, 0f)
00419c7a        stack_widget_below(arg1[1], *arg1)
00419c99        arg1[2] = allocate_border(&g_game_base->border_manager)
00419caf        struct tColour* color_3 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00419ccb        initialize_frontend_widget(arg1[2], 0x14, "Options", 0x14, 20f, 20f, color_3, 2, 0f)
00419cd7        stack_widget_below(arg1[2], arg1[1])
00419d09        arg1[2] = allocate_border(&g_game_base->border_manager)
00419d0c        struct tColour* color_4 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00419d28        initialize_frontend_widget(arg1[2], 0x14, "Options", 0x14, 20f, 20f, color_4, 2, 0f)
00419d34        stack_widget_below(arg1[2], arg1[1])
00419d65        arg1[3] = allocate_border(&g_game_base->border_manager)
00419d68        struct tColour* color_5 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00419d87        initialize_frontend_widget(arg1[3], 0x40000014, "Credits", 0x14, 20f, 20f, color_5, 2, 0f)
00419d93        stack_widget_below(arg1[3], arg1[2])
00419dc5        arg1[5] = allocate_border(&g_game_base->border_manager)
00419dc8        struct tColour* color_6 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00419de4        initialize_frontend_widget(arg1[5], 0x14, "Exit", 0x14, 20f, 390f, color_6, 2, 0f)
00419df9        return stack_widget_below(arg1[5], arg1[3])
