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
0043d8cd        void* esi = game + edx * 0x19c
0043d8d0        *(esi + 0x355e9c) = 1
0043d8da        *(esi + 0x355ea0) = player
0043d8e9        float x = cell->anchor_position.x
0043d8ec        float z = cell->anchor_position.z
0043d8fb        float x_1 = x
0043d8ff        float var_8 = fconvert.s(fconvert.t(cell->anchor_position.y) + fconvert.t(1.5f))
0043d907        *(esi + 0x355e74) = x
0043d90d        *(esi + 0x355e78) = var_8
0043d910        *(esi + 0x355e7c) = z
0043d916        int32_t eax_8 = cell->lane_and_flags & 7
0043d92b        if (eax_8 == 3 && cell->__offset(0xffffffffffffffe8).b == 0xe && cell->__offset(0xe4).b == 0xe)
0043d951        *(esi + 0x355e74) = fconvert.s(fconvert.t(*(esi + 0x355e74)) + fconvert.t(0.5f))
0043d947        if (eax_8 == 4 && cell->__offset(0xffffffffffffff94).b == 0xe && cell->__offset(0x90).b == 0xe)
0043d951        *(esi + 0x355e74) = fconvert.s(fconvert.t(*(esi + 0x355e74)) - fconvert.t(0.5f))
0043d962        if (((*(esi + 0x355e68)).w:1.b & 2) == 0)
0043d973        struct GameRoot* game_base_1 = g_game_base
0043d97f        struct FrameBodBase* first = game_base_1->active_bod_list.first
0043d987        if (first != 0)
0043d995        first->bod.list_prev = esi + 0x355e64
0043d998        void* first_1 = game_base_1->active_bod_list.first
0043d99d        *(*(first_1 + 8) + 0xc) = first_1
0043d9a4        void* list_prev = game_base_1->active_bod_list.first->bod.list_prev
0043d9a7        game_base_1->active_bod_list.first = list_prev
0043d9a9        *(list_prev + 8) = 0
0043d989        game_base_1->active_bod_list.first = esi + 0x355e64
0043d98b        (esi + 0x355e64)->bod.list_prev.b = nullptr
0043d98b        (esi + 0x355e64)->bod.list_prev:1.b = 0
0043d990        game_base_1->active_bod_list.first->bod.list_next = 0
0043d9ac        uint32_t list_flags = (esi + 0x355e64)->bod.list_flags
0043d9af        list_flags:1.b |= 2
0043d9b2        (esi + 0x355e64)->bod.list_flags = list_flags
0043d969        report_errorf("List ADD")
0043d9cb        struct Sprite* eax_13 = allocate_sprite(&g_sprite_manager, player->player_slot, 0x7c, 0xffffffff, 0xffffffff)
0043d9d0        *(esi + 0x355ec8) = eax_13
0043d9d6        enum SpriteFlag flags = eax_13->flags
0043d9d9        flags:1.b |= 8
0043d9dc        eax_13->flags = flags
0043d9e5        *(*(esi + 0x355ec8) + 0x78) = 0
0043d9ee        *(*(esi + 0x355ec8) + 0x68) = 0
0043d9fc        *(*(esi + 0x355ec8) + 0x6c) = 0
0043da05        *(*(esi + 0x355ec8) + 0x60) = 0x3fc00000
0043da0e        *(*(esi + 0x355ec8) + 0x64) = 0x3fc00000
0043da19        float* edx_7 = *(esi + 0x355ec8) + 0x48
0043da1c        *edx_7 = *(esi + 0x355e74)
0043da21        edx_7[1] = *(esi + 0x355e78)
0043da27        edx_7[2] = *(esi + 0x355e7c)
0043da2a        *(esi + 0x355ecc) = cell
0043da30        *(esi + 0x355ed0) = 0
0043da45        int16_t x87control
0043da45        if ((ftol(x87control, fconvert.t(*(esi + 0x355e7c))) & 1) == 0)
0043da5f        *(esi + 0x355ed0) = 0x3f000000
0043da69        __builtin_strncpy(esi + 0x355ed4, "!\rR<", 4)
0043da78        return
0043da47        *(esi + 0x355ed0) = 0
0043da4d        __builtin_strncpy(esi + 0x355ed4, "!\rR<", 4)
0043da5c        return
