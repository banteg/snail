/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_sub_loc @ 0x439d50 */

00439d5c        if (((cell->lane_and_flags).w:1.b & 0x20) == 0)
00439d5c        return
00439d62        struct GameRoot* game_base_1 = g_game_base
00439d68        uint16_t eax_1
00439d68        eax_1.b = game_base_1->subgame.subgame_pause_gate
00439d70        if (eax_1.b != 0)
00439d70        return
00439d76        eax_1.b = cell->tile_id
00439d7b        struct Vec3 var_34
00439d7b        struct tColour out
00439d7b        if (eax_1.b == 0xe)
00439d81        long double x87_r7_1 = float.t(game_base_1->subgame.first_block_row_count)
00439d87        long double temp0_1 = fconvert.t(game_base_1->subgame.player.body.transform.position.z)
00439d87        x87_r7_1 - temp0_1
00439d92        if ((((x87_r7_1 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp0_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00439d98        void* __saved_edi_1 = &data_4a4dc8
00439da2        long double st0_1 = random_float_below(100f)
00439da7        long double temp3_1 = fconvert.t(4f)
00439da7        st0_1 - temp3_1
00439db5        if ((((st0_1 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(st0_1, temp3_1) ? 1 : 0) << 0xa | (st0_1 == temp3_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
00439edb        game_base_1 = g_game_base
00439dbb        float x = cell->anchor_position.x
00439dbe        var_34.y = 0
00439dd1        float z = cell->anchor_position.z
00439dd4        struct Vec3 origin
00439dd4        origin.x = x
00439de9        var_34.x = cell->lane_and_flags u>> 8 & 0xf
00439df5        char* __saved_edi_2 = "Wall2"
00439dff        float z_1 = z
00439e03        origin.y = fconvert.s(fconvert.t(cell->anchor_position.y) + fconvert.t(8f))
00439e0d        origin.z = z
00439e15        origin.x = fconvert.s(float.t(var_34.x.q) * fconvert.t(0.5f) + fconvert.t(x))
00439e19        long double st0_2 = random_signed_float_below(3f)
00439e1e        game_base_1 = g_game_base
00439e3f        out.r = game_base_1->subgame.player.body.transform.position.x
00439e43        out.g = game_base_1->subgame.player.body.transform.position.y
00439e5f        var_34.x = fconvert.s(fconvert.t(out.r) - fconvert.t(origin.x))
00439e6b        long double x87_r7_11 = st0_2 + fconvert.t(8f) + fconvert.t(game_base_1->subgame.player.body.transform.position.z) - fconvert.t(origin.z)
00439e6f        var_34.y = fconvert.s(fconvert.t(out.g) - fconvert.t(origin.y))
00439e77        long double temp4_1 = fconvert.t(-4f)
00439e77        x87_r7_11 - temp4_1
00439e81        var_34.z = fconvert.s(x87_r7_11)
00439e8a        if ((((x87_r7_11 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_11, temp4_1) ? 1 : 0) << 0xa | (x87_r7_11 == temp4_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00439e90        normalize_vector(&var_34)
00439eb6        var_34.x = fconvert.s(fconvert.t(var_34.x) * fconvert.t(0.400000006f))
00439ec4        var_34.y = fconvert.s(fconvert.t(var_34.y) * fconvert.t(0.400000006f))
00439ed2        var_34.z = fconvert.s(fconvert.t(var_34.z) * fconvert.t(0.400000006f))
00439ed6        shoot_subgoldy(&g_game_base->subgame.sub_lazers, &origin, &var_34)
00439edb        game_base_1 = g_game_base
00439ee1        long double x87_r7_20 = fconvert.t(cell->anchor_position.z)
00439ee4        long double temp2_1 = fconvert.t(game_base_1->subgame.player.interaction_max_z)
00439ee4        x87_r7_20 - temp2_1
00439eef        if ((((x87_r7_20 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_20, temp2_1) ? 1 : 0) << 0xa | (x87_r7_20 == temp2_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00439ef7        remove_sub_loc(cell)
00439f03        if (eax_1.b == 0x16)
00439f05        long double x87_r7_21 = fconvert.t(cell->anchor_position.z)
00439f08        long double temp1_1 = fconvert.t(game_base_1->subgame.player.interaction_max_z)
00439f08        x87_r7_21 - temp1_1
00439f13        if ((((x87_r7_21 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_21, temp1_1) ? 1 : 0) << 0xa | (x87_r7_21 == temp1_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00439f1b        remove_sub_loc(cell)
00439f2b        if (eax_1.b == 0x1d || eax_1.b == 0x1e)
00439f73        if (cell->attachment_template_record->kind == PATH_TEMPLATE_KIND_WORM)
00439f8c        cell->render_arg_20 = fconvert.s(fconvert.t(cell->render_arg_20) - fconvert.t(game_base_1->subgame.subgame_rate) * fconvert.t(0.0333333351f))
00439f8f        set_color_alpha(&cell->color, 0.800000012f)
00439f94        game_base_1 = g_game_base
00439fa6        struct tColour* eax_11 = get_track_skirt_color(&game_base_1->subgame, &out)
00439fc2        int32_t* ecx_12 = &g_game_base->subgame.runtime_rows[get_track_cell_row_index(cell)].attachment_body.color
00439fcb        *ecx_12 = eax_11->r
00439fd0        ecx_12[1] = eax_11->g
00439fd6        ecx_12[2] = eax_11->b
00439fdd        ecx_12[3] = eax_11->a
00439ff2        long double x87_r7_29 = fconvert.t(g_game_base->subgame.player.interaction_max_z) - (float.t(cell->attachment_template_record->row_span_count) + fconvert.t(5f))
00439ff8        long double temp5_1 = fconvert.t(cell->anchor_position.z)
00439ff8        x87_r7_29 - temp5_1
0043a000        if ((((x87_r7_29 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_29, temp5_1) ? 1 : 0) << 0xa | (x87_r7_29 == temp5_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043a004        remove_sub_loc(cell)
00439f2d        long double x87_r7_22 = fconvert.t(cell->anchor_position.z)
00439f30        long double temp6_1 = fconvert.t(game_base_1->subgame.player.interaction_max_z)
00439f30        x87_r7_22 - temp6_1
00439f3b        if ((((x87_r7_22 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_22, temp6_1) ? 1 : 0) << 0xa | (x87_r7_22 == temp6_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00439f4a        var_34.x = game_base_1->subgame.completion_row_start - 5
00439f4e        long double x87_r7_23 = float.t(var_34.x)
00439f52        long double temp7_1 = fconvert.t(cell->anchor_position.z)
00439f52        x87_r7_23 - temp7_1
00439f5a        if ((((x87_r7_23 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_23, temp7_1) ? 1 : 0) << 0xa | (x87_r7_23 == temp7_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00439f62        remove_sub_loc(cell)
0043a00d        return
