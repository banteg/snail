/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_main_menu @ 0x419b50 */

00419b61        hide_star_field(data_4df904 + 0x4f33c)
00419b66        void* var_18 = &data_4dfb08
00419b6b        int32_t var_1c = 0
00419b72        cache_music_file("music/mainmenu.ogg")
00419b8b        int32_t eax = load_landscape_script_by_name(data_4df904 + 0x106c218, "Menubg.txt")
00419b98        void* eax_1 = data_4df904
00419bab        change_backdrop(eax_1 + 0x4ec10, eax_1 + eax * 0x124 + 0x106c7bc, 0)
00419bc0        set_border_justify_centre(data_4df904 + 0xb4c, 0x41c80000)
00419bcb        *(data_4df904 + 0x56c) = 2
00419be6        int32_t var_18_1 = 0
00419c02        *arg1 = allocate_border(data_4df904 + 0xb4c)
00419c04        void var_10
00419c04        int32_t* eax_4 = set_color_rgba(&var_10, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00419c1f        initialize_frontend_widget(*arg1, 0x14, "New Game", 0x14, 0x41a00000, 90f, eax_4, 2.80259693e-45f)
00419c34        int32_t var_18_2 = 0
00419c50        arg1[1] = allocate_border(data_4df904 + 0xb4c)
00419c53        int32_t* eax_7 = set_color_rgba(&var_10, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00419c6f        initialize_frontend_widget(arg1[1], 0x14, "High Scores", 0x14, 0x41a00000, 20f, eax_7, 2.80259693e-45f)
00419c7a        stack_widget_below(arg1[1], *arg1)
00419c90        int32_t var_18_4 = 0
00419c99        arg1[2] = allocate_border(data_4df904 + 0xb4c)
00419caf        int32_t* eax_9 = set_color_rgba(&var_10, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00419ccb        initialize_frontend_widget(arg1[2], 0x14, "Options", 0x14, 0x41a00000, 20f, eax_9, 2.80259693e-45f)
00419cd7        stack_widget_below(arg1[2], arg1[1])
00419ced        int32_t var_18_6 = 0
00419d09        arg1[2] = allocate_border(data_4df904 + 0xb4c)
00419d0c        int32_t* eax_12 = set_color_rgba(&var_10, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00419d28        initialize_frontend_widget(arg1[2], 0x14, "Options", 0x14, 0x41a00000, 20f, eax_12, 2.80259693e-45f)
00419d34        stack_widget_below(arg1[2], arg1[1])
00419d49        int32_t var_18_8 = 0
00419d65        arg1[3] = allocate_border(data_4df904 + 0xb4c)
00419d68        int32_t* eax_15 = set_color_rgba(&var_10, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00419d87        initialize_frontend_widget(arg1[3], 0x40000014, "Credits", 0x14, 0x41a00000, 20f, eax_15, 2.80259693e-45f)
00419d93        stack_widget_below(arg1[3], arg1[2])
00419da9        int32_t var_18_10 = 0
00419dc5        arg1[5] = allocate_border(data_4df904 + 0xb4c)
00419dc8        int32_t* eax_17 = set_color_rgba(&var_10, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00419de4        initialize_frontend_widget(arg1[5], 0x14, "Exit", 0x14, 0x41a00000, 390f, eax_17, 2.80259693e-45f)
00419df9        return stack_widget_below(arg1[5], arg1[3])
