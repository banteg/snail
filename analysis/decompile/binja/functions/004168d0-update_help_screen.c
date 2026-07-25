/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_help_screen @ 0x4168d0 */

004168d0        struct FrontendWidget* back_button = help->back_button
004168d2        enum FrontendWidgetFlag widget_flags = back_button->widget_flags
004168da        if ((widget_flags.b & 0x20) == 0)
004168da        return
004168dc        widget_flags.b &= 0xdf
004168de        back_button->widget_flags = widget_flags
004168e4        destroy_help_screen(help)
004168ee        g_game_base->players[0].frontend_state = 2
004168fe        g_game_base->players[0].redispatch_requested = 1
00416905        return
