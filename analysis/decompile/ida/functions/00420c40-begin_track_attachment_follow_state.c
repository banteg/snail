/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: begin_track_attachment_follow_state @ 0x420c40 */
/* selector: begin_track_attachment_follow_state */

// Exact void initializer for the Player-embedded `cRPathFollowGoldy`: stores the selected cRPath and borrowed runtime cRSubLoc, resets the sample index, seeds progress from `world_z - cell_anchor_z`, seeds unclamped local height from `world_y - 0.49`, retains the Player backlink, and copies `SubgameRuntime::runtime_rows[row].installed_heading_delta` into the cRPath. Its only Windows caller discards EAX; the apparent cRPath result was the incidental value left by the final field store. Windows `cdb` confirmed shipped `ARCADE007` HalfPipe entries hit this helper with entry progress around `0.03595` and near-zero entry height. Android and iOS Path.o both preserve the exact authored symbol `cRPathFollowGoldy::Init(cRSubLoc*, tVector&, cRSubGoldy*)`; Windows independently supplies the 0x40-byte layout and offsets.
void __thiscall begin_track_attachment_follow_state(
        cRPathFollowGoldy *follow_state,
        cRSubLoc *source_cell,
        const Vec3 *world_position,
        Player *player)
{
  cRPath *attachment_template_record; // eax
  double v5; // st7

  follow_state->active = 1;
  attachment_template_record = source_cell->attachment_template_record;
  follow_state->source_cell = source_cell;
  follow_state->template_record = attachment_template_record;
  follow_state->sample_index = 0;
  follow_state->progress = world_position->z - source_cell->anchor_position.z;
  v5 = world_position->y - 0.49000001;
  follow_state->player = player;
  follow_state->vertical_offset = v5;
  follow_state->template_record->installed_heading_delta = g_game_base->subgame.runtime_rows[get_track_cell_row_index(source_cell)].installed_heading_delta;
}
