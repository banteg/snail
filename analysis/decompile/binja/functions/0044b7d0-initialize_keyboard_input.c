/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_keyboard_input @ 0x44b7d0 */

0044b7d8        GetWindowLongA(arg1, 0xfffffffa)
0044b7de        release_input_controllers()
0044b7fd        HRESULT result = DirectInput8Create(GetModuleHandleA(nullptr), 0x800, &g_directinput8_iid, &g_keyboard_input, 0)
0044b804        if (result s>= 0)
0044b806        int32_t* eax_1 = g_keyboard_input
0044b81a        result = (*(*eax_1 + 0xc))(eax_1, &g_directinput_keyboard_guid, &g_keyboard_device, 0)
0044b81f        if (result s>= 0)
0044b821        int32_t* eax_2 = g_keyboard_device
0044b82e        result = (*(*eax_2 + 0x2c))(eax_2, &g_directinput_keyboard_data_format)
0044b833        if (result s>= 0)
0044b835        int32_t* eax_3 = g_keyboard_device
0044b840        result = (*(*eax_3 + 0x34))(eax_3, arg1, 5)
0044b845        if (result s>= 0)
0044b847        int32_t* eax_4 = g_keyboard_device
0044b850        (*(*eax_4 + 0x1c))(eax_4)
0044b858        result = 0
0044b85f        __builtin_memset(&g_keyboard_previous_state, 0, 0x100)
0044b86b        __builtin_memset(&g_keyboard_current_state, 0, 0x100)
0044b86f        return result
