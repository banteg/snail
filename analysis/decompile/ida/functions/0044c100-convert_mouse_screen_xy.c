/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: convert_mouse_screen_xy @ 0x44c100 */
/* selector: convert_mouse_screen_xy */

int __cdecl convert_mouse_screen_xy(int a1, float *a2, float *a3)
{
  int result; // eax
  double v4; // st7
  double v5; // st7
  int Point; // [esp+0h] [ebp-8h] BYREF
  int Point_4; // [esp+4h] [ebp-4h]

  if ( !unk_4DFAF4 && is_mouse_captured((char *)MEMORY[0x4DF904] + 656) )
  {
    result = ((int (__stdcall *)(int *))GetCursorPos)(&Point);
    if ( result )
    {
      *a2 = (float)Point;
      *a3 = (float)Point_4;
      return (int)a3;
    }
    else
    {
      *a2 = 0.0;
      *a3 = 0.0;
    }
    return result;
  }
  if ( is_mouse_captured((char *)MEMORY[0x4DF904] + 656) )
  {
    if ( ((int (__stdcall *)(int *))GetCursorPos)(&Point) )
    {
      *a2 = ((double)Point - unk_4DF85C * 0.5) * g_mouse_screen_to_authored_x_scale + *a2;
      *a3 = ((double)Point_4 - unk_4B7760 * 0.5) * g_mouse_screen_to_authored_y_scale + *a3;
    }
    else
    {
      *a2 = 0.0;
      *a3 = 0.0;
    }
    result = ((int (*)(void))GetActiveWindow)();
    if ( result == MEMORY[0x4DFAF0] )
      return ((int (__stdcall *)(_DWORD, _DWORD))SetCursorPos)((__int64)(unk_4DF85C * 0.5), (__int64)(unk_4B7760 * 0.5));
  }
  else
  {
    if ( ((int (__stdcall *)(int *))GetCursorPos)(&Point) )
    {
      v4 = resolve_uncaptured_cursor_sensitivity_scale(flt_4DF950[a1]);
      *a2 = v4 * ((double)Point - unk_4DF85C * 0.5) * g_mouse_screen_to_authored_x_scale + *a2;
      v5 = resolve_uncaptured_cursor_sensitivity_scale(flt_4DF950[a1]);
      *a3 = v5 * ((double)Point_4 - unk_4B7760 * 0.5) * g_mouse_screen_to_authored_y_scale + *a3;
    }
    else
    {
      *a2 = 0.0;
      *a3 = 0.0;
    }
    result = ((int (*)(void))GetActiveWindow)();
    if ( result == MEMORY[0x4DFAF0] )
      return ((int (__stdcall *)(_DWORD, _DWORD))SetCursorPos)((__int64)(unk_4DF85C * 0.5), (__int64)(unk_4B7760 * 0.5));
  }
  return result;
}
