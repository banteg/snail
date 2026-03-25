/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: measure_font_text_width @ 0x449e90 */
/* selector: measure_font_text_width */

// Accumulates atlas slot widths for one string using the registered font's spacing scalar and trailing space padding.
double __cdecl sub_449E90(char *a1, int a2, float a3)
{
  char *v3; // ebp
  char v4; // al
  double v5; // st7
  float v7; // [esp+Ch] [ebp+4h]

  v3 = a1;
  v4 = *a1;
  v7 = 0.0;
  if ( v4 )
  {
    do
    {
      ++v3;
      v5 = unk_777704[522 * a2 + (char)font_slot_index_for_char(v4)] * *(float *)&unk_777B10[522 * a2];
      v4 = *v3;
      v7 = v5 * *(float *)&unk_777B14[522 * a2] * a3 + v7;
    }
    while ( *v3 );
  }
  return (1.0 - *(float *)&unk_777B14[522 * a2])
       * unk_777704[522 * a2 + (char)font_slot_index_for_char(32)]
       * *(float *)&unk_777B10[522 * a2]
       * a3
       + v7;
}

