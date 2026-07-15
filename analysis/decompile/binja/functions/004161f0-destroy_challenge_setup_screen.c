/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: destroy_challenge_setup_screen @ 0x4161f0 */

004161f5        int32_t level_mode = gui->game->level_mode
004161fb        if (level_mode == 0)
004162f9        g_game_base
00416308        kill_border(gui->next_level_button)
00416310        g_game_base
0041631d        kill_border(gui->previous_level_button)
00416325        g_game_base
00416332        kill_border(gui->level_name_widget)
00416337        g_game_base
00416346        kill_border(gui->play_button)
0041634e        g_game_base
0041635b        kill_border(gui->back_button)
0041635b        return
00416202        if (level_mode == 1)
00416292        g_game_base
0041629f        kill_border(gui->play_button)
004162a7        g_game_base
004162b4        kill_border(gui->back_button)
004162b9        g_game_base
004162c8        kill_border(gui->speed_slider)
004162d0        g_game_base
004162dd        kill_border(gui->difficulty_slider)
004162e5        g_game_base
004162f2        kill_border(gui->replay_button)
004162f8        return
0041620b        if (level_mode != 4)
00416214        return
00416214        g_game_base
00416221        kill_border(gui->next_level_button)
00416229        g_game_base
00416236        kill_border(gui->previous_level_button)
0041623b        g_game_base
0041624a        kill_border(gui->level_name_widget)
00416252        g_game_base
0041625f        kill_border(gui->play_button)
00416267        g_game_base
00416274        kill_border(gui->back_button)
00416279        g_game_base
00416288        kill_border(gui->replay_button)
00416361        return
