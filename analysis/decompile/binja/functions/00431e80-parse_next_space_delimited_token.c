/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: parse_next_space_delimited_token @ 0x431e80 */

00431e89        char* ecx
00431e89        if (**arg1 == 0x20)
00431e8d        ecx = *arg1 + 1
00431e8e        *arg1 = ecx
00431e93        do while (*ecx == 0x20)
00431e97        ecx.b = **arg1
00431e99        char* edx_1 = arg2
00431ea0        if (ecx.b != 0x20)
00431eb6        char* ecx_4
00431ea4        char* ecx_2
00431ea4        ecx_2.b = **arg1
00431ea9        if (ecx_2.b == 0xd)
00431ea9        break
00431eab        *edx_1 = ecx_2.b
00431eaf        edx_1 = &edx_1[1]
00431eb0        ecx_4 = *arg1 + 1
00431eb1        *arg1 = ecx_4
00431eb6        do while (*ecx_4 != 0x20)
00431eb8        *edx_1 = 0
00431ebb        return arg1
