/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_options_menu @ 0x41ace0 */

0041acf1        hide_all_borders(data_4df904 + 0xb4c)
0041acfc        *(data_4df904 + 0x568) = 1
0041ad30        *(arg1 + 0x14) = allocate_border(data_4df904 + 0xb4c)
0041ad33        struct Color4f color
0041ad33        struct Color4f* color_1 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0041ad4f        initialize_frontend_widget(*(arg1 + 0x14), 0x14, &data_4dfb08, 0x14, 90f, 75f, color_1, 2, 0f)
0041ad54        void* eax_1 = *(arg1 + 0x14)
0041ad63        *(eax_1 + 0x6f8) = fconvert.s(fconvert.t(*(eax_1 + 0x6f8)) + fconvert.t(8f))
0041ad95        *(arg1 + 0x18) = allocate_border(data_4df904 + 0xb4c)
0041ad98        struct Color4f* color_2 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0041adb7        initialize_frontend_widget(*(arg1 + 0x18), 0x900004, "     Sounds Volume     >", 0x14, 90f, 400f, color_2, 2, 0f)
0041adc3        stack_widget_below(*(arg1 + 0x18), *(arg1 + 0x14))
0041add0        *(*(arg1 + 0x18) + 0x17c) = data_4df918
0041addf        *(*(arg1 + 0x18) + 0x180) = data_4df918
0041adea        (***(arg1 + 0x18))()
0041ae19        *(arg1 + 0x1c) = allocate_border(data_4df904 + 0xb4c)
0041ae1c        struct Color4f* color_3 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0041ae3b        initialize_frontend_widget(*(arg1 + 0x1c), 0x100004, "      Music Volume      >", 0x14, 90f, 400f, color_3, 2, 0f)
0041ae47        stack_widget_below(*(arg1 + 0x1c), *(arg1 + 0x18))
0041ae55        *(*(arg1 + 0x1c) + 0x17c) = data_4df91c
0041ae63        *(*(arg1 + 0x1c) + 0x180) = data_4df91c
0041ae6e        (***(arg1 + 0x1c))()
0041ae9c        *(arg1 + 0x10) = allocate_border(data_4df904 + 0xb4c)
0041ae9f        struct Color4f* color_4 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0041aebb        initialize_frontend_widget(*(arg1 + 0x10), 0x14, "Back", 0x14, 90f, 400f, color_4, 2, 0f)
0041aec7        int32_t result = stack_widget_below(*(arg1 + 0x10), *(arg1 + 0x1c))
0041aed2        *(arg1 + 0x20) = data_4df918
0041aed9        return result
