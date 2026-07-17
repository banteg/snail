/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: try_enter_track_attachment_from_swept_motion @ 0x42c770 */

0042c783        float x = source_cell->anchor_position.x
0042c785        uint32_t segment_count = self->segment_count
0042c78c        float y = source_cell->anchor_position.y
0042c78f        uint32_t esi = segment_count - 1
0042c794        float z = source_cell->anchor_position.z
0042c79b        if (segment_count - 1 s< 0)
0042c79b        return
0042c7ad        int32_t ebp_2 = esi * 0xa8
0042c7b5        struct Vec3 vector
0042c7b5        while (true)
0042c7b5        struct PathTemplateSample* sample = self->secondary_samples + ebp_2
0042c7b7        long double x87_r7_1 = fconvert.t(sample->transform.basis_up.y)
0042c7ba        long double temp2_1 = fconvert.t(0f)
0042c7ba        x87_r7_1 - temp2_1
0042c7c5        if ((((x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0042c80b        vector.x = fconvert.s(fconvert.t(world_x) - (fconvert.t(x) + fconvert.t(sample->transform.position.x)))
0042c822        vector.y = fconvert.s(fconvert.t(world_y) - fconvert.t(fconvert.s(fconvert.t(y) + fconvert.t(sample->transform.position.y))))
0042c82e        vector.z = fconvert.s(fconvert.t(world_z) - fconvert.t(fconvert.s(fconvert.t(z) + fconvert.t(sample->transform.position.z))))
0042c832        rotate_vector_by_matrix(&vector, &sample->inverse_matrix)
0042c837        uint32_t width_cells = self->width_cells
0042c83c        int32_t eax_7
0042c83c        int32_t edx_2
0042c83c        edx_2:eax_7 = sx.q(width_cells)
0042c84b        long double x87_r7_10 = float.t(neg.d((eax_7 - edx_2) s>> 1)) - fconvert.t(0.300000012f)
0042c851        long double temp3_1 = fconvert.t(vector.x)
0042c851        x87_r7_10 - temp3_1
0042c85a        if ((((x87_r7_10 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_10, temp3_1) ? 1 : 0) << 0xa | (x87_r7_10 == temp3_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0042c862        int32_t eax_13
0042c862        int32_t edx_3
0042c862        edx_3:eax_13 = sx.q(width_cells)
0042c86f        long double x87_r7_12 = float.t((eax_13 - edx_3) s>> 1) + fconvert.t(0.300000012f)
0042c875        long double temp4_1 = fconvert.t(vector.x)
0042c875        x87_r7_12 - temp4_1
0042c87e        if ((((x87_r7_12 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_12, temp4_1) ? 1 : 0) << 0xa | (x87_r7_12 == temp4_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0042c884        long double x87_r7_13 = fconvert.t(vector.y)
0042c888        long double temp5_1 = fconvert.t(-0.20000000000000001)
0042c888        x87_r7_13 - temp5_1
0042c893        if ((((x87_r7_13 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_13, temp5_1) ? 1 : 0) << 0xa | (x87_r7_13 == temp5_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
0042c899        long double x87_r7_14 = fconvert.t(vector.z)
0042c89d        long double temp6_1 = fconvert.t(0f)
0042c89d        x87_r7_14 - temp6_1
0042c8a8        if ((((x87_r7_14 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_14, temp6_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp6_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0042c8ae        struct PathTemplateSample* secondary_samples = self->secondary_samples
0042c8b1        long double x87_r7_15 = fconvert.t(vector.z)
0042c8b5        long double temp7_1 = fconvert.t(*(&secondary_samples->delta_length + ebp_2))
0042c8b5        x87_r7_15 - temp7_1
0042c8bc        struct PathTemplateSample* swept_sample = secondary_samples + ebp_2
0042c8c4        if ((((x87_r7_15 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_15, temp7_1) ? 1 : 0) << 0xa | (x87_r7_15 == temp7_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0042c932        struct Vec3 vector_1
0042c932        vector_1.x = fconvert.s(fconvert.t(sweep_dx) + fconvert.t(world_x) - (fconvert.t(x) + fconvert.t(swept_sample->transform.position.x)))
0042c946        vector_1.y = fconvert.s(fconvert.t(fconvert.s(fconvert.t(world_y) + fconvert.t(sweep_dy))) - fconvert.t(fconvert.s(fconvert.t(y) + fconvert.t(swept_sample->transform.position.y))))
0042c952        vector_1.z = fconvert.s(fconvert.t(fconvert.s(fconvert.t(world_z) + fconvert.t(sweep_dz))) - fconvert.t(fconvert.s(fconvert.t(z) + fconvert.t(swept_sample->transform.position.z))))
0042c956        rotate_vector_by_matrix(&vector_1, &swept_sample->inverse_matrix)
0042c95b        long double x87_r7_23 = fconvert.t(vector_1.y)
0042c95f        long double temp8_1 = fconvert.t(0.00100000005f)
0042c95f        x87_r7_23 - temp8_1
0042c96a        if ((((x87_r7_23 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_23, temp8_1) ? 1 : 0) << 0xa | (x87_r7_23 == temp8_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0042c96a        break
0042c96c        esi -= 1
0042c96d        ebp_2 -= 0xa8
0042c975        if (esi s< 0)
0042c982        return
0042c98a        g_game_base->subgame.player.attachment_exit_pending = 0
0042c990        struct GameRoot* game_base_1 = g_game_base
0042c9a2        start_squidge_y(&game_base_1->subgame.player.squidge, game_base_1->subgame.player.velocity.y)
0042c9b4        g_game_base->subgame.player.follow_state.active = 1
0042c9c0        g_game_base->subgame.player.follow_state.template_record = self
0042c9cc        g_game_base->subgame.player.follow_state.source_cell = source_cell
0042c9d7        g_game_base->subgame.player.follow_state.sample_index = esi
0042c9e7        g_game_base->subgame.player.follow_state.progress = fconvert.s(fconvert.t(vector.z))
0042c9f2        g_game_base->subgame.player.follow_state.vertical_offset = 0f
0042ca02        g_game_base->subgame.player.body.transform.position.y = fconvert.s(fconvert.t(vector.y))
0042ca0d        g_game_base->subgame.player.velocity.y = 0f
0042ca13        struct GameRoot* game_base_2 = g_game_base
0042ca1e        game_base_2->subgame.player.follow_state.player = &game_base_2->subgame.player
0042ca24        int32_t eax_26 = get_track_cell_row_index(source_cell)
0042ca32        struct GameRoot* game_base_3 = g_game_base
0042ca44        game_base_3->subgame.player.follow_state.template_record->installed_heading_delta = (&game_base_3->subgame.runtime_rows[0].installed_heading_delta)[eax_26 * 0x3d]
0042ca4f        g_game_base->subgame.player.follow_state.orientation_b = 0f
0042ca5b        g_game_base->subgame.player.follow_state.orientation_a = 0f
0042ca61        struct GameRoot* game_base_4 = g_game_base
0042ca81        update_track_attachment_follow_state(&game_base_4->subgame.player.follow_state, game_base_4->subgame.player.velocity.z, &game_base_4->subgame.player.body.transform.position, &game_base_4->subgame.player.velocity)
0042ca8d        return
