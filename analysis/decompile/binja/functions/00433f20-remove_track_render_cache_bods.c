/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: remove_track_render_cache_bods @ 0x433f20 */

00433f20        struct SegmentCache* manager_1 = manager
00433f25        struct BodNode** esi = &manager->slots[0][0].bod.bod.list_next
00433f28        int32_t var_4 = 0x8f
00433fb4        bool cond:0_1
00433f3a        int32_t i_1 = 5
00433fa9        int32_t i
00433f42        if (((esi - 0x64)->slots[0][0].bod.bod.list_flags & 0x200) != 0)
00433f49        struct BodList* ecx = &g_game_base->active_bod_list
00433f4f        uint32_t list_flags = (esi - 0x64)->slots[0][0].bod.bod.list_flags
00433f54        if ((0x200 & list_flags) == 0)
00433f5b        report_errorf("List remove")
00433f67        if ((list_flags.b & 0x40) == 0)
00433f78        struct BodNode* list_next = (esi - 0x64)->slots[0][0].bod.bod.list_next
00433f7c        if (list_next != 0)
00433f81        list_next->list_prev = (esi - 0x64)->slots[0][0].bod.bod.list_prev
00433f84        struct BodNode* list_prev = (esi - 0x64)->slots[0][0].bod.bod.list_prev
00433f89        if (list_prev == 0)
00433f94        ecx->first = (esi - 0x64)->slots[0][0].bod.bod.list_next
00433f8d        list_prev->list_next = (esi - 0x64)->slots[0][0].bod.bod.list_next
00433f9d        (esi - 0x64)->slots[0][0].bod.bod.list_next = ecx->free_top
00433f9f        ecx->free_top = &esi[-3]
00433fa2        (esi - 0x64)->slots[0][0].bod.bod.list_flags &= 0xfffffdff
00433f6e        report_errorf("List remove NEXTBOD")
00433fa5        esi = &esi[0xf]
00433fa8        i = i_1
00433fa8        i_1 -= 1
00433fa9        do while (i != 1)
00433faf        cond:0_1 = var_4 != 1
00433fb0        var_4 -= 1
00433fb4        do while (cond:0_1)
00433fbb        return
