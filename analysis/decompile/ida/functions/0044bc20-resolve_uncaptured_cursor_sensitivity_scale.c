/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: resolve_uncaptured_cursor_sensitivity_scale @ 0x44bc20 */
/* selector: resolve_uncaptured_cursor_sensitivity_scale */

// Returns the cursor-delta sensitivity scale for uncaptured pointer mode: 1.0 while the cursor is captured, otherwise arg * 1.8 + 0.7.
float __cdecl resolve_uncaptured_cursor_sensitivity_scale(float scale)
{
  if ( is_mouse_captured((MouseCursorState *)((char *)g_game_base + 656)) )
    return 1.0;
  else
    return scale * 1.8 + 0.69999999;
}

