/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: xor_archive_bytes_in_place @ 0x431980 */

00431980        int32_t ecx = arg1
00431984        int32_t result = arg3
00431989        int32_t edi = ecx + result
0043198e        if (ecx s< edi)
00431990        int32_t ebx
00431990        int32_t var_8_1 = ebx
00431996        char* esi_2 = arg2 - ecx
00431998        result.b = ecx.b
0043199a        ebx.b = 3
0043199c        result.w = muls.dp.b(result.b, ecx.b)
0043199e        char edx = result.b
004319a0        result.b = ecx.b
004319a2        result.w = muls.dp.b(result.b, 3)
004319a4        ebx.b = esi_2[ecx]
004319a9        ebx.b ^= edx ^ result.b
004319ab        esi_2[ecx] = ebx.b
004319ae        ecx += 1
004319b1        do while (ecx s< edi)
004319b6        return result
