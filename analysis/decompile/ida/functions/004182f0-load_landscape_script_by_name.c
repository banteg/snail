/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_landscape_script_by_name @ 0x4182f0 */
/* selector: load_landscape_script_by_name */

// Loads or reuses one `Backgrounds/<name>` landscape script, parses its `ID`, `Fog`, `Picture`, `Landscape`, and `Distort` fields, registers the referenced backdrop textures, and returns the cached landscape index.
int32_t __thiscall load_landscape_script_by_name(LandscapeManager *manager, char *script_name)
{
  int32_t v3; // edi
  char *name; // ebp
  char *file_bytes; // edi
  char *case_insensitive_substring; // eax
  char *v8; // eax
  char *v9; // eax
  char *v10; // eax
  char *v11; // edx
  char i; // cl
  int32_t script_count; // eax
  bool v14; // zf
  int32_t v15; // eax
  char *v16; // eax
  char v17; // cl
  char *v18; // eax
  char *v19; // eax
  char *v20; // eax
  char v21; // dl
  char *v22; // ecx
  GameRoot *v23; // eax
  _BYTE *v24; // ecx
  char *v25; // eax
  char *cursor; // [esp+10h] [ebp-708h] BYREF
  int v27; // [esp+14h] [ebp-704h]
  char v28[128]; // [esp+18h] [ebp-700h] BYREF
  char v29[128]; // [esp+98h] [ebp-680h] BYREF
  char Buffer[512]; // [esp+118h] [ebp-600h] BYREF
  char v31[512]; // [esp+318h] [ebp-400h] BYREF
  char mesh_name[512]; // [esp+518h] [ebp-200h] BYREF

  sprintf(Buffer, "Backgrounds/%s", script_name);
  v3 = 0;
  if ( manager->script_count <= 0 )
  {
LABEL_5:
    file_bytes = (char *)load_file_bytes(Buffer, nullptr);
    if ( file_bytes )
    {
      rstrcpy_checked_ascii(manager->scripts[manager->script_count].name, script_name);
      case_insensitive_substring = find_case_insensitive_substring(aId, file_bytes);
      cursor = case_insensitive_substring;
      if ( case_insensitive_substring )
      {
        cursor = find_case_insensitive_substring(asc_4A1644, case_insensitive_substring);
        manager->scripts[manager->script_count].id = parse_next_signed_int(&cursor);
      }
      else
      {
        report_errorf("Landscape. Cannot find ID: %s", Buffer);
        manager->scripts[manager->script_count].id = 0;
      }
      v8 = find_case_insensitive_substring(aFog, file_bytes);
      cursor = v8;
      if ( v8 )
      {
        cursor = find_case_insensitive_substring(asc_4A1644, v8);
        v27 = parse_next_signed_int(&cursor);
        manager->scripts[manager->script_count].fog_color.r = (double)v27 * 0.0039215689;
        v27 = parse_next_signed_int(&cursor);
        manager->scripts[manager->script_count].fog_color.g = (double)v27 * 0.0039215689;
        v27 = parse_next_signed_int(&cursor);
        manager->scripts[manager->script_count].fog_color.b = (double)v27 * 0.0039215689;
      }
      else
      {
        report_errorf("Landscape. Cannot find Fog: %s", Buffer);
        set_color_black(&manager->scripts[manager->script_count].fog_color);
      }
      v9 = find_case_insensitive_substring(aPicture, file_bytes);
      cursor = v9;
      if ( v9 )
      {
        v10 = find_case_insensitive_substring(asc_4A1644, v9) + 1;
        cursor = v10;
        v11 = v31;
        for ( i = *v10; *v10 != 46; i = *v10 )
        {
          *v11++ = i;
          cursor = ++v10;
        }
        script_count = manager->script_count;
        *v11 = 0;
        sprintf(manager->scripts[script_count].backdrop_texture_path, "Backgrounds/%s.tga", v31);
        manager->scripts[manager->script_count].backdrop_texture_id = 2 * manager->script_count + 6;
        v14 = archive_or_file_exists(manager->scripts[manager->script_count].backdrop_texture_path, 0) == 0;
        v15 = manager->script_count;
        if ( v14 )
        {
          manager->scripts[v15].split_backdrop_texture_pair = 1;
          rstrcpy_checked_ascii(v29, manager->scripts[manager->script_count].backdrop_texture_path);
          rstrcpy_checked_ascii(v28, manager->scripts[manager->script_count].backdrop_texture_path);
          v16 = v29;
          if ( v29[0] != 46 )
          {
            do
              v17 = *++v16;
            while ( v17 != 46 );
          }
          v14 = v28[0] == 46;
          *v16 = 95;
          v16[1] = 65;
          v16[2] = 46;
          v16[3] = 116;
          v16[4] = 103;
          v16[5] = 97;
          v16[6] = 0;
          v18 = v28;
          if ( !v14 )
          {
            do
              ++v18;
            while ( *v18 != 46 );
          }
          *v18 = 95;
          v18[1] = 66;
          v18[2] = 46;
          v18[3] = 116;
          v18[4] = 103;
          v18[5] = 97;
          v18[6] = 0;
          register_sprite_texture(v29, manager->scripts[manager->script_count].backdrop_texture_id, 1024);
          register_sprite_texture(v28, manager->scripts[manager->script_count].backdrop_texture_id + 1, 1024);
        }
        else
        {
          register_sprite_texture(
            manager->scripts[v15].backdrop_texture_path,
            manager->scripts[v15].backdrop_texture_id,
            1024);
          manager->scripts[manager->script_count].split_backdrop_texture_pair = 0;
        }
        debug_report_stub();
      }
      else
      {
        report_errorf("Landscape. Cannot find Picture: in %s", Buffer);
      }
      v19 = find_case_insensitive_substring(aLandscape, file_bytes);
      cursor = v19;
      if ( v19 )
      {
        v20 = find_case_insensitive_substring(asc_4A1644, v19) + 1;
        cursor = v20;
        v21 = *v20;
        if ( *v20 <= 32 )
        {
          manager->scripts[manager->script_count].object_index = -1;
        }
        else
        {
          v22 = mesh_name;
          if ( v21 != 46 )
          {
            do
            {
              *v22++ = v21;
              cursor = ++v20;
              v21 = *v20;
            }
            while ( *v20 != 46 );
          }
          v23 = g_game_base;
          *v22 = 46;
          v24 = v22 + 1;
          *v24 = 120;
          v24[1] = 0;
          manager->scripts[manager->script_count].object_index = load_or_reuse_cached_x_mesh(
                                                                   &v23->directx_loader,
                                                                   mesh_name);
        }
      }
      else
      {
        report_errorf("Landscape. Cannot find Landscape: in %s", Buffer);
      }
      v25 = find_case_insensitive_substring(aDistort, file_bytes);
      cursor = v25;
      if ( v25 )
      {
        cursor = find_case_insensitive_substring(asc_4A1644, v25) + 1;
        manager->scripts[manager->script_count].distort = parse_next_float32(&cursor);
      }
      else
      {
        report_errorf("Landscape. Cannot find Distort: in %s", Buffer);
      }
      ++manager->script_count;
      debug_report_stub();
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
      ++v3;
      name += 292;
      if ( v3 >= manager->script_count )
        goto LABEL_5;
    }
    return v3;
  }
}
