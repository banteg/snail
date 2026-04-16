/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: get_track_skirt_color @ 0x442120 */

00442142        struct Color4f color
00442142        struct Color4f* eax_1 = set_color_rgba(&color, *(arg1 + 0x1b0140), *(arg1 + 0x1b0144), *(arg1 + 0x1b0148), 0.400000006f)
00442151        *arg2 = eax_1->r
00442156        arg2[1] = eax_1->g
0044215c        arg2[2] = eax_1->b
00442163        arg2[3] = eax_1->a
00442169        return arg2
