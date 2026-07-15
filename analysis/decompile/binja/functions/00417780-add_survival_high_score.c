/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: add_survival_high_score @ 0x417780 */

00417780        struct SubHighScore* bank_1 = bank
0041778b        int32_t eax = 0
0041779a        record->high_score_mode_tag = 1
004177a1        record->route_or_rank_index = 0
004177a4        record->replay_cursor = 0
004177ab        __builtin_memcpy(&bank->current_result_record, record, 0x1fac0)
004177ba        __builtin_memcpy(&bank->survival_pending_record, record, 0x1fac0)
004177bf        int32_t* ecx = &bank->survival_records[0].score
004177c7        while (record->score s<= (ecx - 0x15c64c)->survival_records[0].score)
004177c9        eax += 1
004177ca        ecx = &ecx[0x7eb0]
004177d3        if (eax s>= 0xa)
004177da        return
004177dd        int32_t ebx = 0xa
004177e4        if (eax s< 0xa)
004177e6        struct SubSolution* ebp_1 = &bank->survival_records[0xa]
004177f1        struct SubSolution* esi_3 = ebp_1 - 0x1fac0
004177f7        struct SubSolution* edi_2 = ebp_1
004177f9        ebp_1 -= 0x1fac0
004177ff        __builtin_memcpy(edi_2, esi_3, 0x1fac0)
00417801        ebp_1->__offset(0x1fb00).d = ebx
00417807        ebx -= 1
0041780a        do while (ebx s> eax)
00417828        void* ebx_1 = eax * 0x1fac0 + bank
00417836        __builtin_memcpy(ebx_1 + 0x15c648, record, 0x1fac0)
0041783d        *(ebx_1 + 0x15c684) = 1
00417843        *(ebx_1 + 0x15c688) = eax
0041784f        g_game_base->players[0].frontend_state = 0x14
0041785f        g_game_base->players[0].high_score_entry_pending = 1
00417865        if (eax == 0xffffffff)
00417865        return
00417867        record->high_score_mode_tag = 1
0041786a        *(ebx_1 + 0x15c684) = 1
0041787c        g_game_base->subgame.sub_high_score.active_record_bank = &bank->survival_records
00417888        g_game_base->players[0].selected_high_score_rank = eax
00417893        g_game_base->players[0].selected_high_score_mode = 1
0041789e        return
