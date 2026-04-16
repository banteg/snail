/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_input_ok @ 0x403560 */

0040356e        struct FrontendWidget* widget = allocate_border(data_4df904 + 0xb4c)
00403573        void* ecx_1 = *(arg1 + 0x1c)
0040357a        *(arg1 + 0x20) = widget
00403595        initialize_frontend_widget(widget, 0x14, "OK", *(ecx_1 + 0x7c), 0f, 0f, ecx_1 + 0x1bc, 0, 0f)
004035a2        return update_input_ok(arg1)
