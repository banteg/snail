/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: match_cheat_text @ 0x4047d0 */

004047d0        int32_t ebx
004047d0        int32_t var_4 = ebx
004047da        int32_t edi = arg2
004047dc        int32_t i = 0xffffffff
004047e1        while (i != 0)
004047e1        bool cond:0_1 = 0 != *edi
004047e1        edi += 1
004047e1        i -= 1
004047e1        if (not(cond:0_1))
004047e1        break
004047eb        char* i_1
004047eb        if (not.d(i) - 1 s>= 8)
004047f2        report_errorf("Cheat text too long")
004047fd        label_4047fd:
004047fd        i_1.b = 0
00404800        return i_1
00404803        i_1 = nullptr
00404807        if (not.d(i) - 1 s> 0)
00404809        char* edx_1 = not.d(i) - 1 + arg1 + 7
0040480d        int32_t ecx_1
0040480d        ecx_1.b = i_1[arg2]
00404810        ebx.b = *edx_1
00404814        if (ecx_1.b != ebx.b)
00404814        goto label_4047fd
00404816        i_1 = &i_1[1]
00404817        edx_1 -= 1
0040481a        do while (i_1 s< not.d(i) - 1)
0040481f        i_1.b = 1
00404822        return i_1
