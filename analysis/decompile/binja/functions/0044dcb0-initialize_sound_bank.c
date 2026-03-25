/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_sound_bank @ 0x44dcb0 */

0044dcb1        int32_t* esi = arg1
0044dcb5        char* result = *esi
0044dcba        if (*result != 0)
0044dcbd        int32_t* edi_1 = esi
0044dcc9        esi = &esi[3]
0044dccc        edi_1[1] = register_sound_sample(result, edi_1[2])
0044dcd2        edi_1 = esi
0044dcd4        result = *esi
0044dcd9        do while (*result != 0)
0044dcdd        return result
