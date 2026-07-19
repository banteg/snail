/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: destroy_completion_screen @ 0x406060 */

00406073        kill_border(&g_game_base->border_manager, exit_controller->prompt_title)
00406087        kill_border(&g_game_base->border_manager, exit_controller->yes_button)
0040609c        kill_border(&g_game_base->border_manager, exit_controller->no_button)
004060ac        unhide_all_borders(&g_game_base->border_manager)
004060bb        g_game_base->players[0].frontend_state = exit_controller->previous_frontend_state
004060c1        return
