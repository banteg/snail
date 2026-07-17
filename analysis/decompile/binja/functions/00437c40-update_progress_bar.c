/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_progress_bar @ 0x437c40 */

00437c40        struct GameRoot* game_base_1 = g_game_base
00437c48        long double x87_r7 = float.t(game_base_1->subgame.first_block_row_count)
00437c60        long double x87_r7_1 = (fconvert.t(game_base_1->subgame.player.body.transform.position.z) - x87_r7) / (float.t(game_base_1->subgame.completion_row_start) - x87_r7)
00437c62        long double temp0 = fconvert.t(0f)
00437c62        x87_r7_1 - temp0
00437c6d        if ((((x87_r7_1 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0) ? 1 : 0) << 0xa | (x87_r7_1 == temp0 ? 1 : 0) << 0xe | 0x3800):1.b & 1) == 0)
00437c79        long double temp1_1 = fconvert.t(1f)
00437c79        x87_r7_1 - temp1_1
00437c84        if ((((x87_r7_1 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp1_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp1_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
00437c88        x87_r7_1 = fconvert.t(1f)
00437c71        x87_r7_1 = fconvert.t(0f)
00437ccd        float height = fconvert.s((fconvert.t(1f) - x87_r7_1) * fconvert.t(232f) + fconvert.t(12f))
00437cdd        float y = fconvert.s(fconvert.t(height) + fconvert.t(150f))
00437ce1        struct tColour color
00437ce1        struct tColour* color_1
00437ce1        int32_t ecx_1
00437ce1        color_1, ecx_1 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00437d00        int32_t var_4c = ecx_1
00437d0e        queue_axis_aligned_textured_quad_uv(0x9d, 12f, fconvert.s(fconvert.t(y) - fconvert.t(39f)), 64f, 64f, 0x1000000, color_1, 0f, 0f, 1f, 1f, 3, 0f)
00437d28        float var_14 = fconvert.s(fconvert.t(height) * fconvert.t(0.00390625f))
00437d72        queue_axis_aligned_textured_quad_uv(0x9b, 13f, 150f, 64f, height, 0x1000000, set_color_rgba(&color, 1f, 1f, 1f, 1f), 0f, 0f, 1f, var_14, 3, 0f)
00437da3        struct tColour* color_2
00437da3        int32_t ecx_4
00437da3        color_2, ecx_4 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00437db8        int32_t var_44_1 = ecx_4
00437dd0        queue_axis_aligned_textured_quad_uv(0x9c, 13f, y, 64f, fconvert.s(fconvert.t(256f) - fconvert.t(height)), 0x1000000, color_2, 0f, var_14, 1f, 1f, 3, 0f)
00437ddc        return
