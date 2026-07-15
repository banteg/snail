/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_high_score_tables @ 0x417540 */
/* selector: initialize_high_score_tables */

// Seeds the cRSubHighScore owner’s postal, challenge, and completion arrays with blank cRSubSolution entries before ScoreA/B/C overlays are loaded.
void __thiscall initialize_high_score_tables(SubHighScore *bank)
{
  int v2; // esi
  SubSolution *postal_records; // edi
  int v4; // esi
  SubSolution *survival_records; // edi
  int v6; // esi
  SubSolution *time_trial_route_records; // edi

  v2 = 0;
  postal_records = bank->postal_records;
  do
    initialize_high_score_entry(postal_records++, 0, 0, 1065353216, 0, 0, v2++);
  while ( v2 < 11 );
  v4 = 0;
  survival_records = bank->survival_records;
  do
    initialize_high_score_entry(survival_records++, 0, 0, 1065353216, 0, 1, v4++);
  while ( v4 < 11 );
  v6 = 0;
  time_trial_route_records = bank->time_trial_route_records;
  do
    initialize_high_score_entry(time_trial_route_records++, 0, 0, 1065353216, 0, 2, v6++);
  while ( v6 < 51 );
  initialize_high_score_entry(&bank->current_result_record, 0, 0, 1065353216, 0, 0, 0);
}
