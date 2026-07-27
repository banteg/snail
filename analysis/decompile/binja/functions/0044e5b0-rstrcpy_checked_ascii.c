/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: rstrcpy_checked_ascii @ 0x44e5b0 */

0044e5b1        char const* source_1 = source
0044e5b5        char const i = *source_1
0044e5b9        if (i == 0)
0044e5f4        *destination = 0
0044e5f7        return
0044e5bc        char* destination_1 = destination
0044e5c0        *destination_1 = i
0044e5c2        i = *source_1
0044e5d1        if (sx.d(i) s> 0x80 || i s< 0)
0044e5d9        report_errorf("Dodgy Rstrcpy %s", source_1)
0044e5e1        i = source_1[1]
0044e5e4        destination_1 = &destination_1[1]
0044e5e5        source_1 = &source_1[1]
0044e5e8        do while (i != 0)
0044e5ea        *destination_1 = i
0044e5ee        return
