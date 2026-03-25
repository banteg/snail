/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: handle_subgoldy_collisions @ 0x444cf0 */
/* selector: handle_subgoldy_collisions */

// Processes Goldy's live collision sweep against rings, parcels, health pickups, garbage, salt, slugs, and related runtime object pools, updating score and the contact-damage gauge side effects as each hit resolves. Cross-port Android and iOS symbols match this helper to `cRSubGoldy::Collision()`.
void __thiscall sub_444CF0(int this)
{
  int i; // edi
  int v3; // eax
  double v4; // st7
  int j; // edi
  int v6; // eax
  double v7; // st7
  int k; // edi
  double v9; // st7
  __int64 v10; // rax
  int m; // edi
  int v12; // edx
  int v13; // ecx
  float *v14; // eax
  double v15; // st7
  long double v16; // st7
  int v17; // eax
  double v18; // st7
  int v19; // eax
  __int64 v20; // rax
  double v21; // st7
  double v22; // st6
  double v23; // st7
  double v24; // st7
  int n; // edi
  int v26; // eax
  double v27; // st7
  _DWORD *v28; // eax
  int v29; // ebx
  int ii; // edi
  int v31; // eax
  double v32; // st7
  double v33; // st7
  double v35; // st7
  char v36; // c0
  int v37; // eax
  double v38; // st7
  double v39; // st7
  double v41; // st7
  char v42; // c0
  int v43; // eax
  double v44; // st7
  double v45; // st7
  int jj; // edi
  int v47; // eax
  double v48; // st7
  int v49; // ecx
  int v50; // eax
  int v51; // ecx
  int v52; // eax
  int v53; // eax
  int v54; // eax
  int v55; // eax
  int v56; // eax
  int v57; // [esp-Ch] [ebp-90h]
  float v58; // [esp+10h] [ebp-74h]
  float v59; // [esp+18h] [ebp-6Ch] BYREF
  float v60; // [esp+1Ch] [ebp-68h]
  float v61; // [esp+20h] [ebp-64h]
  float v62; // [esp+24h] [ebp-60h] BYREF
  float v63; // [esp+28h] [ebp-5Ch]
  float v64; // [esp+2Ch] [ebp-58h]
  float v65; // [esp+30h] [ebp-54h]
  float v66; // [esp+34h] [ebp-50h]
  float v67; // [esp+38h] [ebp-4Ch]
  int v68; // [esp+3Ch] [ebp-48h]
  float v69; // [esp+40h] [ebp-44h]
  float v70; // [esp+44h] [ebp-40h]
  float v71; // [esp+48h] [ebp-3Ch] BYREF
  float v72; // [esp+4Ch] [ebp-38h]
  float v73; // [esp+50h] [ebp-34h]
  float v74; // [esp+54h] [ebp-30h]
  float v75; // [esp+58h] [ebp-2Ch]
  float v76[3]; // [esp+60h] [ebp-24h] BYREF
  float v77[3]; // [esp+6Ch] [ebp-18h] BYREF
  float v78[3]; // [esp+78h] [ebp-Ch] BYREF

  if ( !*(_BYTE *)(this + 1053) && !*(_BYTE *)(this + 1052) && !*(_BYTE *)(this + 728) )
  {
    if ( *(char *)(this + 824) >= 0 )
    {
      for ( i = 0; i < 6080; i += 152 )
      {
        v3 = i + *(_DWORD *)(this + 1032);
        if ( *(_DWORD *)(v3 + 3504448) == 1 && *(_BYTE *)(v3 + 3504468) == 1 )
        {
          v65 = *(float *)(v3 + 3504424) - *(float *)(this + 10596);
          v66 = *(float *)(v3 + 3504428) - *(float *)(this + 10600);
          v4 = *(float *)(v3 + 3504432) - *(float *)(this + 10604);
          v71 = v65;
          v72 = v66;
          v67 = v4;
          v73 = v67;
          if ( v4 < 1.0 && normalize_vector(&v71) < 0.98000002 )
          {
            if ( *(float *)(this + 468) == 0.0 )
              *(_DWORD *)(this + 468) = *(_DWORD *)(this + 472);
            *(_BYTE *)(i + *(_DWORD *)(this + 1032) + 3504468) = 0;
            apply_damage_gauge_delta((float *)(this + 964), 0.15000001, 0);
          }
        }
      }
    }
    for ( j = 0; j < 3520; j += 176 )
    {
      v6 = j + *(_DWORD *)(this + 1032);
      if ( *(_DWORD *)(v6 + 3500928) == 1 )
      {
        v65 = *(float *)(v6 + 3500904) - *(float *)(this + 10596);
        v66 = *(float *)(v6 + 3500908) - *(float *)(this + 10600);
        v7 = *(float *)(v6 + 3500912) - *(float *)(this + 10604);
        v59 = v65;
        v60 = v66;
        v67 = v7;
        v61 = v67;
        if ( v7 < 1.0 && normalize_vector(&v59) < 0.49000001 )
        {
          *(_DWORD *)(j + *(_DWORD *)(this + 1032) + 3500928) = 2;
          apply_damage_gauge_delta((float *)(this + 964), 0.02, 0);
        }
      }
    }
    for ( k = *(_DWORD *)(*(_DWORD *)(this + 1032) + 3510592); k; k = *(_DWORD *)(k + 128) )
    {
      if ( *(_DWORD *)(k + 132) == 1 )
      {
        v65 = *(float *)(k + 104) - *(float *)(this + 10596);
        v66 = *(float *)(k + 108) - *(float *)(this + 10600);
        v9 = *(float *)(k + 112) - *(float *)(this + 10604);
        v59 = v65;
        v60 = v66;
        v67 = v9;
        v61 = v67;
        if ( v9 < 1.0 && normalize_vector(&v59) < 0.98000002 )
        {
          if ( (*(_BYTE *)(this + 824) & 0x80) == 0 )
          {
            *(float *)(this + 1040) = *(float *)(this + 1040) - v59 * *(float *)(this + 1048) * 0.18000001;
            *(float *)(this + 1048) = *(float *)(this + 1048) - v61 * *(float *)(this + 1048) * 0.1;
          }
          *(_DWORD *)(k + 132) = 2;
          if ( v59 >= 0.0 )
            *(_DWORD *)(k + 136) = 1;
          else
            *(_DWORD *)(k + 136) = 2;
          add_subgoldy_score((int *)this, 0, 0);
          apply_damage_gauge_delta((float *)(this + 964), 0.039999999, 0);
          v10 = (__int64)((double)next_math_random_value() * -0.000061035156);
          play_sound_effect(39 - v10);
        }
      }
    }
    for ( m = 0; m < 1888; m += 236 )
    {
      v12 = *(_DWORD *)(this + 1032);
      v13 = *(_DWORD *)(m + v12 + 3499040);
      v14 = (float *)(m + v12);
      if ( v13 == 1 || v13 == 4 )
      {
        v65 = v14[874754] - *(float *)(this + 10596);
        v66 = v14[874755] - *(float *)(this + 10600);
        v15 = v14[874756] - *(float *)(this + 10604);
        v59 = v65;
        v60 = v66;
        v67 = v15;
        v61 = v67;
        if ( v15 < 2.0 )
        {
          v16 = normalize_vector(&v59);
          v58 = v16;
          if ( v16 < 1.5675001 )
          {
            if ( (*(_BYTE *)(this + 824) & 0x80) != 0 )
            {
              kill_slug_hazard(m + *(_DWORD *)(this + 1032) + 3498912);
            }
            else if ( *(_BYTE *)(this + 728) )
            {
              v24 = *(float *)(*(_DWORD *)(this + 1032) + 56);
              *(float *)(this + 1048) = v24 * v24 * 0.0040000002 * -8.0;
              apply_damage_gauge_delta((float *)(this + 964), 1.0, 0);
            }
            else
            {
              v17 = *(_DWORD *)(this + 1032);
              *(_BYTE *)(this + 728) = 1;
              *(_BYTE *)(this + 900) = 0;
              v68 = 0;
              v18 = *(float *)(v17 + 56);
              *(_DWORD *)(this + 1040) = 0;
              v69 = v18 * 0.2;
              *(float *)(this + 1044) = v69;
              v70 = v18 * -0.2;
              *(float *)(this + 1048) = v70;
              initialize_subgoldy_fall_state(this);
              v19 = *(_DWORD *)(this + 1032);
              *(_DWORD *)(this + 17128) = 10;
              *(_BYTE *)(m + v19 + 3499129) = 1;
              v20 = (__int64)((double)next_math_random_value() * -0.000061035156);
              play_slug_voice(m + *(_DWORD *)(this + 1032) + 3498912, 34 - v20);
              v21 = v58 * 0.5;
              *(_DWORD *)(this + 16204) = 0;
              v74 = v21 * v59;
              v75 = v60 * v21;
              v71 = v74 + *(float *)(this + 10596);
              v22 = v75 + *(float *)(this + 10600);
              v76[0] = v71;
              v57 = *(_DWORD *)(this + 896);
              v72 = v22;
              v23 = v21 * v61 + *(float *)(this + 10604);
              v76[1] = v72;
              v73 = v23;
              v76[2] = v73;
              firework_shoot(v76, v57, 92, 80);
            }
          }
        }
      }
    }
    for ( n = 0; n < 7000; n += 140 )
    {
      v26 = n + *(_DWORD *)(this + 1032);
      if ( *(_DWORD *)(v26 + 19260600) == 1 )
      {
        v71 = *(float *)(v26 + 19260560) - *(float *)(this + 10596);
        v72 = *(float *)(v26 + 19260564) - *(float *)(this + 10600);
        v27 = *(float *)(v26 + 19260568) - *(float *)(this + 10604);
        v77[0] = v71;
        v77[1] = v72;
        v73 = v27;
        v77[2] = v73;
        if ( v27 < 1.0 && normalize_vector(v77) < 1.24 )
        {
          add_subgoldy_score((int *)this, 3, 0);
          play_voice_manager((int)unk_751498, 10, 1u, -1);
          play_sound_effect(27);
          *(_DWORD *)(n + *(_DWORD *)(this + 1032) + 19260600) = 4;
          v28 = *(_DWORD **)(this + 1032);
          v29 = *(_DWORD *)(this + 17208) + 1;
          *(_DWORD *)(this + 17208) = v29;
          if ( !v28[16] )
            sprintf((char *const)(v28[880357] + 716), "%i/%i", v29, v28[442488]);
        }
      }
    }
  }
  for ( ii = 0; ii < 928; ii += 116 )
  {
    v31 = ii + *(_DWORD *)(this + 1032);
    if ( *(_DWORD *)(v31 + 3498040) == 1 )
    {
      v59 = *(float *)(v31 + 3498000) - *(float *)(this + 10596);
      v60 = *(float *)(v31 + 3498004) - *(float *)(this + 10600);
      v32 = *(float *)(v31 + 3498008) - *(float *)(this + 10604);
      v62 = v59;
      v63 = v60;
      v61 = v32;
      v33 = *(float *)(this + 108);
      v64 = v61;
      if ( v33 >= 0.49000001 && v61 < 1.0 )
      {
        v35 = v60;
        if ( v36 )
          v35 = -v35;
        if ( v35 < 0.40000001 && normalize_vector(&v62) < 0.98000002 )
        {
          play_sound_effect(14);
          *(_DWORD *)(ii + *(_DWORD *)(this + 1032) + 3498040) = 2;
          health_collect_particles(this, ii + *(_DWORD *)(this + 1032) + 3497984);
          apply_damage_gauge_delta((float *)(this + 964), -0.5, 0);
        }
      }
    }
  }
  v37 = *(_DWORD *)(this + 1032);
  if ( *(_DWORD *)(v37 + 3497520) == 1 )
  {
    v59 = *(float *)(v37 + 3497496) - *(float *)(this + 10596);
    v60 = *(float *)(v37 + 3497500) - *(float *)(this + 10600);
    v38 = *(float *)(v37 + 3497504) - *(float *)(this + 10604);
    v62 = v59;
    v63 = v60;
    v61 = v38;
    v39 = *(float *)(this + 108);
    v64 = v61;
    if ( v39 >= 0.49000001 && v61 < 1.0 )
    {
      v41 = v60;
      if ( v42 )
        v41 = -v41;
      if ( v41 < 0.40000001 && normalize_vector(&v62) < 0.98000002 )
      {
        *(_DWORD *)(*(_DWORD *)(this + 1032) + 3497520) = 2;
        noop_runtime_ai(this);
        *(float *)(this + 1048) = *(float *)(*(_DWORD *)(this + 1032) + 56) * 0.5;
      }
    }
  }
  v43 = *(_DWORD *)(this + 1032);
  if ( *(_DWORD *)(v43 + 3497628) == 1 )
  {
    v59 = *(float *)(v43 + 3497588) - *(float *)(this + 10596);
    v60 = *(float *)(v43 + 3497592) - *(float *)(this + 10600);
    v44 = *(float *)(v43 + 3497596) - *(float *)(this + 10604);
    v62 = v59;
    v63 = v60;
    v61 = v44;
    v45 = *(float *)(this + 108);
    v64 = v61;
    if ( v45 >= 0.49000001 && v61 < 1.0 && normalize_vector(&v62) < 3.0 )
    {
      *(_DWORD *)(*(_DWORD *)(this + 1032) + 3497628) = 2;
      arm_jetpack_gauge(this + 10064);
    }
  }
  for ( jj = 0; jj < 1008; jj += 504 )
  {
    v47 = jj + *(_DWORD *)(this + 1032);
    if ( *(_DWORD *)(v47 + 3520524) == 1 )
    {
      v71 = *(float *)(v47 + 3520500) - *(float *)(this + 10596);
      v72 = *(float *)(v47 + 3520504) - *(float *)(this + 10600);
      v48 = *(float *)(v47 + 3520508) - *(float *)(this + 10604);
      v78[0] = v71;
      v78[1] = v72;
      v73 = v48;
      v78[2] = v73;
      if ( v48 < 1.0 && normalize_vector(v78) < 0.98000002 )
      {
        *(_DWORD *)(jj + *(_DWORD *)(this + 1032) + 3520524) = 2;
        if ( !*(_BYTE *)(this + 1088) )
        {
          v49 = *(_DWORD *)(this + 1032);
          v50 = *(_DWORD *)(jj + v49 + 3520532);
          if ( v50 == 3 || v50 == 7 )
          {
            *(_DWORD *)(this + 1048) = -1110651699;
            play_sound_effect(43);
          }
          else
          {
            *(float *)(this + 1048) = *(float *)(v49 + 56) * 0.5;
          }
        }
        v51 = *(_DWORD *)(this + 1032);
        v52 = *(_DWORD *)(jj + v51 + 3520532);
        switch ( v52 )
        {
          case 4:
          case 5:
            v55 = *(_DWORD *)(this + 1028);
            if ( v55 < 10 )
            {
              if ( (*(_BYTE *)(v51 + 76) & 0x10) != 0 && *(_DWORD *)(v51 + 64) != 3 )
                *(_DWORD *)(this + 1028) = v55 + 1;
              play_voice_manager((int)unk_751498, 5, 1u, -1);
            }
            v56 = *(_DWORD *)(this + 776);
            if ( v56 >= 8 )
            {
              if ( v56 == 8 )
                *(_DWORD *)(this + 776) = 7;
            }
            else
            {
              *(_DWORD *)(this + 776) = v56 + 1;
            }
            v54 = *(_DWORD *)(this + 776) - 1;
            if ( v54 > 6 )
LABEL_105:
              v54 = 6;
LABEL_106:
            play_sound_effect(v54 + 1);
            add_subgoldy_score((int *)this, 2, 0);
            continue;
          case 8:
            v53 = *(_DWORD *)(this + 776);
            if ( v53 >= 8 )
            {
              if ( v53 == 8 )
                *(_DWORD *)(this + 776) = 7;
            }
            else
            {
              *(_DWORD *)(this + 776) = v53 + 1;
            }
            v54 = *(_DWORD *)(this + 776) - 1;
            if ( v54 > 6 )
              goto LABEL_105;
            goto LABEL_106;
          case 1:
            add_subgoldy_score((int *)this, 2, 0);
            play_sound_effect(1);
            break;
          case 2:
          case 6:
            add_subgoldy_score((int *)this, 2, 0);
            play_sound_effect(42);
            *(_DWORD *)(this + 884) = *(_DWORD *)(this + 888);
            initialize_nuke(this + 336);
            break;
        }
      }
    }
  }
}

