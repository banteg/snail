/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: border_input_text_init @ 0x403410 */

00403423        widget->input_flags = flags
0040342a        rstrcpy_checked_ascii(&widget->text_buffer.raw[0x400], text)
00403431        struct FrontendWidgetTextBuffer* eax = &widget->text_buffer
00403437        widget->input_cursor = 0
0040343d        widget->input_length = 0
0040344a        while (eax->raw[0] != 0)
00403452        eax = &eax->raw[1]
00403454        widget->input_length += 1
00403461        widget->input_cursor += 1
00403473        widget->text_buffer.raw[widget->input_cursor] = 0x7c
00403481        widget->text_buffer.raw[1 + widget->input_cursor] = 0
00403488        widget->input_cursor_blink_progress = 0f
00403492        widget->input_cursor_visible = 1
0040349c        widget->input_capacity = capacity
004034a4        widget->input_cursor_blink_step = 0.0833333358f
004034ae        layout_frontend_widget(widget)
004034b6        if ((flags.b & 0xc) != 0)
004034be        initialize_input_ok(&widget->tooltip._pad_1c)
004034c5        return
