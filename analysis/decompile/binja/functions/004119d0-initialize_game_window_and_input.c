/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_game_window_and_input @ 0x4119d0 */

004119d6        int32_t display_mode_index = g_runtime_config.display_mode_index
004119e4        int32_t esi_1 = g_runtime_config.render_flags & RUNTIME_RENDER_32_BIT_COLOR
004119eb        int32_t esi_2 = neg.d(esi_1)
004119f8        int32_t var_e0
004119f8        int32_t ebx
004119f8        int32_t ebp
004119f8        if (display_mode_index u> 4)
00411a41        g_runtime_config.display_mode_index = 1
00411a4b        label_411a4b:
00411a4b        ebp = 0x280
00411a50        ebx = 0x1e0
00411a55        var_e0 = 0x280
004119fa        switch (display_mode_index)
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
00411a59        HINSTANCE game_window_instance_1 = g_game_window_instance
00411a66        g_fullscreen_active = 0
00411a6d        if (game_window_instance_1 == 0)
00411a70        game_window_instance_1 = GetModuleHandleA(nullptr)
00411a76        g_game_window_instance = game_window_instance_1
00411a7b        PSTR lpIconName = 0x67
00411a7e        WNDCLASSA var_c4
00411a7e        var_c4.style = 3
00411a86        var_c4.lpfnWndProc = game_window_proc
00411a8e        var_c4.cbClsExtra = 0
00411a92        var_c4.cbWndExtra = 0
00411a96        var_c4.hInstance = game_window_instance_1
00411aa0        var_c4.hIcon = LoadIconA(game_window_instance_1, lpIconName)
00411aa8        WNDCLASSA* lpWndClass = &var_c4
00411aa9        var_c4.hCursor = 0
00411aad        var_c4.hbrBackground = 0
00411ab1        var_c4.lpszMenuName = 0
00411ab5        var_c4.lpszClassName = "SnailMailWindowClass"
00411ac6        if (RegisterClassA(lpWndClass) == 0)
00411ac8        abort_startup_with_3d_error()
00411ad9        return 0
00411ae1        if (g_fullscreen_active == 0)
00411ae1        goto label_411b3b
00411aee        enum CDS_TYPE dwFlags = CDS_FULLSCREEN
00411af0        DEVMODEA var_9c
00411af0        __builtin_memset(&var_9c, 0, 0x9c)
00411af6        var_9c.dmSize = 0x9c
00411b00        DEVMODEA* lpDevMode = &var_9c
00411b01        var_9c.dmPelsWidth = ebp
00411b08        var_9c.dmPelsHeight = ebx
00411b0f        var_9c.dmBitsPerPel = (sbb.d(esi_2, esi_2, esi_1 != 0) & 0x10) + 0x10
00411b16        var_9c.dmFields = 0x1c0000
00411b29        int32_t X
00411b29        int32_t Y
00411b29        enum WINDOW_STYLE dwStyle
00411b29        enum WINDOW_EX_STYLE dwExStyle
00411b29        if (ChangeDisplaySettingsA(lpDevMode, dwFlags) == DISP_CHANGE_SUCCESSFUL)
00411be5        if (g_fullscreen_active == 0)
00411be5        goto label_411b3b
00411bed        dwExStyle = WS_EX_APPWINDOW
00411bf2        dwStyle = WS_POPUP
00411bf7        int32_t ecx_4 = ShowCursor(0)
00411c01        int32_t var_f8_5 = ecx_4
00411c04        X = 0
00411c08        Y = 0
00411c13        int32_t var_fc_2 = ecx_4
00411c17        update_mouse_authored_scale(fconvert.s(float.t(var_e0)), fconvert.s(float.t(ebx)))
00411b2f        g_fullscreen_active = 0
00411b3b        label_411b3b:
00411b3b        dwExStyle = 0x40100
00411b40        dwStyle = 0x10ca0000
00411b45        X = 0x64
00411b49        Y = 0x64
00411b4d        ebp = 0x280
00411b52        ebx = 0x1e0
00411b5a        BOOL bMenu = 0
00411b60        RECT var_d4
00411b60        RECT* lpRect = &var_d4
00411b6d        var_d4 = struct RECT {
    .left = 0
    .right = ebp
    .top = 0
    .bottom = ebx
}
00411b71        AdjustWindowRectEx(lpRect, dwStyle, bMenu, dwExStyle)
00411bb8        HWND hWnd = CreateWindowExA(dwExStyle, "SnailMailWindowClass", window_name, dwStyle | 0x6000000, X, Y, var_d4.right - var_d4.left, var_d4.bottom - var_d4.top, nullptr, nullptr, g_game_window_instance, 0)
00411bc0        g_main_window = hWnd
00411bc5        if (hWnd == 0)
00411bc7        release_global_direct3d_renderer_resources()
00411bcc        abort_startup_with_3d_error()
00411bdd        return 0
00411c25        HDC eax_10 = GetDC(hWnd)
00411c2d        g_main_window_dc = eax_10
00411c32        if (eax_10 == 0)
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
00411cca        int32_t eax_18 = enumerate_input_controllers(g_main_window, &g_controller_count_view)
00411cd4        if (eax_18 s< 0)
00411cd6        abort_startup_with_3d_error()
00411ce4        EndDialog(g_main_window, 0)
00411cf6        return 0
00411cf7        eax_18.b = g_fullscreen_active
00411d02        int32_t var_f8_14 = eax_18
00411d0e        if (initialize_mouse_input(g_main_window) s>= 0)
00411d37        SetFocus(g_main_window)
00411d3b        set_cull_mode(1)
00411d52        return 1
00411d10        abort_startup_with_3d_error()
00411d1e        EndDialog(g_main_window, 0)
00411d30        return 0
