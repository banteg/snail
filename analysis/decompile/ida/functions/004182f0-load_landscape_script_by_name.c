/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_landscape_script_by_name @ 0x4182f0 */
/* selector: load_landscape_script_by_name */

// Loads or reuses one `Backgrounds/<name>` landscape script, parses its `ID`, `Fog`, `Picture`, `Landscape`, and `Distort` fields, registers the referenced backdrop textures, and returns the cached landscape index.
int32_t __thiscall load_landscape_script_by_name(LandscapeManager *manager, char *script_name)
{
  char *v2; // ebx
  int32_t v4; // edi
  char *name; // ebp
  char *file_bytes; // edi
  char *case_insensitive_substring; // eax
  char *v9; // eax
  char *v10; // eax
  char *v11; // eax
  char *v12; // edx
  char i; // cl
  int32_t script_count; // eax
  bool v15; // zf
  int32_t v16; // eax
  char *v17; // eax
  char v18; // cl
  char *v19; // eax
  char *v20; // eax
  char *v21; // eax
  char v22; // dl
  char *v23; // ecx
  GameRoot *v24; // eax
  _BYTE *v25; // ecx
  char *v26; // eax
  char *cursor; // [esp+10h] [ebp-708h] BYREF
  int v28; // [esp+14h] [ebp-704h]
  char v29[128]; // [esp+18h] [ebp-700h] BYREF
  char texture_path[128]; // [esp+98h] [ebp-680h] BYREF
  char Buffer[512]; // [esp+118h] [ebp-600h] BYREF
  char v32[512]; // [esp+318h] [ebp-400h] BYREF
  char mesh_name[512]; // [esp+518h] [ebp-200h] BYREF

  v2 = script_name;
  sprintf(Buffer, "Backgrounds/%s", script_name);
  v4 = 0;
  if ( manager->script_count <= 0 )
  {
LABEL_5:
    file_bytes = (char *)load_file_bytes(Buffer, nullptr);
    if ( file_bytes != nullptr )
    {
      rstrcpy_checked_ascii(manager->scripts[manager->script_count].name, script_name);
      case_insensitive_substring = find_case_insensitive_substring(aId, file_bytes);
      cursor = case_insensitive_substring;
      if ( case_insensitive_substring != nullptr )
      {
        cursor = find_case_insensitive_substring(asc_4A1644, case_insensitive_substring);
        manager->scripts[manager->script_count].id = parse_next_signed_int(&cursor);
      }
      else
      {
        report_errorf("Landscape. Cannot find ID: %s", Buffer);
        manager->scripts[manager->script_count].id = 0;
      }
      v9 = find_case_insensitive_substring(aFog, file_bytes);
      cursor = v9;
      if ( v9 != nullptr )
      {
        cursor = find_case_insensitive_substring(asc_4A1644, v9);
        v28 = parse_next_signed_int(&cursor);
        manager->scripts[manager->script_count].fog_color.r = (double)v28 * 0.0039215689;
        v28 = parse_next_signed_int(&cursor);
        manager->scripts[manager->script_count].fog_color.g = (double)v28 * 0.0039215689;
        v28 = parse_next_signed_int(&cursor);
        manager->scripts[manager->script_count].fog_color.b = (double)v28 * 0.0039215689;
      }
      else
      {
        report_errorf("Landscape. Cannot find Fog: %s", Buffer);
        set_color_black(&manager->scripts[manager->script_count].fog_color);
      }
      v10 = find_case_insensitive_substring(aPicture, file_bytes);
      cursor = v10;
      if ( v10 != nullptr )
      {
        v11 = find_case_insensitive_substring(asc_4A1644, v10) + 1;
        cursor = v11;
        v12 = v32;
        for ( i = *v11; *v11 != 46; i = *v11 )
        {
          *v12++ = i;
          cursor = ++v11;
        }
        script_count = manager->script_count;
        *v12 = 0;
        sprintf(manager->scripts[script_count].backdrop_texture_path, "Backgrounds/%s.tga", v32);
        manager->scripts[manager->script_count].backdrop_texture_id = 2 * manager->script_count + 6;
        v15 = archive_or_file_exists(manager->scripts[manager->script_count].backdrop_texture_path, 0) == 0;
        v16 = manager->script_count;
        if ( v15 )
        {
          manager->scripts[v16].split_backdrop_texture_pair = 1;
          rstrcpy_checked_ascii(texture_path, manager->scripts[manager->script_count].backdrop_texture_path);
          rstrcpy_checked_ascii(v29, manager->scripts[manager->script_count].backdrop_texture_path);
          v17 = texture_path;
          if ( texture_path[0] != 46 )
          {
            do
              v18 = *++v17;
            while ( v18 != 46 );
          }
          v15 = v29[0] == 46;
          *v17 = 95;
          v17[1] = 65;
          v17[2] = 46;
          v17[3] = 116;
          v17[4] = 103;
          v17[5] = 97;
          v17[6] = 0;
          v19 = v29;
          if ( !v15 )
          {
            do
              ++v19;
            while ( *v19 != 46 );
          }
          *v19 = 95;
          v19[1] = 66;
          v19[2] = 46;
          v19[3] = 116;
          v19[4] = 103;
          v19[5] = 97;
          v19[6] = 0;
          register_sprite_texture(
            &g_sprite_manager,
            texture_path,
            manager->scripts[manager->script_count].backdrop_texture_id,
            1024);
          register_sprite_texture(
            &g_sprite_manager,
            v29,
            manager->scripts[manager->script_count].backdrop_texture_id + 1,
            1024);
          v2 = script_name;
        }
        else
        {
          register_sprite_texture(
            &g_sprite_manager,
            manager->scripts[v16].backdrop_texture_path,
            manager->scripts[v16].backdrop_texture_id,
            1024);
          manager->scripts[manager->script_count].split_backdrop_texture_pair = 0;
        }
        debug_report_stub("Loading backdrop texture %s", manager->scripts[manager->script_count].backdrop_texture_path);
      }
      else
      {
        report_errorf("Landscape. Cannot find Picture: in %s", Buffer);
      }
      v20 = find_case_insensitive_substring(aLandscape, file_bytes);
      cursor = v20;
      if ( v20 != nullptr )
      {
        v21 = find_case_insensitive_substring(asc_4A1644, v20) + 1;
        cursor = v21;
        v22 = *v21;
        if ( *v21 <= 32 )
        {
          manager->scripts[manager->script_count].object_index = -1;
        }
        else
        {
          v23 = mesh_name;
          if ( v22 != 46 )
          {
            do
            {
              *v23++ = v22;
              cursor = ++v21;
              v22 = *v21;
            }
            while ( *v21 != 46 );
          }
          v24 = g_game_base;
          *v23 = 46;
          v25 = v23 + 1;
          *v25 = 120;
          v25[1] = 0;
          manager->scripts[manager->script_count].object_index = load_or_reuse_cached_x_mesh(
                                                                   &v24->directx_loader,
                                                                   mesh_name);
        }
      }
      else
      {
        report_errorf("Landscape. Cannot find Landscape: in %s", Buffer);
      }
      v26 = find_case_insensitive_substring(aDistort, file_bytes);
      cursor = v26;
      if ( v26 != nullptr )
      {
        cursor = find_case_insensitive_substring(asc_4A1644, v26) + 1;
        manager->scripts[manager->script_count].distort = parse_next_float32(&cursor);
      }
      else
      {
        report_errorf("Landscape. Cannot find Distort: in %s", Buffer);
      }
      ++manager->script_count;
      debug_report_stub("Landscape: %s imported\n", v2);
      return manager->script_count - 1;
    }
    else
    {
      report_errorf("Landscape.Cannot load %s", Buffer);
      return 0;
    }
  }
  else
  {
    name = manager->scripts[0].name;
    while ( !strings_equal_case_insensitive_path(name, script_name) )
    {
      ++v4;
      name += 292;
      if ( v4 >= manager->script_count )
        goto LABEL_5;
    }
    return v4;
  }
}
