/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: show_and_focus_game_window @ 0x4073b0 */

004073b4        uint32_t eax = timeGetTime()
004073c0        int32_t var_4 = 0
004073c4        HWND main_window_1 = g_main_window
004073d6        g_previous_frame_timestamp_seconds = fconvert.s(float.t(eax.q) * fconvert.t(0.00100000005f))
004073dc        ShowWindow(main_window_1, SW_SHOWNORMAL)
004073e9        SetForegroundWindow(g_main_window)
004073f6        SetFocus(g_main_window)
00407402        HWND result = SetActiveWindow(g_main_window)
00407408        data_4b7764 = 0
0040740e        data_4b7234 = 0
00407414        data_4b7230 = 0
0040741a        __builtin_memset(&g_right_mouse_button_state, 0, 2)
00407420        data_4b7765 = 0
00407426        data_4b7235 = 0
0040742c        data_4b7231 = 0
0040743c        return result
