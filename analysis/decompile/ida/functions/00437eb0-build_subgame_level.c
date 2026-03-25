/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_subgame_level @ 0x437eb0 */
/* selector: build_subgame_level */

// Builds the active subgame course, including level-file load, runtime track rebuild, mode-specific HUD setup, backdrop selection, and the first gameplay object lists. Cross-port Android and iOS symbols match this helper to `cRSubGame::BuildLevel()`.
void __thiscall sub_437EB0(int this, int a2)
{
  int v3; // eax
  double v4; // st7
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // edi
  int v9; // ecx
  int v10; // edx
  double v11; // st7
  int v12; // eax
  int v13; // ecx
  int v14; // eax
  double v15; // st7
  int v16; // edi
  int v17; // eax
  char *v18; // ecx
  int v19; // edx
  int v20; // edx
  int v21; // ecx
  char *v22; // eax
  int v23; // edx
  int v24; // edx
  int v25; // ecx
  char *v26; // eax
  int v27; // edx
  int v28; // edx
  int v29; // ecx
  char *v30; // eax
  int v31; // edx
  int v32; // edx
  int v33; // ecx
  char *v34; // eax
  int v35; // edx
  int v36; // edx
  int v37; // ecx
  int v38; // ecx
  char *v39; // eax
  int v40; // edx
  int v41; // edx
  char *v42; // eax
  int v43; // ecx
  int v44; // ecx
  int v45; // eax
  int v46; // ecx
  int v47; // eax
  float v48; // [esp+0h] [ebp-14h]

  unhide_star_field((int *)MEMORY[0x4DF904] + 81103);
  if ( *(_DWORD *)(this + 64) == 7 )
    hide_gameplay_scores((_DWORD *)this);
  else
    unhide_gameplay_scores((_DWORD **)this);
  switch ( (unsigned int)(__int64)((double)next_math_random_value() * 0.00012207031) )
  {
    case 0u:
      cache_music_file(aMusic1Ogg);
      break;
    case 1u:
      cache_music_file(aMusic2Ogg);
      break;
    case 2u:
    case 4u:
      cache_music_file(aMusic3Ogg);
      break;
    case 3u:
      cache_music_file(aMusic4Ogg);
      break;
    default:
      break;
  }
  *(_DWORD *)(this + 19337164) = 1112014848;
  *(_DWORD *)(this + 19337168) = 1120403456;
  initialize_enemy_manager((#94 *)(this + 19337172));
  initialize_damage_gauge((_DWORD *)(this + 3914536));
  noop_runtime_ai(this + 3914580);
  initialize_wall2_ambient_hazard_pool((_DWORD *)(this + 3500800));
  initialize_salt_hazard_pool((_DWORD *)(this + 3504320));
  reset_voice_manager(unk_751498);
  load_frontend_level_by_mode_and_index((char *)(this + 43124), *(_DWORD *)(this + 64), a2);
  if ( *(_BYTE *)(this + 16721360) || *(_BYTE *)(this + 16721361) )
  {
    *(_DWORD *)(this + 48) = *(_DWORD *)(*(_DWORD *)(this + 16721364) + 72);
    *(_DWORD *)(this + 64) = *(_DWORD *)(*(_DWORD *)(this + 16721364) + 44);
    *(_DWORD *)(this + 44) = *(_DWORD *)(*(_DWORD *)(this + 16721364) + 80);
    *(_DWORD *)(this + 40) = *(_DWORD *)(*(_DWORD *)(this + 16721364) + 76);
    v4 = (double)*(int *)(*(_DWORD *)(this + 16721364) + 80);
    goto LABEL_24;
  }
  v3 = *(_DWORD *)(this + 64);
  switch ( v3 )
  {
    case 3:
      *(float *)(this + 48) = unk_4DF95C;
      break;
    case 0:
    case 4:
    case 7:
      if ( *(_DWORD *)(this + 1769936) == -1082130432 )
        *(float *)(this + 48) = calc_slider_to_rate(0.0);
      else
        *(float *)(this + 48) = *(float *)(this + 1769936) * 0.0099999998 * 0.90000004 + 0.2;
      break;
    case 1:
      v48 = (double)unk_4DF958 * 0.0099999998;
      *(float *)(this + 48) = calc_slider_to_rate(v48);
      v4 = (double)unk_4DF960;
LABEL_24:
      *(float *)(this + 52) = v4 * 0.0099999998;
      break;
    case 2:
      *(float *)(this + 48) = calc_slider_to_rate(unk_4DF95C);
      break;
  }
  if ( *(_BYTE *)(this + 16721360) || *(_BYTE *)(this + 16721361) )
  {
    *(_DWORD *)(this + 19267544) = *(_DWORD *)(*(_DWORD *)(this + 16721364) + 129712);
    *(_DWORD *)(this + 19267548) = *(_DWORD *)(*(_DWORD *)(this + 16721364) + 129716);
  }
  else
  {
    v5 = *(_DWORD *)(this + 64);
    if ( v5 == 2 || v5 == 3 || !v5 || v5 == 4 || v5 == 7 )
    {
      *(float *)(this + 19267544) = *(float *)(this + 1769940) * 0.0099999998;
      *(float *)(this + 19267548) = *(float *)(this + 1769944) * 0.0099999998;
    }
    else if ( v5 == 1 )
    {
      *(float *)(this + 19267544) = (double)unk_4DF960 * 0.0099999998 * 0.80000001;
      *(float *)(this + 19267548) = (double)unk_4DF960 * 0.0099999998 * 0.80000001;
    }
  }
  initialize_track_parcel_slots((_DWORD *)(this + 19260544));
  if ( *((_BYTE *)MEMORY[0x4DF904] + 324320) == 1 )
  {
    hide_border_init(*(_DWORD **)(this + 3521416));
    hide_border_init(*(_DWORD **)(this + 3521420));
  }
  rebuild_track_runtime_from_segments((int *)this, a2);
  if ( *(_DWORD *)(this + 1769956) == 5 )
  {
    switch ( (unsigned int)(__int64)random_float_below(4.0) )
    {
      case 0u:
        v6 = load_landscape_script_by_name((char *)MEMORY[0x4DF904] + 17220120, aSpaceblueswhor);
        break;
      case 1u:
        v6 = load_landscape_script_by_name((char *)MEMORY[0x4DF904] + 17220120, aSpacegreenwarp);
        break;
      case 2u:
        v6 = load_landscape_script_by_name((char *)MEMORY[0x4DF904] + 17220120, aSpacepurpleTxt);
        break;
      case 3u:
        v6 = load_landscape_script_by_name((char *)MEMORY[0x4DF904] + 17220120, aSpaceredTxt);
        break;
      default:
        v6 = a2;
        break;
    }
    activate_landscape_entry((char *)(this + 16743424), v6);
    *((_BYTE *)MEMORY[0x4DF904] + 322660) = random_float_below(1.0) > 0.5;
  }
  else
  {
    activate_landscape_entry((char *)(this + 16743424), *(_DWORD *)(this + 1769948));
  }
  v7 = this + 3510400;
  v8 = this + 3496860;
  if ( (*(_DWORD *)(this + 3510404) & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    *(_DWORD *)(this + 3510408) = v8;
    *(_DWORD *)(this + 3510412) = *(_DWORD *)(this + 3496872);
    *(_DWORD *)(this + 3496872) = v7;
    v9 = *(_DWORD *)(this + 3510412);
    if ( v9 )
      *(_DWORD *)(v9 + 8) = v7;
    *(_DWORD *)(this + 3510404) |= 0x200u;
  }
  *(_DWORD *)(this + 3510424) = 0;
  *(_DWORD *)(this + 3510420) = 0;
  *(_DWORD *)(this + 3510416) = 0;
  v10 = *(_DWORD *)(this + 3510404);
  v11 = (double)*(int *)(this + 80);
  *(_DWORD *)(this + 3510484) = this + 3913572;
  *(float *)(this + 3510424) = v11;
  v12 = this + 3510496;
  *(_DWORD *)(this + 3510404) = v10 & 0xFFFFFFDF;
  *(_DWORD *)(this + 3510452) = 1065336439;
  if ( (*(_DWORD *)(this + 3510500) & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    *(_DWORD *)(this + 3510504) = v8;
    *(_DWORD *)(this + 3510508) = *(_DWORD *)(this + 3496872);
    *(_DWORD *)(this + 3496872) = v12;
    v13 = *(_DWORD *)(this + 3510508);
    if ( v13 )
      *(_DWORD *)(v13 + 8) = v12;
    *(_DWORD *)(this + 3510500) |= 0x200u;
  }
  *(_DWORD *)(this + 3510520) = 0;
  *(_DWORD *)(this + 3510516) = 0;
  *(_DWORD *)(this + 3510512) = 0;
  v14 = *(_DWORD *)(this + 3510500);
  v15 = (double)*(int *)(this + 88);
  v16 = this + 3913572;
  LOBYTE(v14) = v14 & 0xDF;
  *(_DWORD *)(this + 3510580) = this + 3913572;
  *(_DWORD *)(this + 3510500) = v14;
  *(float *)(this + 3510520) = v15;
  *(_DWORD *)(this + 3510548) = 1065336439;
  *(_BYTE *)(this + 43092) = 0;
  *(_DWORD *)(this + 16721372) = 0;
  *(_DWORD *)(this + 19343400) = 0;
  *(_DWORD *)(this + 60) = 2;
  *((_DWORD *)MEMORY[0x4DF904] + 347) = 1;
  release_mouse_cursor((_DWORD *)MEMORY[0x4DF904] + 164);
  *(_DWORD *)(this + 3914608) = 1;
  *(_DWORD *)(this + 3924180) = 0;
  initialize_subgoldy(this + 3913572, 1);
  v17 = this + 3928776;
  if ( (*(_DWORD *)(this + 3928780) & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    v18 = (char *)MEMORY[0x4DF904] + 1452;
    v19 = *((_DWORD *)MEMORY[0x4DF904] + 363);
    if ( v19 )
    {
      *(_DWORD *)(v19 + 8) = v17;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v18 + 8) + 12) = *(_DWORD *)v18;
      v20 = *(_DWORD *)(*(_DWORD *)v18 + 8);
      *(_DWORD *)v18 = v20;
      *(_DWORD *)(v20 + 8) = 0;
    }
    else
    {
      *(_DWORD *)v18 = v17;
      *(_DWORD *)(this + 3928784) = 0;
      *(_DWORD *)(*(_DWORD *)v18 + 12) = 0;
    }
    *(_DWORD *)(this + 3928780) |= 0x200u;
  }
  v21 = this + 3925812;
  if ( (*(_DWORD *)(this + 3925816) & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    v22 = (char *)MEMORY[0x4DF904] + 1452;
    v23 = *((_DWORD *)MEMORY[0x4DF904] + 363);
    if ( v23 )
    {
      *(_DWORD *)(v23 + 8) = v21;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v22 + 8) + 12) = *(_DWORD *)v22;
      v24 = *(_DWORD *)(*(_DWORD *)v22 + 8);
      *(_DWORD *)v22 = v24;
      *(_DWORD *)(v24 + 8) = 0;
    }
    else
    {
      *(_DWORD *)v22 = v21;
      *(_DWORD *)(this + 3925820) = 0;
      *(_DWORD *)(*(_DWORD *)v22 + 12) = 0;
    }
    *(_DWORD *)(this + 3925816) |= 0x200u;
  }
  v25 = this + 3926800;
  if ( (*(_DWORD *)(this + 3926804) & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    v26 = (char *)MEMORY[0x4DF904] + 1452;
    v27 = *((_DWORD *)MEMORY[0x4DF904] + 363);
    if ( v27 )
    {
      *(_DWORD *)(v27 + 8) = v25;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v26 + 8) + 12) = *(_DWORD *)v26;
      v28 = *(_DWORD *)(*(_DWORD *)v26 + 8);
      *(_DWORD *)v26 = v28;
      *(_DWORD *)(v28 + 8) = 0;
    }
    else
    {
      *(_DWORD *)v26 = v25;
      *(_DWORD *)(this + 3926808) = 0;
      *(_DWORD *)(*(_DWORD *)v26 + 12) = 0;
    }
    *(_DWORD *)(this + 3926804) |= 0x200u;
  }
  v29 = this + 3927788;
  if ( (*(_DWORD *)(this + 3927792) & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    v30 = (char *)MEMORY[0x4DF904] + 1452;
    v31 = *((_DWORD *)MEMORY[0x4DF904] + 363);
    if ( v31 )
    {
      *(_DWORD *)(v31 + 8) = v29;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v30 + 8) + 12) = *(_DWORD *)v30;
      v32 = *(_DWORD *)(*(_DWORD *)v30 + 8);
      *(_DWORD *)v30 = v32;
      *(_DWORD *)(v32 + 8) = 0;
    }
    else
    {
      *(_DWORD *)v30 = v29;
      *(_DWORD *)(this + 3927796) = 0;
      *(_DWORD *)(*(_DWORD *)v30 + 12) = 0;
    }
    *(_DWORD *)(this + 3927792) |= 0x200u;
  }
  v33 = this + 3930492;
  if ( (*(_DWORD *)(this + 3930496) & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    v34 = (char *)MEMORY[0x4DF904] + 1452;
    v35 = *((_DWORD *)MEMORY[0x4DF904] + 363);
    if ( v35 )
    {
      *(_DWORD *)(v35 + 8) = v33;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v34 + 8) + 12) = *(_DWORD *)v34;
      v36 = *(_DWORD *)(*(_DWORD *)v34 + 8);
      *(_DWORD *)v34 = v36;
      *(_DWORD *)(v36 + 8) = 0;
    }
    else
    {
      *(_DWORD *)v34 = v33;
      *(_DWORD *)(this + 3930500) = 0;
      *(_DWORD *)(*(_DWORD *)v34 + 12) = 0;
    }
    *(_DWORD *)(this + 3930496) |= 0x200u;
  }
  v37 = *(_DWORD *)(this + 3930496);
  LOBYTE(v37) = v37 | 0x80;
  *(_DWORD *)(this + 3930496) = v37;
  v38 = this + 3924200;
  if ( (*(_DWORD *)(this + 3924204) & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    v39 = (char *)MEMORY[0x4DF904] + 1452;
    v40 = *((_DWORD *)MEMORY[0x4DF904] + 363);
    if ( v40 )
    {
      *(_DWORD *)(v40 + 8) = v38;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v39 + 8) + 12) = *(_DWORD *)v39;
      v41 = *(_DWORD *)(*(_DWORD *)v39 + 8);
      *(_DWORD *)v39 = v41;
      *(_DWORD *)(v41 + 8) = 0;
    }
    else
    {
      *(_DWORD *)v39 = v38;
      *(_DWORD *)(this + 3924208) = 0;
      *(_DWORD *)(*(_DWORD *)v39 + 12) = 0;
    }
    *(_DWORD *)(this + 3924204) |= 0x200u;
  }
  if ( (*(_DWORD *)(this + 3913576) & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    v42 = (char *)MEMORY[0x4DF904] + 1452;
    v43 = *((_DWORD *)MEMORY[0x4DF904] + 363);
    if ( v43 )
    {
      *(_DWORD *)(v43 + 8) = v16;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v42 + 8) + 12) = *(_DWORD *)v42;
      v44 = *(_DWORD *)(*(_DWORD *)v42 + 8);
      *(_DWORD *)v42 = v44;
      *(_DWORD *)(v44 + 8) = 0;
    }
    else
    {
      *(_DWORD *)v42 = v16;
      *(_DWORD *)(this + 3913580) = 0;
      *(_DWORD *)(*(_DWORD *)v42 + 12) = 0;
    }
    *(_DWORD *)(this + 3913576) |= 0x200u;
  }
  initialize_slug_voice_manager((_DWORD *)(this + 3521404));
  v45 = this + 16743364;
  if ( (*(_DWORD *)(this + 16743368) & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    *(_DWORD *)(this + 16743372) = this + 3496916;
    *(_DWORD *)(this + 16743376) = *(_DWORD *)(this + 3496928);
    *(_DWORD *)(this + 3496928) = v45;
    v46 = *(_DWORD *)(this + 16743376);
    if ( v46 )
      *(_DWORD *)(v46 + 8) = v45;
    *(_DWORD *)(this + 16743368) |= 0x200u;
  }
  v47 = *(_DWORD *)(this + 64);
  *(_DWORD *)(this + 16743420) = v16;
  if ( !v47 )
  {
    sprintf((char *const)(*(_DWORD *)(this + 3521428) + 716), "0/%i", *(_DWORD *)(this + 1769952));
    unhide_border_init(*(_DWORD **)(this + 3521424));
    unhide_border_init(*(_DWORD **)(this + 3521428));
  }
  set_input_controller_pointer_authored_xy(0, 320.0, 240.0);
  set_input_controller_pointer_authored_xy(1, 320.0, 240.0);
  *(_DWORD *)(this + 3923616) = 1134559232;
  *(_DWORD *)(this + 3923620) = 1134559232;
  *(_BYTE *)this = 1;
  calc_subgame_rate(this);
}

