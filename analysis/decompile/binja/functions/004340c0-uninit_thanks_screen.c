/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: uninit_thanks_screen @ 0x4340c0 */

004340d0        kill_border(&g_game_base->border_manager, thanks_screen->message_widget)
004340db        g_game_base->players[0].frontend_state = 0xe
004340e5        return
