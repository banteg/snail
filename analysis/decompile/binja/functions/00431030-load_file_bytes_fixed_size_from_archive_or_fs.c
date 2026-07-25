/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_file_bytes_fixed_size_from_archive_or_fs @ 0x431030 */

0043103f        update_loading_screen(&g_loading_bar)
00431044        struct ArchiveIndex* archive_index = g_archive_index_records
0043104b        int32_t archive_entry_count
0043104b        int32_t archive_entry_index
0043104b        if (archive_index != 0)
00431051        archive_entry_count = archive_index->count
00431053        archive_entry_index = 0
0043105b        char* requested_path
0043105b        if (archive_index == 0 || archive_entry_count s<= 0)
004311ab        requested_path = path
00431061        struct ArchiveEntry* archive_entry_cursor = &archive_index->entries
00431064        char* archive_path_cursor = archive_entry_cursor->path
00431066        requested_path = path
0043106d        char* requested_path_cursor = requested_path
0043106f        char archive_path_char = *archive_path_cursor
00431073        while (archive_path_char != 0)
00431075        char requested_path_char = *requested_path_cursor
00431079        if (requested_path_char == 0)
00431079        break
00431081        if (requested_path_char s>= 0x61 && requested_path_char s<= 0x7a)
00431083        requested_path_char -= 0x20
00431087        if (archive_path_char != requested_path_char)
00431087        break
00431089        archive_path_char = archive_path_cursor[1]
0043108c        requested_path_cursor = &requested_path_cursor[1]
0043108d        archive_path_cursor = &archive_path_cursor[1]
0043109a        if (*archive_path_cursor == 0 && *requested_path_cursor == 0)
004310b7        if (buffer == 0xffffffff)
004310d1        return g_archive_index_records->entries[archive_entry_index].data_offset
004310d4        if (buffer != 0)
0043114c        int32_t caller_archive_position = ftell(g_archive_file)
0043116e        fseek(g_archive_file, g_archive_index_records->entries[archive_entry_index].data_offset - caller_archive_position, 1)
00431184        fread(buffer, 1, byte_count, g_archive_file)
00431196        xor_archive_bytes_in_place(g_archive_index_records->entries[archive_entry_index].data_offset, buffer, byte_count)
004311aa        return buffer
004310df        void* allocated_buffer = allocate_tracked_memory(byte_count, requested_path)
004310ed        int32_t allocation_archive_position = ftell(g_archive_file)
0043110e        fseek(g_archive_file, g_archive_index_records->entries[archive_entry_index].data_offset - allocation_archive_position, 1)
0043111e        fread(allocated_buffer, 1, byte_count, g_archive_file)
00431130        xor_archive_bytes_in_place(g_archive_index_records->entries[archive_entry_index].data_offset, allocated_buffer, byte_count)
00431144        return allocated_buffer
004310a0        archive_entry_index += 1
004310a1        archive_entry_cursor = &archive_entry_cursor[1]
004310a6        do while (archive_entry_index s< archive_entry_count)
004311b8        struct File* filesystem_file = fopen(requested_path, "rb")
004311c4        if (filesystem_file == 0)
004311d0        char cwd_buffer[0x200]
004311d0        getcwd(&cwd_buffer, 0x200)
004311e0        report_messagef("WARNING:Cannot find file : %s (from %s)\n", requested_path, &cwd_buffer)
004311f4        return 0
004311f6        get_stream_length_preserve_position(filesystem_file)
004311fb        void* filesystem_output_buffer = buffer
00431213        if (filesystem_output_buffer == 0 || filesystem_output_buffer == 0xffffffff)
00431226        filesystem_output_buffer = allocate_tracked_memory(byte_count, path)
0043122d        fread(filesystem_output_buffer, 1, byte_count, filesystem_file)
00431233        fclose(filesystem_file)
00431247        return filesystem_output_buffer
