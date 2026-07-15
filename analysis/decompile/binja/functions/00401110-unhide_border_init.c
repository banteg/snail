/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: unhide_border_init @ 0x401110 */

00401110        enum FrontendWidgetFlag widget_flags = widget->widget_flags
00401116        widget->hide_blend = 1f
0040111d        widget_flags:1.b &= 0xef
00401120        widget->widget_flags = widget_flags
00401126        return
