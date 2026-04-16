/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_galaxy @ 0x408cf0 */

00408d03        hide_star_field(data_4df904 + 0x4f33c)
00408d0a        void* var_20 = &data_4dfb08
00408d0f        int32_t var_24 = 0
00408d15        cache_music_file("music/mainmenu.ogg")
00408d2e        int32_t eax = load_landscape_script_by_name(data_4df904 + 0x106c218, "StarMap.txt")
00408d3a        void* eax_1 = data_4df904
00408d4d        change_backdrop(eax_1 + 0x4ec10, eax_1 + eax * 0x124 + 0x106c7bc, 0)
00408d5e        set_border_justify_centre(data_4df904 + 0xb4c, 0)
00408d6f        capture_mouse_cursor(data_4df904 + 0x290)
00408d7f        *(data_4df904 + 0x56c) = 2
00408d89        void* eax_3 = *(arg1 + 0x10f70)
00408d92        if (*(eax_3 + 0x40) == 0)
00408d94        int32_t ecx_8 = *(eax_3 + 0x1270fc8)
00408da2        if (ecx_8 == 3 || ecx_8 == 2)
00408da4        *(arg1 + 8) = 0
00408da7        *(arg1 + 4) = 0
00408db0        *(arg1 + 0x10f80) = data_4df9bc
00408dbc        if (*(eax_3 + 0x1270fc8) == 1)
00408dbe        *(arg1 + 8) = 1
00408dc1        *(arg1 + 4) = 1
00408dc7        *(arg1 + 0x10f80) = *(eax_3 + 0x44)
00408dd1        if (*(eax_3 + 0x40) == 4)
00408dd3        *(arg1 + 8) = 0
00408dd6        *(arg1 + 4) = 2
00408de2        *(arg1 + 0x10f80) = data_4df9bc
00408e13        *(arg1 + 0x10f78) = allocate_border(data_4df904 + 0xb4c)
00408e19        struct Color4f color_2
00408e19        struct Color4f* color_3 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00408e3b        initialize_frontend_widget(*(arg1 + 0x10f78), &__dos_header, "Intergalactic Delivery Route", 0x14, 15f, 15f, color_3, 0, 0f)
00408e46        *(*(arg1 + 0x10f78) + 0x6f0) = 0x3f547ae1
00408e7b        *(arg1 + 0x10f7c) = allocate_border(data_4df904 + 0xb4c)
00408e81        struct Color4f* eax_8 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00408ea1        initialize_frontend_sprite_button(*(arg1 + 0x10f7c), 0x20400802, 0x8a, 370f, 10f, eax_8, 0f, 4)
00408eb8        *(arg1 + 0x10f74) = allocate_border(data_4df904 + 0xb4c)
00408ed8        uint32_t widget_flags
00408ed8        char* text
00408ed8        struct Color4f* color
00408ed8        if (*(arg1 + 4) != 1)
00408f05        color = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00408f06        int32_t var_2c_1 = 0x43d20000
00408f0b        int32_t var_30_1 = 0x41a00000
00408f10        int32_t var_34_1 = 0x14
00408f12        text = "Back"
00408f17        widget_flags = 0x60000014
00408ee3        color = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00408ee4        int32_t var_2c = 0x43d20000
00408ee9        int32_t var_30 = 0x41a00000
00408eee        int32_t var_34 = 0x14
00408ef0        text = "Exit"
00408ef5        widget_flags = 0x20000014
00408f22        initialize_frontend_widget(*(arg1 + 0x10f74), widget_flags, text, 0x14, 20f, 420f, color, 0, 0f)
00408f2a        int32_t i = 0
00408f2e        if (*(arg1 + 0xc) s> 0)
00408f30        int32_t* eax_14 = arg1 + 0x2c
00408f33        eax_14[-1] = 0
00408f36        *eax_14 = 0
00408f3b        i += 1
00408f3c        eax_14 = &eax_14[0xa8]
00408f43        do while (i s< *(arg1 + 0xc))
00408f70        *(arg1 + 0x10f8c) = allocate_border(data_4df904 + 0xb4c)
00408f76        struct Color4f* color_4 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00408f98        initialize_frontend_widget(*(arg1 + 0x10f8c), 0x20010002, &data_4dfb08, 0x14, 30f, 80f, color_4, 0, 0f)
00408fbd        store_color4f(*(arg1 + 0x10f8c) + 0x1cc, 1f, 1f, 1f, 1f)
00408fc8        hide_border_init(*(arg1 + 0x10f8c))
00408fd3        *(*(arg1 + 0x10f8c) + 0x48) = 0x98
00408fe0        *(*(arg1 + 0x10f8c) + 0x4c) = 0x43a00000
00408fed        *(*(arg1 + 0x10f8c) + 0x50) = 0x43700000
00408ffa        *(*(arg1 + 0x10f8c) + 0x54) = 0x43480000
00409007        *(*(arg1 + 0x10f8c) + 0x58) = 0x42c80000
00409039        *(arg1 + 0x10f90) = allocate_border(data_4df904 + 0xb4c)
0040903f        struct Color4f* color_5 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00409061        initialize_frontend_widget(*(arg1 + 0x10f90), 0x20400002, &data_4dfb08, 0x14, 100f, 80f, color_5, 0, 0f)
0040906c        hide_border_init(*(arg1 + 0x10f90))
0040907c        __builtin_strncpy(*(arg1 + 0x10f90) + 0x6f0, "fff?", 4)
00409088        *(*(arg1 + 0x10f90) + 0x26c) = 0
004090b9        *(arg1 + 0x10f94) = allocate_border(data_4df904 + 0xb4c)
004090bf        struct Color4f* color_6 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
004090e1        initialize_frontend_widget(*(arg1 + 0x10f94), 0x20400002, &data_4dfb08, 0x14, 300f, 440f, color_6, 0, 0f)
004090ec        hide_border_init(*(arg1 + 0x10f94))
004090f7        __builtin_strncpy(*(arg1 + 0x10f94) + 0x6f0, "fff?", 4)
00409103        *(*(arg1 + 0x10f94) + 0x26c) = 0
00409134        *(arg1 + 0x10f98) = allocate_border(data_4df904 + 0xb4c)
0040913a        struct Color4f* color_7 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
0040915c        initialize_frontend_widget(*(arg1 + 0x10f98), 0x20400002, &data_4dfb08, 0x14, 300f, 440f, color_7, 0, 0f)
00409167        hide_border_init(*(arg1 + 0x10f98))
00409172        __builtin_strncpy(*(arg1 + 0x10f98) + 0x6f0, "333?", 4)
00409182        *(*(arg1 + 0x10f98) + 0x26c) = 0
00409199        *(arg1 + 0x10f9c) = allocate_border(data_4df904 + 0xb4c)
004091c5        char* text_1
004091c5        struct Color4f* color_1
004091c5        if (*(*(arg1 + 0x10f70) + 0x40) != 0)
004091ed        color_1 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
004091ee        int32_t var_2c_3 = 0x43dc0000
004091f3        int32_t var_30_3 = 0x43960000
004091f8        int32_t var_34_3 = 0x14
004091fa        text_1 = "Play"
004091d0        color_1 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
004091d1        int32_t var_2c_2 = 0x43dc0000
004091d6        int32_t var_30_2 = 0x43960000
004091db        int32_t var_34_2 = 0x14
004091dd        text_1 = "Deliver!"
0040920a        initialize_frontend_widget(*(arg1 + 0x10f9c), 0x60000014, text_1, 0x14, 300f, 440f, color_1, 2, 100f)
00409215        hide_border_init(*(arg1 + 0x10f9c))
00409220        *(*(arg1 + 0x10f9c) + 0x26c) = 0x41a00000
00409256        *(arg1 + 0x10fa0) = allocate_border(data_4df904 + 0xb4c)
0040925c        struct Color4f* color_8 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
0040927e        initialize_frontend_widget(*(arg1 + 0x10fa0), 0x60000014, "Watch Best Trial", 0x14, 300f, 440f, color_8, 2, 0f)
00409289        hide_border_init(*(arg1 + 0x10fa0))
00409294        *(*(arg1 + 0x10fa0) + 0x26c) = 0x41200000
004092a4        *(*(arg1 + 0x10fa0) + 0x6f0) = 0x3f4ccccd
004092b4        *(*(arg1 + 0x10fa0) + 0x214) = 0x40800000
004092c4        *(*(arg1 + 0x10fa0) + 0x214) = 0x41000000
004092e2        return open_galaxy_route(arg1, *(arg1 + 0x10f80))
