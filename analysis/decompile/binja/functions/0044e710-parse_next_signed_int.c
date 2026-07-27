/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: parse_next_signed_int @ 0x44e710 */

0044e719        if (**cursor != 0x2d)
0044e737        char* edx_1
0044e71b        edx_1 = *cursor
0044e71d        char eax_1 = *edx_1
0044e721        if (eax_1 == 0x2b)
0044e721        break
0044e725        if (eax_1 == 0x2e)
0044e725        break
0044e72d        if (eax_1 s>= 0x30 && eax_1 s<= 0x39)
0044e72d        break
0044e732        *cursor = &edx_1[1]
0044e737        do while (edx_1[1] != 0x2d)
0044e739        char* eax_2 = *cursor
0044e740        int32_t edi
0044e740        if (*eax_2 != 0x2d)
0044e74a        edi = 1
0044e742        edi = 0xffffffff
0044e746        *cursor = &eax_2[1]
0044e751        int32_t eax_4 = 0
0044e756        if (**cursor s>= 0x30)
0044e773        char* esi_1
0044e758        esi_1 = *cursor
0044e75a        char edx_3 = *esi_1
0044e75f        if (edx_3 s> 0x39)
0044e75f        break
0044e767        eax_4 = sx.d(edx_3) + eax_4 * 0xa - 0x30
0044e76e        *cursor = &esi_1[1]
0044e773        do while (esi_1[1] s>= 0x30)
0044e77a        return eax_4 * edi
