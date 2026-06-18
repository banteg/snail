/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: kill_slug_hazard @ 0x43f8b0 */
/* selector: kill_slug_hazard */

void __thiscall sub_43F8B0(int this)
{
  __int64 v2; // rax
  double v3; // st7

  if ( *(_DWORD *)(this + 128) == 1 )
  {
    v2 = (__int64)((double)next_math_random_value() * -0.000061035156);
    play_slug_voice(this, 28 - v2);
    v3 = *(float *)(this + 104);
    *(_DWORD *)(this + 128) = 2;
    if ( v3 <= 0.0 )
      *(_DWORD *)(this + 132) = 2;
    else
      *(_DWORD *)(this + 132) = 1;
    add_subgoldy_score((int *)(*(_DWORD *)(this + 136) + 3913572), SUBGOLDY_SCORE_SLUG, 0);
    explode_slug_hazard(this);
  }
}
