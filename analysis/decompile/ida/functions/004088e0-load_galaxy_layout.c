/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_galaxy_layout @ 0x4088e0 */
/* selector: load_galaxy_layout */

// Recovered void Galaxy bootstrap: loads `Galaxy/_Galaxy.txt`, rescales the authored point tables, populates the embedded route/star bank, and binds its borrowed SubgameRuntime backlink. Android and iOS retain this parser inside `cRGalaxy::Open(int)`.
void __thiscall load_galaxy_layout(Galaxy *galaxy)
{
  union GalaxyPoint::$05C98FCC6CBF70FB5A4B689A398B23F2 *p_y_bits; // eax
  double v3; // st7
  union GalaxyPoint::$05C98FCC6CBF70FB5A4B689A398B23F2 *v4; // eax
  double v5; // st7
  int v6; // ebx
  void *archive_data_base; // eax
  union GalaxyPoint::$05C98FCC6CBF70FB5A4B689A398B23F2 *v8; // ebp
  tColour *p_color; // edi
  char *case_insensitive_substring; // eax
  char *v11; // eax
  char *v12; // eax
  char *p_a; // edx
  char i; // cl
  int v15; // ebp
  int v16; // [esp+0h] [ebp-E4h]
  char *cursor; // [esp+10h] [ebp-D4h] BYREF
  int32_t v18; // [esp+14h] [ebp-D0h]
  int v19; // [esp+18h] [ebp-CCh]
  union GalaxyPoint::$05C98FCC6CBF70FB5A4B689A398B23F2 *v20; // [esp+1Ch] [ebp-C8h]
  char *searched; // [esp+20h] [ebp-C4h]
  char Buffer[64]; // [esp+24h] [ebp-C0h] BYREF
  char ArgList[128]; // [esp+64h] [ebp-80h] BYREF

  p_y_bits = (union GalaxyPoint::$05C98FCC6CBF70FB5A4B689A398B23F2 *)&g_galaxy_route_points[0].y_bits;
  galaxy->active = 0;
  galaxy->record_count = 1;
  do
  {
    v3 = p_y_bits[-1].y * 0.80000001;
    p_y_bits += 2;
    p_y_bits[-3].y = v3;
    p_y_bits[-2].y = (p_y_bits[-2].y * 0.80000001 - 240.0) * 0.93000001 + 250.0;
  }
  while ( (int)p_y_bits < (int)&aMissingInGalax[4] );
  v4 = (union GalaxyPoint::$05C98FCC6CBF70FB5A4B689A398B23F2 *)&g_galaxy_group_points[0].y_bits;
  do
  {
    v5 = v4[-1].y * 0.80000001;
    v4 += 2;
    v4[-3].y = v5;
    v4[-2].y = (v4[-2].y * 0.80000001 - 240.0) * 0.93000001 + 250.0;
  }
  while ( (int)v4 < (int)g_galaxy_group_point_y_end );
  v6 = 0;
  galaxy->level_progress_base = &g_game_base->subgame;
  archive_data_base = get_archive_data_base();
  v8 = (union GalaxyPoint::$05C98FCC6CBF70FB5A4B689A398B23F2 *)&g_galaxy_group_points[0].y_bits;
  searched = (char *)load_file_bytes_from_archive_or_fs(aGalaxyGalaxyTx, archive_data_base, nullptr);
  v18 = 0;
  v19 = 0;
  v20 = (union GalaxyPoint::$05C98FCC6CBF70FB5A4B689A398B23F2 *)&g_galaxy_group_points[0].y_bits;
  p_color = &galaxy->route_names[0].color;
  while ( 1 )
  {
    sprintf(Buffer, "Galaxy%i:", v18);
    case_insensitive_substring = find_case_insensitive_substring(Buffer, searched);
    cursor = case_insensitive_substring;
    if ( case_insensitive_substring == nullptr )
    {
      report_errorf("Cannot find Galaxy %i in _Galaxy.txt", v16);
      return;
    }
    v11 = find_case_insensitive_substring(asc_4A1644, case_insensitive_substring) + 1;
    cursor = v11;
    if ( *v11 != 34 )
      break;
    v12 = v11 + 1;
    p_a = (char *)&p_color[-9].a;
    cursor = v12;
    for ( i = *v12; *v12 != 34; i = *v12 )
    {
      *p_a++ = i;
      cursor = ++v12;
    }
    *p_a = 0;
    cursor = find_case_insensitive_substring(aStarnumber, v12);
    cursor = find_case_insensitive_substring(asc_4A2094, cursor) + 1;
    LODWORD(p_color[-1].a) = parse_next_signed_int(&cursor);
    p_color->r = 1.0;
    p_color->g = 1.0;
    p_color->b = 1.0;
    p_color->a = 0.80000001;
    p_color[1].r = v8[-1].y;
    p_color[1].g = v8->y;
    p_color[1].b = 0.0;
    if ( SLODWORD(p_color[-1].a) > 0 )
    {
      v15 = 0;
      do
      {
        galaxy->route_slots[galaxy->record_count].record.route_name_index = v18;
        LODWORD(galaxy->route_slots[galaxy->record_count].record.map_x) = g_galaxy_route_points[v19
                                                                                              + 1
                                                                                              + v15
                                                                                              / SLODWORD(p_color[-1].a)].x_bits;
        galaxy->route_slots[galaxy->record_count].record.map_y = *((float *)&g_galaxy_route_points[1].y_bits
                                                                 + 2 * v19
                                                                 + 2 * (v15 / SLODWORD(p_color[-1].a)));
        galaxy->route_slots[galaxy->record_count].record.map_z = 0.0;
        sprintf(ArgList, "LEVEL %i MISSING", galaxy->record_count);
        rstrcpy_checked_ascii(galaxy->route_slots[galaxy->record_count].record.detail_text, ArgList);
        rstrcpy_checked_ascii(galaxy->route_slots[galaxy->record_count].record.description_text, ArgList);
        ++v6;
        ++galaxy->record_count;
        v15 += 10;
      }
      while ( v6 < SLODWORD(p_color[-1].a) );
      v8 = v20;
      v6 = 0;
    }
    v8 += 2;
    p_color += 10;
    ++v18;
    v20 = v8;
    v19 += 10;
    if ( (int)v8 >= (int)g_galaxy_group_point_y_end )
    {
      galaxy->route_slots[0].record.route_name_index = 0;
      *(GalaxyPoint *)&galaxy->route_slots[0].record.map_x = g_galaxy_route_points[0];
      galaxy->route_slots[0].record.map_z = 0.0;
      galaxy->route_slots[0].record.detail_text[0] = 0;
      galaxy->route_slots[0].record.description_text[0] = 0;
      return;
    }
  }
  report_errorf(aMissingInGalax);
}
