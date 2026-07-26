/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: kill_subgoldy @ 0x445840 */
/* selector: kill_subgoldy */

// Exact void Windows `cRSubGoldy::Kill()`: begins the post-follow/falling carryover and moves Goldy's body to y = -8. Android preserves the same authored method as `FallingInit(this)` followed by the identical -8 body-height store.
void __thiscall kill_subgoldy(Player *player)
{
  begin_post_follow_carryover(player);
  player->body.transform.position.y = -8.0;
}
