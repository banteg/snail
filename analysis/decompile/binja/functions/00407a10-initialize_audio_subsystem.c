/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
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
00407a5b        abort_startup_with_3d_error()
00407a60        int32_t eax_2
00407a60        eax_2.b = 0
00407a66        return eax_2
00407a85        HWND eax_3 = CreateWindowExA(WS_EX_LEFT, "BASS", &data_4dfb08, 0x86000000, 0, 0, 0, 0, nullptr, nullptr, data_4dfad8, nullptr)
00407a8d        data_4dfaf8 = eax_3
00407a92        if (eax_3 == 0)
00407a94        sub_407b00()
00407a99        abort_startup_with_3d_error()
00407a9e        int32_t eax_4
00407a9e        eax_4.b = 0
00407aa4        return eax_4
00407ab2        if (initialize_bass_audio_backend(0x753c58, eax_3) != 0)
00407ad9        set_global_sample_volume_config(data_4df918)
00407aea        set_global_stream_volume_config(data_4df91c)
00407aef        int32_t eax_8
00407aef        eax_8.b = 1
00407af5        return eax_8
00407ab4        abort_startup_with_3d_error()
00407ac0        EndDialog(data_4dfaf8, 0)
00407ac6        BOOL eax_7
00407ac6        eax_7.b = 0
00407acc        return eax_7
