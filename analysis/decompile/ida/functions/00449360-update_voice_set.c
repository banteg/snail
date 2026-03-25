/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_voice_set @ 0x449360 */
/* selector: update_voice_set */

void __thiscall sub_449360(float *this)
{
  double v1; // st7

  if ( *(this + 4) > 0.0 )
  {
    v1 = *(this + 5) + *(this + 4);
    *(this + 4) = v1;
    if ( v1 > 1.0 )
      *(this + 4) = 0.0;
  }
}

