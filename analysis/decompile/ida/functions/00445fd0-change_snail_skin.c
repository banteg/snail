/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: change_snail_skin @ 0x445fd0 */
/* selector: change_snail_skin */

// Exact Windows `SnailSkin::change_snail_skin`, authored as `cRSnailSkin::Change(int, float)`: selects a material slot and either applies it immediately or derives the 60 Hz transition step from the requested duration.
void __thiscall change_snail_skin(SnailSkin *snail_skin, int32_t slot_id, float duration_seconds)
{
  snail_skin->active = 1;
  snail_skin->progress = 0.0;
  if ( duration_seconds == 0.0 )
  {
    snail_skin->progress_step = 0.0;
    snail_skin->selected_slot = slot_id;
  }
  else
  {
    snail_skin->selected_slot = slot_id;
    snail_skin->progress_step = 1.0 / (duration_seconds * 60.0);
  }
}
