/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: clear_subgoldy_score_buckets @ 0x4403a0 */
/* selector: clear_subgoldy_score_buckets */

// Void `Player` member that clears the six per-type score buckets shared by `add_subgoldy_score` and `display_score_stats`, without touching total score or life state. Both callers discard the final zero-register residue.
void __thiscall clear_subgoldy_score_buckets(Player *player)
{
  memset(player->score_buckets, 0, sizeof(player->score_buckets));
}
