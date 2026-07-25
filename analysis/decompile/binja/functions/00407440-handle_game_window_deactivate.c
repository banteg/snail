/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: handle_game_window_deactivate @ 0x407440 */

00407440        int32_t pending_window_deactivate_1
00407440        pending_window_deactivate_1.b = g_window_deactivated
00407447        if (pending_window_deactivate_1.b == 0)
00407450        if (g_runtime_config.fullscreen_enabled != 0)
00407457        pause_audio_backend_if_running(&g_audio_backend)
0040745c        HWND main_window_1 = g_main_window
00407464        g_window_deactivated = 1
0040746b        ShowWindow(main_window_1, SW_MINIMIZE)
00407471        pending_window_deactivate_1 = g_pending_window_deactivate
00407478        if (pending_window_deactivate_1 != 0)
0040747a        g_pending_window_deactivate = 0
00407484        return pending_window_deactivate_1
