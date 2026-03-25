/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: draw_font_text_queue @ 0x44a730 */
/* selector: draw_font_text_queue */

// Iterates the live font text queue, retires dead entries, and draws the ones matching the supplied render mask.
char __cdecl sub_44A730(int a1)
{
  int v1; // eax
  int v2; // esi
  int v3; // ebx

  LOBYTE(v1) = unk_777B24;
  if ( unk_777B24 )
  {
    v2 = 132 * unk_777B24 + 7685352;
    v3 = unk_777B24;
    do
    {
      v1 = *(_DWORD *)(v2 - 132);
      v2 -= 132;
      if ( (a1 & v1 & 0xFF000000) != 0 )
      {
        if ( (v1 & 1) != 0 )
          LOBYTE(v1) = draw_font_text_instance(v2);
        else
          LOBYTE(v1) = draw_queued_font_quad_instance(v2);
      }
      --v3;
    }
    while ( v3 );
  }
  return v1;
}

