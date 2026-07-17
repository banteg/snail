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
0043d6fc        struct SubHealthSlotCursor* health_cursor = game + ebx * 0x74
0043d6ff        health_cursor->health.state = TRACK_PICKUP_STATE_ACTIVE
0043d709        health_cursor->health.owner = player
0043d718        float x = cell_1->anchor_position.x
0043d72a        float x_2 = x
0043d736        health_cursor->health.bod.position.x = x
0043d73c        health_cursor->health.bod.position.y = fconvert.s(fconvert.t(cell_1->anchor_position.y) + fconvert.t(0.600000024f))
0043d73f        health_cursor->health.bod.position.z = cell_1->anchor_position.z
0043d751        if (((health_cursor->health.bod.bod.list_flags).w:1.b & 2) == 0)
0043d762        struct GameRoot* game_base_1 = g_game_base
0043d76e        struct BodNode* first = game_base_1->active_bod_list.first
0043d776        if (first != 0)
0043d784        first->list_prev = &health_cursor->health
0043d787        void* edx_3
0043d787        edx_3.b = game_base_1->active_bod_list.first.b
0043d787        edx_3:1.b = *(&game_base_1->active_bod_list.first + 1)
0043d787        edx_3:2.b = *(&game_base_1->active_bod_list.first + 2)
0043d787        edx_3:3.b = *(&game_base_1->active_bod_list.first + 3)
0043d78c        *(*(edx_3 + 8) + 0xc) = edx_3
0043d78f        void* edx_4
0043d78f        edx_4.b = game_base_1->active_bod_list.first.b
0043d78f        edx_4:1.b = *(&game_base_1->active_bod_list.first + 1)
0043d78f        edx_4:2.b = *(&game_base_1->active_bod_list.first + 2)
0043d78f        edx_4:3.b = *(&game_base_1->active_bod_list.first + 3)
0043d791        cell_1 = cell
0043d795        void* edx_5 = *(edx_4 + 8)
0043d798        game_base_1->active_bod_list.first.b = edx_5.b
0043d798        *(&game_base_1->active_bod_list.first + 1) = edx_5:1.b
0043d798        *(&game_base_1->active_bod_list.first + 2) = edx_5:2.b
0043d798        *(&game_base_1->active_bod_list.first + 3) = edx_5:3.b
0043d79a        *(edx_5 + 8) = 0
0043d778        game_base_1->active_bod_list.first.b = (&health_cursor->health).b
0043d778        *(&game_base_1->active_bod_list.first + 1) = (&health_cursor->health):1.b
0043d778        *(&game_base_1->active_bod_list.first + 2) = (&health_cursor->health):2.b
0043d778        *(&game_base_1->active_bod_list.first + 3) = (&health_cursor->health):3.b
0043d77a        health_cursor->health.bod.bod.list_prev = first
0043d77d        void* ecx_3
0043d77d        ecx_3.b = game_base_1->active_bod_list.first.b
0043d77d        ecx_3:1.b = *(&game_base_1->active_bod_list.first + 1)
0043d77d        ecx_3:2.b = *(&game_base_1->active_bod_list.first + 2)
0043d77d        ecx_3:3.b = *(&game_base_1->active_bod_list.first + 3)
0043d77f        *(ecx_3 + 0xc) = first
0043d7a1        uint32_t list_flags = health_cursor->health.bod.bod.list_flags
0043d7a4        list_flags:1.b |= 2
0043d7a7        health_cursor->health.bod.bod.list_flags = list_flags
0043d758        report_errorf("List ADD")
0043d7c0        struct Sprite* eax_7 = allocate_sprite(&g_sprite_manager, player->player_slot, 0x39, 0xffffffff, 0xffffffff)
0043d7c5        health_cursor->health.sprite = eax_7
0043d7cb        enum SpriteFlag flags = eax_7->flags
0043d7ce        flags:1.b |= 8
0043d7d1        eax_7->flags = flags
0043d7dc        health_cursor->health.sprite->gravity_step = 0f
0043d7e5        health_cursor->health.sprite->progress = 0f
0043d7f3        health_cursor->health.sprite->progress_step = 0f
0043d7fc        health_cursor->health.sprite->size_start = 0.600000024f
0043d805        health_cursor->health.sprite->size_end = 0.600000024f
0043d80e        float x_1 = health_cursor->health.bod.position.x
0043d810        char* ecx_7 = &health_cursor->health.sprite->position
0043d813        *ecx_7 = x_1.b
0043d813        ecx_7[1] = x_1:1.b
0043d813        ecx_7[2] = x_1:2.b
0043d813        ecx_7[3] = x_1:3.b
0043d818        *(ecx_7 + 4) = health_cursor->health.bod.position.y
0043d81b        int16_t z = (health_cursor->health.bod.position.z).w
0043d81e        ecx_7[8] = z.b
0043d81e        ecx_7[9] = z:1.b
0043d821        health_cursor->health.source_cell = cell_1
0043d827        health_cursor->health.bob_phase = 0f
0043d83a        int16_t x87control
0043d83a        if ((ftol(x87control, fconvert.t(health_cursor->health.bod.position.z)) & 1) == 0)
0043d848        health_cursor->health.bob_phase = 0.5f
0043d83c        health_cursor->health.bob_phase = 0f
0043d86c        *(game + (ebx + 0x75cc) * 0x74) = 0x3c520d21
0043d876        return
