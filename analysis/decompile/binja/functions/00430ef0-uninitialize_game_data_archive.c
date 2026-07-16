/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: uninitialize_game_data_archive @ 0x430ef0 */

00430ef6        free_tracked_memory(g_archive_data_base)
00430efb        struct ArchiveIndex* archive_index_records_1 = g_archive_index_records
00430f05        if (archive_index_records_1 != 0)
00430f0e        archive_index_records_1 = fclose(g_archive_file)
00430f16        g_archive_index_records = nullptr
00430f20        return archive_index_records_1
