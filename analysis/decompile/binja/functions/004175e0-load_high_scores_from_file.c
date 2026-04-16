/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_high_scores_from_file @ 0x4175e0 */

004175e2        char* esi = arg2
004175ec        char result = archive_or_file_exists(esi, 1)
004175f6        if (result != 0)
00417607        char* i = load_file_bytes(esi, &arg2)
00417609        char* eax_1 = arg2
0041760f        void* ebx_1 = eax_1 + i
00417612        result = xor_decode_buffer_with_index(i, eax_1)
0041761c        while (i u< ebx_1)
0041761e        int32_t eax_2 = *(i + 0x3c)
00417624        if (eax_2 == 0)
00417687        result = deserialize_compact_high_score_record(*(i + 0x40) * 0x1fac0 + arg1 + 8, i)
00417627        if (eax_2 == 1)
00417687        result = deserialize_compact_high_score_record(*(i + 0x40) * 0x1fac0 + arg1 + 0x15c648, i)
00417629        result = (eax_2 - 1).b - 1
0041762a        if (eax_2 == 2)
00417687        result = deserialize_compact_high_score_record(*(i + 0x40) * 0x1fac0 + arg1 + 0x2b8c88, i)
0041768c        i = &i[*i]
00417695        return result
