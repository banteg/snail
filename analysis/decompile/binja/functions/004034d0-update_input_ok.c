/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_input_ok @ 0x4034d0 */

004034d0        struct FrontendWidget* source_widget = input_ok->source_widget
004034d3        uint8_t input_flags = (source_widget->input_flags).b
004034dc        struct FrontendWidget* ok_widget_1
004034dc        long double x87_r7_4
004034dc        if ((input_flags & 4) != 0)
004034de        ok_widget_1 = input_ok->ok_widget
004034f3        x87_r7_4 = fconvert.t(ok_widget_1->hot_padding) + fconvert.t(source_widget->layout_width) + fconvert.t(source_widget->layout_left) + fconvert.t(source_widget->hot_padding)
0040351f        label_40351f:
0040351f        ok_widget_1->layout_left = fconvert.s(x87_r7_4)
00403531        input_ok->ok_widget->layout_top = input_ok->source_widget->layout_top
00403537        struct FrontendWidget* ok_widget = input_ok->ok_widget
00403540        ok_widget->layout_anchor_x = ok_widget->layout_left
00403552        input_ok->ok_widget->layout_anchor_y = input_ok->source_widget->layout_anchor_y
004034fe        if ((input_flags & 8) != 0)
00403500        ok_widget_1 = input_ok->ok_widget
00403515        long double x87_r6_1 = fconvert.t(ok_widget_1->hot_padding)
0040351d        x87_r7_4 = fconvert.t(source_widget->layout_left) - fconvert.t(ok_widget_1->layout_width) - fconvert.t(source_widget->hot_padding) - (x87_r6_1 + x87_r6_1)
0040351d        goto label_40351f
00403558        return
