/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: kill_slug_hazard @ 0x43f8b0 */
/* selector: kill_slug_hazard */

// Exact `Slug` kill transition from active to death-toss-pending: plays the death voice, records the right/left toss side, awards the slug score event through the containing SubgameRuntime's Player, and calls the explosion emitter. Android and iOS retain `cRSlug::Kill()`.
void __thiscall kill_slug_hazard(Slug *slug)
{
  __int64 v2; // rax
  double x; // st7

  if ( slug->state == SUB_SLUG_STATE_ACTIVE )
  {
    v2 = (__int64)((double)next_math_random_value() * -0.000061035156);
    play_slug_voice(slug, 28 - v2);
    x = slug->body.transform.position.x;
    slug->state = SUB_SLUG_STATE_DEATH_TOSS_PENDING;
    if ( x <= 0.0 )
      slug->death_toss_direction = SUB_SLUG_DEATH_TOSS_LEFT;
    else
      slug->death_toss_direction = SUB_SLUG_DEATH_TOSS_RIGHT;
    add_subgoldy_score(&slug->owner_game->player, 1, 0);
    explode_slug_hazard(slug);
  }
}
