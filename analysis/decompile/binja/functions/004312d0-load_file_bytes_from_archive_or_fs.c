/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_file_bytes_from_archive_or_fs @ 0x4312d0 */

004312df        update_loading_screen(&g_loading_bar)
004312e4        struct ArchiveIndex* archive_index_records_3 = g_archive_index_records
004312f3        if (archive_index_records_3 != 0)
004312f5        int32_t count = archive_index_records_3->count
004312f7        int32_t edi_1 = 0
004312fb        int32_t count_1 = count
004312ff        if (count s> 0)
00431301        struct ArchiveEntry (* ebx)[0x1] = &archive_index_records_3->entries
00431304        char* path_1 = (ebx - 4)->entries[0].path
00431306        char* path_2 = path
00431308        char i = *path_1
0043130c        if (i != 0)
0043130e        char eax_1 = *path_2
00431312        if (eax_1 == 0)
00431312        break
0043131a        if (eax_1 s>= 0x61 && eax_1 s<= 0x7a)
0043131c        eax_1 -= 0x20
00431320        if (i != eax_1)
00431320        break
00431322        i = path_1[1]
00431325        path_2 = &path_2[1]
00431326        path_1 = &path_1[1]
00431329        do while (i != 0)
0043132b        count = count_1
00431337        if (*path_1 == 0 && *path_2 == 0)
00431391        if (out_size != 0)
004313a0        *out_size = *(g_archive_index_records + ((edi_1 * 3 + 3) << 2))
004313ac        if (buffer == 0xffffffff)
004313c4        return g_archive_index_records->entries[edi_1].data_offset
004313c7        if (buffer != 0)
00431454        void* eax_13 = ftell(g_archive_file)
00431474        fseek(g_archive_file, g_archive_index_records->entries[edi_1].data_offset - eax_13, FILE_CURRENT)
0043148a        int32_t* edi_5 = (edi_1 * 3 + 3) << 2
00431494        sub_48b645(buffer, 1, *(edi_5 + g_archive_index_records), g_archive_file)
00431499        struct ArchiveIndex* archive_index_records_2 = g_archive_index_records
004314a8        xor_archive_bytes_in_place(archive_index_records_2->entries[edi_1].data_offset, buffer, *(edi_5 + archive_index_records_2))
004314bc        return buffer
004313d7        int32_t* esi_3 = (edi_1 * 3 + 3) << 2
004313df        void* eax_6 = allocate_tracked_memory(*(esi_3 + g_archive_index_records), path)
004313ec        void* eax_8 = ftell(g_archive_file)
0043140c        fseek(g_archive_file, g_archive_index_records->entries[edi_1].data_offset - eax_8, FILE_CURRENT)
00431425        sub_48b645(eax_6, 1, *(esi_3 + g_archive_index_records), g_archive_file)
0043142a        struct ArchiveIndex* archive_index_records_1 = g_archive_index_records
00431439        xor_archive_bytes_in_place(archive_index_records_1->entries[edi_1].data_offset, eax_6, *(esi_3 + archive_index_records_1))
0043144d        return eax_6
00431339        edi_1 += 1
0043133a        ebx = &ebx[1]
0043133f        do while (edi_1 s< count)
00431347        int32_t* file = fopen(path, "rb")
00431353        if (file == 0)
00431363        void var_200
00431363        sub_496946(&var_200, 0x200)
00431373        report_messagef("WARNING:Cannot find file : %s (from %s)\n", path, &var_200)
00431387        return 0
004314be        int32_t size = get_stream_length_preserve_position(file)
004314c3        void* buffer_1 = buffer
004314d6        if (buffer_1 == 0 || buffer_1 == 0xffffffff)
004314e2        buffer_1 = allocate_tracked_memory(size, path)
004314e9        sub_48b645(buffer_1, 1, size, file)
004314ef        fclose(file)
00431500        if (out_size != 0)
00431502        *out_size = size
00431510        return buffer_1
