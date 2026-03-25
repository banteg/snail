/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_keyboard_input @ 0x44b870 */

0044b870        int32_t* edx_1 = data_777d50
0044b87d        if (edx_1 != 0)
0044b894        __builtin_memcpy(0x777b4c, 0x777c4c, 0x100)
0044b8a0        __builtin_memset(0x777c4c, 0, 0x100)
0044b8b4        if ((*(*edx_1 + 0x24))(edx_1, 0x100, 0x777c4c) s>= 0)
0044b90c        int32_t esi_1 = 0
0044b913        int32_t var_4_1 = 0
0044b917        int32_t var_8_1 = 0
0044b925        if (is_key_down(0xc8) != 0)
0044b927        esi_1 = 1
0044b92c        var_8_1 = 0xbf800000
0044b943        if (is_key_down(0xd0) != 0)
0044b945        esi_1 |= 2
0044b948        var_8_1 = 0x3f800000
0044b95f        if (is_key_down(0xcb) != 0)
0044b961        esi_1 |= 4
0044b964        var_4_1 = 0xbf800000
0044b97b        if (is_key_down(0xcd) != 0)
0044b97d        esi_1 |= 8
0044b980        var_4_1 = 0x3f800000
0044b994        if (is_key_down(0x1d) != 0)
0044b996        esi_1 |= 0x10
0044b9a5        if (is_key_down(0x2c) != 0)
0044b9a7        esi_1 |= 0x100
0044b9b9        if (is_key_down(0x2e) != 0)
0044b9bb        esi_1 |= 0x200
0044b9cd        if (is_key_down(0x1f) != 0)
0044b9cf        esi_1 |= 0x80
0044b9e1        if (is_key_down(0x2d) != 0)
0044b9e3        esi_1 |= 0x40
0044b9f2        if (is_key_down(0x38) != 0)
0044b9f4        esi_1 |= 0x4000000
0044ba06        if (is_key_down(0x38) != 0)
0044ba08        esi_1 |= 0x20
0044ba17        if (is_key_down(0x2c) != 0)
0044ba19        esi_1 |= 0x20000
0044ba2b        if (is_key_down(0x2e) != 0)
0044ba2d        esi_1 |= 0x1000000
0044ba3f        if (is_key_down(0x39) != 0)
0044ba41        esi_1 |= 0x80000
0044ba53        if (is_key_down(0x3c) != 0)
0044ba55        esi_1 |= 0x400
0044ba67        if (is_key_down(0x39) != 0)
0044ba69        esi_1 |= 0x2000
0044ba7b        if (is_key_down(0x11) != 0)
0044ba7d        esi_1 |= &__dos_header
0044ba8f        if (is_key_down(0x2d) != 0)
0044ba91        esi_1 |= 0x40000
0044baa3        if (is_key_down(0x1f) != 0)
0044baa5        esi_1 |= 0x200000
0044bab7        if (is_key_down(0x12) != 0)
0044bab9        esi_1 |= 0x800000
0044bacb        if (is_key_down(0x1d) != 0)
0044bacd        esi_1 |= 0x10000
0044badf        if (is_key_down(0x2a) != 0)
0044bae1        esi_1 |= 0x2000000
0044baf2        set_input_controller_slot0_button_axes(esi_1, var_4_1, var_8_1)
0044b8b6        int32_t* eax_3 = data_777d50
0044b8c6        int32_t i
0044b8c6        int32_t* eax_4
0044b8be        i = (*(*eax_3 + 0x1c))(eax_3)
0044b8c6        while (i == 0x8007001e)
0044b8c8        eax_4 = data_777d50
0044b8d0        i = (*(*eax_4 + 0x1c))(eax_4)
0044b8e6        if (i == 0x80070005 || i == 0x8007000c)
0044b8f8        __builtin_memset(0x777c4c, 0, 0x100)
0044b904        __builtin_memset(0x777b4c, 0, 0x100)
0044bb01        return 0
