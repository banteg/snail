/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: render_game_frame @ 0x40a490 */
/* selector: render_game_frame */

// Renders every active root viewport in camera sort order, synchronizes flagged Snail/weapon BODs from their borrowed cRAnimManager progress into Object::animation, draws eligible BODs, depth-buckets the active sprite list through the fixed 3000-node workspace, drains all 256 buckets, renders queued text, and replays staged after-sprite BODs. The native function has a void thiscall ABI; iOS names the same root-owned method `cRGame::Render()`, and Android preserves the animation-progress chain at port-specific offsets.
void __thiscall render_game_frame(GameRoot *game)
{
  GameRoot *v1; // edi
  int v2; // esi
  int32_t render_skip_count; // eax
  int v4; // ebx
  uint32_t *p_flags; // eax
  int i; // ecx
  int32_t *p_sort_key; // eax
  int v8; // ecx
  int v9; // edx
  int32_t v10; // ebp
  int v11; // eax
  int *v12; // ebx
  int *v13; // eax
  int v14; // ecx
  int v15; // ebx
  char *v16; // ebp
  struct RenderableBod *bod; // esi
  RenderableBod **v18; // edi
  uint32_t list_flags; // eax
  TransformMatrix *p_transform; // ecx
  cRSprite *v21; // ebx
  SpriteFlag flags; // eax
  TransformMatrix *v23; // esi
  double v24; // st7
  double v25; // st7
  int v26; // esi
  SpriteDepthNode *v27; // ecx
  SpriteDepthNode *v28; // edx
  SpriteDepthNode *v29; // edi
  float x; // ecx
  float y; // ecx
  struct SpriteDepthNode **depth_bucket_cursor; // ebx
  struct SpriteDepthNode *v33; // esi
  struct Sprite *sprite; // ecx
  int v35; // ebx
  int v36; // eax
  struct RenderableBod **post_cursor; // edi
  BodBase *v38; // eax
  struct RenderableBod *v39; // esi
  TransformMatrix *v40; // eax
  bool v41; // zf
  float render_arg_1c; // [esp-10h] [ebp-A0h]
  float v43; // [esp-10h] [ebp-A0h]
  float render_arg_20; // [esp-Ch] [ebp-9Ch]
  float v45; // [esp-Ch] [ebp-9Ch]
  tColour *p_color; // [esp-8h] [ebp-98h]
  tColour *v47; // [esp-8h] [ebp-98h]
  char v48; // [esp-4h] [ebp-94h]
  char v49; // [esp-4h] [ebp-94h]
  int32_t *v50; // [esp+10h] [ebp-80h]
  int v51; // [esp+10h] [ebp-80h]
  int v52; // [esp+14h] [ebp-7Ch]
  int v53; // [esp+14h] [ebp-7Ch]
  int v55; // [esp+1Ch] [ebp-74h]
  int *v56; // [esp+1Ch] [ebp-74h]
  int v57; // [esp+20h] [ebp-70h]
  SpriteDepthNode *v58; // [esp+24h] [ebp-6Ch]
  int v59; // [esp+28h] [ebp-68h]
  float *p_viewport_width; // [esp+2Ch] [ebp-64h]
  Vec3 vector; // [esp+30h] [ebp-60h] BYREF
  _DWORD v62[4]; // [esp+3Ch] [ebp-54h] BYREF
  int v63; // [esp+4Ch] [ebp-44h] BYREF
  TransformMatrix transform; // [esp+50h] [ebp-40h] BYREF

  v1 = game;
  v2 = 0;
  render_skip_count = game->render_skip_count;
  if ( render_skip_count > 0 )
  {
    game->render_skip_count = render_skip_count - 1;
    return;
  }
  reset_render_counters();
  v57 = 0;
  set_matrix_identity(&transform);
  v4 = 0;
  memset(v62, 255, sizeof(v62));
  p_flags = &v1->viewports[0].flags;
  v63 = -1;
  for ( i = 5; i != 0; --i )
  {
    if ( (*(_BYTE *)p_flags & 1) != 0 )
      ++v4;
    p_flags += 10;
  }
  p_sort_key = &v1->viewports[0].sort_key;
  v55 = v4;
  v8 = 0;
  v1->viewports[1].flags = v1->viewports[1].flags & 0xFFFFFF | 0x2000000;
  v52 = 0;
  v50 = &v1->viewports[0].sort_key;
  do
  {
    if ( (p_sort_key[1] & 1) != 0 )
    {
      if ( v2 != 0 )
      {
        v9 = 0;
        if ( v2 > 0 )
        {
          v10 = *p_sort_key;
          v11 = 0;
          do
          {
            v12 = &v62[v11];
            if ( v10 > v1->viewports[v62[v11]].sort_key )
            {
              if ( v11 <= 3 )
              {
                v13 = &v63;
                v14 = 4 - v9;
                do
                {
                  *v13 = *(v13 - 1);
                  --v13;
                  --v14;
                }
                while ( v14 != 0 );
              }
              ++v2;
              *v12 = v52;
              v9 = v2;
              v11 = v2;
            }
            ++v9;
            ++v11;
          }
          while ( v9 < v2 );
          p_sort_key = v50;
          v4 = v55;
          v8 = v52;
        }
      }
      else
      {
        v62[0] = v8;
        v2 = 1;
      }
    }
    ++v8;
    p_sort_key += 10;
    v52 = v8;
    v50 = p_sort_key;
  }
  while ( v8 < 5 );
  v51 = 0;
  v53 = 0;
  if ( v4 > 0 )
  {
    v59 = v4;
    v56 = v62;
    do
    {
      v15 = *v56;
      v16 = (char *)v1 + 40 * *v56;
      if ( (v16[1468] & 1) != 0 )
      {
        p_viewport_width = &v1->viewports[v15].viewport_width;
        render_camera(
          *((float *)v16 + 368),
          *((float *)v16 + 369),
          *p_viewport_width,
          *((float *)v16 + 371),
          *(float *)(*((_DWORD *)v16 + 373) + 192),
          (TransformMatrix *)(*((_DWORD *)v16 + 373) + 56),
          (TransformMatrix *)(*((_DWORD *)v16 + 373) + 128),
          v16[1496],
          0);
        if ( (v16[1468] & 2) == 0 )
        {
          bod = (struct RenderableBod *)v1->active_bod_list.first;
          v51 = 0;
          if ( bod != nullptr )
          {
            v18 = &g_post_sprite_bods;
            do
            {
              if ( (bod->bod.bod.list_flags & 0x10) != 0 )
                debug_report_stub(aDebugRender);
              list_flags = bod->bod.bod.list_flags;
              if ( (list_flags & 2) != 0
                && (list_flags & 0x20) != 0
                && (list_flags & *((_DWORD *)v16 + 367) & 0xFF000000) != 0 )
              {
                if ( (list_flags & 0x80u) != 0 )
                {
                  *v18++ = bod;
                  ++v51;
                }
                ++v53;
                if ( (bod->bod.bod.list_flags & 0x800) != 0 )
                  bod->bod.object->animation->progress = bod->render_animation_manager->progress;
                if ( (bod->bod.bod.list_flags & 0x400) != 0 )
                {
                  v48 = is_bod_after_sprites(&bod->bod);
                  p_color = &bod->bod.color;
                  render_arg_20 = bod->bod.render_arg_20;
                  render_arg_1c = bod->bod.render_arg_1c;
                  p_transform = &bod->transform;
                }
                else
                {
                  transform.position = bod->bod.position;
                  v48 = is_bod_after_sprites(&bod->bod);
                  p_color = &bod->bod.color;
                  render_arg_20 = bod->bod.render_arg_20;
                  render_arg_1c = bod->bod.render_arg_1c;
                  p_transform = &transform;
                }
                render_object(bod->bod.object, p_transform, render_arg_1c, render_arg_20, p_color, v48);
              }
              bod = (struct RenderableBod *)bod->bod.bod.list_next;
            }
            while ( bod != nullptr );
            v1 = game;
          }
        }
        v21 = g_sprite_manager.active_heads[v15];
        v58 = g_sprite_depth_nodes;
        begin_sprite_depth_render_state();
        if ( v21 != nullptr )
        {
          while ( 1 )
          {
            ++v57;
            flags = v21->flags;
            if ( (flags & *((_DWORD *)v16 + 367) & 0xFF000000) != 0 )
              break;
            report_errorf(aLooseSpriteSce);
LABEL_63:
            v21 = v21->next;
            if ( v21 == nullptr )
              goto LABEL_64;
          }
          if ( (flags & 1) == 0 || (flags & 0x40) == 0 || (BYTE1(flags) & 2) != 0 )
            goto LABEL_63;
          v23 = (TransformMatrix *)(*((_DWORD *)v16 + 373) + 128);
          vector = v21->position;
          multiply_vector_by_matrix(&vector, *v23);
          vector.x = -vector.x;
          v24 = -vector.z;
          vector.z = v24;
          v25 = -v24 * 4.1967211 + v21->depth_bias;
          v26 = (__int64)v25;
          if ( v26 >= 256 )
          {
            v26 = 255;
            goto LABEL_50;
          }
          if ( (int)(__int64)v25 >= 0 )
          {
LABEL_50:
            v27 = g_sprite_depth_buckets[v26];
            v28 = v58++;
            if ( v27 != nullptr )
            {
              v29 = nullptr;
              while ( v25 < v27->depth_key )
              {
                v29 = v27;
                v27 = v27->next;
                if ( v27 == nullptr )
                {
                  v29->next = v28;
                  goto LABEL_59;
                }
              }
              if ( v29 != nullptr )
              {
                v29->next = v28;
                v28->next = v27;
              }
              else
              {
                v28->next = v27;
                g_sprite_depth_buckets[v26] = v28;
              }
            }
            else
            {
              g_sprite_depth_buckets[v26] = v28;
LABEL_59:
              v28->next = nullptr;
            }
            x = vector.x;
            v28->depth_key = v25;
            v28->position.x = x;
            y = vector.y;
            v28->sprite = v21;
            v28->position.y = y;
            v28->position.z = vector.z;
            v21->render_bucket_index = v26;
            v21->render_depth_key = v25;
          }
          v1 = game;
          goto LABEL_63;
        }
LABEL_64:
        depth_bucket_cursor = &g_sprite_depth_buckets[255];
        do
        {
          v33 = *depth_bucket_cursor;
          if ( *depth_bucket_cursor != nullptr )
          {
            do
            {
              sprite = v33->sprite;
              if ( (sprite->flags & 2) != 0 )
                build_sprite_tail(sprite, (const struct TransformMatrix *)(*((_DWORD *)v16 + 373) + 128));
              draw_sprite_quad((Vec3 *)&v33->position, v33->sprite);
              v33 = v33->next;
            }
            while ( v33 != nullptr );
            *depth_bucket_cursor = nullptr;
          }
          --depth_bucket_cursor;
        }
        while ( (int)depth_bucket_cursor >= (int)g_sprite_depth_buckets );
        end_sprite_depth_render_state();
        begin_overlay_render_state();
        draw_font_text_queue(*((_DWORD *)v16 + 367));
        end_overlay_render_state();
        if ( (v16[1468] & 2) == 0 && v51 != 0 )
        {
          render_camera(
            *((float *)v16 + 368),
            *((float *)v16 + 369),
            *p_viewport_width,
            *((float *)v16 + 371),
            *(float *)(*((_DWORD *)v16 + 373) + 192),
            (TransformMatrix *)(*((_DWORD *)v16 + 373) + 56),
            (TransformMatrix *)(*((_DWORD *)v16 + 373) + 128),
            v16[1496],
            1);
          v35 = v51;
          v36 = v51 + v53;
          post_cursor = (struct RenderableBod **)(4 * v51 + 5110544);
          v51 = 0;
          v53 = v36;
          do
          {
            v38 = (BodBase *)*--post_cursor;
            if ( (v38->bod.list_flags & 0x400) != 0 )
            {
              v39 = (struct RenderableBod *)v38;
              v49 = is_bod_after_sprites(v38);
              v47 = &v39->bod.color;
              v45 = v39->bod.render_arg_20;
              v43 = v39->bod.render_arg_1c;
              v40 = &v39->transform;
            }
            else
            {
              v39 = *post_cursor;
              transform.position = v38->position;
              v49 = is_bod_after_sprites(&v39->bod);
              v47 = &v39->bod.color;
              v45 = v39->bod.render_arg_20;
              v43 = v39->bod.render_arg_1c;
              v40 = &transform;
            }
            render_object(v39->bod.object, v40, v43, v45, v47, v49);
            --v35;
          }
          while ( v35 != 0 );
          v1 = game;
        }
      }
      v41 = v59 == 1;
      ++v56;
      --v59;
    }
    while ( !v41 );
  }
  noop_runtime_ai();
}
