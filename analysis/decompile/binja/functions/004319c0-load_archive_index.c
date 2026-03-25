/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_archive_index @ 0x4319c0 */

004319c3        data_53c7f8 = 0
004319e2        if (archive_or_file_exists(arg1, 0) == 0)
004319e4        data_53c7f8 = 0
004319f4        return 1
004319ff        char var_7c
004319ff        load_file_bytes_fixed_size_from_archive_or_fs(arg1, &var_7c, 0x7c)
00431a0d        xor_archive_bytes_in_place(0, &var_7c, 0x7c)
00431a1c        uint32_t var_74
00431a1c        int32_t* eax_1 = allocate_tracked_memory(var_74, "Dat File Header")
00431a26        load_file_bytes_fixed_size_from_archive_or_fs(arg1, eax_1, var_74)
00431a2f        xor_archive_bytes_in_place(0, eax_1, var_74)
00431a34        int32_t* eax_2 = eax_1
00431a39        data_53c7f8 = eax_2
00431a40        int32_t i = 0
00431a44        if (*eax_1 s> 0)
00431a46        int32_t ecx_1 = 0
00431a48        void* esi_1 = *(ecx_1 + eax_2 + 4)
00431a4c        ecx_1 += 0xc
00431a51        i += 1
00431a52        *(ecx_1 + eax_2 - 8) = esi_1 + eax_2
00431a56        eax_2 = data_53c7f8
00431a5d        do while (i s< *eax_2)
00431a6d        data_53c7f0 = sub_48b41d(arg1, "rb")
00431a72        int32_t* result
00431a72        result.b = 1
00431a7a        return result
