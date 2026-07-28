/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_sub_lazer_projectile @ 0x4417d0 */
/* selector: update_sub_lazer_projectile */

// Windows `cRSubLazer::AI()`: returns SUB_LAZER_STATE_RECYCLE_PENDING actors through GameRoot's shared active BOD list, integrates SUB_LAZER_STATE_ACTIVE actors, distinguishes primary and secondary track-attachment hits with their native debug markers, and dispatches void Kill after collision or exit. The exact constructor table at 0x49733c points directly here, and Android/iOS preserve the authored owner. The honest Windows scratch is 97.25% with 218/218 instructions; only three commutative x87 add orders differ.
void __thiscall update_sub_lazer_projectile(SubLazer *sub_lazer)
{
  uint32_t list_flags; // eax
  BodList *active_bod_list; // ecx
  struct BodNode *list_next; // eax
  struct BodNode *list_prev; // eax
  uint32_t updated_list_flags; // eax
  double next_bob_phase; // st7
  Vec3 *position; // edi
  cRSubLoc *grid_cell; // ebp
  SubRow *runtime_row; // ebx
  Vec3 primary_swept_motion; // 0:^2C.12
  Vec3 secondary_probe; // 0:^2C.12
  Vec3 primary_probe; // 0:^38.12
  Vec3 secondary_swept_motion; // 0:^38.12

  if ( sub_lazer->owner_game->subgame_pause_gate == 0 )
  {
    if ( sub_lazer->state == SUB_LAZER_STATE_ACTIVE )
    {
      next_bob_phase = sub_lazer->sprite_bob_phase_step + sub_lazer->sprite_bob_phase;
      sub_lazer->sprite_bob_phase = next_bob_phase;
      if ( next_bob_phase > 1.0 )
      {
        sub_lazer->state = SUB_LAZER_STATE_RECYCLE_PENDING;
        return;
      }
      position = &sub_lazer->body.transform.position;
      sub_lazer->body.transform.position.x = sub_lazer->velocity.x + sub_lazer->body.transform.position.x;
      sub_lazer->body.transform.position.y = sub_lazer->velocity.y + sub_lazer->body.transform.position.y;
      sub_lazer->body.transform.position.z = sub_lazer->velocity.z + sub_lazer->body.transform.position.z;
      if ( sub_lazer->body.transform.position.y >= 0.0
        && sub_lazer->body.transform.position.z >= (double)sub_lazer->owner_game->player.interaction_max_z )
      {
        grid_cell = get_track_grid_cell_at_world_position(&g_game_base->subgame, &sub_lazer->body.transform.position);
        runtime_row = get_track_runtime_cell_at_world_z(&g_game_base->subgame, &sub_lazer->body.transform.position);
        if ( grid_cell->tile_id != SUBLOC_TILE_WALL2 || sub_lazer->body.transform.position.y >= 7.0 )
        {
          if ( (runtime_row->flags & 0x40) != 0
            && (primary_swept_motion.x = sub_lazer->velocity.x * 1.05,
                primary_swept_motion.y = sub_lazer->velocity.y * 1.05,
                primary_swept_motion.z = sub_lazer->velocity.z * 1.05,
                primary_probe.x = sub_lazer->velocity.x + position->x,
                primary_probe.y = sub_lazer->velocity.y + sub_lazer->body.transform.position.y,
                primary_probe.z = sub_lazer->velocity.z + sub_lazer->body.transform.position.z,
                is_point_inside_track_attachment(
                  runtime_row->primary_attachment_cell->attachment_template_record,
                  primary_probe,
                  primary_swept_motion,
                  runtime_row->primary_attachment_cell)) )
          {
            debug_report_stub(g_lazer_path_kill_format);
          }
          else
          {
            if ( SLOBYTE(runtime_row->flags) >= 0 )
              return;
            secondary_swept_motion.x = sub_lazer->velocity.x * 1.05;
            secondary_swept_motion.y = sub_lazer->velocity.y * 1.05;
            secondary_swept_motion.z = sub_lazer->velocity.z * 1.05;
            secondary_probe.x = sub_lazer->velocity.x + position->x;
            secondary_probe.y = sub_lazer->velocity.y + sub_lazer->body.transform.position.y;
            secondary_probe.z = sub_lazer->velocity.z + sub_lazer->body.transform.position.z;
            if ( !is_point_inside_track_attachment(
                    runtime_row->secondary_attachment_cell->attachment_template_record,
                    secondary_probe,
                    secondary_swept_motion,
                    runtime_row->secondary_attachment_cell) )
              return;
            debug_report_stub(g_lazer_path2_kill_format);
          }
        }
      }
      deactivate_sub_lazer_projectile(sub_lazer);
      return;
    }
    if ( sub_lazer->state == SUB_LAZER_STATE_RECYCLE_PENDING )
    {
      list_flags = sub_lazer->body.bod.bod.list_flags;
      active_bod_list = &g_game_base->active_bod_list;
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
          if ( list_next != nullptr )
            list_next->list_prev = sub_lazer->body.bod.bod.list_prev;
          list_prev = sub_lazer->body.bod.bod.list_prev;
          if ( list_prev != nullptr )
            list_prev->list_next = sub_lazer->body.bod.bod.list_next;
          else
            active_bod_list->first = sub_lazer->body.bod.bod.list_next;
          sub_lazer->body.bod.bod.list_next = active_bod_list->free_top;
          active_bod_list->free_top = &sub_lazer->body.bod.bod;
          updated_list_flags = sub_lazer->body.bod.bod.list_flags;
          sub_lazer->state = SUB_LAZER_STATE_INACTIVE;
          BYTE1(updated_list_flags) &= ~2u;
          sub_lazer->body.bod.bod.list_flags = updated_list_flags;
        }
      }
      else
      {
        report_errorf(aListRemove);
        sub_lazer->state = SUB_LAZER_STATE_INACTIVE;
      }
    }
  }
}
