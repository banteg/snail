/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_subgame_camera @ 0x446020 */

00446036        int32_t eax = *(arg1 + 0x3c)
00446042        struct TransformMatrix from
00446042        __builtin_memcpy(&from, data_4df904 + 0x15c, 0x40)
00446047        *(arg1 + 1) = 0
0044604b        struct TransformMatrix var_80
0044604b        int32_t result
0044604b        if (eax != 1)
00446078        update_cameraman(arg1 + 0x3bb964)
00446085        if (*(arg1 + 0x3bfa4c) == 0)
004460bb        int32_t edx_2 = *(arg1 + 0x3bba2c)
004460c1        __builtin_memcpy(&var_80, arg1 + 0x3bb964, 0x40)
004460c9        *(arg1 + 1) = *(arg1 + 0x3bba30)
004460d1        *(data_4df904 + 0x284) = edx_2
00446093        *(arg1 + 1) = *(arg1 + 0x3bfa98)
00446096        result = data_4df904
004460a4        __builtin_memcpy(&var_80, arg1 + 0x3bfa50, 0x40)
004460a6        *(result + 0x284) = 0x42dc0000
00446051        set_matrix_identity(&var_80)
0044605c        var_80.position.y = 0x40400000
00446064        *(data_4df904 + 0x284) = 0x42dc0000
004460d7        result.b = *(arg1 + 1)
004460dc        if (result.b == 0)
00446103        void* ecx_5 = data_4df904
0044610d        float alpha
0044610d        __builtin_strncpy(&alpha, "fff?", 4)
0044612c        return linear_interpolate_matrix(ecx_5 + 0x15c, &from, &var_80, alpha)
004460f3        __builtin_memcpy(data_4df904 + 0x15c, &var_80, 0x40)
004460f6        *(arg1 + 1) = 0
00446102        return result
