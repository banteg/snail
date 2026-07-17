/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: mini_delete_high_score_entry @ 0x417af0 */
/* selector: mini_delete_high_score_entry */

// Deletes a canceled pending top-ten row by shifting later records upward through the active bank. Cross-port iOS symbols match this owner method to `cRSubHighScore::MiniDelete(int)`.
void __thiscall mini_delete_high_score_entry(SubHighScore *bank, int rank)
{
  int v2; // ebp
  int v3; // eax
  struct SubSolution *source_cursor; // ebx
  struct SubSolution *destination; // edi
  struct SubSolution *source; // esi

  v2 = rank;
  if ( rank < 10 )
  {
    v3 = rank;
    source_cursor = &bank->survival_records[rank + 1];
    do
    {
      destination = &bank->active_record_bank[v3];
      source = source_cursor;
      ++v3;
      ++source_cursor;
      qmemcpy(destination, source, sizeof(struct SubSolution));
      bank->active_record_bank[v3 - 1].route_or_rank_index = v2++;
    }
    while ( v3 < 10 );
  }
}
