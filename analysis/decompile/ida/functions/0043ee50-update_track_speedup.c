/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_track_speedup @ 0x43ee50 */
/* selector: update_track_speedup */

// Exact `SubSpeedUp` AI: skips while the owner subgame is paused and tears down states 1/2 through the inherited BOD list. The exact Windows constructor table at 0x497314 points directly here, while Android and iOS retain `cRSubSpeedUp::AI()`.
void __thiscall update_track_speedup(SubSpeedUp *speedup)
{
  TrackPickupState state; // eax
  __int32 v3; // eax
  uint32_t list_flags; // eax
  BodList *p_active_bod_list; // ecx
  struct BodNode *list_next; // eax
  struct BodNode *list_prev; // eax
  uint32_t v8; // eax
  struct BodNode *v9; // eax
  struct BodNode *v10; // eax
  uint32_t v11; // eax
  Sprite *sprite; // ecx

  if ( !speedup->owner_game->subgame_pause_gate )
  {
    state = speedup->state;
    if ( state )
    {
      v3 = state - 1;
      if ( v3 )
      {
        if ( v3 != 1 )
          return;
        list_flags = speedup->body.bod.bod.list_flags;
        speedup->state = TRACK_PICKUP_STATE_INACTIVE;
        p_active_bod_list = &g_game_base->active_bod_list;
        if ( (list_flags & 0x200) == 0 )
          goto LABEL_6;
        if ( (list_flags & 0x40) != 0 )
        {
LABEL_8:
          report_errorf(aListRemoveNext);
          kill_sprite((int)speedup->sprite);
          return;
        }
        list_next = speedup->body.bod.bod.list_next;
        if ( list_next )
          list_next->list_prev = speedup->body.bod.bod.list_prev;
        list_prev = speedup->body.bod.bod.list_prev;
        if ( list_prev )
        {
          list_prev->list_next = speedup->body.bod.bod.list_next;
LABEL_21:
          speedup->body.bod.bod.list_next = p_active_bod_list->free_top;
          p_active_bod_list->free_top = &speedup->body.bod.bod;
          v11 = speedup->body.bod.bod.list_flags;
          sprite = speedup->sprite;
          BYTE1(v11) &= ~2u;
          speedup->body.bod.bod.list_flags = v11;
          kill_sprite((int)sprite);
          return;
        }
      }
      else
      {
        if ( speedup->body.transform.position.z >= (double)speedup->owner->interaction_max_z )
          return;
        v8 = speedup->body.bod.bod.list_flags;
        speedup->state = TRACK_PICKUP_STATE_INACTIVE;
        p_active_bod_list = &g_game_base->active_bod_list;
        if ( (v8 & 0x200) == 0 )
        {
LABEL_6:
          report_errorf(aListRemove);
          kill_sprite((int)speedup->sprite);
          return;
        }
        if ( (v8 & 0x40) != 0 )
          goto LABEL_8;
        v9 = speedup->body.bod.bod.list_next;
        if ( v9 )
          v9->list_prev = speedup->body.bod.bod.list_prev;
        v10 = speedup->body.bod.bod.list_prev;
        if ( v10 )
        {
          v10->list_next = speedup->body.bod.bod.list_next;
          goto LABEL_21;
        }
      }
      p_active_bod_list->first = speedup->body.bod.bod.list_next;
      goto LABEL_21;
    }
  }
}
