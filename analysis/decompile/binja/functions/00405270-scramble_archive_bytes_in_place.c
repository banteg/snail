/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: scramble_archive_bytes_in_place @ 0x405270 */

00405275        char* ecx = nullptr
00405279        if (arg2 s<= 0)
00405279        return 
0040527b        int32_t ebx
0040527b        int32_t var_8_1 = ebx
00405283        ebx.b = 3
0040528d        ebx.b = ecx[arg1]
00405292        ebx.b ^= muls.dp.b(ecx.b, ecx.b) ^ muls.dp.b(ecx.b, 3)
00405294        ecx[arg1] = ebx.b
00405297        ecx = &ecx[1]
0040529a        do while (ecx s< arg2)
0040529f        return
