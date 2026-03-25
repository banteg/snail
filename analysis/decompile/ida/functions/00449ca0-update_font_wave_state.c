/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_font_wave_state @ 0x449ca0 */
/* selector: update_font_wave_state */

// Advances the shared sine-wave text animation phases, wraps them into `[0, 2pi)`, and resets the transient font-wave bookkeeping lanes each frame.
void update_font_wave_state()
{
  double v0; // st7
  double v1; // st7

  v0 = unk_777B28 + unk_7772E8;
  unk_7772F0 = &unk_753CE8;
  unk_777B20 = 0;
  unk_777B24 = 0;
  unk_7772E8 = v0;
  if ( v0 > 6.2831855 )
    unk_7772E8 = unk_7772E8 - 6.2831855;
  v1 = unk_7772F4 + unk_7772EC;
  unk_7772EC = v1;
  if ( v1 > 6.2831855 )
    unk_7772EC = unk_7772EC - 6.2831855;
}

