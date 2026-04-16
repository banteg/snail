/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: show_and_focus_game_window @ 0x4073b0 */

004073b4        uint32_t eax = timeGetTime()
004073c0        int32_t var_4 = 0
004073c4        HWND hWnd = data_4dfaf0
004073d6        data_4dfb00 = fconvert.s(float.t(eax.q) * fconvert.t(0.00100000005f))
004073dc        ShowWindow(hWnd, SW_SHOWNORMAL)
004073e9        SetForegroundWindow(data_4dfaf0)
004073f6        SetFocus(data_4dfaf0)
00407402        HWND result = SetActiveWindow(data_4dfaf0)
00407408        data_4b7764 = 0
0040740e        data_4b7234 = 0
00407414        data_4b7230 = 0
0040741a        data_4b7640 = 0
00407420        data_4b7765 = 0
00407426        data_4b7235 = 0
0040742c        data_4b7231 = 0
00407432        data_4b7641 = 0
0040743c        return result
