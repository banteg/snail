/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_thanks_for_playing_screen @ 0x433fd0 */

00433fe1        hide_star_field(data_4df904 + 0x4f33c)
00433fe6        void* var_18 = &data_4dfb08
00433feb        int32_t var_1c = 0
00433ff2        cache_music_file("music/introtext.ogg")
0043400b        int32_t eax = load_landscape_script_by_name(data_4df904 + 0x106c218, "Splash.txt")
00434018        void* eax_1 = data_4df904
0043402b        change_backdrop(eax_1 + 0x4ec10, eax_1 + eax * 0x124 + 0x106c7bc, 0)
0043403d        set_border_justify_centre(data_4df904 + 0xb4c, 0)
00434053        int32_t var_18_1 = 0
0043406f        *(arg1 + 4) = allocate_border(data_4df904 + 0xb4c)
00434072        struct Color4f color
00434072        struct Color4f* eax_4 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0043408e        float* result = initialize_frontend_widget(*(arg1 + 4), 0x20400002, "Thanks For Playing!", 0x14, 0, 435f, eax_4, 2.80259693e-45f)
00434096        *(*(arg1 + 4) + 0x6f0) = 0x3f99999a
004340a0        *(arg1 + 0xc) = 0
004340a7        *(arg1 + 0x10) = 0x3b888889
004340ae        *(arg1 + 8) = 0
004340b9        return result
