/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_frontend_state_machine @ 0x4107d0 */

004107d8        *(arg1 + 0x1e8) = 1
004107e9        int32_t eax_1 = *(arg1 + 0x94)
004107ef        *(arg1 + 0x1e8) = 0
004107fd        switch (eax_1)
00410914        case 0
00410914        update_new_game_menu(data_4df904 + 0x4f2dc)
004108ba        case 1
004108ba        *(arg1 + 0x94) = 0
004108c0        capture_mouse_cursor(arg1 + 0x16c)
004108cb        *(data_4df904 + 0x4f2dc) = 0
004108dd        initialize_new_game_menu(data_4df904 + 0x4f2dc)
004108ed        case 2
004108ed        *(arg1 + 0x94) = 0
004108f3        capture_mouse_cursor(arg1 + 0x16c)
00410903        initialize_new_game_menu(data_4df904 + 0x4f2dc)
00410914        update_new_game_menu(data_4df904 + 0x4f2dc)
00410924        case 3
00410924        *(arg1 + 0x94) = 5
0041092a        capture_mouse_cursor(arg1 + 0x16c)
0041093b        initialize_main_menu(data_4df904 + 0x4f324)
0041094b        case 4
0041094b        *(arg1 + 0x94) = 5
00410951        capture_mouse_cursor(arg1 + 0x16c)
00410961        initialize_main_menu(data_4df904 + 0x4f324)
00410972        update_main_menu(data_4df904 + 0x4f324)
00410972        case 5
00410972        update_main_menu(data_4df904 + 0x4f324)
0041097c        case 6
0041097c        *(arg1 + 0x94) = 7
00410992        initialize_options_menu(data_4df904 + 0x4f388)
004109a2        update_options_menu(data_4df904 + 0x4f388)
004109a2        case 7
004109a2        update_options_menu(data_4df904 + 0x4f388)
004109b8        case 8
004109b8        initialize_exit_prompt(data_4df904 + 0x4f3ac)
004109bd        *(arg1 + 0x94) = 9
004109d3        update_completion_screen(data_4df904 + 0x4f3ac)
004109d3        case 9
004109d3        update_completion_screen(data_4df904 + 0x4f3ac)
00410809        case 0xa
00410809        *(data_4df904 + 0x104712c) = 0
0041081b        initialize_subgame(data_4df904 + 0x74618)
00410820        *(arg1 + 0x94) = 0xb
00410836        update_subgame(data_4df904 + 0x74618)
00410836        case 0xb
00410836        update_subgame(data_4df904 + 0x74618)
00410850        case 0xc
00410850        initialize_intro_screen(data_4df904 + 0x4f400, "Intro/Intro.txt")
00410855        *(arg1 + 0x94) = 0xd
00410870        case 0xd
00410870        update_intro_screen(data_4df904 + 0x4f400)
0041088b        case 0xe
0041088b        initialize_intro_screen(data_4df904 + 0x4f400, "Intro/Credits.txt")
00410890        *(arg1 + 0x94) = 0xf
004108aa        case 0xf
004108aa        update_intro_screen(data_4df904 + 0x4f400)
004109f1        case 0x12
004109f1        initialize_high_score_screen(data_4df904 + 0x12e6e50, data_4df9c0, 0xffffffff)
004109f6        *(arg1 + 0x94) = 0x13
00410a11        case 0x13
00410a11        update_high_score_screen(data_4df904 + 0x12e6e50)
00410a1b        case 0x14
00410a1b        void* eax_9 = data_4df904
00410a34        initialize_high_score_screen(eax_9 + 0x12e6e50, *(eax_9 + 0x314), *(eax_9 + 0x310))
00410a39        *(arg1 + 0x94) = 0x15
00410a53        case 0x15
00410a53        update_high_score_screen(data_4df904 + 0x12e6e50)
00410a63        case 0x19
00410a63        *(data_4df904 + 0x38) = 1
00410a7b        case 0x1a
00410a7b        destroy_subgame(data_4df904 + 0x74618)
00410ac1        label_410ac1:
00410ac1        int32_t eax_13 = *(arg1 + 0x98)
00410aca        if (eax_13 != 0xffffffff)
00410acc        *(arg1 + 0x94) = eax_13
00410a8d        case 0x1b
00410a8d        destroy_subgame(data_4df904 + 0x74618)
00410abc        label_410abc:
00410abc        initialize_subgame(data_4df904 + 0x74618)
00410abc        goto label_410ac1
00410aa0        case 0x1c
00410aa0        destroy_subgame(data_4df904 + 0x74618)
00410aaa        *(data_4df904 + 0x12e55e0) = 0
00410aaa        goto label_410abc
00410ad4        case 0x1d
00410ad4        *(arg1 + 0x94) = 0x1e
00410aea        initialize_thanks_for_playing_screen(data_4df904 + 0x12d4624)
00410afa        update_thanks_for_playing_screen(data_4df904 + 0x12d4624)
00410afa        case 0x1e
00410afa        update_thanks_for_playing_screen(data_4df904 + 0x12d4624)
00410b01        case 0x1f
00410b01        *(arg1 + 0x94) = 0x20
00410b13        initialize_help_screen(data_4df904 + 0x12d4620)
00410b24        update_help_screen(data_4df904 + 0x12d4620)
00410b24        case 0x20
00410b24        update_help_screen(data_4df904 + 0x12d4620)
00410b30        do while (*(arg1 + 0x1e8) == 1)
00410b36        void* eax_15 = *(arg1 + 0x168)
00410b4a        *(arg1 + 0x178) = fconvert.s(fconvert.t(*(eax_15 + 0x60)))
00410b50        long double x87_r7_1 = fconvert.t(*(eax_15 + 0x64))
00410b59        __builtin_memcpy(arg1 + 0xd8, arg1 + 0x38, 0x40)
00410b5b        *(arg1 + 0x17c) = fconvert.s(x87_r7_1)
00410b67        invert_matrix_from_source(arg1 + 0x120, arg1 + 0x38)
00410b70        return 0
