/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: resolve_uncaptured_cursor_sensitivity_scale @ 0x44bc20 */
/* selector: resolve_uncaptured_cursor_sensitivity_scale */

// Exact Windows `MouseCalcScale(float)`: returns 1.0 while the desktop cursor is captured and otherwise applies `scale * 1.8 + 0.7`. Android and iOS preserve the authored name and same cRSubGoldy steering-sensitivity callsite while stubbing their platform body to 1.0.
float __cdecl resolve_uncaptured_cursor_sensitivity_scale(float scale)
{
  if ( is_mouse_captured(&g_game_base->players[0].mouse_cursor) != 0 )
    return 1.0;
  else
    return scale * 1.8 + 0.69999999;
}
