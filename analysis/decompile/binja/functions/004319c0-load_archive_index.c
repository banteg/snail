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
004319ff        struct SerializedArchiveHeader serialized_header
004319ff        load_file_bytes_fixed_size_from_archive_or_fs(path, &serialized_header, 0x7c)
00431a0d        xor_archive_bytes_in_place(0, &serialized_header, 0x7c)
00431a12        int32_t index_byte_count = serialized_header.entries[0].data_offset
00431a1c        struct SerializedArchiveIndex* allocated_serialized_index = allocate_tracked_memory(index_byte_count, "Dat File Header")
00431a26        load_file_bytes_fixed_size_from_archive_or_fs(path, allocated_serialized_index, index_byte_count)
00431a2f        xor_archive_bytes_in_place(0, allocated_serialized_index, index_byte_count)
00431a34        struct ArchiveIndex* archive_index = allocated_serialized_index
00431a39        g_archive_index_records = archive_index
00431a40        int32_t entry_index = 0
00431a44        if (allocated_serialized_index->count s> 0)
00431a46        int32_t entry_byte_offset = 0
00431a48        int32_t serialized_path_offset = *(&archive_index->entries + entry_byte_offset)
00431a4c        entry_byte_offset += 0xc
00431a51        entry_index += 1
00431a52        *(entry_byte_offset + archive_index - 8) = serialized_path_offset + archive_index
00431a56        archive_index = g_archive_index_records
00431a5d        do while (entry_index s< archive_index->count)
00431a6d        g_archive_file = fopen(path, "rb")
00431a72        struct File* eax_2
00431a72        eax_2.b = 1
00431a7a        return 1
