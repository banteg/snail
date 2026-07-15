/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_input_ok @ 0x403560 */

0040356e        struct FrontendWidget* widget = allocate_border(&g_game_base->border_manager)
00403573        struct FrontendWidget* source_widget = input_ok->source_widget
0040357a        input_ok->ok_widget = widget
00403595        initialize_frontend_widget(widget, 0x14, "OK", source_widget->widget_type, 0f, 0f, &source_widget->idle_fill_color, 0, 0f)
0040359c        update_input_ok(input_ok)
004035a2        return
