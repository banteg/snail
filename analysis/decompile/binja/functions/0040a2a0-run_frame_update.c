/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: run_frame_update @ 0x40a2a0 */

0040a2aa        update_frontend_transition_overlay(arg1 + 0x24)
0040a2be        update_cheat(&data_4b2f40)
0040a2c8        update_voice_manager(0x751498)
0040a2d3        long double x87_r7_1 = fconvert.t(*(arg1 + 0x518)) + fconvert.t(1f)
0040a2d9        int32_t edx = *(arg1 + 0x51c)
0040a2df        int32_t ebx = 0
0040a2ed        *(arg1 + 0x38) = 0
0040a2f0        *(arg1 + 0x518) = fconvert.s(x87_r7_1)
0040a2f6        *(arg1 + 0x3c) = 1
0040a2f9        *(arg1 + 0x51c) = edx + 1
0040a2ff        *(arg1 + 0x520) = 1
0040a305        int32_t var_14 = 0
0040a310        if (is_mouse_captured(arg1 + 0x290) != 0)
0040a31a        if (*(arg1 + 0x2a4) == 0)
0040a33e        struct Color4f color
0040a33e        int32_t* eax_2
0040a33e        int32_t ecx_4
0040a33e        eax_2, ecx_4 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0040a35f        int32_t var_34_1 = ecx_4
0040a36f        int32_t var_38_1 = ecx_4
0040a375        queue_axis_aligned_textured_quad(0x16, fconvert.s(fconvert.t(*(arg1 + 0x29c)) - fconvert.t(8f)), fconvert.s(fconvert.t(*(arg1 + 0x2a0)) - fconvert.t(7f)), 64f, 64f, 0x1000000, eax_2, 7)
0040a31c        *(arg1 + 0x2a4) = 0
0040a37d        long double x87_r7_6 = fconvert.t(*(arg1 + 0x518))
0040a383        long double temp0 = fconvert.t(1f)
0040a383        x87_r7_6 - temp0
0040a38e        if ((((x87_r7_6 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp0) ? 1 : 0) << 0xa | (x87_r7_6 == temp0 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0040a484        return *(arg1 + 0x38)
0040a46b        long double x87_r7_9
0040a46b        long double temp1_1
0040a3a8        *(arg1 + 0x518) = fconvert.s(fconvert.t(*(arg1 + 0x518)) - fconvert.t(1f))
0040a3ae        draw_frontend_overlay_color_lerp(arg1 + 0x2a8)
0040a3b3        int32_t* edi_1 = *(arg1 + 0x5ac)
0040a3bb        if (edi_1 != 0)
0040a3c1        while (true)
0040a3c1        if ((edi_1[1].b & 0x10) != 0)
0040a3c8        report_errorf("Debug Bod AI")
0040a3d0        int32_t* esi_1 = edi_1[3]
0040a3d5        if (esi_1 != 0)
0040a3d7        int32_t eax_4 = esi_1[1]
0040a3da        eax_4.b |= 0x40
0040a3dc        esi_1[1] = eax_4
0040a3e3        (**edi_1)()
0040a3e9        edi_1 = esi_1
0040a3ee        var_14 += 1
0040a3f2        if (esi_1 == 0)
0040a3f2        break
0040a3f4        int32_t eax_6 = esi_1[1]
0040a3f7        eax_6.b &= 0xbf
0040a3f9        esi_1[1] = eax_6
0040a40a        (**(arg1 + 0x124))()
0040a413        if (*(arg1 + 0x74658) == 6)
0040a421        (**(arg1 + 0x31c))()
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
0040a44e        initialize_enemy_manager(arg1 + 0x12e55ec)
0040a453        x87_r7_9 = fconvert.t(*(arg1 + 0x518))
0040a459        temp1_1 = fconvert.t(1f)
0040a459        x87_r7_9 - temp1_1
0040a45f        *(arg1 + 0x520) = 0
0040a46b        do while ((((x87_r7_9 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp1_1) ? 1 : 0) << 0xa | (x87_r7_9 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0040a47b        return *(arg1 + 0x38)
