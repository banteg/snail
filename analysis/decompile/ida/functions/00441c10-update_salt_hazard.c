/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_salt_hazard @ 0x441c10 */
/* selector: update_salt_hazard */

// Exact Windows `cRSalt::AI()`: advances one live Salt fade state from the shared track z thresholds, updates its alpha tint, and retires the inherited BOD node at the far cutoff. The constructor table at 0x497340 points directly here; cross-port iOS preserves the owner.
void __thiscall update_salt_hazard(Salt *salt)
{
  SubgameRuntime *owner_game; // eax
  uint32_t v3; // ecx
  BodList *p_active_bod_list; // ecx
  uint32_t list_flags; // eax
  struct BodNode *list_next; // eax
  struct BodNode *list_prev; // eax
  uint32_t v8; // eax
  double v9; // st7
  char v11; // c0

  owner_game = salt->owner_game;
  if ( !owner_game->subgame_pause_gate )
  {
    v3 = salt->state - 1;
    if ( salt->state == 1 )
    {
      v9 = 1.0 - (salt->body.transform.position.z - owner_game->player.body.transform.position.z) * 0.021739131;
      salt->fade_alpha = v9;
      if ( v11 )
      {
        v9 = 0.0;
      }
      else if ( v9 > 1.0 )
      {
        v9 = 1.0;
      }
      salt->fade_alpha = v9;
      set_color_alpha(&salt->body.bod.color, 0.89999998);
      if ( salt->body.transform.position.z < (double)salt->owner_game->player.interaction_max_z )
        salt->state = 2;
    }
    else if ( v3 == 1 )
    {
      p_active_bod_list = &g_game_base->active_bod_list;
      list_flags = salt->body.bod.bod.list_flags;
      if ( (list_flags & 0x200) != 0 )
      {
        if ( (list_flags & 0x40) != 0 )
        {
          report_errorf(aListRemoveNext);
          salt->state = 0;
        }
        else
        {
          list_next = salt->body.bod.bod.list_next;
          if ( list_next )
            list_next->list_prev = salt->body.bod.bod.list_prev;
          list_prev = salt->body.bod.bod.list_prev;
          if ( list_prev )
            list_prev->list_next = salt->body.bod.bod.list_next;
          else
            p_active_bod_list->first = salt->body.bod.bod.list_next;
          salt->body.bod.bod.list_next = p_active_bod_list->free_top;
          p_active_bod_list->free_top = &salt->body.bod.bod;
          v8 = salt->body.bod.bod.list_flags;
          salt->state = 0;
          BYTE1(v8) &= ~2u;
          salt->body.bod.bod.list_flags = v8;
        }
      }
      else
      {
        report_errorf(aListRemove);
        salt->state = 0;
      }
    }
  }
}
