/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_track_jetpack_pickup @ 0x43d890 */

0043d893        enum TrackPickupState* eax = &game->jetpack_pickup.state
0043d89d        int32_t edx = 0
0043d8a1        while ((eax - 0x355e9c)->jetpack_pickup.state != TRACK_PICKUP_STATE_INACTIVE)
0043d8a3        edx += 1
0043d8a4        eax = &eax[0x67]
0043d8ac        if (edx s>= 1)
0043d8b3        return
0043d8cd        struct JetPackSlotCursor* jetpack_cursor = game + edx * 0x19c
0043d8d0        jetpack_cursor->jetpack.state = TRACK_PICKUP_STATE_ACTIVE
0043d8da        jetpack_cursor->jetpack.owner = player
0043d8e9        float x = cell->anchor_position.x
0043d8fb        float x_1 = x
0043d907        jetpack_cursor->jetpack.bod.position.x = x
0043d90d        jetpack_cursor->jetpack.bod.position.y = fconvert.s(fconvert.t(cell->anchor_position.y) + fconvert.t(1.5f))
0043d910        jetpack_cursor->jetpack.bod.position.z = cell->anchor_position.z
0043d916        int32_t eax_8 = cell->lane_and_flags & 7
0043d92b        if (eax_8 == 3 && cell->__offset(0xffffffffffffffe8).b == 0xe && cell->__offset(0xe4).b == 0xe)
0043d951        jetpack_cursor->jetpack.bod.position.x = fconvert.s(fconvert.t(jetpack_cursor->jetpack.bod.position.x) + fconvert.t(0.5f))
0043d947        if (eax_8 == 4 && cell->__offset(0xffffffffffffff94).b == 0xe && cell->__offset(0x90).b == 0xe)
0043d951        jetpack_cursor->jetpack.bod.position.x = fconvert.s(fconvert.t(jetpack_cursor->jetpack.bod.position.x) - fconvert.t(0.5f))
0043d962        if (((jetpack_cursor->jetpack.bod.bod.list_flags).w:1.b & 2) == 0)
0043d973        struct GameRoot* game_base_1 = g_game_base
0043d97f        struct BodNode* first = game_base_1->active_bod_list.first
0043d987        if (first != 0)
0043d995        first->list_prev = &jetpack_cursor->jetpack
0043d998        struct BodNode* first_1 = game_base_1->active_bod_list.first
0043d99d        first_1->list_prev->list_next = first_1
0043d9a4        struct BodNode* list_prev = game_base_1->active_bod_list.first->list_prev
0043d9a7        game_base_1->active_bod_list.first = list_prev
0043d9a9        list_prev->list_prev = nullptr
0043d989        game_base_1->active_bod_list.first = &jetpack_cursor->jetpack
0043d98b        jetpack_cursor->jetpack.bod.bod.list_prev.b = nullptr
0043d98b        jetpack_cursor->jetpack.bod.bod.list_prev:1.b = 0
0043d990        game_base_1->active_bod_list.first->list_next = nullptr
0043d9ac        uint32_t list_flags = jetpack_cursor->jetpack.bod.bod.list_flags
0043d9af        list_flags:1.b |= 2
0043d9b2        jetpack_cursor->jetpack.bod.bod.list_flags = list_flags
0043d969        report_errorf("List ADD")
0043d9cb        struct Sprite* eax_12 = allocate_sprite(&g_sprite_manager, player->player_slot, 0x7c, 0xffffffff, 0xffffffff)
0043d9d0        jetpack_cursor->jetpack.sprite = eax_12
0043d9d6        enum SpriteFlag flags = eax_12->flags
0043d9d9        flags:1.b |= 8
0043d9dc        eax_12->flags = flags
0043d9e5        jetpack_cursor->jetpack.sprite->gravity_step = 0f
0043d9ee        jetpack_cursor->jetpack.sprite->progress = 0f
0043d9fc        jetpack_cursor->jetpack.sprite->progress_step = 0f
0043da05        jetpack_cursor->jetpack.sprite->size_start = 1.5f
0043da0e        jetpack_cursor->jetpack.sprite->size_end = 1.5f
0043da19        int32_t* edx_8 = &jetpack_cursor->jetpack.sprite->position
0043da1c        *edx_8 = jetpack_cursor->jetpack.bod.position.x
0043da21        edx_8[1] = jetpack_cursor->jetpack.bod.position.y
0043da27        edx_8[2] = jetpack_cursor->jetpack.bod.position.z
0043da2a        jetpack_cursor->jetpack.source_cell = cell
0043da30        jetpack_cursor->jetpack.bob_phase = 0f
0043da45        int16_t x87control
0043da45        if ((ftol(x87control, fconvert.t(jetpack_cursor->jetpack.bod.position.z)) & 1) == 0)
0043da5f        jetpack_cursor->jetpack.bob_phase = 0.5f
0043da69        jetpack_cursor->jetpack.bob_phase_step = 0.012820513f
0043da78        return
0043da47        jetpack_cursor->jetpack.bob_phase = 0f
0043da4d        jetpack_cursor->jetpack.bob_phase_step = 0.012820513f
0043da5c        return
