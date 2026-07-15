/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: enumerate_input_controllers @ 0x44b3c0 */

0044b3d8        g_joystick_count = 0
0044b3e4        *out_count = 0
0044b3f1        HRESULT result = DirectInput8Create(GetModuleHandleA(nullptr), 0x800, &g_directinput8_iid, &g_joystick_input, 0)
0044b3f8        if (result s>= 0)
0044b3fe        struct IDirectInput8A* joystick_input_1 = g_joystick_input
0044b411        result = joystick_input_1->lpVtbl->EnumDevices(joystick_input_1, 4, append_enumerated_input_controller_callback, nullptr, 1)
0044b416        if (result s>= 0)
0044b41e        *out_count = g_joystick_count
0044b427        if (g_joystick_devices[0] != 0)
0044b42e        int32_t ebx_1 = 0
0044b432        if (g_joystick_count s> 0)
0044b438        struct IDirectInputDevice8A** esi_1 = &g_joystick_devices
0044b43d        while (true)
0044b43d        struct IDirectInputDevice8A* eax_3 = *esi_1
0044b447        result = eax_3->lpVtbl->SetDataFormat(eax_3, &g_directinput_joystick_data_format)
0044b44c        if (result s< 0)
0044b483        return result
0044b44e        struct IDirectInputDevice8A* eax_4 = *esi_1
0044b456        result = eax_4->lpVtbl->SetCooperativeLevel(eax_4, window_handle, 5)
0044b45b        if (result s< 0)
0044b483        return result
0044b45d        struct IDirectInputDevice8A* eax_5 = *esi_1
0044b46a        result = eax_5->lpVtbl->EnumObjects(eax_5, configure_input_controller_axis_range_callback, window_handle, 0)
0044b46f        if (result s< 0)
0044b483        return result
0044b476        ebx_1 += 1
0044b477        esi_1 = &esi_1[1]
0044b47c        if (ebx_1 s>= g_joystick_count)
0044b47e        return 0
0044b47e        return 0
0044b483        return result
