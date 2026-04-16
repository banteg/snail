/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: handle_game_window_activate @ 0x4072f0 */

004072f4        char* var_10 = "G0Maximize %i\n"
004072fe        char* var_14 = "G0Maximize Do something\n"
00407310        resume_audio_backend_if_paused(0x753c58)
0040731c        bool cond:0 = data_4df920 == 0
0040731e        data_4b7654 = 0
00407324        if (not(cond:0))
00407328        set_fullscreen_mode(1)
0040733a        int32_t var_4 = 0
0040733e        long double x87_r7 = float.t(timeGetTime().q)
00407342        HWND hWnd = data_4dfaf0
00407350        data_4dfb00 = fconvert.s(x87_r7 * fconvert.t(0.00100000005f))
00407356        ShowWindow(hWnd, SW_SHOWNORMAL)
00407363        SetForegroundWindow(data_4dfaf0)
00407370        HWND result = SetFocus(data_4dfaf0)
00407376        data_4b7764 = 0
0040737c        data_4b7234 = 0
00407382        data_4b7230 = 0
00407388        data_4b7640 = 0
0040738e        data_4b7765 = 0
00407394        data_4b7235 = 0
0040739a        data_4b7231 = 0
004073a0        data_4b7641 = 0
004073aa        return result
