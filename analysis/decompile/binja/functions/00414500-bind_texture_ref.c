/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: bind_texture_ref @ 0x414500 */

00414500        int32_t result = data_503174
0041450c        if (arg1 == result)
004145b1        return result
00414512        int32_t* eax = data_502fec
00414518        int32_t edi_1 = data_5031c8
0041451e        data_503174 = arg1
00414533        int32_t eax_1 = (*(*eax + 0xf4))(eax, 0, *(edi_1 + (arg1[0x23] << 2)))
00414543        data_5031c0 += 1
00414549        if (eax_1 != 0)
00414554        report_errorf("SetTexture Failed %s", &arg1[3])
0041455d        return 0
00414563        int32_t* eax_3 = data_502fec
00414568        int32_t ecx_2 = *eax_3
0041456a        if (((*arg1).w:1.b & 0x10) == 0)
00414596        (*(ecx_2 + 0xfc))(eax_3, 0, 0xd, 3)
0041459c        int32_t* eax_6 = data_502fec
004145aa        return (*(*eax_6 + 0xfc))(eax_6, 0, 0xe, 3)
00414573        (*(ecx_2 + 0xfc))(eax_3, 0, 0xd, 1)
00414579        int32_t* eax_4 = data_502fec
0041458e        return (*(*eax_4 + 0xfc))(eax_4, 0, 0xe, 1)
