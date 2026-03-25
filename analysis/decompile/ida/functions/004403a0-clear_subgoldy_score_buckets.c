/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: clear_subgoldy_score_buckets @ 0x4403a0 */
/* selector: clear_subgoldy_score_buckets */

// Clears the six per-type score buckets that `add_subgoldy_score` and `display_score_stats` read on the live subgame runner owner, without touching the separate total-score or life lanes.
int __thiscall sub_4403A0(int this)
{
  memset((void *)(this + 784), 0, 0x18u);
  return 0;
}

