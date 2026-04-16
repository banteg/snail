/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_help_screen @ 0x416800 */

00416804        void* var_18 = &data_4dfb08
00416809        int32_t var_1c = 0
00416812        cache_music_file("music/mainmenu.ogg")
0041682a        int32_t eax_1 = load_landscape_script_by_name(data_4df904 + 0x106c218, "Help.txt")
00416837        void* eax_2 = data_4df904
0041684a        change_backdrop(eax_2 + 0x4ec10, eax_2 + eax_1 * 0x124 + 0x106c7bc, 0)
0041685d        set_border_justify_centre(data_4df904 + 0xb4c, 0)
0041688e        *arg1 = allocate_border(data_4df904 + 0xb4c)
00416890        struct Color4f color
00416890        struct Color4f* color_1 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
004168b4        return initialize_frontend_widget(*arg1, 0x40000014, "Back", 0x14, 0f, 420f, color_1, 2, 0f)
