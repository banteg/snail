/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_font_wave_state @ 0x449c70 */
/* selector: initialize_font_wave_state */

// Seeds the shared sine-wave text animation phases and per-tick phase increments that `draw_font_text_instance` consumes for wobble text.
void initialize_font_wave_state()
{
  unk_7772E8 = 0;
  unk_777B28 = 1037465424;
  unk_7772EC = 0;
  unk_7772F4 = 1034221906;
}

