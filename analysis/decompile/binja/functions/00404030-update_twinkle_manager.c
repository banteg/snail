/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_twinkle_manager @ 0x404030 */

00404034        int32_t eax = arg1[0x3c]
0040403a        int32_t result = eax - 1
0040403b        if (eax == 1)
0040403d        result = arg1[0x3d]
00404043        int32_t esi_1 = 0
00404047        if (result s> 0)
0040404a        int32_t* edi_1 = arg1
0040404e        update_twinkle(edi_1)
00404053        result = arg1[0x3d]
00404059        esi_1 += 1
0040405a        edi_1 = &edi_1[0xc]
0040405f        do while (esi_1 s< result)
00404064        return result
