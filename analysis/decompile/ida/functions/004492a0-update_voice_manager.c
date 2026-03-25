/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_voice_manager @ 0x4492a0 */
/* selector: update_voice_manager */

void __thiscall sub_4492A0(float *this)
{
  float *v2; // esi
  int v3; // edi

  v2 = this;
  v3 = 16;
  do
  {
    update_voice_set(v2);
    v2 += 6;
    --v3;
  }
  while ( v3 );
  *(this + 96) = *(this + 96) + 0.016666668;
}

