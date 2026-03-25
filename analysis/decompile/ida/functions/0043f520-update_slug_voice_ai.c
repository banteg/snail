/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_slug_voice_ai @ 0x43f520 */
/* selector: update_slug_voice_ai */

void __thiscall sub_43F520(int this)
{
  double v1; // st7

  if ( *(_BYTE *)(this + 216) )
  {
    v1 = *(float *)(this + 224) + *(float *)(this + 220);
    *(float *)(this + 220) = v1;
    if ( v1 > 1.0 )
    {
      *(_DWORD *)(this + 220) = 0;
      *(_BYTE *)(this + 216) = 0;
    }
  }
}

