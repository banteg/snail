/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: resolve_uncaptured_cursor_sensitivity_scale @ 0x44bc20 */
/* selector: resolve_uncaptured_cursor_sensitivity_scale */

// Returns the cursor-delta sensitivity scale for uncaptured pointer mode: 1.0 while the cursor is captured, otherwise arg * 1.8 + 0.7.
double __cdecl sub_44BC20(float a1)
{
  if ( is_mouse_captured((char *)MEMORY[0x4DF904] + 656) )
    return 1.0;
  else
    return a1 * 1.8 + 0.69999999;
}

