/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: hit_slug_hazard @ 0x43f620 */
/* selector: hit_slug_hazard */

void __thiscall sub_43F620(int this, int a2)
{
  int v3; // ecx
  __int64 v4; // rax

  v3 = *(_DWORD *)(this + 200) - a2;
  *(_DWORD *)(this + 200) = v3;
  if ( v3 >= 0 )
  {
    *(_BYTE *)(this + 204) = 1;
    v4 = (__int64)((double)next_math_random_value() * -0.000091552734);
    play_slug_voice(this, 36 - v4);
  }
  else
  {
    *(_DWORD *)(this + 200) = 0;
    kill_slug_hazard(this);
  }
}

