/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_track_ring_or_special_effect @ 0x43df10 */

0043df13        int32_t slot_index = 0
0043df1b        enum SubRingState* state_cursor = &game->ring_effects.slots[0].state
0043df24        while (*state_cursor != SUB_RING_STATE_INACTIVE)
0043df26        slot_index += 1
0043df27        state_cursor = &state_cursor[0x7e]
0043df30        if (slot_index s>= 2)
0043df39        return
0043df5c        struct SubRingSlotCursor* slot_cursor = game + slot_index * 0x1f8
0043df82        float default_phase_step = fconvert.s(fconvert.t(1f) / ((fconvert.t(2f) - fconvert.t(game->base_subgame_rate) * fconvert.t(0.300000012f)) * fconvert.t(60f)) * float.t(player->movement_flag_selector) * fconvert.t(0.125f) * fconvert.t(game->subgame_rate) * fconvert.t(6.28318548f))
0043df86        set_matrix_identity(&slot_cursor->ring.basis_right)
0043df8b        int32_t effective_kind = requested_kind
0043df8f        slot_cursor->ring.owner_player = player
0043df98        if (effective_kind == 4)
0043df9a        void* var_24_1 = &data_4a4e68
0043dfa4        long double st0_1 = random_float_below(1f)
0043dfa9        long double temp1_1 = fconvert.t(0.930000007f)
0043dfa9        st0_1 - temp1_1
0043dfb7        if ((((st0_1 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(st0_1, temp1_1) ? 1 : 0) << 0xa | (st0_1 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043dfdd        effective_kind = 3
0043dfb9        void* var_24_2 = &data_4a4e64
0043dfc3        long double st0_2 = random_float_below(1f)
0043dfc8        long double temp2_1 = fconvert.t(0.5f)
0043dfc8        st0_2 - temp2_1
0043dfdb        if ((((st0_2 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(st0_2, temp2_1) ? 1 : 0) << 0xa | (st0_2 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0 && game->level_mode == effective_kind)
0043dfdd        effective_kind = 3
0043dfb7        goto label_43dfed
0043dfe7        if (effective_kind u<= 8)
0043dfed        label_43dfed:
0043dfed        switch (effective_kind)
0043dffe        case 0
0043dffe        void* var_24_3 = &data_4a4e60
0043e011        float x_4 = cell->anchor_position.x
0043e016        float x_9 = x_4
0043e02d        slot_cursor->ring.world_position.x = x_4
0043e037        slot_cursor->ring.world_position.y = fconvert.s(fconvert.t(cell->anchor_position.y) + fconvert.t(2.5f))
0043e03a        slot_cursor->ring.world_position.z = fconvert.s(fconvert.t(cell->anchor_position.z) + fconvert.t(6f))
0043e042        long double x87_r7_15 = random_float_below(1f) - fconvert.t(0.5f)
0043e048        void* var_2c_1 = &data_4a4e5c
0043e055        slot_cursor->ring.world_position.x = fconvert.s((x87_r7_15 + x87_r7_15) * fconvert.t(3f))
0043e231        slot_cursor->ring.active_phase = fconvert.s(random_float_below(1f) * fconvert.t(6.28318548f))
0043e237        slot_cursor->ring.active_phase_step = default_phase_step
0043e068        case 1
0043e068        void* var_24_4 = &data_4a4e58
0043e076        float x = cell->anchor_position.x
0043e07e        float x_10 = x
0043e095        slot_cursor->ring.world_position.x = x
0043e09f        slot_cursor->ring.world_position.y = fconvert.s(fconvert.t(cell->anchor_position.y) + fconvert.t(2.5f))
0043e0a2        slot_cursor->ring.world_position.z = fconvert.s(fconvert.t(cell->anchor_position.z) + fconvert.t(6f))
0043e0aa        long double x87_r7_23 = random_float_below(1f) - fconvert.t(0.5f)
0043e0b0        void* var_2c_2 = &data_4a4e54
0043e0bd        slot_cursor->ring.world_position.x = fconvert.s((x87_r7_23 + x87_r7_23) * fconvert.t(3f))
0043e1a6        slot_cursor->ring.active_phase = fconvert.s(random_float_below(1f) * fconvert.t(6.28318548f))
0043e1ac        slot_cursor->ring.active_phase_step = default_phase_step
0043e0ce        case 2
0043e0ce        void* var_24_5 = &data_4a4e50
0043e0e1        float x_5 = cell->anchor_position.x
0043e0e6        float x_11 = x_5
0043e0fd        slot_cursor->ring.world_position.x = x_5
0043e107        slot_cursor->ring.world_position.y = fconvert.s(fconvert.t(cell->anchor_position.y) + fconvert.t(3.5f))
0043e10a        slot_cursor->ring.world_position.z = fconvert.s(fconvert.t(cell->anchor_position.z) + fconvert.t(17f))
0043e112        long double x87_r7_31 = random_float_below(1f) - fconvert.t(0.5f)
0043e118        void* var_2c_3 = &data_4a4e4c
0043e125        slot_cursor->ring.world_position.x = fconvert.s((x87_r7_31 + x87_r7_31) * fconvert.t(3f))
0043e231        slot_cursor->ring.active_phase = fconvert.s(random_float_below(1f) * fconvert.t(6.28318548f))
0043e237        slot_cursor->ring.active_phase_step = default_phase_step
0043e138        case 3
0043e138        void* var_24_6 = &data_4a4e48
0043e146        float x_1 = cell->anchor_position.x
0043e14e        float x_12 = x_1
0043e165        slot_cursor->ring.world_position.x = x_1
0043e16f        slot_cursor->ring.world_position.y = fconvert.s(fconvert.t(cell->anchor_position.y) + fconvert.t(2.5f))
0043e172        slot_cursor->ring.world_position.z = fconvert.s(fconvert.t(cell->anchor_position.z) + fconvert.t(6f))
0043e17a        long double x87_r7_39 = random_float_below(1f) - fconvert.t(0.5f)
0043e180        void* var_2c_4 = &data_4a4e44
0043e18d        slot_cursor->ring.world_position.x = fconvert.s((x87_r7_39 + x87_r7_39) * fconvert.t(3f))
0043e1a6        slot_cursor->ring.active_phase = fconvert.s(random_float_below(1f) * fconvert.t(6.28318548f))
0043e1ac        slot_cursor->ring.active_phase_step = default_phase_step
0043e1c1        case 4
0043e1c1        void* var_24_7 = &data_4a4e40
0043e1d4        float x_6 = cell->anchor_position.x
0043e1d9        float x_13 = x_6
0043e1f0        slot_cursor->ring.world_position.x = x_6
0043e1fa        slot_cursor->ring.world_position.y = fconvert.s(fconvert.t(cell->anchor_position.y) + fconvert.t(2.5f))
0043e1fd        slot_cursor->ring.world_position.z = fconvert.s(fconvert.t(cell->anchor_position.z) + fconvert.t(6f))
0043e205        long double x87_r7_49 = random_float_below(1f) - fconvert.t(0.5f)
0043e20b        void* var_2c_5 = &data_4a4e3c
0043e218        slot_cursor->ring.world_position.x = fconvert.s((x87_r7_49 + x87_r7_49) * fconvert.t(3f))
0043e231        slot_cursor->ring.active_phase = fconvert.s(random_float_below(1f) * fconvert.t(6.28318548f))
0043e237        slot_cursor->ring.active_phase_step = default_phase_step
0043e246        case 5
0043e246        char* var_24_8 = "RR10"
0043e254        float x_2 = cell->anchor_position.x
0043e264        float x_14 = x_2
0043e270        slot_cursor->ring.world_position.x = x_2
0043e276        slot_cursor->ring.world_position.y = fconvert.s(fconvert.t(cell->anchor_position.y) + fconvert.t(2.5f))
0043e279        slot_cursor->ring.world_position.z = cell->anchor_position.z
0043e346        slot_cursor->ring.active_phase = fconvert.s(random_float_below(1f) * fconvert.t(6.28318548f))
0043e365        slot_cursor->ring.active_phase_step = fconvert.s(fconvert.t(1f) / (fconvert.t(ring_speed) * fconvert.t(60f)) * fconvert.t(game->subgame_rate) * fconvert.t(6.28318548f))
0043e2c1        case 6
0043e2c1        char* var_24_10 = "RR12"
0043e2cf        float x_3 = cell->anchor_position.x
0043e2df        float x_16 = x_3
0043e2eb        slot_cursor->ring.world_position.x = x_3
0043e2f1        slot_cursor->ring.world_position.y = fconvert.s(fconvert.t(cell->anchor_position.y) + fconvert.t(2.5f))
0043e2f4        slot_cursor->ring.world_position.z = cell->anchor_position.z
0043e346        slot_cursor->ring.active_phase = fconvert.s(random_float_below(1f) * fconvert.t(6.28318548f))
0043e365        slot_cursor->ring.active_phase_step = fconvert.s(fconvert.t(1f) / (fconvert.t(ring_speed) * fconvert.t(60f)) * fconvert.t(game->subgame_rate) * fconvert.t(6.28318548f))
0043e303        case 7
0043e303        char* var_24_11 = "RR13"
0043e311        float x_8 = cell->anchor_position.x
0043e314        int16_t z_1 = (cell->anchor_position.z).w
0043e31b        slot_cursor->ring.world_position.x.b = x_8.b
0043e31b        slot_cursor->ring.world_position.x:1.b = x_8:1.b
0043e31b        slot_cursor->ring.world_position.x:2.b = x_8:2.b
0043e31b        slot_cursor->ring.world_position.x:3.b = x_8:3.b
0043e31d        float x_17 = x_8
0043e32d        slot_cursor->ring.world_position.y = fconvert.s(fconvert.t(cell->anchor_position.y) + fconvert.t(2.5f))
0043e330        slot_cursor->ring.world_position.z.b = z_1.b
0043e330        slot_cursor->ring.world_position.z:1.b = z_1:1.b
0043e346        slot_cursor->ring.active_phase = fconvert.s(random_float_below(1f) * fconvert.t(6.28318548f))
0043e365        slot_cursor->ring.active_phase_step = fconvert.s(fconvert.t(1f) / (fconvert.t(ring_speed) * fconvert.t(60f)) * fconvert.t(game->subgame_rate) * fconvert.t(6.28318548f))
0043e28b        case 8
0043e28b        char* var_24_9 = "RR11"
0043e299        float x_7 = cell->anchor_position.x
0043e29c        int16_t z = (cell->anchor_position.z).w
0043e2a3        slot_cursor->ring.world_position.x.b = x_7.b
0043e2a3        slot_cursor->ring.world_position.x:1.b = x_7:1.b
0043e2a3        slot_cursor->ring.world_position.x:2.b = x_7:2.b
0043e2a3        slot_cursor->ring.world_position.x:3.b = x_7:3.b
0043e2a5        float x_15 = x_7
0043e2b5        slot_cursor->ring.world_position.y = fconvert.s(fconvert.t(cell->anchor_position.y) + fconvert.t(2.5f))
0043e2b8        slot_cursor->ring.world_position.z.b = z.b
0043e2b8        slot_cursor->ring.world_position.z:1.b = z:1.b
0043e346        slot_cursor->ring.active_phase = fconvert.s(random_float_below(1f) * fconvert.t(6.28318548f))
0043e365        slot_cursor->ring.active_phase_step = fconvert.s(fconvert.t(1f) / (fconvert.t(ring_speed) * fconvert.t(60f)) * fconvert.t(game->subgame_rate) * fconvert.t(6.28318548f))
0043e37d        if (get_track_grid_cell_at_world_position(game, &slot_cursor->ring.world_position)->tile_id == 0xe)
0043e37d        return
0043e387        slot_cursor->ring.kind = effective_kind
0043e38d        void* var_24_13 = &data_4a4e18
0043e39d        slot_cursor->ring.owner_lives_snapshot = player->lives
0043e3a3        slot_cursor->ring.state = SUB_RING_STATE_ACTIVE
0043e3ad        long double st0_11 = random_float_below(1f)
0043e3b2        long double temp3_1 = fconvert.t(0.5f)
0043e3b2        st0_11 - temp3_1
0043e3c0        if ((((st0_11 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(st0_11, temp3_1) ? 1 : 0) << 0xa | (st0_11 == temp3_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043e3ce        slot_cursor->ring.active_phase_step = fconvert.s(fconvert.t(slot_cursor->ring.active_phase_step) * fconvert.t(-1f))
0043e3e7        if ((0x200 & slot_cursor->ring.bod.list_flags) == 0)
0043e3ff        struct BodNode** active_head = &g_game_base->active_bod_list.first
0043e404        struct BodNode* active_first = *active_head
0043e408        if (active_first != 0)
0043e416        active_first->list_prev.b = (&slot_cursor->ring).b
0043e416        active_first->list_prev:1.b = (&slot_cursor->ring):1.b
0043e419        struct BodNode* first_for_link = *active_head
0043e41b        struct BodNode* linked_head
0043e41b        linked_head.b = first_for_link->list_prev.b
0043e41b        linked_head:1.b = first_for_link->list_prev:1.b
0043e41e        linked_head->list_next = first_for_link
0043e421        struct BodNode* first_for_promote = *active_head
0043e423        struct BodNode* promoted_head
0043e423        promoted_head.b = first_for_promote->list_prev.b
0043e423        promoted_head:1.b = first_for_promote->list_prev:1.b
0043e426        *active_head = promoted_head
0043e428        promoted_head->list_prev.b = nullptr
0043e428        promoted_head->list_prev:1.b = 0
0043e40a        *active_head = &slot_cursor->ring
0043e40c        slot_cursor->ring.bod.list_prev = nullptr
0043e411        (*active_head)->list_next = nullptr
0043e42b        slot_cursor->ring.bod.list_flags |= 0x200
0043e3ee        report_errorf("List ADD")
0043e437        initialize_ring_or_special_effect_particles(&slot_cursor->ring, player->lives)
0043e440        (*slot_cursor->ring.bod.vtable)()
0043e449        return
