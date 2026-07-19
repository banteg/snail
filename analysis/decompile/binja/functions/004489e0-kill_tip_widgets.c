/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: kill_tip_widgets @ 0x4489e0 */

004489f3        kill_border(&g_game_base->border_manager, tip->widget_main)
004489f8        struct FrontendWidget* widget_ok = tip->widget_ok
004489fd        if (widget_ok != 0)
00448a0c        kill_border(&g_game_base->border_manager, widget_ok)
00448a11        struct FrontendWidget* widget_disable = tip->widget_disable
00448a16        if (widget_disable != 0)
00448a24        kill_border(&g_game_base->border_manager, widget_disable)
00448a29        tip->active = 0
00448a30        return
