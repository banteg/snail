/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: advance_to_next_crlf_line @ 0x44e690 */

0044e690        char* cursor_1 = cursor
0044e694        char i = *cursor_1
0044e69c        if (i != 0 && i != 0)
0044e6a5        if (i == 0xd && cursor_1[1] == 0xa)
0044e6b5        cursor_1.b = cursor_1[2]
0044e6b8        char temp1 = cursor_1.b
0044e6b8        cursor_1.b = neg.b(cursor_1.b)
0044e6be        return &cursor_1[2] & sbb.d(cursor_1, cursor_1, temp1 != 0)
0044e6a7        i = cursor_1[1]
0044e6aa        cursor_1 = &cursor_1[1]
0044e6ad        do while (i != 0)
0044e6b1        return 0
