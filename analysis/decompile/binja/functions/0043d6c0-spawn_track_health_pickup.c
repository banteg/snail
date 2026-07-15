/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_track_health_pickup @ 0x43d6c0 */

0043d6c8        int32_t ebx = 0
0043d6ca        enum TrackPickupState* eax = &game->health_pickups[0].state
0043d6d3        while ((eax - 0x356038)->health_pickups[0].state != TRACK_PICKUP_STATE_INACTIVE)
0043d6d5        ebx += 1
0043d6d6        eax = &eax[0x1d]
0043d6dc        if (ebx s>= 8)
0043d6e2        return
0043d6ef        struct TrackRowCell* cell_1 = cell
0043d6fc        void* esi = game + ebx * 0x74
0043d6ff        *(esi + 0x356038) = 1
0043d709        *(esi + 0x35603c) = player
0043d718        float x = cell_1->anchor_position.x
0043d71b        float z = cell_1->anchor_position.z
0043d72a        float x_1 = x
0043d72e        float var_8 = fconvert.s(fconvert.t(cell_1->anchor_position.y) + fconvert.t(0.600000024f))
0043d736        *(esi + 0x356010) = x
0043d73c        *(esi + 0x356014) = var_8
0043d73f        *(esi + 0x356018) = z
0043d751        if (((*(esi + 0x356004)).w:1.b & 2) == 0)
0043d762        struct GameRoot* game_base_1 = g_game_base
0043d76e        struct FrameBodBase* first = game_base_1->active_bod_list.first
0043d776        if (first != 0)
0043d784        first->bod.list_prev = esi + 0x356000
0043d787        void* edx_2
0043d787        edx_2.b = game_base_1->active_bod_list.first.b
0043d787        edx_2:1.b = *(&game_base_1->active_bod_list.first + 1)
0043d787        edx_2:2.b = *(&game_base_1->active_bod_list.first + 2)
0043d787        edx_2:3.b = *(&game_base_1->active_bod_list.first + 3)
0043d78c        *(*(edx_2 + 8) + 0xc) = edx_2
0043d78f        void* edx_3
0043d78f        edx_3.b = game_base_1->active_bod_list.first.b
0043d78f        edx_3:1.b = *(&game_base_1->active_bod_list.first + 1)
0043d78f        edx_3:2.b = *(&game_base_1->active_bod_list.first + 2)
0043d78f        edx_3:3.b = *(&game_base_1->active_bod_list.first + 3)
0043d791        cell_1 = cell
0043d795        void* edx_4 = *(edx_3 + 8)
0043d798        game_base_1->active_bod_list.first.b = edx_4.b
0043d798        *(&game_base_1->active_bod_list.first + 1) = edx_4:1.b
0043d798        *(&game_base_1->active_bod_list.first + 2) = edx_4:2.b
0043d798        *(&game_base_1->active_bod_list.first + 3) = edx_4:3.b
0043d79a        *(edx_4 + 8) = 0
0043d778        game_base_1->active_bod_list.first.b = (esi + 0x356000).b
0043d778        *(&game_base_1->active_bod_list.first + 1) = (esi + 0x356000):1.b
0043d778        *(&game_base_1->active_bod_list.first + 2) = (esi + 0x356000):2.b
0043d778        *(&game_base_1->active_bod_list.first + 3) = (esi + 0x356000):3.b
0043d77a        (esi + 0x356000)->bod.list_prev = first
0043d77d        void* ecx_3
0043d77d        ecx_3.b = game_base_1->active_bod_list.first.b
0043d77d        ecx_3:1.b = *(&game_base_1->active_bod_list.first + 1)
0043d77d        ecx_3:2.b = *(&game_base_1->active_bod_list.first + 2)
0043d77d        ecx_3:3.b = *(&game_base_1->active_bod_list.first + 3)
0043d77f        *(ecx_3 + 0xc) = first
0043d7a1        uint32_t list_flags = (esi + 0x356000)->bod.list_flags
0043d7a4        list_flags:1.b |= 2
0043d7a7        (esi + 0x356000)->bod.list_flags = list_flags
0043d758        report_errorf("List ADD")
0043d7c0        struct Sprite* eax_7 = allocate_sprite(&g_sprite_manager, player->player_slot, 0x39, 0xffffffff, 0xffffffff)
0043d7c5        *(esi + 0x356064) = eax_7
0043d7cb        enum SpriteFlag flags = eax_7->flags
0043d7ce        flags:1.b |= 8
0043d7d1        eax_7->flags = flags
0043d7dc        *(*(esi + 0x356064) + 0x78) = 0
0043d7e5        *(*(esi + 0x356064) + 0x68) = 0
0043d7f3        *(*(esi + 0x356064) + 0x6c) = 0
0043d7fc        *(*(esi + 0x356064) + 0x60) = 0x3f19999a
0043d805        *(*(esi + 0x356064) + 0x64) = 0x3f19999a
0043d80e        float edx_9 = *(esi + 0x356010)
0043d810        char* ecx_7 = *(esi + 0x356064) + 0x48
0043d813        *ecx_7 = edx_9.b
0043d813        ecx_7[1] = edx_9:1.b
0043d813        ecx_7[2] = edx_9:2.b
0043d813        ecx_7[3] = edx_9:3.b
0043d818        *(ecx_7 + 4) = *(esi + 0x356014)
0043d81b        int16_t edx_11 = (*(esi + 0x356018)).w
0043d81e        ecx_7[8] = edx_11.b
0043d81e        ecx_7[9] = edx_11:1.b
0043d821        *(esi + 0x356068) = cell_1
0043d827        *(esi + 0x35606c) = 0
0043d83a        int16_t x87control
0043d83a        if ((ftol(x87control, fconvert.t(*(esi + 0x356018))) & 1) == 0)
0043d848        *(esi + 0x35606c) = 0x3f000000
0043d83c        *(esi + 0x35606c) = 0
0043d86c        *(game + (ebx + 0x75cc) * 0x74) = 0x3c520d21
0043d876        return
