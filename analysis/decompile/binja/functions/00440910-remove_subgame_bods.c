/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: remove_subgame_bods @ 0x440910 */

00440910        struct SubgameRuntime* game_1 = game
00440919        struct TrackRowCell* runtime_cell_cursor = &game->runtime_cells
0044091f        struct BodNode** row_list_next_cursor = &game->runtime_rows[0].row_model.body.bod.bod.list_next
00440925        int32_t rows_remaining = 0xc80
004409b3        int32_t i
00440930        if (((row_list_next_cursor[-2]).w:1.b & 2) != 0)
00440937        struct BodList* row_active_list = &g_game_base->active_bod_list
0044093d        uint32_t row_list_flags = row_list_next_cursor[-2]
00440943        if ((row_list_flags:1.b & 2) == 0)
0044094a        report_errorf("List remove")
00440956        if ((row_list_flags.b & 0x40) == 0)
00440967        struct BodNode* row_list_next = *row_list_next_cursor
0044096b        if (row_list_next != 0)
00440970        row_list_next->list_prev = row_list_next_cursor[-1]
00440973        struct BodNode* row_list_prev = row_list_next_cursor[-1]
00440978        if (row_list_prev == 0)
00440983        row_active_list->first = *row_list_next_cursor
0044097c        row_list_prev->list_next = *row_list_next_cursor
00440986        struct BodNode* row_free_top
00440986        row_free_top.b = row_active_list->free_top.b
00440986        row_free_top:1.b = row_active_list->free_top:1.b
0044098c        *row_list_next_cursor = row_free_top
0044098e        row_active_list->free_top.b = (row_list_next_cursor.w - 0xc).b
0044098e        row_active_list->free_top:1.b = (row_list_next_cursor.w - 0xc):1.b
00440991        uint32_t row_flags_after_clear = row_list_next_cursor[-2]
00440994        row_flags_after_clear:1.b &= 0xfd
00440997        row_list_next_cursor[-2] = row_flags_after_clear
0044095d        report_errorf("List remove NEXTBOD")
0044099a        int32_t cells_remaining = 8
004409aa        int32_t j
004409a1        remove_sub_loc(runtime_cell_cursor)
004409a6        runtime_cell_cursor = &runtime_cell_cursor[1]
004409a9        j = cells_remaining
004409a9        cells_remaining -= 1
004409aa        do while (j != 1)
004409ac        row_list_next_cursor = &row_list_next_cursor[0x3d]
004409b2        i = rows_remaining
004409b2        rows_remaining -= 1
004409b3        do while (i != 1)
004409c0        remove_track_render_cache_bods(&game->segment_cache)
004409c5        struct BodNode** health_list_next_cursor = &game->health_pickups[0].bod.bod.list_next
004409cb        int32_t health_remaining = 8
00440a47        int32_t i_1
004409d2        uint32_t health_list_flags = health_list_next_cursor[-2]
004409d8        if ((health_list_flags:1.b & 2) != 0)
004409e0        struct BodList* health_active_list = &g_game_base->active_bod_list
004409e9        if ((health_list_flags:1.b & 2) == 0)
004409f0        report_errorf("List remove")
004409fc        if ((health_list_flags.b & 0x40) == 0)
00440a0d        struct BodNode* health_list_next = *health_list_next_cursor
00440a11        if (health_list_next != 0)
00440a16        health_list_next->list_prev = health_list_next_cursor[-1]
00440a19        struct BodNode* health_list_prev = health_list_next_cursor[-1]
00440a1e        if (health_list_prev == 0)
00440a29        health_active_list->first = *health_list_next_cursor
00440a22        health_list_prev->list_next = *health_list_next_cursor
00440a2c        struct BodNode* health_free_top
00440a2c        health_free_top.b = health_active_list->free_top.b
00440a2c        health_free_top:1.b = health_active_list->free_top:1.b
00440a32        *health_list_next_cursor = health_free_top
00440a34        health_active_list->free_top.b = (health_list_next_cursor.w - 0xc).b
00440a34        health_active_list->free_top:1.b = (health_list_next_cursor.w - 0xc):1.b
00440a37        uint32_t health_flags_after_clear = health_list_next_cursor[-2]
00440a3a        health_flags_after_clear:1.b &= 0xfd
00440a3d        health_list_next_cursor[-2] = health_flags_after_clear
00440a03        report_errorf("List remove NEXTBOD")
00440a40        health_list_next_cursor[0xb] = 0
00440a43        health_list_next_cursor = &health_list_next_cursor[0x1d]
00440a46        i_1 = health_remaining
00440a46        health_remaining -= 1
00440a47        do while (i_1 != 1)
00440a52        if (((game->speedup_pickup.body.bod.bod.list_flags).w:1.b & 2) != 0)
00440a60        struct BodList* edx_9 = &g_game_base->active_bod_list
00440a66        uint16_t list_flags_2 = (game->speedup_pickup.body.bod.bod.list_flags).w
00440a6c        if ((list_flags_2:1.b & 2) == 0)
00440a73        report_errorf("List remove")
00440a80        if ((list_flags_2.b & 0x40) == 0)
00440a91        struct BodNode* list_next_1 = game->speedup_pickup.body.bod.bod.list_next
00440a96        if (list_next_1 != 0)
00440a98        int16_t list_prev_6 = (game->speedup_pickup.body.bod.bod.list_prev).w
00440a9b        list_next_1->list_prev.b = list_prev_6.b
00440a9b        list_next_1->list_prev:1.b = list_prev_6:1.b
00440a9e        struct BodNode* list_prev_1 = game->speedup_pickup.body.bod.bod.list_prev
00440aa3        if (list_prev_1 == 0)
00440ab0        edx_9->first = game->speedup_pickup.body.bod.bod.list_next
00440aa8        list_prev_1->list_next = game->speedup_pickup.body.bod.bod.list_next
00440ab6        game->speedup_pickup.body.bod.bod.list_next = edx_9->free_top
00440ab9        edx_9->free_top = &game->speedup_pickup
00440abc        uint32_t list_flags_3 = game->speedup_pickup.body.bod.bod.list_flags
00440abf        list_flags_3:1.b &= 0xfd
00440ac2        game->speedup_pickup.body.bod.bod.list_flags = list_flags_3
00440a87        report_errorf("List remove NEXTBOD")
00440ac5        game->speedup_pickup.state = TRACK_PICKUP_STATE_INACTIVE
00440ad4        if (((game->jetpack_pickup.bod.bod.list_flags).w:1.b & 2) != 0)
00440adc        uint16_t list_flags_4 = (game->jetpack_pickup.bod.bod.list_flags).w
00440ae8        struct BodList* edx_13 = &g_game_base->active_bod_list
00440af1        if ((list_flags_4:1.b & 2) == 0)
00440af8        report_errorf("List remove")
00440b05        if ((list_flags_4.b & 0x40) == 0)
00440b16        struct BodNode* list_next_2 = game->jetpack_pickup.bod.bod.list_next
00440b1b        if (list_next_2 != 0)
00440b1d        int16_t list_prev_7 = (game->jetpack_pickup.bod.bod.list_prev).w
00440b20        list_next_2->list_prev.b = list_prev_7.b
00440b20        list_next_2->list_prev:1.b = list_prev_7:1.b
00440b23        struct BodNode* list_prev_2 = game->jetpack_pickup.bod.bod.list_prev
00440b28        if (list_prev_2 == 0)
00440b35        edx_13->first = game->jetpack_pickup.bod.bod.list_next
00440b2d        list_prev_2->list_next = game->jetpack_pickup.bod.bod.list_next
00440b3b        game->jetpack_pickup.bod.bod.list_next = edx_13->free_top
00440b3e        edx_13->free_top = &game->jetpack_pickup
00440b41        uint32_t list_flags_5 = game->jetpack_pickup.bod.bod.list_flags
00440b44        list_flags_5:1.b &= 0xfd
00440b47        game->jetpack_pickup.bod.bod.list_flags = list_flags_5
00440b0c        report_errorf("List remove NEXTBOD")
00440b4a        game->jetpack_pickup.state = TRACK_PICKUP_STATE_INACTIVE
00440b50        struct BodNode** garbage_list_next_cursor = &game->garbage_hazards.slots[0].body.bod.bod.list_next
00440b56        int32_t garbage_remaining = 0x32
00440bd6        int32_t i_2
00440b61        if (((garbage_list_next_cursor[-2]).w:1.b & 2) != 0)
00440b63        garbage_list_next_cursor[0x1e] = 0
00440b6c        uint32_t garbage_list_flags = garbage_list_next_cursor[-2]
00440b72        struct BodList* garbage_active_list = &g_game_base->active_bod_list
00440b78        if ((garbage_list_flags:1.b & 2) == 0)
00440b7f        report_errorf("List remove")
00440b8b        if ((garbage_list_flags.b & 0x40) == 0)
00440b9c        struct BodNode* garbage_list_next = *garbage_list_next_cursor
00440ba0        if (garbage_list_next != 0)
00440ba5        garbage_list_next->list_prev = garbage_list_next_cursor[-1]
00440ba8        struct BodNode* garbage_list_prev = garbage_list_next_cursor[-1]
00440bad        if (garbage_list_prev == 0)
00440bb8        garbage_active_list->first = *garbage_list_next_cursor
00440bb1        garbage_list_prev->list_next = *garbage_list_next_cursor
00440bbb        struct BodNode* garbage_free_top
00440bbb        garbage_free_top.b = garbage_active_list->free_top.b
00440bbb        garbage_free_top:1.b = garbage_active_list->free_top:1.b
00440bc1        *garbage_list_next_cursor = garbage_free_top
00440bc3        garbage_active_list->free_top.b = (garbage_list_next_cursor.w - 0xc).b
00440bc3        garbage_active_list->free_top:1.b = (garbage_list_next_cursor.w - 0xc):1.b
00440bc6        uint32_t garbage_flags_after_clear = garbage_list_next_cursor[-2]
00440bc9        garbage_flags_after_clear:1.b &= 0xfd
00440bcc        garbage_list_next_cursor[-2] = garbage_flags_after_clear
00440b92        report_errorf("List remove NEXTBOD")
00440bcf        garbage_list_next_cursor = &garbage_list_next_cursor[0x31]
00440bd5        i_2 = garbage_remaining
00440bd5        garbage_remaining -= 1
00440bd6        do while (i_2 != 1)
00440bd8        struct BodNode** slug_list_next_cursor = &game->slug_hazards.slots[0].body.bod.bod.list_next
00440bde        int32_t slug_remaining = 8
00440c5e        int32_t i_3
00440be9        if (((slug_list_next_cursor[-2]).w:1.b & 2) != 0)
00440beb        slug_list_next_cursor[0x1d] = 0
00440bf4        uint32_t slug_list_flags = slug_list_next_cursor[-2]
00440bf7        struct BodList* slug_active_list = &g_game_base->active_bod_list
00440c00        if ((slug_list_flags:1.b & 2) == 0)
00440c07        report_errorf("List remove")
00440c13        if ((slug_list_flags.b & 0x40) == 0)
00440c24        struct BodNode* slug_list_next = *slug_list_next_cursor
00440c28        if (slug_list_next != 0)
00440c2d        slug_list_next->list_prev = slug_list_next_cursor[-1]
00440c30        struct BodNode* slug_list_prev = slug_list_next_cursor[-1]
00440c35        if (slug_list_prev == 0)
00440c40        slug_active_list->first = *slug_list_next_cursor
00440c39        slug_list_prev->list_next = *slug_list_next_cursor
00440c43        struct BodNode* slug_free_top
00440c43        slug_free_top.b = slug_active_list->free_top.b
00440c43        slug_free_top:1.b = slug_active_list->free_top:1.b
00440c49        *slug_list_next_cursor = slug_free_top
00440c4b        slug_active_list->free_top.b = (slug_list_next_cursor.w - 0xc).b
00440c4b        slug_active_list->free_top:1.b = (slug_list_next_cursor.w - 0xc):1.b
00440c4e        uint32_t slug_flags_after_clear = slug_list_next_cursor[-2]
00440c51        slug_flags_after_clear:1.b &= 0xfd
00440c54        slug_list_next_cursor[-2] = slug_flags_after_clear
00440c1a        report_errorf("List remove NEXTBOD")
00440c57        slug_list_next_cursor = &slug_list_next_cursor[0x3b]
00440c5d        i_3 = slug_remaining
00440c5d        slug_remaining -= 1
00440c5e        do while (i_3 != 1)
00440c60        struct BodNode** ring_list_next_cursor = &game->ring_effects.slots[0].bod.list_next
00440c66        int32_t ring_remaining = 2
00440ce3        int32_t i_4
00440c6e        if (ring_list_next_cursor[0x1d] != 0)
00440c76        uint32_t ring_list_flags = ring_list_next_cursor[-2]
00440c79        struct BodList* ring_active_list = &g_game_base->active_bod_list
00440c82        if ((ring_list_flags:1.b & 2) == 0)
00440c89        report_errorf("List remove")
00440c95        if ((ring_list_flags.b & 0x40) == 0)
00440ca6        struct BodNode* ring_list_next = *ring_list_next_cursor
00440caa        if (ring_list_next != 0)
00440caf        ring_list_next->list_prev = ring_list_next_cursor[-1]
00440cb2        struct BodNode* ring_list_prev = ring_list_next_cursor[-1]
00440cb7        if (ring_list_prev == 0)
00440cc2        ring_active_list->first = *ring_list_next_cursor
00440cbb        ring_list_prev->list_next = *ring_list_next_cursor
00440cc5        struct BodNode* ring_free_top
00440cc5        ring_free_top.b = ring_active_list->free_top.b
00440cc5        ring_free_top:1.b = ring_active_list->free_top:1.b
00440ccb        *ring_list_next_cursor = ring_free_top
00440ccd        ring_active_list->free_top.b = (ring_list_next_cursor.w - 0xc).b
00440ccd        ring_active_list->free_top:1.b = (ring_list_next_cursor.w - 0xc):1.b
00440cd0        uint32_t ring_flags_after_clear = ring_list_next_cursor[-2]
00440cd3        ring_flags_after_clear:1.b &= 0xfd
00440cd6        ring_list_next_cursor[-2] = ring_flags_after_clear
00440c9c        report_errorf("List remove NEXTBOD")
00440cd9        ring_list_next_cursor[0x1d] = 0
00440cdc        ring_list_next_cursor = &ring_list_next_cursor[0x7e]
00440ce2        i_4 = ring_remaining
00440ce2        ring_remaining -= 1
00440ce3        do while (i_4 != 1)
00440cee        if (((game->player.body.bod.bod.list_flags).w:1.b & 2) != 0)
00440cfa        uint16_t list_flags = (game->player.body.bod.bod.list_flags).w
00440d06        struct BodList* ecx_11 = &g_game_base->active_bod_list
00440d0f        if ((list_flags:1.b & 2) == 0)
00440d16        report_errorf("List remove")
00440d22        if ((list_flags.b & 0x40) == 0)
00440d33        struct BodNode* list_next = game->player.body.bod.bod.list_next
00440d38        if (list_next != 0)
00440d3d        list_next->list_prev = game->player.body.bod.bod.list_prev
00440d40        struct BodNode* list_prev = game->player.body.bod.bod.list_prev
00440d45        if (list_prev == 0)
00440d52        ecx_11->first = game->player.body.bod.bod.list_next
00440d4a        list_prev->list_next = game->player.body.bod.bod.list_next
00440d55        struct BodNode* edx_31
00440d55        edx_31.b = ecx_11->free_top.b
00440d55        edx_31:1.b = ecx_11->free_top:1.b
00440d58        game->player.body.bod.bod.list_next = edx_31
00440d5b        ecx_11->free_top.b = (&game->player).b
00440d5b        ecx_11->free_top:1.b = (&game->player):1.b
00440d5e        uint32_t list_flags_1 = game->player.body.bod.bod.list_flags
00440d61        list_flags_1:1.b &= 0xfd
00440d64        game->player.body.bod.bod.list_flags = list_flags_1
00440d29        report_errorf("List remove NEXTBOD")
00440d73        struct BodList* edx_32 = &g_game_base->active_bod_list
00440d79        uint16_t list_flags_6 = (game->player.presentation.body.bod.bod.list_flags).w
00440d7f        if ((list_flags_6:1.b & 2) == 0)
00440d86        report_errorf("List remove")
00440d93        if ((list_flags_6.b & 0x40) == 0)
00440da4        struct BodNode* list_next_3 = game->player.presentation.body.bod.bod.list_next
00440da9        if (list_next_3 != 0)
00440dab        int16_t list_prev_8 = (game->player.presentation.body.bod.bod.list_prev).w
00440dae        list_next_3->list_prev.b = list_prev_8.b
00440dae        list_next_3->list_prev:1.b = list_prev_8:1.b
00440db1        struct BodNode* list_prev_3 = game->player.presentation.body.bod.bod.list_prev
00440db6        if (list_prev_3 == 0)
00440dc3        edx_32->first = game->player.presentation.body.bod.bod.list_next
00440dbb        list_prev_3->list_next = game->player.presentation.body.bod.bod.list_next
00440dc9        game->player.presentation.body.bod.bod.list_next = edx_32->free_top
00440dcc        edx_32->free_top = &game->player.presentation
00440dcf        uint32_t list_flags_7 = game->player.presentation.body.bod.bod.list_flags
00440dd2        list_flags_7:1.b &= 0xfd
00440dd5        game->player.presentation.body.bod.bod.list_flags = list_flags_7
00440d9a        report_errorf("List remove NEXTBOD")
00440dde        uint16_t list_flags_8 = (game->player.presentation.jetpack_channel.body.bod.bod.list_flags).w
00440dea        struct BodList* edx_34 = &g_game_base->active_bod_list
00440df3        if ((list_flags_8:1.b & 2) == 0)
00440dfa        report_errorf("List remove")
00440e07        if ((list_flags_8.b & 0x40) == 0)
00440e18        struct BodNode* list_next_4 = game->player.presentation.jetpack_channel.body.bod.bod.list_next
00440e1d        if (list_next_4 != 0)
00440e1f        int16_t list_prev_9 = (game->player.presentation.jetpack_channel.body.bod.bod.list_prev).w
00440e22        list_next_4->list_prev.b = list_prev_9.b
00440e22        list_next_4->list_prev:1.b = list_prev_9:1.b
00440e25        struct BodNode* list_prev_4 = game->player.presentation.jetpack_channel.body.bod.bod.list_prev
00440e2a        if (list_prev_4 == 0)
00440e37        edx_34->first = game->player.presentation.jetpack_channel.body.bod.bod.list_next
00440e2f        list_prev_4->list_next = game->player.presentation.jetpack_channel.body.bod.bod.list_next
00440e3d        game->player.presentation.jetpack_channel.body.bod.bod.list_next = edx_34->free_top
00440e40        edx_34->free_top = &game->player.presentation.jetpack_channel
00440e43        uint32_t list_flags_9 = game->player.presentation.jetpack_channel.body.bod.bod.list_flags
00440e46        list_flags_9:1.b &= 0xfd
00440e49        game->player.presentation.jetpack_channel.body.bod.bod.list_flags = list_flags_9
00440e0e        report_errorf("List remove NEXTBOD")
00440e52        uint16_t list_flags_10 = (game->player.presentation.weapon_channels[0].body.bod.bod.list_flags).w
00440e5e        struct BodList* edx_36 = &g_game_base->active_bod_list
00440e67        if ((list_flags_10:1.b & 2) == 0)
00440e6e        report_errorf("List remove")
00440e7b        if ((list_flags_10.b & 0x40) == 0)
00440e8c        struct BodNode* list_next_5 = game->player.presentation.weapon_channels[0].body.bod.bod.list_next
00440e91        if (list_next_5 != 0)
00440e93        int16_t list_prev_10 = (game->player.presentation.weapon_channels[0].body.bod.bod.list_prev).w
00440e96        list_next_5->list_prev.b = list_prev_10.b
00440e96        list_next_5->list_prev:1.b = list_prev_10:1.b
00440e99        struct BodNode* list_prev_5 = game->player.presentation.weapon_channels[0].body.bod.bod.list_prev
00440e9e        if (list_prev_5 == 0)
00440eab        edx_36->first = game->player.presentation.weapon_channels[0].body.bod.bod.list_next
00440ea3        list_prev_5->list_next = game->player.presentation.weapon_channels[0].body.bod.bod.list_next
00440eb1        game->player.presentation.weapon_channels[0].body.bod.bod.list_next = edx_36->free_top
00440eb4        edx_36->free_top = &game->player.presentation.weapon_channels
00440eb7        uint32_t list_flags_11 = game->player.presentation.weapon_channels[0].body.bod.bod.list_flags
00440eba        list_flags_11:1.b &= 0xfd
00440ebd        game->player.presentation.weapon_channels[0].body.bod.bod.list_flags = list_flags_11
00440e82        report_errorf("List remove NEXTBOD")
00440ed2        recycle_bod_to_free_list(&g_game_base->active_bod_list, &game->player.presentation.weapon_channels[1])
00440eea        recycle_bod_to_free_list(&g_game_base->active_bod_list, &game->player.presentation.weapon_channels[2])
00440f02        recycle_bod_to_free_list(&g_game_base->active_bod_list, &game->player.presentation.invincible_shell)
00440f09        game->player.movement_mode_selector = 0
00440f14        struct GolbShot* golb_shot_cursor = &game->player.golb_shots
00440f1a        int32_t i_6 = 0xc
00440f3a        int32_t i_5
00440f2a        if (golb_shot_cursor->state == 1)
00440f2e        kill_golb(golb_shot_cursor)
00440f33        golb_shot_cursor = &golb_shot_cursor[1]
00440f39        i_5 = i_6
00440f39        i_6 -= 1
00440f3a        do while (i_5 != 1)
00440f49        if (((game->player.click_start.bod.bod.bod.list_flags).w:1.b & 2) != 0)
00440f5d        recycle_bod_to_free_list(&g_game_base->active_bod_list, &game->player.click_start)
00440f62        game->player.click_start.state = CLICK_START_STATE_INACTIVE
00440f71        kill_game_sprites(&g_sprite_manager)
00440f7b        return
