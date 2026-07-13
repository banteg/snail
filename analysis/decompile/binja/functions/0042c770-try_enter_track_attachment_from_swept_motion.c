/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: try_enter_track_attachment_from_swept_motion @ 0x42c770 */

0042c783        float x = source_cell->anchor_position.x
0042c785        uint32_t segment_count = self->segment_count
0042c78c        float y = source_cell->anchor_position.y
0042c78f        int32_t esi = segment_count - 1
0042c794        float z = source_cell->anchor_position.z
0042c79b        if (segment_count - 1 s< 0)
0042c79b        return
0042c7ad        int32_t ebp_2 = esi * 0xa8
0042c7b5        float var_44_1
0042c7b5        float var_40_1
0042c7b5        while (true)
0042c7b5        void* ecx_1 = self->secondary_samples + ebp_2
0042c7b7        long double x87_r7_1 = fconvert.t(*(ecx_1 + 0x14))
0042c7ba        long double temp2_1 = fconvert.t(0f)
0042c7ba        x87_r7_1 - temp2_1
0042c7c5        if ((((x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0042c7ec        float var_1c_1 = fconvert.s(fconvert.t(z) + fconvert.t(*(ecx_1 + 0x38)))
0042c807        long double x87_r7_6 = fconvert.t(world_y) - fconvert.t(fconvert.s(fconvert.t(y) + fconvert.t(*(ecx_1 + 0x34))))
0042c80b        float var_60 = fconvert.s(fconvert.t(world_x) - (fconvert.t(x) + fconvert.t(*(ecx_1 + 0x30))))
0042c80f        var_44_1 = fconvert.s(x87_r7_6)
0042c826        var_40_1 = fconvert.s(fconvert.t(world_z) - fconvert.t(var_1c_1))
0042c832        rotate_vector_by_matrix(&var_60, ecx_1 + 0x40)
0042c837        uint32_t width_cells = self->width_cells
0042c83c        int32_t eax_7
0042c83c        int32_t edx_2
0042c83c        edx_2:eax_7 = sx.q(width_cells)
0042c84b        long double x87_r7_10 = float.t(neg.d((eax_7 - edx_2) s>> 1)) - fconvert.t(0.300000012f)
0042c851        long double temp3_1 = fconvert.t(var_60)
0042c851        x87_r7_10 - temp3_1
0042c85a        if ((((x87_r7_10 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_10, temp3_1) ? 1 : 0) << 0xa | (x87_r7_10 == temp3_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0042c862        int32_t eax_13
0042c862        int32_t edx_3
0042c862        edx_3:eax_13 = sx.q(width_cells)
0042c86f        long double x87_r7_12 = float.t((eax_13 - edx_3) s>> 1) + fconvert.t(0.300000012f)
0042c875        long double temp4_1 = fconvert.t(var_60)
0042c875        x87_r7_12 - temp4_1
0042c87e        if ((((x87_r7_12 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_12, temp4_1) ? 1 : 0) << 0xa | (x87_r7_12 == temp4_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0042c884        long double x87_r7_13 = fconvert.t(var_44_1)
0042c888        long double temp5_1 = fconvert.t(-0.20000000000000001)
0042c888        x87_r7_13 - temp5_1
0042c893        if ((((x87_r7_13 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_13, temp5_1) ? 1 : 0) << 0xa | (x87_r7_13 == temp5_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
0042c899        long double x87_r7_14 = fconvert.t(var_40_1)
0042c89d        long double temp6_1 = fconvert.t(0f)
0042c89d        x87_r7_14 - temp6_1
0042c8a8        if ((((x87_r7_14 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_14, temp6_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp6_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0042c8ae        struct PathTemplateSample* secondary_samples = self->secondary_samples
0042c8b1        long double x87_r7_15 = fconvert.t(var_40_1)
0042c8b5        long double temp7_1 = fconvert.t(*(&secondary_samples->delta_length + ebp_2))
0042c8b5        x87_r7_15 - temp7_1
0042c8bc        void* ecx_4 = secondary_samples + ebp_2
0042c8c4        if ((((x87_r7_15 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_15, temp7_1) ? 1 : 0) << 0xa | (x87_r7_15 == temp7_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0042c8eb        float var_4_1 = fconvert.s(fconvert.t(z) + fconvert.t(*(ecx_4 + 0x38)))
0042c91a        float var_10_1 = fconvert.s(fconvert.t(world_z) + fconvert.t(sweep_dz))
0042c92e        long double x87_r7_20 = fconvert.t(fconvert.s(fconvert.t(world_y) + fconvert.t(sweep_dy))) - fconvert.t(fconvert.s(fconvert.t(y) + fconvert.t(*(ecx_4 + 0x34))))
0042c932        float var_30 = fconvert.s(fconvert.t(sweep_dx) + fconvert.t(world_x) - (fconvert.t(x) + fconvert.t(*(ecx_4 + 0x30))))
0042c936        float var_38_1 = fconvert.s(x87_r7_20)
0042c952        float var_28_1 = fconvert.s(fconvert.t(var_10_1) - fconvert.t(var_4_1))
0042c956        rotate_vector_by_matrix(&var_30, ecx_4 + 0x40)
0042c95b        long double x87_r7_23 = fconvert.t(var_38_1)
0042c95f        long double temp8_1 = fconvert.t(0.00100000005f)
0042c95f        x87_r7_23 - temp8_1
0042c96a        if ((((x87_r7_23 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_23, temp8_1) ? 1 : 0) << 0xa | (x87_r7_23 == temp8_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0042c96a        break
0042c96c        esi -= 1
0042c96d        ebp_2 -= 0xa8
0042c975        if (esi s< 0)
0042c982        return
0042c98a        g_game_base[0x430199] = 0
0042c990        char* game_base_1 = g_game_base
0042c9a2        start_squidge_y(game_base_1 + uninit_thanks_screen, *(game_base_1 + &data_430190))
0042c9b4        g_game_base[0x430100] = 1
0042c9c0        *(g_game_base + 0x430104) = self
0042c9cc        *(g_game_base + 0x430108) = source_cell
0042c9d7        *(g_game_base + 0x43010c) = esi
0042c9e7        *(g_game_base + &data_430110) = fconvert.s(fconvert.t(var_40_1))
0042c9f2        *(g_game_base + 0x430114) = 0
0042ca02        *(g_game_base + 0x42fde8) = fconvert.s(fconvert.t(var_44_1))
0042ca0d        *(g_game_base + &data_430190) = 0
0042ca13        char* game_base_2 = g_game_base
0042ca1e        *(game_base_2 + 0x430138) = &game_base_2[0x42fd7c]
0042ca24        int32_t eax_26 = get_track_cell_row_index(source_cell)
0042ca32        char* game_base_3 = g_game_base
0042ca44        *(*(game_base_3 + 0x430104) + 0x98) = *(game_base_3 + eax_26 * 0xf4 + 0x64118c)
0042ca4f        *(g_game_base + 0x43011c) = 0
0042ca5b        *(g_game_base + 0x430118) = 0
0042ca61        char* game_base_4 = g_game_base
0042ca81        update_track_attachment_follow_state(&game_base_4[0x430100], *(game_base_4 + 0x430194), &game_base_4[0x42fde4], &game_base_4[0x43018c])
0042ca8d        return
