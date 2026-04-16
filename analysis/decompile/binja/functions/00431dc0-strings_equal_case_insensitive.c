/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: strings_equal_case_insensitive @ 0x431dc0 */

00431dc2        char* esi = arg2
00431dc7        char* edi = arg1
00431dcb        char i = *esi
00431dcd        int32_t ebx
00431dcd        ebx.b = *edi
00431dcf        char i_1 = i
00431dd1        bool eax = ebx.b
00431dd9        if (eax s>= 0x61 && eax s<= 0x7a)
00431ddb        eax -= 0x20
00431de5        if (i_1 s>= 0x61 && i_1 s<= 0x7a)
00431de7        i_1 -= 0x20
00431dec        if (ebx.b != 0)
00431df0        while (i != 0)
00431df4        if (eax != i_1)
00431df4        break
00431df6        ebx.b = edi[1]
00431df9        i = esi[1]
00431dfc        edi = &edi[1]
00431dfd        esi = &esi[1]
00431dfe        eax = ebx.b
00431e00        i_1 = i
00431e08        if (eax s>= 0x61 && eax s<= 0x7a)
00431e0a        eax -= 0x20
00431e14        if (i_1 s>= 0x61 && i_1 s<= 0x7a)
00431e16        i_1 -= 0x20
00431e1b        if (ebx.b == 0)
00431e1b        break
00431e27        return *esi == 0
