/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: add_arcade_high_score @ 0x4176a0 */

004176a0        void* var_4_1 = arg1
004176ae        int32_t eax = 0
004176b0        *(arg2 + 0x40) = arg3
004176c0        *(arg2 + 0x3c) = 0
004176c3        __builtin_memcpy(arg1 + 0x9080c8, arg2, 0x1fac0)
004176cc        int32_t* ecx_1 = arg1 + 0xc
004176d1        while (*(arg2 + 4) s<= *ecx_1)
004176d3        eax += 1
004176d4        ecx_1 = &ecx_1[0x7eb0]
004176dd        if (eax s>= 0xa)
004176e3        return eax
004176e7        int32_t ebx = 0xa
004176ee        if (eax s< 0xa)
004176f0        void* edx_1 = arg1 + 0x13cb88
004176fb        void* esi_2 = edx_1 - 0x1fac0
00417701        void* edi_1 = edx_1
00417703        edx_1 -= 0x1fac0
00417709        __builtin_memcpy(edi_1, esi_2, 0x1fac0)
0041770b        *(edx_1 + 0x1fb00) = ebx
00417711        ebx -= 1
00417714        do while (ebx s> eax)
00417730        void* edx_2 = arg1 + eax * 0x1fac0
0041773a        __builtin_memcpy(edx_2 + 8, arg2, 0x1fac0)
0041773c        *(edx_2 + 0x48) = eax
00417747        *(data_4df904 + 0x1b8) = 0x14
00417758        *(data_4df904 + 0x30d) = 1
00417765        *(data_4df904 + 0x310) = eax
0041776b        void* eax_1 = data_4df904
00417770        *(eax_1 + 0x314) = 0
0041777b        return eax_1
