/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: register_font_texture_sheet @ 0x449f50 */
/* selector: register_font_texture_sheet */

// Loads one FONT-MENU-HOVER atlas, scans row-0 white delimiters into resettable glyph runs and the column-0 height marker, registers single- or split-page texture refs with their source-retention policy, and stores per-font UV, page, and scale metadata.
int32_t __cdecl register_font_texture_sheet(
        char *texture_path,
        int32_t font_kind,
        float width_scale,
        float height_scale)
{
  int v4; // ebx
  _BYTE *file_bytes; // esi
  char v6; // cl
  int i; // eax
  int v8; // eax
  int v9; // edi
  int v10; // ebp
  int v11; // eax
  int32_t v12; // edx
  float *v13; // eax
  int v14; // ecx
  int v15; // edi
  int v16; // eax
  TextureRef *texture_ref; // eax
  TextureRef *v18; // eax
  int flags; // ecx
  int32_t v20; // eax
  int v22; // [esp+10h] [ebp-210h]
  int v23; // [esp+14h] [ebp-20Ch]
  float v24; // [esp+14h] [ebp-20Ch]
  float v25; // [esp+18h] [ebp-208h]
  int32_t v26; // [esp+1Ch] [ebp-204h]
  char texture_patha[256]; // [esp+20h] [ebp-200h] BYREF
  char v28[256]; // [esp+120h] [ebp-100h] BYREF

  v4 = 0;
  if ( g_registered_font_count == 1 )
    report_errorf(aTooManyFontsRf);
  file_bytes = load_file_bytes(texture_path, nullptr);
  if ( *((_WORD *)file_bytes + 6) == 2048 )
  {
    v6 = *texture_path;
    for ( i = 0; v6 != 46; ++i )
    {
      texture_patha[i] = v6;
      v28[i] = v6;
      v6 = texture_path[i + 1];
    }
    texture_patha[i] = 48;
    v28[i] = 49;
    v8 = i + 1;
    v4 = 960;
    v28[v8] = 46;
    texture_patha[v8++] = 46;
    v28[v8] = 116;
    texture_patha[v8++] = 116;
    v28[v8] = 103;
    texture_patha[v8++] = 103;
    v28[v8] = 97;
    texture_patha[v8++] = 97;
    v28[v8] = 0;
    texture_patha[v8] = 0;
  }
  v9 = 0;
  v10 = -1;
  v26 = 0;
  v23 = -1;
  v22 = 0;
  if ( *((_WORD *)file_bytes + 6) )
  {
    do
    {
      v11 = sample_tga_pixel_rgb((int)file_bytes, v9, 0);
      v12 = g_registered_font_count;
      if ( v11 == 0xFFFFFF )
      {
        v13 = (float *)(4 * (v26 + 522 * g_registered_font_count));
        v14 = v9 - v10;
        v13[1957313] = (float)v23;
        v25 = (double)(v9 - v10) + 0.5;
        v13[1957057] = v25 / (double)*((unsigned __int16 *)file_bytes + 6);
        v10 = 0;
        v24 = (double)v22 + 0.5;
        v13[1957185] = v24 / (double)*((unsigned __int16 *)file_bytes + 6);
        *(int32_t *)((char *)g_font_sheets[0].texture_page + (_DWORD)v13) = 0;
        if ( *((_WORD *)file_bytes + 6) == 2048 )
        {
          if ( v14 <= v4 )
          {
            v13[1957057] = v25 * 0.0009765625;
            v13[1957185] = v24 / (double)(*((_WORD *)file_bytes + 6) >> 1);
            *(int32_t *)((char *)g_font_sheets[0].texture_page + (_DWORD)v13) = 0;
          }
          else
          {
            v13[1957057] = ((double)(v14 - v4) + 0.5) * 0.0009765625;
            v13[1957185] = ((double)(v9 - v4) + 0.5) / (double)(*((_WORD *)file_bytes + 6) >> 1);
            *(int32_t *)((char *)g_font_sheets[0].texture_page + (_DWORD)v13) = 1;
          }
        }
        if ( ++v26 == 128 )
        {
          report_errorf(aTooManyFontLet);
          v12 = g_registered_font_count;
        }
      }
      ++v10;
      ++v9;
      v23 = v10;
      v22 = v9;
    }
    while ( v9 < *((unsigned __int16 *)file_bytes + 6) );
  }
  else
  {
    v12 = g_registered_font_count;
  }
  v15 = 1;
  if ( *((_WORD *)file_bytes + 7) > 1u )
  {
    while ( sample_tga_pixel_rgb((int)file_bytes, 0, v15) != 0xFFFFFF )
    {
      if ( ++v15 >= *((unsigned __int16 *)file_bytes + 7) )
      {
        v12 = g_registered_font_count;
        goto LABEL_23;
      }
    }
    v12 = g_registered_font_count;
    g_font_sheets[g_registered_font_count].line_marker_y = (float)v15;
  }
LABEL_23:
  v16 = 2088 * v12;
  *(float *)(v16 + 7830280) = 3.0 / (double)(*((unsigned __int16 *)file_bytes + 7) - 1);
  *(float *)(v16 + 7830284) = *(float *)(v16 + 7830276) / (double)(*((unsigned __int16 *)file_bytes + 7) - 1);
  g_font_sheets[v16 / 0x828u].slot_count = v26;
  g_font_sheets[v16 / 0x828u].font_kind = font_kind;
  if ( *((_WORD *)file_bytes + 6) == 2048 )
  {
    texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_patha, 0, 0);
    g_font_sheets[g_registered_font_count].texture_ref_a = texture_ref;
    texture_ref->flags |= 0x420u;
    v18 = get_or_create_texture_ref(&g_texture_refs, v28, 0, 0);
    g_font_sheets[g_registered_font_count].texture_ref_b = v18;
    flags = v18->flags | 0x420;
  }
  else
  {
    v18 = get_or_create_texture_ref(&g_texture_refs, texture_path, 0, 0);
    g_font_sheets[g_registered_font_count].texture_ref_a = v18;
    flags = v18->flags;
    BYTE1(flags) = ((unsigned __int16)v18->flags >> 8) | 4;
  }
  v18->flags = flags;
  v20 = g_registered_font_count;
  g_font_sheets[v20].spacing_scale = 1.0;
  g_font_sheets[v20].width_scale = width_scale;
  g_font_sheets[v20].height_scale = height_scale;
  *(float *)(v20 * 2088 + 7830276) = height_scale * *(float *)(v20 * 2088 + 7830276);
  free_tracked_memory((int)file_bytes);
  return g_registered_font_count++;
}
