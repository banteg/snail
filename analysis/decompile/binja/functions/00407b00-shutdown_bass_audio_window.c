/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: shutdown_bass_audio_window @ 0x407b00 */

00407b05        uninitialize_bass_audio_backend(&g_audio_backend)
00407b0a        HWND hWnd = data_4dfaf8
00407b11        if (hWnd != 0 && DestroyWindow(hWnd) == 0)
00407b1e        abort_startup_with_3d_error()
00407b23        data_4dfaf8 = 0
00407b38        BOOL result = UnregisterClassA("BASS", g_application_instance)
00407b40        if (result != 0)
00407b47        return result
00407b42        return abort_startup_with_3d_error() __tailcall
