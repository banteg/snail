/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_subgoldy_ghost @ 0x43d230 */

0043d24c        int32_t* eax = allocate_sprite(&g_sprite_manager, arg2, 0x9f, 0xffffffff, 0xffffffff)
0043d251        *(arg1 + 0x98) = eax
0043d25a        int32_t ecx
0043d25a        ecx:1.b = eax[1]:1.b | 8
0043d25f        eax[1] = ecx
0043d272        *(*(arg1 + 0x98) + 0x68) = 0
0043d285        *(*(arg1 + 0x98) + 0x6c) = 0
0043d292        *(*(arg1 + 0x98) + 0x78) = 0
0043d295        struct Color4f color
0043d295        struct Color4f* eax_2 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0043d2a2        float* ecx_4 = *(arg1 + 0x98) + 0x2c
0043d2ae        *ecx_4 = eax_2->r
0043d2b9        ecx_4[1] = eax_2->g
0043d2bf        ecx_4[2] = eax_2->b
0043d2c5        ecx_4[3] = eax_2->a
0043d2ce        *(*(arg1 + 0x98) + 0x60) = 0x3f000000
0043d2d7        *(*(arg1 + 0x98) + 0x64) = 0x3f000000
0043d2e0        *(*(arg1 + 0x98) + 0x48) = 0x40900000
0043d2ed        *(*(arg1 + 0x98) + 0x4c) = 0x3f800000
0043d2ff        *(*(arg1 + 0x98) + 0x50) = 0
0043d302        int32_t* eax_5 = allocate_sprite(&g_sprite_manager, arg2, 0x9f, 0xffffffff, 0xffffffff)
0043d307        *(arg1 + 0x9c) = eax_5
0043d310        int32_t ecx_7
0043d310        ecx_7:1.b = eax_5[1]:1.b | 8
0043d318        eax_5[1] = ecx_7
0043d32b        *(*(arg1 + 0x9c) + 0x68) = 0
0043d339        *(*(arg1 + 0x9c) + 0x6c) = 0
0043d346        *(*(arg1 + 0x9c) + 0x78) = 0
0043d349        struct Color4f* eax_7 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0043d356        float* ecx_11 = *(arg1 + 0x9c) + 0x2c
0043d359        *ecx_11 = eax_7->r
0043d35e        ecx_11[1] = eax_7->g
0043d364        ecx_11[2] = eax_7->b
0043d36a        ecx_11[3] = eax_7->a
0043d373        *(*(arg1 + 0x9c) + 0x60) = 0x3f000000
0043d37c        *(*(arg1 + 0x9c) + 0x64) = 0x3f000000
0043d385        *(*(arg1 + 0x9c) + 0x48) = 0xc0900000
0043d392        *(*(arg1 + 0x9c) + 0x4c) = 0x3f800000
0043d3a4        *(*(arg1 + 0x9c) + 0x50) = 0
0043d3a7        void* eax_10 = *(arg1 + 0x98)
0043d3b3        *(eax_10 + 4) &= 0xffffffbf
0043d3b6        void* esi_1 = *(arg1 + 0x9c)
0043d3bf        int32_t result = *(esi_1 + 4) & 0xffffffbf
0043d3c1        *(esi_1 + 4) = result
0043d3ca        return result
