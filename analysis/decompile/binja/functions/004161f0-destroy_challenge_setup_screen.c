/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: destroy_challenge_setup_screen @ 0x4161f0 */

004161f5        int32_t level_mode = gui->game->level_mode
004161fb        if (level_mode == 0)
00416308        kill_border(&g_game_base->border_manager, gui->next_level_button)
0041631d        kill_border(&g_game_base->border_manager, gui->previous_level_button)
00416332        kill_border(&g_game_base->border_manager, gui->level_name_widget)
00416346        kill_border(&g_game_base->border_manager, gui->play_button)
0041635b        kill_border(&g_game_base->border_manager, gui->back_button)
0041635b        return
00416202        if (level_mode == 1)
0041629f        kill_border(&g_game_base->border_manager, gui->play_button)
004162b4        kill_border(&g_game_base->border_manager, gui->back_button)
004162c8        kill_border(&g_game_base->border_manager, gui->speed_slider)
004162dd        kill_border(&g_game_base->border_manager, gui->difficulty_slider)
004162f2        kill_border(&g_game_base->border_manager, gui->replay_button)
004162f8        return
0041620b        if (level_mode != 4)
00416221        return
00416221        kill_border(&g_game_base->border_manager, gui->next_level_button)
00416236        kill_border(&g_game_base->border_manager, gui->previous_level_button)
0041624a        kill_border(&g_game_base->border_manager, gui->level_name_widget)
0041625f        kill_border(&g_game_base->border_manager, gui->play_button)
00416274        kill_border(&g_game_base->border_manager, gui->back_button)
00416288        kill_border(&g_game_base->border_manager, gui->replay_button)
00416361        return
