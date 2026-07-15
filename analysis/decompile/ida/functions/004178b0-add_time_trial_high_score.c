/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: add_time_trial_high_score @ 0x4178b0 */
/* selector: add_time_trial_high_score */

// Records one per-route time-trial result into the completion bank, replacing the stored entry only when the new time beats the existing route record. Cross-port Android and iOS symbols match this helper to `cRSubHighScore::AddTimeTrial(int, bool)`.
void __thiscall add_time_trial_high_score(
        SubHighScore *bank,
        SubSolution *record,
        int route_index,
        unsigned __int8 route_active)
{
  char *v4; // ebp

  record->high_score_mode_tag = 2;
  record->route_or_rank_index = route_index;
  record->replay_cursor = 0;
  if ( !route_active )
    record->score_or_time.score_buckets[0] = 0;
  qmemcpy(&bank->current_result_record, record, sizeof(bank->current_result_record));
  if ( route_active )
  {
    v4 = (char *)bank + 129728 * route_index;
    if ( record->score_or_time.total_seconds < (double)*((float *)v4 + 713508) || *((float *)v4 + 713508) == 0.0 )
    {
      qmemcpy(v4 + 2854024, record, 0x1FAC0u);
      *((_DWORD *)v4 + 713522) = route_index;
    }
  }
}
