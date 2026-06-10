/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: rstrcpy_checked_ascii @ 0x44e5b0 */

0044e5b1        char* esi = arg2
0044e5b5        char i = *esi
0044e5b9        if (i == 0)
0044e5f4        *arg1 = 0
0044e5f7        return i
0044e5bc        char* edi = arg1
0044e5c0        *edi = i
0044e5c2        i = *esi
0044e5d1        if (sx.d(i) s> 0x80 || i s< 0)
0044e5d9        report_errorf("Dodgy Rstrcpy %s", esi)
0044e5e1        i = esi[1]
0044e5e4        edi = &edi[1]
0044e5e5        esi = &esi[1]
0044e5e8        do while (i != 0)
0044e5ea        *edi = i
0044e5ee        return i
