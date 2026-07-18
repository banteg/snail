/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: render_game_frame @ 0x40a490 */
/* selector: render_game_frame */

// Renders every active root viewport in camera sort order, synchronizes flagged Snail/weapon BODs from their borrowed AnimManager progress into Object::animation, draws eligible BODs, depth-buckets the active sprite list through the fixed 3000-node workspace, drains all 256 buckets, renders queued text, and replays staged after-sprite BODs. The native function has a void thiscall ABI; iOS names the same root-owned method `cRGame::Render()`, and Android preserves the animation-progress chain at port-specific offsets.
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
  struct RenderableBod *bod; // esi
  RenderableBod **v29; // edi
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
  Sprite *v40; // ebx
  int v41; // ecx
  SpriteFlag flags; // eax
  const void *v43; // esi
  double v44; // st7
  double v45; // st7
  int v46; // esi
  SpriteDepthNode *v47; // ecx
  SpriteDepthNode *v48; // edx
  SpriteDepthNode *v49; // edi
  float x; // ecx
  float y; // ecx
  struct SpriteDepthNode **depth_bucket_cursor; // ebx
  struct SpriteDepthNode *v53; // esi
  struct Sprite *sprite; // ecx
  int v55; // ecx
  int32_t *v56; // ebx
  char *v57; // eax
  struct RenderableBod **post_cursor; // edi
  struct RenderableBod *v59; // eax
  struct RenderableBod *v60; // esi
  float v61; // eax
  float v62; // ecx
  float v63; // edx
  TransformMatrix *v64; // eax
  float *p_x; // eax
  float v66; // eax
  float v67; // ecx
  float v68; // edx
  bool v69; // zf
  TransformMatrix v70; // [esp-40h] [ebp-D0h] BYREF
  char v71; // [esp+0h] [ebp-90h]
  int32_t *v72; // [esp+10h] [ebp-80h]
  int v73; // [esp+14h] [ebp-7Ch]
  GameRoot *v74; // [esp+18h] [ebp-78h]
  int *v75; // [esp+1Ch] [ebp-74h]
  int v76; // [esp+20h] [ebp-70h]
  SpriteDepthNode *v77; // [esp+24h] [ebp-6Ch]
  int v78; // [esp+28h] [ebp-68h]
  float *v79; // [esp+2Ch] [ebp-64h]
  Vec3 vector; // [esp+30h] [ebp-60h] BYREF
  _DWORD v81[4]; // [esp+3Ch] [ebp-54h] BYREF
  int v82; // [esp+4Ch] [ebp-44h] BYREF
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
  v4 = 0;
  memset(v81, 255, sizeof(v81));
  v75 = nullptr;
  p_flags = &v1->render_camera_slots[0].flags;
  v82 = -1;
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
  v75 = (int *)v4;
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
            v13 = &v81[v12];
            if ( v11 > v1->render_camera_slots[v81[v12]].sort_key )
            {
              if ( v12 <= 3 )
              {
                v14 = &v82;
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
          v4 = (int)v75;
          v9 = v73;
        }
      }
      else
      {
        v81[0] = v9;
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
    v75 = v81;
    do
    {
      v16 = *(float *)&v75;
      v17 = *v75;
      v18 = (char *)v1 + 40 * *v75;
      if ( (v18[1468] & 1) != 0 )
      {
        v19 = *((_DWORD *)v18 + 373);
        LOBYTE(v16) = v18[1496];
        v70.position.w = 0.0;
        v70.position.z = v16;
        LODWORD(v20) = v19 + 56;
        p_viewport_width = &v1->render_camera_slots[v17].viewport_width;
        LODWORD(v22) = v19 + 128;
        v23 = *(float *)(v19 + 192);
        v70.position.y = v22;
        v24 = *((float *)v18 + 371);
        v70.position.x = v20;
        v25 = *p_viewport_width;
        v70.basis_forward.w = v23;
        v26 = *((float *)v18 + 369);
        v70.basis_forward.z = v24;
        v27 = *((float *)v18 + 368);
        v79 = p_viewport_width;
        render_camera(
          (int)p_viewport_width,
          v27,
          v26,
          v25,
          v70.basis_forward.z,
          SLODWORD(v70.basis_forward.w),
          v70.position.x,
          SLODWORD(v70.position.y),
          SLODWORD(v70.position.z),
          0,
          v71);
        if ( (v18[1468] & 2) == 0 )
        {
          bod = (struct RenderableBod *)v1->active_bod_list.first;
          v72 = nullptr;
          if ( bod )
          {
            v29 = &g_post_sprite_bods;
            do
            {
              if ( (bod->bod.bod.list_flags & 0x10) != 0 )
              {
                LODWORD(v70.position.w) = aDebugRender;
                debug_report_stub();
              }
              list_flags = bod->bod.bod.list_flags;
              if ( (list_flags & 2) != 0
                && (list_flags & 0x20) != 0
                && (list_flags & *((_DWORD *)v18 + 367) & 0xFF000000) != 0 )
              {
                if ( (list_flags & 0x80u) != 0 )
                {
                  v31 = v72;
                  *v29++ = bod;
                  v72 = (int32_t *)((char *)v31 + 1);
                }
                v32 = bod->bod.bod.list_flags;
                ++v73;
                if ( (v32 & 0x800) != 0 )
                  bod->bod.object->animation->progress = bod->render_animation_manager->progress;
                if ( (bod->bod.bod.list_flags & 0x400) != 0 )
                {
                  LOBYTE(v33) = is_bod_after_sprites((char *)bod);
                  render_arg_20 = bod->bod.render_arg_20;
                  v70.position.w = v33;
                  render_arg_1c = bod->bod.render_arg_1c;
                  LODWORD(v70.position.z) = &bod->bod.color;
                  v70.position.y = render_arg_20;
                  v70.position.x = render_arg_1c;
                  p_transform = &bod->transform;
                }
                else
                {
                  transform.position.x = bod->bod.position.x;
                  transform.position.y = bod->bod.position.y;
                  transform.position.z = bod->bod.position.z;
                  LOBYTE(v37) = is_bod_after_sprites((char *)bod);
                  v38 = bod->bod.render_arg_20;
                  v70.position.w = v37;
                  v39 = bod->bod.render_arg_1c;
                  LODWORD(v70.position.z) = &bod->bod.color;
                  v70.position.y = v38;
                  v70.position.x = v39;
                  p_transform = &transform;
                }
                render_object(
                  bod->bod.object,
                  p_transform,
                  v70.position.x,
                  v70.position.y,
                  (tColour *)LODWORD(v70.position.z),
                  SLOBYTE(v70.position.w));
              }
              bod = (struct RenderableBod *)bod->bod.bod.list_next;
            }
            while ( bod );
            v1 = v74;
          }
        }
        v40 = g_sprite_manager.active_heads[v17];
        v77 = g_sprite_depth_nodes;
        begin_sprite_depth_render_state();
        if ( v40 )
        {
          while ( 1 )
          {
            v41 = *((_DWORD *)v18 + 367);
            ++v76;
            flags = v40->flags;
            if ( (flags & v41 & 0xFF000000) != 0 )
              break;
            report_errorf(aLooseSpriteSce);
LABEL_63:
            v40 = v40->next;
            if ( !v40 )
              goto LABEL_64;
          }
          if ( (flags & 1) == 0 || (flags & 0x40) == 0 || (BYTE1(flags) & 2) != 0 )
            goto LABEL_63;
          v43 = (const void *)(*((_DWORD *)v18 + 373) + 128);
          vector = v40->position;
          qmemcpy(&v70, v43, sizeof(v70));
          multiply_vector_by_matrix(&vector, v70);
          vector.x = -vector.x;
          v44 = -vector.z;
          vector.z = v44;
          v45 = -v44 * 4.1967211 + v40->depth_bias;
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
            x = vector.x;
            v48->depth_key = v45;
            v48->position.x = x;
            y = vector.y;
            v48->sprite = v40;
            v48->position.y = y;
            v48->position.z = vector.z;
            v40->render_bucket_index = v46;
            v40->render_depth_key = v45;
          }
          v1 = v74;
          goto LABEL_63;
        }
LABEL_64:
        depth_bucket_cursor = &g_sprite_depth_buckets[255];
        do
        {
          v53 = *depth_bucket_cursor;
          if ( *depth_bucket_cursor )
          {
            do
            {
              sprite = v53->sprite;
              if ( (sprite->flags & 2) != 0 )
                update_sprite_facing_angle(sprite, (const struct TransformMatrix *)(*((_DWORD *)v18 + 373) + 128));
              draw_sprite_quad((Vec3 *)&v53->position, v53->sprite);
              v53 = v53->next;
            }
            while ( v53 );
            *depth_bucket_cursor = nullptr;
          }
          --depth_bucket_cursor;
        }
        while ( (int)depth_bucket_cursor >= (int)g_sprite_depth_buckets );
        end_sprite_depth_render_state();
        begin_overlay_render_state();
        draw_font_text_queue(*((_DWORD *)v18 + 367));
        end_overlay_render_state();
        if ( (v18[1468] & 2) == 0 && v72 )
        {
          LOBYTE(v55) = v18[1496];
          render_camera(
            (int)v53,
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
          post_cursor = (struct RenderableBod **)(4 * (_DWORD)v72 + 5110544);
          v72 = nullptr;
          v73 = (int)v57;
          do
          {
            v59 = *--post_cursor;
            if ( (v59->bod.bod.list_flags & 0x400) != 0 )
            {
              v60 = v59;
              LOBYTE(v61) = is_bod_after_sprites((char *)v59);
              v62 = v60->bod.render_arg_20;
              v63 = v60->bod.render_arg_1c;
              v70.position.w = v61;
              LODWORD(v70.position.z) = &v60->bod.color;
              v70.position.y = v62;
              v70.position.x = v63;
              v64 = &v60->transform;
            }
            else
            {
              p_x = &v59->bod.position.x;
              v60 = *post_cursor;
              transform.position.x = *p_x;
              transform.position.y = p_x[1];
              transform.position.z = p_x[2];
              LOBYTE(v66) = is_bod_after_sprites((char *)v60);
              v67 = v60->bod.render_arg_20;
              v68 = v60->bod.render_arg_1c;
              v70.position.w = v66;
              LODWORD(v70.position.z) = &v60->bod.color;
              v70.position.y = v67;
              v70.position.x = v68;
              v64 = &transform;
            }
            render_object(
              v60->bod.object,
              v64,
              v70.position.x,
              v70.position.y,
              (tColour *)LODWORD(v70.position.z),
              SLOBYTE(v70.position.w));
            v56 = (int32_t *)((char *)v56 - 1);
          }
          while ( v56 );
          v1 = v74;
        }
      }
      v69 = v78 == 1;
      ++v75;
      --v78;
    }
    while ( !v69 );
  }
  noop_runtime_ai();
}
