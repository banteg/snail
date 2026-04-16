/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: draw_split_backdrop @ 0x410f90 */

00410fc0        struct Color4f color
00410fc0        struct Color4f* eax = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00410fdd        queue_axis_aligned_textured_quad_uv(*(arg1 + 0x3c), 0, 0, 512f, 512f, 0x8000000, eax, 0, 0, 0x3f800000, 0x3f800000, 0, 0)
0041100f        struct Color4f* eax_2 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0041103b        return queue_axis_aligned_textured_quad_uv(*(arg1 + 0x44), 0x44000000, 0, 128f, 512f, 0x8000000, eax_2, 0, 0, 0x3f800000, 0x3f800000, 0, 0)
