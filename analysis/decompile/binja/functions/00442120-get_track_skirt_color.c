/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: get_track_skirt_color @ 0x442120 */

00442142        struct tColour color
00442142        struct tColour* eax_1 = set_color_rgba(&color, game->level_definition.fringe_color.r, game->level_definition.fringe_color.g, game->level_definition.fringe_color.b, 0.400000006f)
0044214f        int32_t esi
0044214f        esi.b = eax_1->r.b
0044214f        esi:1.b = eax_1->r:1.b
0044214f        esi:2.b = eax_1->r:2.b
0044214f        esi:3.b = eax_1->r:3.b
00442151        out->r = esi
00442156        out->g = eax_1->g
00442159        float esi_2
00442159        esi_2.b = eax_1->b.b
00442159        esi_2:1.b = eax_1->b:1.b
0044215c        out->b = esi_2
00442163        out->a = eax_1->a
00442169        return out
