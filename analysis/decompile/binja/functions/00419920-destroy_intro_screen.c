/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: destroy_intro_screen @ 0x419920 */

00419927        data_4df934.d = *(arg1 + 0xc)
0041992c        void* eax_1 = data_4df904
00419938        if (*(eax_1 + 0x30d) != 1)
00419946        *(eax_1 + 0x1b8) = 3
0041993a        *(eax_1 + 0x1b8) = 0x14
00419950        int32_t result = *(arg1 + 0x14)
00419953        int32_t edi = 0
00419957        if (result s> 0)
0041995a        int32_t* esi_1 = arg1 + 0x24
00419963        int16_t eax_2 = (esi_1[-2]).w
00419966        void* ecx_1 = data_4df904 + 0x5a8
0041996f        if ((eax_2:1.b & 2) == 0)
00419976        report_errorf("List remove")
00419982        if ((eax_2.b & 0x40) == 0)
00419993        void* eax_3 = *esi_1
00419997        if (eax_3 != 0)
0041999c        *(eax_3 + 8) = esi_1[-1]
0041999f        void* eax_4 = esi_1[-1]
004199a4        if (eax_4 == 0)
004199af        *(ecx_1 + 4) = *esi_1
004199a8        *(eax_4 + 0xc) = *esi_1
004199b8        *esi_1 = *(ecx_1 + 8)
004199ba        *(ecx_1 + 8) = &esi_1[-3]
004199c0        int32_t eax_7
004199c0        eax_7:1.b = esi_1[-2]:1.b & 0xfd
004199c3        esi_1[-2] = eax_7
00419989        report_errorf("List remove NEXTBOD")
004199c6        result = *(arg1 + 0x14)
004199c9        edi += 1
004199ca        esi_1 = &esi_1[0x24]
004199d2        do while (edi s< result)
004199d7        return result
