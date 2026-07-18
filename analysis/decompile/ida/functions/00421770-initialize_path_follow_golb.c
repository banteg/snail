/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_path_follow_golb @ 0x421770 */
/* selector: initialize_path_follow_golb */

// Starts one Golb projectile attachment-follow session by borrowing the runtime `SubLoc`, its authored `Path`, and its world anchor; iOS Path.o names this owner family `cRPathFollowGolb::Init(cRSubLoc*, tVector&, cRSubGolb*)`.
int32_t __thiscall initialize_path_follow_golb(
        GolbPathFollowState *state,
        TrackRowCell *source_cell,
        const Vec3 *position,
        GolbShot *shot)
{
  Path *attachment_template_record; // edx
  double v5; // st7

  state->active = 1;
  attachment_template_record = source_cell->attachment_template_record;
  state->source_cell = source_cell;
  state->template_record = attachment_template_record;
  state->sample_index = 0;
  v5 = position->z - source_cell->anchor_position.z;
  state->shot = shot;
  state->progress = v5;
  state->vertical_offset = position->y - 0.49000001;
  return (int32_t)shot;
}
