/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: uninit_pause_menu @ 0x440600 */

00440612        kill_border(&g_game_base->border_manager, pause->options_widget)
00440626        kill_border(&g_game_base->border_manager, pause->end_game_widget)
0044063b        kill_border(&g_game_base->border_manager, pause->resume_widget)
0044064b        release_mouse_cursor(&g_game_base->players[0].mouse_cursor)
00440651        return
