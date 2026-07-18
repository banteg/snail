/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_thanks_for_playing_screen @ 0x433fd0 */

00433fe1        hide_star_field(&g_game_base->star_manager)
00433ff2        cache_music_file("music/introtext.ogg", 0, &g_blank_text)
0043400b        int32_t eax = load_landscape_script_by_name(&g_game_base->subgame.landscape_manager, "Splash.txt")
00434018        struct GameRoot* game_base_1 = g_game_base
0043402b        change_backdrop(&game_base_1->backdrop, &game_base_1->subgame.landscape_manager.scripts[eax], 0)
0043403d        set_border_justify_centre(&g_game_base->border_manager, 0f)
0043406f        thanks_screen->message_widget = allocate_border(&g_game_base->border_manager)
00434072        struct tColour color
00434072        struct tColour* color_1 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0043408e        initialize_frontend_widget(thanks_screen->message_widget, 0x20400002, "Thanks For Playing!", 0x14, 0f, 435f, color_1, 2, 0f)
00434096        thanks_screen->message_widget->font_scale = 1.20000005f
004340a0        thanks_screen->message_progress = 0f
004340a7        thanks_screen->message_progress_step = 0.00416666688f
004340ae        thanks_screen->message_state = 0
004340b9        return
