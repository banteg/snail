/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_pause_menu @ 0x440660 */

00440692        arg1[1] = allocate_border(data_4df904 + 0xb4c)
00440695        struct Color4f color
00440695        struct Color4f* color_1 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
004406ae        initialize_frontend_widget(arg1[1], 0x14, "End Game", 0x14, 0f, 145f, color_1, 2, 0f)
004406b8        sub_402790(arg1[1], 0xb)
004406ea        *arg1 = allocate_border(data_4df904 + 0xb4c)
004406ec        struct Color4f* color_2 = set_color_rgba(&color, 1f, 1f, 1f, 0.0299999993f)
00440704        initialize_frontend_widget(*arg1, 0x14, "Options", 0x14, 0f, 190f, color_2, 2, 0f)
0044070d        sub_402790(*arg1, 0x6f)
00440714        layout_frontend_widget(*arg1)
0044071f        stack_widget_below(*arg1, arg1[1])
00440750        arg1[2] = allocate_border(data_4df904 + 0xb4c)
00440753        struct Color4f* color_3 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0044076c        initialize_frontend_widget(arg1[2], 0x14, "Resume", 0x14, 0f, 320f, color_3, 2, 0f)
00440776        sub_402790(arg1[2], 5)
00440781        stack_widget_below(arg1[2], *arg1)
0044079b        return capture_mouse_cursor(data_4df904 + 0x290)
