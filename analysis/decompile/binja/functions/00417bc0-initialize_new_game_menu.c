/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_new_game_menu @ 0x417bc0 */

00417bd1        hide_star_field(data_4df904 + 0x4f33c)
00417bd6        void* var_18 = &data_4dfb08
00417bdb        int32_t var_1c = 0
00417be2        cache_music_file("music/mainmenu.ogg")
00417bfb        int32_t eax = load_landscape_script_by_name(data_4df904 + 0x106c218, "Menubg.txt")
00417c08        void* eax_1 = data_4df904
00417c1b        change_backdrop(eax_1 + 0x4ec10, eax_1 + eax * 0x124 + 0x106c7bc, 0)
00417c30        set_border_justify_centre(data_4df904 + 0xb4c, 0x41c80000)
00417c3b        *(data_4df904 + 0x56c) = 2
00417c72        *(arg1 + 0x3c) = allocate_border(data_4df904 + 0xb4c)
00417c75        struct Color4f color
00417c75        struct Color4f* color_1 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00417c94        initialize_frontend_widget(*(arg1 + 0x3c), 0x40000014, "Tutorial", 0x14, 20f, 80f, color_1, 2, 0f)
00417cc5        *(arg1 + 0x30) = allocate_border(data_4df904 + 0xb4c)
00417cc8        struct Color4f* color_2 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00417ce7        initialize_frontend_widget(*(arg1 + 0x30), 0x40000014, "Postal Mode", 0x14, 20f, 20f, color_2, 2, 0f)
00417cf3        stack_widget_below(*(arg1 + 0x30), *(arg1 + 0x3c))
00417d12        *(arg1 + 0x34) = allocate_border(data_4df904 + 0xb4c)
00417d28        struct Color4f* color_3 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00417d47        initialize_frontend_widget(*(arg1 + 0x34), 0x40000014, "Time Trial", 0x14, 20f, 20f, color_3, 2, 0f)
00417d53        stack_widget_below(*(arg1 + 0x34), *(arg1 + 0x30))
00417d85        *(arg1 + 0x38) = allocate_border(data_4df904 + 0xb4c)
00417d88        struct Color4f* color_4 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00417da4        initialize_frontend_widget(*(arg1 + 0x38), 0x14, "Challenge Mode", 0x14, 20f, 20f, color_4, 2, 0f)
00417db0        stack_widget_below(*(arg1 + 0x38), *(arg1 + 0x34))
00417de4        *(arg1 + 0x40) = allocate_border(data_4df904 + 0xb4c)
00417de7        struct Color4f* color_5 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00417e03        initialize_frontend_widget(*(arg1 + 0x40), 0x40000014, "Help", 0x14, 0f, 350f, color_5, 2, -220f)
00417e35        *(arg1 + 0x44) = allocate_border(data_4df904 + 0xb4c)
00417e38        struct Color4f* color_6 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00417e54        initialize_frontend_widget(*(arg1 + 0x44), 0x14, "Back", 0x14, 20f, 350f, color_6, 2, 0f)
00417e60        stack_widget_below(*(arg1 + 0x44), *(arg1 + 0x38))
00417e65        int32_t result
00417e65        result.b = data_4df9d8
00417e6c        if (result.b == 0)
00417e6e        void* eax_12 = *(arg1 + 0x30)
00417e7e        *(eax_12 + 0x1a0) |= 0x8000
00417e84        result = *(arg1 + 0x34)
00417e8f        *(result + 0x1a0) |= 0x8000
00417e95        void* esi_1 = *(arg1 + 0x38)
00417e98        *(esi_1 + 0x1a0) |= 0x8000
00417ea2        return result
