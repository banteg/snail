/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: queue_frontend_widget_flag_after_delay @ 0x403f60 */

00403f6b        if (manager->delayed_widget_active != 0)
00403f6b        return
00403f7c        if ((widget->widget_flags & FRONTEND_WIDGET_FLAG_FADE_BEFORE_ACTION) != 0)
00403f88        begin_frontend_fade_out(&g_game_base->fade, nullptr)
00403f91        manager->delayed_widget = widget
00403f97        manager->delayed_widget_active = 1
00403f9e        manager->delayed_widget_progress = 0f
00403fa8        manager->delayed_widget_progress_step = 0.0833333358f
00403fb2        manager->delayed_widget_flags = queued_flags
00403fba        return
