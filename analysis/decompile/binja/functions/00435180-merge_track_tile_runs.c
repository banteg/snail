/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: merge_track_tile_runs @ 0x435180 */

00435185        struct Game* game_1 = game
00435187        int32_t i = 0
00435189        struct Game* game_2 = game_1
00435192        if (game_1->runtime_row_count s> 0)
00435194        void* __offset(Game, 0x3bfb08) eax_1 = &game_1->__offset(0x3bfb08).d
0043519a        int32_t j_1 = 8
004351ae        int32_t j
0043519f        int32_t ebp_1 = (eax_1 - 0x3bfb08)->__offset(0x3bfb08).d
004351a1        eax_1 += 0x54
004351aa        j = j_1
004351aa        j_1 -= 1
004351ab        (eax_1 - 0x3bfb08)->__offset(0x3bfab4).d = ebp_1 | 0x6000
004351ae        do while (j != 1)
004351b3        i += 1
004351b6        do while (i s< game_1->runtime_row_count)
004351b8        int32_t runtime_row_count = game_1->runtime_row_count
004351bb        int32_t var_10 = 0
004351c5        if (runtime_row_count s> 0)
004351d3        void* __offset(Game, 0x5ccb7c) var_4_1 = &game_1->__offset(0x5ccb7c).d
004351d7        void* __offset(Game, 0x3bfb08) ebx_1 = &game_1->__offset(0x3bfb08).d
004353d4        bool cond:3_1
004351dd        int32_t i_2 = 0
004351df        int32_t i_6 = 0
004351ee        while (true)
004351ee        char eax_3 = is_slide_cache_tile_family(ebx_1 - 0x40)
004351f5        int16_t eax_4
004351f5        if (eax_3 != 0)
004351fb        eax_4 = ((ebx_1 - 0x3bfb08)->__offset(0x3bfb08).d).w
00435208        if (eax_3 == 0 || (eax_4:1.b & 0x80) != 0 || (eax_4.b & 0x40) != 0)
004352c9        int16_t eax_10
004352c9        if (is_floor_cache_tile_family(ebx_1 - 0x40).b == 0)
004353e2        label_4353e2:
004353e2        eax_10.b = (ebx_1 + 0xf8)->:0x3bfb04.b
004353e5        void* __offset(Game, 0x3bfb04) edx_5 = ebx_1 - 4
004353ea        if (eax_10.b == 0xe)
004353f2        int32_t esi_4 = 0
004353f4        int32_t eax_20
004353f4        eax_20:1.b = (ebx_1 - 0x3bfb08)->__offset(0x3bfb08).d:1.b & 0xf1
004353f7        eax_20:1.b |= 1
004353fd        (ebx_1 - 0x3bfb08)->__offset(0x3bfb08).d = eax_20
004353ff        if (i_2 s< 8)
00435401        int32_t i_7 = i_2
00435406        while ((edx_5 - 0x3bfb04)->:0x3bfb04.b == 0xe)
00435416        if ((eax_20 & 0x4000) != 0x4000)
00435416        break
00435418        eax_20:1.b &= 0xf1
0043541b        edx_5 += 0x54
0043541e        eax_20:1.b |= 1
00435421        esi_4 += 1
00435422        i_7 += 1
00435423        (ebx_1 - 0x3bfb08)->__offset(0x3bfb08).d = eax_20
00435428        if (i_7 s>= 8)
00435428        break
0043542d        if (esi_4 s> 1)
0043544d        set_bod_object(ebx_1 - 0x40, *(data_4df904 + esi_4 * 0x38 + 0x445bc))
00435459        int32_t edx_7
00435459        edx_7:1.b = (ebx_1 - 0x3bfb08)->__offset(0x3bfb08).d:1.b & 0xf0
00435461        int32_t i_10 = esi_4 - 1
00435464        (ebx_1 - 0x3bfb08)->__offset(0x3bfb08).d = (esi_4 & 0xf) << 8 | edx_7
00435466        if (i_10 s> 0)
00435485        void* eax_25 = &game_2->_pad_00[(i_10 + (var_10 << 3) + i_2) * 0x54 + 0x3bfb08]
004354a5        int32_t i_1
0043548c        int32_t ecx_33 = *(eax_25 - 0x3c)
0043548f        eax_25 -= 0x54
00435495        *(eax_25 + 0x18) = ecx_33 & 0xffffffdf
004354a1        i_1 = i_10
004354a1        i_10 -= 1
004354a2        *(eax_25 + 0x54) &= 0xffff9fff
004354a5        do while (i_1 != 1)
004354b2        if (eax_10.b == 0 || eax_10.b == 0x23)
004354ba        int32_t eax_26
004354ba        eax_26:1.b = (ebx_1 - 0x3bfb08)->__offset(0x3bfb08).d:1.b & 0xdf
004354bd        (ebx_1 - 0x3bfb08)->__offset(0x3bfb08).d = eax_26
004354c5        if (game_1->level_mode != 2)
004354df        eax_26:1.b &= 0xbf
004354e2        (ebx_1 - 0x3bfb08)->__offset(0x3bfb08).d = eax_26
004354d5        set_bod_object(ebx_1 - 0x40, *(data_4df904 + 0x44124))
004352cf        eax_10 = ((ebx_1 - 0x3bfb08)->__offset(0x3bfb08).d).w
004352dc        if ((eax_10:1.b & 0x80) != 0 || (eax_10.b & 0x40) != 0)
004352d4        goto label_4353e2
004352e2        int32_t esi_1 = 0
004352e7        if (i_2 s< 8)
004352ed        void* __offset(Game, 0x3bfb08) edi_4 = ebx_1
004352f9        if (is_floor_cache_tile_family(edi_4 - 0x40) == 0)
004352f9        break
004352fb        int16_t eax_12 = ((edi_4 - 0x3bfb08)->__offset(0x3bfb08).d).w
00435300        if ((eax_12:1.b & 0x80) != 0)
00435300        break
00435305        if ((eax_12:1.b & 0x40) == 0)
00435305        break
00435309        if ((eax_12.b & 0x60) != 0)
00435309        break
0043530b        esi_1 += 1
0043530c        edi_4 += 0x54
0043530f        i_2 += 1
00435313        do while (i_2 s< 8)
00435318        if (esi_1 s> 1)
00435334        set_bod_object(ebx_1 - 0x40, *(data_4df904 + esi_1 * 0x38 + 0x44afc))
00435339        int32_t i_9 = esi_1 - 1
0043533c        if (i_9 s> 0)
0043535b        void* eax_17 = &game_2->_pad_00[(i_9 + (var_10 << 3) + i_6) * 0x54 + 0x3bfb08]
0043537b        int32_t i_3
00435362        int32_t ebp_3 = *(eax_17 - 0x3c)
00435365        eax_17 -= 0x54
0043536b        *(eax_17 + 0x18) = ebp_3 & 0xffffffdf
00435377        i_3 = i_9
00435377        i_9 -= 1
00435378        *(eax_17 + 0x54) &= 0xffff9fff
0043537b        do while (i_3 != 1)
0043537d        i_2 = i_6
0043520e        int32_t esi = 0
00435213        if (i_2 s< 8)
00435219        int32_t i_4 = i_2
0043521b        void* __offset(Game, 0x3bfb04) ecx_2 = ebx_1 - 4
0043521e        eax_4.b = (ecx_2 - 0x3bfb04)->:0x3bfb04.b
00435232        if (eax_4.b != 1 && eax_4.b != 0x15 && eax_4.b != 0x1b && eax_4.b != 0x21 && eax_4.b != 0x22)
00435232        break
00435234        eax_4.b = (ecx_2 - 0x3bfb04)->:0x3bfb08.b
00435234        eax_4:1.b = (ecx_2 - 0x3bfb04)->:0x3bfb09.b
00435234        eax_4:2.b = (ecx_2 - 0x3bfb04)->:0x3bfb0a.b
00435234        eax_4:3.b = (ecx_2 - 0x3bfb04)->:0x3bfb0b.b
0043523a        if ((eax_4:1.b & 0x80) != 0)
0043523a        break
0043523f        if ((eax_4:1.b & 0x40) == 0)
0043523f        break
00435243        if ((eax_4.b & 0x60) != 0)
00435243        break
00435245        esi += 1
00435246        ecx_2 += 0x54
00435249        i_4 += 1
0043524d        do while (i_4 s< 8)
00435252        if (esi s> 1)
00435272        set_bod_object(ebx_1 - 0x40, *(data_4df904 + esi * 0x38 + 0x4477c))
00435277        int32_t i_8 = esi - 1
0043527a        if (i_8 s> 0)
00435299        void* eax_9 = &game_2->_pad_00[(i_8 + (var_10 << 3) + i_2) * 0x54 + 0x3bfb08]
004352b9        int32_t i_5
004352a0        int32_t ecx_9 = *(eax_9 - 0x3c)
004352a3        eax_9 -= 0x54
004352a9        *(eax_9 + 0x18) = ecx_9 & 0xffffffdf
004352b5        i_5 = i_8
004352b5        i_8 -= 1
004352b6        *(eax_9 + 0x54) &= 0xffff9fff
004352b9        do while (i_5 != 1)
0043538c        if (((var_4_1 - 0x5ccb7c)->:0x5ccac8.b & 4) != 0)
00435397        (ebx_1 - 0x3bfb08)->__offset(0x3bfacc).d &= 0xfffffddd
0043539c        int32_t edx_4
0043539c        edx_4:1.b = (ebx_1 - 0x3bfb08)->__offset(0x3bfb08).d:1.b & 0xbf
0043539f        (ebx_1 - 0x3bfb08)->__offset(0x3bfb08).d = edx_4
004353a6        (var_4_1 - 0x5ccb7c)->__offset(0x5ccb7c).d &= 0xffffffdf
004353a8        i_2 += 1
004353a9        ebx_1 += 0x54
004353af        i_6 = i_2
004353b3        if (i_2 s>= 8)
004353b3        break
004351e5        game_1 = game_2
004353b9        game_1 = game_2
004353c7        var_4_1 += 0xf4
004353cb        runtime_row_count = game_1->runtime_row_count
004353ce        cond:3_1 = var_10 + 1 s< runtime_row_count
004353d0        var_10 += 1
004353d4        do while (cond:3_1)
004353e1        return runtime_row_count
