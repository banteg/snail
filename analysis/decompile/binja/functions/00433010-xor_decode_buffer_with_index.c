/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: xor_decode_buffer_with_index @ 0x433010 */

00433014        char* result = arg1
00433018        int32_t ecx = 0
0043301c        if (arg2 s> 0)
0043301e        int32_t ebx
0043301e        int32_t var_4_1 = ebx
0043301f        ebx.b = *result
00433021        ebx.b ^= ecx.b
00433023        *result = ebx.b
00433025        result = &result[1]
00433026        ecx += 1
00433029        do while (ecx s< arg2)
0043302c        return result
