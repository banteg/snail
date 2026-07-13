/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: begin_track_attachment_follow_state @ 0x420c40 */
/* selector: begin_track_attachment_follow_state */

// Exact void initializer for the Player-embedded attachment `FollowState`: stores the selected Path and borrowed runtime cell, resets the sample index, seeds progress from `world_z - cell_anchor_z`, seeds unclamped local height from `world_y - 0.49`, retains the Player backlink, and copies `SubgameRuntime::runtime_rows[row].installed_heading_delta` into the Path. Its only Windows caller discards EAX; the apparent Path result was the incidental value left by the final field store. Windows `cdb` confirmed shipped `ARCADE007` HalfPipe entries hit this helper with entry progress around `0.03595` and near-zero entry height. iOS Path.o names it `cRPathFollowGoldy::Init(cRSubLoc*, tVector&, cRSubGoldy*)`.
void __thiscall begin_track_attachment_follow_state(
        FollowState *follow_state,
        TrackRowCell *source_cell,
        const Vec3 *world_position,
        Player *player)
{
  Path *attachment_template_record; // eax
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
  follow_state->template_record->installed_heading_delta = *(float *)((char *)&g_row_heading_table
                                                                    + (_DWORD)g_game_base
                                                                    + 244 * get_track_cell_row_index(source_cell));
}

