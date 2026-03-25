/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_tooltip @ 0x403c20 */
/* selector: update_tooltip */

void __thiscall sub_403C20(int this)
{
  _DWORD *v2; // ecx
  int v3; // ecx
  double v4; // st7
  int v5; // eax
  int v6; // eax
  _DWORD *v7; // eax
  int v8; // edi
  _DWORD *v9; // eax
  int v10; // edi
  float *v11; // eax
  double v12; // st7
  int v13; // edi
  int v14; // ecx
  float *v15; // ecx
  double v16; // st7
  float v17; // [esp+0h] [ebp-6Ch]
  float v18; // [esp+0h] [ebp-6Ch]
  float v19; // [esp+0h] [ebp-6Ch]
  float v20; // [esp+0h] [ebp-6Ch]
  _DWORD *v21; // [esp+4h] [ebp-68h]
  _DWORD *v22; // [esp+4h] [ebp-68h]
  int v23; // [esp+8h] [ebp-64h]
  float v24; // [esp+Ch] [ebp-60h]
  float v25; // [esp+18h] [ebp-54h]
  _DWORD v26[4]; // [esp+1Ch] [ebp-50h] BYREF
  _DWORD v27[4]; // [esp+2Ch] [ebp-40h] BYREF
  _DWORD v28[4]; // [esp+3Ch] [ebp-30h] BYREF
  _DWORD v29[4]; // [esp+4Ch] [ebp-20h] BYREF
  _DWORD v30[4]; // [esp+5Ch] [ebp-10h] BYREF

  if ( *(_DWORD *)(this + 4) != 1 )
  {
    if ( *(_DWORD *)(this + 4) != 2 )
    {
      if ( *(_DWORD *)(this + 4) == 3 && (*(_DWORD *)(*(_DWORD *)(this + 12) + 416) & 0x20000) == 0 )
      {
        v2 = *(_DWORD **)(this + 24);
        *(_DWORD *)(this + 4) = 1;
        kill_border(v2);
        *(_DWORD *)(this + 24) = 0;
      }
      return;
    }
    v3 = *(_DWORD *)(this + 12);
    if ( (*(_DWORD *)(v3 + 416) & 0x20000) == 0 )
    {
      *(_DWORD *)(this + 4) = 1;
      return;
    }
    v4 = *(float *)(this + 20) + *(float *)(this + 16);
    *(float *)(this + 16) = v4;
    if ( v4 <= 1.0 )
      return;
    if ( *(_DWORD *)(v3 + 604) )
      v25 = *(float *)(v3 + 608);
    else
      v25 = *(float *)(v3 + 584) * 0.5 + *(float *)(v3 + 1780) - 320.0;
    v5 = *(_DWORD *)(this + 24);
    *(_DWORD *)(this + 4) = 3;
    if ( v5 )
      report_errorf(aToolTipOverloa);
    else
      *(_DWORD *)(this + 24) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
    v6 = *(_DWORD *)(this + 8);
    if ( (v6 & 1) != 0 )
    {
      v7 = set_color_rgba(v26, 1065353216, 1065353216, 1065353216, 1065353216);
      v17 = *((float *)MEMORY[0x4DF904] + 168) + 64.0;
      initialize_frontend_widget(
        *(_DWORD *)(this + 24),
        2,
        (char *)this,
        7,
        *((_DWORD *)MEMORY[0x4DF904] + 167),
        v17,
        (int)v7,
        1,
        v25);
LABEL_27:
      v14 = *(_DWORD *)(this + 24);
      if ( *(float *)(v14 + 568) - *(float *)(v14 + 536) - *(float *)(v14 + 620) < 0.0 )
        *(_DWORD *)(v14 + 1780) = *(_DWORD *)(v14 + 620);
      v15 = *(float **)(this + 24);
      v16 = v15[155] + v15[146] + v15[142] + v15[134];
      if ( v16 > 640.0 )
        v15[445] = v15[445] - (v16 - 640.0);
      layout_frontend_widget(*(_DWORD *)(this + 24));
      return;
    }
    if ( (v6 & 4) != 0 )
    {
      v8 = *(_DWORD *)(this + 12);
      v24 = v25;
      v23 = 1;
      v9 = set_color_rgba(v27, 1065353216, 1065353216, 1065353216, 1065353216);
LABEL_22:
      v19 = *(float *)(v8 + 1784) - *(float *)(v8 + 544);
      initialize_frontend_widget(
        *(_DWORD *)(this + 24),
        2,
        (char *)this,
        7,
        *(_DWORD *)(v8 + 1780),
        v19,
        (int)v9,
        v23,
        v24);
      v11 = *(float **)(this + 24);
      v12 = v11[446] - (v11[147] + v11[136]);
LABEL_26:
      v11[446] = v12;
      goto LABEL_27;
    }
    if ( (v6 & 2) != 0 )
    {
      v10 = *(_DWORD *)(this + 12);
      v21 = set_color_rgba(v28, 1065353216, 1065353216, 1065353216, 1065353216);
      v18 = *(float *)(v10 + 1784) + *(float *)(v10 + 588) + *(float *)(v10 + 544);
      initialize_frontend_widget(
        *(_DWORD *)(this + 24),
        2,
        (char *)this,
        7,
        *(_DWORD *)(v10 + 1780),
        v18,
        (int)v21,
        1,
        v25);
    }
    else
    {
      if ( (v6 & 0x10) != 0 )
      {
        v8 = *(_DWORD *)(this + 12);
        v24 = 0.0;
        v23 = 0;
        v9 = set_color_rgba(v29, 1065353216, 1065353216, 1065353216, 1065353216);
        goto LABEL_22;
      }
      if ( (v6 & 8) == 0 )
        goto LABEL_27;
      v13 = *(_DWORD *)(this + 12);
      v22 = set_color_rgba(v30, 1065353216, 1065353216, 1065353216, 1065353216);
      v20 = *(float *)(v13 + 1784) + *(float *)(v13 + 588) + *(float *)(v13 + 544);
      initialize_frontend_widget(
        *(_DWORD *)(this + 24),
        2,
        (char *)this,
        7,
        *(_DWORD *)(v13 + 1780),
        v20,
        (int)v22,
        0,
        0.0);
    }
    v11 = *(float **)(this + 24);
    v12 = v11[136] + v11[446];
    goto LABEL_26;
  }
  if ( (*(_DWORD *)(*(_DWORD *)(this + 12) + 416) & 0x20000) != 0 )
  {
    *(_DWORD *)(this + 16) = 0;
    *(_DWORD *)(this + 4) = 2;
  }
}

