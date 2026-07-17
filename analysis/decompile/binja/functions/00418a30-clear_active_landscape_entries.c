/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: clear_active_landscape_entries @ 0x418a30 */

00418a32        struct BodNode** esi = &manager->active_entries[0].bod.bod.bod.list_next
00418a35        int32_t i_1 = 0xa
00418ab8        int32_t i
00418a40        if ((((esi - 0xc)->active_entries[0].bod.bod.bod.list_flags).w:1.b & 2) != 0)
00418a42        (esi - 0xc)->active_entries[0].state = 0
00418a4e        struct BodList* ecx = &g_game_base->active_bod_list
00418a54        uint16_t list_flags = ((esi - 0xc)->active_entries[0].bod.bod.bod.list_flags).w
00418a5a        if ((list_flags:1.b & 2) == 0)
00418a61        report_errorf("List remove")
00418a6d        if ((list_flags.b & 0x40) == 0)
00418a7e        struct BodNode* list_next = (esi - 0xc)->active_entries[0].bod.bod.bod.list_next
00418a82        if (list_next != 0)
00418a87        list_next->list_prev = (esi - 0xc)->active_entries[0].bod.bod.bod.list_prev
00418a8a        struct BodNode* list_prev = (esi - 0xc)->active_entries[0].bod.bod.bod.list_prev
00418a8f        if (list_prev == 0)
00418a9a        ecx->first = (esi - 0xc)->active_entries[0].bod.bod.bod.list_next
00418a93        list_prev->list_next = (esi - 0xc)->active_entries[0].bod.bod.bod.list_next
00418aa3        (esi - 0xc)->active_entries[0].bod.bod.bod.list_next = ecx->free_top
00418aa5        ecx->free_top = &esi[-3]
00418aa8        uint32_t list_flags_1 = (esi - 0xc)->active_entries[0].bod.bod.bod.list_flags
00418aab        list_flags_1:1.b &= 0xfd
00418aae        (esi - 0xc)->active_entries[0].bod.bod.bod.list_flags = list_flags_1
00418a74        report_errorf("List remove NEXTBOD")
00418ab1        esi = &esi[0x24]
00418ab7        i = i_1
00418ab7        i_1 -= 1
00418ab8        do while (i != 1)
00418abc        return
