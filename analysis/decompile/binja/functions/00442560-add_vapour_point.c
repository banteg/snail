/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: add_vapour_point @ 0x442560 */

00442564        int32_t edi = *(arg1 + 0x80)
0044256a        int32_t ecx = *(arg1 + 0x84)
00442572        if (edi s< ecx)
00442588        __builtin_memcpy((edi << 6) + *(arg1 + 0x90), arg2, 0x40)
00442593        *(arg1 + 0x80) += 1
00442599        return arg1
0044259d        int32_t i = 0
004425a2        if (ecx - 1 s> 0)
004425a4        int32_t edx_2 = 0
004425a6        int32_t ecx_4 = *(arg1 + 0x90)
004425ac        i += 1
004425ad        int32_t esi_2 = edx_2 + ecx_4 + 0x40
004425b1        int32_t edi_3 = edx_2 + ecx_4
004425b9        edx_2 += 0x40
004425bc        __builtin_memcpy(edi_3, esi_2, 0x40)
004425c7        do while (i s< *(arg1 + 0x84) - 1)
004425cf        int32_t eax = *(arg1 + 0x90)
004425e6        __builtin_memcpy((*(arg1 + 0x80) << 6) + eax - 0x40, arg2, 0x40)
004425ea        return eax
