/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_audio_subsystem @ 0x407a10 */

00407a20        WNDCLASSA wndClass
00407a20        wndClass.style = 0
00407a24        wndClass.lpfnWndProc = sub_4079e0
00407a2c        wndClass.cbClsExtra = 0
00407a30        wndClass.cbWndExtra = 0
00407a34        wndClass.hInstance = data_4dfad8
00407a38        wndClass.hIcon = 0
00407a3c        wndClass.hCursor = 0
00407a40        wndClass.hbrBackground = 0
00407a44        wndClass.lpszMenuName = 0
00407a48        wndClass.lpszClassName = "BASS"
00407a59        if (RegisterClassA(&wndClass) == 0)
00407a5b        int32_t eax_2 = abort_startup_with_3d_error()
00407a60        eax_2.b = 0
00407a66        return eax_2
00407a85        HWND hwnd = CreateWindowExA(WS_EX_LEFT, "BASS", &g_blank_text, 0x86000000, 0, 0, 0, 0, nullptr, nullptr, data_4dfad8, nullptr)
00407a8d        data_4dfaf8 = hwnd
00407a92        if (hwnd == 0)
00407a94        shutdown_bass_audio_window()
00407a99        int32_t eax_3 = abort_startup_with_3d_error()
00407a9e        eax_3.b = 0
00407aa4        return eax_3
00407ab2        if (initialize_bass_audio_backend(&g_audio_backend, hwnd) != 0)
00407ad9        set_global_sample_volume_config(&g_audio_backend, g_runtime_config.sample_volume)
00407aea        int32_t eax_7 = set_global_stream_volume_config(&g_audio_backend, g_runtime_config.stream_volume)
00407aef        eax_7.b = 1
00407af5        return eax_7
00407ab4        abort_startup_with_3d_error()
00407ac0        BOOL eax_6 = EndDialog(data_4dfaf8, 0)
00407ac6        eax_6.b = 0
00407acc        return eax_6
