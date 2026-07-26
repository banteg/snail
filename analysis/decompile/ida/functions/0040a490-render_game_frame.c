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
  float v21; // ecx
  float v22; // eax
  float v23; // ecx
  float viewport_width; // edx
  float v25; // eax
  float v26; // ecx
  struct RenderableBod *bod; // esi
  RenderableBod **v28; // edi
  uint32_t list_flags; // eax
  int32_t *v30; // ecx
  uint32_t v31; // eax
  float v32; // eax
  float render_arg_20; // edx
  float render_arg_1c; // eax
  TransformMatrix *p_transform; // ecx
  float v36; // eax
  float v37; // edx
  float v38; // eax
  Sprite *v39; // ebx
  int v40; // ecx
  SpriteFlag flags; // eax
  const void *v42; // esi
  double v43; // st7
  double v44; // st7
  int v45; // esi
  SpriteDepthNode *v46; // ecx
  SpriteDepthNode *v47; // edx
  SpriteDepthNode *v48; // edi
  float x; // ecx
  float y; // ecx
  struct SpriteDepthNode **depth_bucket_cursor; // ebx
  struct SpriteDepthNode *v52; // esi
  struct Sprite *sprite; // ecx
  int32_t *v54; // ebx
  char *v55; // eax
  struct RenderableBod **post_cursor; // edi
  BodBase *v57; // eax
  struct RenderableBod *v58; // esi
  float v59; // eax
  float v60; // ecx
  float v61; // edx
  TransformMatrix *v62; // eax
  float v63; // eax
  float v64; // ecx
  float v65; // edx
  bool v66; // zf
  TransformMatrix v67; // [esp-40h] [ebp-D0h] BYREF
  int32_t *v68; // [esp+10h] [ebp-80h]
  int v69; // [esp+14h] [ebp-7Ch]
  GameRoot *v70; // [esp+18h] [ebp-78h]
  int *v71; // [esp+1Ch] [ebp-74h]
  int v72; // [esp+20h] [ebp-70h]
  SpriteDepthNode *v73; // [esp+24h] [ebp-6Ch]
  int v74; // [esp+28h] [ebp-68h]
  float *p_viewport_width; // [esp+2Ch] [ebp-64h]
  Vec3 vector; // [esp+30h] [ebp-60h] BYREF
  _DWORD v77[4]; // [esp+3Ch] [ebp-54h] BYREF
  int v78; // [esp+4Ch] [ebp-44h] BYREF
  TransformMatrix transform; // [esp+50h] [ebp-40h] BYREF

  v1 = game;
  v2 = 0;
  v70 = game;
  render_skip_count = game->render_skip_count;
  if ( render_skip_count > 0 )
  {
    game->render_skip_count = render_skip_count - 1;
    return;
  }
  reset_render_counters();
  v72 = 0;
  set_matrix_identity(&transform);
  v4 = 0;
  memset(v77, 255, sizeof(v77));
  v71 = nullptr;
  p_flags = &v1->viewports[0].flags;
  v78 = -1;
  v6 = 5;
  do
  {
    if ( (*(_BYTE *)p_flags & 1) != 0 )
      ++v4;
    p_flags += 10;
    --v6;
  }
  while ( v6 );
  p_sort_key = &v1->viewports[0].sort_key;
  v8 = v1->viewports[1].flags & 0xFFFFFF;
  v71 = (int *)v4;
  v9 = 0;
  v1->viewports[1].flags = v8 | 0x2000000;
  v69 = 0;
  v68 = &v1->viewports[0].sort_key;
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
            v13 = &v77[v12];
            if ( v11 > v1->viewports[v77[v12]].sort_key )
            {
              if ( v12 <= 3 )
              {
                v14 = &v78;
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
              *v13 = v69;
              v10 = v2;
              v12 = v2;
            }
            ++v10;
            ++v12;
          }
          while ( v10 < v2 );
          p_sort_key = v68;
          v4 = (int)v71;
          v9 = v69;
        }
      }
      else
      {
        v77[0] = v9;
        v2 = 1;
      }
    }
    ++v9;
    p_sort_key += 10;
    v69 = v9;
    v68 = p_sort_key;
  }
  while ( v9 < 5 );
  v68 = nullptr;
  v69 = 0;
  if ( v4 > 0 )
  {
    v74 = v4;
    v71 = v77;
    do
    {
      v16 = *(float *)&v71;
      v17 = *v71;
      v18 = (char *)v1 + 40 * *v71;
      if ( (v18[1468] & 1) != 0 )
      {
        v19 = *((_DWORD *)v18 + 373);
        LOBYTE(v16) = v18[1496];
        v67.position_w = 0.0;
        v67.position.z = v16;
        LODWORD(v20) = v19 + 56;
        LODWORD(v21) = v19 + 128;
        v22 = *(float *)(v19 + 192);
        v67.position.y = v21;
        v23 = *((float *)v18 + 371);
        v67.position.x = v20;
        viewport_width = v1->viewports[v17].viewport_width;
        v67.basis_forward_w = v22;
        v25 = *((float *)v18 + 369);
        v67.basis_forward.z = v23;
        v26 = *((float *)v18 + 368);
        p_viewport_width = &v1->viewports[v17].viewport_width;
        render_camera(
          v26,
          v25,
          viewport_width,
          v67.basis_forward.z,
          v67.basis_forward_w,
          (TransformMatrix *)LODWORD(v67.position.x),
          (TransformMatrix *)LODWORD(v67.position.y),
          SLOBYTE(v67.position.z),
          0);
        if ( (v18[1468] & 2) == 0 )
        {
          bod = (struct RenderableBod *)v1->active_bod_list.first;
          v68 = nullptr;
          if ( bod )
          {
            v28 = &g_post_sprite_bods;
            do
            {
              if ( (bod->bod.bod.list_flags & 0x10) != 0 )
              {
                LODWORD(v67.position_w) = aDebugRender;
                debug_report_stub();
              }
              list_flags = bod->bod.bod.list_flags;
              if ( (list_flags & 2) != 0
                && (list_flags & 0x20) != 0
                && (list_flags & *((_DWORD *)v18 + 367) & 0xFF000000) != 0 )
              {
                if ( (list_flags & 0x80u) != 0 )
                {
                  v30 = v68;
                  *v28++ = bod;
                  v68 = (int32_t *)((char *)v30 + 1);
                }
                v31 = bod->bod.bod.list_flags;
                ++v69;
                if ( (v31 & 0x800) != 0 )
                  bod->bod.object->animation->progress = bod->render_animation_manager->progress;
                if ( (bod->bod.bod.list_flags & 0x400) != 0 )
                {
                  LOBYTE(v32) = is_bod_after_sprites(&bod->bod);
                  render_arg_20 = bod->bod.render_arg_20;
                  v67.position_w = v32;
                  render_arg_1c = bod->bod.render_arg_1c;
                  LODWORD(v67.position.z) = &bod->bod.color;
                  v67.position.y = render_arg_20;
                  v67.position.x = render_arg_1c;
                  p_transform = &bod->transform;
                }
                else
                {
                  transform.position = bod->bod.position;
                  LOBYTE(v36) = is_bod_after_sprites(&bod->bod);
                  v37 = bod->bod.render_arg_20;
                  v67.position_w = v36;
                  v38 = bod->bod.render_arg_1c;
                  LODWORD(v67.position.z) = &bod->bod.color;
                  v67.position.y = v37;
                  v67.position.x = v38;
                  p_transform = &transform;
                }
                render_object(
                  bod->bod.object,
                  p_transform,
                  v67.position.x,
                  v67.position.y,
                  (tColour *)LODWORD(v67.position.z),
                  SLOBYTE(v67.position_w));
              }
              bod = (struct RenderableBod *)bod->bod.bod.list_next;
            }
            while ( bod );
            v1 = v70;
          }
        }
        v39 = g_sprite_manager.active_heads[v17];
        v73 = g_sprite_depth_nodes;
        begin_sprite_depth_render_state();
        if ( v39 )
        {
          while ( 1 )
          {
            v40 = *((_DWORD *)v18 + 367);
            ++v72;
            flags = v39->flags;
            if ( (flags & v40 & 0xFF000000) != 0 )
              break;
            report_errorf(aLooseSpriteSce);
LABEL_63:
            v39 = v39->next;
            if ( !v39 )
              goto LABEL_64;
          }
          if ( (flags & 1) == 0 || (flags & 0x40) == 0 || (BYTE1(flags) & 2) != 0 )
            goto LABEL_63;
          v42 = (const void *)(*((_DWORD *)v18 + 373) + 128);
          vector = v39->position;
          qmemcpy(&v67, v42, sizeof(v67));
          multiply_vector_by_matrix(&vector, v67);
          vector.x = -vector.x;
          v43 = -vector.z;
          vector.z = v43;
          v44 = -v43 * 4.1967211 + v39->depth_bias;
          v45 = (__int64)v44;
          if ( v45 >= 256 )
          {
            v45 = 255;
            goto LABEL_50;
          }
          if ( (int)(__int64)v44 >= 0 )
          {
LABEL_50:
            v46 = g_sprite_depth_buckets[v45];
            v47 = v73++;
            if ( v46 )
            {
              v48 = nullptr;
              while ( v44 < v46->depth_key )
              {
                v48 = v46;
                v46 = v46->next;
                if ( !v46 )
                {
                  v48->next = v47;
                  goto LABEL_59;
                }
              }
              if ( v48 )
              {
                v48->next = v47;
                v47->next = v46;
              }
              else
              {
                v47->next = v46;
                g_sprite_depth_buckets[v45] = v47;
              }
            }
            else
            {
              g_sprite_depth_buckets[v45] = v47;
LABEL_59:
              v47->next = nullptr;
            }
            x = vector.x;
            v47->depth_key = v44;
            v47->position.x = x;
            y = vector.y;
            v47->sprite = v39;
            v47->position.y = y;
            v47->position.z = vector.z;
            v39->render_bucket_index = v45;
            v39->render_depth_key = v44;
          }
          v1 = v70;
          goto LABEL_63;
        }
LABEL_64:
        depth_bucket_cursor = &g_sprite_depth_buckets[255];
        do
        {
          v52 = *depth_bucket_cursor;
          if ( *depth_bucket_cursor )
          {
            do
            {
              sprite = v52->sprite;
              if ( (sprite->flags & 2) != 0 )
                build_sprite_tail(sprite, (const struct TransformMatrix *)(*((_DWORD *)v18 + 373) + 128));
              draw_sprite_quad((Vec3 *)&v52->position, v52->sprite);
              v52 = v52->next;
            }
            while ( v52 );
            *depth_bucket_cursor = nullptr;
          }
          --depth_bucket_cursor;
        }
        while ( (int)depth_bucket_cursor >= (int)g_sprite_depth_buckets );
        end_sprite_depth_render_state();
        begin_overlay_render_state();
        draw_font_text_queue(*((_DWORD *)v18 + 367));
        end_overlay_render_state();
        if ( (v18[1468] & 2) == 0 && v68 )
        {
          render_camera(
            *((float *)v18 + 368),
            *((float *)v18 + 369),
            *p_viewport_width,
            *((float *)v18 + 371),
            *(float *)(*((_DWORD *)v18 + 373) + 192),
            (TransformMatrix *)(*((_DWORD *)v18 + 373) + 56),
            (TransformMatrix *)(*((_DWORD *)v18 + 373) + 128),
            v18[1496],
            1);
          v54 = v68;
          v55 = (char *)v68 + v69;
          post_cursor = (struct RenderableBod **)(4 * (_DWORD)v68 + 5110544);
          v68 = nullptr;
          v69 = (int)v55;
          do
          {
            v57 = (BodBase *)*--post_cursor;
            if ( (v57->bod.list_flags & 0x400) != 0 )
            {
              v58 = (struct RenderableBod *)v57;
              LOBYTE(v59) = is_bod_after_sprites(v57);
              v60 = v58->bod.render_arg_20;
              v61 = v58->bod.render_arg_1c;
              v67.position_w = v59;
              LODWORD(v67.position.z) = &v58->bod.color;
              v67.position.y = v60;
              v67.position.x = v61;
              v62 = &v58->transform;
            }
            else
            {
              v58 = *post_cursor;
              transform.position = v57->position;
              LOBYTE(v63) = is_bod_after_sprites(&v58->bod);
              v64 = v58->bod.render_arg_20;
              v65 = v58->bod.render_arg_1c;
              v67.position_w = v63;
              LODWORD(v67.position.z) = &v58->bod.color;
              v67.position.y = v64;
              v67.position.x = v65;
              v62 = &transform;
            }
            render_object(
              v58->bod.object,
              v62,
              v67.position.x,
              v67.position.y,
              (tColour *)LODWORD(v67.position.z),
              SLOBYTE(v67.position_w));
            v54 = (int32_t *)((char *)v54 - 1);
          }
          while ( v54 );
          v1 = v70;
        }
      }
      v66 = v74 == 1;
      ++v71;
      --v74;
    }
    while ( !v66 );
  }
  noop_runtime_ai();
}
