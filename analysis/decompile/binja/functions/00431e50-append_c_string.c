/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: append_c_string @ 0x431e50 */

00431e50        char* destination_1 = destination
00431e57        if (*destination_1 != 0)
00431e5f        char i
00431e59        i = destination_1[1]
00431e5c        destination_1 = &destination_1[1]
00431e5f        do while (i != 0)
00431e61        char* source_1 = source
00431e65        char i_1 = *source_1
00431e69        while (i_1 != 0)
00431e6b        *destination_1 = i_1
00431e6d        i_1 = source_1[1]
00431e70        destination_1 = &destination_1[1]
00431e71        source_1 = &source_1[1]
00431e76        *destination_1 = 0
00431e79        return
