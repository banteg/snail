/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: remove_track_render_cache_bods @ 0x433f20 */

00433f20        struct SegmentCache* manager_1 = manager
00433f25        struct BodNode** next_ref = &manager->slots[0][0].bod.bod.list_next
00433f28        int32_t rows_remaining = 0x8f
00433fb4        bool cond:0_1
00433f3a        int32_t families_remaining = 5
00433fa9        int32_t i
00433f42        if ((next_ref[-2] & 0x200) != 0)
00433f49        struct BodList* active_list = &g_game_base->active_bod_list
00433f4f        uint32_t list_flags = next_ref[-2]
00433f54        if ((0x200 & list_flags) == 0)
00433f5b        report_errorf("List remove")
00433f67        if ((list_flags.b & 0x40) == 0)
00433f78        struct BodNode* list_next = *next_ref
00433f7c        if (list_next != 0)
00433f81        list_next->list_prev = next_ref[-1]
00433f84        struct BodNode* list_prev = next_ref[-1]
00433f89        if (list_prev == 0)
00433f94        active_list->first = *next_ref
00433f8d        list_prev->list_next = *next_ref
00433f9d        *next_ref = active_list->free_top
00433f9f        active_list->free_top = &next_ref[-3]
00433fa2        next_ref[-2] &= 0xfffffdff
00433f6e        report_errorf("List remove NEXTBOD")
00433fa5        next_ref = &next_ref[0xf]
00433fa8        i = families_remaining
00433fa8        families_remaining -= 1
00433fa9        do while (i != 1)
00433faf        cond:0_1 = rows_remaining != 1
00433fb0        rows_remaining -= 1
00433fb4        do while (cond:0_1)
00433fbb        return
