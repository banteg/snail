/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: remove_subgame_bods @ 0x440910 */
/* selector: remove_subgame_bods */

void __thiscall sub_440910(int this)
{
  int v1; // edi
  char *v2; // esi
  int v3; // ebp
  char *v4; // ecx
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // ebx
  _DWORD *v9; // esi
  int v10; // edi
  int v11; // eax
  char *v12; // ecx
  int v13; // eax
  int v14; // eax
  char *v15; // edx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  char *v21; // edx
  int v22; // ecx
  int v23; // ecx
  int v24; // ecx
  _DWORD *v25; // esi
  int v26; // edi
  int v27; // eax
  char *v28; // ecx
  int v29; // eax
  int v30; // eax
  _DWORD *v31; // esi
  int v32; // edi
  int v33; // eax
  char *v34; // ecx
  int v35; // eax
  int v36; // eax
  _DWORD *v37; // esi
  int v38; // edi
  int v39; // eax
  char *v40; // ecx
  int v41; // eax
  int v42; // eax
  int v43; // eax
  char *v44; // ecx
  int v45; // eax
  int v46; // eax
  int v47; // eax
  char *v48; // edx
  int v49; // ecx
  int v50; // ecx
  int v51; // ecx
  int v52; // ecx
  int v53; // ecx
  char *v54; // edx
  int v55; // ecx
  int v56; // ecx
  int v57; // ecx
  int v58; // ecx
  char *v59; // edx
  int v60; // ecx
  int v61; // ecx
  int v62; // ecx
  int *v63; // esi
  int v64; // edi

  v1 = this + 3930824;
  v2 = (char *)&unk_5CCAD8 + this;
  v3 = 3200;
  do
  {
    if ( (*((_DWORD *)v2 - 2) & 0x200) != 0 )
    {
      v4 = (char *)MEMORY[0x4DF904] + 1448;
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
            *((_DWORD *)v4 + 1) = *(_DWORD *)v2;
          *(_DWORD *)v2 = *((_DWORD *)v4 + 2);
          *((_DWORD *)v4 + 2) = v2 - 12;
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
      remove_sub_loc(v1);
      v1 += 84;
      --v8;
    }
    while ( v8 );
    v2 += 244;
    --v3;
  }
  while ( v3 );
  remove_track_render_cache_bods((char *)(this + 92));
  v9 = (_DWORD *)(this + 3497996);
  v10 = 8;
  do
  {
    v11 = *(v9 - 2);
    if ( (v11 & 0x200) != 0 )
    {
      v12 = (char *)MEMORY[0x4DF904] + 1448;
      if ( (v11 & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
      }
      else
      {
        if ( *v9 )
          *(_DWORD *)(*v9 + 8) = *(v9 - 1);
        v13 = *(v9 - 1);
        if ( v13 )
          *(_DWORD *)(v13 + 12) = *v9;
        else
          *((_DWORD *)v12 + 1) = *v9;
        *v9 = *((_DWORD *)v12 + 2);
        *((_DWORD *)v12 + 2) = v9 - 3;
        v14 = *(v9 - 2);
        BYTE1(v14) &= ~2u;
        *(v9 - 2) = v14;
      }
      v9[11] = 0;
    }
    v9 += 29;
    --v10;
  }
  while ( v10 );
  if ( (*(_DWORD *)(this + 3497396) & 0x200) != 0 )
  {
    v15 = (char *)MEMORY[0x4DF904] + 1448;
    v16 = *(_DWORD *)(this + 3497396);
    if ( (v16 & 0x200) != 0 )
    {
      if ( (v16 & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
      }
      else
      {
        v17 = *(_DWORD *)(this + 3497404);
        if ( v17 )
          *(_DWORD *)(v17 + 8) = *(_DWORD *)(this + 3497400);
        v18 = *(_DWORD *)(this + 3497400);
        if ( v18 )
          *(_DWORD *)(v18 + 12) = *(_DWORD *)(this + 3497404);
        else
          *((_DWORD *)v15 + 1) = *(_DWORD *)(this + 3497404);
        *(_DWORD *)(this + 3497404) = *((_DWORD *)v15 + 2);
        *((_DWORD *)v15 + 2) = this + 3497392;
        v19 = *(_DWORD *)(this + 3497396);
        BYTE1(v19) &= ~2u;
        *(_DWORD *)(this + 3497396) = v19;
      }
    }
    else
    {
      report_errorf(aListRemove);
    }
    *(_DWORD *)(this + 3497520) = 0;
  }
  if ( (*(_DWORD *)(this + 3497576) & 0x200) != 0 )
  {
    v20 = *(_DWORD *)(this + 3497576);
    v21 = (char *)MEMORY[0x4DF904] + 1448;
    if ( (v20 & 0x200) != 0 )
    {
      if ( (v20 & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
      }
      else
      {
        v22 = *(_DWORD *)(this + 3497584);
        if ( v22 )
          *(_DWORD *)(v22 + 8) = *(_DWORD *)(this + 3497580);
        v23 = *(_DWORD *)(this + 3497580);
        if ( v23 )
          *(_DWORD *)(v23 + 12) = *(_DWORD *)(this + 3497584);
        else
          *((_DWORD *)v21 + 1) = *(_DWORD *)(this + 3497584);
        *(_DWORD *)(this + 3497584) = *((_DWORD *)v21 + 2);
        *((_DWORD *)v21 + 2) = this + 3497572;
        v24 = *(_DWORD *)(this + 3497576);
        BYTE1(v24) &= ~2u;
        *(_DWORD *)(this + 3497576) = v24;
      }
    }
    else
    {
      report_errorf(aListRemove);
    }
    *(_DWORD *)(this + 3497628) = 0;
  }
  v25 = (_DWORD *)(this + 3510608);
  v26 = 50;
  do
  {
    if ( (*(v25 - 2) & 0x200) != 0 )
    {
      v25[30] = 0;
      v27 = *(v25 - 2);
      v28 = (char *)MEMORY[0x4DF904] + 1448;
      if ( (v27 & 0x200) != 0 )
      {
        if ( (v27 & 0x40) != 0 )
        {
          report_errorf(aListRemoveNext);
        }
        else
        {
          if ( *v25 )
            *(_DWORD *)(*v25 + 8) = *(v25 - 1);
          v29 = *(v25 - 1);
          if ( v29 )
            *(_DWORD *)(v29 + 12) = *v25;
          else
            *((_DWORD *)v28 + 1) = *v25;
          *v25 = *((_DWORD *)v28 + 2);
          *((_DWORD *)v28 + 2) = v25 - 3;
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
  v31 = (_DWORD *)(this + 3498924);
  v32 = 8;
  do
  {
    if ( (*(v31 - 2) & 0x200) != 0 )
    {
      v31[29] = 0;
      v33 = *(v31 - 2);
      v34 = (char *)MEMORY[0x4DF904] + 1448;
      if ( (v33 & 0x200) != 0 )
      {
        if ( (v33 & 0x40) != 0 )
        {
          report_errorf(aListRemoveNext);
        }
        else
        {
          if ( *v31 )
            *(_DWORD *)(*v31 + 8) = *(v31 - 1);
          v35 = *(v31 - 1);
          if ( v35 )
            *(_DWORD *)(v35 + 12) = *v31;
          else
            *((_DWORD *)v34 + 1) = *v31;
          *v31 = *((_DWORD *)v34 + 2);
          *((_DWORD *)v34 + 2) = v31 - 3;
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
  v37 = (_DWORD *)(this + 3520408);
  v38 = 2;
  do
  {
    if ( v37[29] )
    {
      v39 = *(v37 - 2);
      v40 = (char *)MEMORY[0x4DF904] + 1448;
      if ( (v39 & 0x200) != 0 )
      {
        if ( (v39 & 0x40) != 0 )
        {
          report_errorf(aListRemoveNext);
        }
        else
        {
          if ( *v37 )
            *(_DWORD *)(*v37 + 8) = *(v37 - 1);
          v41 = *(v37 - 1);
          if ( v41 )
            *(_DWORD *)(v41 + 12) = *v37;
          else
            *((_DWORD *)v40 + 1) = *v37;
          *v37 = *((_DWORD *)v40 + 2);
          *((_DWORD *)v40 + 2) = v37 - 3;
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
    v37[29] = 0;
    v37 += 126;
    --v38;
  }
  while ( v38 );
  if ( (*(_DWORD *)(this + 3913576) & 0x200) != 0 )
  {
    v43 = *(_DWORD *)(this + 3913576);
    v44 = (char *)MEMORY[0x4DF904] + 1448;
    if ( (v43 & 0x200) != 0 )
    {
      if ( (v43 & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
      }
      else
      {
        v45 = *(_DWORD *)(this + 3913584);
        if ( v45 )
          *(_DWORD *)(v45 + 8) = *(_DWORD *)(this + 3913580);
        v46 = *(_DWORD *)(this + 3913580);
        if ( v46 )
          *(_DWORD *)(v46 + 12) = *(_DWORD *)(this + 3913584);
        else
          *((_DWORD *)v44 + 1) = *(_DWORD *)(this + 3913584);
        *(_DWORD *)(this + 3913584) = *((_DWORD *)v44 + 2);
        *((_DWORD *)v44 + 2) = this + 3913572;
        v47 = *(_DWORD *)(this + 3913576);
        BYTE1(v47) &= ~2u;
        *(_DWORD *)(this + 3913576) = v47;
      }
    }
    else
    {
      report_errorf(aListRemove);
    }
    v48 = (char *)MEMORY[0x4DF904] + 1448;
    v49 = *(_DWORD *)(this + 3924204);
    if ( (v49 & 0x200) != 0 )
    {
      if ( (v49 & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
      }
      else
      {
        v50 = *(_DWORD *)(this + 3924212);
        if ( v50 )
          *(_DWORD *)(v50 + 8) = *(_DWORD *)(this + 3924208);
        v51 = *(_DWORD *)(this + 3924208);
        if ( v51 )
          *(_DWORD *)(v51 + 12) = *(_DWORD *)(this + 3924212);
        else
          *((_DWORD *)v48 + 1) = *(_DWORD *)(this + 3924212);
        *(_DWORD *)(this + 3924212) = *((_DWORD *)v48 + 2);
        *((_DWORD *)v48 + 2) = this + 3924200;
        v52 = *(_DWORD *)(this + 3924204);
        BYTE1(v52) &= ~2u;
        *(_DWORD *)(this + 3924204) = v52;
      }
    }
    else
    {
      report_errorf(aListRemove);
    }
    v53 = *(_DWORD *)(this + 3928780);
    v54 = (char *)MEMORY[0x4DF904] + 1448;
    if ( (v53 & 0x200) != 0 )
    {
      if ( (v53 & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
      }
      else
      {
        v55 = *(_DWORD *)(this + 3928788);
        if ( v55 )
          *(_DWORD *)(v55 + 8) = *(_DWORD *)(this + 3928784);
        v56 = *(_DWORD *)(this + 3928784);
        if ( v56 )
          *(_DWORD *)(v56 + 12) = *(_DWORD *)(this + 3928788);
        else
          *((_DWORD *)v54 + 1) = *(_DWORD *)(this + 3928788);
        *(_DWORD *)(this + 3928788) = *((_DWORD *)v54 + 2);
        *((_DWORD *)v54 + 2) = this + 3928776;
        v57 = *(_DWORD *)(this + 3928780);
        BYTE1(v57) &= ~2u;
        *(_DWORD *)(this + 3928780) = v57;
      }
    }
    else
    {
      report_errorf(aListRemove);
    }
    v58 = *(_DWORD *)(this + 3925816);
    v59 = (char *)MEMORY[0x4DF904] + 1448;
    if ( (v58 & 0x200) != 0 )
    {
      if ( (v58 & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
      }
      else
      {
        v60 = *(_DWORD *)(this + 3925824);
        if ( v60 )
          *(_DWORD *)(v60 + 8) = *(_DWORD *)(this + 3925820);
        v61 = *(_DWORD *)(this + 3925820);
        if ( v61 )
          *(_DWORD *)(v61 + 12) = *(_DWORD *)(this + 3925824);
        else
          *((_DWORD *)v59 + 1) = *(_DWORD *)(this + 3925824);
        *(_DWORD *)(this + 3925824) = *((_DWORD *)v59 + 2);
        *((_DWORD *)v59 + 2) = this + 3925812;
        v62 = *(_DWORD *)(this + 3925816);
        BYTE1(v62) &= ~2u;
        *(_DWORD *)(this + 3925816) = v62;
      }
    }
    else
    {
      report_errorf(aListRemove);
    }
    recycle_bod_to_free_list((_DWORD *)MEMORY[0x4DF904] + 362, (_DWORD *)(this + 3926800));
    recycle_bod_to_free_list((_DWORD *)MEMORY[0x4DF904] + 362, (_DWORD *)(this + 3927788));
    recycle_bod_to_free_list((_DWORD *)MEMORY[0x4DF904] + 362, (_DWORD *)(this + 3930492));
    *(_DWORD *)(this + 3914608) = 0;
    noop_runtime_ai(this + 3913572);
  }
  v63 = (int *)(this + 3914676);
  v64 = 12;
  do
  {
    if ( v63[145] == 1 )
      kill_golb(v63);
    v63 += 186;
    --v64;
  }
  while ( v64 );
  if ( (*(_DWORD *)(this + 3913736) & 0x200) != 0 )
  {
    recycle_bod_to_free_list((_DWORD *)MEMORY[0x4DF904] + 362, (_DWORD *)(this + 3913732));
    *(_DWORD *)(this + 3913860) = 0;
  }
  kill_game_sprites();
}
