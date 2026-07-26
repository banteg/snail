/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: clear_subgoldy_score_buckets @ 0x4403a0 */
/* selector: clear_subgoldy_score_buckets */

// Exact void Windows `cRSubGoldy::ScoreStatsInit()`: clears the per-event score-stat block shared by `add_subgoldy_score` and `display_score_stats`, without touching total score or life state. Windows has six buckets while Android and iOS clear seven in their port-specific Goldy layout; the owner and initialization role are otherwise exact.
void __thiscall clear_subgoldy_score_buckets(Player *player)
{
  memset(player->score_buckets, 0, sizeof(player->score_buckets));
}
