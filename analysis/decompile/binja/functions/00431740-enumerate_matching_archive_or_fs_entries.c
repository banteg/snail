/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: enumerate_matching_archive_or_fs_entries @ 0x431740 */

00431740        struct ArchiveIndex* archive_index_records_1 = g_archive_index_records
00431751        data_503320 = 0
00431757        if (archive_index_records_1 == 0)
00431896        void var_200
00431896        sub_496946(&var_200, 0x200)
004318ae        if (set_current_directory_with_drive_fallback(directory) == 1)
004318be        *out_count = data_503320
004318c6        return
004318d4        struct FileSearchData find_data
004318d4        int32_t handle = findfirst(pattern, &find_data)
004318e1        if (handle != 0xffffffff)
004318fb        var_304
004318fb        rstrcpy_checked_ascii(&names[data_503320], &var_304)
0043190c        data_503320 += 1
0043191c        if (findnext(handle, &find_data) != 0xffffffff)
00431950        int32_t i
0043192f        rstrcpy_checked_ascii(&names[data_503320], &var_304)
00431940        data_503320 += 1
00431945        i = findnext(handle, &find_data)
00431950        do while (i != 0xffffffff)
00431967        *out_count = data_503320
00431969        sub_48c18b(&var_200)
00431979        return
0043175f        int32_t var_31c = 0
00431765        if (archive_index_records_1->count s> 0)
0043176b        int32_t ebx
0043176b        int32_t var_330_1 = ebx
0043176d        int32_t var_320_1 = 0
00431869        bool cond:1_1
00431775        char* directory_1 = directory
0043177c        char* ecx_2 = *(&archive_index_records_1->entries + var_320_1)
00431780        char i_1 = *ecx_2
00431784        while (i_1 != 0)
00431786        archive_index_records_1.b = *directory_1
0043178a        if (archive_index_records_1.b == 0)
0043178a        break
00431792        if (archive_index_records_1.b s>= 0x61 && archive_index_records_1.b s<= 0x7a)
00431794        archive_index_records_1.b -= 0x20
00431798        if (i_1 != archive_index_records_1.b)
00431798        break
0043179a        i_1 = ecx_2[1]
0043179d        directory_1 = &directory_1[1]
0043179e        ecx_2 = &ecx_2[1]
004317af        if (*ecx_2 == 0x2f && *directory_1 == 0)
004317b5        archive_index_records_1.b = ecx_2[1]
004317bb        char* edi_1 = nullptr
004317bd        char* esi_1 = nullptr
004317c1        if (archive_index_records_1.b != 0)
004317ca        ebx.b = *(esi_1 + pattern)
004317cf        if (ebx.b == 0)
004317cf        break
004317d1        archive_index_records_1.b = *(edi_1 + &ecx_2[1])
004317ed        bool cond:2_1 = ascii_upper_if_lowercase(archive_index_records_1.b) == ascii_upper_if_lowercase(ebx.b)
004317ef        archive_index_records_1 = pattern
004317fc        if (not(cond:2_1) && *(esi_1 + archive_index_records_1) != 0x2a)
004317fc        break
0043180d        if (*(esi_1 + archive_index_records_1) == 0x2a && *(edi_1 + &ecx_2[1]) == *(esi_1 + archive_index_records_1 + 1))
0043180f        esi_1 = &esi_1[1]
00431813        edi_1 = &edi_1[1]
00431817        if (*(esi_1 + archive_index_records_1) != 0x2a)
00431819        esi_1 = &esi_1[1]
0043181e        do while (*(edi_1 + &ecx_2[1]) != 0)
00431824        if (*(edi_1 + &ecx_2[1]) == 0)
00431839        rstrcpy_checked_ascii(&names[data_503320], &ecx_2[1])
00431847        data_503320 += 1
0043184c        archive_index_records_1 = g_archive_index_records
0043185f        cond:1_1 = var_31c + 1 s< archive_index_records_1->count
00431861        var_31c += 1
00431865        var_320_1 += 0xc
00431869        do while (cond:1_1)
00431880        *out_count = data_503320
00431888        return
