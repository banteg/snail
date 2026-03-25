/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_galaxy @ 0x4092f0 */
/* selector: update_galaxy */

// Runs the Star Map galaxy-screen state machine, including route selection, replay launch, and Deliver/Play actions through the shared level-path handoff. Cross-port Android and iOS symbols match this helper to `cRGalaxy::AI()`.
int __thiscall sub_4092F0(int this)
{
  int v2; // edi
  float *v3; // ebx
  int v4; // edx
  int v5; // ecx
  double v6; // st7
  int i; // ebp
  int v8; // edi
  double v9; // st7
  int v10; // ebp
  float *v11; // edi
  int v12; // edi
  float *v13; // ebp
  int v14; // ebp
  float v15; // ebx
  int v16; // eax
  float v17; // ecx
  float v18; // edx
  int v19; // eax
  float *v20; // ecx
  int v21; // eax
  _DWORD *v22; // ecx
  int v23; // ecx
  int v24; // edx
  double v25; // st7
  float *v26; // edi
  double v27; // st7
  double v28; // st7
  int v29; // ecx
  int v30; // eax
  int v32; // edx
  int v33; // ecx
  int v34; // eax
  int v35; // esi
  int v36; // ecx
  int v37; // eax
  int v38; // eax
  int v39; // [esp+0h] [ebp-7Ch]
  int v40; // [esp+0h] [ebp-7Ch]
  int v41; // [esp+0h] [ebp-7Ch]
  int v42; // [esp+4h] [ebp-78h]
  int v43; // [esp+4h] [ebp-78h]
  int v44; // [esp+4h] [ebp-78h]
  int *v45; // [esp+14h] [ebp-68h]
  float v46; // [esp+18h] [ebp-64h]
  float v47; // [esp+20h] [ebp-5Ch]
  float v48; // [esp+44h] [ebp-38h]
  float v49; // [esp+48h] [ebp-34h]
  float v50; // [esp+50h] [ebp-2Ch] BYREF
  float v51; // [esp+54h] [ebp-28h]
  int v52; // [esp+58h] [ebp-24h]
  float v53; // [esp+5Ch] [ebp-20h] BYREF
  float v54; // [esp+60h] [ebp-1Ch]
  int v55; // [esp+64h] [ebp-18h]
  int v56[3]; // [esp+6Ch] [ebp-10h] BYREF
  int v57; // [esp+78h] [ebp-4h]

  Iostream_init::Iostream_init((#93 *)v56);
  hide_gameplay_scores(*(_DWORD **)(this + 69488));
  v2 = 0;
  if ( dword_4DF9B8 >= 0 )
  {
    v3 = (float *)(this + 16);
    do
    {
      sub_409BD0(v3);
      ++v2;
      v3 += 168;
    }
    while ( v2 <= dword_4DF9B8 );
  }
  if ( *(_DWORD *)(this + 8) == 1 && (*(_DWORD *)(*(_DWORD *)(this + 69516) + 416) & 0x1000) == 0 )
  {
    store_color4f(v56, 1065353216, 1065353216, 1065353216, 1065336439);
    v4 = *(_DWORD *)(this + 69516);
    v5 = this + 672 * *(_DWORD *)(this + 69504);
    if ( *(float *)(v4 + 76) <= (double)*(float *)(v5 + 28) )
    {
      v47 = *(float *)(v4 + 84) + *(float *)(v4 + 76) + 6.0;
      v6 = *(float *)(v5 + 28) - 16.0;
    }
    else
    {
      v47 = *(float *)(v4 + 76) - 6.0;
      v6 = *(float *)(v5 + 28) + 16.0;
    }
    v46 = v6;
    draw_galaxy_line(153, v46, *(float *)(v5 + 32), v47, *(float *)(v5 + 32), 4.0, v56);
  }
  for ( i = 1; i <= dword_4DF9B8; ++i )
  {
    v8 = 672 * i + this;
    v56[0] = 1065353216;
    v56[1] = 1065353216;
    v56[2] = 1065353216;
    v57 = 1065185444;
    if ( i )
    {
      if ( *(_DWORD *)(this + 4) == 1 && i > *(_DWORD *)(this + 69504) )
        goto LABEL_17;
      v45 = v56;
      *(float *)&v42 = *(float *)(v8 + 32) - 16.0;
      v9 = *(float *)(v8 + 28);
    }
    else
    {
      v45 = set_color_rgba(&v53, 1065353216, 0, 0, 1065185444);
      *(float *)&v42 = *(float *)(this + 32) - 16.0;
      v9 = *(float *)(this + 28);
    }
    *(float *)&v39 = v9 - 16.0;
    queue_axis_aligned_textured_quad_uv(
      151,
      v39,
      v42,
      1107296256,
      1107296256,
      0x1000000,
      v45,
      0,
      0,
      1065353216,
      1065353216,
      15,
      0);
LABEL_17:
    if ( *(float *)(v8 + 40) > 0.0 )
    {
      v57 = *(_DWORD *)(v8 + 40);
      *(float *)&v43 = *(float *)(v8 + 32) - 32.0;
      *(float *)&v40 = *(float *)(v8 + 28) - 32.0;
      queue_axis_aligned_textured_quad_uv(
        150,
        v40,
        v43,
        1115684864,
        1115684864,
        0x1000000,
        v56,
        0,
        0,
        1065353216,
        1065353216,
        15,
        0);
    }
  }
  set_color_white(v56);
  v57 = 1045220557;
  v10 = 1;
  if ( dword_4DF9B8 > 1 )
  {
    v11 = (float *)(this + 1372);
    do
    {
      if ( v10 >= *(_DWORD *)(this + 69504) )
      {
        if ( *(_DWORD *)(this + 4) != 1 )
        {
          v57 = 1045220557;
          draw_galaxy_line(154, *(v11 - 168), *(v11 - 167), *v11, v11[1], 4.0, v56);
        }
      }
      else
      {
        v57 = 1061997773;
        draw_galaxy_line(154, *(v11 - 168), *(v11 - 167), *v11, v11[1], 4.0, v56);
      }
      ++v10;
      v11 += 168;
    }
    while ( v10 < dword_4DF9B8 );
  }
  set_color_white(v56);
  v12 = 0;
  v13 = (float *)(this + 68036);
  do
  {
    *(float *)&v44 = v13[1] - 128.0;
    *(float *)&v41 = *v13 - 128.0;
    queue_axis_aligned_textured_quad_uv(
      v12 + 139,
      v41,
      v44,
      1132462080,
      1132462080,
      0x1000000,
      v56,
      0,
      0,
      1065353216,
      1065353216,
      15,
      0);
    ++v12;
    v13 += 40;
  }
  while ( v12 < 10 );
  v14 = 1;
  v15 = NAN;
  v16 = *((_DWORD *)MEMORY[0x4DF904] + 163);
  v17 = *(float *)(v16 + 96);
  v18 = *(float *)(v16 + 100);
  v19 = *(_DWORD *)(this + 8);
  v48 = v17;
  v49 = v18;
  *(_DWORD *)(this + 69508) = 0;
  if ( v19 == 1 )
  {
    v20 = *(float **)(this + 69516);
    if ( v20[19] - v20[136] < v48
      && v20[21] + v20[136] + v20[19] > v48
      && v20[20] - v20[136] < v18
      && v20[22] + v20[20] + v20[136] > v18 )
    {
      *(_DWORD *)(this + 69508) = 1;
      v21 = 1;
      if ( dword_4DF9B8 >= 1 )
      {
        v22 = (_DWORD *)(this + 716);
        do
        {
          if ( v21 == *(_DWORD *)(this + 69504) )
            *v22 = 1065353216;
          else
            *v22 = 0;
          ++v21;
          v22 += 168;
        }
        while ( v21 <= dword_4DF9B8 );
      }
    }
  }
  if ( *(_DWORD *)(this + 4) == 1 )
  {
    *(_DWORD *)(672 * *(_DWORD *)(this + 69504) + this + 44) = 1065353216;
  }
  else if ( !*(_DWORD *)(this + 69508) )
  {
    if ( *(_DWORD *)(this + 8) == 1 )
    {
      v23 = 672 * *(_DWORD *)(this + 69504);
      v24 = *(_DWORD *)(v23 + this + 36);
      v53 = *(float *)(v23 + this + 28) - v48;
      v25 = *(float *)(v23 + this + 32) - v49;
      v55 = v24;
      v50 = v53;
      v52 = v24;
      v54 = v25;
      v51 = v54;
      if ( normalize_vector(&v50) < 17.0 && !*(_DWORD *)(this + 69508) )
      {
        v15 = *(float *)(this + 69504);
        *(_DWORD *)(this + 69508) = 2;
        *(_DWORD *)(672 * LODWORD(v15) + this + 44) = 1065353216;
      }
    }
    if ( dword_4DF9B8 >= 1 )
    {
      v26 = (float *)(this + 716);
      do
      {
        v27 = *(v26 - 4) - v48;
        v55 = *((_DWORD *)v26 - 2);
        v53 = v27;
        v28 = *(v26 - 3) - v49;
        v52 = v55;
        v50 = v53;
        v54 = v28;
        v51 = v54;
        if ( normalize_vector(&v50) >= 17.0 || *(_DWORD *)(this + 69508) )
        {
          if ( *(_DWORD *)(this + 8) == 1 && v14 == *(_DWORD *)(this + 69504) )
            *v26 = 1.0;
          else
            *v26 = 0.0;
        }
        else
        {
          *(_DWORD *)(this + 69508) = 2;
          v15 = *(float *)&v14;
          *v26 = 1.0;
        }
        ++v14;
        v26 += 168;
      }
      while ( v14 <= dword_4DF9B8 );
    }
  }
  if ( *((_BYTE *)MEMORY[0x4DF904] + 278764) )
    return 0;
  v29 = *(_DWORD *)(this + 69492);
  v30 = *(_DWORD *)(v29 + 416);
  if ( (v30 & 0x20) == 0 )
  {
    v32 = *(_DWORD *)(this + 8);
    if ( v32 == 1 )
    {
      v33 = *(_DWORD *)(this + 69532);
      v34 = *(_DWORD *)(v33 + 416);
      if ( (v34 & 0x20) != 0 )
      {
        LOBYTE(v34) = v34 & 0xDF;
        *(_DWORD *)(v33 + 416) = v34;
        destroy_galaxy((_DWORD **)this);
        *(_DWORD *)(*(_DWORD *)(this + 69488) + 68) = *(_DWORD *)(this + 69504);
        load_frontend_level_by_mode_and_index(
          (char *)(*(_DWORD *)(this + 69488) + 43124),
          *(_DWORD *)(*(_DWORD *)(this + 69488) + 64),
          *(_DWORD *)(*(_DWORD *)(this + 69488) + 68));
        v35 = *(_DWORD *)(this + 69488);
        if ( !*(_DWORD *)(v35 + 64) && *(_DWORD *)(v35 + 19337160) == 1 )
          return 2;
        return 1;
      }
    }
    v36 = *(_DWORD *)(this + 69536);
    v37 = *(_DWORD *)(v36 + 416);
    if ( (v37 & 0x20) != 0 )
    {
      LOBYTE(v37) = v37 & 0xDF;
      *(_DWORD *)(v36 + 416) = v37;
      destroy_galaxy((_DWORD **)this);
      *(_DWORD *)(*(_DWORD *)(this + 69488) + 68) = *(_DWORD *)(this + 69504);
      load_frontend_level_by_mode_and_index(
        (char *)(*(_DWORD *)(this + 69488) + 43124),
        *(_DWORD *)(*(_DWORD *)(this + 69488) + 64),
        *(_DWORD *)(*(_DWORD *)(this + 69488) + 68));
      *(_BYTE *)(*(_DWORD *)(this + 69488) + 16721360) = 1;
      *(_DWORD *)(*(_DWORD *)(this + 69488) + 16721364) = 129728 * *(_DWORD *)(this + 69504)
                                                        + *(_DWORD *)(this + 69488)
                                                        + 9716048;
      return 1;
    }
    if ( !*((_DWORD *)MEMORY[0x4DF904] + 9) && *(_DWORD *)(this + 4) != 1 )
    {
      v38 = *(_DWORD *)(this + 69508);
      if ( v38 != 1 )
      {
        if ( v38 != 2 || (*(_DWORD *)(*((_DWORD *)MEMORY[0x4DF904] + 163) + 60) & 0x4000) == 0 )
        {
          if ( v38
            || (*(_DWORD *)(*((_DWORD *)MEMORY[0x4DF904] + 163) + 60) & 0x4000) == 0
            || v32 != 1
            || dword_4DF9B8 <= 1 )
          {
            return 0;
          }
          close_galaxy_route(this);
          goto LABEL_85;
        }
        if ( LODWORD(v15) != *(_DWORD *)(this + 69504) )
        {
          if ( v32 == 1 )
          {
            close_galaxy_route(this);
            open_galaxy_route(this, v15);
LABEL_85:
            play_sound_effect(8);
            return 0;
          }
          if ( !v32 )
          {
            open_galaxy_route(this, v15);
            goto LABEL_85;
          }
        }
      }
    }
    return 0;
  }
  LOBYTE(v30) = v30 & 0xDF;
  *(_DWORD *)(v29 + 416) = v30;
  if ( *(_DWORD *)(this + 4) == 1 )
  {
    *((_DWORD *)MEMORY[0x4DF904] + 81133) = *((_DWORD *)MEMORY[0x4DF904] + 110);
    *((_DWORD *)MEMORY[0x4DF904] + 81131) = 11;
    *((_DWORD *)MEMORY[0x4DF904] + 110) = 8;
    return 0;
  }
  else
  {
    destroy_galaxy((_DWORD **)this);
    return 3;
  }
}

