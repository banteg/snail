/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_subgame_camera @ 0x446020 */

00446036        int32_t subgame_state = game->subgame_state
00446042        struct TransformMatrix from
00446042        __builtin_memcpy(&from, &g_game_base[0x15c], 0x40)
00446047        game->_pad_00[1] = 0
0044604b        struct TransformMatrix var_80
0044604b        if (subgame_state != 1)
00446078        update_cameraman(&game->__offset(0x3bb964).d)
00446085        if (game->__offset(0x3bfa4c).d == 0)
004460bb        int32_t edx_2 = game->__offset(0x3bba2c).d
004460c1        __builtin_memcpy(&var_80, &game->__offset(0x3bb964).d, 0x40)
004460c9        game->_pad_00[1] = game->__offset(0x3bba30).b
004460d1        *(g_game_base + 0x284) = edx_2
00446093        game->_pad_00[1] = game->__offset(0x3bfa98).b
00446096        char* game_base_1 = g_game_base
004460a4        __builtin_memcpy(&var_80, &game->__offset(0x3bfa50).d, 0x40)
004460a6        *(game_base_1 + 0x284) = 0x42dc0000
00446051        set_matrix_identity(&var_80)
0044605c        var_80.position.y = 0x40400000
00446064        *(g_game_base + 0x284) = 0x42dc0000
004460d7        uint8_t result = game->_pad_00[1]
004460dc        if (result == 0)
00446103        char* game_base_2 = g_game_base
0044610d        float alpha
0044610d        __builtin_strncpy(&alpha, "fff?", 4)
0044612c        return linear_interpolate_matrix(&game_base_2[0x15c], &from, &var_80, alpha)
004460f3        __builtin_memcpy(&g_game_base[0x15c], &var_80, 0x40)
004460f6        game->_pad_00[1] = 0
00446102        return result
