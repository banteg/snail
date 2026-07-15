/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: destroy_options_menu @ 0x41aee0 */

0041aeee        unhide_all_borders(&g_game_base->border_manager)
0041aef6        g_game_base
0041af03        kill_border(options->back_widget)
0041af0b        g_game_base
0041af18        kill_border(options->music_volume_widget)
0041af1d        g_game_base
0041af2c        kill_border(options->sound_volume_widget)
0041af34        g_game_base
0041af41        kill_border(options->fullscreen_widget)
0041af55        save_config_file("SnailMail.cfg", &g_runtime_config, 0xc4)
0041af5e        return
