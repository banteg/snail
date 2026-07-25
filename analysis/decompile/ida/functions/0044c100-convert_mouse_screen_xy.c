/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: convert_mouse_screen_xy @ 0x44c100 */
/* selector: convert_mouse_screen_xy */

// Side-effect-only Windows cursor bridge: copies a captured OS cursor directly or converts centered cursor deltas into authored x/y, applies steering sensitivity only while uncaptured, zeros both outputs on query failure, and recenters the active main window. Native leaves incidental eax values; the helper has a void ABI.
void __cdecl convert_mouse_screen_xy(int sensitivity_slot, float *x, float *y)
{
  double v3; // st7
  double v4; // st7
  int Point; // [esp+0h] [ebp-8h] BYREF
  int Point_4; // [esp+4h] [ebp-4h]

  if ( !g_fullscreen_active && is_mouse_captured(&g_game_base->players[0].mouse_cursor) )
  {
    if ( ((int (__stdcall *)(int *))GetCursorPos)(&Point) )
    {
      *x = (float)Point;
      *y = (float)Point_4;
    }
    else
    {
      *x = 0.0;
      *y = 0.0;
    }
    return;
  }
  if ( is_mouse_captured(&g_game_base->players[0].mouse_cursor) )
  {
    if ( ((int (__stdcall *)(int *))GetCursorPos)(&Point) )
    {
      *x = ((double)Point - g_authored_view_width * 0.5) * g_mouse_screen_to_authored_x_scale + *x;
      *y = ((double)Point_4 - g_authored_view_height * 0.5) * g_mouse_screen_to_authored_y_scale + *y;
    }
    else
    {
      *x = 0.0;
      *y = 0.0;
    }
    if ( ((int (*)(void))GetActiveWindow)() == g_main_window )
      goto LABEL_16;
  }
  else
  {
    if ( ((int (__stdcall *)(int *))GetCursorPos)(&Point) )
    {
      v3 = resolve_uncaptured_cursor_sensitivity_scale(g_runtime_config.steering_sensitivity[sensitivity_slot]);
      *x = v3 * ((double)Point - g_authored_view_width * 0.5) * g_mouse_screen_to_authored_x_scale + *x;
      v4 = resolve_uncaptured_cursor_sensitivity_scale(g_runtime_config.steering_sensitivity[sensitivity_slot]);
      *y = v4 * ((double)Point_4 - g_authored_view_height * 0.5) * g_mouse_screen_to_authored_y_scale + *y;
    }
    else
    {
      *x = 0.0;
      *y = 0.0;
    }
    if ( ((int (*)(void))GetActiveWindow)() == g_main_window )
LABEL_16:
      SetCursorPos((__int64)(g_authored_view_width * 0.5), (__int64)(g_authored_view_height * 0.5));
  }
}
