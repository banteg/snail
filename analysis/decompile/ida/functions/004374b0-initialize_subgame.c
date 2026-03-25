/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_subgame @ 0x4374b0 */
/* selector: initialize_subgame */

// Initializes the active gameplay subgame state, including the continuation selector at `+0x1270fc8`, per-mode HUD widgets, replay-backed startup, and the first galaxy, challenge-setup, or gameplay handoff. Cross-port Android and iOS symbols match this helper to `cRSubGame::Init()`.
_BYTE *__thiscall initialize_subgame(int this)
{
  int v1; // edx
  _DWORD *v3; // eax
  int v4; // ecx
  _DWORD *v5; // edi
  int v6; // eax
  int landscape_script_by_name; // eax
  int v8; // eax
  int v9; // eax
  char *v10; // eax
  _DWORD *v11; // eax
  _DWORD *v12; // eax
  _DWORD *v13; // eax
  int v14; // edi
  int *v15; // esi
  _DWORD *v16; // eax
  int v17; // eax
  _DWORD *v18; // edx
  char *v19; // eax
  _DWORD *v20; // eax
  char *v21; // eax
  _BYTE *result; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // edx
  int v27; // [esp+0h] [ebp-40h]
  int v28; // [esp+24h] [ebp-1Ch]
  _DWORD v29[6]; // [esp+28h] [ebp-18h] BYREF

  v1 = 3200;
  v3 = (_DWORD *)(this + 3930892);
  do
  {
    v4 = 8;
    do
    {
      v5 = v3;
      v3 += 21;
      --v4;
      *v5 = 0;
      v5[1] = 0;
      v5[2] = 0;
      v5[3] = 0;
    }
    while ( v4 );
    --v1;
  }
  while ( v1 );
  v6 = *(_DWORD *)(this + 19337160);
  if ( v6 == 2 || v6 == 1 )
  {
    cache_music_file(aMusicMainmenuO);
    landscape_script_by_name = load_landscape_script_by_name((char *)MEMORY[0x4DF904] + 17220120, aMenubgTxt);
    change_backdrop(
      (int)MEMORY[0x4DF904] + 322576,
      (int)MEMORY[0x4DF904] + 292 * landscape_script_by_name + 17221564,
      0);
    set_border_justify_centre((_DWORD *)MEMORY[0x4DF904] + 723, 1103626240);
  }
  v8 = *(_DWORD *)(this + 64);
  if ( !v8 )
  {
    v10 = (char *)&unk_68B4D0 + this;
LABEL_14:
    *(_DWORD *)((char *)&unk_68B4C8 + this) = v10;
    *(_DWORD *)(this + 3497364) = *((_DWORD *)v10 + 1);
    goto LABEL_15;
  }
  v9 = v8 - 1;
  if ( v9 )
  {
    if ( v9 != 3 )
      goto LABEL_16;
    v10 = (char *)(this + 9716048);
    goto LABEL_14;
  }
  v10 = (char *)&unk_7E7B10 + this;
  *(_DWORD *)((char *)&unk_68B4C8 + this) = (char *)&unk_7E7B10 + this;
  *(_DWORD *)(this + 3497364) = *(_DWORD *)((char *)&unk_7E7B10 + this + 4);
LABEL_15:
  qmemcpy((void *)(this + 3497368), v10 + 8, 0x18u);
LABEL_16:
  if ( *(_BYTE *)(this + 16721361) )
    *(_DWORD *)(this + 48) = *(_DWORD *)(*(_DWORD *)(this + 16721364) + 72);
  *(_BYTE *)(this + 9) = 0;
  *(_BYTE *)(this + 8) = 0;
  *(_DWORD *)(this + 12) = 0;
  *(_DWORD *)(this + 16) = 1023969417;
  noop_runtime_ai((char *)&unk_68B4C8 + this);
  *(_DWORD *)(this + 60) = 0;
  *(_DWORD *)(this + 19343400) = 0;
  *(_DWORD *)(this + 3521416) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v11 = set_color_rgba(v29, 1065353216, 1065353216, 1065353216, 1022739087);
  initialize_frontend_widget(*(_DWORD *)(this + 3521416), 4194306, a0, 20, 1137180672, 14.0, (int)v11, 3, 300.0);
  *(_DWORD *)(*(_DWORD *)(this + 3521416) + 1776) = 1069547520;
  *(_DWORD *)(*(_DWORD *)(this + 3521416) + 628) = 7;
  *(_BYTE *)(*(_DWORD *)(this + 3521416) + 716) = 0;
  if ( !*(_DWORD *)(this + 64) )
  {
    *(_DWORD *)(this + 3521424) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
    v12 = set_color_rgba(v29, 1065353216, 1065353216, 1065353216, 1065353216);
    initialize_frontend_sprite_button(*(_DWORD *)(this + 3521424), 4196352, 122, 0, 1114112000, v12, 0.0, 4);
    hide_border_init(*(_DWORD **)(this + 3521424));
    *(_DWORD *)(*(_DWORD *)(this + 3521424) + 376) = 0;
    *(_DWORD *)(this + 3521428) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
    v13 = set_color_rgba(v29, 1065353216, 1065353216, 1065353216, 1022739087);
    initialize_frontend_widget(*(_DWORD *)(this + 3521428), 4194306, a0, 20, 1111228416, 80.0, (int)v13, 0, 0.0);
    hide_border_init(*(_DWORD **)(this + 3521428));
    v14 = 0;
    v28 = 0;
    v15 = (int *)(this + 3521432);
    *(_DWORD *)(*(_DWORD *)(this + 3521428) + 1776) = 1060320051;
    do
    {
      *v15 = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v16 = set_color_rgba(v29, 1065353216, 1065353216, 1065353216, 1065353216);
      *(float *)&v27 = (double)v28 * 24.0 + 13.0;
      initialize_frontend_sprite_button(*v15, 4196352, 123, v27, 1138163712, v16, 0.0, 4);
      *(_DWORD *)(*v15 + 376) = 0;
      hide_border_init((_DWORD *)*v15);
      ++v14;
      ++v15;
      v28 = v14;
    }
    while ( v14 < 9 );
  }
  v17 = *(_DWORD *)(this + 64);
  if ( *(_DWORD *)(this + 16332220) == v17 )
  {
    if ( v17 == 4 )
    {
      v18 = (_DWORD *)(this + 16332184);
LABEL_24:
      v19 = format_time_trial_string((int)v18);
      sub_44E5B0((char *)(*(_DWORD *)(this + 3521416) + 716), v19);
      goto LABEL_29;
    }
    border_add_text_number(*(_BYTE **)(this + 3521416), *(_DWORD *)(this + 16332180));
  }
  else
  {
    if ( v17 == 4 )
    {
      zero_timer_counters(v29);
      v18 = v29;
      goto LABEL_24;
    }
    border_add_text_number(*(_BYTE **)(this + 3521416), 0);
  }
LABEL_29:
  *(_DWORD *)(this + 3521420) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v20 = set_color_rgba(v29, 1065353216, 1065353216, 1065353216, 1022739087);
  initialize_frontend_widget(*(_DWORD *)(this + 3521420), 4194306, a0, 20, 1109393408, 14.0, (int)v20, 3, -71.0);
  *(_DWORD *)(*(_DWORD *)(this + 3521420) + 1776) = 1069547520;
  *(_DWORD *)(*(_DWORD *)(this + 3521420) + 628) = 7;
  *(_BYTE *)(*(_DWORD *)(this + 3521420) + 716) = 0;
  switch ( *(_DWORD *)(this + 64) )
  {
    case 0:
    case 1:
      border_add_text_number(*(_BYTE **)(this + 3521420), *(_DWORD *)(this + 3497364));
      break;
    case 2:
    case 3:
      hide_border_init(*(_DWORD **)(this + 3521420));
      hide_border_init(*(_DWORD **)(this + 3521416));
      break;
    case 4:
      v21 = format_time_trial_string(this + 3497368);
      sub_44E5B0((char *)(*(_DWORD *)(this + 3521420) + 716), v21);
      break;
    default:
      break;
  }
  result = MEMORY[0x4DF904];
  if ( *((_BYTE *)MEMORY[0x4DF904] + 324320) || *(_DWORD *)(this + 64) == 7 )
  {
    hide_border_init(*(_DWORD **)(this + 3521420));
    hide_border_init(*(_DWORD **)(this + 3521416));
    result = MEMORY[0x4DF904];
  }
  if ( !result[781] )
  {
    result[781] = 0;
    *((_DWORD *)MEMORY[0x4DF904] + 196) = 0;
    load_builtin_segment_definitions((int *)(this + 1769964), (int)&off_4A63D0);
    set_matrix_identity((_DWORD *)(this + 3913628));
    *(_DWORD *)(this + 3914608) = 0;
    *(_DWORD *)(this + 3914604) = this;
    v23 = *(_DWORD *)(this + 3913676);
    *(_BYTE *)(this + 3914625) = 0;
    *(_DWORD *)(this + 3924168) = v23;
    *(_BYTE *)(this + 3914624) = 0;
    v24 = *(_DWORD *)(this + 3913680);
    *(_DWORD *)(this + 3914600) = 0;
    *(_DWORD *)(this + 3924172) = v24;
    *(_DWORD *)(this + 3924176) = *(_DWORD *)(this + 3913684);
    *(_DWORD *)(this + 3913576) &= ~0x20u;
    initialize_warning((int *)(this + 3914584));
    v25 = *(_DWORD *)(this + 19337160);
    if ( v25 && v25 != 3 )
    {
      if ( !*(_BYTE *)(this + 16721361) )
      {
        switch ( *(_DWORD *)(this + 64) )
        {
          case 0:
            if ( v25 == 1 )
            {
              v26 = *(_DWORD *)(this + 68) + 1;
              *(_DWORD *)(this + 68) = v26;
              if ( v26 > dword_4DF9B8 )
              {
                dword_4DF9B8 = v26;
                save_config_file(aSnailmailCfg, &unk_4DF918, 196);
              }
              unk_4DF9BC = *(_DWORD *)(this + 68);
            }
            goto LABEL_45;
          case 1:
            initialize_challenge_setup_screen((int *)(this + 19267552));
            result = (_BYTE *)reset_subgame((_DWORD *)this);
            break;
          case 4:
LABEL_45:
            initialize_galaxy(this + 19267616);
            result = (_BYTE *)reset_subgame((_DWORD *)this);
            break;
          case 7:
            *(_DWORD *)(this + 60) = 0;
            result = (_BYTE *)reset_subgame((_DWORD *)this);
            break;
          default:
            report_errorf(aUnknownGameMod);
            result = (_BYTE *)reset_subgame((_DWORD *)this);
            break;
        }
        return result;
      }
      *(_DWORD *)(this + 48) = *(_DWORD *)(*(_DWORD *)(this + 16721364) + 72);
    }
    return (_BYTE *)reset_subgame((_DWORD *)this);
  }
  return result;
}

