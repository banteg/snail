/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_subgoldy_resurrect @ 0x441fd0 */

00441fd3        player->velocity.z = 0f
00441fe7        void* eax
00441fe7        if (*(data_4df904 + 0x24) == 0)
00441fef        long double x87_r7_2 = fconvert.t(player->_pad_78[0x18].d) + fconvert.t(player->_pad_78[0x14].d)
00441ff5        player->_pad_78[0x14].d = fconvert.s(x87_r7_2)
00441ffb        long double temp1_1 = fconvert.t(1f)
00441ffb        x87_r7_2 - temp1_1
00442001        eax.w = (x87_r7_2 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1_1 ? 1 : 0) << 0xe
00442006        if ((eax:1.b & 0x41) == 0)
0044200e        int32_t* ecx_2 = data_4df904 + 0x24
00442014        if (*ecx_2 == 0)
00442018        begin_frontend_fade_out(ecx_2, 0)
0044201d        long double x87_r7_3 = fconvert.t(player->_pad_78[0x14].d)
00442023        long double temp0 = fconvert.t(1f)
00442023        x87_r7_3 - temp0
00442029        eax.w = (x87_r7_3 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp0) ? 1 : 0) << 0xa | (x87_r7_3 == temp0 ? 1 : 0) << 0xe
0044203e        if ((eax:1.b & 0x41) != 0 || *(data_4df904 + 0x24) != 4)
0044203e        return 
0044204c        struct Game* game = player->game
00442052        if (player->_pad_78[8].d == 0)
00442059        if (game->level_mode == 0)
0044205b        player->_pad_4340 -= 1
00442061        void* eax_2 = data_4df904
0044206d        *(eax_2 + 0x1bc) = *(eax_2 + 0x1b8)
00442079        *(data_4df904 + 0x1b8) = 0x1c
00442083        return 
00442084        game->subgame_rebuild_selector = 2
00442096        complete_subgame(player->game, 1)
004420a9        void* eax_4 = data_4df904
004420ae        if (player->game->selected_level_record_persistent != 0)
004420b7        *(eax_4 + 0x1bc) = *(eax_4 + 0x1b8)
004420c2        *(data_4df904 + 0x1b8) = 0x1a
004420cc        return 
004420d3        *(eax_4 + 0x1bc) = *(eax_4 + 0x1b8)
004420e4        void* eax_7 = data_4df904
004420e9        if (player->game->level_mode == 0)
004420eb        int32_t ecx_7
004420eb        ecx_7.b = *(eax_7 + 0x30d)
004420f3        if (ecx_7.b == 0)
004420f5        *(eax_7 + 0x1b8) = 0x1a
00442105        *(data_4df904 + 0x1bc) = 2
0044210f        return 
00442110        *(eax_7 + 0x1b8) = 0x1b
0044211b        return
