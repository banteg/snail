/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: click_mouse_screen @ 0x44c060 */
/* selector: click_mouse_screen */

// Optionally forwards a cursor position to SetCursorPos when the window is active and captured, then stores raw and authored mouse coordinates for the selected mouse slot.
void *__cdecl click_mouse_screen(int slot, int x, int y)
{
  double v3; // st7
  _DWORD *v4; // ecx
  void *result; // eax
  float X; // [esp+14h] [ebp+8h]

  if ( !g_fullscreen_active
    && is_mouse_captured((MouseCursorState *)((char *)g_game_base + 656)) == 1
    && !slot
    && !g_window_deactivated
    && ((int (*)(void))GetActiveWindow)() == g_main_window )
  {
    SetCursorPos(x, y);
  }
  v3 = (double)x;
  v4 = g_game_base;
  g_mouse_screen_x[slot] = x;
  g_mouse_screen_y[slot] = y;
  g_mouse_live_x[slot] = v3;
  X = (float)y;
  g_mouse_live_y[slot] = X;
  *(float *)(v4[163] + 96) = v3;
  result = g_game_base;
  *(float *)(*((_DWORD *)g_game_base + 163) + 100) = X;
  return result;
}
