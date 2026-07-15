/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: hide_border_init @ 0x4010e0 */

004010e0        enum FrontendWidgetFlag widget_flags = widget->widget_flags
004010e9        if ((widget_flags:1.b & 0x10) != 0)
00401106        return
004010eb        widget_flags:1.b |= 0x10
004010ee        widget->hide_blend = 0f
004010f5        widget->widget_flags = widget_flags
00401101        return reset_tooltip(&widget->tooltip) __tailcall
