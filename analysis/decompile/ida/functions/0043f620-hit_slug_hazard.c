/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: hit_slug_hazard @ 0x43f620 */
/* selector: hit_slug_hazard */

// Exact hit handler on one live `Slug`: decrements hit points, routes underflow to `Kill`, or arms the hit flash and voice response. Android and iOS retain `cRSlug::Hit(int)`.
void __thiscall hit_slug_hazard(Slug *slug, int32_t damage)
{
  int32_t v3; // ecx
  __int64 v4; // rax

  v3 = slug->hit_points - damage;
  slug->hit_points = v3;
  if ( v3 >= 0 )
  {
    slug->hit_flash_pending = 1;
    v4 = (__int64)((double)next_math_random_value() * -0.000091552734);
    play_slug_voice(slug, 36 - v4);
  }
  else
  {
    slug->hit_points = 0;
    kill_slug_hazard(slug);
  }
}
