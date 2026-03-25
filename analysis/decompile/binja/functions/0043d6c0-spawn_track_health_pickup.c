/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_track_health_pickup @ 0x43d6c0 */

0043d6c8        int32_t ebx = 0
0043d6ca        uint32_t* eax = &game->health_pickups[0].state
0043d6d3        while ((eax - 0x356038)->health_pickups[0].state != 0)
0043d6d5        ebx += 1
0043d6d6        eax = &eax[0x1d]
0043d6dc        if (ebx s>= 8)
0043d6e2        return eax
0043d6ef        struct TrackRowCell* cell_1 = cell
0043d6fc        void* esi = &game->_pad_00[ebx * 0x74]
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
0043d762        void* edx_2 = data_4df904
0043d76e        void* edx_3 = *(edx_2 + 0x5ac)
0043d776        if (edx_3 != 0)
0043d784        *(edx_3 + 8) = esi + 0x356000
0043d787        void* edx_4 = *(edx_2 + 0x5ac)
0043d78c        *(*(edx_4 + 8) + 0xc) = edx_4
0043d791        cell_1 = cell
0043d795        void* edx_6 = *(*(edx_2 + 0x5ac) + 8)
0043d798        *(edx_2 + 0x5ac) = edx_6
0043d79a        *(edx_6 + 8) = 0
0043d778        *(edx_2 + 0x5ac) = esi + 0x356000
0043d77a        *(esi + 0x356008) = edx_3
0043d77f        *(*(edx_2 + 0x5ac) + 0xc) = edx_3
0043d7a4        int32_t ecx_4
0043d7a4        ecx_4:1.b = (*(esi + 0x356004)):1.b | 2
0043d7a7        *(esi + 0x356004) = ecx_4
0043d758        report_errorf("List ADD")
0043d7c0        int32_t* eax_7 = allocate_sprite(&data_790f30, player->__offset(0x380).d, 0x39, 0xffffffff, 0xffffffff)
0043d7c5        *(esi + 0x356064) = eax_7
0043d7ce        int32_t ecx_6
0043d7ce        ecx_6:1.b = eax_7[1]:1.b | 8
0043d7d1        eax_7[1] = ecx_6
0043d7dc        *(*(esi + 0x356064) + 0x78) = 0
0043d7e5        *(*(esi + 0x356064) + 0x68) = 0
0043d7f3        *(*(esi + 0x356064) + 0x6c) = 0
0043d7fc        *(*(esi + 0x356064) + 0x60) = 0x3f19999a
0043d805        *(*(esi + 0x356064) + 0x64) = 0x3f19999a
0043d810        float* ecx_9 = *(esi + 0x356064) + 0x48
0043d813        *ecx_9 = *(esi + 0x356010)
0043d818        ecx_9[1] = *(esi + 0x356014)
0043d81e        ecx_9[2] = *(esi + 0x356018)
0043d821        *(esi + 0x356068) = cell_1
0043d827        *(esi + 0x35606c) = 0
0043d83a        int16_t x87control
0043d83a        if ((__ftol(x87control, fconvert.t(*(esi + 0x356018))) & 1) == 0)
0043d848        *(esi + 0x35606c) = 0x3f000000
0043d83c        *(esi + 0x35606c) = 0
0043d866        int32_t eax_10 = (ebx + 0x75cc) * 7
0043d86c        *(game + ((ebx + 0x75cc + (eax_10 << 2)) << 2)) = 0x3c520d21
0043d876        return eax_10
