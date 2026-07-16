/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: build_track_colours @ 0x435d40 */

00435d42        int32_t i = 0
00435dd8        while (i s< 0x330)
00435d4a        set_color_white(i + &g_loc_colour_lookup_check_black)
00435d55        set_color_white(i + &g_loc_colour_lookup_floor_slide_0)
00435d60        set_color_white(i + &g_loc_colour_lookup_floor_slide_0.slide_0)
00435d6b        set_color_white(i + &g_loc_colour_lookup_slide_1)
00435d76        set_color_white(i + &g_loc_colour_lookup_wall)
00435d81        set_color_white(i + &g_loc_colour_lookup_trampoline)
00435d8c        set_color_white(i + &g_loc_colour_lookup_ramp)
00435d97        set_color_white(i + &g_loc_colour_lookup_empty)
00435da2        set_color_white(i + &g_loc_colour_lookup_path)
00435daf        set_color_white(i + &g_loc_colour_lookup_path_worm)
00435db6        set_color_white(i + &g_loc_colour_lookup_path_worm)
00435dc3        set_color_white(i + &g_loc_colour_lookup_path_warp)
00435dca        set_color_white(i + &g_loc_colour_lookup_path_warp)
00435dcf        i += 0x10
00435de0        return
