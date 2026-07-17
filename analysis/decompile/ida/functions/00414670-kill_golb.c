/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: kill_golb @ 0x414670 */
/* selector: kill_golb */

void __thiscall kill_golb(GolbShot *shot)
{
  BodList *p_active_bod_list; // ecx
  uint32_t list_flags; // eax
  struct BodNode *list_next; // eax
  struct BodNode *list_prev; // eax
  uint32_t v6; // eax
  int32_t kind; // eax
  int v8; // eax
  BodList *v9; // edx
  uint32_t v10; // ecx
  struct BodNode *v11; // ecx
  struct BodNode *v12; // ecx
  uint32_t v13; // ecx
  ContactTargetObject *homing_target_object; // esi
  int32_t v15; // eax
  uint32_t v16; // ecx
  BodList *v17; // edx
  struct BodNode *v18; // ecx
  struct BodNode *v19; // ecx
  uint32_t v20; // ecx

  p_active_bod_list = &g_game_base->active_bod_list;
  list_flags = shot->primary_body.bod.bod.list_flags;
  if ( (list_flags & 0x200) != 0 )
  {
    if ( (list_flags & 0x40) != 0 )
    {
      report_errorf(aListRemoveNext);
    }
    else
    {
      list_next = shot->primary_body.bod.bod.list_next;
      if ( list_next )
        list_next->list_prev = shot->primary_body.bod.bod.list_prev;
      list_prev = shot->primary_body.bod.bod.list_prev;
      if ( list_prev )
        list_prev->list_next = shot->primary_body.bod.bod.list_next;
      else
        p_active_bod_list->first = shot->primary_body.bod.bod.list_next;
      shot->primary_body.bod.bod.list_next = p_active_bod_list->free_top;
      p_active_bod_list->free_top = &shot->primary_body.bod.bod;
      v6 = shot->primary_body.bod.bod.list_flags;
      BYTE1(v6) &= ~2u;
      shot->primary_body.bod.bod.list_flags = v6;
    }
  }
  else
  {
    report_errorf(aListRemove);
  }
  kind = shot->kind;
  shot->state = 0;
  if ( kind )
  {
    v8 = kind - 1;
    if ( v8 )
    {
      if ( v8 == 1 )
      {
        v9 = &g_game_base->active_bod_list;
        v10 = shot->tertiary_body.bod.bod.list_flags;
        if ( (v10 & 0x200) != 0 )
        {
          if ( (v10 & 0x40) != 0 )
          {
            report_errorf(aListRemoveNext);
          }
          else
          {
            v11 = shot->tertiary_body.bod.bod.list_next;
            if ( v11 )
              v11->list_prev = shot->tertiary_body.bod.bod.list_prev;
            v12 = shot->tertiary_body.bod.bod.list_prev;
            if ( v12 )
              v12->list_next = shot->tertiary_body.bod.bod.list_next;
            else
              v9->first = shot->tertiary_body.bod.bod.list_next;
            shot->tertiary_body.bod.bod.list_next = v9->free_top;
            v9->free_top = &shot->tertiary_body.bod.bod;
            v13 = shot->tertiary_body.bod.bod.list_flags;
            BYTE1(v13) &= ~2u;
            shot->tertiary_body.bod.bod.list_flags = v13;
          }
        }
        else
        {
          report_errorf(aListRemove);
        }
        homing_target_object = shot->homing_target_object;
        if ( homing_target_object )
        {
          v15 = homing_target_object->list_flags;
          BYTE1(v15) &= ~0x10u;
          homing_target_object->list_flags = v15;
        }
      }
    }
    else
    {
      v16 = shot->vapour.body.bod.bod.list_flags;
      v17 = &g_game_base->active_bod_list;
      if ( (v16 & 0x200) != 0 )
      {
        if ( (v16 & 0x40) != 0 )
        {
          report_errorf(aListRemoveNext);
        }
        else
        {
          v18 = shot->vapour.body.bod.bod.list_next;
          if ( v18 )
            v18->list_prev = shot->vapour.body.bod.bod.list_prev;
          v19 = shot->vapour.body.bod.bod.list_prev;
          if ( v19 )
            v19->list_next = shot->vapour.body.bod.bod.list_next;
          else
            v17->first = shot->vapour.body.bod.bod.list_next;
          shot->vapour.body.bod.bod.list_next = v17->free_top;
          v17->free_top = &shot->vapour.body.bod.bod;
          v20 = shot->vapour.body.bod.bod.list_flags;
          BYTE1(v20) &= ~2u;
          shot->vapour.body.bod.bod.list_flags = v20;
        }
      }
      else
      {
        report_errorf(aListRemove);
      }
    }
  }
  else
  {
    kill_sprite((int)shot->render_body_owner);
  }
}
