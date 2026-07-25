/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: find_archive_entry @ 0x431250 */

00431250        int32_t entry_count_snapshot_1
00431250        int32_t entry_count_snapshot = entry_count_snapshot_1
00431255        struct ArchiveIndex* archive_index = g_archive_index_records
0043125d        if (archive_index != 0)
0043125f        int32_t archive_entry_count = archive_index->count
00431261        int32_t archive_entry_index = 0
00431265        entry_count_snapshot = archive_entry_count
00431269        if (archive_entry_count s> 0)
0043126f        struct ArchiveEntry* archive_entry_cursor = &archive_index->entries
00431272        char* archive_path_cursor = archive_entry_cursor->path
00431274        char* requested_path_cursor = path
00431276        char archive_path_char = *archive_path_cursor
0043127a        if (archive_path_char != 0)
0043127c        char requested_path_char = *requested_path_cursor
00431280        if (requested_path_char == 0)
00431280        break
00431288        if (requested_path_char s>= 0x61 && requested_path_char s<= 0x7a)
0043128a        requested_path_char -= 0x20
0043128e        if (archive_path_char != requested_path_char)
0043128e        break
00431290        archive_path_char = archive_path_cursor[1]
00431293        requested_path_cursor = &requested_path_cursor[1]
00431294        archive_path_cursor = &archive_path_cursor[1]
00431297        do while (archive_path_char != 0)
00431299        archive_entry_count = entry_count_snapshot
004312a5        if (*archive_path_cursor == 0 && *requested_path_cursor == 0)
004312c9        return &(&g_archive_index_records->entries)[archive_entry_index]
004312a7        archive_entry_index += 1
004312a8        archive_entry_cursor = &archive_entry_cursor[1]
004312ad        do while (archive_entry_index s< archive_entry_count)
004312b6        return 0
