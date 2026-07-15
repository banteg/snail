/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: remove_subgame_bods @ 0x440910 */
/* selector: remove_subgame_bods */

// Unlinks gameplay body lists and runtime pickup/hazard bods during subgame teardown. Cross-port iOS symbols match this helper to `cRSubGame::RemoveBods()` in `SubGame.o`.
void __thiscall remove_subgame_bods(SubgameRuntime *game)
{
  TrackRowCell *v1; // edi
  char *v2; // esi
  int v3; // ebp
  FrameBodList *p_active_bod_list; // ecx
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // ebx
  struct BodNode **p_list_next; // esi
  int v10; // edi
  int v11; // eax
  FrameBodList *v12; // ecx
  int v13; // eax
  struct BodNode *v14; // eax
  FrameBodList *v15; // edx
  uint32_t list_flags; // ecx
  struct BodNode *list_next; // ecx
  struct BodNode *list_prev; // ecx
  uint32_t v19; // ecx
  uint32_t v20; // ecx
  FrameBodList *v21; // edx
  struct BodNode *v22; // ecx
  struct BodNode *v23; // ecx
  uint32_t v24; // ecx
  struct BodNode **v25; // esi
  int v26; // edi
  int v27; // eax
  FrameBodList *v28; // ecx
  int v29; // eax
  struct BodNode *v30; // eax
  struct BodNode **v31; // esi
  int v32; // edi
  int v33; // eax
  FrameBodList *v34; // ecx
  int v35; // eax
  struct BodNode *v36; // eax
  struct BodNode **v37; // esi
  int v38; // edi
  int v39; // eax
  FrameBodList *v40; // ecx
  int v41; // eax
  struct BodNode *v42; // eax
  uint32_t v43; // eax
  FrameBodList *v44; // ecx
  struct BodNode *v45; // eax
  struct BodNode *v46; // eax
  uint32_t v47; // eax
  FrameBodList *v48; // edx
  uint32_t v49; // ecx
  struct BodNode *v50; // ecx
  struct BodNode *v51; // ecx
  uint32_t v52; // ecx
  uint32_t v53; // ecx
  FrameBodList *v54; // edx
  struct BodNode *v55; // ecx
  struct BodNode *v56; // ecx
  uint32_t v57; // ecx
  uint32_t v58; // ecx
  FrameBodList *v59; // edx
  struct BodNode *v60; // ecx
  struct BodNode *v61; // ecx
  uint32_t v62; // ecx
  GolbShot *golb_shots; // esi
  int v64; // edi

  v1 = game->runtime_cells[0];
  v2 = (char *)&unk_5CCAD8 + (_DWORD)game;
  v3 = 3200;
  do
  {
    if ( (*((_DWORD *)v2 - 2) & 0x200) != 0 )
    {
      p_active_bod_list = &g_game_base->active_bod_list;
      v5 = *((_DWORD *)v2 - 2);
      if ( (v5 & 0x200) != 0 )
      {
        if ( (v5 & 0x40) != 0 )
        {
          report_errorf(aListRemoveNext);
        }
        else
        {
          if ( *(_DWORD *)v2 )
            *(_DWORD *)(*(_DWORD *)v2 + 8) = *((_DWORD *)v2 - 1);
          v6 = *((_DWORD *)v2 - 1);
          if ( v6 )
            *(_DWORD *)(v6 + 12) = *(_DWORD *)v2;
          else
            p_active_bod_list->first = *(FrameBodBase **)v2;
          *(_DWORD *)v2 = p_active_bod_list->free_top;
          p_active_bod_list->free_top = (FrameBodBase *)(v2 - 12);
          v7 = *((_DWORD *)v2 - 2);
          BYTE1(v7) &= ~2u;
          *((_DWORD *)v2 - 2) = v7;
        }
      }
      else
      {
        report_errorf(aListRemove);
      }
    }
    v8 = 8;
    do
    {
      remove_sub_loc(v1++);
      --v8;
    }
    while ( v8 );
    v2 += 244;
    --v3;
  }
  while ( v3 );
  remove_track_render_cache_bods(&game->segment_cache);
  p_list_next = &game->health_pickups[0].bod.list_next;
  v10 = 8;
  do
  {
    v11 = (int)*(p_list_next - 2);
    if ( (v11 & 0x200) != 0 )
    {
      v12 = &g_game_base->active_bod_list;
      if ( (v11 & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
      }
      else
      {
        if ( *p_list_next )
          (*p_list_next)->list_prev = *(p_list_next - 1);
        v13 = (int)*(p_list_next - 1);
        if ( v13 )
          *(_DWORD *)(v13 + 12) = *p_list_next;
        else
          v12->first = (FrameBodBase *)*p_list_next;
        *p_list_next = (struct BodNode *)v12->free_top;
        v12->free_top = (FrameBodBase *)(p_list_next - 3);
        v14 = *(p_list_next - 2);
        BYTE1(v14) &= ~2u;
        *(p_list_next - 2) = v14;
      }
      p_list_next[11] = nullptr;
    }
    p_list_next += 29;
    --v10;
  }
  while ( v10 );
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
        if ( list_next )
          list_next->list_prev = game->speedup_pickup.body.bod.bod.list_prev;
        list_prev = game->speedup_pickup.body.bod.bod.list_prev;
        if ( list_prev )
          list_prev->list_next = game->speedup_pickup.body.bod.bod.list_next;
        else
          v15->first = (FrameBodBase *)game->speedup_pickup.body.bod.bod.list_next;
        game->speedup_pickup.body.bod.bod.list_next = (struct BodNode *)v15->free_top;
        v15->free_top = (FrameBodBase *)&game->speedup_pickup;
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
  if ( (game->jetpack_pickup.bod.list_flags & 0x200) != 0 )
  {
    v20 = game->jetpack_pickup.bod.list_flags;
    v21 = &g_game_base->active_bod_list;
    if ( (v20 & 0x200) != 0 )
    {
      if ( (v20 & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
      }
      else
      {
        v22 = game->jetpack_pickup.bod.list_next;
        if ( v22 )
          v22->list_prev = game->jetpack_pickup.bod.list_prev;
        v23 = game->jetpack_pickup.bod.list_prev;
        if ( v23 )
          v23->list_next = game->jetpack_pickup.bod.list_next;
        else
          v21->first = (FrameBodBase *)game->jetpack_pickup.bod.list_next;
        game->jetpack_pickup.bod.list_next = (struct BodNode *)v21->free_top;
        v21->free_top = (FrameBodBase *)&game->jetpack_pickup;
        v24 = game->jetpack_pickup.bod.list_flags;
        BYTE1(v24) &= ~2u;
        game->jetpack_pickup.bod.list_flags = v24;
      }
    }
    else
    {
      report_errorf(aListRemove);
    }
    game->jetpack_pickup.state = TRACK_PICKUP_STATE_INACTIVE;
  }
  v25 = &game->garbage_hazards.slots[0].body.bod.bod.list_next;
  v26 = 50;
  do
  {
    if ( (((unsigned __int16)*(v25 - 2) >> 8) & 2) != 0 )
    {
      v25[30] = nullptr;
      v27 = (int)*(v25 - 2);
      v28 = &g_game_base->active_bod_list;
      if ( (v27 & 0x200) != 0 )
      {
        if ( (v27 & 0x40) != 0 )
        {
          report_errorf(aListRemoveNext);
        }
        else
        {
          if ( *v25 )
            (*v25)->list_prev = *(v25 - 1);
          v29 = (int)*(v25 - 1);
          if ( v29 )
            *(_DWORD *)(v29 + 12) = *v25;
          else
            v28->first = (FrameBodBase *)*v25;
          *v25 = (struct BodNode *)v28->free_top;
          v28->free_top = (FrameBodBase *)(v25 - 3);
          v30 = *(v25 - 2);
          BYTE1(v30) &= ~2u;
          *(v25 - 2) = v30;
        }
      }
      else
      {
        report_errorf(aListRemove);
      }
    }
    v25 += 49;
    --v26;
  }
  while ( v26 );
  v31 = &game->slug_hazards.slots[0].body.bod.bod.list_next;
  v32 = 8;
  do
  {
    if ( (((unsigned __int16)*(v31 - 2) >> 8) & 2) != 0 )
    {
      v31[29] = nullptr;
      v33 = (int)*(v31 - 2);
      v34 = &g_game_base->active_bod_list;
      if ( (v33 & 0x200) != 0 )
      {
        if ( (v33 & 0x40) != 0 )
        {
          report_errorf(aListRemoveNext);
        }
        else
        {
          if ( *v31 )
            (*v31)->list_prev = *(v31 - 1);
          v35 = (int)*(v31 - 1);
          if ( v35 )
            *(_DWORD *)(v35 + 12) = *v31;
          else
            v34->first = (FrameBodBase *)*v31;
          *v31 = (struct BodNode *)v34->free_top;
          v34->free_top = (FrameBodBase *)(v31 - 3);
          v36 = *(v31 - 2);
          BYTE1(v36) &= ~2u;
          *(v31 - 2) = v36;
        }
      }
      else
      {
        report_errorf(aListRemove);
      }
    }
    v31 += 59;
    --v32;
  }
  while ( v32 );
  v37 = &game->ring_effects.slots[0].body.bod.bod.list_next;
  v38 = 2;
  do
  {
    if ( v37[29] )
    {
      v39 = (int)*(v37 - 2);
      v40 = &g_game_base->active_bod_list;
      if ( (v39 & 0x200) != 0 )
      {
        if ( (v39 & 0x40) != 0 )
        {
          report_errorf(aListRemoveNext);
        }
        else
        {
          if ( *v37 )
            (*v37)->list_prev = *(v37 - 1);
          v41 = (int)*(v37 - 1);
          if ( v41 )
            *(_DWORD *)(v41 + 12) = *v37;
          else
            v40->first = (FrameBodBase *)*v37;
          *v37 = (struct BodNode *)v40->free_top;
          v40->free_top = (FrameBodBase *)(v37 - 3);
          v42 = *(v37 - 2);
          BYTE1(v42) &= ~2u;
          *(v37 - 2) = v42;
        }
      }
      else
      {
        report_errorf(aListRemove);
      }
    }
    v37[29] = nullptr;
    v37 += 126;
    --v38;
  }
  while ( v38 );
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
        if ( v45 )
          v45->list_prev = game->player.body.bod.bod.list_prev;
        v46 = game->player.body.bod.bod.list_prev;
        if ( v46 )
          v46->list_next = game->player.body.bod.bod.list_next;
        else
          v44->first = (FrameBodBase *)game->player.body.bod.bod.list_next;
        game->player.body.bod.bod.list_next = (struct BodNode *)v44->free_top;
        v44->free_top = (FrameBodBase *)&game->player;
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
        if ( v50 )
          v50->list_prev = game->player.presentation.body.bod.bod.list_prev;
        v51 = game->player.presentation.body.bod.bod.list_prev;
        if ( v51 )
          v51->list_next = game->player.presentation.body.bod.bod.list_next;
        else
          v48->first = (FrameBodBase *)game->player.presentation.body.bod.bod.list_next;
        game->player.presentation.body.bod.bod.list_next = (struct BodNode *)v48->free_top;
        v48->free_top = (FrameBodBase *)&game->player.presentation;
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
        if ( v55 )
          v55->list_prev = game->player.presentation.jetpack_channel.body.bod.bod.list_prev;
        v56 = game->player.presentation.jetpack_channel.body.bod.bod.list_prev;
        if ( v56 )
          v56->list_next = game->player.presentation.jetpack_channel.body.bod.bod.list_next;
        else
          v54->first = (FrameBodBase *)game->player.presentation.jetpack_channel.body.bod.bod.list_next;
        game->player.presentation.jetpack_channel.body.bod.bod.list_next = (struct BodNode *)v54->free_top;
        v54->free_top = (FrameBodBase *)&game->player.presentation.jetpack_channel;
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
        if ( v60 )
          v60->list_prev = game->player.presentation.weapon_channels[0].body.bod.bod.list_prev;
        v61 = game->player.presentation.weapon_channels[0].body.bod.bod.list_prev;
        if ( v61 )
          v61->list_next = game->player.presentation.weapon_channels[0].body.bod.bod.list_next;
        else
          v59->first = (FrameBodBase *)game->player.presentation.weapon_channels[0].body.bod.bod.list_next;
        game->player.presentation.weapon_channels[0].body.bod.bod.list_next = (struct BodNode *)v59->free_top;
        v59->free_top = (FrameBodBase *)game->player.presentation.weapon_channels;
        v62 = game->player.presentation.weapon_channels[0].body.bod.bod.list_flags;
        BYTE1(v62) &= ~2u;
        game->player.presentation.weapon_channels[0].body.bod.bod.list_flags = v62;
      }
    }
    else
    {
      report_errorf(aListRemove);
    }
    recycle_bod_to_free_list(
      &g_game_base->active_bod_list.unknown_00,
      &game->player.presentation.weapon_channels[1].body.bod.bod.vtable);
    recycle_bod_to_free_list(
      &g_game_base->active_bod_list.unknown_00,
      &game->player.presentation.weapon_channels[2].body.bod.bod.vtable);
    recycle_bod_to_free_list(
      &g_game_base->active_bod_list.unknown_00,
      &game->player.presentation.invincible_shell.body.bod.bod.vtable);
    game->player.movement_mode_selector = 0;
    noop_runtime_ai();
  }
  golb_shots = game->player.golb_shots;
  v64 = 12;
  do
  {
    if ( golb_shots->state == 1 )
      kill_golb(golb_shots);
    ++golb_shots;
    --v64;
  }
  while ( v64 );
  if ( (game->player.click_start.bod.bod.bod.list_flags & 0x200) != 0 )
  {
    recycle_bod_to_free_list(&g_game_base->active_bod_list.unknown_00, &game->player.click_start.bod.bod.bod.vtable);
    game->player.click_start.state = CLICK_START_STATE_INACTIVE;
  }
  kill_game_sprites();
}
