/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_tip @ 0x448c40 */

00448c50        struct FrontendWidget* widget_main = tip->widget_main
00448c53        if (g_game_base->subgame.subgame_pause_gate != 0)
00448c55        hide_border_init(widget_main)
00448c5b        return
00448c5c        unhide_border_init(widget_main)
00448c61        struct FrontendWidget* ecx_1 = tip->widget_ok
00448c66        enum FrontendWidgetFlag widget_flags
00448c66        if (ecx_1 != 0)
00448c68        widget_flags = ecx_1->widget_flags
00448c70        if (ecx_1 == 0 || (widget_flags.b & 0x20) == 0)
00448c72        ecx_1 = tip->widget_disable
00448c77        if (ecx_1 != 0)
00448c79        widget_flags = ecx_1->widget_flags
00448c81        if (ecx_1 == 0 || (widget_flags.b & 0x20) == 0)
00448cbf        if ((tip->definition->flags.b & 2) != 0)
00448cc4        long double x87_r7_2 = fconvert.t(tip->dismiss_step) + fconvert.t(tip->dismiss_progress)
00448cc7        tip->dismiss_progress = fconvert.s(x87_r7_2)
00448cca        long double temp0_1 = fconvert.t(1f)
00448cca        x87_r7_2 - temp0_1
00448cd5        if ((((x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00448cd9        kill_tip_widgets(tip)
00448cde        tip->active = 0
00448ce5        return
00448c83        widget_flags.b &= 0xdf
00448c85        ecx_1->widget_flags = widget_flags
00448c94        g_game_base->players[0].frontend_state = tip->previous_outer_owner
00448c9c        kill_tip_widgets(tip)
00448cac        unhide_all_borders(&g_game_base->border_manager)
00448cb1        tip->active = 0
00448cb8        return
