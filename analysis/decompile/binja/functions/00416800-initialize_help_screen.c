/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_help_screen @ 0x416800 */

00416812        cache_music_file("music/mainmenu.ogg", 0, &g_blank_text)
0041682a        int32_t eax_1 = load_landscape_script_by_name(&g_game_base->subgame.landscape_manager, "Help.txt")
00416837        struct GameRoot* game_base_1 = g_game_base
0041684a        change_backdrop(&game_base_1->backdrop, &game_base_1->unknown_000000[eax_1 * 0x124 + 0x106c7bc], 0)
0041685d        set_border_justify_centre(&g_game_base->border_manager, 0f)
0041688e        *arg1 = allocate_border(&g_game_base->border_manager)
00416890        struct tColour color
00416890        struct tColour* color_1 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
004168b4        return initialize_frontend_widget(*arg1, 0x40000014, "Back", 0x14, 0f, 420f, color_1, 2, 0f)
