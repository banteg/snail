/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: configure_input_controller_axis_range_callback @ 0x44b4e0 */

0044b4e7        uint32_t dwType = instance->dwType
0044b4ee        if ((dwType.b & 3) != 0)
0044b4f0        struct DIPROPRANGE range
0044b4f0        range.diph.dwObj = dwType
0044b4f9        int32_t i = 0
0044b4fb        range.diph.dwSize = 0x18
0044b505        range.diph.dwHeaderSize = 0x10
0044b50d        range.diph.dwHow = 2
0044b515        range.lMin = 0xfffffc18
0044b51d        range.lMax = 0x3e8
0044b525        if (g_joystick_count s> 0)
0044b527        struct IDirectInputDevice8A** esi_1 = &g_joystick_devices
0044b52c        struct IDirectInputDevice8A* eax_1 = *esi_1
0044b53d        if (eax_1->lpVtbl->SetProperty(eax_1, 4, &range) s< 0)
0044b560        return 0
0044b544        i += 1
0044b545        esi_1 = &esi_1[1]
0044b54a        do while (i s< g_joystick_count)
0044b556        return 1
