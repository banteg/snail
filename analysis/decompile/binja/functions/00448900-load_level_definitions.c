/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_level_definitions @ 0x448900 */

00448905        chkstk(0x4004)
0044891f        EnumeratedEntryName names[0x80]
0044891f        enumerate_matching_archive_or_fs_entries("Levels", "*.txt", &__return_addr, &names)
0044892b        int32_t esi = 0
0044892f        if (__return_addr s<= 0)
0044892f        return
00448932        EnumeratedEntryName (* filename)[0x80] = &names
00448943        load_level_definition_file(&g_game_base->subgame.level_definition_scratch, filename)
0044894c        esi += 1
0044894d        filename = &(*filename)[1]
00448955        do while (esi s< __return_addr)
0044895f        return
