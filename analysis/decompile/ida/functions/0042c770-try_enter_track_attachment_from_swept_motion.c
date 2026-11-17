/* database: private replay copy of /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: try_enter_track_attachment_from_swept_motion @ 0x42c770 */
/* selector: try_enter_track_attachment_from_swept_motion */

// Scans `cRPath::secondary_samples` against the player's swept motion, using real vector subtraction in each sample-local frame. On acceptance it clears `Player::attachment_exit_pending`, seeds the Player-embedded `cRPathFollowGoldy`, copies the runtime row's installed heading into the cRPath, and immediately validates the candidate through one follow update. The caller rechecks the cleared byte before its secondary-slot probe, so a successful primary entry suppresses that fallback. Windows `cdb` confirmed shipped `ARCADE007` HalfPipe play reaches this entry family; Android and iOS name the broader owner `cRPath::Search(cRSubGoldy*, tVector, tVector, tVector, cRSubLoc*)` and independently confirm that the accepted tail hands off to `cRPathFollowGoldy`.
void __thiscall try_enter_track_attachment_from_swept_motion(
        cRPath *self,
        Vec3 position,
        Vec3 sweep,
        cRSubLoc *source_cell)
{
  uint32_t segment_count; // esi
  signed int v6; // esi
  signed int i; // ebp
  PathTemplateSample *v8; // ecx
  double v9; // st7
  PathTemplateSample *v10; // ecx
  double v11; // st7
  Vec3 vector; // [esp+14h] [ebp-60h] BYREF
  Vec3 anchor_position; // [esp+20h] [ebp-54h]
  Vec3 v14; // [esp+2Ch] [ebp-48h]
  Vec3 v15; // [esp+38h] [ebp-3Ch]
  Vec3 v16; // [esp+44h] [ebp-30h] BYREF
  float v17; // [esp+54h] [ebp-20h]
  float v18; // [esp+58h] [ebp-1Ch]
  float v19; // [esp+60h] [ebp-14h]
  float v20; // [esp+64h] [ebp-10h]
  float v21; // [esp+6Ch] [ebp-8h]
  float v22; // [esp+70h] [ebp-4h]

  segment_count = self->segment_count;
  anchor_position = source_cell->anchor_position;
  v6 = segment_count - 1;
  if ( v6 >= 0 )
  {
    for ( i = v6; ; --i )
    {
      v8 = &self->secondary_samples[i];
      if ( v8->transform.basis_up.y > 0.0 )
      {
        v9 = anchor_position.x + v8->transform.position.x;
        v17 = anchor_position.y + v8->transform.position.y;
        v18 = anchor_position.z + v8->transform.position.z;
        v14.x = position.x - v9;
        v14.y = position.y - v17;
        v14.z = position.z - v18;
        vector = v14;
        rotate_vector_by_matrix(&vector, &v8->inverse_matrix);
        if ( (double)((signed int)self->width_cells / -2) - 0.30000001 < vector.x
          && (double)((signed int)self->width_cells / 2) + 0.30000001 > vector.x
          && vector.y >= -0.2
          && vector.z > 0.0 )
        {
          v10 = &self->secondary_samples[i];
          if ( vector.z < (double)v10->delta_length )
          {
            v11 = anchor_position.x + v10->transform.position.x;
            v21 = anchor_position.y + v10->transform.position.y;
            v22 = anchor_position.z + v10->transform.position.z;
            v19 = position.y + sweep.y;
            v20 = position.z + sweep.z;
            v15.x = sweep.x + position.x - v11;
            v15.y = v19 - v21;
            v15.z = v20 - v22;
            v16 = v15;
            rotate_vector_by_matrix(&v16, &v10->inverse_matrix);
            if ( v16.y <= 0.001 )
              break;
          }
        }
      }
      if ( --v6 < 0 )
        return;
    }
    g_game_base->subgame.player.attachment_exit_pending = 0;
    start_squidge_y(&g_game_base->subgame.player.squidge, g_game_base->subgame.player.velocity.y);
    g_game_base->subgame.player.follow_state.active = 1;
    g_game_base->subgame.player.follow_state.template_record = self;
    g_game_base->subgame.player.follow_state.source_cell = source_cell;
    g_game_base->subgame.player.follow_state.sample_index = v6;
    g_game_base->subgame.player.follow_state.progress = vector.z;
    g_game_base->subgame.player.follow_state.vertical_offset = 0.0;
    g_game_base->subgame.player.body.transform.position.y = vector.y;
    g_game_base->subgame.player.velocity.y = 0.0;
    g_game_base->subgame.player.follow_state.player = &g_game_base->subgame.player;
    g_game_base->subgame.player.follow_state.template_record->installed_heading_delta = g_game_base->subgame.runtime_rows[get_track_cell_row_index(source_cell)].installed_heading_delta;
    g_game_base->subgame.player.follow_state.orientation_b = 0.0;
    g_game_base->subgame.player.follow_state.orientation_a = 0.0;
    update_track_attachment_follow_state(
      &g_game_base->subgame.player.follow_state,
      g_game_base->subgame.player.velocity.z,
      &g_game_base->subgame.player.body.transform.position,
      &g_game_base->subgame.player.velocity);
  }
}
