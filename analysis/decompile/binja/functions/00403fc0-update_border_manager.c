/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_border_manager @ 0x403fc0 */

00403fc0        int16_t eax
00403fc0        eax.b = manager->delayed_widget_active
00403fc9        if (eax.b == 0)
00403fc9        return
00403fd1        long double x87_r7_2 = fconvert.t(manager->delayed_widget_progress_step) + fconvert.t(manager->delayed_widget_progress)
00403fd7        manager->delayed_widget_progress = fconvert.s(x87_r7_2)
00403fdd        long double temp0_1 = fconvert.t(1f)
00403fdd        x87_r7_2 - temp0_1
00403fe8        if ((((x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
00403fe8        return
00403fea        struct FrontendWidget* delayed_widget = manager->delayed_widget
00403ff0        manager->delayed_widget_progress = 1f
00403ffa        enum FrontendWidgetFlag widget_flags = delayed_widget->widget_flags
00404016        if ((widget_flags & FRONTEND_WIDGET_FLAG_FADE_BEFORE_ACTION) == 0 || g_game_base->fade.state == 4)
00404020        delayed_widget->widget_flags = manager->delayed_widget_flags | widget_flags
00404026        manager->delayed_widget_active = 0
0040402e        return
