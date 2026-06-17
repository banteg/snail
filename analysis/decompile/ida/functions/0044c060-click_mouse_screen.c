/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: click_mouse_screen @ 0x44c060 */
/* selector: click_mouse_screen */

void *__cdecl click_mouse_screen(int a1, int X, int Y)
{
  double v3; // st7
  _DWORD *v4; // ecx
  void *result; // eax
  float Xa; // [esp+14h] [ebp+8h]

  if ( !g_fullscreen_active
    && is_mouse_captured(g_game_base + 656) == 1
    && !a1
    && !g_window_deactivated
    && ((int (*)(void))GetActiveWindow)() == g_main_window )
  {
    ((void (__stdcall *)(int, int))SetCursorPos)(X, Y);
  }
  v3 = (double)X;
  v4 = g_game_base;
  g_mouse_screen_x[a1] = X;
  g_mouse_screen_y[a1] = Y;
  g_mouse_live_x[a1] = v3;
  Xa = (float)Y;
  g_mouse_live_y[a1] = Xa;
  *(float *)(v4[163] + 96) = v3;
  result = g_game_base;
  *(float *)(*((_DWORD *)g_game_base + 163) + 100) = Xa;
  return result;
}
