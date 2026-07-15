/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_golb_ai @ 0x414820 */

00414829        struct TrackRowCell* game = arg1->game
00414834        if (game->bod.list_prev:1.b == 0)
00414841        if (arg1->skip_one_tick == 1)
00414844        arg1->skip_one_tick = 0
00414851        return game
00414852        int32_t state = arg1->state
00414858        game = state - 1
00414859        if (state == 1)
0041486d        struct Vec3 vector_1
0041486d        if (arg1->path_follow.active != 1)
004148f1        arg1->flight_transform.position.x = fconvert.s(fconvert.t(arg1->velocity.x) + fconvert.t(arg1->flight_transform.position.x))
004148f9        arg1->flight_transform.position.y = fconvert.s(fconvert.t(arg1->velocity.y) + fconvert.t(arg1->flight_transform.position.y))
00414902        arg1->flight_transform.position.z = fconvert.s(fconvert.t(arg1->velocity.z) + fconvert.t(arg1->flight_transform.position.z))
00414905        int32_t kind = arg1->kind
0041490d        if (kind == 0)
0041490f        long double x87_r7_7 = fconvert.t(arg1->flight_transform.position.y)
00414915        long double temp2_1 = fconvert.t(0.49000001f)
00414915        x87_r7_7 - temp2_1
00414920        long double x87_r7_8
00414920        long double temp5_1
00414920        if ((((x87_r7_7 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp2_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
00414922        x87_r7_8 = fconvert.t(arg1->flight_transform.position.y)
00414928        temp5_1 = fconvert.t(0f)
00414928        x87_r7_8 - temp5_1
00414933        if ((((x87_r7_7 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp2_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0 || (((x87_r7_8 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp5_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp5_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00414959        arg1->velocity.y = fconvert.s(fconvert.t(arg1->velocity.y) - fconvert.t(arg1->game->subgame_rate) * fconvert.t(0.0170000009f))
00414935        arg1->velocity.y = 0f
00414975        if (kind == 2 && arg1->homing_target_object != 0)
00414981        long double x87_r7_13 = fconvert.t(arg1->homing_blend_step) + fconvert.t(arg1->homing_blend)
00414987        arg1->homing_blend = fconvert.s(x87_r7_13)
0041498d        long double temp8_1 = fconvert.t(1f)
0041498d        x87_r7_13 - temp8_1
00414998        if ((((x87_r7_13 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_13, temp8_1) ? 1 : 0) << 0xa | (x87_r7_13 == temp8_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0041499a        arg1->homing_blend = 1f
004149ab        float var_70_1 = fconvert.s(normalize_vector(&arg1->velocity.x))
004149c8        vector_1.x = fconvert.s(fconvert.t(arg1->homing_target.x) - fconvert.t(arg1->flight_transform.position.x))
004149e1        vector_1.y = fconvert.s(fconvert.t(arg1->homing_target.y) - fconvert.t(arg1->flight_transform.position.y))
004149ed        vector_1.z = fconvert.s(fconvert.t(arg1->homing_target.z) - fconvert.t(arg1->flight_transform.position.z))
004149f1        long double st0_2 = normalize_vector(&vector_1)
004149f6        long double temp11_1 = fconvert.t(0.400000006f)
004149f6        st0_2 - temp11_1
00414a01        if ((((st0_2 < temp11_1 ? 1 : 0) << 8 | (is_unordered.t(st0_2, temp11_1) ? 1 : 0) << 0xa | (st0_2 == temp11_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0041525c        spawn_golb_impact_sprite(arg1, &arg1->flight_transform.position.x)
00415263        return kill_golb(arg1)
00414a09        long double x87_r7_22 = fconvert.t(arg1->homing_blend)
00414a35        long double x87_r6_7 = fconvert.t(1f) - fconvert.t(arg1->homing_blend) * fconvert.t(1.5f)
00414a67        arg1->velocity.x = fconvert.s(fconvert.t(fconvert.s(x87_r6_7 * fconvert.t(arg1->velocity.x))) + fconvert.t(fconvert.s(fconvert.t(vector_1.x) * x87_r7_22)))
00414a73        arg1->velocity.y = fconvert.s(fconvert.t(fconvert.s(x87_r6_7 * fconvert.t(arg1->velocity.y))) + fconvert.t(fconvert.s(fconvert.t(vector_1.y) * x87_r7_22)))
00414a80        arg1->velocity.z = fconvert.s(x87_r6_7 * fconvert.t(arg1->velocity.z) + x87_r7_22 * fconvert.t(vector_1.z))
00414a83        normalize_vector(&arg1->velocity.x)
00414a90        arg1->velocity.x = fconvert.s(fconvert.t(var_70_1) * fconvert.t(arg1->velocity.x))
00414a99        arg1->velocity.y = fconvert.s(fconvert.t(var_70_1) * fconvert.t(arg1->velocity.y))
00414aa3        arg1->velocity.z = fconvert.s(fconvert.t(var_70_1) * fconvert.t(arg1->velocity.z))
00414aa6        long double x87_r7_33 = fconvert.t(var_70_1)
00414aaa        long double temp14_1 = fconvert.t(0.100000001f)
00414aaa        x87_r7_33 - temp14_1
00414ab5        if ((((x87_r7_33 < temp14_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_33, temp14_1) ? 1 : 0) << 0xa | (x87_r7_33 == temp14_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00415263        return kill_golb(arg1)
00414ac7        long double x87_r7_34 = fconvert.t(arg1->path_entry_z_latch)
00414acd        arg1->source_matrix.position.x = arg1->flight_transform.position.x
00414ad5        arg1->source_matrix.position.y = arg1->flight_transform.position.y
00414ad8        arg1->source_matrix.position.z = arg1->flight_transform.position.z
00414adb        long double temp4_1 = fconvert.t(arg1->source_matrix.position.z)
00414adb        x87_r7_34 - temp4_1
00414ae6        if ((((x87_r7_34 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_34, temp4_1) ? 1 : 0) << 0xa | (x87_r7_34 == temp4_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00414aec        long double x87_r7_35 = fconvert.t(arg1->flight_transform.position.y)
00414af2        long double temp7_1 = fconvert.t(1f)
00414af2        x87_r7_35 - temp7_1
00414afd        if ((((x87_r7_35 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_35, temp7_1) ? 1 : 0) << 0xa | (x87_r7_35 == temp7_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00414b03        long double x87_r7_36 = fconvert.t(arg1->flight_transform.position.y)
00414b09        long double temp10_1 = fconvert.t(0f)
00414b09        x87_r7_36 - temp10_1
00414b14        if ((((x87_r7_36 < temp10_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_36, temp10_1) ? 1 : 0) << 0xa | (x87_r7_36 == temp10_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00414b1d        int32_t source_cell = get_track_grid_cell_at_world_position(arg1->game, &arg1->source_matrix.position)
00414b29        if (*(source_cell + 0x3c) == 0x1e)
00414b32        arg1->path_entry_z_latch = arg1->source_matrix.position.z
00414b40        initialize_path_follow_golb(&arg1->path_follow, source_cell, &arg1->flight_transform.position, arg1)
00414b45        long double x87_r7_37 = fconvert.t(arg1->velocity.z)
00414b4b        long double temp16_1 = fconvert.t(1f)
00414b4b        x87_r7_37 - temp16_1
00414b5e        if ((((x87_r7_37 < temp16_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_37, temp16_1) ? 1 : 0) << 0xa | (x87_r7_37 == temp16_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0 && *(source_cell - 0x264) == 0x1e)
00414b7b        arg1->path_entry_z_latch = fconvert.s(fconvert.t(arg1->source_matrix.position.z) + fconvert.t(1f))
00414b81        initialize_path_follow_golb(&arg1->path_follow, source_cell - 0x2a0, &arg1->flight_transform.position.x, arg1)
00414892        switch (calc_path_length_z(&arg1->path_follow, arg1->path_factor, &arg1->flight_transform.position, &arg1->velocity))
004148c6        case 0, 2
004148c6        arg1->source_matrix.position.x = arg1->path_follow.output_position.x
004148cb        arg1->source_matrix.position.y = arg1->path_follow.output_position.y
004148d1        arg1->source_matrix.position.z = arg1->path_follow.output_position.z
004148a4        case 1, 3
004148a4        arg1->source_matrix.position.x = arg1->flight_transform.position.x
004148ad        arg1->source_matrix.position.y = arg1->flight_transform.position.y
004148b0        arg1->source_matrix.position.z = arg1->flight_transform.position.z
00414b86        int32_t kind_1 = arg1->kind
00414b8f        if (kind_1 == 0)
00414c8d        float* ecx_20 = arg1->render_body_owner + 0x48
00414c93        *ecx_20 = arg1->source_matrix.position.x
00414c98        ecx_20[1] = arg1->source_matrix.position.y
00414c9e        ecx_20[2] = arg1->source_matrix.position.z
00414ca3        spawn_golb_trail_sprite(arg1, &arg1->source_matrix.position)
00414cd0        float var_34_2 = fconvert.s(fconvert.t(arg1->direction.z) * fconvert.t(0.300000012f))
00414ce5        long double x87_r7_55 = fconvert.t(arg1->source_matrix.position.y) - fconvert.t(fconvert.s(fconvert.t(arg1->direction.y) * fconvert.t(0.300000012f)))
00414ce9        float var_24 = fconvert.s(fconvert.t(arg1->source_matrix.position.x) - fconvert.t(arg1->direction.x) * fconvert.t(0.300000012f))
00414d01        float var_20_1 = fconvert.s(x87_r7_55)
00414d0f        float var_1c_1 = fconvert.s(fconvert.t(arg1->source_matrix.position.z) - fconvert.t(var_34_2))
00414d13        spawn_golb_trail_sprite(arg1, &var_24)
00414d40        float var_34_3 = fconvert.s(fconvert.t(arg1->direction.z) * fconvert.t(0.600000024f))
00414d55        long double x87_r7_62 = fconvert.t(arg1->source_matrix.position.y) - fconvert.t(fconvert.s(fconvert.t(arg1->direction.y) * fconvert.t(0.600000024f)))
00414d59        float var_18 = fconvert.s(fconvert.t(arg1->source_matrix.position.x) - fconvert.t(arg1->direction.x) * fconvert.t(0.600000024f))
00414d73        float var_14_1 = fconvert.s(x87_r7_62)
00414d7f        float var_10_1 = fconvert.s(fconvert.t(arg1->source_matrix.position.z) - fconvert.t(var_34_3))
00414d83        spawn_golb_trail_sprite(arg1, &var_18)
00414b96        if (kind_1 == 1)
00414c75        add_vapour_point(&arg1->..secondary_body.bod.bod.vtable, &arg1->source_matrix)
00414b9d        if (kind_1 == 2)
00414ba9        long double x87_r7_41 = fconvert.t(arg1->spin_step) + fconvert.t(arg1->spin)
00414bc0        long double temp13_1 = fconvert.t(6.28318548f)
00414bc0        x87_r7_41 - temp13_1
00414bc6        arg1->spin = fconvert.s(x87_r7_41)
00414bc6        bool c1_1 = unknown  {fst dword [ebp+0x1b4], st0}
00414bcc        __builtin_memcpy(&arg1->..tertiary_body.transform.basis_right.x, &arg1->source_matrix, 0x40)
00414bd3        if ((((x87_r7_41 < temp13_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_41, temp13_1) ? 1 : 0) << 0xa | (x87_r7_41 == temp13_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
00414bdb        arg1->spin = fconvert.s(x87_r7_41 - fconvert.t(6.28318548f))
00414bee        spawn_golb_smoke(arg1, &arg1->source_matrix.position.x)
00414c1b        float var_34_1 = fconvert.s(fconvert.t(arg1->direction.z) * fconvert.t(0.5f))
00414c30        long double x87_r7_48 = fconvert.t(arg1->source_matrix.position.y) - fconvert.t(fconvert.s(fconvert.t(arg1->direction.y) * fconvert.t(0.5f)))
00414c34        float var_30 = fconvert.s(fconvert.t(arg1->source_matrix.position.x) - fconvert.t(arg1->direction.x) * fconvert.t(0.5f))
00414c4c        float var_2c_1 = fconvert.s(x87_r7_48)
00414c58        float var_28_1 = fconvert.s(fconvert.t(arg1->source_matrix.position.z) - fconvert.t(var_34_1))
00414c5e        spawn_golb_smoke(arg1, &var_30)
00414dc5        arg1->direction.x = fconvert.s(fconvert.t(arg1->source_matrix.position.x) - fconvert.t(arg1->previous_flight_transform.position.x))
00414dcb        arg1->direction.y = fconvert.s(fconvert.t(arg1->source_matrix.position.y) - fconvert.t(arg1->previous_flight_transform.position.y))
00414dd6        arg1->direction.z = fconvert.s(fconvert.t(arg1->source_matrix.position.z) - fconvert.t(arg1->previous_flight_transform.position.z))
00414de1        if (arg1->kind == 2)
00414dec        set_matrix_z_direction(&arg1->..tertiary_body.transform, &arg1->direction)
00414dfa        rotate_matrix_local_z(&arg1->..tertiary_body.transform, arg1->spin)
00414e05        long double x87_r7_72 = fconvert.t(arg1->lifetime_step) + fconvert.t(arg1->lifetime)
00414e0f        arg1->lifetime = fconvert.s(x87_r7_72)
00414e18        arg1->previous_flight_transform.position.x = arg1->source_matrix.position.x
00414e1e        long double temp12_1 = fconvert.t(1f)
00414e1e        x87_r7_72 - temp12_1
00414e27        arg1->previous_flight_transform.position.y = arg1->source_matrix.position.y
00414e2d        arg1->previous_flight_transform.position.z = arg1->source_matrix.position.z
00414e38        if ((((x87_r7_72 < temp12_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_72, temp12_1) ? 1 : 0) << 0xa | (x87_r7_72 == temp12_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00415263        return kill_golb(arg1)
00414e3e        struct Player* owner_player = arg1->owner_player
00414e44        long double x87_r7_73 = fconvert.t(arg1->flight_transform.position.z)
00414e4a        long double temp15_1 = fconvert.t(owner_player->interaction_max_z)
00414e4a        x87_r7_73 - temp15_1
00414e55        if ((((x87_r7_73 < temp15_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_73, temp15_1) ? 1 : 0) << 0xa | (x87_r7_73 == temp15_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00415263        return kill_golb(arg1)
00414e5e        long double x87_r7_75 = fconvert.t(owner_player->body.transform.position.z) + fconvert.t(46f)
00414e64        long double temp17_1 = fconvert.t(arg1->flight_transform.position.z)
00414e64        x87_r7_75 - temp17_1
00414e6f        if ((((x87_r7_75 < temp17_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_75, temp17_1) ? 1 : 0) << 0xa | (x87_r7_75 == temp17_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00415263        return kill_golb(arg1)
00414e7b        struct SubGarbage* esi_7 = arg1->game->garbage_hazards.active_head
00414e83        struct Vec3 vector
00414e83        if (esi_7 == 0)
00414f64        label_414f64:
00414f64        int32_t esi_8 = 0
00414f66        int32_t i = 0
00415090        while (i s< 0x760)
00414f6e        void* eax_38 = arg1->game + i
00414f70        int32_t ecx_37 = *(eax_38 + 0x356420)
00414f7e        if (ecx_37 == 1 || ecx_37 == 4)
00414fa7        long double x87_r7_90 = fconvert.t(*(eax_38 + 0x356410)) - fconvert.t(arg1->source_matrix.position.z)
00414fae        vector.x = fconvert.s(fconvert.t(*(eax_38 + 0x356408)) - fconvert.t(arg1->source_matrix.position.x))
00414fb2        vector.y = fconvert.s(fconvert.t(*(eax_38 + 0x35640c)) - fconvert.t(arg1->source_matrix.position.y))
00414fb6        long double temp19_1 = fconvert.t(0f)
00414fb6        x87_r7_90 - temp19_1
00414fbc        bool c1_3 = unknown  {fst dword [esp+0x34], st0}
00414fc4        vector.z = fconvert.s(x87_r7_90)
00414fcd        if ((((x87_r7_90 < temp19_1 ? 1 : 0) << 8 | (c1_3 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_90, temp19_1) ? 1 : 0) << 0xa | (x87_r7_90 == temp19_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
00414fcf        x87_r7_90 = fneg(x87_r7_90)
00414fd1        long double temp21_1 = fconvert.t(2.5f)
00414fd1        x87_r7_90 - temp21_1
00414fdc        if ((((x87_r7_90 < temp21_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_90, temp21_1) ? 1 : 0) << 0xa | (x87_r7_90 == temp21_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00414fe6        long double st0_5 = normalize_vector(&vector)
00414feb        long double temp22_1 = fconvert.t(2.5f)
00414feb        st0_5 - temp22_1
00414ff6        if ((((st0_5 < temp22_1 ? 1 : 0) << 8 | (is_unordered.t(st0_5, temp22_1) ? 1 : 0) << 0xa | (st0_5 == temp22_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00415002        arg1->path_follow.active = 0
0041500e        float var_70_2 = fconvert.s(normalize_vector(&arg1->velocity))
00415016        vector.y = 0
0041501e        normalize_vector(&vector)
00415033        vector_1.y = 0
00415041        vector_1.x = fconvert.s(fneg(fconvert.t(var_70_2) * fconvert.t(vector.x)))
00415051        arg1->velocity.x = vector_1.x
00415055        vector_1.z = fconvert.s(fneg(fconvert.t(var_70_2) * fconvert.t(vector.z)))
0041505d        arg1->velocity.y = 0
00415060        arg1->velocity.z = vector_1.z
00415063        int32_t kind_2 = arg1->kind
0041506c        if (kind_2 == 1)
00415173        kill_golb(arg1)
0041517b        spawn_golb_impact_sprite(arg1, &arg1->source_matrix.position.x)
004151aa        return hit_slug_hazard(&arg1->game->slug_hazards.slots[esi_8], 2)
00415075        if (kind_2 == 2)
004151ad        kill_golb(arg1)
004151b5        spawn_golb_impact_sprite(arg1, &arg1->source_matrix.position.x)
004151e4        return hit_slug_hazard(&arg1->game->slug_hazards.slots[esi_8], 4)
0041507d        if (kind_2 == 0)
004151e5        kind_2.b = arg1->slug_bounce_armed
004151ed        if (kind_2.b != 0)
00415200        kill_golb(arg1)
00415214        return spawn_golb_impact_sprite(arg1, &arg1->source_matrix.position.x)
004151f0        arg1->slug_bounce_armed = 1
004151fd        return kind_2
00415083        i += 0xec
00415089        esi_8 += 1
0041521c        game = get_track_grid_cell_at_world_position(arg1->game, &arg1->source_matrix.position.x)
00415225        if (game->tile_id == 0xe)
00415230        int32_t x = arg1->source_matrix.position.x
00415232        int32_t y = arg1->source_matrix.position.y
00415237        int32_t x_1 = x
0041523b        int32_t y_1 = y
0041523f        int32_t x_2 = x
00415251        int32_t y_2 = y
00415255        float var_4_1 = fconvert.s(fconvert.t(arg1->source_matrix.position.z) - fconvert.t(1f))
0041525c        spawn_golb_impact_sprite(arg1, &x_2)
00415263        return kill_golb(arg1)
00414e90        while (true)
00414e90        if (esi_7->state == 1)
00414eb0        long double x87_r7_81 = fconvert.t(esi_7->body.transform.position.z) - fconvert.t(arg1->source_matrix.position.z)
00414eb7        vector.x = fconvert.s(fconvert.t(esi_7->body.transform.position.x) - fconvert.t(arg1->source_matrix.position.x))
00414ebb        vector.y = fconvert.s(fconvert.t(esi_7->body.transform.position.y) - fconvert.t(arg1->source_matrix.position.y))
00414ebf        long double temp18_1 = fconvert.t(0f)
00414ebf        x87_r7_81 - temp18_1
00414ec5        bool c1_2 = unknown  {fst dword [esp+0x34], st0}
00414ecd        vector.z = fconvert.s(x87_r7_81)
00414ed6        if ((((x87_r7_81 < temp18_1 ? 1 : 0) << 8 | (c1_2 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_81, temp18_1) ? 1 : 0) << 0xa | (x87_r7_81 == temp18_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
00414ed8        x87_r7_81 = fneg(x87_r7_81)
00414eda        long double temp20_1 = fconvert.t(3f)
00414eda        x87_r7_81 - temp20_1
00414ee5        if ((((x87_r7_81 < temp20_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_81, temp20_1) ? 1 : 0) << 0xa | (x87_r7_81 == temp20_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00414eeb        long double st0_4 = normalize_vector(&vector)
00414ef6        long double x87_r6_29 = fconvert.t(esi_7->radius) + fconvert.t(0.49000001f)
00414efe        st0_4 - x87_r6_29
00414f05        if ((((st0_4 < x87_r6_29 ? 1 : 0) << 8 | (is_unordered.t(st0_4, x87_r6_29) ? 1 : 0) << 0xa | (st0_4 == x87_r6_29 ? 1 : 0) << 0xe):1.b & 1) != 0)
00414f07        esi_7->state = 2
00414f0d        long double x87_r7_84 = fconvert.t(vector.x)
00414f11        long double temp23_1 = fconvert.t(0f)
00414f11        x87_r7_84 - temp23_1
00414f1c        if ((((x87_r7_84 < temp23_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_84, temp23_1) ? 1 : 0) << 0xa | (x87_r7_84 == temp23_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
00414f30        esi_7->collision_side = 1
00414f1e        esi_7->collision_side = 2
00414f40        add_subgoldy_score(arg1->owner_player, 0, 0)
00414f4b        if (arg1->kind != 1)
0041509d        kill_golb(arg1)
004150a5        game = spawn_golb_impact_sprite(arg1, &arg1->source_matrix.position.x)
004150b1        if (arg1->kind == 2)
004150bd        struct SubGarbage* i_1 = arg1->game->garbage_hazards.active_head
004150c5        if (i_1 != 0)
004150d1        if (i_1->state == 1)
004150f8        vector.x = fconvert.s(fconvert.t(i_1->body.transform.position.x) - fconvert.t(arg1->source_matrix.position.x))
004150fc        vector.y = fconvert.s(fconvert.t(i_1->body.transform.position.y) - fconvert.t(arg1->source_matrix.position.y))
0041510c        vector.z = fconvert.s(fconvert.t(i_1->body.transform.position.z) - fconvert.t(arg1->source_matrix.position.z))
00415110        long double st0_8
00415110        st0_8, game = normalize_vector(&vector)
00415115        long double temp24_1 = fconvert.t(3f)
00415115        st0_8 - temp24_1
0041511b        game.w = (st0_8 < temp24_1 ? 1 : 0) << 8 | (is_unordered.t(st0_8, temp24_1) ? 1 : 0) << 0xa | (st0_8 == temp24_1 ? 1 : 0) << 0xe
00415120        if ((game:1.b & 1) != 0)
00415127        i_1->state = 2
0041512d        long double x87_r7_108 = fconvert.t(vector.x)
00415131        long double temp25_1 = fconvert.t(0f)
00415131        x87_r7_108 - temp25_1
0041513c        if ((((x87_r7_108 < temp25_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_108, temp25_1) ? 1 : 0) << 0xa | (x87_r7_108 == temp25_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
00415146        i_1->collision_side = 1
0041513e        i_1->collision_side = 2
00415156        game = add_subgoldy_score(arg1->owner_player, 0, 0)
0041515b        i_1 = i_1->next_active
00415163        do while (i_1 != 0)
00415170        return game
004150b1        break
00414f56        esi_7 = esi_7->next_active
00414f5e        if (esi_7 == 0)
00414f5e        goto label_414f64
0041526f        return game
