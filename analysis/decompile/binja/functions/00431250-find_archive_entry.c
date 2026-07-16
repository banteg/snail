/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: find_archive_entry @ 0x431250 */

00431250        int32_t count_2
00431250        int32_t count_1 = count_2
00431255        struct ArchiveIndex* archive_index_records_1 = g_archive_index_records
0043125d        if (archive_index_records_1 != 0)
0043125f        int32_t count = archive_index_records_1->count
00431261        int32_t ebx_1 = 0
00431265        count_1 = count
00431269        if (count s> 0)
0043126f        struct ArchiveEntry (* edi)[0x1] = &archive_index_records_1->entries
00431272        char* path_1 = (edi - 4)->entries[0].path
00431274        char* path_2 = path
00431276        char i = *path_1
0043127a        if (i != 0)
0043127c        char eax_1 = *path_2
00431280        if (eax_1 == 0)
00431280        break
00431288        if (eax_1 s>= 0x61 && eax_1 s<= 0x7a)
0043128a        eax_1 -= 0x20
0043128e        if (i != eax_1)
0043128e        break
00431290        i = path_1[1]
00431293        path_2 = &path_2[1]
00431294        path_1 = &path_1[1]
00431297        do while (i != 0)
00431299        count = count_1
004312a5        if (*path_1 == 0 && *path_2 == 0)
004312c9        return &(&g_archive_index_records->entries)[ebx_1]
004312a7        ebx_1 += 1
004312a8        edi = &edi[1]
004312ad        do while (ebx_1 s< count)
004312b6        return 0
