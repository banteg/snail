/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_game_data_archive @ 0x430e40 */

00430e4b        data_53c7f4 = 0
00430e51        data_5108b4 = 0
00430e57        initialize_enemy_manager(&data_5108c0)
00430e61        data_5108b8 = 0
00430e67        data_50339c = 0
00430e6d        data_53c7f5 = 0
00430e73        char eax = load_archive_index("SnailMail.dat")
00430e7d        if (eax == 0)
00430e83        return eax
00430e84        sub_432d40()
00430ea2        data_53c7ec = allocate_tracked_memory(&__dos_header, "Scratch Pad")
00430eac        data_53c7e8 = allocate_tracked_memory(0x64000, "Music Memory Buffer")
00430eb4        int32_t* i = &data_503340
00430edc        while (i s< 0x5033b0)
00430ec3        i[-1] = 0
00430ec6        *i = 0
00430ec8        i[1] = 0
00430ecb        i[4] = 0x43a00000
00430ece        i[5] = 0x43700000
00430ed1        i[6] = 0
00430ed4        i = &i[0xe]
00430ee3        RECT rect
00430ee3        GetClipCursor(&rect)
00430ee9        BOOL eax_3
00430ee9        eax_3.b = 1
00430eef        return eax_3
