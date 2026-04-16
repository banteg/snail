/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: select_track_tile_edge_variants @ 0x435a80 */

00435a83        int32_t result = *(arg1 + 0x54)
00435a87        int32_t i = 0
00435a8f        int32_t i_1 = 0
00435a93        if (result s> 0)
00435a9c        char* esi_1 = arg1 + 0x3bfb04
00435aa7        int32_t j = 0
00435cfc        while (j s< 8)
00435aa9        esi_1[1] = 0
00435ab0        int32_t edx_1
00435ab0        edx_1:1.b = (*(esi_1 + 4)):1.b & 0x7f
00435ab3        *(esi_1 + 4) = edx_1
00435ab6        result.b = *esi_1
00435ae2        if (result.b != 0 && result.b != 0x23 && result.b != 0x1c && result.b != 0x1d && result.b != 0x1e && result.b != 0xe)
00435aea        char eax
00435aea        if (j != 0)
00435af2        eax = is_open_neighbor_tile_family(&esi_1[0xffffff70])
00435af9        if (j == 0 || eax != 0)
00435afb        esi_1[1] |= 8
00435b02        char eax_1
00435b02        if (j != 7)
00435b07        eax_1 = is_open_neighbor_tile_family(&esi_1[0x18])
00435b0e        if (j == 7 || eax_1 != 0)
00435b10        esi_1[1] |= 4
00435b16        char eax_2
00435b16        if (i != 0)
00435b1e        eax_2 = is_open_neighbor_tile_family(&esi_1[0xfffffd24])
00435b25        if (i == 0 || eax_2 != 0)
00435b27        esi_1[1] |= 1
00435b35        char eax_4
00435b35        if (i s< *(arg1 + 0x54) - 1)
00435b3d        eax_4 = is_open_neighbor_tile_family(&esi_1[0x264])
00435b44        if (i s>= *(arg1 + 0x54) - 1 || eax_4 != 0)
00435b46        esi_1[1] |= 2
00435b4c        int32_t eax_5
00435b4c        eax_5.b = esi_1[1]
00435b55        int32_t edx_5
00435b55        if (eax_5 - 5 u<= 5)
00435b55        switch (eax_5)
00435bd0        case 5
00435bd0        *(esi_1 + 4) |= 0x8000
00435bd3        result.b = *esi_1
00435beb        if (result.b == 1 || result.b == 0x14 || result.b == 0x15 || result.b == 0x1b || result.b == 0x21 || result.b == 0x22)
00435cec        set_bod_object(&esi_1[0xffffffc4], *(data_4df904 + 0x44274))
00435bf7        if (result.b != 0x16 && result.b != 0xe && is_ramp_cache_tile_family(&esi_1[0xffffffc4]).b == 0)
00435cec        set_bod_object(&esi_1[0xffffffc4], *(data_4df904 + 0x44434))
00435c98        case 6
00435c98        *(esi_1 + 4) |= 0x8000
00435c9b        result.b = *esi_1
00435cb3        if (result.b == 1 || result.b == 0x14 || result.b == 0x15 || result.b == 0x1b || result.b == 0x21 || result.b == 0x22)
00435ce2        edx_5 = *(data_4df904 + 0x442e4)
00435ce2        goto label_435ce8
00435cbb        if (result.b != 0x16 && result.b != 0xe && is_ramp_cache_tile_family(&esi_1[0xffffffc4]).b == 0)
00435cec        set_bod_object(&esi_1[0xffffffc4], *(data_4df904 + 0x444a4))
00435b67        case 9
00435b67        *(esi_1 + 4) |= 0x8000
00435b6a        result.b = *esi_1
00435b82        if (result.b == 1 || result.b == 0x14 || result.b == 0x15 || result.b == 0x1b || result.b == 0x21 || result.b == 0x22)
00435bc0        edx_5 = *(data_4df904 + 0x4423c)
00435ce8        label_435ce8:
00435cec        set_bod_object(&esi_1[0xffffffc4], edx_5)
00435b8e        if (result.b != 0x16 && result.b != 0xe && is_ramp_cache_tile_family(&esi_1[0xffffffc4]).b == 0)
00435cec        set_bod_object(&esi_1[0xffffffc4], *(data_4df904 + 0x443fc))
00435c39        case 0xa
00435c39        *(esi_1 + 4) |= 0x8000
00435c3c        result.b = *esi_1
00435c54        if (result.b == 1 || result.b == 0x14 || result.b == 0x15 || result.b == 0x1b || result.b == 0x21 || result.b == 0x22)
00435cec        set_bod_object(&esi_1[0xffffffc4], *(data_4df904 + 0x442ac))
00435c60        if (result.b != 0x16 && result.b != 0xe && is_ramp_cache_tile_family(&esi_1[0xffffffc4]).b == 0)
00435cec        set_bod_object(&esi_1[0xffffffc4], *(data_4df904 + 0x4446c))
00435cf1        i = i_1
00435cf5        j += 1
00435cf6        esi_1 = &esi_1[0x54]
00435d02        result = arg1
00435d06        i += 1
00435d07        i_1 = i
00435d0e        do while (i s< *(result + 0x54))
00435d1b        return result
