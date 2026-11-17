/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: bass_audio_window_proc @ 0x4079e0 */
/* selector: bass_audio_window_proc */

// Hidden BASS window procedure that posts WM_QUIT on close and otherwise forwards messages to DefWindowProcA.
LRESULT __stdcall bass_audio_window_proc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  if ( Msg != 16 )
    return DefWindowProcA(hWnd, Msg, wParam, lParam);
  PostQuitMessage(0);
  return 0;
}
