/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: layout_and_queue_wrapped_font_text @ 0x44abe0 */
/* selector: layout_and_queue_wrapped_font_text */

// Splits one text string into wrapped line runs, queues each run through `queue_font_text_instance`, and returns the aligned authored-space origin and measured bounds for the wrapped block.
float *__cdecl sub_44ABE0(
        char *a1,
        int a2,
        int a3,
        float a4,
        float a5,
        float *a6,
        float *a7,
        float *a8,
        float *a9,
        int a10,
        char a11,
        int a12,
        int a13,
        int a14,
        int a15,
        char a16,
        char a17)
{
  int *v17; // eax
  char v18; // bl
  double v19; // st7
  float *result; // eax
  float v21; // [esp+0h] [ebp-430h]
  int v22; // [esp+14h] [ebp-41Ch]
  float v23; // [esp+18h] [ebp-418h]
  int v25[3]; // [esp+20h] [ebp-410h] BYREF
  float v26; // [esp+2Ch] [ebp-404h]
  char v27[1024]; // [esp+30h] [ebp-400h] BYREF

  Iostream_init::Iostream_init((#93 *)v25);
  v25[0] = *(_DWORD *)a15;
  v25[1] = *(_DWORD *)(a15 + 4);
  v25[2] = *(_DWORD *)(a15 + 8);
  v26 = *(float *)(a15 + 12);
  v23 = a4;
  *(float *)&v22 = a5;
  v17 = (int *)v27;
  do
  {
    v18 = *a1;
    if ( *a1 == 62 || !v18 )
    {
      *(_BYTE *)v17 = 0;
      if ( v17 != (int *)v27 )
      {
        v19 = measure_font_text_width(v27, a2, *(float *)&a3) + a4;
        if ( v19 > v23 )
          v23 = v19;
        if ( !a16 )
        {
          if ( a17 )
          {
            v21 = *(float *)&v22 * 0.0065449849;
            v26 = sine(v21);
          }
          queue_font_text_instance(v27, a2, a3, SLODWORD(a4), v22, a12, a13, a14, v25, a10, a11);
        }
      }
      v17 = (int *)v27;
      *(float *)&v22 = *(float *)&unk_777B18[522 * a2]
                     * *(float *)&unk_777B10[522 * a2]
                     * unk_777B04[522 * a2]
                     * *(float *)&a3
                     + *(float *)&v22;
    }
    else
    {
      *(_BYTE *)v17 = v18;
      v17 = (int *)((char *)v17 + 1);
    }
    ++a1;
  }
  while ( v18 );
  result = a6;
  *a6 = a4;
  *a7 = a5;
  *a8 = v23 - a4;
  *a9 = *(float *)&v22 - a5;
  switch ( a12 )
  {
    case 1:
      *a6 = *(float *)&a13 + 320.0;
      break;
    case 3:
      *a6 = *(float *)&a13 + 320.0 - *a8;
      break;
    case 2:
      *a6 = *(float *)&a13 + 320.0 - *a8 * 0.5;
      break;
  }
  return result;
}

