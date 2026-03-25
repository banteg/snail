/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_track_jetpack_pickup @ 0x43d890 */

0043d893        uint32_t* eax = &game->jetpack_pickup.state
0043d89d        int32_t edx = 0
0043d8a1        while ((eax - 0x355e9c)->jetpack_pickup.state != 0)
0043d8a3        edx += 1
0043d8a4        eax = &eax[0x67]
0043d8ac        if (edx s>= 1)
0043d8b3        return eax
0043d8cd        void* esi = &game->_pad_00[edx * 0x19c]
0043d8d0        *(esi + 0x355e9c) = 1
0043d8da        *(esi + 0x355ea0) = player
0043d8e9        float world_x = cell->world_x
0043d8ec        float world_z = cell->world_z
0043d8fb        float world_x_1 = world_x
0043d8ff        float var_8 = fconvert.s(fconvert.t(cell->floor_height) + fconvert.t(1.5f))
0043d907        *(esi + 0x355e74) = world_x
0043d90d        *(esi + 0x355e78) = var_8
0043d910        *(esi + 0x355e7c) = world_z
0043d916        int32_t eax_8 = cell->lane_bits & 7
0043d92b        if (eax_8 == 3 && cell->__offset(0xffffffffffffffe8).b == 0xe && cell->__offset(0xe4).b == 0xe)
0043d951        *(esi + 0x355e74) = fconvert.s(fconvert.t(*(esi + 0x355e74)) + fconvert.t(0.5f))
0043d947        if (eax_8 == 4 && cell->__offset(0xffffffffffffff94).b == 0xe && cell->__offset(0x90).b == 0xe)
0043d951        *(esi + 0x355e74) = fconvert.s(fconvert.t(*(esi + 0x355e74)) - fconvert.t(0.5f))
0043d962        if (((*(esi + 0x355e68)).w:1.b & 2) == 0)
0043d973        void* edx_3 = data_4df904
0043d97f        void* edx_4 = *(edx_3 + 0x5ac)
0043d987        if (edx_4 != 0)
0043d995        *(edx_4 + 8) = esi + 0x355e64
0043d998        void* edx_5 = *(edx_3 + 0x5ac)
0043d99d        *(*(edx_5 + 8) + 0xc) = edx_5
0043d9a4        void* edx_7 = *(*(edx_3 + 0x5ac) + 8)
0043d9a7        *(edx_3 + 0x5ac) = edx_7
0043d9a9        *(edx_7 + 8) = 0
0043d989        *(edx_3 + 0x5ac) = esi + 0x355e64
0043d98b        *(esi + 0x355e6c) = 0
0043d990        *(*(edx_3 + 0x5ac) + 0xc) = 0
0043d9af        int32_t eax_12
0043d9af        eax_12:1.b = (*(esi + 0x355e68)):1.b | 2
0043d9b2        *(esi + 0x355e68) = eax_12
0043d969        report_errorf("List ADD")
0043d9cb        int32_t* eax_14 = allocate_sprite(&data_790f30, player->player_slot, 0x7c, 0xffffffff, 0xffffffff)
0043d9d0        *(esi + 0x355ec8) = eax_14
0043d9d9        int32_t ecx_3
0043d9d9        ecx_3:1.b = eax_14[1]:1.b | 8
0043d9dc        eax_14[1] = ecx_3
0043d9e5        *(*(esi + 0x355ec8) + 0x78) = 0
0043d9ee        *(*(esi + 0x355ec8) + 0x68) = 0
0043d9fc        *(*(esi + 0x355ec8) + 0x6c) = 0
0043da05        *(*(esi + 0x355ec8) + 0x60) = 0x3fc00000
0043da0e        *(*(esi + 0x355ec8) + 0x64) = 0x3fc00000
0043da19        float* edx_11 = *(esi + 0x355ec8) + 0x48
0043da1c        *edx_11 = *(esi + 0x355e74)
0043da21        edx_11[1] = *(esi + 0x355e78)
0043da27        edx_11[2] = *(esi + 0x355e7c)
0043da2a        *(esi + 0x355ecc) = cell
0043da30        *(esi + 0x355ed0) = 0
0043da3c        int16_t x87control
0043da3c        int32_t eax_18 = __ftol(x87control, fconvert.t(*(esi + 0x355e7c)))
0043da45        if ((eax_18.b & 1) == 0)
0043da5f        *(esi + 0x355ed0) = 0x3f000000
0043da69        __builtin_strncpy(esi + 0x355ed4, "!\rR<", 4)
0043da78        return eax_18
0043da47        *(esi + 0x355ed0) = 0
0043da4d        __builtin_strncpy(esi + 0x355ed4, "!\rR<", 4)
0043da5c        return eax_18
