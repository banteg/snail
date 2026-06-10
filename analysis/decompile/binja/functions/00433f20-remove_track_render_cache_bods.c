/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: remove_track_render_cache_bods @ 0x433f20 */

00433f20        struct TrackRenderCacheManager* manager_1 = manager
00433f25        uint8_t* esi = &manager->slots[0]._pad_00[0xc]
00433f28        int32_t result_1 = 0x8f
00433fb4        int32_t result
00433fb4        bool cond:0_1
00433f3a        int32_t i_1 = 5
00433fa9        int32_t i
00433f42        if (((esi - 0x64)->slots[0]._pad_00[4].d & 0x200) != 0)
00433f49        void* ecx = data_4df904 + 0x5a8
00433f4f        int32_t eax_2
00433f4f        eax_2.b = (esi - 0x64)->slots[0]._pad_00[4]
00433f4f        eax_2:1.b = (esi - 0x64)->slots[0]._pad_00[5]
00433f4f        eax_2:2.b = (esi - 0x64)->slots[0]._pad_00[6]
00433f4f        eax_2:3.b = (esi - 0x64)->slots[0]._pad_00[7]
00433f54        if ((0x200 & eax_2) == 0)
00433f5b        report_errorf("List remove")
00433f67        if ((eax_2.b & 0x40) == 0)
00433f78        void* eax_3
00433f78        eax_3.b = (esi - 0x64)->slots[0]._pad_00[0xc]
00433f78        eax_3:1.b = (esi - 0x64)->slots[0]._pad_00[0xd]
00433f78        eax_3:2.b = (esi - 0x64)->slots[0]._pad_00[0xe]
00433f78        eax_3:3.b = (esi - 0x64)->slots[0]._pad_00[0xf]
00433f7c        if (eax_3 != 0)
00433f7e        int32_t edx_1
00433f7e        edx_1.b = (esi - 0x64)->slots[0]._pad_00[8]
00433f7e        edx_1:1.b = (esi - 0x64)->slots[0]._pad_00[9]
00433f7e        edx_1:2.b = (esi - 0x64)->slots[0]._pad_00[0xa]
00433f7e        edx_1:3.b = (esi - 0x64)->slots[0]._pad_00[0xb]
00433f81        *(eax_3 + 8) = edx_1
00433f84        void* eax_4
00433f84        eax_4.b = (esi - 0x64)->slots[0]._pad_00[8]
00433f84        eax_4:1.b = (esi - 0x64)->slots[0]._pad_00[9]
00433f84        eax_4:2.b = (esi - 0x64)->slots[0]._pad_00[0xa]
00433f84        eax_4:3.b = (esi - 0x64)->slots[0]._pad_00[0xb]
00433f89        if (eax_4 == 0)
00433f92        int32_t eax_5
00433f92        eax_5.b = (esi - 0x64)->slots[0]._pad_00[0xc]
00433f92        eax_5:1.b = (esi - 0x64)->slots[0]._pad_00[0xd]
00433f92        eax_5:2.b = (esi - 0x64)->slots[0]._pad_00[0xe]
00433f92        eax_5:3.b = (esi - 0x64)->slots[0]._pad_00[0xf]
00433f94        *(ecx + 4) = eax_5
00433f8b        int32_t edx_2
00433f8b        edx_2.b = (esi - 0x64)->slots[0]._pad_00[0xc]
00433f8b        edx_2:1.b = (esi - 0x64)->slots[0]._pad_00[0xd]
00433f8b        edx_2:2.b = (esi - 0x64)->slots[0]._pad_00[0xe]
00433f8b        edx_2:3.b = (esi - 0x64)->slots[0]._pad_00[0xf]
00433f8d        *(eax_4 + 0xc) = edx_2
00433f97        int32_t edx_3 = *(ecx + 8)
00433f9d        (esi - 0x64)->slots[0]._pad_00[0xc] = edx_3.b
00433f9d        (esi - 0x64)->slots[0]._pad_00[0xd] = edx_3:1.b
00433f9d        (esi - 0x64)->slots[0]._pad_00[0xe] = edx_3:2.b
00433f9d        (esi - 0x64)->slots[0]._pad_00[0xf] = edx_3:3.b
00433f9f        *(ecx + 8) = &esi[0xfffffff4]
00433fa2        (esi - 0x64)->slots[0]._pad_00[4].d &= 0xfffffdff
00433f6e        report_errorf("List remove NEXTBOD")
00433fa5        esi = &esi[0x3c]
00433fa8        i = i_1
00433fa8        i_1 -= 1
00433fa9        do while (i != 1)
00433faf        result = result_1 - 1
00433faf        cond:0_1 = result_1 != 1
00433fb0        result_1 = result
00433fb4        do while (cond:0_1)
00433fbb        return result
