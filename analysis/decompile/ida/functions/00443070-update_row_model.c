/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_row_model @ 0x443070 */
/* selector: update_row_model */

// Exact per-frame update for the `RowModel` embedded at `SubRow +0x04`: adds its velocity at model +0x80 to the inherited transform position, then recycles the model's intrusive body node once it crosses the live row threshold. iOS preserves the authored callback as `cRRowModel::AI()`.
void __thiscall update_row_model(RowModel *row_model)
{
  uint32_t list_flags; // eax
  BodList *p_active_bod_list; // edx
  struct BodNode *list_next; // eax
  struct BodNode *list_prev; // eax
  uint32_t v5; // eax

  row_model->body.transform.position.x = row_model->velocity.x + row_model->body.transform.position.x;
  row_model->body.transform.position.y = row_model->velocity.y + row_model->body.transform.position.y;
  row_model->body.transform.position.z = row_model->velocity.z + row_model->body.transform.position.z;
  if ( row_model->body.bod.object->bounds_max.z + g_game_base->subgame.player.interaction_max_z > row_model->body.transform.position.z )
  {
    list_flags = row_model->body.bod.bod.list_flags;
    p_active_bod_list = &g_game_base->active_bod_list;
    if ( (list_flags & 0x200) != 0 )
    {
      if ( (list_flags & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
      }
      else
      {
        list_next = row_model->body.bod.bod.list_next;
        if ( list_next )
          list_next->list_prev = row_model->body.bod.bod.list_prev;
        list_prev = row_model->body.bod.bod.list_prev;
        if ( list_prev )
          list_prev->list_next = row_model->body.bod.bod.list_next;
        else
          p_active_bod_list->first = row_model->body.bod.bod.list_next;
        row_model->body.bod.bod.list_next = p_active_bod_list->free_top;
        p_active_bod_list->free_top = &row_model->body.bod.bod;
        v5 = row_model->body.bod.bod.list_flags;
        BYTE1(v5) &= ~2u;
        row_model->body.bod.bod.list_flags = v5;
      }
    }
    else
    {
      report_errorf(aListRemove);
    }
  }
}
