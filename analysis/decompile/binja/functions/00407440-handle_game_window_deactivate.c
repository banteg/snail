/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: handle_game_window_deactivate @ 0x407440 */

00407440        int32_t result
00407440        result.b = data_4b7654
00407447        if (result.b == 0)
00407449        result.b = data_4df920
00407450        if (result.b != 0)
00407457        pause_audio_backend_if_running(0x753c58)
0040745c        HWND hWnd = data_4dfaf0
00407464        data_4b7654 = 1
0040746b        ShowWindow(hWnd, SW_MINIMIZE)
00407471        result = data_4df860
00407478        if (result != 0)
0040747a        data_4df860 = 0
00407484        return result
