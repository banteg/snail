/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: clear_active_landscape_entries @ 0x418a30 */

00418a32        int32_t* esi = entries + 0xc
00418a35        int32_t i_1 = 0xa
00418ab8        int32_t i
00418a40        if (((esi[-2]).w:1.b & 2) != 0)
00418a42        esi[0x1d] = 0
00418a4e        struct BodList* ecx = &g_game_base->active_bod_list
00418a54        int16_t eax_3 = (esi[-2]).w
00418a5a        if ((eax_3:1.b & 2) == 0)
00418a61        report_errorf("List remove")
00418a6d        if ((eax_3.b & 0x40) == 0)
00418a7e        void* eax_4 = *esi
00418a82        if (eax_4 != 0)
00418a87        *(eax_4 + 8) = esi[-1]
00418a8a        void* eax_5 = esi[-1]
00418a8f        if (eax_5 == 0)
00418a9a        ecx->first = *esi
00418a93        *(eax_5 + 0xc) = *esi
00418aa3        *esi = ecx->free_top
00418aa5        ecx->free_top = &esi[-3]
00418aa8        int32_t eax_8 = esi[-2]
00418aab        eax_8:1.b &= 0xfd
00418aae        esi[-2] = eax_8
00418a74        report_errorf("List remove NEXTBOD")
00418ab1        esi = &esi[0x24]
00418ab7        i = i_1
00418ab7        i_1 -= 1
00418ab8        do while (i != 1)
00418abc        return
