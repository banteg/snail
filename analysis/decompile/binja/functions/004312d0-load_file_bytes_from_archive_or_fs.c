/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_file_bytes_from_archive_or_fs @ 0x4312d0 */

004312df        update_loading_screen(&g_loading_bar)
004312e4        struct ArchiveIndex* archive_index = g_archive_index_records
004312f3        if (archive_index != 0)
004312f5        int32_t count = archive_index->count
004312f7        int32_t archive_entry_index = 0
004312fb        int32_t count_1 = count
004312ff        if (count s> 0)
00431301        struct ArchiveEntry* archive_entry_cursor = &archive_index->entries
00431304        char* archive_path_cursor = archive_entry_cursor->path
00431306        char* requested_path_cursor = path
00431308        char archive_path_char = *archive_path_cursor
0043130c        if (archive_path_char != 0)
0043130e        char requested_path_char = *requested_path_cursor
00431312        if (requested_path_char == 0)
00431312        break
0043131a        if (requested_path_char s>= 0x61 && requested_path_char s<= 0x7a)
0043131c        requested_path_char -= 0x20
00431320        if (archive_path_char != requested_path_char)
00431320        break
00431322        archive_path_char = archive_path_cursor[1]
00431325        requested_path_cursor = &requested_path_cursor[1]
00431326        archive_path_cursor = &archive_path_cursor[1]
00431329        do while (archive_path_char != 0)
0043132b        count = count_1
00431337        if (*archive_path_cursor == 0 && *requested_path_cursor == 0)
00431391        if (out_size != 0)
004313a0        *out_size = *(g_archive_index_records + ((archive_entry_index * 3 + 3) << 2))
004313ac        if (buffer == 0xffffffff)
004313c4        return g_archive_index_records->entries[archive_entry_index].data_offset
004313c7        if (buffer != 0)
00431454        int32_t caller_archive_position = ftell(g_archive_file)
00431474        fseek(g_archive_file, g_archive_index_records->entries[archive_entry_index].data_offset - caller_archive_position, 1)
0043148a        int32_t caller_byte_count_offset = (archive_entry_index * 3 + 3) << 2
00431494        fread(buffer, 1, *(caller_byte_count_offset + g_archive_index_records), g_archive_file)
00431499        struct ArchiveIndex* archive_index_records_2 = g_archive_index_records
004314a8        xor_archive_bytes_in_place(archive_index_records_2->entries[archive_entry_index].data_offset, buffer, *(caller_byte_count_offset + archive_index_records_2))
004314bc        return buffer
004313d7        int32_t allocation_byte_count_offset = (archive_entry_index * 3 + 3) << 2
004313df        void* tracked_memory = allocate_tracked_memory(*(allocation_byte_count_offset + g_archive_index_records), path)
004313ec        int32_t allocation_archive_position = ftell(g_archive_file)
0043140c        fseek(g_archive_file, g_archive_index_records->entries[archive_entry_index].data_offset - allocation_archive_position, 1)
00431425        fread(tracked_memory, 1, *(allocation_byte_count_offset + g_archive_index_records), g_archive_file)
0043142a        struct ArchiveIndex* archive_index_records_1 = g_archive_index_records
00431439        xor_archive_bytes_in_place(archive_index_records_1->entries[archive_entry_index].data_offset, tracked_memory, *(allocation_byte_count_offset + archive_index_records_1))
0043144d        return tracked_memory
00431339        archive_entry_index += 1
0043133a        archive_entry_cursor = &archive_entry_cursor[1]
0043133f        do while (archive_entry_index s< count)
00431347        struct File* filesystem_file = fopen(path, "rb")
00431353        if (filesystem_file == 0)
00431363        char cwd_buffer[0x200]
00431363        getcwd(&cwd_buffer, 0x200)
00431373        report_messagef("WARNING:Cannot find file : %s (from %s)\n", path, &cwd_buffer)
00431387        return 0
004314be        int32_t filesystem_byte_count = get_stream_length_preserve_position(filesystem_file)
004314c3        void* filesystem_output_buffer = buffer
004314d6        if (filesystem_output_buffer == 0 || filesystem_output_buffer == 0xffffffff)
004314e2        filesystem_output_buffer = allocate_tracked_memory(filesystem_byte_count, path)
004314e9        fread(filesystem_output_buffer, 1, filesystem_byte_count, filesystem_file)
004314ef        fclose(filesystem_file)
00431500        if (out_size != 0)
00431502        *out_size = filesystem_byte_count
00431510        return filesystem_output_buffer
