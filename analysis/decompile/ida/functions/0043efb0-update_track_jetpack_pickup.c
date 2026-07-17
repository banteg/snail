/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_track_jetpack_pickup @ 0x43efb0 */
/* selector: update_track_jetpack_pickup */

// Exact `cRJetPack::AI()`: runs the owned JetPack singleton through bobbing and teardown states, inlining the shared `cLinkedList<cRBod>::Remove` operation in both removal arms. The Windows constructor table at 0x497318 points directly here, while Android and iOS retain the authored member.
void __thiscall update_track_jetpack_pickup(JetPack *jetpack)
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
  double v13; // st7
  unsigned __int8 v15; // c0
  unsigned __int8 v16; // c3
  float v17; // [esp+0h] [ebp-Ch]

  if ( !jetpack->owner_game->subgame_pause_gate )
  {
    state = jetpack->state;
    if ( state )
    {
      v3 = state - 1;
      if ( v3 )
      {
        if ( v3 == 1 )
        {
          list_flags = jetpack->bod.bod.list_flags;
          jetpack->state = TRACK_PICKUP_STATE_INACTIVE;
          p_active_bod_list = &g_game_base->active_bod_list;
          if ( (list_flags & 0x200) == 0 )
          {
LABEL_6:
            report_errorf(aListRemove);
            kill_sprite((int)jetpack->sprite);
            return;
          }
          if ( (list_flags & 0x40) != 0 )
            goto LABEL_8;
          list_next = jetpack->bod.bod.list_next;
          if ( list_next )
            list_next->list_prev = jetpack->bod.bod.list_prev;
          list_prev = jetpack->bod.bod.list_prev;
          if ( list_prev )
          {
            list_prev->list_next = jetpack->bod.bod.list_next;
LABEL_21:
            jetpack->bod.bod.list_next = p_active_bod_list->free_top;
            p_active_bod_list->free_top = &jetpack->bod.bod;
            v11 = jetpack->bod.bod.list_flags;
            sprite = jetpack->sprite;
            BYTE1(v11) &= ~2u;
            jetpack->bod.bod.list_flags = v11;
            kill_sprite((int)sprite);
            return;
          }
          goto LABEL_20;
        }
      }
      else if ( jetpack->bod.position.z < (double)jetpack->owner->interaction_max_z )
      {
        v8 = jetpack->bod.bod.list_flags;
        jetpack->state = TRACK_PICKUP_STATE_INACTIVE;
        p_active_bod_list = &g_game_base->active_bod_list;
        if ( (v8 & 0x200) == 0 )
          goto LABEL_6;
        if ( (v8 & 0x40) != 0 )
        {
LABEL_8:
          report_errorf(aListRemoveNext);
          kill_sprite((int)jetpack->sprite);
          return;
        }
        v9 = jetpack->bod.bod.list_next;
        if ( v9 )
          v9->list_prev = jetpack->bod.bod.list_prev;
        v10 = jetpack->bod.bod.list_prev;
        if ( v10 )
        {
          v10->list_next = jetpack->bod.bod.list_next;
          goto LABEL_21;
        }
LABEL_20:
        p_active_bod_list->first = jetpack->bod.bod.list_next;
        goto LABEL_21;
      }
      v13 = jetpack->bob_phase_step + jetpack->bob_phase;
      jetpack->bob_phase = v13;
      if ( !(v15 | v16) )
        jetpack->bob_phase = v13 - 1.0;
      v17 = jetpack->bob_phase * 6.2831855;
      jetpack->sprite->position.y = sine(v17) * 0.30000001 + jetpack->bod.position.y;
    }
  }
}
