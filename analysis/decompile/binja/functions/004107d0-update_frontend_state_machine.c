/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_frontend_state_machine @ 0x4107d0 */

004107d0        int32_t ebx
004107d0        int32_t var_4 = ebx
004107d1        int32_t ebp
004107d1        int32_t var_8 = ebp
004107d4        int32_t esi
004107d4        int32_t var_c = esi
004107d5        int32_t edi
004107d5        int32_t var_10 = edi
004107d8        player->redispatch_requested = 1
00410b30        struct TransformMatrix* source
004107e9        int32_t frontend_state = player->frontend_state
004107ef        player->redispatch_requested = 0
004107fd        switch (frontend_state)
00410914        case 0
00410914        source = update_new_game_menu(&g_game_base[0x4f2dc])
004108ba        case 1
004108ba        player->frontend_state = 0
004108c0        capture_mouse_cursor(&player->mouse_cursor)
004108cb        *(g_game_base + 0x4f2dc) = 0
004108dd        source = initialize_new_game_menu(&g_game_base[0x4f2dc])
004108ed        case 2
004108ed        player->frontend_state = 0
004108f3        capture_mouse_cursor(&player->mouse_cursor)
00410903        initialize_new_game_menu(&g_game_base[0x4f2dc])
00410914        source = update_new_game_menu(&g_game_base[0x4f2dc])
00410924        case 3
00410924        player->frontend_state = 5
0041092a        capture_mouse_cursor(&player->mouse_cursor)
0041093b        source = initialize_main_menu(&g_game_base[0x4f324])
0041094b        case 4
0041094b        player->frontend_state = 5
00410951        capture_mouse_cursor(&player->mouse_cursor)
00410961        initialize_main_menu(&g_game_base[0x4f324])
00410972        source = update_main_menu(&g_game_base[0x4f324])
00410972        case 5
00410972        source = update_main_menu(&g_game_base[0x4f324])
0041097c        case 6
0041097c        player->frontend_state = 7
00410992        initialize_options_menu(&g_game_base[0x4f388])
004109a2        source = update_options_menu(&g_game_base[0x4f388])
004109a2        case 7
004109a2        source = update_options_menu(&g_game_base[0x4f388])
004109b8        case 8
004109b8        initialize_exit_prompt(&g_game_base[0x4f3ac])
004109bd        player->frontend_state = 9
004109d3        source = update_completion_screen(&g_game_base[0x4f3ac])
004109d3        case 9
004109d3        source = update_completion_screen(&g_game_base[0x4f3ac])
00410809        case 0xa
00410809        *(g_game_base + 0x104712c) = 0
0041081b        initialize_subgame(&g_game_base[0x74618])
00410820        player->frontend_state = 0xb
00410836        source = update_subgame(&g_game_base[0x74618])
00410836        case 0xb
00410836        source = update_subgame(&g_game_base[0x74618])
00410850        case 0xc
00410850        source = initialize_intro_screen(&g_game_base[0x4f400], "Intro/Intro.txt")
00410855        player->frontend_state = 0xd
00410870        case 0xd
00410870        source = update_intro_screen(&g_game_base[0x4f400])
0041088b        case 0xe
0041088b        source = initialize_intro_screen(&g_game_base[0x4f400], "Intro/Credits.txt")
00410890        player->frontend_state = 0xf
004108aa        case 0xf
004108aa        source = update_intro_screen(&g_game_base[0x4f400])
004109f1        case 0x12
004109f1        source = initialize_high_score_screen(&g_game_base[0x12e6e50], g_high_score_selected_bank, 0xffffffff)
004109f6        player->frontend_state = 0x13
00410a11        case 0x13
00410a11        source = update_high_score_screen(&g_game_base[0x12e6e50])
00410a1b        case 0x14
00410a1b        char* game_base_1 = g_game_base
00410a34        source = initialize_high_score_screen(&game_base_1[0x12e6e50], *(game_base_1 + 0x314), *(game_base_1 + 0x310))
00410a39        player->frontend_state = 0x15
00410a53        case 0x15
00410a53        source = update_high_score_screen(&g_game_base[0x12e6e50])
00410a63        case 0x19
00410a63        *(g_game_base + 0x38) = 1
00410a7b        case 0x1a
00410a7b        source = destroy_subgame(&g_game_base[0x74618])
00410ac1        label_410ac1:
00410ac1        int32_t saved_frontend_state = player->saved_frontend_state
00410aca        if (saved_frontend_state != 0xffffffff)
00410acc        player->frontend_state = saved_frontend_state
00410a8d        case 0x1b
00410a8d        destroy_subgame(&g_game_base[0x74618])
00410abc        label_410abc:
00410abc        source = initialize_subgame(&g_game_base[0x74618])
00410abc        goto label_410ac1
00410aa0        case 0x1c
00410aa0        destroy_subgame(&g_game_base[0x74618])
00410aaa        *(g_game_base + 0x12e55e0) = 0
00410aaa        goto label_410abc
00410ad4        case 0x1d
00410ad4        player->frontend_state = 0x1e
00410aea        initialize_thanks_for_playing_screen(&g_game_base[0x12d4624])
00410afa        source = update_thanks_for_playing_screen(&g_game_base[0x12d4624])
00410afa        case 0x1e
00410afa        source = update_thanks_for_playing_screen(&g_game_base[0x12d4624])
00410b01        case 0x1f
00410b01        player->frontend_state = 0x20
00410b13        initialize_help_screen(&g_game_base[0x12d4620])
00410b24        source = update_help_screen(&g_game_base[0x12d4620])
00410b24        case 0x20
00410b24        source = update_help_screen(&g_game_base[0x12d4620])
00410b30        do while (player->redispatch_requested == 1)
00410b36        struct GameInput* game_input = player->game_input
00410b4a        player->mouse_cursor.saved_x = fconvert.s(fconvert.t(game_input->input.authored_x))
00410b50        long double x87_r7_1 = fconvert.t(game_input->input.authored_y)
00410b58        struct FrameTransformMatrix* var_14_2 = &player->transform
00410b59        __builtin_memcpy(&player->camera.transform, &player->transform, 0x40)
00410b5b        player->mouse_cursor.saved_y = fconvert.s(x87_r7_1)
00410b67        invert_matrix_from_source(&player->camera.view_matrix, source)
00410b70        return 0
