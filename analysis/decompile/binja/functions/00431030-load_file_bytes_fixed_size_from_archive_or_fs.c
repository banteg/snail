/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_file_bytes_fixed_size_from_archive_or_fs @ 0x431030 */

0043103f        update_loading_screen(&g_loading_bar)
00431044        struct ArchiveIndex* archive_index_records_1 = g_archive_index_records
0043104b        int32_t count
0043104b        int32_t ebp_1
0043104b        if (archive_index_records_1 != 0)
00431051        count = archive_index_records_1->count
00431053        ebp_1 = 0
0043105b        char* name
0043105b        if (archive_index_records_1 == 0 || count s<= 0)
004311ab        name = path
00431061        struct ArchiveEntry (* edi_1)[0x1] = &archive_index_records_1->entries
00431064        char* path_1 = (edi_1 - 4)->entries[0].path
00431066        name = path
0043106d        char* name_1 = name
0043106f        char i = *path_1
00431073        while (i != 0)
00431075        char eax = *name_1
00431079        if (eax == 0)
00431079        break
00431081        if (eax s>= 0x61 && eax s<= 0x7a)
00431083        eax -= 0x20
00431087        if (i != eax)
00431087        break
00431089        i = path_1[1]
0043108c        name_1 = &name_1[1]
0043108d        path_1 = &path_1[1]
0043109a        if (*path_1 == 0 && *name_1 == 0)
004310b7        if (buffer == 0xffffffff)
004310d1        return g_archive_index_records->entries[ebp_1].data_offset
004310d4        if (buffer != 0)
0043114c        void* eax_8 = ftell(g_archive_file)
0043116e        fseek(g_archive_file, g_archive_index_records->entries[ebp_1].data_offset - eax_8, FILE_CURRENT)
00431184        sub_48b645(buffer, 1, byte_count, g_archive_file)
00431196        xor_archive_bytes_in_place(g_archive_index_records->entries[ebp_1].data_offset, buffer, byte_count)
004311aa        return buffer
004310df        void* eax_3 = allocate_tracked_memory(byte_count, name)
004310ed        void* eax_4 = ftell(g_archive_file)
0043110e        fseek(g_archive_file, g_archive_index_records->entries[ebp_1].data_offset - eax_4, FILE_CURRENT)
0043111e        sub_48b645(eax_3, 1, byte_count, g_archive_file)
00431130        xor_archive_bytes_in_place(g_archive_index_records->entries[ebp_1].data_offset, eax_3, byte_count)
00431144        return eax_3
004310a0        ebp_1 += 1
004310a1        edi_1 = &edi_1[1]
004310a6        do while (ebp_1 s< count)
004311b8        int32_t* file = fopen(name, "rb")
004311c4        if (file == 0)
004311d0        void var_200
004311d0        sub_496946(&var_200, 0x200)
004311e0        report_messagef("WARNING:Cannot find file : %s (from %s)\n", name, &var_200)
004311f4        return 0
004311f6        get_stream_length_preserve_position(file)
004311fb        void* buffer_1 = buffer
00431213        if (buffer_1 == 0 || buffer_1 == 0xffffffff)
00431226        buffer_1 = allocate_tracked_memory(byte_count, path)
0043122d        sub_48b645(buffer_1, 1, byte_count, file)
00431233        fclose(file)
00431247        return buffer_1
