/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_subgame @ 0x438850 */
/* selector: destroy_subgame */

// Tears down the active gameplay subgame state, including runtime lists, HUD widgets, and the current mode handoff state before control returns to the front-end. Cross-port Android and iOS symbols match this helper to `cRSubGame::UnInit()`.
void __thiscall sub_438850(int this)
{
  int v2; // esi
  int v3; // ebx
  int v4; // eax
  char *v5; // ecx
  int v6; // eax
  int v7; // eax
  int v8; // esi
  int v9; // ebx
  int v10; // eax
  char *v11; // ecx
  int v12; // eax
  int v13; // eax
  int v14; // esi
  int v15; // ebx
  int v16; // eax
  char *v17; // ecx
  int v18; // eax
  int v19; // eax
  char *v20; // edx
  int v21; // ecx
  int v22; // ecx
  int v23; // ecx
  int v24; // ecx
  _DWORD **v25; // esi
  int v26; // edi

  sub_449C00();
  *((_DWORD *)MEMORY[0x4DF904] + 81051) = 1;
  if ( *(_DWORD *)(this + 64) == 7 )
    uninit_tutorial();
  uninit_warning((_DWORD **)(this + 3914584));
  clear_active_landscape_entries((_DWORD *)(this + 16743424));
  uninit_times_up((_DWORD **)(this + 19343400));
  remove_subgame_bods(this);
  if ( *(_DWORD *)(this + 60) != 1 )
  {
    if ( *(_DWORD *)(this + 64) <= 1u )
      flush_row_event_display((_DWORD *)(this + 19343320));
    v2 = this + 3500812;
    v3 = 20;
    do
    {
      v4 = *(_DWORD *)(v2 - 8);
      if ( (v4 & 0x200) != 0 )
      {
        v5 = (char *)MEMORY[0x4DF904] + 1448;
        if ( (v4 & 0x40) != 0 )
        {
          report_errorf(aListRemoveNext);
        }
        else
        {
          if ( *(_DWORD *)v2 )
            *(_DWORD *)(*(_DWORD *)v2 + 8) = *(_DWORD *)(v2 - 4);
          v6 = *(_DWORD *)(v2 - 4);
          if ( v6 )
            *(_DWORD *)(v6 + 12) = *(_DWORD *)v2;
          else
            *((_DWORD *)v5 + 1) = *(_DWORD *)v2;
          *(_DWORD *)v2 = *((_DWORD *)v5 + 2);
          *((_DWORD *)v5 + 2) = v2 - 12;
          v7 = *(_DWORD *)(v2 - 8);
          BYTE1(v7) &= ~2u;
          *(_DWORD *)(v2 - 8) = v7;
        }
      }
      v2 += 176;
      --v3;
    }
    while ( v3 );
    v8 = this + 3504332;
    v9 = 40;
    do
    {
      v10 = *(_DWORD *)(v8 - 8);
      if ( (v10 & 0x200) != 0 )
      {
        v11 = (char *)MEMORY[0x4DF904] + 1448;
        if ( (v10 & 0x40) != 0 )
        {
          report_errorf(aListRemoveNext);
        }
        else
        {
          if ( *(_DWORD *)v8 )
            *(_DWORD *)(*(_DWORD *)v8 + 8) = *(_DWORD *)(v8 - 4);
          v12 = *(_DWORD *)(v8 - 4);
          if ( v12 )
            *(_DWORD *)(v12 + 12) = *(_DWORD *)v8;
          else
            *((_DWORD *)v11 + 1) = *(_DWORD *)v8;
          *(_DWORD *)v8 = *((_DWORD *)v11 + 2);
          *((_DWORD *)v11 + 2) = v8 - 12;
          v13 = *(_DWORD *)(v8 - 8);
          BYTE1(v13) &= ~2u;
          *(_DWORD *)(v8 - 8) = v13;
        }
      }
      v8 += 152;
      --v9;
    }
    while ( v9 );
    v14 = this + 3510412;
    v15 = 2;
    do
    {
      v16 = *(_DWORD *)(v14 - 8);
      if ( (v16 & 0x200) != 0 )
      {
        v17 = (char *)MEMORY[0x4DF904] + 1448;
        if ( (v16 & 0x40) != 0 )
        {
          report_errorf(aListRemoveNext);
        }
        else
        {
          if ( *(_DWORD *)v14 )
            *(_DWORD *)(*(_DWORD *)v14 + 8) = *(_DWORD *)(v14 - 4);
          v18 = *(_DWORD *)(v14 - 4);
          if ( v18 )
            *(_DWORD *)(v18 + 12) = *(_DWORD *)v14;
          else
            *((_DWORD *)v17 + 1) = *(_DWORD *)v14;
          *(_DWORD *)v14 = *((_DWORD *)v17 + 2);
          *((_DWORD *)v17 + 2) = v14 - 12;
          v19 = *(_DWORD *)(v14 - 8);
          BYTE1(v19) &= ~2u;
          *(_DWORD *)(v14 - 8) = v19;
        }
      }
      v14 += 96;
      --v15;
    }
    while ( v15 );
  }
  if ( (*(_DWORD *)(this + 16743368) & 0x200) != 0 )
  {
    v20 = (char *)MEMORY[0x4DF904] + 1448;
    v21 = *(_DWORD *)(this + 16743368);
    if ( (v21 & 0x200) != 0 )
    {
      if ( (v21 & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
      }
      else
      {
        v22 = *(_DWORD *)(this + 16743376);
        if ( v22 )
          *(_DWORD *)(v22 + 8) = *(_DWORD *)(this + 16743372);
        v23 = *(_DWORD *)(this + 16743372);
        if ( v23 )
          *(_DWORD *)(v23 + 12) = *(_DWORD *)(this + 16743376);
        else
          *((_DWORD *)v20 + 1) = *(_DWORD *)(this + 16743376);
        *(_DWORD *)(this + 16743376) = *((_DWORD *)v20 + 2);
        *((_DWORD *)v20 + 2) = this + 16743364;
        v24 = *(_DWORD *)(this + 16743368);
        BYTE1(v24) &= ~2u;
        *(_DWORD *)(this + 16743368) = v24;
      }
    }
    else
    {
      report_errorf(aListRemove);
    }
  }
  kill_border(*(_DWORD **)(this + 3521416));
  kill_border(*(_DWORD **)(this + 3521420));
  if ( *(_BYTE *)(this + 16721361) )
  {
    *((_DWORD *)MEMORY[0x4DF904] + 111) = 18;
    *(_BYTE *)(this + 16721361) = 0;
  }
  if ( *(_DWORD *)(this + 64) == 3 )
    *((_DWORD *)MEMORY[0x4DF904] + 119190) = 2;
  if ( !*(_DWORD *)(this + 64) )
  {
    kill_border(*(_DWORD **)(this + 3521424));
    kill_border(*(_DWORD **)(this + 3521428));
    v25 = (_DWORD **)(this + 3521432);
    v26 = 9;
    do
    {
      kill_border(*v25++);
      --v26;
    }
    while ( v26 );
  }
}

