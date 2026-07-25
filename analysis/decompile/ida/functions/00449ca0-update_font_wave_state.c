/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_font_wave_state @ 0x449ca0 */
/* selector: update_font_wave_state */

// Void FontAI counterpart: advances the shared sine-wave text animation phases, wraps them into `[0, 2pi)`, and resets the transient font-wave bookkeeping lanes each frame. Its sole Windows caller discards EAX.
void __cdecl update_font_wave_state()
{
  double v0; // st7
  double v1; // st7

  v0 = g_font_wave_step_a + g_font_wave_phase_a;
  g_font_text_cursor = g_font_text_buffer;
  g_registered_font_count = 0;
  g_font_queue_count = 0;
  g_font_wave_phase_a = v0;
  if ( v0 > 6.2831855 )
    g_font_wave_phase_a = g_font_wave_phase_a - 6.2831855;
  v1 = g_font_wave_step_b + g_font_wave_phase_b;
  g_font_wave_phase_b = v1;
  if ( v1 > 6.2831855 )
    g_font_wave_phase_b = g_font_wave_phase_b - 6.2831855;
}
