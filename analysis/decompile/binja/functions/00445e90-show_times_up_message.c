/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: show_times_up_message @ 0x445e90 */

00445e99        if (*arg1 != 0)
00445e99        return 
00445eab        int32_t var_18_1 = 0
00445ec7        arg1[1] = allocate_border(data_4df904 + 0xb4c)
00445eca        struct Color4f color
00445eca        struct Color4f* eax_3 = set_color_rgba(&color, 1f, 1f, 1f, 0.0299999993f)
00445ee6        initialize_frontend_widget(arg1[1], &__dos_header.e_cblp, "Time's Up", 0x14, 0, 200f, eax_3, 2.80259693e-45f)
00445eeb        arg1[2] = 0
00445ef2        arg1[3] = 0x3bb60b61
00445ef9        *arg1 = 1
00445f03        return
