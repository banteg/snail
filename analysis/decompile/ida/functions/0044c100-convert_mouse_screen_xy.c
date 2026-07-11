/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: convert_mouse_screen_xy @ 0x44c100 */
/* selector: convert_mouse_screen_xy */

BOOL __cdecl convert_mouse_screen_xy(int sensitivity_slot, float *x, float *y)
{
  BOOL result; // eax
  double v4; // st7
  double v5; // st7
  int Point; // [esp+0h] [ebp-8h] BYREF
  int Point_4; // [esp+4h] [ebp-4h]

  if ( !g_fullscreen_active && is_mouse_captured((MouseCursorState *)((char *)g_game_base + 656)) )
  {
    result = ((int (__stdcall *)(int *))GetCursorPos)(&Point);
    if ( result )
    {
      *x = (float)Point;
      *y = (float)Point_4;
      return (BOOL)y;
    }
    else
    {
      *x = 0.0;
      *y = 0.0;
    }
    return result;
  }
  if ( is_mouse_captured((MouseCursorState *)((char *)g_game_base + 656)) )
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
    result = ((int (*)(void))GetActiveWindow)();
    if ( result == g_main_window )
      return SetCursorPos((__int64)(g_authored_view_width * 0.5), (__int64)(g_authored_view_height * 0.5));
  }
  else
  {
    if ( ((int (__stdcall *)(int *))GetCursorPos)(&Point) )
    {
      v4 = resolve_uncaptured_cursor_sensitivity_scale(g_steering_sensitivity[sensitivity_slot]);
      *x = v4 * ((double)Point - g_authored_view_width * 0.5) * g_mouse_screen_to_authored_x_scale + *x;
      v5 = resolve_uncaptured_cursor_sensitivity_scale(g_steering_sensitivity[sensitivity_slot]);
      *y = v5 * ((double)Point_4 - g_authored_view_height * 0.5) * g_mouse_screen_to_authored_y_scale + *y;
    }
    else
    {
      *x = 0.0;
      *y = 0.0;
    }
    result = ((int (*)(void))GetActiveWindow)();
    if ( result == g_main_window )
      return SetCursorPos((__int64)(g_authored_view_width * 0.5), (__int64)(g_authored_view_height * 0.5));
  }
  return result;
}
