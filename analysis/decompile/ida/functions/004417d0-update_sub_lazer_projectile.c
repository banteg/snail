/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_sub_lazer_projectile @ 0x4417d0 */
/* selector: update_sub_lazer_projectile */

// Windows `cRSubLazer::AI()`: returns SUB_LAZER_STATE_RECYCLE_PENDING actors through GameRoot's shared active BOD list, integrates SUB_LAZER_STATE_ACTIVE actors, distinguishes primary and secondary track-attachment hits with their native debug markers, and dispatches void Kill after collision or exit. The exact constructor table at 0x49733c points directly here, and Android/iOS preserve the authored owner. The honest Windows scratch is 97.25% with 218/218 instructions; only three commutative x87 add orders differ.
void __thiscall update_sub_lazer_projectile(SubLazer *sub_lazer)
{
  uint32_t list_flags; // eax
  BodList *p_active_bod_list; // ecx
  struct BodNode *list_next; // eax
  struct BodNode *list_prev; // eax
  uint32_t v6; // eax
  double v7; // st7
  Vec4 *p_position; // edi
  TrackRowCell *track_grid_cell_at_world_position; // ebp
  SubRow *track_runtime_cell_at_world_z; // ebx
  Vec3 v11; // 0:^2C.12
  Vec3 v12; // 0:^2C.12
  Vec3 v13; // 0:^38.12
  Vec3 v14; // 0:^38.12

  if ( sub_lazer->owner_game->subgame_pause_gate )
    return;
  if ( sub_lazer->state == SUB_LAZER_STATE_ACTIVE )
  {
    v7 = sub_lazer->sprite_bob_phase_step + sub_lazer->sprite_bob_phase;
    sub_lazer->sprite_bob_phase = v7;
    if ( v7 > 1.0 )
    {
      sub_lazer->state = SUB_LAZER_STATE_RECYCLE_PENDING;
      return;
    }
    p_position = &sub_lazer->body.transform.position;
    sub_lazer->body.transform.position.x = sub_lazer->velocity.x + sub_lazer->body.transform.position.x;
    sub_lazer->body.transform.position.y = sub_lazer->velocity.y + sub_lazer->body.transform.position.y;
    sub_lazer->body.transform.position.z = sub_lazer->velocity.z + sub_lazer->body.transform.position.z;
    if ( sub_lazer->body.transform.position.y >= 0.0
      && sub_lazer->body.transform.position.z >= (double)sub_lazer->owner_game->player.interaction_max_z )
    {
      track_grid_cell_at_world_position = get_track_grid_cell_at_world_position(
                                            &g_game_base->subgame,
                                            (Vec3 *)&sub_lazer->body.transform.position);
      track_runtime_cell_at_world_z = get_track_runtime_cell_at_world_z(
                                        &g_game_base->subgame,
                                        (Vec3 *)&sub_lazer->body.transform.position);
      if ( track_grid_cell_at_world_position->tile_id != SUBLOC_TILE_WALL2
        || sub_lazer->body.transform.position.y >= 7.0 )
      {
        if ( (track_runtime_cell_at_world_z->flags & 0x40) == 0
          || (v11.x = sub_lazer->velocity.x * 1.05,
              v11.y = sub_lazer->velocity.y * 1.05,
              v11.z = sub_lazer->velocity.z * 1.05,
              v13.x = sub_lazer->velocity.x + p_position->x,
              v13.y = sub_lazer->velocity.y + sub_lazer->body.transform.position.y,
              v13.z = sub_lazer->velocity.z + sub_lazer->body.transform.position.z,
              !is_point_inside_track_attachment(
                 track_runtime_cell_at_world_z->primary_attachment_cell->attachment_template_record,
                 v13,
                 v11,
                 track_runtime_cell_at_world_z->primary_attachment_cell)) )
        {
          if ( SLOBYTE(track_runtime_cell_at_world_z->flags) >= 0 )
            return;
          v14.x = sub_lazer->velocity.x * 1.05;
          v14.y = sub_lazer->velocity.y * 1.05;
          v14.z = sub_lazer->velocity.z * 1.05;
          v12.x = sub_lazer->velocity.x + p_position->x;
          v12.y = sub_lazer->velocity.y + sub_lazer->body.transform.position.y;
          v12.z = sub_lazer->velocity.z + sub_lazer->body.transform.position.z;
          if ( !is_point_inside_track_attachment(
                  track_runtime_cell_at_world_z->secondary_attachment_cell->attachment_template_record,
                  v12,
                  v14,
                  track_runtime_cell_at_world_z->secondary_attachment_cell) )
            return;
        }
        debug_report_stub();
      }
    }
    deactivate_sub_lazer_projectile(sub_lazer);
    return;
  }
  if ( sub_lazer->state == SUB_LAZER_STATE_RECYCLE_PENDING )
  {
    list_flags = sub_lazer->body.bod.bod.list_flags;
    p_active_bod_list = &g_game_base->active_bod_list;
    if ( (list_flags & 0x200) != 0 )
    {
      if ( (list_flags & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
        sub_lazer->state = SUB_LAZER_STATE_INACTIVE;
      }
      else
      {
        list_next = sub_lazer->body.bod.bod.list_next;
        if ( list_next )
          list_next->list_prev = sub_lazer->body.bod.bod.list_prev;
        list_prev = sub_lazer->body.bod.bod.list_prev;
        if ( list_prev )
          list_prev->list_next = sub_lazer->body.bod.bod.list_next;
        else
          p_active_bod_list->first = sub_lazer->body.bod.bod.list_next;
        sub_lazer->body.bod.bod.list_next = p_active_bod_list->free_top;
        p_active_bod_list->free_top = &sub_lazer->body.bod.bod;
        v6 = sub_lazer->body.bod.bod.list_flags;
        sub_lazer->state = SUB_LAZER_STATE_INACTIVE;
        BYTE1(v6) &= ~2u;
        sub_lazer->body.bod.bod.list_flags = v6;
      }
    }
    else
    {
      report_errorf(aListRemove);
      sub_lazer->state = SUB_LAZER_STATE_INACTIVE;
    }
  }
}
