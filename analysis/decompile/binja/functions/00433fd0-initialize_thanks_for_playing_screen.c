/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_thanks_for_playing_screen @ 0x433fd0 */

00433fe1        hide_star_field(&g_game_base->star_manager)
00433ff2        cache_music_file("music/introtext.ogg", 0, &g_blank_text)
0043400b        int32_t eax = load_landscape_script_by_name(&g_game_base->subgame.landscape_manager, "Splash.txt")
00434018        struct GameRoot* game_base_1 = g_game_base
0043402b        change_backdrop(&game_base_1->backdrop, &game_base_1->unknown_000000[eax * 0x124 + 0x106c7bc], 0)
0043403d        set_border_justify_centre(&g_game_base->border_manager, 0f)
0043406f        *(arg1 + 4) = allocate_border(&g_game_base->border_manager)
00434072        struct tColour color
00434072        struct tColour* color_1 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0043408e        int32_t result = initialize_frontend_widget(*(arg1 + 4), 0x20400002, "Thanks For Playing!", 0x14, 0f, 435f, color_1, 2, 0f)
00434096        *(*(arg1 + 4) + 0x6f0) = 0x3f99999a
004340a0        *(arg1 + 0xc) = 0
004340a7        *(arg1 + 0x10) = 0x3b888889
004340ae        *(arg1 + 8) = 0
004340b9        return result
