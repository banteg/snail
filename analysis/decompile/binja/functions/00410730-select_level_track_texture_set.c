/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: select_level_track_texture_set @ 0x410730 */

0041073d        int32_t texture_set_1
0041073d        switch (texture_set)
00410744        case 0
00410744        texture_set_1 = 0
00410748        case 1
00410748        texture_set_1 = 1
0041074f        case 2
0041074f        texture_set_1 = 2
00410756        case 3
00410756        texture_set_1 = 3
0041075d        case 5
0041075d        int32_t var_c_1 = 0
00410771        int16_t x87control
00410771        texture_set_1 = ftol(x87control, random_float_below(4f))
00410775        texture_set_1 = texture_set
00410779        int32_t current_texture_set = track->current_texture_set
0041077e        if (texture_set_1 == current_texture_set)
0041077e        return
0041078d        replace_object_list_texture_refs(&g_object_list, track->track_textures[texture_set_1], track->track_textures[current_texture_set])
004107a4        replace_object_list_texture_refs(&g_object_list, track->slide_textures[texture_set_1], track->slide_textures[track->current_texture_set])
004107a9        track->current_texture_set = texture_set_1
004107ae        return
