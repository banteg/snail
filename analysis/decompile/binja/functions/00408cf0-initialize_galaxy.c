/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
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
00408df9        int32_t var_20_1 = 0
00408e13        *(arg1 + 0x10f78) = allocate_border(data_4df904 + 0xb4c)
00408e19        struct Color4f color
00408e19        struct Color4f* eax_6 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00408e3b        initialize_frontend_widget(*(arg1 + 0x10f78), &__dos_header, "Intergalactic Delivery Route", 0x14, 0x41700000, 15f, eax_6, 0f)
00408e46        *(*(arg1 + 0x10f78) + 0x6f0) = 0x3f547ae1
00408e7b        *(arg1 + 0x10f7c) = allocate_border(data_4df904 + 0xb4c)
00408e81        struct Color4f* eax_9 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00408ea1        initialize_frontend_sprite_button(*(arg1 + 0x10f7c), 0x20400802, 0x8a, 0x43b90000, 0x41200000, eax_9, 0f, 4)
00408eb7        int32_t var_20_2 = 0
00408eb8        *(arg1 + 0x10f74) = allocate_border(data_4df904 + 0xb4c)
00408ed8        int32_t var_3c
00408ed8        char* var_38
00408ed8        struct Color4f* var_28_2
00408ed8        if (*(arg1 + 4) != 1)
00408f05        var_28_2 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00408f06        int32_t var_2c_1 = 0x43d20000
00408f0b        int32_t var_30_1 = 0x41a00000
00408f10        int32_t var_34_1 = 0x14
00408f12        var_38 = "Back"
00408f17        var_3c = 0x60000014
00408ee3        var_28_2 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00408ee4        int32_t var_2c = 0x43d20000
00408ee9        int32_t var_30 = 0x41a00000
00408eee        int32_t var_34 = 0x14
00408ef0        var_38 = "Exit"
00408ef5        var_3c = 0x20000014
00408f22        initialize_frontend_widget(*(arg1 + 0x10f74), var_3c, var_38, 0x14, 0x41a00000, 420f, var_28_2, 0f)
00408f2a        int32_t i = 0
00408f2e        if (*(arg1 + 0xc) s> 0)
00408f30        int32_t* eax_15 = arg1 + 0x2c
00408f33        eax_15[-1] = 0
00408f36        *eax_15 = 0
00408f3b        i += 1
00408f3c        eax_15 = &eax_15[0xa8]
00408f43        do while (i s< *(arg1 + 0xc))
00408f56        int32_t var_20_3 = 0
00408f70        *(arg1 + 0x10f8c) = allocate_border(data_4df904 + 0xb4c)
00408f76        struct Color4f* eax_17 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00408f98        initialize_frontend_widget(*(arg1 + 0x10f8c), 0x20010002, &data_4dfb08, 0x14, 0x41f00000, 80f, eax_17, 0f)
00408fbd        store_color4f(*(arg1 + 0x10f8c) + 0x1cc, 1f, 1f, 1f, 1f)
00408fc8        hide_border_init(*(arg1 + 0x10f8c))
00408fd3        __builtin_memcpy(*(arg1 + 0x10f8c) + 0x48, "\x98\x00\x00\x00\x00\x00\xa0\x43\x00\x00\x70\x43\x00\x00\x48\x43\x00\x00\xc8\x42", 0x14)
00408fda        *(arg1 + 0x10f8c)
00408fe7        *(arg1 + 0x10f8c)
00408ff4        *(arg1 + 0x10f8c)
00409001        *(arg1 + 0x10f8c)
0040901f        int32_t var_20_4 = 0
00409039        *(arg1 + 0x10f90) = allocate_border(data_4df904 + 0xb4c)
0040903f        struct Color4f* eax_21 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00409061        initialize_frontend_widget(*(arg1 + 0x10f90), 0x20400002, &data_4dfb08, 0x14, 0x42c80000, 80f, eax_21, 0f)
0040906c        hide_border_init(*(arg1 + 0x10f90))
0040907c        __builtin_strncpy(*(arg1 + 0x10f90) + 0x6f0, "fff?", 4)
00409088        *(*(arg1 + 0x10f90) + 0x26c) = 0
0040909f        int32_t var_20_5 = 0
004090b9        *(arg1 + 0x10f94) = allocate_border(data_4df904 + 0xb4c)
004090bf        struct Color4f* eax_24 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
004090e1        initialize_frontend_widget(*(arg1 + 0x10f94), 0x20400002, &data_4dfb08, 0x14, 0x43960000, 440f, eax_24, 0f)
004090ec        hide_border_init(*(arg1 + 0x10f94))
004090f7        __builtin_strncpy(*(arg1 + 0x10f94) + 0x6f0, "fff?", 4)
00409103        *(*(arg1 + 0x10f94) + 0x26c) = 0
0040911a        int32_t var_20_6 = 0
00409134        *(arg1 + 0x10f98) = allocate_border(data_4df904 + 0xb4c)
0040913a        struct Color4f* eax_27 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0040915c        initialize_frontend_widget(*(arg1 + 0x10f98), 0x20400002, &data_4dfb08, 0x14, 0x43960000, 440f, eax_27, 0f)
00409167        hide_border_init(*(arg1 + 0x10f98))
00409172        __builtin_strncpy(*(arg1 + 0x10f98) + 0x6f0, "333?", 4)
00409182        *(*(arg1 + 0x10f98) + 0x26c) = 0
00409199        *(arg1 + 0x10f9c) = allocate_border(data_4df904 + 0xb4c)
004091a5        int32_t var_20_7 = 0x42c80000
004091c5        char* var_38_1
004091c5        struct Color4f* var_28_7
004091c5        if (*(*(arg1 + 0x10f70) + 0x40) != 0)
004091ed        var_28_7 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
004091ee        int32_t var_2c_3 = 0x43dc0000
004091f3        int32_t var_30_3 = 0x43960000
004091f8        int32_t var_34_3 = 0x14
004091fa        var_38_1 = "Play"
004091d0        var_28_7 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
004091d1        int32_t var_2c_2 = 0x43dc0000
004091d6        int32_t var_30_2 = 0x43960000
004091db        int32_t var_34_2 = 0x14
004091dd        var_38_1 = "Deliver!"
0040920a        initialize_frontend_widget(*(arg1 + 0x10f9c), 0x60000014, var_38_1, 0x14, 0x43960000, 440f, var_28_7, 2.80259693e-45f)
00409215        hide_border_init(*(arg1 + 0x10f9c))
00409220        *(*(arg1 + 0x10f9c) + 0x26c) = 0x41a00000
0040923b        int32_t var_20_8 = 0
00409256        *(arg1 + 0x10fa0) = allocate_border(data_4df904 + 0xb4c)
0040925c        struct Color4f* eax_34 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0040927e        initialize_frontend_widget(*(arg1 + 0x10fa0), 0x60000014, "Watch Best Trial", 0x14, 0x43960000, 440f, eax_34, 2.80259693e-45f)
00409289        hide_border_init(*(arg1 + 0x10fa0))
00409294        *(*(arg1 + 0x10fa0) + 0x26c) = 0x41200000
004092a4        *(*(arg1 + 0x10fa0) + 0x6f0) = 0x3f4ccccd
004092b4        *(*(arg1 + 0x10fa0) + 0x214) = 0x40800000
004092c4        *(*(arg1 + 0x10fa0) + 0x214) = 0x41000000
004092e2        return open_galaxy_route(arg1, *(arg1 + 0x10f80))
