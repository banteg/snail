/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* export: isolated copy with manifest symbols applied */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: bass_audio_window_proc @ 0x4079e0 */

004079e7        if (arg2 != 0x10)
004079ff        return DefWindowProcA(arg1, arg2, arg3, arg4)
00407a04        PostQuitMessage(0)
00407a0c        return 0
