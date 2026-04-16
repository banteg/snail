/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_level_definitions @ 0x448900 */

00448905        sub_48bf30(0x4004)
0044891f        void arg_4
0044891f        enumerate_matching_archive_or_fs_entries("Levels", "*.txt", &__return_addr, &arg_4)
00448924        void* const result = __return_addr
0044892b        int32_t esi = 0
0044892f        if (result s> 0)
00448932        char* edi_1 = &arg_4
00448943        load_level_definition_file(data_4df904 + 0x224804, edi_1)
00448948        result = __return_addr
0044894c        esi += 1
0044894d        edi_1 = &edi_1[0x80]
00448955        do while (esi s< result)
0044895f        return result
