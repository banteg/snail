/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: remove_track_render_cache_bods @ 0x433f20 */

00433f20        struct TrackRenderCacheManager* manager_1 = manager
00433f25        void* __offset(TrackRenderCacheManager, 0x64) esi = &manager->slots[0].__offset(0xc).d
00433f28        int32_t var_4 = 0x8f
00433fb4        bool cond:0_1
00433f3a        int32_t i_1 = 5
00433fa9        int32_t i
00433f42        if (((esi - 0x64)->slots[0].__offset(0x4).d & 0x200) != 0)
00433f49        void* ecx = data_4df904 + 0x5a8
00433f4f        int32_t eax_2 = (esi - 0x64)->slots[0].__offset(0x4).d
00433f54        if ((0x200 & eax_2) == 0)
00433f5b        report_errorf("List remove")
00433f67        if ((eax_2.b & 0x40) == 0)
00433f78        void* eax_3 = (esi - 0x64)->slots[0].__offset(0xc).d
00433f7c        if (eax_3 != 0)
00433f81        *(eax_3 + 8) = (esi - 0x64)->slots[0].__offset(0x8).d
00433f84        void* eax_4 = (esi - 0x64)->slots[0].__offset(0x8).d
00433f89        if (eax_4 == 0)
00433f94        *(ecx + 4) = (esi - 0x64)->slots[0].__offset(0xc).d
00433f8d        *(eax_4 + 0xc) = (esi - 0x64)->slots[0].__offset(0xc).d
00433f9d        (esi - 0x64)->slots[0].__offset(0xc).d = *(ecx + 8)
00433f9f        *(ecx + 8) = esi - 0xc
00433fa2        (esi - 0x64)->slots[0].__offset(0x4).d &= 0xfffffdff
00433f6e        report_errorf("List remove NEXTBOD")
00433fa5        esi += 0x3c
00433fa8        i = i_1
00433fa8        i_1 -= 1
00433fa9        do while (i != 1)
00433faf        cond:0_1 = var_4 != 1
00433fb0        var_4 -= 1
00433fb4        do while (cond:0_1)
00433fbb        return
