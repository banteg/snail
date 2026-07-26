/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_keyboard_input @ 0x44b870 */

0044b870        struct IDirectInputDevice8A* keyboard_device_3 = g_keyboard_device
0044b87d        if (keyboard_device_3 != 0)
0044b894        __builtin_memcpy(&g_keyboard_previous_state, &g_keyboard_current_state, 0x100)
0044b8a0        __builtin_memset(&g_keyboard_current_state, 0, 0x100)
0044b8b4        if (keyboard_device_3->lpVtbl->GetDeviceState(keyboard_device_3, 0x100, &g_keyboard_current_state) s>= 0)
0044b90c        enum InputButtonFlag buttons = 0
0044b913        float axis_x = 0f
0044b917        float axis_y = 0f
0044b925        if (is_key_down(0xc8) != 0)
0044b927        buttons = 0x1
0044b92c        axis_y = -1f
0044b943        if (is_key_down(0xd0) != 0)
0044b945        buttons |= 0x2
0044b948        axis_y = 1f
0044b95f        if (is_key_down(0xcb) != 0)
0044b961        buttons |= 0x4
0044b964        axis_x = -1f
0044b97b        if (is_key_down(0xcd) != 0)
0044b97d        buttons |= 0x8
0044b980        axis_x = 1f
0044b994        if (is_key_down(0x1d) != 0)
0044b996        buttons |= 0x10
0044b9a5        if (is_key_down(0x2c) != 0)
0044b9a7        buttons |= 0x100
0044b9b9        if (is_key_down(0x2e) != 0)
0044b9bb        buttons |= 0x200
0044b9cd        if (is_key_down(0x1f) != 0)
0044b9cf        buttons |= 0x80
0044b9e1        if (is_key_down(0x2d) != 0)
0044b9e3        buttons |= 0x40
0044b9f2        if (is_key_down(0x38) != 0)
0044b9f4        buttons |= 0x4000000
0044ba06        if (is_key_down(0x38) != 0)
0044ba08        buttons |= 0x20
0044ba17        if (is_key_down(0x2c) != 0)
0044ba19        buttons |= 0x20000
0044ba2b        if (is_key_down(0x2e) != 0)
0044ba2d        buttons |= 0x1000000
0044ba3f        if (is_key_down(0x39) != 0)
0044ba41        buttons |= 0x80000
0044ba53        if (is_key_down(0x3c) != 0)
0044ba55        buttons |= 0x400
0044ba67        if (is_key_down(0x39) != 0)
0044ba69        buttons |= 0x2000
0044ba7b        if (is_key_down(0x11) != 0)
0044ba7d        buttons |= INPUT_BUTTON_UNRESOLVED_00400000
0044ba8f        if (is_key_down(0x2d) != 0)
0044ba91        buttons |= 0x40000
0044baa3        if (is_key_down(0x1f) != 0)
0044baa5        buttons |= 0x200000
0044bab7        if (is_key_down(0x12) != 0)
0044bab9        buttons |= INPUT_BUTTON_UNRESOLVED_00800000
0044bacb        if (is_key_down(0x1d) != 0)
0044bacd        buttons |= 0x10000
0044badf        if (is_key_down(0x2a) != 0)
0044bae1        buttons |= 0x2000000
0044baf2        set_input_controller_slot0_button_axes(buttons, axis_x, axis_y)
0044b8b6        struct IDirectInputDevice8A* keyboard_device_1 = g_keyboard_device
0044b8c6        int32_t i
0044b8c6        struct IDirectInputDevice8A* keyboard_device_2
0044b8be        i = keyboard_device_1->lpVtbl->Acquire(keyboard_device_1)
0044b8c6        while (i == 0x8007001e)
0044b8c8        keyboard_device_2 = g_keyboard_device
0044b8d0        i = keyboard_device_2->lpVtbl->Acquire(keyboard_device_2)
0044b8e6        if (i == 0x80070005 || i == 0x8007000c)
0044b8f8        __builtin_memset(&g_keyboard_current_state, 0, 0x100)
0044b904        __builtin_memset(&g_keyboard_previous_state, 0, 0x100)
0044bb01        return 0
