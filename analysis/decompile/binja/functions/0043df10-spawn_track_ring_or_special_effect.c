/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_track_ring_or_special_effect @ 0x43df10 */

0043df13        int32_t eax = 0
0043df1b        int32_t* ecx = &game->ring_effects.slots[0].state
0043df24        while ((ecx - 0x35b80c)->ring_effects.slots[0].state != 0)
0043df26        eax += 1
0043df27        ecx = &ecx[0x7e]
0043df30        if (eax s>= 2)
0043df39        return
0043df5c        void* esi = &game->unknown_000000[eax * 0x1f8]
0043df82        float var_10 = fconvert.s(fconvert.t(1f) / ((fconvert.t(2f) - fconvert.t(game->base_subgame_rate) * fconvert.t(0.300000012f)) * fconvert.t(60f)) * float.t(player->movement_flag_selector) * fconvert.t(0.125f) * fconvert.t(game->subgame_rate) * fconvert.t(6.28318548f))
0043df86        set_matrix_identity(esi + 0x35b7c4)
0043df8b        int32_t requested_kind_1 = requested_kind
0043df8f        *(esi + 0x35b810) = player
0043df98        if (requested_kind_1 == 4)
0043df9a        void* var_24_1 = &data_4a4e68
0043dfa4        long double st0_1 = random_float_below(1f)
0043dfa9        long double temp1_1 = fconvert.t(0.930000007f)
0043dfa9        st0_1 - temp1_1
0043dfb7        if ((((st0_1 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(st0_1, temp1_1) ? 1 : 0) << 0xa | (st0_1 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043dfdd        requested_kind_1 = 3
0043dfb9        void* var_24_2 = &data_4a4e64
0043dfc3        long double st0_2 = random_float_below(1f)
0043dfc8        long double temp2_1 = fconvert.t(0.5f)
0043dfc8        st0_2 - temp2_1
0043dfdb        if ((((st0_2 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(st0_2, temp2_1) ? 1 : 0) << 0xa | (st0_2 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0 && game->level_mode == requested_kind_1)
0043dfdd        requested_kind_1 = 3
0043dfb7        goto label_43dfed
0043dfe7        if (requested_kind_1 u<= 8)
0043dfed        label_43dfed:
0043dfed        switch (requested_kind_1)
0043dffe        case 0
0043dffe        void* var_24_3 = &data_4a4e60
0043e011        float x_4 = cell->anchor_position.x
0043e016        float x_9 = x_4
0043e01a        float var_8_1 = fconvert.s(fconvert.t(cell->anchor_position.y) + fconvert.t(2.5f))
0043e021        long double x87_r7_13 = fconvert.t(cell->anchor_position.z) + fconvert.t(6f)
0043e02d        *(esi + 0x35b7f4) = x_4
0043e037        *(esi + 0x35b7f8) = var_8_1
0043e03a        *(esi + 0x35b7fc) = fconvert.s(x87_r7_13)
0043e042        long double x87_r7_15 = random_float_below(1f) - fconvert.t(0.5f)
0043e048        void* var_2c_1 = &data_4a4e5c
0043e055        *(esi + 0x35b7f4) = fconvert.s((x87_r7_15 + x87_r7_15) * fconvert.t(3f))
0043e231        *(esi + 0x35b96c) = fconvert.s(random_float_below(1f) * fconvert.t(6.28318548f))
0043e237        *(esi + 0x35b970) = var_10
0043e068        case 1
0043e068        void* var_24_4 = &data_4a4e58
0043e076        float x = cell->anchor_position.x
0043e07e        float x_10 = x
0043e082        float var_8_2 = fconvert.s(fconvert.t(cell->anchor_position.y) + fconvert.t(2.5f))
0043e089        long double x87_r7_21 = fconvert.t(cell->anchor_position.z) + fconvert.t(6f)
0043e095        *(esi + 0x35b7f4) = x
0043e09f        *(esi + 0x35b7f8) = var_8_2
0043e0a2        *(esi + 0x35b7fc) = fconvert.s(x87_r7_21)
0043e0aa        long double x87_r7_23 = random_float_below(1f) - fconvert.t(0.5f)
0043e0b0        void* var_2c_2 = &data_4a4e54
0043e0bd        *(esi + 0x35b7f4) = fconvert.s((x87_r7_23 + x87_r7_23) * fconvert.t(3f))
0043e1a6        *(esi + 0x35b96c) = fconvert.s(random_float_below(1f) * fconvert.t(6.28318548f))
0043e1ac        *(esi + 0x35b970) = var_10
0043e0ce        case 2
0043e0ce        void* var_24_5 = &data_4a4e50
0043e0e1        float x_5 = cell->anchor_position.x
0043e0e6        float x_11 = x_5
0043e0ea        float var_8_3 = fconvert.s(fconvert.t(cell->anchor_position.y) + fconvert.t(3.5f))
0043e0f1        long double x87_r7_29 = fconvert.t(cell->anchor_position.z) + fconvert.t(17f)
0043e0fd        *(esi + 0x35b7f4) = x_5
0043e107        *(esi + 0x35b7f8) = var_8_3
0043e10a        *(esi + 0x35b7fc) = fconvert.s(x87_r7_29)
0043e112        long double x87_r7_31 = random_float_below(1f) - fconvert.t(0.5f)
0043e118        void* var_2c_3 = &data_4a4e4c
0043e125        *(esi + 0x35b7f4) = fconvert.s((x87_r7_31 + x87_r7_31) * fconvert.t(3f))
0043e231        *(esi + 0x35b96c) = fconvert.s(random_float_below(1f) * fconvert.t(6.28318548f))
0043e237        *(esi + 0x35b970) = var_10
0043e138        case 3
0043e138        void* var_24_6 = &data_4a4e48
0043e146        float x_1 = cell->anchor_position.x
0043e14e        float x_12 = x_1
0043e152        float var_8_4 = fconvert.s(fconvert.t(cell->anchor_position.y) + fconvert.t(2.5f))
0043e159        long double x87_r7_37 = fconvert.t(cell->anchor_position.z) + fconvert.t(6f)
0043e165        *(esi + 0x35b7f4) = x_1
0043e16f        *(esi + 0x35b7f8) = var_8_4
0043e172        *(esi + 0x35b7fc) = fconvert.s(x87_r7_37)
0043e17a        long double x87_r7_39 = random_float_below(1f) - fconvert.t(0.5f)
0043e180        void* var_2c_4 = &data_4a4e44
0043e18d        *(esi + 0x35b7f4) = fconvert.s((x87_r7_39 + x87_r7_39) * fconvert.t(3f))
0043e1a6        *(esi + 0x35b96c) = fconvert.s(random_float_below(1f) * fconvert.t(6.28318548f))
0043e1ac        *(esi + 0x35b970) = var_10
0043e1c1        case 4
0043e1c1        void* var_24_7 = &data_4a4e40
0043e1d4        float x_6 = cell->anchor_position.x
0043e1d9        float x_13 = x_6
0043e1dd        float var_8_5 = fconvert.s(fconvert.t(cell->anchor_position.y) + fconvert.t(2.5f))
0043e1e4        long double x87_r7_47 = fconvert.t(cell->anchor_position.z) + fconvert.t(6f)
0043e1f0        *(esi + 0x35b7f4) = x_6
0043e1fa        *(esi + 0x35b7f8) = var_8_5
0043e1fd        *(esi + 0x35b7fc) = fconvert.s(x87_r7_47)
0043e205        long double x87_r7_49 = random_float_below(1f) - fconvert.t(0.5f)
0043e20b        void* var_2c_5 = &data_4a4e3c
0043e218        *(esi + 0x35b7f4) = fconvert.s((x87_r7_49 + x87_r7_49) * fconvert.t(3f))
0043e231        *(esi + 0x35b96c) = fconvert.s(random_float_below(1f) * fconvert.t(6.28318548f))
0043e237        *(esi + 0x35b970) = var_10
0043e246        case 5
0043e246        char* var_24_8 = "RR10"
0043e254        float x_2 = cell->anchor_position.x
0043e257        float z_2 = cell->anchor_position.z
0043e264        float x_14 = x_2
0043e268        float var_8_6 = fconvert.s(fconvert.t(cell->anchor_position.y) + fconvert.t(2.5f))
0043e270        *(esi + 0x35b7f4) = x_2
0043e276        *(esi + 0x35b7f8) = var_8_6
0043e279        *(esi + 0x35b7fc) = z_2
0043e346        *(esi + 0x35b96c) = fconvert.s(random_float_below(1f) * fconvert.t(6.28318548f))
0043e365        *(esi + 0x35b970) = fconvert.s(fconvert.t(1f) / (fconvert.t(ring_speed) * fconvert.t(60f)) * fconvert.t(game->subgame_rate) * fconvert.t(6.28318548f))
0043e2c1        case 6
0043e2c1        char* var_24_10 = "RR12"
0043e2cf        float x_3 = cell->anchor_position.x
0043e2d2        float z_3 = cell->anchor_position.z
0043e2df        float x_16 = x_3
0043e2e3        float var_8_8 = fconvert.s(fconvert.t(cell->anchor_position.y) + fconvert.t(2.5f))
0043e2eb        *(esi + 0x35b7f4) = x_3
0043e2f1        *(esi + 0x35b7f8) = var_8_8
0043e2f4        *(esi + 0x35b7fc) = z_3
0043e346        *(esi + 0x35b96c) = fconvert.s(random_float_below(1f) * fconvert.t(6.28318548f))
0043e365        *(esi + 0x35b970) = fconvert.s(fconvert.t(1f) / (fconvert.t(ring_speed) * fconvert.t(60f)) * fconvert.t(game->subgame_rate) * fconvert.t(6.28318548f))
0043e303        case 7
0043e303        char* var_24_11 = "RR13"
0043e30b        long double x87_r7_61 = fconvert.t(cell->anchor_position.y) + fconvert.t(2.5f)
0043e311        float x_8 = cell->anchor_position.x
0043e314        float z_1 = cell->anchor_position.z
0043e31b        *(esi + 0x35b7f4) = x_8.b
0043e31b        *(esi + 0x35b7f5) = x_8:1.b
0043e31b        *(esi + 0x35b7f6) = x_8:2.b
0043e31b        *(esi + 0x35b7f7) = x_8:3.b
0043e31d        float x_17 = x_8
0043e32d        *(esi + 0x35b7f8) = fconvert.s(x87_r7_61)
0043e330        *(esi + 0x35b7fc) = z_1.b
0043e330        *(esi + 0x35b7fd) = z_1:1.b
0043e330        *(esi + 0x35b7fe) = z_1:2.b
0043e330        *(esi + 0x35b7ff) = z_1:3.b
0043e346        *(esi + 0x35b96c) = fconvert.s(random_float_below(1f) * fconvert.t(6.28318548f))
0043e365        *(esi + 0x35b970) = fconvert.s(fconvert.t(1f) / (fconvert.t(ring_speed) * fconvert.t(60f)) * fconvert.t(game->subgame_rate) * fconvert.t(6.28318548f))
0043e28b        case 8
0043e28b        char* var_24_9 = "RR11"
0043e293        long double x87_r7_57 = fconvert.t(cell->anchor_position.y) + fconvert.t(2.5f)
0043e299        float x_7 = cell->anchor_position.x
0043e29c        float z = cell->anchor_position.z
0043e2a3        *(esi + 0x35b7f4) = x_7.b
0043e2a3        *(esi + 0x35b7f5) = x_7:1.b
0043e2a3        *(esi + 0x35b7f6) = x_7:2.b
0043e2a3        *(esi + 0x35b7f7) = x_7:3.b
0043e2a5        float x_15 = x_7
0043e2b5        *(esi + 0x35b7f8) = fconvert.s(x87_r7_57)
0043e2b8        *(esi + 0x35b7fc) = z.b
0043e2b8        *(esi + 0x35b7fd) = z:1.b
0043e2b8        *(esi + 0x35b7fe) = z:2.b
0043e2b8        *(esi + 0x35b7ff) = z:3.b
0043e346        *(esi + 0x35b96c) = fconvert.s(random_float_below(1f) * fconvert.t(6.28318548f))
0043e365        *(esi + 0x35b970) = fconvert.s(fconvert.t(1f) / (fconvert.t(ring_speed) * fconvert.t(60f)) * fconvert.t(game->subgame_rate) * fconvert.t(6.28318548f))
0043e37d        if (get_track_grid_cell_at_world_position(game, esi + 0x35b7f4)->tile_id == 0xe)
0043e37d        return
0043e387        *(esi + 0x35b814) = requested_kind_1
0043e38d        void* var_24_13 = &data_4a4e18
0043e39d        *(esi + 0x35b818) = player->lives
0043e3a3        *(esi + 0x35b80c) = 1
0043e3ad        long double st0_11 = random_float_below(1f)
0043e3b2        long double temp3_1 = fconvert.t(0.5f)
0043e3b2        st0_11 - temp3_1
0043e3c0        if ((((st0_11 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(st0_11, temp3_1) ? 1 : 0) << 0xa | (st0_11 == temp3_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043e3ce        *(esi + 0x35b970) = fconvert.s(fconvert.t(*(esi + 0x35b970)) * fconvert.t(-1f))
0043e3e7        if ((0x200 & *(esi + 0x35b790)) == 0)
0043e3ff        struct SubRing** eax_31 = &g_game_base[0x5ac]
0043e404        struct SubRing* ecx_20 = *eax_31
0043e408        if (ecx_20 != 0)
0043e416        ecx_20->bod.list_prev.b = (esi + 0x35b78c).b
0043e416        ecx_20->bod.list_prev:1.b = (esi + 0x35b78c):1.b
0043e416        ecx_20->bod.list_prev:2.b = (esi + 0x35b78c):2.b
0043e416        ecx_20->bod.list_prev:3.b = (esi + 0x35b78c):3.b
0043e419        struct SubRing* ecx_22 = *eax_31
0043e41b        void* ebp
0043e41b        ebp.b = ecx_22->bod.list_prev.b
0043e41b        ebp:1.b = ecx_22->bod.list_prev:1.b
0043e41b        ebp:2.b = ecx_22->bod.list_prev:2.b
0043e41b        ebp:3.b = ecx_22->bod.list_prev:3.b
0043e41e        *(ebp + 0xc) = ecx_22
0043e421        struct SubRing* ecx_23 = *eax_31
0043e423        struct SubRing* ecx_24
0043e423        ecx_24.b = ecx_23->bod.list_prev.b
0043e423        ecx_24:1.b = ecx_23->bod.list_prev:1.b
0043e423        ecx_24:2.b = ecx_23->bod.list_prev:2.b
0043e423        ecx_24:3.b = ecx_23->bod.list_prev:3.b
0043e426        *eax_31 = ecx_24
0043e428        ecx_24->bod.list_prev.b = nullptr
0043e428        ecx_24->bod.list_prev:1.b = 0
0043e428        ecx_24->bod.list_prev:2.b = 0
0043e428        ecx_24->bod.list_prev:3.b = 0
0043e40a        *eax_31 = esi + 0x35b78c
0043e40c        (esi + 0x35b78c)->bod.list_prev = nullptr
0043e40f        struct SubRing* ecx_21 = *eax_31
0043e411        ecx_21->bod.list_next.b = nullptr
0043e411        ecx_21->bod.list_next:1.b = 0
0043e411        ecx_21->bod.list_next:2.b = 0
0043e411        ecx_21->bod.list_next:3.b = 0
0043e42b        (esi + 0x35b78c)->bod.list_flags |= 0x200
0043e3ee        report_errorf("List ADD")
0043e437        initialize_ring_or_special_effect_particles(esi + 0x35b78c, player->lives)
0043e440        (*(esi + 0x35b78c)->bod.vtable)()
0043e449        return
