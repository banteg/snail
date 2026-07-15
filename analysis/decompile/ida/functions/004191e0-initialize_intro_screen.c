/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_intro_screen @ 0x4191e0 */
/* selector: initialize_intro_screen */

// Void Windows `cRLogo::Init(char*)`: loads SpaceRed plus INTROTEXT.OGG, parses an intro or credits script into the root-owned 1024-entry LogoLetter bank, borrows sequential preloaded image objects, derives each velocity from Duration, and releases the script through void `RShellMemoryFree`.
void __thiscall initialize_intro_screen(Logo *logo, char *file_name)
{
  int32_t v2; // ebx
  int landscape_script_by_name; // eax
  char *v5; // esi
  char *case_insensitive_substring; // eax
  char *v7; // eax
  char *v8; // ecx
  char v9; // al
  float v10; // edi
  bool v11; // zf
  char *v12; // esi
  char *v13; // ecx
  char *v14; // eax
  char i; // dl
  _BYTE *v16; // eax
  int32_t renderable_count; // ecx
  LogoLetter *v18; // eax
  FrameBodBase **p_first; // ecx
  FrameBodBase *first; // edx
  FrameBodBase *list_prev; // edx
  float v22; // esi
  int32_t v23; // eax
  Vec4 *p_position; // ecx
  double v25; // st7
  float v26; // edx
  double v27; // st7
  double v28; // st7
  double v29; // st6
  Object *object; // ecx
  Vec3 *p_velocity; // eax
  double v32; // st7
  char v33; // al
  double v34; // st7
  int32_t v35; // ecx
  uint32_t list_flags; // eax
  LogoLetter *v37; // ecx
  FrameBodBase **v38; // eax
  FrameBodBase *v39; // edx
  FrameBodBase *v40; // edx
  uint32_t v41; // eax
  int v42; // eax
  double v43; // st7
  Vec4 *v44; // eax
  int v45; // edx
  float v46; // ecx
  Vec3 *v47; // eax
  int v48; // eax
  double v49; // st7
  double v50; // st7
  int32_t v51; // eax
  int v52; // ecx
  Vec3 *v53; // eax
  float *p_x; // edx
  float v55; // edi
  char *cursor; // [esp+10h] [ebp-178h] BYREF
  float v57; // [esp+14h] [ebp-174h]
  float v58; // [esp+18h] [ebp-170h]
  float v59; // [esp+1Ch] [ebp-16Ch]
  float v60; // [esp+20h] [ebp-168h]
  float v61; // [esp+24h] [ebp-164h]
  float v62; // [esp+28h] [ebp-160h]
  int v63; // [esp+2Ch] [ebp-15Ch]
  float v64; // [esp+30h] [ebp-158h]
  char *file_bytes; // [esp+34h] [ebp-154h]
  int v66; // [esp+38h] [ebp-150h]
  int v67; // [esp+3Ch] [ebp-14Ch]
  float v68; // [esp+40h] [ebp-148h]
  char *v69; // [esp+44h] [ebp-144h]
  TransformMatrix transform; // [esp+48h] [ebp-140h] BYREF
  char v71[128]; // [esp+88h] [ebp-100h] BYREF
  char Buffer[128]; // [esp+108h] [ebp-80h] BYREF

  v2 = 0;
  cache_music_file(aMusicIntrotext, 0, (char *)g_blank_text);
  landscape_script_by_name = load_landscape_script_by_name(
                               (char *)&g_game_base->subgame.landscape_manager,
                               aSpaceredTxt);
  change_backdrop(&g_game_base->backdrop, &g_game_base->subgame.landscape_manager.scripts[landscape_script_by_name], 0);
  set_border_justify_centre(&g_game_base->border_manager, 0.0);
  unhide_star_field(&g_game_base->star_manager);
  file_bytes = load_file_bytes(file_name, nullptr);
  logo->saved_render_flags = g_runtime_config.render_flags;
  qmemcpy(
    &g_game_base->players[0].transform,
    initialize_matrix_from_values(
      &transform,
      1.0,
      0.0,
      0.0,
      0.0,
      0.0,
      0.63439298,
      0.77301002,
      0.0,
      0.0,
      -0.77301002,
      0.63439298,
      0.0,
      0.0,
      0.0,
      0.0,
      1.0),
    sizeof(g_game_base->players[0].transform));
  g_game_base->players[0].camera.fov_degrees = 100.0;
  logo->progress = 0.0;
  logo->progress_step = 0.0016666667;
  release_mouse_cursor(&g_game_base->players[0].mouse_cursor);
  v5 = file_bytes;
  logo->state = 0;
  v59 = 0.2;
  logo->renderable_count = 0;
  case_insensitive_substring = find_case_insensitive_substring(aTextStart, v5);
  cursor = find_case_insensitive_substring(asc_4A1644, case_insensitive_substring) + 1;
  v7 = find_case_insensitive_substring(aTextEnd, v5);
  v8 = cursor;
  v69 = v7;
  if ( cursor < v7 )
  {
    LODWORD(v60) = &logo->image_donors[0].renderable.bod.object;
    do
    {
      v9 = *v8;
      v10 = 0.0;
      v11 = *v8 == 42;
      v61 = 0.0;
      v12 = v8;
      if ( v11 )
      {
        v13 = v8 + 1;
        v14 = v71;
        cursor = v13;
        for ( i = *v13; *v13 != 46; i = *v13 )
        {
          *v14++ = i;
          cursor = ++v13;
        }
        *v14 = 46;
        v16 = v14 + 1;
        *v16++ = 116;
        *v16++ = 103;
        *v16 = 97;
        v16[1] = 0;
        cursor = v13 + 1;
        v58 = parse_next_float32(&cursor);
        v57 = parse_next_float32(&cursor);
        sprintf(Buffer, "Intro/%s", v71);
        renderable_count = logo->renderable_count;
        v18 = &logo->letters[renderable_count];
        if ( (logo->letters[renderable_count].renderable.bod.bod.list_flags & 0x200) != 0 )
        {
          report_errorf(aListAdd);
        }
        else
        {
          p_first = &g_game_base->active_bod_list.first;
          first = g_game_base->active_bod_list.first;
          if ( first )
          {
            first->bod.list_prev = (FrameBodBase *)v18;
            (*p_first)->bod.list_prev->bod.list_next = *p_first;
            list_prev = (*p_first)->bod.list_prev;
            *p_first = list_prev;
            list_prev->bod.list_prev = nullptr;
          }
          else
          {
            *p_first = (FrameBodBase *)v18;
            v18->renderable.bod.bod.list_prev = nullptr;
            (*p_first)->bod.list_next = nullptr;
          }
          v18->renderable.bod.bod.list_flags |= 0x200u;
        }
        v22 = v60;
        set_bod_object(&logo->letters[logo->renderable_count].renderable.bod, *(Object **)LODWORD(v60));
        logo->letters[logo->renderable_count].renderable.bod.object->facequads->texture_ref = get_or_create_texture_ref(
                                                                                                &g_texture_refs,
                                                                                                Buffer,
                                                                                                0,
                                                                                                0);
        set_matrix_identity(&logo->letters[logo->renderable_count].renderable.transform);
        v23 = logo->renderable_count;
        v66 = 0;
        v67 = -1065353216;
        v68 = 0.0;
        p_position = &logo->letters[v23].renderable.transform.position;
        v25 = v57 * 0.5;
        p_position->x = 0.0;
        v26 = v68;
        p_position->y = -4.0;
        v60 = v25;
        v27 = v59;
        p_position->z = v26;
        logo->letters[logo->renderable_count].renderable.transform.position.z = v27
                                                                              - v60
                                                                              + logo->letters[logo->renderable_count].renderable.transform.position.z;
        set_color_white(&logo->letters[logo->renderable_count].renderable.bod.color);
        v28 = v58 * 0.5;
        logo->letters[logo->renderable_count].renderable.bod.color.a = 0.99900001;
        logo->letters[logo->renderable_count].glyph = -1;
        logo->letters[logo->renderable_count].renderable.bod.object->vertices->x = v28;
        v29 = v58 * -0.5;
        logo->letters[logo->renderable_count].renderable.bod.object->vertices->z = v60;
        logo->letters[logo->renderable_count].renderable.bod.object->vertices[1].x = v29;
        logo->letters[logo->renderable_count].renderable.bod.object->vertices[1].z = v60;
        logo->letters[logo->renderable_count].renderable.bod.object->vertices[2].x = v29;
        object = logo->letters[logo->renderable_count].renderable.bod.object;
        v58 = v57 * -0.5;
        object->vertices[2].z = v58;
        logo->letters[logo->renderable_count].renderable.bod.object->vertices[3].x = v28;
        logo->letters[logo->renderable_count].renderable.bod.object->vertices[3].z = v58;
        p_velocity = &logo->letters[logo->renderable_count].velocity;
        p_velocity->z = 0.0;
        p_velocity->y = 0.0;
        p_velocity->x = 0.0;
        (*(void (__thiscall **)(LogoLetter *))logo->letters[logo->renderable_count].renderable.bod.bod.vtable)(&logo->letters[logo->renderable_count]);
        v8 = cursor;
        v32 = v59 - v57;
        LODWORD(v60) = LODWORD(v22) + 144;
        ++logo->renderable_count;
        v33 = *v8;
        v59 = v32;
        if ( v33 )
        {
          do
          {
            if ( v33 == 13 )
              break;
            cursor = ++v8;
            v33 = *v8;
          }
          while ( *v8 );
        }
      }
      else if ( v9 )
      {
        do
        {
          if ( v9 == 13 )
            break;
          v34 = v61 + g_font3d_scales[font_slot_index_for_char(v9)];
          ++LODWORD(v10);
          v8 = cursor + 1;
          cursor = v8;
          v9 = *v8;
          v61 = v34;
        }
        while ( v9 );
        if ( SLODWORD(v10) > 0 )
        {
          v62 = 0.0;
          v63 = -1065353216;
          v64 = 0.0;
          v58 = v10;
          v57 = v61 * 0.5 * 0.80000001;
          do
          {
            v35 = logo->renderable_count;
            list_flags = logo->letters[v35].renderable.bod.bod.list_flags;
            v37 = &logo->letters[v35];
            if ( (list_flags & 0x200) != 0 )
            {
              report_errorf(aListAdd);
            }
            else
            {
              v38 = &g_game_base->active_bod_list.first;
              v39 = g_game_base->active_bod_list.first;
              if ( v39 )
              {
                v39->bod.list_prev = (FrameBodBase *)v37;
                (*v38)->bod.list_prev->bod.list_next = *v38;
                v40 = (*v38)->bod.list_prev;
                *v38 = v40;
                v40->bod.list_prev = nullptr;
              }
              else
              {
                *v38 = (FrameBodBase *)v37;
                v37->renderable.bod.bod.list_prev = nullptr;
                (*v38)->bod.list_next = nullptr;
              }
              v41 = v37->renderable.bod.bod.list_flags;
              BYTE1(v41) |= 2u;
              v37->renderable.bod.bod.list_flags = v41;
            }
            v42 = font_slot_index_for_char(*v12);
            set_bod_object(&logo->letters[logo->renderable_count].renderable.bod, g_font3d_bods[v42].object);
            set_matrix_identity(&logo->letters[logo->renderable_count].renderable.transform);
            v43 = v57;
            v44 = &logo->letters[logo->renderable_count].renderable.transform.position;
            v45 = v63;
            v44->x = v62;
            v46 = v64;
            LODWORD(v44->y) = v45;
            v44->z = v46;
            logo->letters[logo->renderable_count].renderable.transform.position.x = v43
                                                                                  + logo->letters[logo->renderable_count].renderable.transform.position.x;
            logo->letters[logo->renderable_count].renderable.transform.position.z = v59
                                                                                  + logo->letters[logo->renderable_count].renderable.transform.position.z;
            set_color_white(&logo->letters[logo->renderable_count].renderable.bod.color);
            logo->letters[logo->renderable_count].renderable.bod.color.a = 0.99900001;
            v47 = &logo->letters[logo->renderable_count].velocity;
            v47->z = 0.0;
            v47->y = 0.0;
            v47->x = 0.0;
            logo->letters[logo->renderable_count].glyph = *v12;
            (*(void (__thiscall **)(LogoLetter *))logo->letters[logo->renderable_count].renderable.bod.bod.vtable)(&logo->letters[logo->renderable_count]);
            v48 = font_slot_index_for_char(*v12++);
            v49 = v57 - g_font3d_scales[v48] * 0.80000001;
            ++logo->renderable_count;
            v57 = v49;
            --LODWORD(v58);
          }
          while ( v58 != 0.0 );
          v8 = cursor;
        }
      }
      if ( *v8 == 13 )
      {
        v8 += 2;
        cursor = v8;
        v59 = v59 - 1.0;
      }
    }
    while ( v8 < v69 );
    v5 = file_bytes;
  }
  cursor = find_case_insensitive_substring(aDuration, v5);
  cursor = find_case_insensitive_substring(asc_4A1644, cursor);
  v50 = parse_next_float32(&cursor);
  logo->duration_seconds = v50;
  v51 = logo->renderable_count;
  v62 = 0.0;
  v63 = 0;
  v64 = 1.0 / (v50 * 60.0) * (3.0 - v59);
  if ( v51 > 0 )
  {
    v52 = v63;
    v53 = &logo->letters[0].velocity;
    do
    {
      p_x = &v53->x;
      ++v2;
      v53 += 12;
      *p_x = v62;
      v55 = v64;
      *((_DWORD *)p_x + 1) = v52;
      p_x[2] = v55;
    }
    while ( v2 < logo->renderable_count );
  }
  free_tracked_memory((int)v5);
}
