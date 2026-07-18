/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_track_render_cache_rows @ 0x433b30 */
/* selector: update_track_render_cache_rows */

// Advances cRSegmentCache while Goldy’s current row stays ahead of the next cached row, linking the Floor, Slide, Warn, Ramp, and Fringe BOD slots into their active lists and seeding each slot color.
void __thiscall update_track_render_cache_rows(SegmentCache *manager)
{
  GameRoot *v2; // ecx
  struct BodNode *p_bod; // ecx
  TrackRenderCacheSlot *v4; // eax
  struct BodNode *list_next; // ecx
  Vec3 *p_position; // eax
  BodBase *p_track_body_list_head; // ecx
  TrackRenderCacheSlot *v8; // eax
  struct BodNode *v9; // ecx
  Vec3 *v10; // eax
  BodBase *v11; // ecx
  TrackRenderCacheSlot *v12; // eax
  struct BodNode *v13; // ecx
  Vec3 *v14; // eax
  BodBase *v15; // ecx
  TrackRenderCacheSlot *v16; // eax
  struct BodNode *v17; // ecx
  Vec3 *v18; // eax
  BodBase *v19; // ecx
  TrackRenderCacheSlot *v20; // eax
  struct BodNode *v21; // ecx
  Vec3 *v22; // eax
  double v23; // st7
  tColour out; // [esp+4h] [ebp-10h] BYREF

  v2 = g_game_base;
  if ( g_game_base->subgame.player.body.transform.position.z + 46.0 > manager->next_cache_row_z )
  {
    do
    {
      p_bod = &v2->subgame.fringe_attachment_list_head.bod;
      v4 = &manager->slots[manager->next_cache_row_index][4];
      if ( (manager->slots[manager->next_cache_row_index][4].bod.bod.list_flags & 0x200) != 0 )
      {
        report_errorf(aListAddafter);
      }
      else
      {
        manager->slots[manager->next_cache_row_index][4].bod.bod.list_prev = p_bod;
        v4->bod.bod.list_next = p_bod->list_next;
        p_bod->list_next = &v4->bod.bod;
        list_next = v4->bod.bod.list_next;
        if ( list_next )
          list_next->list_prev = &v4->bod.bod;
        v4->bod.bod.list_flags |= 0x200u;
      }
      p_position = &manager->slots[manager->next_cache_row_index][4].bod.position;
      p_position->z = 0.0;
      p_position->y = 0.0;
      p_position->x = 0.0;
      manager->slots[manager->next_cache_row_index][4].bod.color = *get_track_skirt_color(&g_game_base->subgame, &out);
      p_track_body_list_head = &g_game_base->subgame.track_body_list_head;
      v8 = manager->slots[manager->next_cache_row_index];
      if ( (manager->slots[manager->next_cache_row_index][0].bod.bod.list_flags & 0x200) != 0 )
      {
        report_errorf(aListAddafter);
      }
      else
      {
        manager->slots[manager->next_cache_row_index][0].bod.bod.list_prev = &p_track_body_list_head->bod;
        v8->bod.bod.list_next = p_track_body_list_head->bod.list_next;
        p_track_body_list_head->bod.list_next = &v8->bod.bod;
        v9 = v8->bod.bod.list_next;
        if ( v9 )
          v9->list_prev = &v8->bod.bod;
        v8->bod.bod.list_flags |= 0x200u;
      }
      v10 = &manager->slots[manager->next_cache_row_index][0].bod.position;
      v10->z = 0.0;
      v10->y = 0.0;
      v10->x = 0.0;
      set_color_white(&manager->slots[manager->next_cache_row_index][0].bod.color);
      v11 = &g_game_base->subgame.track_body_list_head;
      v12 = &manager->slots[manager->next_cache_row_index][1];
      if ( (manager->slots[manager->next_cache_row_index][1].bod.bod.list_flags & 0x200) != 0 )
      {
        report_errorf(aListAddafter);
      }
      else
      {
        manager->slots[manager->next_cache_row_index][1].bod.bod.list_prev = &v11->bod;
        v12->bod.bod.list_next = v11->bod.list_next;
        v11->bod.list_next = &v12->bod.bod;
        v13 = v12->bod.bod.list_next;
        if ( v13 )
          v13->list_prev = &v12->bod.bod;
        v12->bod.bod.list_flags |= 0x200u;
      }
      v14 = &manager->slots[manager->next_cache_row_index][1].bod.position;
      v14->z = 0.0;
      v14->y = 0.0;
      v14->x = 0.0;
      set_color_white(&manager->slots[manager->next_cache_row_index][1].bod.color);
      v15 = &g_game_base->subgame.track_body_list_head;
      v16 = &manager->slots[manager->next_cache_row_index][3];
      if ( (manager->slots[manager->next_cache_row_index][3].bod.bod.list_flags & 0x200) != 0 )
      {
        report_errorf(aListAddafter);
      }
      else
      {
        manager->slots[manager->next_cache_row_index][3].bod.bod.list_prev = &v15->bod;
        v16->bod.bod.list_next = v15->bod.list_next;
        v15->bod.list_next = &v16->bod.bod;
        v17 = v16->bod.bod.list_next;
        if ( v17 )
          v17->list_prev = &v16->bod.bod;
        v16->bod.bod.list_flags |= 0x200u;
      }
      v18 = &manager->slots[manager->next_cache_row_index][3].bod.position;
      v18->z = 0.0;
      v18->y = 0.0;
      v18->x = 0.0;
      set_color_white(&manager->slots[manager->next_cache_row_index][3].bod.color);
      v19 = &g_game_base->subgame.track_body_list_head;
      v20 = &manager->slots[manager->next_cache_row_index][2];
      if ( (manager->slots[manager->next_cache_row_index][2].bod.bod.list_flags & 0x200) != 0 )
      {
        report_errorf(aListAddafter);
      }
      else
      {
        manager->slots[manager->next_cache_row_index][2].bod.bod.list_prev = &v19->bod;
        v20->bod.bod.list_next = v19->bod.list_next;
        v19->bod.list_next = &v20->bod.bod;
        v21 = v20->bod.bod.list_next;
        if ( v21 )
          v21->list_prev = &v20->bod.bod;
        v20->bod.bod.list_flags |= 0x200u;
      }
      v22 = &manager->slots[manager->next_cache_row_index][2].bod.position;
      v22->z = 0.0;
      v22->y = 0.0;
      v22->x = 0.0;
      set_color_white(&manager->slots[manager->next_cache_row_index][2].bod.color);
      v23 = manager->next_cache_row_z + 24.0;
      ++manager->next_cache_row_index;
      manager->next_cache_row_z = v23;
      v2 = g_game_base;
    }
    while ( g_game_base->subgame.player.body.transform.position.z + 46.0 > v23 );
  }
}
