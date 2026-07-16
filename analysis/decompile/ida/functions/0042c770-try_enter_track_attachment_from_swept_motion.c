/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: try_enter_track_attachment_from_swept_motion @ 0x42c770 */
/* selector: try_enter_track_attachment_from_swept_motion */

// Scans `Path::secondary_samples` against the player's swept motion, using real vector subtraction in each sample-local frame. On acceptance it clears `Player::attachment_exit_pending`, seeds the Player-embedded `FollowState`, copies the runtime row's installed heading into the Path, and immediately validates the candidate through one follow update. The caller rechecks the cleared byte before its secondary-slot probe, so a successful primary entry suppresses that fallback. Windows `cdb` confirmed shipped `ARCADE007` HalfPipe play reaches this entry family.
void __thiscall try_enter_track_attachment_from_swept_motion(
        Path *self,
        float world_x,
        float world_y,
        float world_z,
        float sweep_dx,
        float sweep_dy,
        float sweep_dz,
        TrackRowCell *source_cell)
{
  uint32_t segment_count; // esi
  signed int v10; // esi
  signed int i; // ebp
  const TransformMatrix *p_transform; // ecx
  double v13; // st7
  const TransformMatrix *v14; // ecx
  double v15; // st7
  Vec3 vector; // [esp+14h] [ebp-60h] BYREF
  Vec3 anchor_position; // [esp+20h] [ebp-54h]
  Vec3 v18; // [esp+2Ch] [ebp-48h]
  Vec3 v19; // [esp+38h] [ebp-3Ch]
  Vec3 v20; // [esp+44h] [ebp-30h] BYREF
  float v21; // [esp+54h] [ebp-20h]
  float v22; // [esp+58h] [ebp-1Ch]
  float v23; // [esp+60h] [ebp-14h]
  float v24; // [esp+64h] [ebp-10h]
  float v25; // [esp+6Ch] [ebp-8h]
  float v26; // [esp+70h] [ebp-4h]

  segment_count = self->segment_count;
  anchor_position = source_cell->anchor_position;
  v10 = segment_count - 1;
  if ( v10 >= 0 )
  {
    for ( i = v10; ; --i )
    {
      p_transform = &self->secondary_samples[i].transform;
      if ( p_transform->basis_up.y > 0.0 )
      {
        v13 = anchor_position.x + p_transform->position.x;
        v21 = anchor_position.y + p_transform->position.y;
        v22 = anchor_position.z + p_transform->position.z;
        v18.x = world_x - v13;
        v18.y = world_y - v21;
        v18.z = world_z - v22;
        vector = v18;
        rotate_vector_by_matrix(&vector, p_transform + 1);
        if ( (double)((signed int)self->width_cells / -2) - 0.30000001 < vector.x
          && (double)((signed int)self->width_cells / 2) + 0.30000001 > vector.x
          && vector.y >= -0.2
          && vector.z > 0.0 )
        {
          v14 = &self->secondary_samples[i].transform;
          if ( vector.z < (double)v14[2].basis_right.w )
          {
            v15 = anchor_position.x + v14->position.x;
            v25 = anchor_position.y + v14->position.y;
            v26 = anchor_position.z + v14->position.z;
            v23 = world_y + sweep_dy;
            v24 = world_z + sweep_dz;
            v19.x = sweep_dx + world_x - v15;
            v19.y = v23 - v25;
            v19.z = v24 - v26;
            v20 = v19;
            rotate_vector_by_matrix(&v20, v14 + 1);
            if ( v20.y <= 0.001 )
              break;
          }
        }
      }
      if ( --v10 < 0 )
        return;
    }
    g_game_base->subgame.player.attachment_exit_pending = 0;
    start_squidge_y(&g_game_base->subgame.player.squidge, g_game_base->subgame.player.velocity.y);
    g_game_base->subgame.player.follow_state.active = 1;
    g_game_base->subgame.player.follow_state.template_record = self;
    g_game_base->subgame.player.follow_state.source_cell = source_cell;
    g_game_base->subgame.player.follow_state.sample_index = v10;
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
      (Vec3 *)&g_game_base->subgame.player.body.transform.position,
      &g_game_base->subgame.player.velocity);
  }
}
