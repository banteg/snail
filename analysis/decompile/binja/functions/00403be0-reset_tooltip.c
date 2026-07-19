/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: reset_tooltip @ 0x403be0 */

00403be3        int32_t state = tooltip->state
00403be9        if (state == 2)
00403c0a        tooltip->state = 1
00403bec        if (state == 3)
00403bfe        kill_border(&g_game_base->border_manager, tooltip->tooltip_widget)
00403c03        tooltip->tooltip_widget = nullptr
00403c0a        tooltip->state = 1
00403c12        return
