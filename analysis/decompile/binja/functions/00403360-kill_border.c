/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: kill_border @ 0x403360 */

0040336a        if (widget == 0)
0040336a        return
0040336c        enum FrontendWidgetFlag widget_flags = widget->widget_flags
00403379        if (widget_flags == 0 || (widget_flags:1.b & 4) != 0)
00403379        return
0040337b        widget_flags.b &= 1
0040337d        widget_flags:1.b |= 2
00403385        widget->widget_flags = widget_flags
0040338b        if ((widget_flags & 0x100000) == 0)
0040338b        return
00403394        kill_border(manager, widget->slider_less_widget)
004033a2        kill_border(manager, widget->slider_more_widget)
004033b0        kill_border(manager, widget->slider_value_widget)
004033b7        return
