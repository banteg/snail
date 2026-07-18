/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: match_cheat_text @ 0x4047d0 */

004047d0        int32_t ebx
004047d0        int32_t var_4 = ebx
004047da        char* text_1 = text
004047dc        int32_t i = 0xffffffff
004047e1        while (i != 0)
004047e1        bool cond:0_1 = 0 != *text_1
004047e1        text_1 = &text_1[1]
004047e1        i -= 1
004047e1        if (not(cond:0_1))
004047e1        break
004047eb        if (not.d(i) - 1 s>= 8)
004047f2        report_errorf("Cheat text too long")
004047fd        label_4047fd:
004047fd        char* eax
004047fd        eax.b = 0
00404800        return 0
00404803        char* i_1 = nullptr
00404807        if (not.d(i) - 1 s> 0)
00404809        char* recent_text_cursor = not.d(i) - 1 + cheat + 7
00404814        if (*(i_1 + text) != *recent_text_cursor)
00404814        goto label_4047fd
00404816        i_1 = &i_1[1]
00404817        recent_text_cursor -= 1
0040481a        do while (i_1 s< not.d(i) - 1)
0040481f        char* eax_1
0040481f        eax_1.b = 1
00404822        return 1
