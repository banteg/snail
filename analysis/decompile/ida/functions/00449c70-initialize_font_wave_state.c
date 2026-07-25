/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_font_wave_state @ 0x449c70 */
/* selector: initialize_font_wave_state */

// Seeds the shared sine-wave text animation phases and per-tick phase increments that `draw_font_text_instance` consumes for wobble text.
void __cdecl initialize_font_wave_state()
{
  g_font_wave_phase_a = 0.0;
  g_font_wave_step_a = 0.10471976;
  g_font_wave_phase_b = 0.0;
  g_font_wave_step_b = 0.080553666;
}
