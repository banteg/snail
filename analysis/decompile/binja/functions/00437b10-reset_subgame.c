/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: reset_subgame @ 0x437b10 */

00437b16        int32_t i_4 = 8
00437b1b        struct TrackPickupOwnerGameView** eax = &game->health_pickups[0].owner_game
00437b2a        int32_t i
00437b21        (eax - 0x356044)->health_pickups[0].state = 0
00437b24        (eax - 0x356044)->health_pickups[0].owner_game = game
00437b26        eax = &eax[0x1d]
00437b29        i = i_4
00437b29        i_4 -= 1
00437b2a        do while (i != 1)
00437b2c        game->speedup_pickup.state = 0
00437b32        game->speedup_pickup.owner_game = game
00437b38        game->jetpack_pickup.state = 0
00437b3e        game->jetpack_pickup.owner_game = game
00437b44        struct Game** eax_1 = &game->garbage_hazards.slots[0].game
00437b4a        int32_t i_5 = 0x32
00437b5d        int32_t i_1
00437b4f        (eax_1 - 0x3591d0)->garbage_hazards.slots[0].state = 0
00437b52        (eax_1 - 0x3591d0)->garbage_hazards.slots[0].game = game
00437b54        (eax_1 - 0x3591d0)->garbage_hazards.slots[0].next_active = nullptr
00437b57        eax_1 = &eax_1[0x31]
00437b5c        i_1 = i_5
00437b5c        i_5 -= 1
00437b5d        do while (i_1 != 1)
00437b5f        struct Game** eax_2 = &game->slug_slots[0].owner_game
00437b65        int32_t i_6 = 8
00437b75        int32_t i_2
00437b6a        (eax_2 - 0x356428)->slug_slots[0].state = 0
00437b6d        (eax_2 - 0x356428)->slug_slots[0].owner_game = game
00437b6f        eax_2 = &eax_2[0x3b]
00437b74        i_2 = i_6
00437b74        i_6 -= 1
00437b75        do while (i_2 != 1)
00437b77        struct RingEffectRateSource** eax_3 = &game->ring_effects.slots[0].rate_source
00437b7d        int32_t i_7 = 2
00437b90        int32_t i_3
00437b82        (eax_3 - 0x35b95c)->ring_effects.slots[0].state = 0
00437b88        (eax_3 - 0x35b95c)->ring_effects.slots[0].rate_source = game
00437b8a        eax_3 = &eax_3[0x7e]
00437b8f        i_3 = i_7
00437b8f        i_7 -= 1
00437b90        do while (i_3 != 1)
00437ba6        if (game->selected_level_record_active != 1 || game->level_mode != game->__offset(0xfd2b3c).d)
00437bec        if (game->subgame_rebuild_selector == 2)
00437bf4        game->__offset(0x3bba48).d = 0
00437bfa        clear_subgoldy_score_buckets(&game->__offset(0x3bb764).d)
00437c05        zero_timer_counters()
00437c0a        game->__offset(0x3bba64).d = 0
00437c10        game->__offset(0x3bba68).d = 0
00437bae        int32_t edx_1 = game->__offset(0xfd2b30).d
00437bb4        int32_t eax_5 = game->__offset(0xfd2b34).d
00437bbc        game->__offset(0x3bba48).d = game->__offset(0xfd2b14).d
00437bd3        game->__offset(0x3bba64).d = edx_1
00437bd9        __builtin_memcpy(&game->stopwatch, &game->__offset(0xfd2b18).d, 0x18)
00437bdc        game->__offset(0x3bba68).d = eax_5
00437c16        game->__offset(0x3bbae0).d = 0
00437c1c        game->_pad_00[0] = 1
00437c20        game->_pad_00[1] = 1
00437c24        game->selected_level_record_active = 0
00437c2a        game->garbage_hazards.active_head = 0
00437c32        return
