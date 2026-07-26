/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: remove_subgame_bods @ 0x440910 */
/* selector: remove_subgame_bods */

// Unlinks gameplay body lists and runtime pickup/hazard bods during subgame teardown. Cross-port iOS symbols match this helper to `cRSubGame::RemoveBods()` in `SubGame.o`.
void __thiscall remove_subgame_bods(SubgameRuntime *game)
{
  TrackRowCell *runtime_cell_cursor; // edi
  BodNode **row_list_next_cursor; // esi
  int i; // ebp
  BodList *p_active_bod_list; // ecx
  int v5; // eax
  int v6; // eax
  BodNode *v7; // eax
  int j; // ebx
  BodNode **health_list_next_cursor; // esi
  int k; // edi
  int v11; // eax
  BodList *v12; // ecx
  int v13; // eax
  BodNode *v14; // eax
  BodList *v15; // edx
  uint32_t list_flags; // ecx
  struct BodNode *list_next; // ecx
  struct BodNode *list_prev; // ecx
  uint32_t v19; // ecx
  uint32_t v20; // ecx
  BodList *v21; // edx
  struct BodNode *v22; // ecx
  struct BodNode *v23; // ecx
  uint32_t v24; // ecx
  BodNode **garbage_list_next_cursor; // esi
  int m; // edi
  int v27; // eax
  BodList *v28; // ecx
  int v29; // eax
  BodNode *v30; // eax
  BodNode **slug_list_next_cursor; // esi
  int n; // edi
  int v33; // eax
  BodList *v34; // ecx
  int v35; // eax
  BodNode *v36; // eax
  BodNode **ring_list_next_cursor; // esi
  int ii; // edi
  int v39; // eax
  BodList *v40; // ecx
  int v41; // eax
  BodNode *v42; // eax
  uint32_t v43; // eax
  BodList *v44; // ecx
  struct BodNode *v45; // eax
  struct BodNode *v46; // eax
  uint32_t v47; // eax
  BodList *v48; // edx
  uint32_t v49; // ecx
  struct BodNode *v50; // ecx
  struct BodNode *v51; // ecx
  uint32_t v52; // ecx
  uint32_t v53; // ecx
  BodList *v54; // edx
  struct BodNode *v55; // ecx
  struct BodNode *v56; // ecx
  uint32_t v57; // ecx
  uint32_t v58; // ecx
  BodList *v59; // edx
  struct BodNode *v60; // ecx
  struct BodNode *v61; // ecx
  uint32_t v62; // ecx
  GolbShot *golb_shot_cursor; // esi
  int jj; // edi

  runtime_cell_cursor = game->runtime_cells[0];
  row_list_next_cursor = &game->runtime_rows[0].row_model.body.bod.bod.list_next;
  for ( i = 3200; i != 0; --i )
  {
    if ( (((unsigned __int16)*(row_list_next_cursor - 2) >> 8) & 2) != 0 )
    {
      p_active_bod_list = &g_game_base->active_bod_list;
      v5 = (int)*(row_list_next_cursor - 2);
      if ( (v5 & 0x200) != 0 )
      {
        if ( (v5 & 0x40) != 0 )
        {
          report_errorf(aListRemoveNext);
        }
        else
        {
          if ( *row_list_next_cursor != nullptr )
            (*row_list_next_cursor)->list_prev = *(row_list_next_cursor - 1);
          v6 = (int)*(row_list_next_cursor - 1);
          if ( v6 != 0 )
            *(_DWORD *)(v6 + 12) = *row_list_next_cursor;
          else
            p_active_bod_list->first = *row_list_next_cursor;
          *row_list_next_cursor = p_active_bod_list->free_top;
          p_active_bod_list->free_top = (BodNode *)(row_list_next_cursor - 3);
          v7 = *(row_list_next_cursor - 2);
          BYTE1(v7) &= ~2u;
          *(row_list_next_cursor - 2) = v7;
        }
      }
      else
      {
        report_errorf(aListRemove);
      }
    }
    for ( j = 8; j != 0; --j )
      remove_sub_loc(runtime_cell_cursor++);
    row_list_next_cursor += 61;
  }
  remove_track_render_cache_bods(&game->segment_cache);
  health_list_next_cursor = &game->health_pickups[0].bod.bod.list_next;
  for ( k = 8; k != 0; --k )
  {
    v11 = (int)*(health_list_next_cursor - 2);
    if ( (v11 & 0x200) != 0 )
    {
      v12 = &g_game_base->active_bod_list;
      if ( (v11 & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
      }
      else
      {
        if ( *health_list_next_cursor != nullptr )
          (*health_list_next_cursor)->list_prev = *(health_list_next_cursor - 1);
        v13 = (int)*(health_list_next_cursor - 1);
        if ( v13 != 0 )
          *(_DWORD *)(v13 + 12) = *health_list_next_cursor;
        else
          v12->first = *health_list_next_cursor;
        *health_list_next_cursor = v12->free_top;
        v12->free_top = (BodNode *)(health_list_next_cursor - 3);
        v14 = *(health_list_next_cursor - 2);
        BYTE1(v14) &= ~2u;
        *(health_list_next_cursor - 2) = v14;
      }
      health_list_next_cursor[11] = nullptr;
    }
    health_list_next_cursor += 29;
  }
  if ( (game->speedup_pickup.body.bod.bod.list_flags & 0x200) != 0 )
  {
    v15 = &g_game_base->active_bod_list;
    list_flags = game->speedup_pickup.body.bod.bod.list_flags;
    if ( (list_flags & 0x200) != 0 )
    {
      if ( (list_flags & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
      }
      else
      {
        list_next = game->speedup_pickup.body.bod.bod.list_next;
        if ( list_next != nullptr )
          list_next->list_prev = game->speedup_pickup.body.bod.bod.list_prev;
        list_prev = game->speedup_pickup.body.bod.bod.list_prev;
        if ( list_prev != nullptr )
          list_prev->list_next = game->speedup_pickup.body.bod.bod.list_next;
        else
          v15->first = game->speedup_pickup.body.bod.bod.list_next;
        game->speedup_pickup.body.bod.bod.list_next = v15->free_top;
        v15->free_top = &game->speedup_pickup.body.bod.bod;
        v19 = game->speedup_pickup.body.bod.bod.list_flags;
        BYTE1(v19) &= ~2u;
        game->speedup_pickup.body.bod.bod.list_flags = v19;
      }
    }
    else
    {
      report_errorf(aListRemove);
    }
    game->speedup_pickup.state = TRACK_PICKUP_STATE_INACTIVE;
  }
  if ( (game->jetpack_pickup.bod.bod.list_flags & 0x200) != 0 )
  {
    v20 = game->jetpack_pickup.bod.bod.list_flags;
    v21 = &g_game_base->active_bod_list;
    if ( (v20 & 0x200) != 0 )
    {
      if ( (v20 & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
      }
      else
      {
        v22 = game->jetpack_pickup.bod.bod.list_next;
        if ( v22 != nullptr )
          v22->list_prev = game->jetpack_pickup.bod.bod.list_prev;
        v23 = game->jetpack_pickup.bod.bod.list_prev;
        if ( v23 != nullptr )
          v23->list_next = game->jetpack_pickup.bod.bod.list_next;
        else
          v21->first = game->jetpack_pickup.bod.bod.list_next;
        game->jetpack_pickup.bod.bod.list_next = v21->free_top;
        v21->free_top = &game->jetpack_pickup.bod.bod;
        v24 = game->jetpack_pickup.bod.bod.list_flags;
        BYTE1(v24) &= ~2u;
        game->jetpack_pickup.bod.bod.list_flags = v24;
      }
    }
    else
    {
      report_errorf(aListRemove);
    }
    game->jetpack_pickup.state = TRACK_PICKUP_STATE_INACTIVE;
  }
  garbage_list_next_cursor = &game->garbage_hazards.slots[0].body.bod.bod.list_next;
  for ( m = 50; m != 0; --m )
  {
    if ( (((unsigned __int16)*(garbage_list_next_cursor - 2) >> 8) & 2) != 0 )
    {
      garbage_list_next_cursor[30] = nullptr;
      v27 = (int)*(garbage_list_next_cursor - 2);
      v28 = &g_game_base->active_bod_list;
      if ( (v27 & 0x200) != 0 )
      {
        if ( (v27 & 0x40) != 0 )
        {
          report_errorf(aListRemoveNext);
        }
        else
        {
          if ( *garbage_list_next_cursor != nullptr )
            (*garbage_list_next_cursor)->list_prev = *(garbage_list_next_cursor - 1);
          v29 = (int)*(garbage_list_next_cursor - 1);
          if ( v29 != 0 )
            *(_DWORD *)(v29 + 12) = *garbage_list_next_cursor;
          else
            v28->first = *garbage_list_next_cursor;
          *garbage_list_next_cursor = v28->free_top;
          v28->free_top = (BodNode *)(garbage_list_next_cursor - 3);
          v30 = *(garbage_list_next_cursor - 2);
          BYTE1(v30) &= ~2u;
          *(garbage_list_next_cursor - 2) = v30;
        }
      }
      else
      {
        report_errorf(aListRemove);
      }
    }
    garbage_list_next_cursor += 49;
  }
  slug_list_next_cursor = &game->slug_hazards.slots[0].body.bod.bod.list_next;
  for ( n = 8; n != 0; --n )
  {
    if ( (((unsigned __int16)*(slug_list_next_cursor - 2) >> 8) & 2) != 0 )
    {
      slug_list_next_cursor[29] = nullptr;
      v33 = (int)*(slug_list_next_cursor - 2);
      v34 = &g_game_base->active_bod_list;
      if ( (v33 & 0x200) != 0 )
      {
        if ( (v33 & 0x40) != 0 )
        {
          report_errorf(aListRemoveNext);
        }
        else
        {
          if ( *slug_list_next_cursor != nullptr )
            (*slug_list_next_cursor)->list_prev = *(slug_list_next_cursor - 1);
          v35 = (int)*(slug_list_next_cursor - 1);
          if ( v35 != 0 )
            *(_DWORD *)(v35 + 12) = *slug_list_next_cursor;
          else
            v34->first = *slug_list_next_cursor;
          *slug_list_next_cursor = v34->free_top;
          v34->free_top = (BodNode *)(slug_list_next_cursor - 3);
          v36 = *(slug_list_next_cursor - 2);
          BYTE1(v36) &= ~2u;
          *(slug_list_next_cursor - 2) = v36;
        }
      }
      else
      {
        report_errorf(aListRemove);
      }
    }
    slug_list_next_cursor += 59;
  }
  ring_list_next_cursor = &game->ring_effects.slots[0].body.bod.bod.list_next;
  for ( ii = 2; ii != 0; --ii )
  {
    if ( ring_list_next_cursor[29] != nullptr )
    {
      v39 = (int)*(ring_list_next_cursor - 2);
      v40 = &g_game_base->active_bod_list;
      if ( (v39 & 0x200) != 0 )
      {
        if ( (v39 & 0x40) != 0 )
        {
          report_errorf(aListRemoveNext);
        }
        else
        {
          if ( *ring_list_next_cursor != nullptr )
            (*ring_list_next_cursor)->list_prev = *(ring_list_next_cursor - 1);
          v41 = (int)*(ring_list_next_cursor - 1);
          if ( v41 != 0 )
            *(_DWORD *)(v41 + 12) = *ring_list_next_cursor;
          else
            v40->first = *ring_list_next_cursor;
          *ring_list_next_cursor = v40->free_top;
          v40->free_top = (BodNode *)(ring_list_next_cursor - 3);
          v42 = *(ring_list_next_cursor - 2);
          BYTE1(v42) &= ~2u;
          *(ring_list_next_cursor - 2) = v42;
        }
      }
      else
      {
        report_errorf(aListRemove);
      }
    }
    ring_list_next_cursor[29] = nullptr;
    ring_list_next_cursor += 126;
  }
  if ( (game->player.body.bod.bod.list_flags & 0x200) != 0 )
  {
    v43 = game->player.body.bod.bod.list_flags;
    v44 = &g_game_base->active_bod_list;
    if ( (v43 & 0x200) != 0 )
    {
      if ( (v43 & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
      }
      else
      {
        v45 = game->player.body.bod.bod.list_next;
        if ( v45 != nullptr )
          v45->list_prev = game->player.body.bod.bod.list_prev;
        v46 = game->player.body.bod.bod.list_prev;
        if ( v46 != nullptr )
          v46->list_next = game->player.body.bod.bod.list_next;
        else
          v44->first = game->player.body.bod.bod.list_next;
        game->player.body.bod.bod.list_next = v44->free_top;
        v44->free_top = &game->player.body.bod.bod;
        v47 = game->player.body.bod.bod.list_flags;
        BYTE1(v47) &= ~2u;
        game->player.body.bod.bod.list_flags = v47;
      }
    }
    else
    {
      report_errorf(aListRemove);
    }
    v48 = &g_game_base->active_bod_list;
    v49 = game->player.presentation.body.bod.bod.list_flags;
    if ( (v49 & 0x200) != 0 )
    {
      if ( (v49 & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
      }
      else
      {
        v50 = game->player.presentation.body.bod.bod.list_next;
        if ( v50 != nullptr )
          v50->list_prev = game->player.presentation.body.bod.bod.list_prev;
        v51 = game->player.presentation.body.bod.bod.list_prev;
        if ( v51 != nullptr )
          v51->list_next = game->player.presentation.body.bod.bod.list_next;
        else
          v48->first = game->player.presentation.body.bod.bod.list_next;
        game->player.presentation.body.bod.bod.list_next = v48->free_top;
        v48->free_top = &game->player.presentation.body.bod.bod;
        v52 = game->player.presentation.body.bod.bod.list_flags;
        BYTE1(v52) &= ~2u;
        game->player.presentation.body.bod.bod.list_flags = v52;
      }
    }
    else
    {
      report_errorf(aListRemove);
    }
    v53 = game->player.presentation.jetpack_channel.body.bod.bod.list_flags;
    v54 = &g_game_base->active_bod_list;
    if ( (v53 & 0x200) != 0 )
    {
      if ( (v53 & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
      }
      else
      {
        v55 = game->player.presentation.jetpack_channel.body.bod.bod.list_next;
        if ( v55 != nullptr )
          v55->list_prev = game->player.presentation.jetpack_channel.body.bod.bod.list_prev;
        v56 = game->player.presentation.jetpack_channel.body.bod.bod.list_prev;
        if ( v56 != nullptr )
          v56->list_next = game->player.presentation.jetpack_channel.body.bod.bod.list_next;
        else
          v54->first = game->player.presentation.jetpack_channel.body.bod.bod.list_next;
        game->player.presentation.jetpack_channel.body.bod.bod.list_next = v54->free_top;
        v54->free_top = &game->player.presentation.jetpack_channel.body.bod.bod;
        v57 = game->player.presentation.jetpack_channel.body.bod.bod.list_flags;
        BYTE1(v57) &= ~2u;
        game->player.presentation.jetpack_channel.body.bod.bod.list_flags = v57;
      }
    }
    else
    {
      report_errorf(aListRemove);
    }
    v58 = game->player.presentation.weapon_channels[0].body.bod.bod.list_flags;
    v59 = &g_game_base->active_bod_list;
    if ( (v58 & 0x200) != 0 )
    {
      if ( (v58 & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
      }
      else
      {
        v60 = game->player.presentation.weapon_channels[0].body.bod.bod.list_next;
        if ( v60 != nullptr )
          v60->list_prev = game->player.presentation.weapon_channels[0].body.bod.bod.list_prev;
        v61 = game->player.presentation.weapon_channels[0].body.bod.bod.list_prev;
        if ( v61 != nullptr )
          v61->list_next = game->player.presentation.weapon_channels[0].body.bod.bod.list_next;
        else
          v59->first = game->player.presentation.weapon_channels[0].body.bod.bod.list_next;
        game->player.presentation.weapon_channels[0].body.bod.bod.list_next = v59->free_top;
        v59->free_top = &game->player.presentation.weapon_channels[0].body.bod.bod;
        v62 = game->player.presentation.weapon_channels[0].body.bod.bod.list_flags;
        BYTE1(v62) &= ~2u;
        game->player.presentation.weapon_channels[0].body.bod.bod.list_flags = v62;
      }
    }
    else
    {
      report_errorf(aListRemove);
    }
    recycle_bod_to_free_list(&g_game_base->active_bod_list, &game->player.presentation.weapon_channels[1].body.bod.bod);
    recycle_bod_to_free_list(&g_game_base->active_bod_list, &game->player.presentation.weapon_channels[2].body.bod.bod);
    recycle_bod_to_free_list(&g_game_base->active_bod_list, &game->player.presentation.invincible_shell.body.bod.bod);
    game->player.movement_mode_selector = 0;
    noop_runtime_ai();
  }
  golb_shot_cursor = game->player.golb_shots;
  for ( jj = 12; jj != 0; --jj )
  {
    if ( golb_shot_cursor->state == 1 )
      kill_golb(golb_shot_cursor);
    ++golb_shot_cursor;
  }
  if ( (game->player.click_start.bod.bod.bod.list_flags & 0x200) != 0 )
  {
    recycle_bod_to_free_list(&g_game_base->active_bod_list, &game->player.click_start.bod.bod.bod);
    game->player.click_start.state = CLICK_START_STATE_INACTIVE;
  }
  kill_game_sprites(&g_sprite_manager);
}
