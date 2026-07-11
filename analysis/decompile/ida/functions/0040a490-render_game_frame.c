/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: render_game_frame @ 0x40a490 */
/* selector: render_game_frame */

void __thiscall render_game_frame(GameRoot *game)
{
  GameRoot *v1; // edi
  int v2; // esi
  int32_t render_skip_count; // eax
  int v4; // ebx
  uint32_t *p_flags; // eax
  int v6; // ecx
  int32_t *p_sort_key; // eax
  int v8; // edx
  int v9; // ecx
  int v10; // edx
  int32_t v11; // ebp
  int v12; // eax
  int *v13; // ebx
  int *v14; // eax
  int v15; // ecx
  float v16; // edx
  int v17; // ebx
  char *v18; // ebp
  int v19; // eax
  float v20; // edx
  float *p_viewport_width; // esi
  float v22; // ecx
  float v23; // eax
  float v24; // ecx
  float v25; // edx
  float v26; // eax
  float v27; // ecx
  FrameBodBase *first; // esi
  FrameBodBase **v29; // edi
  uint32_t list_flags; // eax
  int32_t *v31; // ecx
  uint32_t v32; // eax
  float v33; // eax
  float render_arg_20; // edx
  float render_arg_1c; // eax
  TransformMatrix *p_transform; // ecx
  float v37; // eax
  float v38; // edx
  float v39; // eax
  int v40; // ebx
  int v41; // ecx
  int v42; // eax
  const void *v43; // esi
  double v44; // st7
  double v45; // st7
  int v46; // esi
  SpriteDepthNode *v47; // ecx
  SpriteDepthNode *v48; // edx
  SpriteDepthNode *v49; // edi
  float v50; // ecx
  float v51; // ecx
  int *v52; // ebx
  int v53; // esi
  int v54; // ecx
  int v55; // ecx
  int32_t *v56; // ebx
  char *v57; // eax
  int *v58; // edi
  int v59; // eax
  int v60; // esi
  float v61; // eax
  float v62; // ecx
  float v63; // edx
  TransformMatrix *v64; // eax
  float *v65; // eax
  float v66; // eax
  float v67; // ecx
  float v68; // edx
  bool v69; // zf
  float v70[16]; // [esp-40h] [ebp-D0h] BYREF
  char v71; // [esp+0h] [ebp-90h]
  int32_t *v72; // [esp+10h] [ebp-80h]
  int v73; // [esp+14h] [ebp-7Ch]
  GameRoot *v74; // [esp+18h] [ebp-78h]
  float v75; // [esp+1Ch] [ebp-74h]
  int v76; // [esp+20h] [ebp-70h]
  SpriteDepthNode *v77; // [esp+24h] [ebp-6Ch]
  int v78; // [esp+28h] [ebp-68h]
  float *v79; // [esp+2Ch] [ebp-64h]
  float v80; // [esp+30h] [ebp-60h] BYREF
  float v81; // [esp+34h] [ebp-5Ch]
  float v82; // [esp+38h] [ebp-58h]
  _DWORD v83[4]; // [esp+3Ch] [ebp-54h] BYREF
  int v84; // [esp+4Ch] [ebp-44h] BYREF
  TransformMatrix transform; // [esp+50h] [ebp-40h] BYREF

  v1 = game;
  v2 = 0;
  v74 = game;
  render_skip_count = game->render_skip_count;
  if ( render_skip_count > 0 )
  {
    game->render_skip_count = render_skip_count - 1;
    return;
  }
  reset_render_counters();
  v76 = 0;
  set_matrix_identity(&transform);
  *(float *)&v4 = 0.0;
  memset(v83, 255, sizeof(v83));
  v75 = 0.0;
  p_flags = &v1->render_camera_slots[0].flags;
  v84 = -1;
  v6 = 5;
  do
  {
    if ( (*(_BYTE *)p_flags & 1) != 0 )
      ++v4;
    p_flags += 10;
    --v6;
  }
  while ( v6 );
  p_sort_key = &v1->render_camera_slots[0].sort_key;
  v8 = v1->render_camera_slots[1].flags & 0xFFFFFF;
  v75 = *(float *)&v4;
  v9 = 0;
  v1->render_camera_slots[1].flags = v8 | 0x2000000;
  v73 = 0;
  v72 = &v1->render_camera_slots[0].sort_key;
  do
  {
    if ( (p_sort_key[1] & 1) != 0 )
    {
      if ( v2 )
      {
        v10 = 0;
        if ( v2 > 0 )
        {
          v11 = *p_sort_key;
          v12 = 0;
          do
          {
            v13 = &v83[v12];
            if ( v11 > v1->render_camera_slots[v83[v12]].sort_key )
            {
              if ( v12 <= 3 )
              {
                v14 = &v84;
                v15 = 4 - v10;
                do
                {
                  *v14 = *(v14 - 1);
                  --v14;
                  --v15;
                }
                while ( v15 );
              }
              ++v2;
              *v13 = v73;
              v10 = v2;
              v12 = v2;
            }
            ++v10;
            ++v12;
          }
          while ( v10 < v2 );
          p_sort_key = v72;
          *(float *)&v4 = v75;
          v9 = v73;
        }
      }
      else
      {
        v83[0] = v9;
        v2 = 1;
      }
    }
    ++v9;
    p_sort_key += 10;
    v73 = v9;
    v72 = p_sort_key;
  }
  while ( v9 < 5 );
  v72 = nullptr;
  v73 = 0;
  if ( v4 > 0 )
  {
    v78 = v4;
    v75 = COERCE_FLOAT(v83);
    do
    {
      v16 = v75;
      v17 = *(_DWORD *)LODWORD(v75);
      v18 = (char *)v1 + 40 * *(_DWORD *)LODWORD(v75);
      if ( (v18[1468] & 1) != 0 )
      {
        v19 = *((_DWORD *)v18 + 373);
        LOBYTE(v16) = v18[1496];
        v70[15] = 0.0;
        v70[14] = v16;
        LODWORD(v20) = v19 + 56;
        p_viewport_width = &v1->render_camera_slots[v17].viewport_width;
        LODWORD(v22) = v19 + 128;
        v23 = *(float *)(v19 + 192);
        v70[13] = v22;
        v24 = *((float *)v18 + 371);
        v70[12] = v20;
        v25 = *p_viewport_width;
        v70[11] = v23;
        v26 = *((float *)v18 + 369);
        v70[10] = v24;
        v27 = *((float *)v18 + 368);
        v79 = p_viewport_width;
        render_camera(
          (int)p_viewport_width,
          v27,
          v26,
          v25,
          v70[10],
          SLODWORD(v70[11]),
          v70[12],
          SLODWORD(v70[13]),
          SLODWORD(v70[14]),
          0,
          v71);
        if ( (v18[1468] & 2) == 0 )
        {
          first = v1->active_bod_list.first;
          v72 = nullptr;
          if ( first )
          {
            v29 = (FrameBodBase **)&unk_4DFB10;
            do
            {
              if ( (first->bod.list_flags & 0x10) != 0 )
              {
                LODWORD(v70[15]) = aDebugRender;
                debug_report_stub();
              }
              list_flags = first->bod.list_flags;
              if ( (list_flags & 2) != 0
                && (list_flags & 0x20) != 0
                && (list_flags & *((_DWORD *)v18 + 367) & 0xFF000000) != 0 )
              {
                if ( (list_flags & 0x80u) != 0 )
                {
                  v31 = v72;
                  *v29++ = first;
                  v72 = (int32_t *)((char *)v31 + 1);
                }
                v32 = first->bod.list_flags;
                ++v73;
                if ( (v32 & 0x800) != 0 )
                  *(_DWORD *)(*((_DWORD *)first->object + 47) + 12) = first[2].bod.list_prev->bod.list_flags;
                if ( (first->bod.list_flags & 0x400) != 0 )
                {
                  LOBYTE(v33) = is_bod_after_sprites((char *)first);
                  render_arg_20 = first->render_arg_20;
                  v70[15] = v33;
                  render_arg_1c = first->render_arg_1c;
                  LODWORD(v70[14]) = &first->color;
                  v70[13] = render_arg_20;
                  v70[12] = render_arg_1c;
                  p_transform = (TransformMatrix *)&first[1];
                }
                else
                {
                  transform.position.x = first->position.x;
                  transform.position.y = first->position.y;
                  transform.position.z = first->position.z;
                  LOBYTE(v37) = is_bod_after_sprites((char *)first);
                  v38 = first->render_arg_20;
                  v70[15] = v37;
                  v39 = first->render_arg_1c;
                  LODWORD(v70[14]) = &first->color;
                  v70[13] = v38;
                  v70[12] = v39;
                  p_transform = &transform;
                }
                render_object(
                  (Object *)first->object,
                  p_transform,
                  SLODWORD(v70[12]),
                  v70[13],
                  (Color4f *)LODWORD(v70[14]),
                  SLOBYTE(v70[15]));
              }
              first = first->bod.list_next;
            }
            while ( first );
            v1 = v74;
          }
        }
        v40 = g_sprite_active_heads[v17];
        v77 = g_sprite_depth_nodes;
        begin_sprite_depth_render_state();
        if ( v40 )
        {
          while ( 1 )
          {
            v41 = *((_DWORD *)v18 + 367);
            ++v76;
            v42 = *(_DWORD *)(v40 + 4);
            if ( (v42 & v41 & 0xFF000000) != 0 )
              break;
            report_errorf(aLooseSpriteSce);
LABEL_63:
            v40 = *(_DWORD *)(v40 + 12);
            if ( !v40 )
              goto LABEL_64;
          }
          if ( (v42 & 1) == 0 || (v42 & 0x40) == 0 || (v42 & 0x200) != 0 )
            goto LABEL_63;
          v43 = (const void *)(*((_DWORD *)v18 + 373) + 128);
          v80 = *(float *)(v40 + 72);
          v81 = *(float *)(v40 + 76);
          v82 = *(float *)(v40 + 80);
          qmemcpy(v70, v43, sizeof(v70));
          multiply_vector_by_matrix(
            &v80,
            v70[0],
            v70[1],
            v70[2],
            SLODWORD(v70[3]),
            v70[4],
            v70[5],
            v70[6],
            SLODWORD(v70[7]),
            v70[8],
            v70[9],
            v70[10],
            SLODWORD(v70[11]),
            v70[12],
            v70[13],
            v70[14],
            SLODWORD(v70[15]));
          v80 = -v80;
          v44 = -v82;
          v82 = v44;
          v45 = -v44 * 4.1967211 + *(float *)(v40 + 152);
          v46 = (__int64)v45;
          if ( v46 >= 256 )
          {
            v46 = 255;
            goto LABEL_50;
          }
          if ( (int)(__int64)v45 >= 0 )
          {
LABEL_50:
            v47 = g_sprite_depth_buckets[v46];
            v48 = v77++;
            if ( v47 )
            {
              v49 = nullptr;
              while ( v45 < v47->depth_key )
              {
                v49 = v47;
                v47 = v47->next;
                if ( !v47 )
                {
                  v49->next = v48;
                  goto LABEL_59;
                }
              }
              if ( v49 )
              {
                v49->next = v48;
                v48->next = v47;
              }
              else
              {
                v48->next = v47;
                g_sprite_depth_buckets[v46] = v48;
              }
            }
            else
            {
              g_sprite_depth_buckets[v46] = v48;
LABEL_59:
              v48->next = nullptr;
            }
            v50 = v80;
            v48->depth_key = v45;
            v48->position.x = v50;
            v51 = v81;
            v48->sprite = (void *)v40;
            v48->position.y = v51;
            v48->position.z = v82;
            *(_DWORD *)(v40 + 20) = v46;
            *(float *)(v40 + 24) = v45;
          }
          v1 = v74;
          goto LABEL_63;
        }
LABEL_64:
        v52 = (int *)&g_sprite_depth_buckets[255];
        do
        {
          v53 = *v52;
          if ( *v52 )
          {
            do
            {
              v54 = *(_DWORD *)(v53 + 20);
              if ( (*(_BYTE *)(v54 + 4) & 2) != 0 )
                update_sprite_facing_angle(v54, (float *)(*((_DWORD *)v18 + 373) + 128));
              draw_sprite_quad(v53 + 4, *(float *)(v53 + 20));
              v53 = *(_DWORD *)v53;
            }
            while ( v53 );
            *v52 = 0;
          }
          --v52;
        }
        while ( (int)v52 >= (int)g_sprite_depth_buckets );
        end_sprite_depth_render_state();
        begin_overlay_render_state();
        draw_font_text_queue(*((_DWORD *)v18 + 367));
        end_overlay_render_state();
        if ( (v18[1468] & 2) == 0 && v72 )
        {
          LOBYTE(v55) = v18[1496];
          render_camera(
            v53,
            *((float *)v18 + 368),
            *((float *)v18 + 369),
            *v79,
            *((float *)v18 + 371),
            *(_DWORD *)(*((_DWORD *)v18 + 373) + 192),
            COERCE_FLOAT(*((_DWORD *)v18 + 373) + 56),
            *((_DWORD *)v18 + 373) + 128,
            v55,
            1,
            v71);
          v56 = v72;
          v57 = (char *)v72 + v73;
          v58 = (int *)(4 * (_DWORD)v72 + 5110544);
          v72 = nullptr;
          v73 = (int)v57;
          do
          {
            v59 = *--v58;
            if ( (*(_DWORD *)(v59 + 4) & 0x400) != 0 )
            {
              v60 = v59;
              LOBYTE(v61) = is_bod_after_sprites((char *)v59);
              v62 = *(float *)(v60 + 32);
              v63 = *(float *)(v60 + 28);
              v70[15] = v61;
              LODWORD(v70[14]) = v60 + 40;
              v70[13] = v62;
              v70[12] = v63;
              v64 = (TransformMatrix *)(v60 + 56);
            }
            else
            {
              v65 = (float *)(v59 + 16);
              v60 = *v58;
              transform.position.x = *v65;
              transform.position.y = v65[1];
              transform.position.z = v65[2];
              LOBYTE(v66) = is_bod_after_sprites((char *)v60);
              v67 = *(float *)(v60 + 32);
              v68 = *(float *)(v60 + 28);
              v70[15] = v66;
              LODWORD(v70[14]) = v60 + 40;
              v70[13] = v67;
              v70[12] = v68;
              v64 = &transform;
            }
            render_object(
              *(Object **)(v60 + 36),
              v64,
              SLODWORD(v70[12]),
              v70[13],
              (Color4f *)LODWORD(v70[14]),
              SLOBYTE(v70[15]));
            v56 = (int32_t *)((char *)v56 - 1);
          }
          while ( v56 );
          v1 = v74;
        }
      }
      v69 = v78 == 1;
      LODWORD(v75) += 4;
      --v78;
    }
    while ( !v69 );
  }
  noop_runtime_ai();
}

