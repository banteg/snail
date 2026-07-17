/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: remove_subgame_bods @ 0x440910 */

00440910        struct SubgameRuntime* game_1 = game
00440919        struct TrackRowCell (* cell)[0xc80][0x8] = &game->runtime_cells
0044091f        struct BodNode** esi = &game->runtime_rows[0].primary_body.bod.bod.list_next
00440925        int32_t i_6 = 0xc80
004409b3        int32_t i
00440930        if ((((esi - 0x5ccad8)->runtime_rows[0].primary_body.bod.bod.list_flags).w:1.b & 2) != 0)
00440937        struct BodList* ecx = &g_game_base->active_bod_list
0044093d        uint16_t list_flags = ((esi - 0x5ccad8)->runtime_rows[0].primary_body.bod.bod.list_flags).w
00440943        if ((list_flags:1.b & 2) == 0)
0044094a        report_errorf("List remove")
00440956        if ((list_flags.b & 0x40) == 0)
00440967        struct BodNode* list_next = (esi - 0x5ccad8)->runtime_rows[0].primary_body.bod.bod.list_next
0044096b        if (list_next != 0)
00440970        list_next->list_prev = (esi - 0x5ccad8)->runtime_rows[0].primary_body.bod.bod.list_prev
00440973        struct BodNode* list_prev = (esi - 0x5ccad8)->runtime_rows[0].primary_body.bod.bod.list_prev
00440978        if (list_prev == 0)
00440983        ecx->first = (esi - 0x5ccad8)->runtime_rows[0].primary_body.bod.bod.list_next
0044097c        list_prev->list_next = (esi - 0x5ccad8)->runtime_rows[0].primary_body.bod.bod.list_next
00440986        struct BodNode* edx_3
00440986        edx_3.b = ecx->free_top.b
00440986        edx_3:1.b = ecx->free_top:1.b
0044098c        (esi - 0x5ccad8)->runtime_rows[0].primary_body.bod.bod.list_next = edx_3
0044098e        ecx->free_top.b = (esi.w - 0xc).b
0044098e        ecx->free_top:1.b = (esi.w - 0xc):1.b
00440991        uint32_t list_flags_1 = (esi - 0x5ccad8)->runtime_rows[0].primary_body.bod.bod.list_flags
00440994        list_flags_1:1.b &= 0xfd
00440997        (esi - 0x5ccad8)->runtime_rows[0].primary_body.bod.bod.list_flags = list_flags_1
0044095d        report_errorf("List remove NEXTBOD")
0044099a        int32_t j_1 = 8
004409aa        int32_t j
004409a1        remove_sub_loc(cell)
004409a6        cell = &(*cell)[0][1]
004409a9        j = j_1
004409a9        j_1 -= 1
004409aa        do while (j != 1)
004409ac        esi = &esi[0x3d]
004409b2        i = i_6
004409b2        i_6 -= 1
004409b3        do while (i != 1)
004409c0        remove_track_render_cache_bods(&game->segment_cache)
004409c5        struct SubHealth** esi_1 = &game->health_pickups[0].list_next
004409cb        int32_t i_7 = 8
00440a47        int32_t i_1
004409d2        uint16_t list_flags_2 = ((esi_1 - 0x35600c)->health_pickups[0].list_flags).w
004409d8        if ((list_flags_2:1.b & 2) != 0)
004409e0        struct BodList* ecx_4 = &g_game_base->active_bod_list
004409e9        if ((list_flags_2:1.b & 2) == 0)
004409f0        report_errorf("List remove")
004409fc        if ((list_flags_2.b & 0x40) == 0)
00440a0d        struct SubHealth* list_next_1 = (esi_1 - 0x35600c)->health_pickups[0].list_next
00440a11        if (list_next_1 != 0)
00440a16        list_next_1->list_prev = (esi_1 - 0x35600c)->health_pickups[0].list_prev
00440a19        struct SubHealth* list_prev_1 = (esi_1 - 0x35600c)->health_pickups[0].list_prev
00440a1e        if (list_prev_1 == 0)
00440a29        ecx_4->first = (esi_1 - 0x35600c)->health_pickups[0].list_next
00440a22        list_prev_1->list_next = (esi_1 - 0x35600c)->health_pickups[0].list_next
00440a2c        struct SubHealth* edx_10
00440a2c        edx_10.b = ecx_4->free_top.b
00440a2c        edx_10:1.b = ecx_4->free_top:1.b
00440a32        (esi_1 - 0x35600c)->health_pickups[0].list_next = edx_10
00440a34        ecx_4->free_top.b = (esi_1.w - 0xc).b
00440a34        ecx_4->free_top:1.b = (esi_1.w - 0xc):1.b
00440a37        uint32_t list_flags_3 = (esi_1 - 0x35600c)->health_pickups[0].list_flags
00440a3a        list_flags_3:1.b &= 0xfd
00440a3d        (esi_1 - 0x35600c)->health_pickups[0].list_flags = list_flags_3
00440a03        report_errorf("List remove NEXTBOD")
00440a40        (esi_1 - 0x35600c)->health_pickups[0].state = TRACK_PICKUP_STATE_INACTIVE
00440a43        esi_1 = &esi_1[0x1d]
00440a46        i_1 = i_7
00440a46        i_7 -= 1
00440a47        do while (i_1 != 1)
00440a52        if (((game->speedup_pickup.list_flags).w:1.b & 2) != 0)
00440a60        struct BodList* edx_11 = &g_game_base->active_bod_list
00440a66        uint16_t list_flags_12 = (game->speedup_pickup.list_flags).w
00440a6c        if ((list_flags_12:1.b & 2) == 0)
00440a73        report_errorf("List remove")
00440a80        if ((list_flags_12.b & 0x40) == 0)
00440a91        struct SubSpeedUp* list_next_6 = game->speedup_pickup.list_next
00440a96        if (list_next_6 != 0)
00440a98        int16_t list_prev_11 = (game->speedup_pickup.list_prev).w
00440a9b        list_next_6->list_prev.b = list_prev_11.b
00440a9b        list_next_6->list_prev:1.b = list_prev_11:1.b
00440a9e        struct SubSpeedUp* list_prev_6 = game->speedup_pickup.list_prev
00440aa3        if (list_prev_6 == 0)
00440ab0        edx_11->first = game->speedup_pickup.list_next
00440aa8        list_prev_6->list_next = game->speedup_pickup.list_next
00440ab6        game->speedup_pickup.list_next = edx_11->free_top
00440ab9        edx_11->free_top = &game->speedup_pickup
00440abc        uint32_t list_flags_13 = game->speedup_pickup.list_flags
00440abf        list_flags_13:1.b &= 0xfd
00440ac2        game->speedup_pickup.list_flags = list_flags_13
00440a87        report_errorf("List remove NEXTBOD")
00440ac5        game->speedup_pickup.state = TRACK_PICKUP_STATE_INACTIVE
00440ad4        if (((game->jetpack_pickup.bod.list_flags).w:1.b & 2) != 0)
00440adc        uint16_t list_flags_14 = (game->jetpack_pickup.bod.list_flags).w
00440ae8        struct BodList* edx_15 = &g_game_base->active_bod_list
00440af1        if ((list_flags_14:1.b & 2) == 0)
00440af8        report_errorf("List remove")
00440b05        if ((list_flags_14.b & 0x40) == 0)
00440b16        struct BodNode* list_next_7 = game->jetpack_pickup.bod.list_next
00440b1b        if (list_next_7 != 0)
00440b1d        int16_t list_prev_12 = (game->jetpack_pickup.bod.list_prev).w
00440b20        list_next_7->list_prev.b = list_prev_12.b
00440b20        list_next_7->list_prev:1.b = list_prev_12:1.b
00440b23        struct BodNode* list_prev_7 = game->jetpack_pickup.bod.list_prev
00440b28        if (list_prev_7 == 0)
00440b35        edx_15->first = game->jetpack_pickup.bod.list_next
00440b2d        list_prev_7->list_next = game->jetpack_pickup.bod.list_next
00440b3b        game->jetpack_pickup.bod.list_next = edx_15->free_top
00440b3e        edx_15->free_top = &game->jetpack_pickup
00440b41        uint32_t list_flags_15 = game->jetpack_pickup.bod.list_flags
00440b44        list_flags_15:1.b &= 0xfd
00440b47        game->jetpack_pickup.bod.list_flags = list_flags_15
00440b0c        report_errorf("List remove NEXTBOD")
00440b4a        game->jetpack_pickup.state = TRACK_PICKUP_STATE_INACTIVE
00440b50        struct BodNode** esi_4 = &game->garbage_hazards.slots[0].body.bod.bod.list_next
00440b56        int32_t i_8 = 0x32
00440bd6        int32_t i_2
00440b61        if ((((esi_4 - 0x359150)->garbage_hazards.slots[0].body.bod.bod.list_flags).w:1.b & 2) != 0)
00440b63        (esi_4 - 0x359150)->garbage_hazards.slots[0].state = 0
00440b6c        uint16_t list_flags_4 = ((esi_4 - 0x359150)->garbage_hazards.slots[0].body.bod.bod.list_flags).w
00440b72        struct BodList* ecx_10 = &g_game_base->active_bod_list
00440b78        if ((list_flags_4:1.b & 2) == 0)
00440b7f        report_errorf("List remove")
00440b8b        if ((list_flags_4.b & 0x40) == 0)
00440b9c        struct BodNode* list_next_2 = (esi_4 - 0x359150)->garbage_hazards.slots[0].body.bod.bod.list_next
00440ba0        if (list_next_2 != 0)
00440ba5        list_next_2->list_prev = (esi_4 - 0x359150)->garbage_hazards.slots[0].body.bod.bod.list_prev
00440ba8        struct BodNode* list_prev_2 = (esi_4 - 0x359150)->garbage_hazards.slots[0].body.bod.bod.list_prev
00440bad        if (list_prev_2 == 0)
00440bb8        ecx_10->first = (esi_4 - 0x359150)->garbage_hazards.slots[0].body.bod.bod.list_next
00440bb1        list_prev_2->list_next = (esi_4 - 0x359150)->garbage_hazards.slots[0].body.bod.bod.list_next
00440bbb        struct BodNode* edx_23
00440bbb        edx_23.b = ecx_10->free_top.b
00440bbb        edx_23:1.b = ecx_10->free_top:1.b
00440bc1        (esi_4 - 0x359150)->garbage_hazards.slots[0].body.bod.bod.list_next = edx_23
00440bc3        ecx_10->free_top.b = (esi_4.w - 0xc).b
00440bc3        ecx_10->free_top:1.b = (esi_4.w - 0xc):1.b
00440bc6        uint32_t list_flags_5 = (esi_4 - 0x359150)->garbage_hazards.slots[0].body.bod.bod.list_flags
00440bc9        list_flags_5:1.b &= 0xfd
00440bcc        (esi_4 - 0x359150)->garbage_hazards.slots[0].body.bod.bod.list_flags = list_flags_5
00440b92        report_errorf("List remove NEXTBOD")
00440bcf        esi_4 = &esi_4[0x31]
00440bd5        i_2 = i_8
00440bd5        i_8 -= 1
00440bd6        do while (i_2 != 1)
00440bd8        struct BodNode** esi_5 = &game->slug_hazards.slots[0].body.bod.bod.list_next
00440bde        int32_t i_9 = 8
00440c5e        int32_t i_3
00440be9        if ((((esi_5 - 0x3563ac)->slug_hazards.slots[0].body.bod.bod.list_flags).w:1.b & 2) != 0)
00440beb        (esi_5 - 0x3563ac)->slug_hazards.slots[0].state = 0
00440bf4        uint16_t list_flags_6 = ((esi_5 - 0x3563ac)->slug_hazards.slots[0].body.bod.bod.list_flags).w
00440bf7        struct BodList* ecx_12 = &g_game_base->active_bod_list
00440c00        if ((list_flags_6:1.b & 2) == 0)
00440c07        report_errorf("List remove")
00440c13        if ((list_flags_6.b & 0x40) == 0)
00440c24        struct BodNode* list_next_3 = (esi_5 - 0x3563ac)->slug_hazards.slots[0].body.bod.bod.list_next
00440c28        if (list_next_3 != 0)
00440c2d        list_next_3->list_prev = (esi_5 - 0x3563ac)->slug_hazards.slots[0].body.bod.bod.list_prev
00440c30        struct BodNode* list_prev_3 = (esi_5 - 0x3563ac)->slug_hazards.slots[0].body.bod.bod.list_prev
00440c35        if (list_prev_3 == 0)
00440c40        ecx_12->first = (esi_5 - 0x3563ac)->slug_hazards.slots[0].body.bod.bod.list_next
00440c39        list_prev_3->list_next = (esi_5 - 0x3563ac)->slug_hazards.slots[0].body.bod.bod.list_next
00440c43        struct BodNode* edx_28
00440c43        edx_28.b = ecx_12->free_top.b
00440c43        edx_28:1.b = ecx_12->free_top:1.b
00440c49        (esi_5 - 0x3563ac)->slug_hazards.slots[0].body.bod.bod.list_next = edx_28
00440c4b        ecx_12->free_top.b = (esi_5.w - 0xc).b
00440c4b        ecx_12->free_top:1.b = (esi_5.w - 0xc):1.b
00440c4e        uint32_t list_flags_7 = (esi_5 - 0x3563ac)->slug_hazards.slots[0].body.bod.bod.list_flags
00440c51        list_flags_7:1.b &= 0xfd
00440c54        (esi_5 - 0x3563ac)->slug_hazards.slots[0].body.bod.bod.list_flags = list_flags_7
00440c1a        report_errorf("List remove NEXTBOD")
00440c57        esi_5 = &esi_5[0x3b]
00440c5d        i_3 = i_9
00440c5d        i_9 -= 1
00440c5e        do while (i_3 != 1)
00440c60        struct BodNode** esi_6 = &game->ring_effects.slots[0].bod.list_next
00440c66        int32_t i_10 = 2
00440ce3        int32_t i_4
00440c6e        if ((esi_6 - 0x35b798)->ring_effects.slots[0].state != SUB_RING_STATE_INACTIVE)
00440c76        uint16_t list_flags_8 = ((esi_6 - 0x35b798)->ring_effects.slots[0].bod.list_flags).w
00440c79        struct BodList* ecx_14 = &g_game_base->active_bod_list
00440c82        if ((list_flags_8:1.b & 2) == 0)
00440c89        report_errorf("List remove")
00440c95        if ((list_flags_8.b & 0x40) == 0)
00440ca6        struct BodNode* list_next_4 = (esi_6 - 0x35b798)->ring_effects.slots[0].bod.list_next
00440caa        if (list_next_4 != 0)
00440caf        list_next_4->list_prev = (esi_6 - 0x35b798)->ring_effects.slots[0].bod.list_prev
00440cb2        struct BodNode* list_prev_4 = (esi_6 - 0x35b798)->ring_effects.slots[0].bod.list_prev
00440cb7        if (list_prev_4 == 0)
00440cc2        ecx_14->first = (esi_6 - 0x35b798)->ring_effects.slots[0].bod.list_next
00440cbb        list_prev_4->list_next = (esi_6 - 0x35b798)->ring_effects.slots[0].bod.list_next
00440cc5        struct BodNode* edx_33
00440cc5        edx_33.b = ecx_14->free_top.b
00440cc5        edx_33:1.b = ecx_14->free_top:1.b
00440ccb        (esi_6 - 0x35b798)->ring_effects.slots[0].bod.list_next = edx_33
00440ccd        ecx_14->free_top.b = (esi_6.w - 0xc).b
00440ccd        ecx_14->free_top:1.b = (esi_6.w - 0xc):1.b
00440cd0        uint32_t list_flags_9 = (esi_6 - 0x35b798)->ring_effects.slots[0].bod.list_flags
00440cd3        list_flags_9:1.b &= 0xfd
00440cd6        (esi_6 - 0x35b798)->ring_effects.slots[0].bod.list_flags = list_flags_9
00440c9c        report_errorf("List remove NEXTBOD")
00440cd9        (esi_6 - 0x35b798)->ring_effects.slots[0].state = SUB_RING_STATE_INACTIVE
00440cdc        esi_6 = &esi_6[0x7e]
00440ce2        i_4 = i_10
00440ce2        i_10 -= 1
00440ce3        do while (i_4 != 1)
00440cee        if (((game->player.body.bod.bod.list_flags).w:1.b & 2) != 0)
00440cfa        uint16_t list_flags_10 = (game->player.body.bod.bod.list_flags).w
00440d06        struct BodList* ecx_16 = &g_game_base->active_bod_list
00440d0f        if ((list_flags_10:1.b & 2) == 0)
00440d16        report_errorf("List remove")
00440d22        if ((list_flags_10.b & 0x40) == 0)
00440d33        struct BodNode* list_next_5 = game->player.body.bod.bod.list_next
00440d38        if (list_next_5 != 0)
00440d3d        list_next_5->list_prev = game->player.body.bod.bod.list_prev
00440d40        struct BodNode* list_prev_5 = game->player.body.bod.bod.list_prev
00440d45        if (list_prev_5 == 0)
00440d52        ecx_16->first = game->player.body.bod.bod.list_next
00440d4a        list_prev_5->list_next = game->player.body.bod.bod.list_next
00440d55        struct BodNode* edx_36
00440d55        edx_36.b = ecx_16->free_top.b
00440d55        edx_36:1.b = ecx_16->free_top:1.b
00440d58        game->player.body.bod.bod.list_next = edx_36
00440d5b        ecx_16->free_top.b = (&game->player).b
00440d5b        ecx_16->free_top:1.b = (&game->player):1.b
00440d5e        uint32_t list_flags_11 = game->player.body.bod.bod.list_flags
00440d61        list_flags_11:1.b &= 0xfd
00440d64        game->player.body.bod.bod.list_flags = list_flags_11
00440d29        report_errorf("List remove NEXTBOD")
00440d73        struct BodList* edx_37 = &g_game_base->active_bod_list
00440d79        uint16_t list_flags_16 = (game->player.presentation.body.bod.bod.list_flags).w
00440d7f        if ((list_flags_16:1.b & 2) == 0)
00440d86        report_errorf("List remove")
00440d93        if ((list_flags_16.b & 0x40) == 0)
00440da4        struct BodNode* list_next_8 = game->player.presentation.body.bod.bod.list_next
00440da9        if (list_next_8 != 0)
00440dab        int16_t list_prev_13 = (game->player.presentation.body.bod.bod.list_prev).w
00440dae        list_next_8->list_prev.b = list_prev_13.b
00440dae        list_next_8->list_prev:1.b = list_prev_13:1.b
00440db1        struct BodNode* list_prev_8 = game->player.presentation.body.bod.bod.list_prev
00440db6        if (list_prev_8 == 0)
00440dc3        edx_37->first = game->player.presentation.body.bod.bod.list_next
00440dbb        list_prev_8->list_next = game->player.presentation.body.bod.bod.list_next
00440dc9        game->player.presentation.body.bod.bod.list_next = edx_37->free_top
00440dcc        edx_37->free_top = &game->player.presentation
00440dcf        uint32_t list_flags_17 = game->player.presentation.body.bod.bod.list_flags
00440dd2        list_flags_17:1.b &= 0xfd
00440dd5        game->player.presentation.body.bod.bod.list_flags = list_flags_17
00440d9a        report_errorf("List remove NEXTBOD")
00440dde        uint16_t list_flags_18 = (game->player.presentation.jetpack_channel.body.bod.bod.list_flags).w
00440dea        struct BodList* edx_39 = &g_game_base->active_bod_list
00440df3        if ((list_flags_18:1.b & 2) == 0)
00440dfa        report_errorf("List remove")
00440e07        if ((list_flags_18.b & 0x40) == 0)
00440e18        struct BodNode* list_next_9 = game->player.presentation.jetpack_channel.body.bod.bod.list_next
00440e1d        if (list_next_9 != 0)
00440e1f        int16_t list_prev_14 = (game->player.presentation.jetpack_channel.body.bod.bod.list_prev).w
00440e22        list_next_9->list_prev.b = list_prev_14.b
00440e22        list_next_9->list_prev:1.b = list_prev_14:1.b
00440e25        struct BodNode* list_prev_9 = game->player.presentation.jetpack_channel.body.bod.bod.list_prev
00440e2a        if (list_prev_9 == 0)
00440e37        edx_39->first = game->player.presentation.jetpack_channel.body.bod.bod.list_next
00440e2f        list_prev_9->list_next = game->player.presentation.jetpack_channel.body.bod.bod.list_next
00440e3d        game->player.presentation.jetpack_channel.body.bod.bod.list_next = edx_39->free_top
00440e40        edx_39->free_top = &game->player.presentation.jetpack_channel
00440e43        uint32_t list_flags_19 = game->player.presentation.jetpack_channel.body.bod.bod.list_flags
00440e46        list_flags_19:1.b &= 0xfd
00440e49        game->player.presentation.jetpack_channel.body.bod.bod.list_flags = list_flags_19
00440e0e        report_errorf("List remove NEXTBOD")
00440e52        uint16_t list_flags_20 = (game->player.presentation.weapon_channels[0].body.bod.bod.list_flags).w
00440e5e        struct BodList* edx_41 = &g_game_base->active_bod_list
00440e67        if ((list_flags_20:1.b & 2) == 0)
00440e6e        report_errorf("List remove")
00440e7b        if ((list_flags_20.b & 0x40) == 0)
00440e8c        struct BodNode* list_next_10 = game->player.presentation.weapon_channels[0].body.bod.bod.list_next
00440e91        if (list_next_10 != 0)
00440e93        int16_t list_prev_15 = (game->player.presentation.weapon_channels[0].body.bod.bod.list_prev).w
00440e96        list_next_10->list_prev.b = list_prev_15.b
00440e96        list_next_10->list_prev:1.b = list_prev_15:1.b
00440e99        struct BodNode* list_prev_10 = game->player.presentation.weapon_channels[0].body.bod.bod.list_prev
00440e9e        if (list_prev_10 == 0)
00440eab        edx_41->first = game->player.presentation.weapon_channels[0].body.bod.bod.list_next
00440ea3        list_prev_10->list_next = game->player.presentation.weapon_channels[0].body.bod.bod.list_next
00440eb1        game->player.presentation.weapon_channels[0].body.bod.bod.list_next = edx_41->free_top
00440eb4        edx_41->free_top = &game->player.presentation.weapon_channels
00440eb7        uint32_t list_flags_21 = game->player.presentation.weapon_channels[0].body.bod.bod.list_flags
00440eba        list_flags_21:1.b &= 0xfd
00440ebd        game->player.presentation.weapon_channels[0].body.bod.bod.list_flags = list_flags_21
00440e82        report_errorf("List remove NEXTBOD")
00440ed2        recycle_bod_to_free_list(&g_game_base->active_bod_list, &game->player.presentation.weapon_channels[1])
00440eea        recycle_bod_to_free_list(&g_game_base->active_bod_list, &game->player.presentation.weapon_channels[2])
00440f02        recycle_bod_to_free_list(&g_game_base->active_bod_list, &game->player.presentation.invincible_shell)
00440f09        game->player.movement_mode_selector = 0
00440f14        struct GolbShot (* shot)[0xc] = &game->player.golb_shots
00440f1a        int32_t i_11 = 0xc
00440f3a        int32_t i_5
00440f2a        if ((shot - 0x3bbbb4)->player.golb_shots[0].state == 1)
00440f2e        kill_golb(shot)
00440f33        shot = &(*shot)[1]
00440f39        i_5 = i_11
00440f39        i_11 -= 1
00440f3a        do while (i_5 != 1)
00440f49        if (((game->player.click_start.bod.bod.bod.list_flags).w:1.b & 2) != 0)
00440f5d        recycle_bod_to_free_list(&g_game_base->active_bod_list, &game->player.click_start)
00440f62        game->player.click_start.state = CLICK_START_STATE_INACTIVE
00440f71        kill_game_sprites(&g_sprite_manager)
00440f7b        return
