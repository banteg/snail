/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_golb_ai @ 0x414820 */
/* selector: update_golb_ai */

// Advances one live Golb shot actor, borrowing the authored `SubLoc`/`Path` follow owners and the shared `SubGarbagePool` collision chain for straight-flight or path-follow motion, impact transitions, trail effects, and final cleanup.
void __thiscall update_golb_ai(int this)
{
  char *v2; // ecx
  int v3; // edx
  int v4; // ecx
  Vec3 *v5; // edi
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
  TrackRowCell *track_grid_cell_at_world_position; // eax
  TrackRowCell *v19; // edi
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
  float z; // ecx
  int v56; // eax
  int i; // esi
  double v58; // st7
  float v59; // edx
  float v60; // [esp+10h] [ebp-70h]
  float v61; // [esp+10h] [ebp-70h]
  Vec3 v62; // [esp+14h] [ebp-6Ch] BYREF
  Vec3 vector; // [esp+20h] [ebp-60h] BYREF
  Vec3 v64; // [esp+2Ch] [ebp-54h]
  float v65; // [esp+38h] [ebp-48h]
  float v66; // [esp+3Ch] [ebp-44h]
  float v67; // [esp+44h] [ebp-3Ch]
  float v68; // [esp+48h] [ebp-38h]
  float v69; // [esp+4Ch] [ebp-34h]
  float v70[3]; // [esp+50h] [ebp-30h] BYREF
  _DWORD v71[3]; // [esp+5Ch] [ebp-24h] BYREF
  _DWORD v72[3]; // [esp+68h] [ebp-18h] BYREF
  _DWORD v73[3]; // [esp+74h] [ebp-Ch] BYREF

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
        v5 = (Vec3 *)(this + 588);
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
            v60 = normalize_vector(v5);
            v64.x = *(float *)(this + 412) - *v6;
            v9 = *(float *)(this + 416) - *(float *)(this + 504);
            vector.x = v64.x;
            v64.y = v9;
            v10 = *(float *)(this + 420) - *(float *)(this + 508);
            vector.y = v64.y;
            v64.z = v10;
            vector.z = v64.z;
            if ( normalize_vector(&vector) < 0.40000001 )
            {
              spawn_golb_impact_sprite((_DWORD *)this, (_DWORD *)(this + 500));
              goto LABEL_82;
            }
            v11 = *(float *)(this + 428);
            v67 = vector.x * v11;
            v68 = vector.y * v11;
            v12 = v11 * vector.z;
            v13 = 1.0 - *(float *)(this + 428) * 1.5;
            v65 = v13 * v5->x;
            v66 = v13 * *(float *)(this + 592);
            v14 = v13 * *(float *)(this + 596);
            v64.x = v65 + v67;
            v15 = v66 + v68;
            v5->x = v64.x;
            v64.y = v15;
            *(float *)(this + 592) = v64.y;
            v64.z = v14 + v12;
            *(float *)(this + 596) = v64.z;
            normalize_vector(v5);
            v5->x = v60 * v5->x;
            *(float *)(this + 592) = v60 * *(float *)(this + 592);
            *(float *)(this + 596) = v60 * *(float *)(this + 596);
            if ( v60 < 0.1 )
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
          track_grid_cell_at_world_position = get_track_grid_cell_at_world_position(
                                                *(SubgameRuntime **)(this + 624),
                                                (Vec3 *)(this + 684));
          v19 = track_grid_cell_at_world_position;
          if ( track_grid_cell_at_world_position->tile_id == 30 )
          {
            *(_DWORD *)(this + 740) = *(_DWORD *)(this + 692);
            initialize_path_follow_golb((float *)(this + 700), (int)track_grid_cell_at_world_position, this + 500, this);
          }
          if ( *(float *)(this + 596) > 1.0 && v19[-8].tile_id == 30 )
          {
            *(float *)(this + 740) = *(float *)(this + 692) + 1.0;
            initialize_path_follow_golb((float *)(this + 700), (int)&v19[-8], this + 500, this);
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
            v68 = *(float *)(this + 604) * 0.5;
            v69 = *(float *)(this + 608) * 0.5;
            v64.x = *(float *)(this + 684) - v26;
            v27 = *(float *)(this + 688) - v68;
            v70[0] = v64.x;
            v64.y = v27;
            v28 = *(float *)(this + 692) - v69;
            v70[1] = v64.y;
            v64.z = v28;
            v70[2] = v64.z;
            spawn_golb_smoke(this, v70);
          }
        }
        else
        {
          add_vapour_point((Vapour *)(this + 128), (const TransformMatrix *)(this + 636));
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
        v68 = *(float *)(this + 604) * 0.30000001;
        v69 = *(float *)(this + 608) * 0.30000001;
        v64.x = *(float *)(this + 684) - v30;
        v31 = *(float *)(this + 688) - v68;
        v71[0] = LODWORD(v64.x);
        v64.y = v31;
        v32 = *(float *)(this + 692) - v69;
        v71[1] = LODWORD(v64.y);
        v64.z = v32;
        v71[2] = LODWORD(v64.z);
        spawn_golb_trail_sprite((_DWORD *)this, v71);
        v33 = *(float *)(this + 600) * 0.60000002;
        v68 = *(float *)(this + 604) * 0.60000002;
        v69 = *(float *)(this + 608) * 0.60000002;
        v64.x = *(float *)(this + 684) - v33;
        v34 = *(float *)(this + 688) - v68;
        v72[0] = LODWORD(v64.x);
        v64.y = v34;
        v35 = *(float *)(this + 692) - v69;
        v72[1] = LODWORD(v64.y);
        v64.z = v35;
        v72[2] = LODWORD(v64.z);
        spawn_golb_trail_sprite((_DWORD *)this, v72);
      }
      v36 = (float *)(this + 684);
      v64.x = *(float *)(this + 684) - *(float *)(this + 564);
      v64.y = *(float *)(this + 688) - *(float *)(this + 568);
      v37 = *(float *)(this + 692) - *(float *)(this + 572);
      *(float *)(this + 600) = v64.x;
      *(float *)(this + 604) = v64.y;
      v64.z = v37;
      *(float *)(this + 608) = v64.z;
      if ( *(_DWORD *)(this + 448) == 2 )
      {
        set_matrix_z_direction((TransformMatrix *)(this + 336), (const Vec3 *)(this + 600));
        rotate_matrix_world_z((TransformMatrix *)(this + 336), *(float *)(this + 436));
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
                v64.x = *(float *)(v43 + 104) - *v36;
                v64.y = *(float *)(v43 + 108) - *(float *)(this + 688);
                v44 = *(float *)(v43 + 112) - *(float *)(this + 692);
                v64.z = v44;
                v62 = v64;
                if ( v46 )
                  v44 = -v44;
                if ( v44 < 3.0 && normalize_vector(&v62) < *(float *)(v43 + 156) + 0.49000001 )
                {
                  *(_DWORD *)(v43 + 132) = 2;
                  *(_DWORD *)(v43 + 136) = v62.x >= 0.0 ? 1 : 2;
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
                  v64.x = *(float *)(i + 104) - *v36;
                  v64.y = *(float *)(i + 108) - *(float *)(this + 688);
                  v64.z = *(float *)(i + 112) - *(float *)(this + 692);
                  v62 = v64;
                  if ( normalize_vector(&v62) < 3.0 )
                  {
                    *(_DWORD *)(i + 132) = 2;
                    if ( v62.x >= 0.0 )
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
              v64.x = *(float *)(v49 + 3499016) - *v36;
              v64.y = *(float *)(v49 + 3499020) - *(float *)(this + 688);
              v51 = *(float *)(v49 + 3499024) - *(float *)(this + 692);
              v64.z = v51;
              v62 = v64;
              if ( v53 )
                v51 = -v51;
              if ( v51 < 2.5 && normalize_vector(&v62) < 2.5 )
              {
                *(_BYTE *)(this + 700) = 0;
                v61 = normalize_vector((Vec3 *)(this + 588));
                v62.y = 0.0;
                normalize_vector(&v62);
                vector.y = 0.0;
                vector.x = -(v61 * v62.x);
                v54 = v61 * v62.z;
                *(float *)(this + 588) = vector.x;
                vector.z = -v54;
                z = vector.z;
                *(_DWORD *)(this + 592) = 0;
                *(float *)(this + 596) = z;
                v56 = *(_DWORD *)(this + 448);
                switch ( v56 )
                {
                  case 1:
                    kill_golb((int *)this);
                    spawn_golb_impact_sprite((_DWORD *)this, (_DWORD *)(this + 684));
                    hit_slug_hazard((Slug *)(*(_DWORD *)(this + 624) + 236 * v47 + 3498912), 2);
                    return;
                  case 2:
                    kill_golb((int *)this);
                    spawn_golb_impact_sprite((_DWORD *)this, (_DWORD *)(this + 684));
                    hit_slug_hazard((Slug *)(*(_DWORD *)(this + 624) + 236 * v47 + 3498912), 4);
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
          if ( get_track_grid_cell_at_world_position(*(SubgameRuntime **)(this + 624), (Vec3 *)(this + 684))->tile_id != 14 )
            return;
          v58 = *(float *)(this + 692) - 1.0;
          v59 = *(float *)(this + 688);
          v64.x = *v36;
          v64.y = v59;
          v73[0] = LODWORD(v64.x);
          v64.z = v58;
          *(float *)&v73[1] = v59;
          v73[2] = LODWORD(v64.z);
          spawn_golb_impact_sprite((_DWORD *)this, v73);
        }
      }
LABEL_82:
      kill_golb((int *)this);
    }
  }
}
