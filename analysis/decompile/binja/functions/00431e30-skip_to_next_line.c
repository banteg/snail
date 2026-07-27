/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: skip_to_next_line @ 0x431e30 */

00431e39        if (**cursor != 0)
00431e48        char* eax_1
00431e3b        eax_1 = *cursor
00431e40        if (*eax_1 == 0xa)
00431e40        break
00431e43        *cursor = &eax_1[1]
00431e48        do while (eax_1[1] != 0)
00431e4a        *cursor = &(*cursor)[1]
00431e4c        return
