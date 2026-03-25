/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: remove_track_render_cache_bods @ 0x433f20 */

00433f20        void* var_4 = arg1
00433f25        int32_t* esi = arg1 + 0x64
00433f28        int32_t result_1 = 0x8f
00433fb4        int32_t result
00433fb4        bool cond:0_1
00433f3a        int32_t i_1 = 5
00433fa9        int32_t i
00433f42        if ((esi[-2] & 0x200) != 0)
00433f49        void* ecx = data_4df904 + 0x5a8
00433f4f        int32_t eax_2 = esi[-2]
00433f54        if ((0x200 & eax_2) == 0)
00433f5b        report_errorf("List remove")
00433f67        if ((eax_2.b & 0x40) == 0)
00433f78        void* eax_3 = *esi
00433f7c        if (eax_3 != 0)
00433f81        *(eax_3 + 8) = esi[-1]
00433f84        void* eax_4 = esi[-1]
00433f89        if (eax_4 == 0)
00433f94        *(ecx + 4) = *esi
00433f8d        *(eax_4 + 0xc) = *esi
00433f9d        *esi = *(ecx + 8)
00433f9f        *(ecx + 8) = &esi[-3]
00433fa2        esi[-2] &= 0xfffffdff
00433f6e        report_errorf("List remove NEXTBOD")
00433fa5        esi = &esi[0xf]
00433fa8        i = i_1
00433fa8        i_1 -= 1
00433fa9        do while (i != 1)
00433faf        result = result_1 - 1
00433faf        cond:0_1 = result_1 != 1
00433fb0        result_1 = result
00433fb4        do while (cond:0_1)
00433fbb        return result
