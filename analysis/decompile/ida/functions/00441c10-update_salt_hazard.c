/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_salt_hazard @ 0x441c10 */
/* selector: update_salt_hazard */

// Exact Windows `cRSalt::AI()`: advances one live Salt fade state from the shared track z thresholds, updates its alpha tint, and retires the inherited BOD node at the far cutoff. The constructor table at 0x497340 points directly here; cross-port iOS preserves the owner.
void __thiscall update_salt_hazard(SaltHazardSlot *slot)
{
  SubgameRuntime *owner_game; // eax
  uint32_t v3; // ecx
  char *v4; // ecx
  uint32_t list_flags; // eax
  struct BodNode *list_next; // eax
  struct BodNode *list_prev; // eax
  uint32_t v8; // eax
  double v9; // st7
  char v11; // c0

  owner_game = slot->owner_game;
  if ( !owner_game->subgame_pause_gate )
  {
    v3 = slot->state - 1;
    if ( slot->state == 1 )
    {
      v9 = 1.0 - (*(float *)&slot->body.transform[56] - *(float *)&owner_game->player.body.transform[56]) * 0.021739131;
      slot->fade_alpha = v9;
      if ( v11 )
      {
        v9 = 0.0;
      }
      else if ( v9 > 1.0 )
      {
        v9 = 1.0;
      }
      slot->fade_alpha = v9;
      set_color_alpha(&slot->body.bod.color, 0.89999998);
      if ( *(float *)&slot->body.transform[56] < (double)slot->owner_game->player.interaction_max_z )
        slot->state = 2;
    }
    else if ( v3 == 1 )
    {
      v4 = (char *)g_game_base + 1448;
      list_flags = slot->body.bod.bod.list_flags;
      if ( (list_flags & 0x200) != 0 )
      {
        if ( (list_flags & 0x40) != 0 )
        {
          report_errorf(aListRemoveNext);
          slot->state = 0;
        }
        else
        {
          list_next = slot->body.bod.bod.list_next;
          if ( list_next )
            list_next->list_prev = slot->body.bod.bod.list_prev;
          list_prev = slot->body.bod.bod.list_prev;
          if ( list_prev )
            list_prev->list_next = slot->body.bod.bod.list_next;
          else
            *((_DWORD *)v4 + 1) = slot->body.bod.bod.list_next;
          slot->body.bod.bod.list_next = *((struct BodNode **)v4 + 2);
          *((_DWORD *)v4 + 2) = slot;
          v8 = slot->body.bod.bod.list_flags;
          slot->state = 0;
          BYTE1(v8) &= ~2u;
          slot->body.bod.bod.list_flags = v8;
        }
      }
      else
      {
        report_errorf(aListRemove);
        slot->state = 0;
      }
    }
  }
}
