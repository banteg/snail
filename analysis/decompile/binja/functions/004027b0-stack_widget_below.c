/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: stack_widget_below @ 0x4027b0 */

004027ba        widget->layout_anchor_x = previous_widget->layout_anchor_x
004027d2        widget->layout_anchor_y = fconvert.s(fconvert.t(previous_widget->layout_anchor_y) + fconvert.t(widget->stack_gap) + fconvert.t(previous_widget->layout_height))
004027d8        layout_frontend_widget(widget)
004027dd        return
