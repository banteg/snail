/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_high_score_screen @ 0x416910 */
/* selector: initialize_high_score_screen */

// Builds the postal or challenge high-score screen, optionally enables inline name entry for a pending rank, and lays out the per-row replay or submit controls. Cross-port Android and iOS symbols match this helper to `cRHighScore::Init(int, int)`.
float *__thiscall sub_416910(int this, int a2, int a3)
{
  int v4; // eax
  int v5; // eax
  _DWORD *v6; // eax
  _DWORD *v7; // eax
  int v8; // ebx
  int v9; // eax
  int *v10; // esi
  int v11; // edi
  int v12; // eax
  _DWORD *v13; // eax
  _DWORD *v14; // eax
  _DWORD *v15; // eax
  int v16; // ecx
  _DWORD *v17; // eax
  _DWORD *v18; // eax
  _DWORD *v19; // eax
  _DWORD *v20; // eax
  _DWORD *v21; // eax
  int v22; // ecx
  _DWORD *v23; // eax
  _DWORD *v24; // eax
  _DWORD *v25; // eax
  _DWORD *v26; // ecx
  _DWORD *v27; // eax
  _DWORD *v28; // ecx
  bool v29; // cc
  _DWORD *v30; // eax
  _DWORD *v31; // eax
  float *result; // eax
  _DWORD *v33; // eax
  int v34; // eax
  _DWORD *v35; // [esp-Ch] [ebp-E4h]
  _DWORD *v36; // [esp-Ch] [ebp-E4h]
  float v37; // [esp+8h] [ebp-D0h]
  float v38; // [esp+8h] [ebp-D0h]
  float v39; // [esp+8h] [ebp-D0h]
  int v40; // [esp+Ch] [ebp-CCh]
  int v41; // [esp+10h] [ebp-C8h]
  float v42; // [esp+14h] [ebp-C4h]
  _DWORD v43[4]; // [esp+18h] [ebp-C0h] BYREF
  _DWORD v44[4]; // [esp+28h] [ebp-B0h] BYREF
  _DWORD v45[4]; // [esp+38h] [ebp-A0h] BYREF
  _DWORD v46[4]; // [esp+48h] [ebp-90h] BYREF
  _DWORD v47[4]; // [esp+58h] [ebp-80h] BYREF
  _DWORD v48[4]; // [esp+68h] [ebp-70h] BYREF
  _DWORD v49[4]; // [esp+78h] [ebp-60h] BYREF
  _DWORD v50[4]; // [esp+88h] [ebp-50h] BYREF
  _DWORD v51[4]; // [esp+98h] [ebp-40h] BYREF
  _DWORD v52[4]; // [esp+A8h] [ebp-30h] BYREF
  _DWORD v53[4]; // [esp+B8h] [ebp-20h] BYREF
  _DWORD v54[4]; // [esp+C8h] [ebp-10h] BYREF

  *(_DWORD *)(this + 8) = a2;
  *(_DWORD *)(this + 20) = a3;
  *(_BYTE *)(this + 16) = a3 != -1;
  hide_star_field((int *)MEMORY[0x4DF904] + 81103);
  hide_gameplay_scores((_DWORD *)MEMORY[0x4DF904] + 119174);
  cache_music_file(aMusicMainmenuO);
  v4 = load_landscape_script_by_name((char *)MEMORY[0x4DF904] + 17220120, aMenubgTxt);
  change_backdrop((int)MEMORY[0x4DF904] + 322576, (int)MEMORY[0x4DF904] + 292 * v4 + 17221564, 0);
  set_border_justify_centre((_DWORD *)MEMORY[0x4DF904] + 723, 1103626240);
  capture_mouse_cursor((float *)MEMORY[0x4DF904] + 164);
  *(_DWORD *)(this + 24) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v5 = *(_DWORD *)(this + 8);
  if ( !v5 )
  {
    v7 = set_color_rgba(v44, 1065353216, 1065353216, 1065353216, 1065353216);
    initialize_frontend_widget(*(_DWORD *)(this + 24), 0, aPostalHighScor, 23, 0, 64.0, (int)v7, 2, 0.0);
    *(int *)((char *)&byte_6FFAE0 + (_DWORD)MEMORY[0x4DF904]) = (int)&unk_6FFAE8 + (_DWORD)MEMORY[0x4DF904];
    *(int *)((char *)&unk_6FFAE4 + (_DWORD)MEMORY[0x4DF904]) = 10;
    goto LABEL_8;
  }
  if ( v5 == 1 )
  {
    v6 = set_color_rgba(v45, 1065353216, 1065353216, 1065353216, 1065353216);
    initialize_frontend_widget(*(_DWORD *)(this + 24), 0, aChallengeHighS, 23, 0, 64.0, (int)v6, 2, 0.0);
    *(int *)((char *)&byte_6FFAE0 + (_DWORD)MEMORY[0x4DF904]) = (int)MEMORY[0x4DF904] + 8765736;
    *(int *)((char *)&unk_6FFAE4 + (_DWORD)MEMORY[0x4DF904]) = 10;
LABEL_8:
    v42 = 27.0;
  }
  if ( *(_BYTE *)(this + 16) )
  {
    rstrcpy_checked_ascii((char *)(*(_DWORD *)(this + 24) + 716), aEnterYourNameH);
    layout_frontend_widget(*(_DWORD *)(this + 24));
  }
  v8 = 0;
  v9 = 0;
  v40 = 0;
  v41 = 0;
  v10 = (int *)(this + 124);
  do
  {
    v10[20] = 0;
    v11 = v8 != *(_DWORD *)(this + 20) ? 0 : 2;
    if ( *(_DWORD *)(*(int *)((char *)&byte_6FFAE0 + (_DWORD)MEMORY[0x4DF904]) + v9) != 1 )
      goto LABEL_25;
    v12 = *(_DWORD *)(this + 8);
    if ( v12 )
    {
      if ( v12 != 1 )
        goto LABEL_23;
      v37 = (double)v40 * v42 + 111.0;
      *(v10 - 20) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v13 = set_color_rgba(v44, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(*(v10 - 20), v11 | 0x20000000, asc_4A3830, 22, 0, v37, (int)v13, 1, -228.0);
      *(v10 - 10) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v14 = set_color_rgba(v45, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(*(v10 - 10), v11 | 0x20400000, MEMORY[0x4DFB08], 22, 0, v37, (int)v14, 1, -222.0);
      border_add_text_number((_BYTE *)*(v10 - 10), v40 + 1);
      layout_frontend_widget(*(v10 - 10));
      *v10 = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v15 = set_color_rgba(v52, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(
        *v10,
        v11 | 0x20400000,
        (char *)(*(int *)((char *)&byte_6FFAE0 + (_DWORD)MEMORY[0x4DF904]) + v41 + 84),
        22,
        0,
        v37,
        (int)v15,
        1,
        -180.0);
      if ( v40 == *(_DWORD *)(this + 20) )
      {
        border_input_text_init(*v10, 16, &byte_4DF978, 16);
        v16 = *(_DWORD *)(*v10 + 416);
        BYTE1(v16) |= 0x20u;
        *(_DWORD *)(*v10 + 416) = v16;
      }
      layout_frontend_widget(*v10);
      v10[10] = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v17 = set_color_rgba(v47, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(v10[10], v11 | 0x20400000, MEMORY[0x4DFB08], 22, 0, v37, (int)v17, 3, 125.0);
      border_add_text_number(
        (_BYTE *)v10[10],
        *(_DWORD *)(*(int *)((char *)&byte_6FFAE0 + (_DWORD)MEMORY[0x4DF904]) + v41 + 4));
      layout_frontend_widget(v10[10]);
      v10[20] = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v18 = set_color_rgba(v54, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(v10[20], v11 | 0x20000014, aReplay, 22, 0, v37, (int)v18, 2, 170.0);
      if ( !*(_BYTE *)(this + 16) )
        goto LABEL_23;
    }
    else
    {
      v38 = (double)v40 * v42 + 111.0;
      *(v10 - 20) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v19 = set_color_rgba(v49, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(*(v10 - 20), v11 | 0x20000000, asc_4A37F8, 22, 0, v38, (int)v19, 1, -228.0);
      *(v10 - 10) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v20 = set_color_rgba(v53, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(*(v10 - 10), v11 | 0x20400000, MEMORY[0x4DFB08], 22, 0, v38, (int)v20, 1, -222.0);
      border_add_text_number((_BYTE *)*(v10 - 10), v40 + 1);
      layout_frontend_widget(*(v10 - 10));
      *v10 = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v21 = set_color_rgba(v51, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(
        *v10,
        v11 | 0x20400000,
        (char *)(*(int *)((char *)&byte_6FFAE0 + (_DWORD)MEMORY[0x4DF904]) + v41 + 84),
        22,
        0,
        v38,
        (int)v21,
        1,
        -180.0);
      if ( v40 == *(_DWORD *)(this + 20) )
      {
        border_input_text_init(*v10, 16, &byte_4DF978, 16);
        v22 = *(_DWORD *)(*v10 + 416);
        BYTE1(v22) |= 0x20u;
        *(_DWORD *)(*v10 + 416) = v22;
      }
      layout_frontend_widget(*v10);
      v10[10] = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v23 = set_color_rgba(v48, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(v10[10], v11 | 0x20400000, MEMORY[0x4DFB08], 22, 0, v38, (int)v23, 3, 160.0);
      border_add_text_number(
        (_BYTE *)v10[10],
        *(_DWORD *)(*(int *)((char *)&byte_6FFAE0 + (_DWORD)MEMORY[0x4DF904]) + v41 + 4));
      layout_frontend_widget(v10[10]);
      v10[20] = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v24 = set_color_rgba(v50, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(v10[20], v11 | 0x20000014, aReplay, 22, 0, v38, (int)v24, 2, 125.0);
    }
    hide_border_init((_DWORD *)v10[20]);
LABEL_23:
    v8 = v40;
    if ( (v40 & 1) != 0 )
    {
      v25 = set_color_rgba(v46, 1051240617, 1044167869, 1054267095, 1060320051);
      v26 = (_DWORD *)(*(v10 - 20) + 444);
      *v26 = *v25;
      v26[1] = v25[1];
      v26[2] = v25[2];
      v26[3] = v25[3];
      v27 = set_color_rgba(v43, 1051240617, 1044167869, 1054267095, 1060320051);
      v28 = (_DWORD *)(v10[20] + 444);
      *v28 = *v27;
      v28[1] = v27[1];
      v28[2] = v27[2];
      v28[3] = v27[3];
    }
LABEL_25:
    ++v8;
    v9 = v41 + 129728;
    ++v10;
    v29 = v41 + 129728 < 1297280;
    v40 = v8;
    v41 += 129728;
  }
  while ( v29 );
  v39 = v42 * 10.0 + 111.0;
  if ( *(_BYTE *)(this + 16) )
  {
    *(_DWORD *)(this + 36) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
    v30 = set_color_rgba(v43, 1065353216, 1065353216, 1065353216, 1065353216);
    initialize_frontend_widget(*(_DWORD *)(this + 36), 536870932, aCancel, 23, 0, v39, (int)v30, 2, -110.0);
    set_frontend_widget_shortcut_key(*(_DWORD **)(this + 36), 11);
    *(_DWORD *)(this + 40) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
    v31 = set_color_rgba(v43, 1065353216, 1065353216, 1065353216, 1065353216);
    initialize_frontend_widget(*(_DWORD *)(this + 40), 536870932, aSubmit, 23, 0, v39, (int)v31, 2, 55.0);
    return (float *)set_frontend_widget_shortcut_key(*(_DWORD **)(this + 40), 5);
  }
  else
  {
    *(_DWORD *)(this + 28) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
    v33 = set_color_rgba(v43, 1065353216, 1065353216, 1065353216, 1065353216);
    initialize_frontend_widget(*(_DWORD *)(this + 28), 536870932, aBack, 23, 0, v39, (int)v33, 2, -132.0);
    *(_DWORD *)(this + 32) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
    v34 = *(_DWORD *)(this + 8);
    if ( v34 )
    {
      result = (float *)(v34 - 1);
      if ( !result )
      {
        v35 = set_color_rgba(v43, 1065353216, 1065353216, 1065353216, 1065353216);
        return initialize_frontend_widget(
                 *(_DWORD *)(this + 32),
                 536870932,
                 aPostalScores,
                 23,
                 0,
                 v39,
                 (int)v35,
                 2,
                 33.0);
      }
    }
    else
    {
      v36 = set_color_rgba(v46, 1065353216, 1065353216, 1065353216, 1065353216);
      return initialize_frontend_widget(
               *(_DWORD *)(this + 32),
               536870932,
               aChallengeScore,
               23,
               0,
               v39,
               (int)v36,
               2,
               33.0);
    }
  }
  return result;
}

