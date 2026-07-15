/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: display_score_stats @ 0x4403c0 */
/* selector: display_score_stats */

// Void `Player` member that formats and displays Goldy's per-event score buckets. Its sole `complete_subgame` caller discards EAX; the terminal value is only the last debug-report call residue. Cross-port iOS symbols match this helper to `cRSubGoldy::ScoreStatsDisplay()` in `SubGame.o`.
void __thiscall display_score_stats(Player *player)
{
  if ( player->total_score )
  {
    debug_report_stub();
    debug_report_stub();
    debug_report_stub();
    debug_report_stub();
    debug_report_stub();
    debug_report_stub();
    debug_report_stub();
    debug_report_stub();
  }
}
