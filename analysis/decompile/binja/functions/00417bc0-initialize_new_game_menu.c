/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
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
00417c56        int32_t var_18_1 = 0
00417c72        *(arg1 + 0x3c) = allocate_border(data_4df904 + 0xb4c)
00417c75        void var_10
00417c75        int32_t* eax_4 = set_color_rgba(&var_10, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00417c94        initialize_frontend_widget(*(arg1 + 0x3c), 0x40000014, "Tutorial", 0x14, 0x41a00000, 80f, eax_4, 2.80259693e-45f)
00417ca9        int32_t var_18_2 = 0
00417cc5        *(arg1 + 0x30) = allocate_border(data_4df904 + 0xb4c)
00417cc8        int32_t* eax_7 = set_color_rgba(&var_10, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00417ce7        initialize_frontend_widget(*(arg1 + 0x30), 0x40000014, "Postal Mode", 0x14, 0x41a00000, 20f, eax_7, 2.80259693e-45f)
00417cf3        stack_widget_below(*(arg1 + 0x30), *(arg1 + 0x3c))
00417d09        int32_t var_18_4 = 0
00417d12        *(arg1 + 0x34) = allocate_border(data_4df904 + 0xb4c)
00417d28        int32_t* eax_9 = set_color_rgba(&var_10, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00417d47        initialize_frontend_widget(*(arg1 + 0x34), 0x40000014, "Time Trial", 0x14, 0x41a00000, 20f, eax_9, 2.80259693e-45f)
00417d53        stack_widget_below(*(arg1 + 0x34), *(arg1 + 0x30))
00417d69        int32_t var_18_6 = 0
00417d85        *(arg1 + 0x38) = allocate_border(data_4df904 + 0xb4c)
00417d88        int32_t* eax_12 = set_color_rgba(&var_10, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00417da4        initialize_frontend_widget(*(arg1 + 0x38), 0x14, "Challenge Mode", 0x14, 0x41a00000, 20f, eax_12, 2.80259693e-45f)
00417db0        stack_widget_below(*(arg1 + 0x38), *(arg1 + 0x34))
00417dc5        int32_t var_18_8 = 0xc35c0000
00417de4        *(arg1 + 0x40) = allocate_border(data_4df904 + 0xb4c)
00417de7        int32_t* eax_15 = set_color_rgba(&var_10, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00417e03        initialize_frontend_widget(*(arg1 + 0x40), 0x40000014, "Help", 0x14, 0, 350f, eax_15, 2.80259693e-45f)
00417e19        int32_t var_18_9 = 0
00417e35        *(arg1 + 0x44) = allocate_border(data_4df904 + 0xb4c)
00417e38        int32_t* eax_17 = set_color_rgba(&var_10, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00417e54        initialize_frontend_widget(*(arg1 + 0x44), 0x14, "Back", 0x14, 0x41a00000, 350f, eax_17, 2.80259693e-45f)
00417e60        stack_widget_below(*(arg1 + 0x44), *(arg1 + 0x38))
00417e65        float* result
00417e65        result.b = data_4df9d8
00417e6c        if (result.b == 0)
00417e6e        void* eax_18 = *(arg1 + 0x30)
00417e7e        *(eax_18 + 0x1a0) |= 0x8000
00417e84        result = *(arg1 + 0x34)
00417e8f        result[0x68] |= 0x8000
00417e95        void* esi_1 = *(arg1 + 0x38)
00417e98        *(esi_1 + 0x1a0) |= 0x8000
00417ea2        return result
