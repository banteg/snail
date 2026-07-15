/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: add_arcade_high_score @ 0x4176a0 */

004176a0        struct SubHighScore* bank_1 = bank
004176ae        int32_t eax = 0
004176b0        record->route_or_rank_index = level_arg
004176c0        record->high_score_mode_tag = 0
004176c3        __builtin_memcpy(&bank->current_result_record, record, 0x1fac0)
004176cc        int32_t* ecx_1 = &bank->postal_records[0].score
004176d1        while (record->score s<= (ecx_1 - 0xc)->postal_records[0].score)
004176d3        eax += 1
004176d4        ecx_1 = &ecx_1[0x7eb0]
004176dd        if (eax s>= 0xa)
004176e3        return
004176e7        int32_t ebx = 0xa
004176ee        if (eax s< 0xa)
004176f0        struct SubSolution* edx_1 = &bank->postal_records[0xa]
004176fb        struct SubSolution* esi_2 = edx_1 - 0x1fac0
00417701        struct SubSolution* edi_1 = edx_1
00417703        edx_1 -= 0x1fac0
00417709        __builtin_memcpy(edi_1, esi_2, 0x1fac0)
0041770b        edx_1->__offset(0x1fb00).d = ebx
00417711        ebx -= 1
00417714        do while (ebx s> eax)
00417730        void* edx_2 = bank + eax * 0x1fac0
0041773a        __builtin_memcpy(edx_2 + 8, record, 0x1fac0)
0041773c        *(edx_2 + 0x48) = eax
00417747        g_game_base->players[0].frontend_state = 0x14
00417758        g_game_base->players[0].high_score_entry_pending = 1
00417765        g_game_base->players[0].selected_high_score_rank = eax
00417770        g_game_base->players[0].selected_high_score_mode = 0
0041777b        return
