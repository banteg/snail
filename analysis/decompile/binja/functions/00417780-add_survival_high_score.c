/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: add_survival_high_score @ 0x417780 */

00417780        void* var_4_1 = arg1
0041778b        void* result = nullptr
0041779a        *(arg2 + 0x3c) = 1
004177a1        *(arg2 + 0x40) = 0
004177a4        *(arg2 + 0x44) = 0
004177ab        __builtin_memcpy(arg1 + 0x9080c8, arg2, 0x1fac0)
004177ba        __builtin_memcpy(arg1 + 0x927b88, arg2, 0x1fac0)
004177bf        int32_t* ecx = arg1 + 0x15c64c
004177c7        while (*(arg2 + 4) s<= *ecx)
004177c9        result += 1
004177ca        ecx = &ecx[0x7eb0]
004177d3        if (result s>= 0xa)
004177da        return result
004177dd        int32_t ebx = 0xa
004177e4        if (result s< 0xa)
004177e6        void* ebp_1 = arg1 + 0x2991c8
004177f1        void* esi_3 = ebp_1 - 0x1fac0
004177f7        void* edi_2 = ebp_1
004177f9        ebp_1 -= 0x1fac0
004177ff        __builtin_memcpy(edi_2, esi_3, 0x1fac0)
00417801        *(ebp_1 + 0x1fb00) = ebx
00417807        ebx -= 1
0041780a        do while (ebx s> result)
00417828        void* ebx_1 = result * 0x1fac0 + arg1
00417836        __builtin_memcpy(ebx_1 + 0x15c648, arg2, 0x1fac0)
0041783d        *(ebx_1 + 0x15c684) = 1
00417843        *(ebx_1 + 0x15c688) = result
0041784f        *(data_4df904 + 0x1b8) = 0x14
0041785f        *(data_4df904 + 0x30d) = 1
00417865        if (result != 0xffffffff)
00417867        *(arg2 + 0x3c) = 1
0041786a        *(ebx_1 + 0x15c684) = 1
0041787c        *(data_4df904 + 0x6ffae0) = arg1 + 0x15c648
00417888        *(data_4df904 + 0x310) = result
0041788e        result = data_4df904
00417893        *(result + 0x314) = 1
0041789e        return result
