/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: draw_split_backdrop @ 0x410f90 */

00410fc0        struct tColour color
00410fc0        struct tColour* color_1 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00410fdd        queue_axis_aligned_textured_quad_uv(backdrop->active_primary_texture_id, 0f, 0f, 512f, 512f, 0x8000000, color_1, 0f, 0f, 1f, 1f, 0, 0f)
0041100f        struct tColour* color_2 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0041103b        return queue_axis_aligned_textured_quad_uv(backdrop->active_secondary_texture_id, 512f, 0f, 128f, 512f, 0x8000000, color_2, 0f, 0f, 1f, 1f, 0, 0f)
