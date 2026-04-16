/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_frontend_level_by_mode_and_index @ 0x443650 */

00443666        void var_80
00443666        switch (arg2)
00443677        case 0
00443677        if (arg3 s<= 0x32)
00443679        int32_t var_88_1 = arg3
00443684        sub_48b32c(&var_80, "Arcade%03i.txt")
00443691        if (arg3 == 0x33)
004436ed        sub_48b32c(&var_80, "ArcadeExtra000.txt")
004436cf        case 1
004436ed        sub_48b32c(&var_80, "Challenge000.txt")
004436e7        case 2, 3
004436ed        sub_48b32c(&var_80, "Arcade000.txt")
004436a9        case 4
004436a9        if (arg3 s> 0x32)
004436c3        int32_t var_88_4 = arg3 - 0x32
00443684        sub_48b32c(&var_80, "TimeTrialExtra%03i.txt")
004436ab        int32_t var_88_3 = arg3
004436b6        sub_48b32c(&var_80, "Arcade%03i.txt")
004436db        case 7
004436ed        sub_48b32c(&var_80, "Tutorial.txt")
00443708        return load_level_definition_file(arg1, &var_80)
