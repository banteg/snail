/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: parse_next_space_delimited_token @ 0x431e80 */

00431e89        char* ecx
00431e89        if (**cursor == 0x20)
00431e8d        ecx = &(*cursor)[1]
00431e8e        *cursor = ecx
00431e93        do while (*ecx == 0x20)
00431e97        ecx.b = **cursor
00431e99        char* out_1 = out
00431ea0        if (ecx.b != 0x20)
00431eb6        char* ecx_4
00431ea4        char* ecx_2
00431ea4        ecx_2.b = **cursor
00431ea9        if (ecx_2.b == 0xd)
00431ea9        break
00431eab        *out_1 = ecx_2.b
00431eaf        out_1 = &out_1[1]
00431eb0        ecx_4 = &(*cursor)[1]
00431eb1        *cursor = ecx_4
00431eb6        do while (*ecx_4 != 0x20)
00431eb8        *out_1 = 0
00431ebb        return cursor
