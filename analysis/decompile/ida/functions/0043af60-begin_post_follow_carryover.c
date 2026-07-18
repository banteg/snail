/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: begin_post_follow_carryover @ 0x43af60 */
/* selector: begin_post_follow_carryover */

// Begins Goldy's pending post-follow carryover window. If the active follow byte is still set, it copies `follow_state.orientation_b` into `post_follow_exit_roll` and the live attachment record's installed-heading bits into `post_follow_heading_carryover`, clears `follow_state.active`, sets `attachment_exit_pending`, latches player z into `attachment_exit_anchor_z`, and zeroes the exit-progress and gate bytes. Windows `cdb` confirmed this helper can also run after the active follow byte has already been cleared, so it is one real exit lane but not the only attachment-retirement path.
void __thiscall begin_post_follow_carryover(Player *player)
{
  float z; // edx

  if ( player->follow_state.active )
  {
    player->post_follow_heading_carryover = LODWORD(player->follow_state.template_record->installed_heading_delta);
    player->post_follow_exit_roll = player->follow_state.orientation_b;
  }
  else
  {
    player->post_follow_heading_carryover = 0;
    player->post_follow_exit_roll = 0.0;
  }
  z = player->body.transform.position.z;
  player->follow_state.active = 0;
  player->attachment_exit_pending = 1;
  player->attachment_exit_anchor_z = z;
  player->attachment_exit_progress = 0.0;
  player->attachment_exit_gate_a = 0;
  player->attachment_exit_gate_b = 0;
}
