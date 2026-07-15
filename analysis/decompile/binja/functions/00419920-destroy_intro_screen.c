/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: destroy_intro_screen @ 0x419920 */

00419927        g_runtime_config.render_flags = logo->saved_render_flags
0041992c        struct GameRoot* game_base_1 = g_game_base
00419938        if (game_base_1->players[0].high_score_entry_pending != 1)
00419946        game_base_1->players[0].frontend_state = 3
0041993a        game_base_1->players[0].frontend_state = 0x14
00419953        int32_t i = 0
00419957        if (logo->renderable_count s<= 0)
00419957        return
0041995a        struct BodNode** esi_1 = &logo->letters[0].renderable.bod.bod.list_next
00419963        uint16_t list_flags = ((esi_1 - 0x24)->letters[0].renderable.bod.bod.list_flags).w
00419966        struct FrameBodList* ecx_1 = &g_game_base->active_bod_list
0041996f        if ((list_flags:1.b & 2) == 0)
00419976        report_errorf("List remove")
00419982        if ((list_flags.b & 0x40) == 0)
00419993        struct BodNode* list_next = (esi_1 - 0x24)->letters[0].renderable.bod.bod.list_next
00419997        if (list_next != 0)
0041999c        list_next->list_prev = (esi_1 - 0x24)->letters[0].renderable.bod.bod.list_prev
0041999f        struct BodNode* list_prev = (esi_1 - 0x24)->letters[0].renderable.bod.bod.list_prev
004199a4        if (list_prev == 0)
004199af        ecx_1->first = (esi_1 - 0x24)->letters[0].renderable.bod.bod.list_next
004199a8        list_prev->list_next = (esi_1 - 0x24)->letters[0].renderable.bod.bod.list_next
004199b8        (esi_1 - 0x24)->letters[0].renderable.bod.bod.list_next = ecx_1->free_top
004199ba        ecx_1->free_top = &esi_1[-3]
004199bd        uint32_t list_flags_1 = (esi_1 - 0x24)->letters[0].renderable.bod.bod.list_flags
004199c0        list_flags_1:1.b &= 0xfd
004199c3        (esi_1 - 0x24)->letters[0].renderable.bod.bod.list_flags = list_flags_1
00419989        report_errorf("List remove NEXTBOD")
004199c9        i += 1
004199ca        esi_1 = &esi_1[0x24]
004199d2        do while (i s< logo->renderable_count)
004199d7        return
