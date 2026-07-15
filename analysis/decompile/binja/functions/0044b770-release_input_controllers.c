/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: release_input_controllers @ 0x44b770 */

0044b776        int32_t i = 0
0044b77a        if (g_joystick_count s> 0)
0044b77d        struct IDirectInputDevice8A** esi_1 = &g_joystick_devices
0044b782        struct IDirectInputDevice8A* eax = *esi_1
0044b786        if (eax != 0)
0044b78b        eax->lpVtbl->Unacquire(eax)
0044b78e        struct IDirectInputDevice8A* eax_1 = *esi_1
0044b792        if (eax_1 != 0)
0044b797        eax_1->lpVtbl->Release(eax_1)
0044b79a        *esi_1 = nullptr
0044b7a5        i += 1
0044b7a6        esi_1 = &esi_1[1]
0044b7ab        do while (i s< g_joystick_count)
0044b7ae        struct IDirectInput8A* joystick_input_1 = g_joystick_input
0044b7b6        if (joystick_input_1 != 0)
0044b7bb        joystick_input_1 = joystick_input_1->lpVtbl->Release(joystick_input_1)
0044b7be        g_joystick_input = nullptr
0044b7c8        return joystick_input_1
