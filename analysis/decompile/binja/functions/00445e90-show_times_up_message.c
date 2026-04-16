/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: show_times_up_message @ 0x445e90 */

00445e99        if (*arg1 != 0)
00445e99        return 
00445ec7        arg1[1] = allocate_border(data_4df904 + 0xb4c)
00445eca        struct Color4f color
00445eca        struct Color4f* color_1 = set_color_rgba(&color, 1f, 1f, 1f, 0.0299999993f)
00445ee6        initialize_frontend_widget(arg1[1], &__dos_header.e_cblp, "Time's Up", 0x14, 0f, 200f, color_1, 2, 0f)
00445eeb        arg1[2] = 0
00445ef2        arg1[3] = 0x3bb60b61
00445ef9        *arg1 = 1
00445f03        return
