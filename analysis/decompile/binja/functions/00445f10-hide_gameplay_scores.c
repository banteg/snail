/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: hide_gameplay_scores @ 0x445f10 */

00445f13        struct FrontendWidget* bottom_score_widget = game->bottom_score_widget
00445f1b        if (bottom_score_widget != 0)
00445f1d        hide_border_init(bottom_score_widget)
00445f22        struct FrontendWidget* top_score_widget = game->top_score_widget
00445f2b        if (top_score_widget == 0)
00445f32        return
00445f2d        return hide_border_init(top_score_widget) __tailcall
