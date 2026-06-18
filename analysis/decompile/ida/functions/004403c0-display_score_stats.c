/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: display_score_stats @ 0x4403c0 */
/* selector: display_score_stats */

int __thiscall display_score_stats(RunScoreStats *stats)
{
  int total_score; // eax

  total_score = stats->total_score;
  if ( total_score )
  {
    debug_report_stub("\n Score Stats: %i\n", total_score);
    debug_report_stub("Garbage       :%i%%\n", 100 * stats->score_buckets[SUBGOLDY_SCORE_GARBAGE] / total_score);
    debug_report_stub("Slug          :%i%%\n", 100 * stats->score_buckets[SUBGOLDY_SCORE_SLUG] / total_score);
    debug_report_stub("Ring          :%i%%\n", 100 * stats->score_buckets[SUBGOLDY_SCORE_RING] / total_score);
    debug_report_stub("Parcel Collect:%i%%\n", 100 * stats->score_buckets[SUBGOLDY_SCORE_PARCEL_COLLECT] / total_score);
    debug_report_stub("Parcel Deliver:%i%%\n", 100 * stats->score_buckets[SUBGOLDY_SCORE_PARCEL_DELIVER] / total_score);
    debug_report_stub("Bonus         :%i%%\n", 100 * stats->score_buckets[SUBGOLDY_SCORE_BONUS] / total_score);
    return debug_report_stub("\n");
  }
  return total_score;
}
