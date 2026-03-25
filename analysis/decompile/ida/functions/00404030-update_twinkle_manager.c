/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_twinkle_manager @ 0x404030 */
/* selector: update_twinkle_manager */

int __thiscall sub_404030(_DWORD *this)
{
  int result; // eax
  int v3; // esi
  float *v4; // edi

  result = *(this + 60) - 1;
  if ( *(this + 60) == 1 )
  {
    result = *(this + 61);
    v3 = 0;
    if ( result > 0 )
    {
      v4 = (float *)this;
      do
      {
        update_twinkle(v4);
        result = *(this + 61);
        ++v3;
        v4 += 12;
      }
      while ( v3 < result );
    }
  }
  return result;
}

