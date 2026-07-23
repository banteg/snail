/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_frontend_level_by_mode_and_index @ 0x443650 */

00443666        char var_80[0x80]
00443666        switch (mode)
00443677        case 0
00443677        if (level_index s<= 0x32)
00443684        sprintf(&var_80, "Arcade%03i.txt", level_index)
00443691        if (level_index == 0x33)
004436ed        sprintf(&var_80, "ArcadeExtra000.txt")
004436cf        case 1
004436ed        sprintf(&var_80, "Challenge000.txt")
004436e7        case 2, 3
004436ed        sprintf(&var_80, "Arcade000.txt")
004436a9        case 4
004436a9        if (level_index s> 0x32)
00443684        sprintf(&var_80, "TimeTrialExtra%03i.txt", level_index - 0x32)
004436b6        sprintf(&var_80, "Arcade%03i.txt", level_index)
004436db        case 7
004436ed        sprintf(&var_80, "Tutorial.txt")
004436fc        load_level_definition_file(tracks, &var_80)
00443708        return
