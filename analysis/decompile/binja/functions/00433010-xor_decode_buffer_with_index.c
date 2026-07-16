/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: xor_decode_buffer_with_index @ 0x433010 */

00433014        char* result = bytes
00433018        int32_t ecx = 0
0043301c        if (byte_count s> 0)
0043301e        int32_t ebx
0043301e        int32_t var_4_1 = ebx
00433023        *result ^= ecx.b
00433025        result = &result[1]
00433026        ecx += 1
00433029        do while (ecx s< byte_count)
0043302c        return result
