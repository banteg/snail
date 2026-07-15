/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: activate_landscape_entry @ 0x418870 */

00418878        int32_t level_mode = g_game_base->subgame.level_mode
00418886        char var_8
00418886        if (level_mode == 7)
00418888        var_8 = 0
00418892        if (level_mode != 1)
004188cb        var_8 = g_runtime_config.landscape_backdrop_variant_selector.b & 1
004188a1        long double x87_r7_2 = float.t(next_math_random_value()) * fconvert.t(3.05175781e-05f)
004188a7        long double temp1_1 = fconvert.t(0.5f)
004188a7        x87_r7_2 - temp1_1
004188b2        if ((((x87_r7_2 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
004188bb        var_8 = 1
004188b4        var_8 = 0
004188d3        int32_t i = 0
004188d5        int32_t i_1 = 0
004188df        void* edi = arg1 + arg2 * 0x124
004188e2        int32_t* esi_1 = arg1 + 4
004188ec        if (*(edi + 0x6b0) != 0xffffffff)
0041890a        struct BodBase* eax_4 = &g_game_base->subgame.landscape_slice_list_head
00418915        if (((*esi_1).w:1.b & 2) == 0)
00418926        esi_1[1] = eax_4
0041892f        esi_1[2] = eax_4->bod.list_next
00418932        eax_4->bod.list_next = &esi_1[-1]
00418935        void* eax_5 = esi_1[2]
0041893a        if (eax_5 != 0)
0041893c        *(eax_5 + 8) = &esi_1[-1]
0041893f        int32_t eax_6 = *esi_1
00418941        eax_6:1.b |= 2
00418944        *esi_1 = eax_6
0041891c        report_errorf("List ADDafter")
00418946        esi_1[0x1f] = 1
0041894d        int32_t eax_7 = *esi_1
0041894f        eax_7.b |= 0x20
00418951        *esi_1 = eax_7
00418972        set_bod_object(&esi_1[-1], g_game_base->directx_loader.cached_x_mesh_slots[*(edi + 0x6b0)].object)
00418977        void* eax_10 = esi_1[8]
00418989        esi_1[0x21] = fconvert.s(fconvert.t(*(eax_10 + 0xb8)) - fconvert.t(*(eax_10 + 0xac)))
0041898f        set_matrix_identity(&esi_1[0xd])
004189a4        esi_1[0x1b] = fconvert.s((float.t(i_1) - fconvert.t(0.5f)) * fconvert.t(esi_1[0x21]))
004189b3        esi_1[0x22] = &g_game_base->subgame.player
004188f5        *esi_1 &= 0xffffffdf
004188fa        set_bod_object(&esi_1[-1], nullptr)
004189b9        i += 1
004189ba        esi_1 = &esi_1[0x24]
004189c3        i_1 = i
004189c7        do while (i s< 0xa)
004189e5        change_backdrop(&g_game_base->backdrop, edi + 0x5a4, var_8)
004189f8        set_border_justify_centre(&g_game_base->border_manager, 0f)
00418a08        uint8_t* result = &g_game_base->unknown_000000[0x14]
00418a0b        int32_t ecx_17 = *(edi + 0x6b4)
00418a0d        (result - 0x14)->unknown_000000[0x14] = ecx_17.b
00418a0d        (result - 0x14)->unknown_000000[0x15] = ecx_17:1.b
00418a0d        (result - 0x14)->unknown_000000[0x16] = ecx_17:2.b
00418a0d        (result - 0x14)->unknown_000000[0x17] = ecx_17:3.b
00418a0f        int32_t edx_5 = *(edi + 0x6b8)
00418a12        (result - 0x14)->unknown_000000[0x18] = edx_5.b
00418a12        (result - 0x14)->unknown_000000[0x19] = edx_5:1.b
00418a12        (result - 0x14)->unknown_000000[0x1a] = edx_5:2.b
00418a12        (result - 0x14)->unknown_000000[0x1b] = edx_5:3.b
00418a15        int32_t ecx_18 = *(edi + 0x6bc)
00418a18        (result - 0x14)->unknown_000000[0x1c] = ecx_18.b
00418a18        (result - 0x14)->unknown_000000[0x1d] = ecx_18:1.b
00418a18        (result - 0x14)->unknown_000000[0x1e] = ecx_18:2.b
00418a18        (result - 0x14)->unknown_000000[0x1f] = ecx_18:3.b
00418a1b        int32_t edx_6 = *(edi + 0x6c0)
00418a20        (result - 0x14)->unknown_000000[0x20] = edx_6.b
00418a20        (result - 0x14)->unknown_000000[0x21] = edx_6:1.b
00418a20        (result - 0x14)->unknown_000000[0x22] = edx_6:2.b
00418a20        (result - 0x14)->unknown_000000[0x23] = edx_6:3.b
00418a27        return result
