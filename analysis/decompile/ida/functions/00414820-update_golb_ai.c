/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_golb_ai @ 0x414820 */
/* selector: update_golb_ai */

// Advances one live Golb shot actor, including straight-flight or path-follow motion, collision transitions, burst or smoke aftermath, and the final cleanup path once it passes the player or leaves the valid band.
void __thiscall sub_414820(int this)
{
  char *v2; // ecx
  int v3; // edx
  int v4; // ecx
  float *v5; // edi
  float *v6; // esi
  int v7; // eax
  double v8; // st7
  double v9; // st7
  double v10; // st7
  double v11; // st7
  double v12; // st7
  double v13; // st6
  double v14; // st6
  double v15; // st5
  double v16; // st7
  int v17; // eax
  char *v18; // eax
  char *v19; // edi
  int v20; // eax
  int v21; // eax
  double v22; // st7
  unsigned __int8 v24; // c0
  unsigned __int8 v25; // c3
  double v26; // st7
  double v27; // st7
  double v28; // st7
  _DWORD *v29; // ecx
  double v30; // st7
  double v31; // st7
  double v32; // st7
  double v33; // st7
  double v34; // st7
  double v35; // st7
  float *v36; // edi
  double v37; // st7
  double v38; // st7
  float v39; // ecx
  int v40; // edx
  int v41; // eax
  int v42; // ecx
  int v43; // esi
  double v44; // st7
  char v46; // c0
  int v47; // esi
  int j; // ebx
  int v49; // eax
  int v50; // ecx
  double v51; // st7
  char v53; // c0
  double v54; // st7
  float v55; // ecx
  int v56; // eax
  int i; // esi
  double v58; // st7
  double v59; // st7
  float v60; // edx
  float v61; // [esp+10h] [ebp-70h]
  float v62; // [esp+10h] [ebp-70h]
  float v63; // [esp+14h] [ebp-6Ch] BYREF
  float v64; // [esp+18h] [ebp-68h]
  float v65; // [esp+1Ch] [ebp-64h]
  float v66; // [esp+20h] [ebp-60h] BYREF
  float v67; // [esp+24h] [ebp-5Ch]
  float v68; // [esp+28h] [ebp-58h]
  float v69; // [esp+2Ch] [ebp-54h]
  float v70; // [esp+30h] [ebp-50h]
  float v71; // [esp+34h] [ebp-4Ch]
  float v72; // [esp+38h] [ebp-48h]
  float v73; // [esp+3Ch] [ebp-44h]
  float v74; // [esp+44h] [ebp-3Ch]
  float v75; // [esp+48h] [ebp-38h]
  float v76; // [esp+4Ch] [ebp-34h]
  float v77[3]; // [esp+50h] [ebp-30h] BYREF
  _DWORD v78[3]; // [esp+5Ch] [ebp-24h] BYREF
  _DWORD v79[3]; // [esp+68h] [ebp-18h] BYREF
  _DWORD v80[3]; // [esp+74h] [ebp-Ch] BYREF

  if ( !*(_BYTE *)(*(_DWORD *)(this + 624) + 9) )
  {
    if ( *(_BYTE *)(this + 444) == 1 )
    {
      *(_BYTE *)(this + 444) = 0;
      return;
    }
    if ( *(_DWORD *)(this + 580) == 1 )
    {
      v2 = (char *)(this + 700);
      if ( *(_BYTE *)(this + 700) == 1 )
      {
        switch ( calc_path_length_z(v2, *(float *)(this + 612), (float *)(this + 500), (float *)(this + 588)) )
        {
          case 0:
          case 2:
            *(_DWORD *)(this + 684) = *(_DWORD *)(this + 724);
            *(_DWORD *)(this + 688) = *(_DWORD *)(this + 728);
            *(_DWORD *)(this + 692) = *(_DWORD *)(this + 732);
            break;
          case 1:
          case 3:
            v3 = *(_DWORD *)(this + 504);
            *(_DWORD *)(this + 684) = *(_DWORD *)(this + 500);
            v4 = *(_DWORD *)(this + 508);
            *(_DWORD *)(this + 688) = v3;
            *(_DWORD *)(this + 692) = v4;
            break;
          default:
            break;
        }
      }
      else
      {
        v5 = (float *)(this + 588);
        v6 = (float *)(this + 500);
        *(float *)(this + 500) = *(float *)(this + 588) + *(float *)(this + 500);
        *(float *)(this + 504) = *(float *)(this + 592) + *(float *)(this + 504);
        *(float *)(this + 508) = *(float *)(this + 596) + *(float *)(this + 508);
        v7 = *(_DWORD *)(this + 448);
        if ( v7 )
        {
          if ( v7 == 2 && *(_DWORD *)(this + 408) )
          {
            v8 = *(float *)(this + 432) + *(float *)(this + 428);
            *(float *)(this + 428) = v8;
            if ( v8 > 1.0 )
              *(_DWORD *)(this + 428) = 1065353216;
            v61 = normalize_vector(v5);
            v69 = *(float *)(this + 412) - *v6;
            v9 = *(float *)(this + 416) - *(float *)(this + 504);
            v66 = v69;
            v70 = v9;
            v10 = *(float *)(this + 420) - *(float *)(this + 508);
            v67 = v70;
            v71 = v10;
            v68 = v71;
            if ( normalize_vector(&v66) < 0.40000001 )
            {
              spawn_golb_impact_sprite((_DWORD *)this, (_DWORD *)(this + 500));
              goto LABEL_82;
            }
            v11 = *(float *)(this + 428);
            v74 = v66 * v11;
            v75 = v67 * v11;
            v12 = v11 * v68;
            v13 = 1.0 - *(float *)(this + 428) * 1.5;
            v72 = v13 * *v5;
            v73 = v13 * *(float *)(this + 592);
            v14 = v13 * *(float *)(this + 596);
            v69 = v72 + v74;
            v15 = v73 + v75;
            *v5 = v69;
            v70 = v15;
            *(float *)(this + 592) = v70;
            v71 = v14 + v12;
            *(float *)(this + 596) = v71;
            normalize_vector(v5);
            *v5 = v61 * *v5;
            *(float *)(this + 592) = v61 * *(float *)(this + 592);
            *(float *)(this + 596) = v61 * *(float *)(this + 596);
            if ( v61 < 0.1 )
              goto LABEL_82;
          }
        }
        else if ( *(float *)(this + 504) > 0.49000001 || *(float *)(this + 504) < 0.0 )
        {
          *(float *)(this + 592) = *(float *)(this + 592) - *(float *)(*(_DWORD *)(this + 624) + 56) * 0.017000001;
        }
        else
        {
          *(_DWORD *)(this + 592) = 0;
        }
        v16 = *(float *)(this + 740);
        *(float *)(this + 684) = *v6;
        v17 = *(_DWORD *)(this + 508);
        *(_DWORD *)(this + 688) = *(_DWORD *)(this + 504);
        *(_DWORD *)(this + 692) = v17;
        if ( v16 < *(float *)(this + 692) && *(float *)(this + 504) < 1.0 && *(float *)(this + 504) > 0.0 )
        {
          v18 = get_track_grid_cell_at_world_position(*(char **)(this + 624), (float *)(this + 684));
          v19 = v18;
          if ( v18[60] == 30 )
          {
            *(_DWORD *)(this + 740) = *(_DWORD *)(this + 692);
            initialize_path_follow_golb((float *)(this + 700), (int)v18, this + 500, this);
          }
          if ( *(float *)(this + 596) > 1.0 && *(v19 - 612) == 30 )
          {
            *(float *)(this + 740) = *(float *)(this + 692) + 1.0;
            initialize_path_follow_golb((float *)(this + 700), (int)(v19 - 672), this + 500, this);
          }
        }
      }
      v20 = *(_DWORD *)(this + 448);
      if ( v20 )
      {
        v21 = v20 - 1;
        if ( v21 )
        {
          if ( v21 == 1 )
          {
            v22 = *(float *)(this + 440) + *(float *)(this + 436);
            *(float *)(this + 436) = v22;
            qmemcpy((void *)(this + 336), (const void *)(this + 636), 0x40u);
            if ( !(v24 | v25) )
              *(float *)(this + 436) = v22 - 6.2831855;
            spawn_golb_smoke(this, (float *)(this + 684));
            v26 = *(float *)(this + 600) * 0.5;
            v75 = *(float *)(this + 604) * 0.5;
            v76 = *(float *)(this + 608) * 0.5;
            v69 = *(float *)(this + 684) - v26;
            v27 = *(float *)(this + 688) - v75;
            v77[0] = v69;
            v70 = v27;
            v28 = *(float *)(this + 692) - v76;
            v77[1] = v70;
            v71 = v28;
            v77[2] = v71;
            spawn_golb_smoke(this, v77);
          }
        }
        else
        {
          add_vapour_point((_DWORD *)(this + 128), (const void *)(this + 636));
        }
      }
      else
      {
        v29 = (_DWORD *)(*(_DWORD *)(this + 584) + 72);
        *v29 = *(_DWORD *)(this + 684);
        v29[1] = *(_DWORD *)(this + 688);
        v29[2] = *(_DWORD *)(this + 692);
        spawn_golb_trail_sprite((_DWORD *)this, (_DWORD *)(this + 684));
        v30 = *(float *)(this + 600) * 0.30000001;
        v75 = *(float *)(this + 604) * 0.30000001;
        v76 = *(float *)(this + 608) * 0.30000001;
        v69 = *(float *)(this + 684) - v30;
        v31 = *(float *)(this + 688) - v75;
        *(float *)v78 = v69;
        v70 = v31;
        v32 = *(float *)(this + 692) - v76;
        *(float *)&v78[1] = v70;
        v71 = v32;
        *(float *)&v78[2] = v71;
        spawn_golb_trail_sprite((_DWORD *)this, v78);
        v33 = *(float *)(this + 600) * 0.60000002;
        v75 = *(float *)(this + 604) * 0.60000002;
        v76 = *(float *)(this + 608) * 0.60000002;
        v69 = *(float *)(this + 684) - v33;
        v34 = *(float *)(this + 688) - v75;
        *(float *)v79 = v69;
        v70 = v34;
        v35 = *(float *)(this + 692) - v76;
        *(float *)&v79[1] = v70;
        v71 = v35;
        *(float *)&v79[2] = v71;
        spawn_golb_trail_sprite((_DWORD *)this, v79);
      }
      v36 = (float *)(this + 684);
      v69 = *(float *)(this + 684) - *(float *)(this + 564);
      v70 = *(float *)(this + 688) - *(float *)(this + 568);
      v37 = *(float *)(this + 692) - *(float *)(this + 572);
      *(float *)(this + 600) = v69;
      *(float *)(this + 604) = v70;
      v71 = v37;
      *(float *)(this + 608) = v71;
      if ( *(_DWORD *)(this + 448) == 2 )
      {
        set_matrix_z_direction(this + 336, v37, (_DWORD *)(this + 600));
        rotate_matrix_world_z((float *)(this + 336), *(float *)(this + 436));
      }
      v38 = *(float *)(this + 620) + *(float *)(this + 616);
      v39 = *v36;
      *(float *)(this + 616) = v38;
      v40 = *(_DWORD *)(this + 688);
      *(float *)(this + 564) = v39;
      v41 = *(_DWORD *)(this + 692);
      *(_DWORD *)(this + 568) = v40;
      *(_DWORD *)(this + 572) = v41;
      if ( v38 <= 1.0 )
      {
        v42 = *(_DWORD *)(this + 632);
        if ( *(float *)(this + 508) >= (double)*(float *)(v42 + 10624)
          && *(float *)(v42 + 112) + 46.0 >= *(float *)(this + 508) )
        {
          v43 = *(_DWORD *)(*(_DWORD *)(this + 624) + 3510592);
          if ( v43 )
          {
            while ( 1 )
            {
              if ( *(_DWORD *)(v43 + 132) == 1 )
              {
                v69 = *(float *)(v43 + 104) - *v36;
                v70 = *(float *)(v43 + 108) - *(float *)(this + 688);
                v44 = *(float *)(v43 + 112) - *(float *)(this + 692);
                v63 = v69;
                v64 = v70;
                v71 = v44;
                v65 = v71;
                if ( v46 )
                  v44 = -v44;
                if ( v44 < 3.0 && normalize_vector(&v63) < *(float *)(v43 + 156) + 0.49000001 )
                {
                  *(_DWORD *)(v43 + 132) = 2;
                  *(_DWORD *)(v43 + 136) = v63 >= 0.0 ? 1 : 2;
                  add_subgoldy_score(*(int **)(this + 632), 0, 0);
                  if ( *(_DWORD *)(this + 448) != 1 )
                    break;
                }
              }
              v43 = *(_DWORD *)(v43 + 128);
              if ( !v43 )
                goto LABEL_53;
            }
            kill_golb((int *)this);
            spawn_golb_impact_sprite((_DWORD *)this, (_DWORD *)(this + 684));
            if ( *(_DWORD *)(this + 448) == 2 )
            {
              for ( i = *(_DWORD *)(*(_DWORD *)(this + 624) + 3510592); i; i = *(_DWORD *)(i + 128) )
              {
                if ( *(_DWORD *)(i + 132) == 1 )
                {
                  v69 = *(float *)(i + 104) - *v36;
                  v70 = *(float *)(i + 108) - *(float *)(this + 688);
                  v58 = *(float *)(i + 112) - *(float *)(this + 692);
                  v63 = v69;
                  v64 = v70;
                  v71 = v58;
                  v65 = v71;
                  if ( normalize_vector(&v63) < 3.0 )
                  {
                    *(_DWORD *)(i + 132) = 2;
                    if ( v63 >= 0.0 )
                      *(_DWORD *)(i + 136) = 1;
                    else
                      *(_DWORD *)(i + 136) = 2;
                    add_subgoldy_score(*(int **)(this + 632), 0, 0);
                  }
                }
              }
            }
            return;
          }
LABEL_53:
          v47 = 0;
          for ( j = 0; j < 1888; j += 236 )
          {
            v49 = j + *(_DWORD *)(this + 624);
            v50 = *(_DWORD *)(v49 + 3499040);
            if ( v50 == 1 || v50 == 4 )
            {
              v69 = *(float *)(v49 + 3499016) - *v36;
              v70 = *(float *)(v49 + 3499020) - *(float *)(this + 688);
              v51 = *(float *)(v49 + 3499024) - *(float *)(this + 692);
              v63 = v69;
              v64 = v70;
              v71 = v51;
              v65 = v71;
              if ( v53 )
                v51 = -v51;
              if ( v51 < 2.5 && normalize_vector(&v63) < 2.5 )
              {
                *(_BYTE *)(this + 700) = 0;
                v62 = normalize_vector((float *)(this + 588));
                v64 = 0.0;
                normalize_vector(&v63);
                v67 = 0.0;
                v66 = -(v62 * v63);
                v54 = v62 * v65;
                *(float *)(this + 588) = v66;
                v68 = -v54;
                v55 = v68;
                *(_DWORD *)(this + 592) = 0;
                *(float *)(this + 596) = v55;
                v56 = *(_DWORD *)(this + 448);
                switch ( v56 )
                {
                  case 1:
                    kill_golb((int *)this);
                    spawn_golb_impact_sprite((_DWORD *)this, (_DWORD *)(this + 684));
                    hit_slug_hazard(*(_DWORD *)(this + 624) + 236 * v47 + 3498912, 2);
                    return;
                  case 2:
                    kill_golb((int *)this);
                    spawn_golb_impact_sprite((_DWORD *)this, (_DWORD *)(this + 684));
                    hit_slug_hazard(*(_DWORD *)(this + 624) + 236 * v47 + 3498912, 4);
                    return;
                  case 0:
                    if ( *(_BYTE *)(this + 445) )
                    {
                      kill_golb((int *)this);
                      spawn_golb_impact_sprite((_DWORD *)this, (_DWORD *)(this + 684));
                    }
                    else
                    {
                      *(_BYTE *)(this + 445) = 1;
                    }
                    return;
                }
              }
            }
            ++v47;
          }
          if ( get_track_grid_cell_at_world_position(*(char **)(this + 624), (float *)(this + 684))[60] != 14 )
            return;
          v59 = *(float *)(this + 692) - 1.0;
          v60 = *(float *)(this + 688);
          v69 = *v36;
          v70 = v60;
          *(float *)v80 = v69;
          v71 = v59;
          *(float *)&v80[1] = v60;
          *(float *)&v80[2] = v71;
          spawn_golb_impact_sprite((_DWORD *)this, v80);
        }
      }
LABEL_82:
      kill_golb((int *)this);
    }
  }
}

