/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: enumerate_matching_archive_or_fs_entries @ 0x431740 */

00431740        struct ArchiveIndex* archive_index = g_archive_index_records
00431751        g_enumerated_entry_count = 0
00431757        if (archive_index == 0)
00431896        char cwd_buffer[0x200]
00431896        getcwd(&cwd_buffer, 0x200)
004318ae        if (set_current_directory_with_drive_fallback(directory) == 1)
004318be        *out_count = g_enumerated_entry_count
004318c6        return
004318d4        struct FileSearchData find_data
004318d4        int32_t handle = findfirst(pattern, &find_data)
004318e1        if (handle != 0xffffffff)
004318fb        var_304
004318fb        rstrcpy_checked_ascii(&names[g_enumerated_entry_count], &var_304)
0043190c        g_enumerated_entry_count += 1
0043191c        if (findnext(handle, &find_data) != 0xffffffff)
00431950        int32_t i
0043192f        rstrcpy_checked_ascii(&names[g_enumerated_entry_count], &var_304)
00431940        g_enumerated_entry_count += 1
00431945        i = findnext(handle, &find_data)
00431950        do while (i != 0xffffffff)
00431967        *out_count = g_enumerated_entry_count
00431969        chdir(&cwd_buffer)
00431979        return
0043175f        int32_t archive_entry_index = 0
00431765        if (archive_index->count s> 0)
0043176b        char ebx
0043176b        char var_330_1 = ebx
0043176d        int32_t archive_entry_offset = 0
00431869        bool cond:1_1
00431775        char* directory_cursor = directory
0043177c        char* archive_path_cursor = *(&archive_index->entries + archive_entry_offset)
00431780        char archive_path_char = *archive_path_cursor
00431784        char* pattern_1
00431784        while (archive_path_char != 0)
00431786        pattern_1.b = *directory_cursor
0043178a        if (pattern_1.b == 0)
0043178a        break
00431792        if (pattern_1.b s>= 0x61 && pattern_1.b s<= 0x7a)
00431794        pattern_1.b -= 0x20
00431798        if (archive_path_char != pattern_1.b)
00431798        break
0043179a        archive_path_char = archive_path_cursor[1]
0043179d        directory_cursor = &directory_cursor[1]
0043179e        archive_path_cursor = &archive_path_cursor[1]
004317af        if (*archive_path_cursor == 0x2f && *directory_cursor == 0)
004317b5        pattern_1.b = archive_path_cursor[1]
004317bb        int32_t basename_index = 0
004317bd        int32_t pattern_index = 0
004317c1        if (pattern_1.b != 0)
004317ca        ebx = pattern[pattern_index]
004317cf        if (ebx == 0)
004317cf        break
004317d1        pattern_1.b = archive_path_cursor[1 + basename_index]
004317ed        bool cond:2_1 = ascii_upper_if_lowercase(pattern_1.b) == ascii_upper_if_lowercase(ebx)
004317ef        pattern_1 = pattern
004317fc        if (not(cond:2_1) && pattern_1[pattern_index] != 0x2a)
004317fc        break
0043180d        if (pattern_1[pattern_index] == 0x2a && archive_path_cursor[1 + basename_index] == pattern_1[pattern_index + 1])
0043180f        pattern_index += 1
00431813        basename_index += 1
00431817        if (pattern_1[pattern_index] != 0x2a)
00431819        pattern_index += 1
0043181e        do while (archive_path_cursor[1 + basename_index] != 0)
00431824        if (archive_path_cursor[1 + basename_index] == 0)
00431839        rstrcpy_checked_ascii(&names[g_enumerated_entry_count], &archive_path_cursor[1])
00431847        g_enumerated_entry_count += 1
0043184c        archive_index = g_archive_index_records
0043185f        cond:1_1 = archive_entry_index + 1 s< archive_index->count
00431861        archive_entry_index += 1
00431865        archive_entry_offset += 0xc
00431869        do while (cond:1_1)
00431880        *out_count = g_enumerated_entry_count
00431888        return
