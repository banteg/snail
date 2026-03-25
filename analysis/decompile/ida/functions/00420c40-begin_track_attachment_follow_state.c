/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: begin_track_attachment_follow_state @ 0x420c40 */
/* selector: begin_track_attachment_follow_state */

// Starts one live attachment-follow session from the selected runtime attachment cell by marking the follow struct active, storing the template and owner cell, zeroing the segment index, seeding progress from `world_z - cell_anchor_z`, seeding local height from `world_y - 0.49`, caching the player pointer, and copying the row payload into template `+0x98`. Windows `cdb` confirmed shipped `ARCADE007` HalfPipe entries hit this helper with entry progress around `0.03595` and near-zero entry height.
PathTemplate *__thiscall begin_track_attachment_follow_state(
        FollowState *follow_state,
        TrackRowCell *source_cell,
        Vec3 *world_position,
        Player *player)
{
  PathTemplate *attachment_template_record; // eax
  double v6; // st7
  int v7; // edx
  PathTemplate *result; // eax

  follow_state->active = 1;
  attachment_template_record = source_cell->attachment_template_record;
  follow_state->source_cell = source_cell;
  follow_state->template_record = attachment_template_record;
  follow_state->sample_index = 0;
  follow_state->progress = world_position->z - source_cell->anchor_position.z;
  v6 = world_position->y - 0.49000001;
  follow_state->player = player;
  follow_state->vertical_offset = v6;
  v7 = 61 * get_track_cell_row_index(source_cell);
  result = follow_state->template_record;
  result->installed_heading_delta = *(float *)((char *)&unk_64118C + (_DWORD)MEMORY[0x4DF904] + 4 * v7);
  return result;
}

