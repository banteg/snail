/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: exit_high_score_screen @ 0x417b50 */

00417b50        char* game_base_1 = g_game_base
00417b68        if (*(game_base_1 + 0x74658) == 0)
00417b6a        *(game_base_1 + 0x1b8) = 2
00417b75        *(g_game_base + 0x12e55e0) = 2
00417b80        g_game_base[0x30c] = 1
00417b86        game_base_1 = g_game_base
00417b94        if (*(game_base_1 + 0x74658) != 1)
00417b94        return
00417b96        *(game_base_1 + 0x1b8) = 0xa
00417ba5        *(g_game_base + 0x12e55e0) = 2
00417bb1        g_game_base[0x30c] = 1
00417bb7        return
