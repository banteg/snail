/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_subgame @ 0x438850 */
/* selector: destroy_subgame */

// Tears down the active gameplay subgame state, including runtime lists, HUD widgets, and the current mode handoff state before control returns to the front-end. Cross-port Android and iOS symbols match this helper to `cRSubGame::UnInit()`.
void __thiscall destroy_subgame(SubgameRuntime *game)
{
  struct BodNode **p_list_next; // esi
  int v3; // ebx
  int v4; // eax
  BodList *p_active_bod_list; // ecx
  int v6; // eax
  struct BodNode *v7; // eax
  struct BodNode **v8; // esi
  int v9; // ebx
  int v10; // eax
  BodList *v11; // ecx
  int v12; // eax
  struct BodNode *v13; // eax
  struct BodNode **v14; // esi
  int v15; // ebx
  int v16; // eax
  BodList *v17; // ecx
  int v18; // eax
  struct BodNode *v19; // eax
  BodList *v20; // edx
  uint32_t list_flags; // ecx
  struct BodNode *list_next; // ecx
  struct BodNode *list_prev; // ecx
  uint32_t v24; // ecx
  FrontendWidget **life_stock_widgets; // esi
  int v26; // edi

  debug_report_stub();
  g_game_base->backdrop.unknown_65c = 1;
  if ( game->level_mode == 7 )
    uninit_tutorial(&game->tutorial);
  uninit_warning(&game->player.warning);
  clear_active_landscape_entries(&game->landscape_manager);
  uninit_times_up(&game->times_up);
  remove_subgame_bods(game);
  if ( game->subgame_state != 1 )
  {
    if ( game->level_mode <= 1u )
      flush_row_event_display(&game->completion);
    p_list_next = &game->sub_lazers.slots[0].body.bod.bod.list_next;
    v3 = 20;
    do
    {
      v4 = (int)*(p_list_next - 2);
      if ( (v4 & 0x200) != 0 )
      {
        p_active_bod_list = &g_game_base->active_bod_list;
        if ( (v4 & 0x40) != 0 )
        {
          report_errorf(aListRemoveNext);
        }
        else
        {
          if ( *p_list_next )
            (*p_list_next)->list_prev = *(p_list_next - 1);
          v6 = (int)*(p_list_next - 1);
          if ( v6 )
            *(_DWORD *)(v6 + 12) = *p_list_next;
          else
            p_active_bod_list->first = *p_list_next;
          *p_list_next = p_active_bod_list->free_top;
          p_active_bod_list->free_top = (BodNode *)(p_list_next - 3);
          v7 = *(p_list_next - 2);
          BYTE1(v7) &= ~2u;
          *(p_list_next - 2) = v7;
        }
      }
      p_list_next += 44;
      --v3;
    }
    while ( v3 );
    v8 = &game->salt_hazards.slots[0].body.bod.bod.list_next;
    v9 = 40;
    do
    {
      v10 = (int)*(v8 - 2);
      if ( (v10 & 0x200) != 0 )
      {
        v11 = &g_game_base->active_bod_list;
        if ( (v10 & 0x40) != 0 )
        {
          report_errorf(aListRemoveNext);
        }
        else
        {
          if ( *v8 )
            (*v8)->list_prev = *(v8 - 1);
          v12 = (int)*(v8 - 1);
          if ( v12 )
            *(_DWORD *)(v12 + 12) = *v8;
          else
            v11->first = *v8;
          *v8 = v11->free_top;
          v11->free_top = (BodNode *)(v8 - 3);
          v13 = *(v8 - 2);
          BYTE1(v13) &= ~2u;
          *(v8 - 2) = v13;
        }
      }
      v8 += 38;
      --v9;
    }
    while ( v9 );
    v14 = &game->banners.slots[0].bod.bod.list_next;
    v15 = 2;
    do
    {
      v16 = (int)*(v14 - 2);
      if ( (v16 & 0x200) != 0 )
      {
        v17 = &g_game_base->active_bod_list;
        if ( (v16 & 0x40) != 0 )
        {
          report_errorf(aListRemoveNext);
        }
        else
        {
          if ( *v14 )
            (*v14)->list_prev = *(v14 - 1);
          v18 = (int)*(v14 - 1);
          if ( v18 )
            *(_DWORD *)(v18 + 12) = *v14;
          else
            v17->first = *v14;
          *v14 = v17->free_top;
          v17->free_top = (BodNode *)(v14 - 3);
          v19 = *(v14 - 2);
          BYTE1(v19) &= ~2u;
          *(v14 - 2) = v19;
        }
      }
      v14 += 24;
      --v15;
    }
    while ( v15 );
  }
  if ( (game->barrier.bod.bod.list_flags & 0x200) != 0 )
  {
    v20 = &g_game_base->active_bod_list;
    list_flags = game->barrier.bod.bod.list_flags;
    if ( (list_flags & 0x200) != 0 )
    {
      if ( (list_flags & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
      }
      else
      {
        list_next = game->barrier.bod.bod.list_next;
        if ( list_next )
          list_next->list_prev = game->barrier.bod.bod.list_prev;
        list_prev = game->barrier.bod.bod.list_prev;
        if ( list_prev )
          list_prev->list_next = game->barrier.bod.bod.list_next;
        else
          v20->first = game->barrier.bod.bod.list_next;
        game->barrier.bod.bod.list_next = v20->free_top;
        v20->free_top = &game->barrier.bod.bod;
        v24 = game->barrier.bod.bod.list_flags;
        BYTE1(v24) &= ~2u;
        game->barrier.bod.bod.list_flags = v24;
      }
    }
    else
    {
      report_errorf(aListRemove);
    }
  }
  kill_border(&game->top_score_widget->list_kind);
  kill_border(&game->bottom_score_widget->list_kind);
  if ( game->selected_level_record_persistent )
  {
    g_game_base->players[0].saved_frontend_state = 18;
    game->selected_level_record_persistent = 0;
  }
  if ( game->level_mode == 3 )
    g_game_base->subgame.level_mode = 2;
  if ( !game->level_mode )
  {
    kill_border(&game->lives_icon_widget->list_kind);
    kill_border(&game->lives_text_widget->list_kind);
    life_stock_widgets = game->life_stock_widgets;
    v26 = 9;
    do
    {
      kill_border(*life_stock_widgets++);
      --v26;
    }
    while ( v26 );
  }
}
