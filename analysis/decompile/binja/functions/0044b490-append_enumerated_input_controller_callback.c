/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: append_enumerated_input_controller_callback @ 0x44b490 */

0044b490        int32_t joystick_count_1 = g_joystick_count
0044b4a4        g_joystick_count = joystick_count_1 + 1
0044b4a9        struct IDirectInput8A* joystick_input_1 = g_joystick_input
0044b4ba        if (joystick_input_1->lpVtbl->CreateDevice(joystick_input_1, &instance->guidInstance, &g_joystick_devices[joystick_count_1], nullptr) s< 0)
0044b4c1        return 1
0044b4ca        int32_t result = 0
0044b4cf        result.b = g_joystick_count s< 4
0044b4d2        return result
