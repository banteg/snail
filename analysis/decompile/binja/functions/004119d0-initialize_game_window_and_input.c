/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_game_window_and_input @ 0x4119d0 */

004119d6        int32_t eax = data_4df94c
004119e4        int32_t esi_1 = data_4df934.d & 0x400
004119eb        int32_t esi_2 = neg.d(esi_1)
004119f8        int32_t var_e0
004119f8        int32_t ebx
004119f8        int32_t ebp
004119f8        if (eax u> 4)
00411a41        data_4df94c = 1
00411a4b        label_411a4b:
00411a4b        ebp = 0x280
00411a50        ebx = 0x1e0
00411a55        var_e0 = 0x280
004119fa        switch (eax)
00411a01        case 0
00411a01        ebp = 0x140
00411a06        ebx = 0xf0
00411a0b        var_e0 = 0x140
004119fa        case 1
004119fa        goto label_411a4b
00411a11        case 2
00411a11        ebp = 0x320
00411a16        ebx = 0x258
00411a1b        var_e0 = 0x320
00411a21        case 3
00411a21        ebp = 0x400
00411a26        ebx = 0x300
00411a2b        var_e0 = 0x400
00411a31        case 4
00411a31        ebp = 0x640
00411a36        ebx = 0x4b0
00411a3b        var_e0 = 0x640
00411a59        HMODULE hInstance = data_50327c
00411a66        g_fullscreen_active = 0
00411a6d        if (hInstance == 0)
00411a70        hInstance = GetModuleHandleA(nullptr)
00411a76        data_50327c = hInstance
00411a7e        WNDCLASSA wndClass
00411a7e        wndClass.style = 3
00411a86        wndClass.lpfnWndProc = game_window_proc
00411a8e        wndClass.cbClsExtra = 0
00411a92        wndClass.cbWndExtra = 0
00411a96        wndClass.hInstance = hInstance
00411aa0        wndClass.hIcon = LoadIconA(hInstance, 0x67)
00411aa9        wndClass.hCursor = 0
00411aad        wndClass.hbrBackground = 0
00411ab1        wndClass.lpszMenuName = 0
00411ab5        wndClass.lpszClassName = "SnailMailWindowClass"
00411ac6        if (RegisterClassA(&wndClass) == 0)
00411ac8        abort_startup_with_3d_error()
00411ad9        return 0
00411ae1        if (g_fullscreen_active == 0)
00411ae1        goto label_411b3b
00411aee        enum CDS_TYPE dwFlags = CDS_FULLSCREEN
00411af0        DEVMODEA devMode
00411af0        __builtin_memset(&devMode, 0, 0x9c)
00411af6        devMode.dmSize = 0x9c
00411b01        devMode.dmPelsWidth = ebp
00411b08        devMode.dmPelsHeight = ebx
00411b0f        devMode.dmBitsPerPel = (sbb.d(esi_2, esi_2, esi_1 != 0) & 0x10) + 0x10
00411b16        devMode.dmFields = 0x1c0000
00411b29        int32_t X
00411b29        int32_t Y
00411b29        enum WINDOW_STYLE dwStyle
00411b29        enum WINDOW_EX_STYLE dwExStyle
00411b29        if (ChangeDisplaySettingsA(&devMode, dwFlags) == DISP_CHANGE_SUCCESSFUL)
00411be5        if (g_fullscreen_active == 0)
00411be5        goto label_411b3b
00411bed        dwExStyle = WS_EX_APPWINDOW
00411bf2        dwStyle = WS_POPUP
00411bf7        int32_t ecx_4 = ShowCursor(0)
00411c01        int32_t var_f8_7 = ecx_4
00411c04        X = 0
00411c08        Y = 0
00411c13        int32_t var_fc_4 = ecx_4
00411c17        update_mouse_authored_scale(fconvert.s(float.t(var_e0)), fconvert.s(float.t(ebx)))
00411b2f        g_fullscreen_active = 0
00411b3b        label_411b3b:
00411b3b        dwExStyle = 0x40100
00411b40        dwStyle = 0x10ca0000
00411b45        X = 0x64
00411b49        Y = 0x64
00411b4d        ebp = 0x280
00411b52        ebx = 0x1e0
00411b61        RECT rect
00411b61        rect.left = 0
00411b65        rect.right = ebp
00411b69        rect.top = 0
00411b6d        rect.bottom = ebx
00411b71        AdjustWindowRectEx(&rect, dwStyle, 0, dwExStyle)
00411bb8        HWND hWnd = CreateWindowExA(dwExStyle, "SnailMailWindowClass", arg1, dwStyle | 0x6000000, X, Y, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, data_50327c, 0)
00411bc0        g_main_window = hWnd
00411bc5        if (hWnd == 0)
00411bc7        release_global_direct3d_renderer_resources()
00411bcc        abort_startup_with_3d_error()
00411bdd        return 0
00411c25        HDC eax_11 = GetDC(hWnd)
00411c2d        data_4dfaec = eax_11
00411c32        if (eax_11 == 0)
00411c34        release_global_direct3d_renderer_resources()
00411c39        abort_startup_with_3d_error()
00411c4a        return 0
00411c53        ShowWindow(g_main_window, SW_SHOW)
00411c60        SetForegroundWindow(g_main_window)
00411c73        SetFocus(g_main_window)
00411c7c        if (initialize_direct3d_renderer() == 0)
00411c7e        release_global_direct3d_renderer_resources()
00411c83        abort_startup_with_3d_error()
00411c94        return 0
00411ca5        if (initialize_keyboard_input(g_main_window) s< 0)
00411ca7        abort_startup_with_3d_error()
00411cac        release_keyboard_input()
00411cbd        return 0
00411cca        HRESULT eax_19 = enumerate_input_controllers(g_main_window, &data_4b776c)
00411cd4        if (eax_19 s< 0)
00411cd6        abort_startup_with_3d_error()
00411ce4        EndDialog(g_main_window, 0)
00411cf6        return 0
00411cf7        eax_19.b = g_fullscreen_active
00411d02        HRESULT var_f8_16 = eax_19
00411d0e        if (initialize_mouse_input(g_main_window) s>= 0)
00411d37        SetFocus(g_main_window)
00411d3b        set_cull_mode(1)
00411d52        return 1
00411d10        abort_startup_with_3d_error()
00411d1e        EndDialog(g_main_window, 0)
00411d30        return 0
