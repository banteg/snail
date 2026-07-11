/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_mouse_input @ 0x44c310 */

0044c32d        g_mouse_live_x[0] = fconvert.s(fconvert.t(data_4df85c) * fconvert.t(0.5f))
0044c339        long double x87_r7_2 = fconvert.t(data_4b7760) * fconvert.t(0.5f)
0044c341        g_hide_system_cursor_flag = 1
0044c348        g_mouse_live_y[0] = fconvert.s(x87_r7_2)
0044c355        HRESULT result = DirectInput8Create(GetModuleHandleA(nullptr), 0x800, &g_directinput8_iid, &g_mouse_input, 0)
0044c35c        if (result s>= 0)
0044c35e        void* mouse_input_1 = g_mouse_input
0044c372        result = (*(*mouse_input_1 + 0xc))(mouse_input_1, 0x49b020, &g_mouse_device, 0)
0044c377        if (result s>= 0)
0044c379        void* mouse_device_1 = g_mouse_device
0044c386        result = (*(*mouse_device_1 + 0x2c))(mouse_device_1, 0x49b70c)
0044c38b        if (result s>= 0)
0044c38d        void* mouse_device_2 = g_mouse_device
0044c39c        (*(*mouse_device_2 + 0x34))(mouse_device_2, window_handle, 4)
0044c39f        void* mouse_device_3 = g_mouse_device
0044c3a7        (*(*mouse_device_3 + 0x1c))(mouse_device_3)
0044c3aa        return 0
0044c3ac        return result
