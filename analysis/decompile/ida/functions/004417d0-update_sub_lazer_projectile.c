/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_sub_lazer_projectile @ 0x4417d0 */
/* selector: update_sub_lazer_projectile */

// Windows `cRSubLazer::AI()`: returns recycle-pending projectiles through GameRoot's shared active BOD list, integrates one active SubLazer, distinguishes primary and secondary track-attachment hits with their native debug markers, and dispatches void Kill after collision or exit. The exact constructor table at 0x49733c points directly here, and Android/iOS preserve the authored owner. The honest Windows scratch is 97.25% with 218/218 instructions; only three commutative x87 add orders differ.
void __thiscall update_sub_lazer_projectile(SubLazer *sub_lazer)
{
  uint32_t list_flags; // eax
  FrameBodList *p_active_bod_list; // ecx
  struct BodNode *list_next; // eax
  struct BodNode *list_prev; // eax
  uint32_t v6; // eax
  double v7; // st7
  Vec4 *p_position; // edi
  TrackRowCell *track_grid_cell_at_world_position; // ebp
  SubRow *track_runtime_cell_at_world_z; // ebx
  int v11; // [esp+10h] [ebp-18h]
  float v12; // [esp+10h] [ebp-18h]
  int v13; // [esp+14h] [ebp-14h]
  float v14; // [esp+14h] [ebp-14h]
  int v15; // [esp+18h] [ebp-10h]
  float v16; // [esp+18h] [ebp-10h]
  float v17; // [esp+1Ch] [ebp-Ch]
  int v18; // [esp+1Ch] [ebp-Ch]
  float v19; // [esp+20h] [ebp-8h]
  int v20; // [esp+20h] [ebp-8h]
  float v21; // [esp+24h] [ebp-4h]
  int v22; // [esp+24h] [ebp-4h]

  if ( sub_lazer->owner_game->subgame_pause_gate )
    return;
  if ( sub_lazer->state == 1 )
  {
    v7 = sub_lazer->sprite_bob_phase_step + sub_lazer->sprite_bob_phase;
    sub_lazer->sprite_bob_phase = v7;
    if ( v7 > 1.0 )
    {
      sub_lazer->state = 2;
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
      if ( track_grid_cell_at_world_position->tile_id != 14 || sub_lazer->body.transform.position.y >= 7.0 )
      {
        if ( (track_runtime_cell_at_world_z->flags & 0x40) == 0
          || (*(float *)&v11 = sub_lazer->velocity.x * 1.05,
              *(float *)&v13 = sub_lazer->velocity.y * 1.05,
              *(float *)&v15 = sub_lazer->velocity.z * 1.05,
              v17 = sub_lazer->velocity.x + p_position->x,
              v19 = sub_lazer->velocity.y + sub_lazer->body.transform.position.y,
              v21 = sub_lazer->velocity.z + sub_lazer->body.transform.position.z,
              !is_point_inside_track_attachment(
                 &track_runtime_cell_at_world_z->primary_attachment_cell->attachment_template_record->bod.bod.vtable,
                 v17,
                 v19,
                 v21,
                 v11,
                 v13,
                 v15,
                 (float *)track_runtime_cell_at_world_z->primary_attachment_cell)) )
        {
          if ( SLOBYTE(track_runtime_cell_at_world_z->flags) >= 0 )
            return;
          *(float *)&v18 = sub_lazer->velocity.x * 1.05;
          *(float *)&v20 = sub_lazer->velocity.y * 1.05;
          *(float *)&v22 = sub_lazer->velocity.z * 1.05;
          v12 = sub_lazer->velocity.x + p_position->x;
          v14 = sub_lazer->velocity.y + sub_lazer->body.transform.position.y;
          v16 = sub_lazer->velocity.z + sub_lazer->body.transform.position.z;
          if ( !is_point_inside_track_attachment(
                  &track_runtime_cell_at_world_z->secondary_attachment_cell->attachment_template_record->bod.bod.vtable,
                  v12,
                  v14,
                  v16,
                  v18,
                  v20,
                  v22,
                  (float *)track_runtime_cell_at_world_z->secondary_attachment_cell) )
            return;
        }
        debug_report_stub();
      }
    }
    deactivate_sub_lazer_projectile(sub_lazer);
    return;
  }
  if ( sub_lazer->state == 2 )
  {
    list_flags = sub_lazer->body.bod.bod.list_flags;
    p_active_bod_list = &g_game_base->active_bod_list;
    if ( (list_flags & 0x200) != 0 )
    {
      if ( (list_flags & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
        sub_lazer->state = 0;
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
          p_active_bod_list->first = (FrameBodBase *)sub_lazer->body.bod.bod.list_next;
        sub_lazer->body.bod.bod.list_next = (struct BodNode *)p_active_bod_list->free_top;
        p_active_bod_list->free_top = (FrameBodBase *)sub_lazer;
        v6 = sub_lazer->body.bod.bod.list_flags;
        sub_lazer->state = 0;
        BYTE1(v6) &= ~2u;
        sub_lazer->body.bod.bod.list_flags = v6;
      }
    }
    else
    {
      report_errorf(aListRemove);
      sub_lazer->state = 0;
    }
  }
}
