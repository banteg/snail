/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: append_c_string @ 0x431e50 */

00431e50        char* result = arg1
00431e57        char i
00431e57        if (*result != 0)
00431e59        i = result[1]
00431e5c        result = &result[1]
00431e5f        do while (i != 0)
00431e61        char* edx = arg2
00431e65        i = *edx
00431e69        while (i != 0)
00431e6b        *result = i
00431e6d        i = edx[1]
00431e70        result = &result[1]
00431e71        edx = &edx[1]
00431e76        *result = 0
00431e79        return result
