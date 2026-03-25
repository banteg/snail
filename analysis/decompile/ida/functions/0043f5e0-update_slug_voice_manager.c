/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_slug_voice_manager @ 0x43f5e0 */
/* selector: update_slug_voice_manager */

void __thiscall sub_43F5E0(float *this)
{
  double v1; // st7

  if ( *(this + 1) > 0.0 )
  {
    v1 = *(this + 2) + *(this + 1);
    *(this + 1) = v1;
    if ( v1 > 1.0 )
    {
      *(this + 1) = 0.0;
      *(_BYTE *)this = 0;
    }
  }
}

