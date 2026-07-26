/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: click_mouse_screen @ 0x44c060 */
/* selector: click_mouse_screen */

// Optionally forwards a cursor position to SetCursorPos when the window is active and captured, then stores raw/live mouse coordinates for the selected slot and publishes authored x/y through player zero's borrowed cRGameInput owner.
void __cdecl click_mouse_screen(int32_t slot, int32_t x, int32_t y)
{
  double v3; // st7
  GameRoot *v4; // ecx
  float X; // [esp+14h] [ebp+8h]

  if ( g_fullscreen_active == 0
    && is_mouse_captured(&g_game_base->players[0].mouse_cursor) == 1
    && slot == 0
    && g_window_deactivated == 0
    && GetActiveWindow() == g_main_window )
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
  v4->players[0].game_input->input.authored_x = v3;
  g_game_base->players[0].game_input->input.authored_y = X;
}
