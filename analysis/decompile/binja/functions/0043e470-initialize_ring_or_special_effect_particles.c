/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_ring_or_special_effect_particles @ 0x43e470 */

0043e47b        int32_t i_1 = 0
0043e47f        *(arg1 + 0x80) = 1
0043e489        *(arg1 + 0x1e8) = 0
0043e492        int32_t* esi = arg1 + 0x90
0043e677        int32_t i
0043e4a9        esi[5] = fconvert.s(float.t(i_1) * fconvert.t(0.628318548f))
0043e4bb        esi[6] = fconvert.s(fconvert.t(*(*(arg1 + 0x1d0) + 0x38)) * fconvert.t(0.104719758f))
0043e4be        esi[1] = arg1
0043e4c3        esi[2] = *(arg1 + 0x68)
0043e4c8        esi[3] = *(arg1 + 0x6c)
0043e4ce        esi[4] = *(arg1 + 0x70)
0043e4d1        esi[7] = 0x3f99999a
0043e4d8        int32_t eax_4 = *(arg1 + 0x88)
0043e4f3        if (eax_4 == 4 || eax_4 == 5 || eax_4 == 8)
0043e59f        *esi = allocate_sprite(&data_790f30, *(*(arg1 + 0x84) + 0x380), 0x87, 0xffffffff, 0xffffffff)
0043e5a1        *(arg1 + 0x1ec) = 0x88
0043e5ad        *(*esi + 0x28) = 9
0043e501        if (eax_4 == 2 || eax_4 == 6)
0043e568        *esi = allocate_sprite(&data_790f30, *(*(arg1 + 0x84) + 0x380), 0x83, 0xffffffff, 0xffffffff)
0043e56a        *(arg1 + 0x1ec) = 0x84
0043e576        *(*esi + 0x28) = 0xd
0043e50b        if (eax_4 == 3 || eax_4 == 7)
0043e531        *esi = allocate_sprite(&data_790f30, *(*(arg1 + 0x84) + 0x380), 0x85, 0xffffffff, 0xffffffff)
0043e533        *(arg1 + 0x1ec) = 0x86
0043e53f        *(*esi + 0x28) = 0xd
0043e5cc        struct Color4f color
0043e5cc        struct Color4f* eax_11 = set_color_rgba(&color, 1f, 1f, 1f, 0.800000012f)
0043e5d5        float* edx_6 = *esi + 0x2c
0043e5d8        *edx_6 = eax_11->r
0043e5dd        edx_6[1] = eax_11->g
0043e5e3        edx_6[2] = eax_11->b
0043e5e9        edx_6[3] = eax_11->a
0043e5ec        void* eax_13 = *esi
0043e5f1        int32_t ecx_9
0043e5f1        ecx_9:1.b = (*(eax_13 + 4)):1.b | 8
0043e5f4        *(eax_13 + 4) = ecx_9
0043e5fb        *(*esi + 0x68) = 0
0043e600        *(*esi + 0x6c) = 0
0043e605        *(*esi + 0x78) = 0
0043e60f        *(*esi + 0x60) = 0x3f3851ec
0043e614        *(*esi + 0x64) = 0x3f3851ec
0043e61b        int32_t* edx_10 = *esi + 0x48
0043e620        *edx_10 = *(arg1 + 0x68)
0043e625        edx_10[1] = *(arg1 + 0x6c)
0043e62b        edx_10[2] = *(arg1 + 0x70)
0043e633        *(*esi + 0x7c) = esi[5]
0043e636        int32_t eax_16 = *(arg1 + 0x88)
0043e644        if (eax_16 == 3 || eax_16 == 6)
0043e657        *(*esi + 0x80) = 0
0043e64d        *(*esi + 0x80) = fconvert.s(fneg(fconvert.t(esi[6])))
0043e663        update_ring_or_special_effect_particle(esi)
0043e66c        esi = &esi[8]
0043e66f        i = i_1 + 1
0043e673        i_1 = i
0043e677        do while (i s< 0xa)
0043e684        return i
