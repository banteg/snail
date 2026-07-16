/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_archive_index @ 0x4319c0 */

004319c3        g_archive_index_records = nullptr
004319e2        if (archive_or_file_exists(path, 0) == 0)
004319e4        g_archive_index_records = nullptr
004319ee        int32_t eax_1
004319ee        eax_1.b = 1
004319f4        return 1
004319ff        void buffer
004319ff        load_file_bytes_fixed_size_from_archive_or_fs(path, &buffer, 0x7c)
00431a0d        xor_archive_bytes_in_place(0, &buffer, 0x7c)
00431a1c        int32_t var_74
00431a1c        struct ArchiveIndex* buffer_1 = allocate_tracked_memory(var_74, "Dat File Header")
00431a26        load_file_bytes_fixed_size_from_archive_or_fs(path, buffer_1, var_74)
00431a2f        xor_archive_bytes_in_place(0, buffer_1, var_74)
00431a34        struct ArchiveIndex* archive_index_records_1 = buffer_1
00431a39        g_archive_index_records = archive_index_records_1
00431a40        int32_t i = 0
00431a44        if (buffer_1->count s> 0)
00431a46        int32_t ecx_1 = 0
00431a48        void* esi_1 = *(&archive_index_records_1->entries + ecx_1)
00431a4c        ecx_1 += 0xc
00431a51        i += 1
00431a52        *(ecx_1 + archive_index_records_1 - 8) = esi_1 + archive_index_records_1
00431a56        archive_index_records_1 = g_archive_index_records
00431a5d        do while (i s< archive_index_records_1->count)
00431a6d        g_archive_file = fopen(path, "rb")
00431a72        int32_t* eax_3
00431a72        eax_3.b = 1
00431a7a        return 1
