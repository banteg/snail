/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: refresh_fringe_object_draw_list @ 0x439b00 */
/* selector: refresh_fringe_object_draw_list */

// Windows cRFringe callback: copies the current track skirt tint into one authored Fringe and, once its world-z falls behind the live fringe threshold, unlinks it from the active list and requeues it onto the shared draw-list bucket. The constructor table points directly here; Android preserves `cRFringe::AI()` but implements it as a no-op.
void __thiscall refresh_fringe_object_draw_list(Fringe *fringe)
{
  tColour *track_skirt_color; // eax
  double z; // st7
  uint32_t list_flags; // eax
  BodList *p_active_bod_list; // ecx
  struct BodNode *list_next; // eax
  struct BodNode *list_prev; // eax
  uint32_t v8; // eax
  tColour out; // [esp+4h] [ebp-10h] BYREF

  track_skirt_color = get_track_skirt_color(&g_game_base->subgame, &out);
  z = fringe->bod.position.z;
  fringe->bod.color = *track_skirt_color;
  if ( z < g_game_base->subgame.player.interaction_max_z )
  {
    list_flags = fringe->bod.bod.list_flags;
    p_active_bod_list = &g_game_base->active_bod_list;
    if ( (list_flags & 0x200) != 0 )
    {
      if ( (list_flags & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
      }
      else
      {
        list_next = fringe->bod.bod.list_next;
        if ( list_next )
          list_next->list_prev = fringe->bod.bod.list_prev;
        list_prev = fringe->bod.bod.list_prev;
        if ( list_prev )
          list_prev->list_next = fringe->bod.bod.list_next;
        else
          p_active_bod_list->first = fringe->bod.bod.list_next;
        fringe->bod.bod.list_next = p_active_bod_list->free_top;
        p_active_bod_list->free_top = &fringe->bod.bod;
        v8 = fringe->bod.bod.list_flags;
        BYTE1(v8) &= ~2u;
        fringe->bod.bod.list_flags = v8;
      }
    }
    else
    {
      report_errorf(aListRemove);
    }
  }
}
