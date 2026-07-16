/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: archive_or_file_exists @ 0x430fd0 */

00430fe0        if (g_archive_index_records == 0 || force_filesystem != 0)
0043100f        int32_t* eax_5 = fopen(path, "rb")
00431019        if (eax_5 == 0)
0043101b        int32_t* eax_6
0043101b        eax_6.b = 0
0043101e        return 0
00431020        fclose(eax_5)
00430ff1        if (find_archive_entry(path) == 0)
00430ff9        report_warningf("Missing Dat File %s", path)
00431001        int32_t eax_3
00431001        eax_3.b = 0
00431004        return 0
00431028        struct ArchiveEntry* eax_7
00431028        eax_7.b = 1
0043102b        return 1
