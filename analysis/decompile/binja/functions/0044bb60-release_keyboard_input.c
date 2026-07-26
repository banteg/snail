/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: release_keyboard_input @ 0x44bb60 */

0044bb60        struct IDirectInputDevice8A* keyboard_device_2 = g_keyboard_device
0044bb67        if (keyboard_device_2 != 0)
0044bb6c        keyboard_device_2->lpVtbl->Unacquire(keyboard_device_2)
0044bb6f        struct IDirectInputDevice8A* keyboard_device_1 = g_keyboard_device
0044bb76        if (keyboard_device_1 != 0)
0044bb7b        keyboard_device_1->lpVtbl->Release(keyboard_device_1)
0044bb7e        g_keyboard_device = nullptr
0044bb88        struct IDirectInput8A* keyboard_input_1 = g_keyboard_input
0044bb8f        if (keyboard_input_1 != 0)
0044bb94        keyboard_input_1->lpVtbl->Release(keyboard_input_1)
0044bb97        g_keyboard_input = nullptr
0044bba1        return
