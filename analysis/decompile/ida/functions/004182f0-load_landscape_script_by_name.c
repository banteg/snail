/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_landscape_script_by_name @ 0x4182f0 */
/* selector: load_landscape_script_by_name */

// Loads or reuses one `Backgrounds/<name>` landscape script, parses its `ID`, `Fog`, `Picture`, `Landscape`, and `Distort` fields, registers the referenced backdrop textures, and returns the cached landscape index.
int __thiscall load_landscape_script_by_name(char *this, char *ArgList)
{
  int v3; // edi
  char *v4; // ebp
  char *file_bytes; // edi
  char *case_insensitive_substring; // eax
  char *v8; // eax
  char *v9; // eax
  char *v10; // eax
  char *v11; // edx
  char i; // cl
  int v13; // eax
  bool v14; // zf
  int v15; // eax
  char *v16; // eax
  char v17; // cl
  char *v18; // eax
  char *v19; // eax
  char *v20; // eax
  char v21; // dl
  char *v22; // ecx
  char *v23; // eax
  _BYTE *v24; // ecx
  char *v25; // eax
  char *v26; // [esp+10h] [ebp-708h] BYREF
  int v27; // [esp+14h] [ebp-704h]
  char v28[128]; // [esp+18h] [ebp-700h] BYREF
  char v29[128]; // [esp+98h] [ebp-680h] BYREF
  char Buffer[512]; // [esp+118h] [ebp-600h] BYREF
  char v31[512]; // [esp+318h] [ebp-400h] BYREF
  char v32[512]; // [esp+518h] [ebp-200h] BYREF

  sprintf(Buffer, "Backgrounds/%s", ArgList);
  v3 = 0;
  if ( *((int *)this + 360) <= 0 )
  {
LABEL_5:
    file_bytes = load_file_bytes(Buffer, nullptr);
    if ( file_bytes )
    {
      sub_44E5B0(this + 292 * *((_DWORD *)this + 360) + 1448, ArgList);
      case_insensitive_substring = find_case_insensitive_substring(aId, file_bytes);
      v26 = case_insensitive_substring;
      if ( case_insensitive_substring )
      {
        v26 = find_case_insensitive_substring(asc_4A1644, case_insensitive_substring);
        *((_DWORD *)this + 73 * *((_DWORD *)this + 360) + 361) = sub_44E710(&v26);
      }
      else
      {
        report_errorf("Landscape. Cannot find ID: %s", Buffer);
        *((_DWORD *)this + 73 * *((_DWORD *)this + 360) + 361) = 0;
      }
      v8 = find_case_insensitive_substring(aFog, file_bytes);
      v26 = v8;
      if ( v8 )
      {
        v26 = find_case_insensitive_substring(asc_4A1644, v8);
        v27 = sub_44E710(&v26);
        *((float *)this + 73 * *((_DWORD *)this + 360) + 429) = (double)v27 * 0.0039215689;
        v27 = sub_44E710(&v26);
        *((float *)this + 73 * *((_DWORD *)this + 360) + 430) = (double)v27 * 0.0039215689;
        v27 = sub_44E710(&v26);
        *((float *)this + 73 * *((_DWORD *)this + 360) + 431) = (double)v27 * 0.0039215689;
      }
      else
      {
        report_errorf("Landscape. Cannot find Fog: %s", Buffer);
        set_color_black((_DWORD *)this + 73 * *((_DWORD *)this + 360) + 429);
      }
      v9 = find_case_insensitive_substring(aPicture, file_bytes);
      v26 = v9;
      if ( v9 )
      {
        v10 = find_case_insensitive_substring(asc_4A1644, v9) + 1;
        v26 = v10;
        v11 = v31;
        for ( i = *v10; *v10 != 46; i = *v10 )
        {
          *v11++ = i;
          v26 = ++v10;
        }
        v13 = *((_DWORD *)this + 360);
        *v11 = 0;
        sprintf(this + 292 * v13 + 1581, "Backgrounds/%s.tga", v31);
        *((_DWORD *)this + 73 * *((_DWORD *)this + 360) + 394) = 2 * *((_DWORD *)this + 360) + 6;
        v14 = archive_or_file_exists(this + 292 * *((_DWORD *)this + 360) + 1581, 0) == 0;
        v15 = *((_DWORD *)this + 360);
        if ( v14 )
        {
          *(this + 292 * v15 + 1580) = 1;
          sub_44E5B0(v29, this + 292 * *((_DWORD *)this + 360) + 1581);
          sub_44E5B0(v28, this + 292 * *((_DWORD *)this + 360) + 1581);
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
          register_sprite_texture(v29, *((_DWORD *)this + 73 * *((_DWORD *)this + 360) + 394), 1024);
          register_sprite_texture(v28, *((_DWORD *)this + 73 * *((_DWORD *)this + 360) + 394) + 1, 1024);
        }
        else
        {
          register_sprite_texture(this + 292 * v15 + 1581, *((_DWORD *)this + 73 * v15 + 394), 1024);
          *(this + 292 * *((_DWORD *)this + 360) + 1580) = 0;
        }
        sub_449C00();
      }
      else
      {
        report_errorf("Landscape. Cannot find Picture: in %s", Buffer);
      }
      v19 = find_case_insensitive_substring(aLandscape, file_bytes);
      v26 = v19;
      if ( v19 )
      {
        v20 = find_case_insensitive_substring(asc_4A1644, v19) + 1;
        v26 = v20;
        v21 = *v20;
        if ( *v20 <= 32 )
        {
          *((_DWORD *)this + 73 * *((_DWORD *)this + 360) + 428) = -1;
        }
        else
        {
          v22 = v32;
          if ( v21 != 46 )
          {
            do
            {
              *v22++ = v21;
              v26 = ++v20;
              v21 = *v20;
            }
            while ( *v20 != 46 );
          }
          v23 = (char *)MEMORY[0x4DF904];
          *v22 = 46;
          v24 = v22 + 1;
          *v24 = 120;
          v24[1] = 0;
          *((_DWORD *)this + 73 * *((_DWORD *)this + 360) + 428) = load_or_reuse_cached_x_mesh(v23 + 298496, v32);
        }
      }
      else
      {
        report_errorf("Landscape. Cannot find Landscape: in %s", Buffer);
      }
      v25 = find_case_insensitive_substring(aDistort, file_bytes);
      v26 = v25;
      if ( v25 )
      {
        v26 = find_case_insensitive_substring(asc_4A1644, v25) + 1;
        *((float *)this + 73 * *((_DWORD *)this + 360) + 433) = parse_next_float32(&v26);
      }
      else
      {
        report_errorf("Landscape. Cannot find Distort: in %s", Buffer);
      }
      ++*((_DWORD *)this + 360);
      sub_449C00();
      return *((_DWORD *)this + 360) - 1;
    }
    else
    {
      report_errorf("Landscape.Cannot load %s", Buffer);
      return 0;
    }
  }
  else
  {
    v4 = this + 1448;
    while ( !sub_44E6C0(v4, ArgList) )
    {
      ++v3;
      v4 += 292;
      if ( v3 >= *((_DWORD *)this + 360) )
        goto LABEL_5;
    }
    return v3;
  }
}

