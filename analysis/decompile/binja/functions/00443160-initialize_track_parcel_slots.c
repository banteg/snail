/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_track_parcel_slots @ 0x443160 */

00443160        struct SubgameRuntime** eax = &manager->slots[0].owner_subgame
00443164        int32_t i_1 = 0x32
00443182        int32_t i
0044316b        (eax - 0x3c)->slots[0].state = PARCEL_STATE_INACTIVE
0044317a        (eax - 0x3c)->slots[0].owner_subgame = &g_game_base->subgame.scan_reset
0044317c        eax = &eax[0x23]
00443181        i = i_1
00443181        i_1 -= 1
00443182        do while (i != 1)
00443185        return
