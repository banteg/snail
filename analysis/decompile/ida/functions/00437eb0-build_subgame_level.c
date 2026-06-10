/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_subgame_level @ 0x437eb0 */
/* selector: build_subgame_level */

// Builds the active subgame course, including level-file load, runtime track rebuild, mode-specific HUD setup, backdrop selection, and the first gameplay object lists. Cross-port Android and iOS symbols match this helper to `cRSubGame::BuildLevel()`.
void __thiscall build_subgame_level(Game *game, int32_t level_index)
{
  int32_t level_mode; // eax
  double challenge_difficulty_value; // st7
  int32_t v5; // eax
  int landscape_script_by_name; // eax
  uint8_t *v7; // eax
  uint8_t *v8; // edi
  int v9; // ecx
  int v10; // edx
  double first_block_row_count; // st7
  uint8_t *v12; // eax
  int v13; // ecx
  int v14; // eax
  double completion_row_start; // st7
  uint8_t *v16; // edi
  uint8_t *v17; // eax
  char *v18; // ecx
  int v19; // edx
  int v20; // edx
  uint8_t *v21; // ecx
  char *v22; // eax
  int v23; // edx
  int v24; // edx
  uint8_t *v25; // ecx
  char *v26; // eax
  int v27; // edx
  int v28; // edx
  uint8_t *v29; // ecx
  char *v30; // eax
  int v31; // edx
  int v32; // edx
  uint8_t *v33; // ecx
  char *v34; // eax
  int v35; // edx
  int v36; // edx
  int v37; // ecx
  uint8_t *v38; // ecx
  char *v39; // eax
  int v40; // edx
  int v41; // edx
  char *v42; // eax
  int v43; // ecx
  int v44; // ecx
  uint8_t *v45; // eax
  int v46; // ecx
  int32_t v47; // eax
  float v48; // [esp+0h] [ebp-14h]

  unhide_star_field((int *)MEMORY[0x4DF904] + 81103);
  if ( game->level_mode == 7 )
    hide_gameplay_scores(game);
  else
    unhide_gameplay_scores(game);
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
  *(_DWORD *)&game->_pad_ff25e8[2615780] = 1112014848;
  *(_DWORD *)&game->_pad_ff25e8[2615784] = 1120403456;
  initialize_enemy_manager((#94 *)&game->_pad_ff25e8[2615788]);
  initialize_damage_gauge(&game->_pad_74622[3437830]);
  noop_runtime_ai();
  initialize_sub_lazer_pool(&game->_pad_74622[3024094]);
  initialize_salt_hazard_pool(&game->_pad_74622[3027614]);
  reset_voice_manager(unk_751498);
  load_frontend_level_by_mode_and_index((char *)&game->level_segment_count, game->level_mode, level_index);
  if ( game->selected_level_record_active || game->selected_level_record_persistent )
  {
    *(float *)&game->_pad_00[48] = game->selected_level_record->replay_speed_scalar;
    game->level_mode = game->selected_level_record->replay_mode_id;
    *(_DWORD *)&game->_pad_00[44] = game->selected_level_record->challenge_difficulty_value;
    *(_DWORD *)&game->_pad_00[40] = game->selected_level_record->challenge_speed_value;
    challenge_difficulty_value = (double)(int)game->selected_level_record->challenge_difficulty_value;
    goto LABEL_24;
  }
  level_mode = game->level_mode;
  switch ( level_mode )
  {
    case 3:
      *(float *)&game->_pad_00[48] = unk_4DF95C;
      break;
    case 0:
    case 4:
    case 7:
      if ( *(_DWORD *)&game->_pad_74622[1293230] == -1082130432 )
        *(float *)&game->_pad_00[48] = calc_slider_to_rate(0.0);
      else
        *(float *)&game->_pad_00[48] = *(float *)&game->_pad_74622[1293230] * 0.0099999998 * 0.90000004 + 0.2;
      break;
    case 1:
      v48 = (double)unk_4DF958 * 0.0099999998;
      *(float *)&game->_pad_00[48] = calc_slider_to_rate(v48);
      challenge_difficulty_value = (double)unk_4DF960;
LABEL_24:
      game->challenge_difficulty_scalar = challenge_difficulty_value * 0.0099999998;
      break;
    case 2:
      *(float *)&game->_pad_00[48] = calc_slider_to_rate(unk_4DF95C);
      break;
  }
  if ( game->selected_level_record_active || game->selected_level_record_persistent )
  {
    *(_DWORD *)&game->_pad_ff25e8[2546160] = *(_DWORD *)&game->selected_level_record[1080].replay_samples[0].lateral_x;
    *(_DWORD *)&game->_pad_ff25e8[2546164] = *(_DWORD *)&game->selected_level_record[1080].replay_samples[0].flags;
  }
  else
  {
    v5 = game->level_mode;
    if ( v5 == 2 || v5 == 3 || !v5 || v5 == 4 || v5 == 7 )
    {
      *(float *)&game->_pad_ff25e8[2546160] = *(float *)&game->_pad_74622[1293234] * 0.0099999998;
      *(float *)&game->_pad_ff25e8[2546164] = *(float *)&game->_pad_74622[1293238] * 0.0099999998;
    }
    else if ( v5 == 1 )
    {
      *(float *)&game->_pad_ff25e8[2546160] = (double)unk_4DF960 * 0.0099999998 * 0.80000001;
      *(float *)&game->_pad_ff25e8[2546164] = (double)unk_4DF960 * 0.0099999998 * 0.80000001;
    }
  }
  initialize_track_parcel_slots(&game->_pad_ff25e8[2539160]);
  if ( *((_BYTE *)MEMORY[0x4DF904] + 324320) == 1 )
  {
    hide_border_init(*(_DWORD **)&game->_pad_74622[3044710]);
    hide_border_init(*(_DWORD **)&game->_pad_74622[3044714]);
  }
  rebuild_track_runtime_from_segments(game, level_index);
  if ( *(_DWORD *)&game->_pad_74622[1293250] == 5 )
  {
    switch ( (unsigned int)(__int64)random_float_below(4.0) )
    {
      case 0u:
        landscape_script_by_name = load_landscape_script_by_name((char *)MEMORY[0x4DF904] + 17220120, aSpaceblueswhor);
        break;
      case 1u:
        landscape_script_by_name = load_landscape_script_by_name((char *)MEMORY[0x4DF904] + 17220120, aSpacegreenwarp);
        break;
      case 2u:
        landscape_script_by_name = load_landscape_script_by_name((char *)MEMORY[0x4DF904] + 17220120, aSpacepurpleTxt);
        break;
      case 3u:
        landscape_script_by_name = load_landscape_script_by_name((char *)MEMORY[0x4DF904] + 17220120, aSpaceredTxt);
        break;
      default:
        landscape_script_by_name = level_index;
        break;
    }
    activate_landscape_entry((char *)&game->_pad_ff25e8[22040], landscape_script_by_name);
    *((_BYTE *)MEMORY[0x4DF904] + 322660) = random_float_below(1.0) > 0.5;
  }
  else
  {
    activate_landscape_entry((char *)&game->_pad_ff25e8[22040], *(_DWORD *)&game->_pad_74622[1293242]);
  }
  v7 = &game->_pad_74622[3033694];
  v8 = &game->_pad_74622[3020154];
  if ( (*(_DWORD *)&game->_pad_74622[3033698] & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    *(_DWORD *)&game->_pad_74622[3033702] = v8;
    *(_DWORD *)&game->_pad_74622[3033706] = *(_DWORD *)&game->_pad_74622[3020166];
    *(_DWORD *)&game->_pad_74622[3020166] = v7;
    v9 = *(_DWORD *)&game->_pad_74622[3033706];
    if ( v9 )
      *(_DWORD *)(v9 + 8) = v7;
    *(_DWORD *)&game->_pad_74622[3033698] |= 0x200u;
  }
  *(_DWORD *)&game->_pad_74622[3033718] = 0;
  *(_DWORD *)&game->_pad_74622[3033714] = 0;
  *(_DWORD *)&game->_pad_74622[3033710] = 0;
  v10 = *(_DWORD *)&game->_pad_74622[3033698];
  first_block_row_count = (double)game->first_block_row_count;
  *(_DWORD *)&game->_pad_74622[3033778] = &game->_pad_74622[3436866];
  *(float *)&game->_pad_74622[3033718] = first_block_row_count;
  v12 = &game->_pad_74622[3033790];
  *(_DWORD *)&game->_pad_74622[3033698] = v10 & 0xFFFFFFDF;
  *(_DWORD *)&game->_pad_74622[3033746] = 1065336439;
  if ( (*(_DWORD *)&game->_pad_74622[3033794] & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    *(_DWORD *)&game->_pad_74622[3033798] = v8;
    *(_DWORD *)&game->_pad_74622[3033802] = *(_DWORD *)&game->_pad_74622[3020166];
    *(_DWORD *)&game->_pad_74622[3020166] = v12;
    v13 = *(_DWORD *)&game->_pad_74622[3033802];
    if ( v13 )
      *(_DWORD *)(v13 + 8) = v12;
    *(_DWORD *)&game->_pad_74622[3033794] |= 0x200u;
  }
  *(_DWORD *)&game->_pad_74622[3033814] = 0;
  *(_DWORD *)&game->_pad_74622[3033810] = 0;
  *(_DWORD *)&game->_pad_74622[3033806] = 0;
  v14 = *(_DWORD *)&game->_pad_74622[3033794];
  completion_row_start = (double)game->completion_row_start;
  v16 = &game->_pad_74622[3436866];
  LOBYTE(v14) = v14 & 0xDF;
  *(_DWORD *)&game->_pad_74622[3033874] = &game->_pad_74622[3436866];
  *(_DWORD *)&game->_pad_74622[3033794] = v14;
  *(float *)&game->_pad_74622[3033814] = completion_row_start;
  *(_DWORD *)&game->_pad_74622[3033842] = 1065336439;
  game->track_state_latch = 0;
  game->replay_update_cursor = 0;
  *((_DWORD *)game + 4835850) = 0;
  game->subgame_state = 2;
  *((_DWORD *)MEMORY[0x4DF904] + 347) = 1;
  release_mouse_cursor((_DWORD *)MEMORY[0x4DF904] + 164);
  *(_DWORD *)&game->_pad_74622[3437902] = 1;
  *(_DWORD *)&game->_pad_74622[3447474] = 0;
  initialize_subgoldy((Player *)&game->_pad_74622[3436866], 1);
  v17 = &game->_pad_74622[3452070];
  if ( (*(_DWORD *)&game->_pad_74622[3452074] & 0x200) != 0 )
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
      *(_DWORD *)&game->_pad_74622[3452078] = 0;
      *(_DWORD *)(*(_DWORD *)v18 + 12) = 0;
    }
    *(_DWORD *)&game->_pad_74622[3452074] |= 0x200u;
  }
  v21 = &game->_pad_74622[3449106];
  if ( (*(_DWORD *)&game->_pad_74622[3449110] & 0x200) != 0 )
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
      *(_DWORD *)&game->_pad_74622[3449114] = 0;
      *(_DWORD *)(*(_DWORD *)v22 + 12) = 0;
    }
    *(_DWORD *)&game->_pad_74622[3449110] |= 0x200u;
  }
  v25 = &game->_pad_74622[3450094];
  if ( (*(_DWORD *)&game->_pad_74622[3450098] & 0x200) != 0 )
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
      *(_DWORD *)&game->_pad_74622[3450102] = 0;
      *(_DWORD *)(*(_DWORD *)v26 + 12) = 0;
    }
    *(_DWORD *)&game->_pad_74622[3450098] |= 0x200u;
  }
  v29 = &game->_pad_74622[3451082];
  if ( (*(_DWORD *)&game->_pad_74622[3451086] & 0x200) != 0 )
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
      *(_DWORD *)&game->_pad_74622[3451090] = 0;
      *(_DWORD *)(*(_DWORD *)v30 + 12) = 0;
    }
    *(_DWORD *)&game->_pad_74622[3451086] |= 0x200u;
  }
  v33 = &game->_pad_74622[3453786];
  if ( (*(_DWORD *)&game->_pad_74622[3453790] & 0x200) != 0 )
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
      *(_DWORD *)&game->_pad_74622[3453794] = 0;
      *(_DWORD *)(*(_DWORD *)v34 + 12) = 0;
    }
    *(_DWORD *)&game->_pad_74622[3453790] |= 0x200u;
  }
  v37 = *(_DWORD *)&game->_pad_74622[3453790];
  LOBYTE(v37) = v37 | 0x80;
  *(_DWORD *)&game->_pad_74622[3453790] = v37;
  v38 = &game->_pad_74622[3447494];
  if ( (*(_DWORD *)&game->_pad_74622[3447498] & 0x200) != 0 )
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
      *(_DWORD *)&game->_pad_74622[3447502] = 0;
      *(_DWORD *)(*(_DWORD *)v39 + 12) = 0;
    }
    *(_DWORD *)&game->_pad_74622[3447498] |= 0x200u;
  }
  if ( (*(_DWORD *)&game->_pad_74622[3436870] & 0x200) != 0 )
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
      *(_DWORD *)&game->_pad_74622[3436874] = 0;
      *(_DWORD *)(*(_DWORD *)v42 + 12) = 0;
    }
    *(_DWORD *)&game->_pad_74622[3436870] |= 0x200u;
  }
  initialize_slug_voice_manager(&game->_pad_74622[3044698]);
  v45 = &game->_pad_ff25e8[21980];
  if ( (*(_DWORD *)&game->_pad_ff25e8[21984] & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    *(_DWORD *)&game->_pad_ff25e8[21988] = &game->_pad_74622[3020210];
    *(_DWORD *)&game->_pad_ff25e8[21992] = *(_DWORD *)&game->_pad_74622[3020222];
    *(_DWORD *)&game->_pad_74622[3020222] = v45;
    v46 = *(_DWORD *)&game->_pad_ff25e8[21992];
    if ( v46 )
      *(_DWORD *)(v46 + 8) = v45;
    *(_DWORD *)&game->_pad_ff25e8[21984] |= 0x200u;
  }
  v47 = game->level_mode;
  *(_DWORD *)&game->_pad_ff25e8[22036] = v16;
  if ( !v47 )
  {
    sprintf((char *const)(*(_DWORD *)&game->_pad_74622[3044722] + 716), "0/%i", *(_DWORD *)&game->_pad_74622[1293246]);
    unhide_border_init(*(_DWORD **)&game->_pad_74622[3044718]);
    unhide_border_init(*(_DWORD **)&game->_pad_74622[3044722]);
  }
  set_input_controller_pointer_authored_xy(0, 320.0, 240.0);
  set_input_controller_pointer_authored_xy(1, 320.0, 240.0);
  *(_DWORD *)&game->_pad_74622[3446910] = 1134559232;
  *(_DWORD *)&game->_pad_74622[3446914] = 1134559232;
  game->_pad_00[0] = 1;
  calc_subgame_rate(game);
}

