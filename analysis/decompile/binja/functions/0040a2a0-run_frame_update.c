/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: run_frame_update @ 0x40a2a0 */

0040a2aa        update_frontend_transition_overlay(&game->fade)
0040a2be        update_cheat(&g_cheat_state)
0040a2c8        update_voice_manager(&g_voice_manager)
0040a2d3        long double x87_r7_1 = fconvert.t(game->fixed_update_accumulator) + fconvert.t(1f)
0040a2d9        int32_t frame_counter = game->frame_counter
0040a2df        int32_t ebx = 0
0040a2ed        game->frontend_quit_requested = 0
0040a2f0        game->fixed_update_accumulator = fconvert.s(x87_r7_1)
0040a2f6        game->fixed_update_count = 1
0040a2f9        game->frame_counter = frame_counter + 1
0040a2ff        game->input_sampling_gate = 1
0040a305        int32_t var_14 = 0
0040a310        if (is_mouse_captured(&game->players[0].mouse_cursor) != 0)
0040a31a        if (game->players[0].mouse_cursor.suppress_next_draw == 0)
0040a33e        struct tColour color
0040a33e        struct tColour* color_1
0040a33e        int32_t ecx_4
0040a33e        color_1, ecx_4 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0040a35f        int32_t var_34_1 = ecx_4
0040a36f        int32_t var_38_1 = ecx_4
0040a375        queue_axis_aligned_textured_quad(0x16, fconvert.s(fconvert.t(game->players[0].mouse_cursor.saved_x) - fconvert.t(8f)), fconvert.s(fconvert.t(game->players[0].mouse_cursor.saved_y) - fconvert.t(7f)), 64f, 64f, 0x1000000, color_1, 7)
0040a31c        game->players[0].mouse_cursor.suppress_next_draw = 0
0040a37d        long double x87_r7_6 = fconvert.t(game->fixed_update_accumulator)
0040a383        long double temp0 = fconvert.t(1f)
0040a383        x87_r7_6 - temp0
0040a38e        if ((((x87_r7_6 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp0) ? 1 : 0) << 0xa | (x87_r7_6 == temp0 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0040a484        return game->frontend_quit_requested
0040a46b        long double x87_r7_9
0040a46b        long double temp1_1
0040a3a8        game->fixed_update_accumulator = fconvert.s(fconvert.t(game->fixed_update_accumulator) - fconvert.t(1f))
0040a3ae        draw_frontend_overlay_color_lerp(&game->players[0].frontend_overlay)
0040a3b3        struct BodNode* first = game->active_bod_list.first
0040a3bb        if (first != 0)
0040a3c1        while (true)
0040a3c1        if ((first->list_flags.b & 0x10) != 0)
0040a3c8        report_errorf("Debug Bod AI")
0040a3d0        struct BodNode* list_next = first->list_next
0040a3d5        if (list_next != 0)
0040a3d7        uint32_t list_flags = list_next->list_flags
0040a3da        list_flags.b |= 0x40
0040a3dc        list_next->list_flags = list_flags
0040a3e3        (*first->vtable)()
0040a3e9        first = list_next
0040a3ee        var_14 += 1
0040a3f2        if (list_next == 0)
0040a3f2        break
0040a3f4        uint32_t list_flags_1 = list_next->list_flags
0040a3f7        list_flags_1.b &= 0xbf
0040a3f9        list_next->list_flags = list_flags_1
0040a40a        (*game->players[0].body.bod.bod.vtable)()
0040a413        if (game->subgame.level_mode == 6)
0040a421        (*game->players[1].body.bod.bod.vtable)()
0040a423        struct Sprite** i = &g_sprite_active_heads
0040a446        while (i s< &g_sprite_free_head)
0040a428        struct Sprite* sprite = *i
0040a42c        if (sprite != 0)
0040a43b        struct Sprite* next
0040a42e        next = sprite->next
0040a431        update_sprite(sprite)
0040a436        ebx += 1
0040a437        sprite = next
0040a43b        do while (next != 0)
0040a43d        i = &i[1]
0040a44e        initialize_enemy_manager(&game->subgame.enemy_manager)
0040a453        x87_r7_9 = fconvert.t(game->fixed_update_accumulator)
0040a459        temp1_1 = fconvert.t(1f)
0040a459        x87_r7_9 - temp1_1
0040a45f        game->input_sampling_gate = 0
0040a46b        do while ((((x87_r7_9 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp1_1) ? 1 : 0) << 0xa | (x87_r7_9 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0040a47b        return game->frontend_quit_requested
