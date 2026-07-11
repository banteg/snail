/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: click_mouse_screen @ 0x44c060 */

0044c076        if (g_fullscreen_active == 0 && is_mouse_captured(&g_game_base[0x290]) == 1 && slot == 0 && g_window_deactivated == 0 && GetActiveWindow() == g_main_window)
0044c0a9        SetCursorPos(x, y)
0044c0af        long double x87_r7 = float.t(x)
0044c0b3        char* game_base_2 = g_game_base
0044c0b9        g_mouse_screen_x[slot] = x
0044c0c0        g_mouse_screen_y[slot] = y
0044c0c8        g_mouse_live_x[slot] = fconvert.s(x87_r7)
0044c0cf        long double x87_r6 = float.t(y)
0044c0d7        g_mouse_live_y[slot] = fconvert.s(x87_r6)
0044c0e6        *(*(game_base_2 + 0x28c) + 0x60) = fconvert.s(x87_r7)
0044c0e9        char* game_base_1 = g_game_base
0044c0f8        *(*(game_base_1 + 0x28c) + 0x64) = fconvert.s(x87_r6)
0044c0fb        return game_base_1
