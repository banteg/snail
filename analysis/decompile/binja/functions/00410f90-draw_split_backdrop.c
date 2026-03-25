/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: draw_split_backdrop @ 0x410f90 */

00410fc0        void var_10
00410fc0        int32_t* eax = set_color_rgba(&var_10, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00410fdd        queue_axis_aligned_textured_quad_uv(*(arg1 + 0x3c), 0, 0, 512f, 512f, 0x8000000, eax, 0, 0, 0x3f800000, 0x3f800000, 0, 0)
0041100f        int32_t* eax_2 = set_color_rgba(&var_10, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
0041103b        return queue_axis_aligned_textured_quad_uv(*(arg1 + 0x44), 0x44000000, 0, 128f, 512f, 0x8000000, eax_2, 0, 0, 0x3f800000, 0x3f800000, 0, 0)
