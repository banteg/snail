/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: destroy_high_score_screen @ 0x417220 */

0041722f        g_runtime_config.high_score_selected_bank = high_score->selected_bank
00417234        kill_all_borders(&g_game_base->border_manager)
00417241        g_game_base->players[0].high_score_entry_pending = 0
0041724d        g_game_base->players[0].selected_high_score_rank = 0
00417253        return
