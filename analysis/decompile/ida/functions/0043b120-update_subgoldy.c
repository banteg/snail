/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_subgoldy @ 0x43b120 */
/* selector: update_subgoldy */

// Main per-frame player or Goldy actor step. Updates attachment-follow state, samples current track cells, drives row events, dispatches pickups and completion handoff, emits movement flags and sounds, and advances the runtime track index. It contains four direct calls to `initialize_subgoldy_fall_state`, plus the post-exit progress loop that advances `attachment_exit_progress` by `attachment_exit_progress_step` and trips the `gate_a` and `gate_b` thresholds. Windows `cdb` confirmed those fall-helper lanes are real, but at least one clean level-complete path bypasses all four of them. Newer field-xref narrowing also shows later retirement of `attachment_exit_pending` happens only through five clear sites inside this function, not through the swept-entry helper or a standalone progress-expiry store; one of those clear sites, `0x43bcb3`, now resolves to the non-follow floor-cache/slide motion branch for runtime tiles `0x0f`/`0x10`/`0x12`/`0x13` plus the `damage_gauge.state == 2` slide override. Cross-port Android
int32_t __thiscall update_subgoldy(Player *player)
{
  int32_t result; // eax
  PathTemplate *template_record; // esi
  signed int v4; // eax
  signed int segment_count; // ecx
  Game *game; // eax
  Game *v13; // eax
  int v14; // ecx
  int v15; // eax
  double v17; // st7
  Game *v19; // eax
  __int16 v34; // ax
  Game *v36; // esi
  Game *v37; // esi
  Game *v38; // eax
  PlayerControlSource *control_source; // eax
  Game *v40; // eax
  char *track_grid_cell_at_world_position; // eax
  Game *v44; // edi
  int v45; // eax
  char *v46; // esi
  int v47; // eax
  int v49; // esi
  Game *v50; // edx
  uint8_t v51; // al
  char *v80; // eax
  char *v96; // esi
  int track_cell_row_index; // eax
  int v100; // eax
  char v105; // al
  char v108; // al
  Game *v111; // ecx
  float v138; // eax
  char *v139; // ecx
  Game *v163; // ecx
  Game *v167; // eax
  Game *v169; // ecx
  int v172; // eax
  Game *v173; // eax
  int v174; // ecx
  Game *v175; // ebp
  bool v176; // zf
  float v183; // edx
  int skin_hold_ticks; // eax
  Game *v199; // ecx
  char *v200; // eax
  int v201; // ecx
  int v202; // edx
  int v203; // ecx
  int32_t state; // eax
  uint8_t control_override_active; // al
  Game *v226; // ecx
  int32_t movement_state; // eax
  Game *v232; // eax
  float x; // [esp-14h] [ebp-6Ch]
  float v234; // [esp-14h] [ebp-6Ch]
  float y; // [esp-10h] [ebp-68h]
  float v236; // [esp-10h] [ebp-68h]
  float z; // [esp-Ch] [ebp-64h]
  float v238; // [esp-Ch] [ebp-64h]
  float v239; // [esp+0h] [ebp-58h]
  int v240; // [esp+4h] [ebp-54h]
  int v241; // [esp+4h] [ebp-54h]
  float v242; // [esp+4h] [ebp-54h]
  float v243; // [esp+4h] [ebp-54h]
  int v244; // [esp+4h] [ebp-54h]
  float v245; // [esp+18h] [ebp-40h]
  TrackRowCell *v246; // [esp+18h] [ebp-40h]
  int v247; // [esp+18h] [ebp-40h]
  int v248; // [esp+18h] [ebp-40h]
  int v249; // [esp+18h] [ebp-40h]
  int v251; // [esp+18h] [ebp-40h]
  float v253; // [esp+1Ch] [ebp-3Ch]
  float v254; // [esp+1Ch] [ebp-3Ch]
  float v256; // [esp+20h] [ebp-38h]
  float v257; // [esp+20h] [ebp-38h]
  float v259; // [esp+24h] [ebp-34h]
  float v260; // [esp+24h] [ebp-34h]
  float v261; // [esp+24h] [ebp-34h]
  float v262; // [esp+28h] [ebp-30h] BYREF
  float v263; // [esp+2Ch] [ebp-2Ch]
  float v264; // [esp+30h] [ebp-28h]
  float v269; // [esp+4Ch] [ebp-Ch]
  float v270; // [esp+50h] [ebp-8h]
  float v271; // [esp+54h] [ebp-4h]

  _EBP = player;
  result = (int32_t)player->game;
  if ( *(_BYTE *)(result + 9) )
  {
    if ( *((_DWORD *)MEMORY[0x4DF904] + 110) != 9 )
    {
      update_damage_gauge((int)&player->damage_gauge);
      update_progress_bar();
      update_warning((float *)&_EBP->_pad_3f0[4]);
      update_row_event_display((_DWORD **)_EBP->game + 4835830);
    }
    return result;
  }
  if ( player->follow_state.active == 1 )
  {
    template_record = player->follow_state.template_record;
    v4 = player->follow_state.sample_index + 3;
    segment_count = template_record->segment_count;
    if ( v4 >= segment_count )
      v4 = segment_count - 1;
    _EDX = _EBP->snail_visual;
    _EAX = 21 * v4;
    _ECX = template_record->primary_samples;
    __asm
    {
      fld     dword ptr [ecx+eax*8+0A4h]
      fmul    ds:flt_497444
      fsub    dword ptr [edx+80h]
      fmul    ds:flt_497258
      fadd    dword ptr [edx+80h]
      fstp    dword ptr [edx+80h]
    }
    _EDX->follow_lateral_response = _ET1;
  }
  else
  {
    _EAX = player->snail_visual;
    __asm
    {
      fld     dword ptr [eax+80h]
      fchs
      fmul    ds:flt_497258
      fadd    dword ptr [eax+80h]
      fstp    dword ptr [eax+80h]
    }
    _EAX->follow_lateral_response = _ET1;
  }
  update_squidge(&_EBP->squidge);
  _EBP->snail_visual->squidge_primary = _EBP->squidge.y_output;
  _EBP->snail_visual->squidge_secondary = _EBP->squidge.z_output;
  if ( !*((_DWORD *)_EBP->game + 16) )
    show_subgoldy_lives(_EBP);
  result = _EBP->movement_mode_selector;
  if ( result )
  {
    result -= 2;
    if ( result )
    {
      game = _EBP->game;
      if ( *((int *)game + 4180343) > 20 && !*((_BYTE *)game + 43092) )
        *((_BYTE *)game + 43092) = 1;
      v13 = _EBP->game;
      if ( *((_BYTE *)v13 + 16721360) )
      {
        v14 = *((_DWORD *)v13 + 4180341);
        v15 = *((_DWORD *)v13 + 4180343);
        if ( v15 < *(_DWORD *)(v14 + 108) && _EBP->movement_state != 2 )
        {
          _EBX = &_EBP->position;
          v17 = convert_math_type16_to_32(*(_WORD *)(v14 + 6 * v15 + 112), 16.0);
          __asm { fstp    dword ptr [ebx] }
          _EBX->x = _ET1;
          v19 = _EBP->game;
          *((_BYTE *)v19 + 43092) = (*(_BYTE *)(*((_DWORD *)v19 + 4180341) + 6 * *((_DWORD *)v19 + 4180343) + 116) & 4) != 0;
          if ( (*(_BYTE *)(*((_DWORD *)_EBP->game + 4180341) + 6 * *((_DWORD *)_EBP->game + 4180343) + 116) & 8) != 0 )
          {
            *((_DWORD *)MEMORY[0x4DF904] + 110) = 26;
            *((_DWORD *)MEMORY[0x4DF904] + 111) = 10;
            *((_BYTE *)MEMORY[0x4DF904] + 780) = 1;
            begin_frontend_fade_in((_DWORD *)MEMORY[0x4DF904] + 9);
            return result;
          }
LABEL_61:
          __asm
          {
            fld     dword ptr [ebx]
            fcomp   ds:flt_497420
            fnstsw  ax
          }
          if ( (_AX & 0x100) != 0 )
          {
            _EBX->x = -4.0;
            _EBP->velocity.x = 0.0;
          }
          __asm
          {
            fld     dword ptr [ebx]
            fcomp   ds:flt_497210
            fnstsw  ax
          }
          if ( (_AX & 0x4100) == 0 )
          {
            _EBX->x = 4.0;
            _EBP->velocity.x = 0.0;
          }
          if ( _EBP->_pad_74[16] )
            update_subgoldy_resurrect((int)_EBP);
          track_grid_cell_at_world_position = get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x);
          v44 = _EBP->game;
          v246 = (TrackRowCell *)track_grid_cell_at_world_position;
          v45 = 61 * get_track_cell_row_index(track_grid_cell_at_world_position);
          v46 = &byte_5CCAC8[(_DWORD)v44 + 4 * v45];
          v47 = *(int *)((char *)unk_5CCBB8 + (_DWORD)v44 + 4 * v45);
          if ( v47 > 0 && v47 != _EBP->row_event.id && v47 < *((_DWORD *)v44 + 10781) + 1 )
          {
            _EBP->row_event.id = v47;
            if ( *((_BYTE *)_EBP->game + 16928 * *((_DWORD *)v46 + 60) + 42608) )
            {
              _EBP->row_event.state = 2;
              _EBP->row_event.data_b = (int32_t)_EBP->game + 16928 * *((_DWORD *)v46 + 60) + 42608;
              _EBP->row_event.timer = 0.0;
              *(_DWORD *)_EBP->row_event._pad_0c = 1106247680;
              _EBP->row_event.data_a = *((_DWORD *)_EBP->game + 4232 * *((_DWORD *)v46 + 60) + 10780);
              if ( !_EBP->_pad_124[40] )
              {
                _EBP->_pad_124[40] = 1;
                __asm
                {
                  fld     dword ptr [ebx]
                  fcomp   ds:flt_497234
                }
                __asm { fnstsw  ax }
                if ( (_AX & 0x4100) != 0 )
                  dispatch_cutscene_animation((int)_EBP->_pad_2984, 3, 1, -1);
                else
                  dispatch_cutscene_animation((int)_EBP->_pad_2984, 4, 1, -1);
                dispatch_cutscene_animation((int)_EBP->_pad_2984, 1, 0, -1);
              }
              v49 = *((_DWORD *)v46 + 60);
              v50 = _EBP->game;
              if ( *((_DWORD *)v50 + 4232 * v49 + 10781) != -1 )
                play_voice_manager((int)unk_751498, 13, 2u, *((_DWORD *)v50 + 4232 * v49 + 10781));
              enqueue_tip_message((_DWORD *)MEMORY[0x4DF904] + 4955094, (int)&_EBP->row_event.state, 1);
            }
          }
          if ( !_EBP->attachment_exit_pending )
          {
            v51 = v246[1]._pad_00[0];
            if ( (v51 == 29 || v51 == 30) && !_EBP->follow_state.active )
            {
              begin_track_attachment_follow_state(&_EBP->follow_state, v246, _EBX, _EBP);
              if ( _EBP->follow_state.template_record->kind == PATH_TEMPLATE_KIND_WORM )
                play_voice_manager((int)unk_751498, 12, 0, -1);
            }
          }
          if ( _EBP->control_override_active )
          {
            __asm
            {
              fld     dword ptr [ebp+418h]
              fcomp   ds:flt_497234
              fnstsw  ax
            }
            if ( (_AX & 0x100) != 0 )
            {
              _ECX = _EBP->game;
              __asm
              {
                fld     dword ptr [ecx+38h]
                fld     st
                fmul    st, st(1)
                fmul    ds:flt_4973BC
                fmul    ds:flt_49744C
                fadd    dword ptr [ebp+418h]
                fstp    dword ptr [ebp+418h]
              }
              _EBP->velocity.z = _ET1;
              __asm { fstp    st }
            }
            __asm
            {
              fld     dword ptr [ebp+418h]
              fcomp   ds:flt_497234
              fnstsw  ax
            }
            if ( (_AX & 0x4100) == 0 )
LABEL_95:
              _EBP->velocity.z = 0.0;
          }
          else
          {
            _ECX = _EBP->game;
            __asm
            {
              fild    dword ptr [ecx+50h]
              fcomp   dword ptr [ebp+70h]
              fnstsw  ax
            }
            if ( (_AX & 0x4100) == 0 )
            {
              __asm
              {
                fld     dword ptr [ecx+38h]
                fld     st
                fmul    st, st(1)
                fmul    ds:flt_4973BC
                fadd    dword ptr [ebp+418h]
                fstp    dword ptr [ebp+418h]
              }
              _EBP->velocity.z = _ET1;
              __asm { fstp    st }
            }
            __asm
            {
              fld     dword ptr [ebp+418h]
              fcomp   ds:flt_497220
              fnstsw  ax
            }
            if ( (_AX & 0x4100) == 0 )
              _EBP->velocity.z = 1.0;
            if ( _EBP->movement_state == 2 )
              goto LABEL_95;
          }
          if ( _EBP->follow_state.active == 1 )
          {
            _ESI = &_EBP->velocity.x;
            switch ( update_track_attachment_follow_state(&_EBP->follow_state, _EBP->velocity.z, _EBX, &_EBP->velocity) )
            {
              case 0:
                if ( _EBP->follow_state.template_record->kind != PATH_TEMPLATE_KIND_DETOUR )
                {
                  _ECX = _EBP->game;
                  __asm
                  {
                    fld     dword ptr [ecx+38h]
                    fld     st
                    fmul    st, st(1)
                    fmul    ds:flt_4973BC
                    fadd    st, st
                    fadd    dword ptr [ebp+418h]
                    fstp    dword ptr [ebp+418h]
                  }
                  _EBP->velocity.z = _ET1;
                  __asm { fstp    st }
                }
                goto LABEL_102;
              case 1:
              case 3:
                if ( _EBP->follow_state.active == 1 )
                  goto LABEL_99;
                break;
              case 2:
LABEL_102:
                __asm
                {
                  fld     dword ptr [ebx]; jumptable 0043B9A6 case 2
                  fadd    dword ptr [esi]
                  fstp    dword ptr [ebx]
                }
                _EBX->x = _ET1;
                __asm
                {
                  fld     dword ptr [esi+4]
                  fadd    dword ptr [ebx+4]
                  fstp    dword ptr [ebx+4]
                }
                _EBX->y = _ET1;
                __asm
                {
                  fld     dword ptr [esi+8]
                  fadd    dword ptr [ebx+8]
                  fstp    dword ptr [ebx+8]
                }
                _EBX->z = _ET1;
                _EDX = _EBP->game;
                __asm
                {
                  fld     dword ptr [edx+38h]
                  fmul    ds:flt_4975D0
                  fsubr   ds:flt_497220
                  fmul    dword ptr [ebp+418h]
                  fstp    dword ptr [ebp+418h]
                }
                _EBP->velocity.z = _ET1;
                _EAX = _EBP->game;
                __asm
                {
                  fld     dword ptr [eax+38h]
                  fmul    ds:flt_4975D0
                  fsubr   ds:flt_497220
                  fmul    dword ptr [ebp+414h]
                  fstp    dword ptr [ebp+414h]
                }
                _EBP->velocity.y = _ET1;
                _ECX = _EBP->game;
                __asm
                {
                  fld     dword ptr [ecx+38h]
                  fmul    ds:flt_497258
                  fsubr   ds:flt_497220
                  fmul    dword ptr [esi]
                  fstp    dword ptr [esi]
                }
                *_ESI = _ET1;
                _EDX = _EBP->game;
                __asm
                {
                  fld     dword ptr [edx+38h]
                  fld     st
                  fmul    st, st(1)
                  fmul    ds:flt_4975CC
                  fadd    dword ptr [ebp+414h]
                  fstp    dword ptr [ebp+414h]
                }
                _EBP->velocity.y = _ET1;
                __asm
                {
                  fstp    st
                  fld     dword ptr [ebx]
                  fcomp   ds:flt_497420
                  fnstsw  ax
                }
                if ( (BYTE1(_EAX) & 1) != 0 )
                {
                  _EBX->x = -4.0;
                  *_ESI = 0.0;
                }
                __asm
                {
                  fld     dword ptr [ebx]
                  fcomp   ds:flt_497210
                  fnstsw  ax
                }
                if ( (_AX & 0x4100) == 0 )
                {
                  _EBX->x = 4.0;
                  *_ESI = 0.0;
                }
                break;
              default:
                break;
            }
          }
          else
          {
            __asm
            {
              fld     dword ptr [ebp+410h]
              fadd    dword ptr [ebx]
              fstp    dword ptr [ebx]
            }
            _EBX->x = _ET1;
            __asm
            {
              fld     dword ptr [ebp+414h]
              fadd    dword ptr [ebx+4]
              fstp    dword ptr [ebx+4]
            }
            _EBX->y = _ET1;
            __asm
            {
              fld     dword ptr [ebp+418h]
              fadd    dword ptr [ebx+8]
              fstp    dword ptr [ebx+8]
            }
            _EBX->z = _ET1;
            __asm
            {
              fld     dword ptr [ebx]
              fcomp   ds:flt_497420
              fnstsw  ax
            }
            if ( (_AX & 0x100) != 0 )
            {
              _EBX->x = -4.0;
              _EBP->velocity.x = 0.0;
            }
            __asm
            {
              fld     dword ptr [ebx]
              fcomp   ds:flt_497210
              fnstsw  ax
            }
            if ( (_AX & 0x4100) == 0 )
            {
              _EBX->x = 4.0;
              _EBP->velocity.x = 0.0;
            }
            if ( !LOBYTE(_EBP->completion_handoff_active) )
            {
              if ( get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 15
                || get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 16
                || get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 18
                || get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 19
                || _EBP->damage_gauge.state == 2
                && (v80 = get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x),
                    is_slide_cache_tile_family(v80)) )
              {
                _EAX = _EBP->game;
                __asm
                {
                  fld     dword ptr [eax+38h]
                  fld     st
                  fmul    st, st(1)
                  fmul    ds:flt_4973BC
                  fadd    st, st
                  fadd    dword ptr [ebp+418h]
                  fstp    dword ptr [ebp+418h]
                }
                _EBP->velocity.z = _ET1;
                _ECX = _EBP->game;
                __asm
                {
                  fstp    st
                  fild    dword ptr [ecx+50h]
                  fcomp   dword ptr [ebp+70h]
                  fnstsw  ax
                }
                if ( (BYTE1(_EAX) & 0x41) != 0 )
                {
                  __asm
                  {
                    fld     dword ptr [ebp+70h]
                    fcomp   dword ptr [ebp+2738h]
                    fnstsw  ax
                  }
                  if ( (_AX & 0x4100) == 0 )
                  {
                    __asm
                    {
                      fld     dword ptr [ebp+70h]
                      fadd    ds:flt_497220
                      fstp    dword ptr [ebp+2738h]
                    }
                    *(float *)_EBP->_pad_2738 = _ET1;
                  }
                }
              }
            }
            if ( _EBP->jetpack_gauge.state == 1 )
            {
              _EDX = _EBP->game;
              __asm
              {
                fld     dword ptr [edx+38h]
                fld     st
                fmul    st, st(1)
                fmul    ds:flt_4973BC
                fadd    st, st
                fadd    dword ptr [ebp+418h]
                fstp    dword ptr [ebp+418h]
              }
              _EBP->velocity.z = _ET1;
              __asm { fstp    st }
            }
            if ( !_EBP->_pad_1cc[24] )
            {
              _EAX = _EBP->game;
              __asm
              {
                fld     dword ptr [eax+38h]
                fmul    ds:flt_4975D0
                fsubr   ds:flt_497220
                fmul    dword ptr [ebp+418h]
                fstp    dword ptr [ebp+418h]
              }
              _EBP->velocity.z = _ET1;
            }
            _ECX = _EBP->game;
            __asm
            {
              fld     dword ptr [ecx+38h]
              fmul    ds:flt_4975D0
              fsubr   ds:flt_497220
              fmul    dword ptr [ebp+414h]
              fstp    dword ptr [ebp+414h]
            }
            _EBP->velocity.y = _ET1;
            _EDX = _EBP->game;
            __asm
            {
              fld     dword ptr [edx+38h]
              fmul    ds:flt_497258
              fsubr   ds:flt_497220
              fmul    dword ptr [ebp+410h]
              fstp    dword ptr [ebp+410h]
            }
            _EBP->velocity.x = _ET1;
            if ( _EBP->_pad_41c[0] )
            {
              _EAX = _EBP->game;
              __asm
              {
                fld     dword ptr [eax+38h]
                fld     st
                fmul    st, st(1)
                fmul    ds:flt_4973BC
                fadd    st, st
                fadd    dword ptr [ebp+418h]
                fstp    dword ptr [ebp+418h]
              }
              _EBP->velocity.z = _ET1;
              _EBP->attachment_exit_pending = 0;
              __asm { fstp    st }
            }
            else
            {
              v96 = get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x);
              if ( _EBP->attachment_exit_pending )
              {
                _EDI = _EBP->game;
                if ( (*(_DWORD *)&byte_5CCAC8[(_DWORD)_EDI + 244 * get_track_cell_row_index(v96)] & 0x100) == 0
                  && !_EBP->jetpack_gauge.state
                  && !_EBP->control_override_active )
                {
                  __asm
                  {
                    fld     dword ptr [edi+38h]
                    fmul    ds:flt_497270
                    fsubr   ds:flt_497220
                    fmul    dword ptr [ebp+418h]
                    fstp    dword ptr [ebp+418h]
                  }
                  _EBP->velocity.z = _ET1;
                }
                if ( (byte_5CCAC8[(unsigned int)_EBP->game + 244 * get_track_cell_row_index(v96)] & 0x40) != 0 )
                {
                  __asm
                  {
                    fld     dword ptr [ebp+410h]
                    fmul    ds:flt_4975C8
                  }
                  __asm
                  {
                    fstp    [esp+50h+var_3C]
                    fld     dword ptr [ebp+414h]
                    fmul    ds:flt_4975C8
                    fstp    [esp+50h+var_38]
                    fld     dword ptr [ebp+418h]
                    fmul    ds:flt_4975C8
                    fstp    [esp+50h+var_34]
                  }
                  v240 = *(int *)((char *)unk_5CCB6C + (unsigned int)_EBP->game + 244 * get_track_cell_row_index(v96));
                  x = _EBX->x;
                  y = _EBX->y;
                  z = _EBX->z;
                  track_cell_row_index = get_track_cell_row_index(v96);
                  try_enter_track_attachment_from_swept_motion(
                    *(_DWORD **)(*(int *)((char *)unk_5CCB6C + (unsigned int)_EBP->game + 244 * track_cell_row_index)
                               + 56),
                    x,
                    y,
                    z,
                    v253,
                    v256,
                    v259,
                    v240);
                }
                if ( _EBP->attachment_exit_pending
                  && byte_5CCAC8[(unsigned int)_EBP->game + 244 * get_track_cell_row_index(v96)] < 0 )
                {
                  __asm
                  {
                    fld     dword ptr [ebp+410h]
                    fmul    ds:flt_4975C8
                  }
                  __asm
                  {
                    fstp    [esp+50h+var_3C]
                    fld     dword ptr [ebp+414h]
                    fmul    ds:flt_4975C8
                    fstp    [esp+50h+var_38]
                    fld     dword ptr [ebp+418h]
                    fmul    ds:flt_4975C8
                    fstp    [esp+50h+var_34]
                  }
                  v241 = *(int *)((char *)unk_5CCB70 + (unsigned int)_EBP->game + 244 * get_track_cell_row_index(v96));
                  v234 = _EBX->x;
                  v236 = _EBX->y;
                  v238 = _EBX->z;
                  v100 = get_track_cell_row_index(v96);
                  try_enter_track_attachment_from_swept_motion(
                    *(_DWORD **)(*(int *)((char *)unk_5CCB70 + (unsigned int)_EBP->game + 244 * v100) + 56),
                    v234,
                    v236,
                    v238,
                    v254,
                    v257,
                    v260,
                    v241);
                }
              }
              if ( !_EBP->follow_state.active )
              {
                __asm
                {
                  fld     dword ptr [ebp+6Ch]
                  fcomp   ds:flt_4973E8
                }
                __asm { fnstsw  ax }
                if ( (_AX & 0x100) != 0 )
                {
                  __asm
                  {
                    fld     dword ptr [ebp+6Ch]
                    fcomp   ds:flt_4975C4
                    fnstsw  ax
                  }
                  if ( (_AX & 0x4100) == 0 && !is_open_neighbor_tile_family(v96) && v96[60] != 22 )
                  {
                    set_matrix_rotation_identity((TransformMatrix *)&_EBP->_pad_00[56]);
                    _EBP->_pad_1cc[24] = 0;
                    __asm
                    {
                      fld     dword ptr [ebp+414h]
                      fcomp   ds:flt_4975C0
                      fnstsw  ax
                    }
                    if ( (_AX & 0x100) != 0 )
                    {
                      __asm
                      {
                        fld     dword ptr [ebp+414h]
                        fsub    ds:flt_497548
                      }
                      __asm { fstp    [esp+54h+var_54]; float }
                      start_squidge_y(&_EBP->squidge, v242);
                    }
                    __asm
                    {
                      fld     dword ptr [ebp+414h]
                      fcomp   ds:flt_497234
                      fnstsw  ax
                    }
                    if ( (_AX & 0x4100) != 0 )
                    {
                      _EBP->position.y = 0.49000001;
                      _EBP->velocity.y = 0.0;
                    }
                    _EBP->attachment_exit_pending = 0;
                  }
                }
                v105 = v96[60];
                if ( !v105 || v105 == 35 )
                {
                  __asm
                  {
                    fld     dword ptr [ebp+6Ch]
                    fcomp   ds:flt_4973E8
                    fnstsw  ax
                  }
                  if ( (_AX & 0x100) != 0 )
                  {
                    __asm
                    {
                      fld     dword ptr [ebp+414h]
                      fcomp   ds:flt_497234
                      fnstsw  ax
                    }
                    if ( (_AX & 0x4100) != 0 )
                    {
                      __asm { fld     dword ptr [ebp+70h] }
                      v247 = _ftol(v17);
                      v108 = v96[61];
                      __asm { fild    [esp+50h+var_40] }
                      __asm { fsubr   dword ptr [ebp+70h] }
                      if ( (v108 & 2) != 0 )
                        __asm { fld     ds:flt_497250 }
                      else
                        __asm { fld     ds:flt_497220 }
                      v248 = 0;
                      if ( (v108 & 1) != 0 )
                        v248 = 1045220557;
                      __asm
                      {
                        fld     st(1)
                        fcomp   st(1)
                        fnstsw  ax
                      }
                      __asm { fstp    st }
                      if ( (_AX & 0x100) != 0 )
                      {
                        __asm
                        {
                          fcomp   [esp+50h+var_40]
                          fnstsw  ax
                        }
                        if ( (_AX & 0x4100) == 0 && !_EBP->attachment_exit_pending )
                          initialize_subgoldy_fall_state((int)_EBP);
                      }
                      else
                      {
                        __asm { fstp    st }
                      }
                    }
                  }
                }
                v111 = _EBP->game;
                if ( *((_DWORD *)v111 + 16) == 3 )
                  get_track_grid_cell_at_world_position((char *)v111, &_EBX->x);
                if ( (*((_DWORD *)_EBP->game + 19) & 0x400) == 0 || (byte_4B2F40 & 2) != 0 )
                {
                  __asm
                  {
                    fld     dword ptr [ebp+6Ch]
                    fcomp   ds:flt_4973E8
                    fnstsw  ax
                  }
                  if ( (_AX & 0x100) != 0 )
                  {
                    start_squidge_y(&_EBP->squidge, _EBP->velocity.y);
                    _EBP->_pad_1cc[24] = 0;
                    _EBP->velocity.y = 0.0;
                    _EBP->attachment_exit_pending = 0;
                    _EBP->position.y = 0.49000001;
                  }
                }
                __asm
                {
                  fld     dword ptr [ebp+6Ch]
                  fcomp   ds:flt_4975BC
                  fnstsw  ax
                }
                if ( (_AX & 0x100) != 0 && !_EBP->_pad_74[16] )
                  initialize_subgoldy_death(_EBP);
              }
            }
            __asm
            {
              fld     dword ptr [ebp+1DCh]
              fcomp   ds:flt_497234
              fnstsw  ax
            }
            if ( (_AX & 0x4000) == 0 )
            {
              __asm
              {
                fld     dword ptr [ebp+1E0h]
                fadd    dword ptr [ebp+1DCh]
                fst     dword ptr [ebp+1DCh]
              }
              *(float *)&_EBP->_pad_1cc[16] = _ET1;
              __asm
              {
                fcomp   ds:flt_497220
                fnstsw  ax
              }
              if ( (_AX & 0x4100) == 0 )
                *(_DWORD *)&_EBP->_pad_1cc[16] = 0;
            }
            if ( _EBP->attachment_exit_pending )
            {
              _EAX = _EBP->game;
              __asm
              {
                fld     dword ptr [eax+38h]
                fld     st
                fmul    st, st(1)
                fmul    ds:flt_4975CC
                fadd    dword ptr [ebp+414h]
                fstp    dword ptr [ebp+414h]
              }
              _EBP->velocity.y = _ET1;
              __asm { fstp    st }
              _ESI = get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x);
              if ( _ESI[60] == 22 )
              {
                __asm
                {
                  fld     dword ptr [esi+14h]
                  fadd    ds:flt_4973E8
                  fcomp   dword ptr [ebp+6Ch]
                  fnstsw  ax
                }
                if ( (_AX & 0x4100) == 0 )
                {
                  __asm
                  {
                    fld     dword ptr [esi+14h]
                    fsub    ds:flt_4973E8
                    fcomp   dword ptr [ebp+6Ch]
                    fnstsw  ax
                  }
                  if ( (_AX & 0x100) != 0 )
                  {
                    start_squidge_y(&_EBP->squidge, _EBP->velocity.y);
                    _EDX = _EBP->game;
                    __asm
                    {
                      fld     dword ptr [edx+38h]
                      fmul    ds:flt_4973D8
                      fstp    dword ptr [ebp+414h]
                    }
                    _EBP->velocity.y = _ET1;
                    __asm
                    {
                      fld     dword ptr [esi+14h]
                      fadd    ds:flt_4973E8
                      fstp    dword ptr [ebp+6Ch]
                    }
                    _EBP->position.y = _ET1;
                    _EBP->attachment_exit_pending = 0;
                    _EBP->_pad_1cc[24] = 1;
                    play_sound_effect(41);
                  }
                }
              }
            }
            else
            {
              v17 = sample_track_floor_height_at_position((char *)_EBP->game, &_EBX->x);
              __asm
              {
                fadd    ds:flt_4973E8
                fcom    dword ptr [ebp+6Ch]
                fnstsw  ax
              }
              if ( (_AX & 0x4100) != 0 )
              {
                _EDX = _EBP->game;
                __asm
                {
                  fstp    st
                  fld     dword ptr [edx+38h]
                  fld     st
                  fmul    st, st(1)
                  fmul    ds:flt_4975CC
                  fadd    dword ptr [ebp+414h]
                  fstp    dword ptr [ebp+414h]
                }
                _EBP->velocity.y = _ET1;
                __asm { fstp    st }
              }
              else
              {
                __asm
                {
                  fld     dword ptr [ebp+414h]
                  fcomp   ds:flt_497234
                  fnstsw  ax
                }
                if ( (_AX & 0x4100) != 0 )
                {
                  __asm { fstp    dword ptr [ebp+6Ch] }
                  _EBP->position.y = _ET1;
                }
                else
                {
                  __asm { fstp    st }
                }
                if ( get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 8
                  || get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 9
                  || get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 10
                  || get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 11
                  || get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 12
                  || get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 13 )
                {
                  _ECX = _EBP->game;
                  __asm
                  {
                    fld     dword ptr [ecx+38h]
                    fmul    ds:flt_4973D8
                    fstp    dword ptr [ebp+414h]
                  }
                  _EBP->velocity.y = _ET1;
                }
                else if ( get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 2
                       || get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 3
                       || get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 4
                       || get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 5
                       || get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 6
                       || get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 7 )
                {
                  __asm
                  {
                    fld     dword ptr [ebp+1DCh]
                    fcomp   ds:flt_497234
                    fnstsw  ax
                  }
                  if ( (_AX & 0x4000) != 0 )
                    *(_DWORD *)&_EBP->_pad_1cc[16] = *(_DWORD *)&_EBP->_pad_1cc[20];
                  _EAX = _EBP->game;
                  __asm
                  {
                    fld     dword ptr [eax+38h]
                    fmul    ds:flt_497270
                    fstp    dword ptr [ebp+414h]
                  }
                  _EBP->velocity.y = _ET1;
                  if ( !_EBP->control_override_active )
                  {
                    __asm
                    {
                      fld     dword ptr [ebx]
                      fcomp   ds:flt_497234
                    }
                    __asm { fnstsw  ax }
                    if ( (_AX & 0x4100) != 0 )
                      dispatch_cutscene_animation((int)_EBP->_pad_2984, 3, 1, -1);
                    else
                      dispatch_cutscene_animation((int)_EBP->_pad_2984, 4, 1, -1);
                    dispatch_cutscene_animation((int)_EBP->_pad_2984, 1, 0, -1);
                  }
                }
                else if ( get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60]
                       && get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] != 35
                       && get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] != 22 )
                {
                  _EBP->_pad_1cc[24] = 0;
                  _EBP->velocity.y = 0.0;
                }
              }
              __asm
              {
                fld     dword ptr [ebp+6Ch]
                fcomp   ds:flt_497234
                fnstsw  ax
              }
              if ( (_AX & 0x100) != 0 )
              {
                __asm
                {
                  fld     dword ptr [ebp+414h]
                  fcomp   ds:flt_497234
                  fnstsw  ax
                }
                if ( (_AX & 0x4100) != 0 )
LABEL_99:
                  initialize_subgoldy_fall_state((int)_EBP);
              }
            }
          }
          update_warning((float *)&_EBP->_pad_3f0[4]);
          if ( _EBP->_pad_41c[0] )
            goto LABEL_218;
          if ( _EBP->follow_state.active )
            goto LABEL_218;
          __asm
          {
            fld     dword ptr [ebx+8]
            fadd    ds:flt_4973E8
          }
          v138 = _EBX->y;
          __asm { fstp    [esp+50h+var_34] }
          v262 = _EBX->x;
          v264 = v261;
          v139 = (char *)_EBP->game;
          v263 = v138;
          if ( get_track_grid_cell_at_world_position(v139, &v262)[60] != 14 )
            goto LABEL_218;
          __asm
          {
            fld     dword ptr [ebp+6Ch]
            fcomp   ds:flt_4975B8
            fnstsw  ax
          }
          if ( (_AX & 0x100) == 0 )
          {
LABEL_218:
            *(_DWORD *)&_EBP->_pad_30c[28] = 0;
          }
          else
          {
            _EBP->velocity.z = 0.0;
            __asm
            {
              fld     dword ptr [ebp+70h]
              fadd    ds:flt_4973E8
            }
            v249 = _ftol(v17);
            __asm
            {
              fild    [esp+50h+var_40]
              fsub    ds:flt_497228
              fstp    dword ptr [ebp+70h]
            }
            _EBP->position.z = _ET1;
            __asm
            {
              fld     dword ptr [ebp+4350h]
              fcomp   ds:flt_497234
              fnstsw  ax
            }
            if ( (_AX & 0x4000) != 0 )
              play_sound_effect(47);
            start_squidge_z(&_EBP->squidge, -0.33000001);
            __asm
            {
              fld     dword ptr [ebp+32Ch]
              fadd    dword ptr [ebp+328h]
              fst     dword ptr [ebp+328h]
            }
            *(float *)&_EBP->_pad_30c[28] = _ET1;
            __asm
            {
              fcomp   ds:flt_497220
              fnstsw  ax
            }
            if ( (_AX & 0x4100) == 0 )
            {
              *(_DWORD *)&_EBP->_pad_30c[28] = 0;
              if ( !_EBP->attachment_exit_pending )
                initialize_subgoldy_fall_state((int)_EBP);
            }
          }
          if ( !*(_DWORD *)&_EBP->_pad_340[16]
            && (get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 2
             || get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 4
             || get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 5
             || get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 7
             || get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 10
             || get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 8
             || get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 10
             || get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 11
             || get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 13)
            && !_EBP->attachment_exit_pending )
          {
            __asm
            {
              fld     dword ptr [ebp+6Ch]
              fcomp   ds:flt_49756C
              fnstsw  ax
            }
            if ( (_AX & 0x4100) != 0 )
            {
              _EAX = _EBP->game;
              __asm
              {
                fld     dword ptr [eax+38h]
                fmul    ds:flt_4975B4
                fstp    dword ptr [ebp+35Ch]
              }
              *(float *)&_EBP->_pad_340[28] = _ET1;
              if ( get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 2
                || get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 5
                || get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 8
                || get_track_grid_cell_at_world_position((char *)_EBP->game, &_EBX->x)[60] == 11 )
              {
                *(_DWORD *)&_EBP->_pad_340[16] = 1;
                *(_DWORD *)&_EBP->_pad_340[20] = 1065353216;
              }
              else
              {
                *(_DWORD *)&_EBP->_pad_340[16] = 2;
                *(_DWORD *)&_EBP->_pad_340[20] = -1082130432;
              }
            }
          }
          __asm
          {
            fld     dword ptr [ebp+1D4h]
            fcomp   ds:flt_497234
            fnstsw  ax
          }
          if ( (_AX & 0x4000) == 0 )
          {
            __asm
            {
              fld     dword ptr [ebp+1D8h]
              fadd    dword ptr [ebp+1D4h]
              fst     dword ptr [ebp+1D4h]
            }
            *(float *)&_EBP->_pad_1cc[8] = _ET1;
            __asm
            {
              fcomp   ds:flt_497220
              fnstsw  ax
            }
            if ( (_AX & 0x4100) == 0 )
              *(_DWORD *)&_EBP->_pad_1cc[8] = 0;
          }
          _ECX = _EBP->game;
          __asm
          {
            fild    dword ptr [ecx+58h]
            fstp    [esp+50h+var_40]
            fld     dword ptr [ebp+70h]
            fcomp   [esp+50h+var_40]
            fnstsw  ax
          }
          if ( (_AX & 0x100) != 0 || _EBP->attachment_exit_pending )
          {
            if ( !_EBP->_pad_41c[0] && !_EBP->control_override_active )
            {
              __asm
              {
                fld     dword ptr [ecx+38h]
                fmul    ds:flt_4975B0
                fld     dword ptr [ebp+418h]
                fcomp   st(1)
                fnstsw  ax
              }
              if ( (_AX & 0x100) == 0 )
              {
                __asm
                {
                  fstp    st
                  fld     dword ptr [ecx+38h]
                  fmul    ds:flt_497228
                  fld     dword ptr [ebp+418h]
                  fcomp   st(1)
                  fnstsw  ax
                }
                if ( (_AX & 0x4100) != 0 )
                {
                  __asm
                  {
                    fstp    st
                    fld     dword ptr [ebp+418h]
                  }
                }
              }
              __asm { fstp    dword ptr [ebp+418h] }
              _EBP->velocity.z = _ET1;
            }
          }
          else
          {
            if ( !LOBYTE(_EBP->completion_handoff_active) )
            {
              if ( *((_DWORD *)_ECX + 16) == 4 )
              {
                __asm
                {
                  fld     dword ptr [ebp+70h]
                  fsub    [esp+50h+var_40]
                }
                __asm
                {
                  fdiv    dword ptr [ebp+418h]
                  fsubr   ds:flt_497220
                  fmul    ds:flt_4972C8
                  fstp    [esp+54h+var_54]; float
                }
                advance_timer_counters((float *)&_EBP->_pad_2e4[4], v243);
              }
              _ECX = _EBP->game;
              _EBP->completion_handoff_timer = 0.0;
              _EBP->completion_handoff_timer_step = 0.016666668;
              _EBP->completion_handoff_voice_gate = 0;
              __asm
              {
                fld     dword ptr [ecx+38h]
                fmul    ds:flt_4975B0
                fld     dword ptr [ebp+418h]
                fcomp   st(1)
                fnstsw  ax
              }
              if ( (_AX & 0x100) == 0 )
              {
                __asm
                {
                  fstp    st
                  fld     dword ptr [ecx+38h]
                  fmul    ds:flt_497228
                  fld     dword ptr [ebp+418h]
                  fcomp   st(1)
                  fnstsw  ax
                }
                if ( (_AX & 0x4100) != 0 )
                {
                  __asm
                  {
                    fstp    st
                    fld     dword ptr [ebp+418h]
                  }
                }
              }
              __asm { fstp    dword ptr [ebp+418h] }
              _EBP->velocity.z = _ET1;
              reset_voice_manager(unk_751498);
              end_jetpack_hover(&_EBP->jetpack_gauge.progress);
              *(_DWORD *)&_EBP->_pad_29ac[6460] = 5;
              play_sound_effect(0);
              _EBP->_pad_41c[0] = 0;
            }
            LOBYTE(_EBP->completion_handoff_active) = 1;
            _ECX = _EBP->game;
            __asm
            {
              fild    dword ptr [ecx+58h]
              fadd    ds:flt_4973CC
              fcomp   dword ptr [ebp+70h]
              fnstsw  ax
            }
            if ( (_AX & 0x100) != 0 )
            {
              __asm
              {
                fld     dword ptr [ecx+38h]
                fld     st
                fmulp   st(1), st
                fmul    ds:flt_4973BC
                fadd    st, st
                fsubr   dword ptr [ebp+418h]
                fst     dword ptr [ebp+418h]
              }
              _EBP->velocity.z = _ET1;
              __asm
              {
                fcomp   ds:flt_497234
                fnstsw  ax
              }
              if ( (_AX & 0x100) != 0 )
                _EBP->velocity.z = 0.0;
            }
            __asm
            {
              fld     dword ptr [ebp+2748h]
              fadd    dword ptr [ebp+2744h]
              fst     dword ptr [ebp+2744h]
            }
            *(float *)_EBP->_pad_2744 = _ET1;
            __asm
            {
              fcomp   ds:flt_497220
              fnstsw  ax
            }
            if ( (_AX & 0x4100) == 0 )
              *(_DWORD *)_EBP->_pad_2744 = 0;
            __asm
            {
              fld     dword ptr [ebp+444h]
              fadd    dword ptr [ebp+448h]
            }
            v163 = _EBP->game;
            __asm { fstp    dword ptr [ebp+444h] }
            _EBP->completion_handoff_timer = _ET1;
            *((_DWORD *)v163 + 4834290) = 2;
            __asm
            {
              fld     dword ptr [ebp+444h]
              fcomp   ds:flt_4974A4
              fnstsw  ax
            }
            if ( (_AX & 0x4100) == 0 && !_EBP->completion_handoff_voice_gate )
            {
              _EBP->completion_handoff_voice_gate = 1;
              play_voice_manager((int)unk_751498, 8, 2u, -1);
            }
            __asm
            {
              fld     dword ptr [ebp+444h]
              fcomp   ds:flt_4974A4
              fnstsw  ax
            }
            if ( (_AX & 0x4100) == 0 )
            {
              v167 = _EBP->game;
              if ( *((_DWORD *)v167 + 16) <= 1u )
              {
                if ( *((_BYTE *)v167 + 19343344) == 1 && (_EBP->control_source->control_flags_a & 0x4000) != 0 )
                  _EBP->completion_handoff_timer = 5.0999999;
                if ( *((_DWORD *)v167 + 4835835) == 5 )
                  _EBP->completion_handoff_timer = 5.0999999;
              }
            }
            __asm
            {
              fld     dword ptr [ebp+444h]
              fcomp   ds:flt_497288
              fnstsw  ax
            }
            if ( (_AX & 0x4100) == 0 )
            {
              v169 = _EBP->game;
              if ( *((_DWORD *)v169 + 16) <= 1u && *((_DWORD *)v169 + 4835835) != 5 )
              {
                __asm
                {
                  fld     dword ptr [ebp+444h]
                  fsub    dword ptr [ebp+448h]
                  fstp    dword ptr [ebp+444h]
                }
                _EBP->completion_handoff_timer = _ET1;
              }
            }
            __asm
            {
              fld     dword ptr [ebp+444h]
              fcomp   ds:flt_497288
              fnstsw  ax
            }
            if ( (_AX & 0x4100) == 0 )
            {
              v172 = *((_DWORD *)MEMORY[0x4DF904] + 9);
              if ( !v172 )
              {
                begin_frontend_fade_out((_DWORD *)MEMORY[0x4DF904] + 9, 0);
                goto LABEL_290;
              }
              if ( v172 == 4 )
              {
                v173 = _EBP->game;
                if ( *((_DWORD *)v173 + 4835835) )
                  flush_row_event_display((_DWORD *)v173 + 4835830);
                v174 = (int)_EBP->game;
                if ( *(_DWORD *)(v174 + 64) )
                {
                  complete_subgame(v174, 1);
                }
                else
                {
                  if ( *(_DWORD *)(v174 + 68) == *((_DWORD *)MEMORY[0x4DF904] + 4936081) - 1 )
                  {
                    complete_subgame(v174, 1);
                    *((_DWORD *)MEMORY[0x4DF904] + 111) = 29;
                    *((_DWORD *)MEMORY[0x4DF904] + 110) = 26;
                    return result;
                  }
                  complete_subgame(v174, 0);
                  result = (int32_t)_EBP->game;
                  *(_DWORD *)(result + 19337160) = 1;
                }
                v175 = _EBP->game;
                if ( *((_DWORD *)v175 + 16) == 7 )
                {
                  *((_DWORD *)MEMORY[0x4DF904] + 110) = 26;
                  *((_DWORD *)MEMORY[0x4DF904] + 111) = 2;
                }
                else
                {
                  v176 = *((_BYTE *)v175 + 16721361) == 0;
                  result = (int32_t)MEMORY[0x4DF904];
                  *((_DWORD *)MEMORY[0x4DF904] + 111) = *((_DWORD *)MEMORY[0x4DF904] + 110);
                  if ( v176 )
                    *((_DWORD *)MEMORY[0x4DF904] + 110) = 27;
                  else
                    *((_DWORD *)MEMORY[0x4DF904] + 110) = 26;
                }
                return result;
              }
            }
          }
LABEL_290:
          v269 = _EBX->x;
          v270 = _EBX->y;
          v271 = _EBX->z;
          if ( _EBP->follow_state.active == 1 )
          {
            _EBX->x = _EBP->follow_state.output_position.x;
            _EBX->y = _EBP->follow_state.output_position.y;
            _EBX->z = _EBP->follow_state.output_position.z;
          }
          update_jetpack_gauge((int)&_EBP->jetpack_gauge);
          if ( LOBYTE(_EBP->completion_handoff_active) )
          {
            qmemcpy((char *)MEMORY[0x4DF904] + 716, (char *)MEMORY[0x4DF904] + 348, 0x40u);
            _EAX = (float *)MEMORY[0x4DF904];
            __asm
            {
              fld     dword ptr [eax+300h]
              fsub    ds:flt_497220
              fstp    dword ptr [eax+300h]
            }
            _EAX[192] = _ET1;
          }
          update_damage_gauge((int)&_EBP->damage_gauge);
          update_progress_bar();
          __asm { fld     dword ptr [ebp+276Ch] }
          _ECX = &_EBP->cached_camera_target_world.x;
          __asm { fld     st }
          _EBP->cached_camera_target_world.x = _EBX->x;
          v183 = _EBX->z;
          _EBP->cached_camera_target_world.y = _EBX->y;
          _EBP->cached_camera_target_world.z = v183;
          __asm
          {
            fmul    dword ptr [ebp+58h]
            fstp    [esp+50h+var_18]
            fld     st
            fmul    dword ptr [ebp+5Ch]
            fstp    [esp+50h+var_14]
            fmul    dword ptr [ebp+60h]
            fld     dword ptr [ebp+2768h]
            fld     st
            fmul    dword ptr [ebp+48h]
            fstp    [esp+50h+var_3C]
            fld     st
            fmul    dword ptr [ebp+4Ch]
            fstp    [esp+50h+var_38]
            fmul    dword ptr [ebp+50h]
            fld     dword ptr [ebp+2764h]
            fld     st
            fmul    dword ptr [ebp+38h]
            fstp    [esp+50h+var_30]
            fld     st
            fmul    dword ptr [ebp+3Ch]
            fstp    [esp+50h+var_2C]
            fmul    dword ptr [ebp+40h]
            fld     [esp+50h+var_30]
            fadd    [esp+50h+var_3C]
            fstp    [esp+50h+var_24]
            fld     [esp+50h+var_2C]
            fadd    [esp+50h+var_38]
            fstp    [esp+50h+var_20]
            faddp   st(1), st
            fld     [esp+50h+var_24]
            fadd    [esp+50h+var_18]
            fstp    [esp+50h+var_30]
            fld     [esp+50h+var_20]
            fadd    [esp+50h+var_14]
            fstp    [esp+50h+var_2C]
            faddp   st(1), st
            fld     [esp+50h+var_30]
            fadd    dword ptr [eax]
            fstp    dword ptr [eax]
          }
          *_ECX = _ET1;
          __asm
          {
            fld     [esp+50h+var_2C]
            fadd    dword ptr [eax+4]
            fstp    dword ptr [eax+4]
          }
          _ECX[1] = _ET1;
          __asm
          {
            fadd    dword ptr [eax+8]
            fstp    dword ptr [eax+8]
          }
          _ECX[2] = _ET1;
          skin_hold_ticks = _EBP->damage_gauge.skin_hold_ticks;
          if ( skin_hold_ticks > 0 )
            _EBP->damage_gauge.skin_hold_ticks = skin_hold_ticks - 1;
          if ( _EBP->follow_state.active == 1 )
            _EBX->x = v269;
          _ECX = _EBP->game;
          __asm
          {
            fld     dword ptr [ecx+38h]
            fmul    ds:flt_4975B4
            fst     dword ptr [ebp+35Ch]
          }
          *(float *)&_EBP->_pad_340[28] = _ET1;
          if ( *(_DWORD *)&_EBP->_pad_340[16] )
          {
            __asm
            {
              fadd    dword ptr [ebp+358h]
              fst     dword ptr [ebp+358h]
            }
            *(float *)&_EBP->_pad_340[24] = _ET1;
            __asm
            {
              fcomp   ds:flt_497220
              fnstsw  ax
            }
            if ( (_AX & 0x4100) == 0 )
            {
              *(_DWORD *)&_EBP->_pad_340[24] = 0;
              *(_DWORD *)&_EBP->_pad_340[16] = 0;
            }
          }
          else
          {
            __asm { fstp    st }
          }
          if ( *(_DWORD *)&_EBP->_pad_340[32] )
          {
            __asm
            {
              fld     dword ptr [ebp+36Ch]
              fadd    dword ptr [ebp+368h]
              fst     dword ptr [ebp+368h]
            }
            *(float *)&_EBP->_pad_340[40] = _ET1;
            __asm
            {
              fcomp   ds:flt_497220
              fnstsw  ax
            }
            if ( (_AX & 0x4100) == 0 )
            {
              *(_DWORD *)&_EBP->_pad_340[40] = 0;
              *(_DWORD *)&_EBP->_pad_340[32] = 0;
            }
          }
          _EDX = _EBP->game;
          __asm
          {
            fld     dword ptr [edx+38h]
            fmul    ds:flt_4975AC
            fst     dword ptr [ebp+378h]
          }
          *(float *)&_EBP->_pad_340[56] = _ET1;
          __asm
          {
            fld     dword ptr [ebp+374h]
            fcomp   ds:flt_497234
            fnstsw  ax
          }
          if ( (_AX & 0x4100) != 0 )
          {
            __asm { fstp    st }
          }
          else
          {
            __asm
            {
              fadd    dword ptr [ebp+374h]
              fst     dword ptr [ebp+374h]
            }
            *(float *)&_EBP->_pad_340[52] = _ET1;
            __asm
            {
              fcomp   ds:flt_497220
              fnstsw  ax
            }
            if ( (_AX & 0x4100) != 0 )
            {
              update_nuke(&_EBP->nuke);
            }
            else
            {
              *(_DWORD *)&_EBP->_pad_340[52] = 0;
              uninit_nuke(&_EBP->nuke);
            }
          }
          v199 = _EBP->game;
          if ( *((_DWORD *)v199 + 16) == 4 )
          {
            v200 = (char *)v199 + 129728 * *((_DWORD *)v199 + 17);
            if ( *((_DWORD *)v200 + 2429012) == 1 && !*((_BYTE *)v199 + 16721360) )
            {
              v201 = *((_DWORD *)v199 + 4180343);
              if ( v201 >= *((_DWORD *)v200 + 2429039) )
                v201 = *((_DWORD *)v200 + 2429039);
              v202 = *(_DWORD *)&_EBP->_pad_2e4[32];
              if ( v202 && (v203 = *((_DWORD *)v200 + 2429021) - v202 + v201) != 0 )
              {
                convert_math_type16_to_32(*(_WORD *)&v200[6 * v203 + 9716162], 32.0);
                __asm { fadd    flt_643190 }
              }
              else
              {
                convert_math_type16_to_32(*((_WORD *)v200 + 4858081), 32.0);
              }
              __asm { fstp    flt_643190 }
              if ( *((_BYTE *)_EBP->game + 16721360) )
                flt_643190 = _EBP->position.z;
              __asm
              {
                fld     dword ptr [ebp+70h]
                fadd    ds:flt_497448
                fld     flt_643190
                fcomp   st(1)
                fnstsw  ax
              }
              if ( (_AX & 0x100) != 0 )
              {
                __asm { fstp    st }
                mark_current_track_pair_with_payload(_EBP, SLODWORD(flt_643190));
              }
              else
              {
                __asm { fstp    [esp+50h+var_40] }
                mark_current_track_pair_with_payload(_EBP, v251);
              }
            }
          }
          _EDX = _EBP->game;
          __asm { fild    dword ptr [edx+54h] }
          __asm
          {
            fdivr   dword ptr [ebp+70h]
            fstp    [esp+54h+var_54]
          }
          set_backdrop_progress_fraction((_DWORD *)MEMORY[0x4DF904] + 80644, v244);
          _ECX = _EBP->game;
          __asm
          {
            fild    dword ptr [ecx+58h]
            fsub    ds:flt_4972C0
            fld     dword ptr [ebp+70h]
            fsub    ds:flt_49720C
            fstp    [esp+50h+var_40]
            fcom    [esp+50h+var_40]
            fnstsw  ax
          }
          if ( (_AX & 0x100) == 0 )
          {
            __asm
            {
              fstp    st
              fld     [esp+50h+var_40]
            }
          }
          state = _EBP->jetpack_gauge.state;
          __asm { fstp    dword ptr [ebp+2980h] }
          _EBP->interaction_max_z = _ET1;
          if ( state == 1 )
          {
            __asm
            {
              fld     dword ptr [ebp+6Ch]
              fcomp   ds:flt_497220
              fnstsw  ax
            }
            if ( (_AX & 0x100) != 0 )
            {
              __asm
              {
                fld     dword ptr [ebp+414h]
                fmul    ds:flt_49726C
                fst     dword ptr [ebp+414h]
              }
              _EBP->velocity.y = _ET1;
              _EDX = _EBP->game;
              __asm
              {
                fld     dword ptr [edx+38h]
                fld     st
                fmul    st, st(1)
                fmul    ds:flt_4975CC
                fsubr   st, st(2)
                fstp    dword ptr [ebp+414h]
              }
              _EBP->velocity.y = _ET1;
              __asm
              {
                fstp    st
                fstp    st
              }
            }
            _EBP->attachment_exit_pending = 0;
          }
          if ( _EBP->attachment_exit_pending )
          {
            __asm
            {
              fld     dword ptr [ebp+438h]
              fadd    dword ptr [ebp+434h]
              fst     dword ptr [ebp+434h]
            }
            _EBP->attachment_exit_progress = _ET1;
            __asm
            {
              fcomp   ds:flt_497200
              fnstsw  ax
            }
            if ( (_AX & 0x4100) == 0 && !_EBP->attachment_exit_gate_a )
            {
              play_voice_manager((int)unk_751498, 3, 0, -1);
              control_override_active = _EBP->control_override_active;
              _EBP->attachment_exit_gate_a = 1;
              if ( !control_override_active )
              {
                __asm
                {
                  fld     dword ptr [ebp+6Ch]
                  fcomp   ds:flt_4975A8
                  fnstsw  ax
                }
                if ( (_AX & 0x100) != 0 )
                  dispatch_cutscene_animation((int)_EBP->_pad_2984, 5, 1, -1);
              }
            }
            __asm
            {
              fld     dword ptr [ebp+6Ch]
              fcomp   ds:flt_4975BC
              fnstsw  ax
            }
            if ( (_AX & 0x100) != 0 && !_EBP->attachment_exit_gate_b )
            {
              play_voice_manager((int)unk_751498, 1, 2u, -1);
              _EBP->attachment_exit_gate_b = 1;
              _EBP->attachment_exit_gate_a = 1;
            }
          }
          __asm
          {
            fld     dword ptr [ebp+330h]
            fcomp   ds:flt_497234
            fnstsw  ax
          }
          if ( (_AX & 0x4100) == 0 )
          {
            __asm
            {
              fld     dword ptr [ebp+334h]
              fadd    dword ptr [ebp+330h]
              fst     dword ptr [ebp+330h]
            }
            *(float *)&_EBP->_pad_30c[36] = _ET1;
            __asm
            {
              fcomp   ds:flt_497220
              fnstsw  ax
            }
            if ( (_AX & 0x4100) == 0 )
            {
              play_voice_manager((int)unk_751498, 7, 2u, -1);
              *(_DWORD *)&_EBP->_pad_30c[36] = 0;
            }
          }
          _EAX = _EBP->game;
          __asm
          {
            fld     dword ptr [eax+38h]
            fmul    ds:flt_4975B0
            fld     dword ptr [eax+38h]
            fmul    ds:flt_497228
            fsub    st, st(1)
            fmul    ds:flt_497258
            fadd    st, st(1)
            fcomp   dword ptr [ebp+418h]
            fnstsw  ax
          }
          if ( (BYTE1(_EAX) & 0x41) != 0 )
          {
            __asm { fstp    st }
          }
          else
          {
            __asm
            {
              fcomp   dword ptr [ebp+418h]
              fnstsw  ax
            }
            if ( (_AX & 0x100) != 0 && !_EBP->attachment_exit_pending && _EBP->movement_state != 2 )
            {
              __asm
              {
                fld     dword ptr [ebp+4360h]
                fadd    dword ptr [ebp+435Ch]
                fst     dword ptr [ebp+435Ch]
              }
              *(float *)_EBP[1]._pad_00 = _ET1;
              __asm
              {
                fcomp   ds:flt_497220
                fnstsw  ax
              }
              if ( (_AX & 0x4100) == 0 )
              {
                *(_DWORD *)_EBP[1]._pad_00 = 0;
                play_voice_manager((int)unk_751498, 6, 1u, -1);
              }
LABEL_350:
              handle_subgoldy_collisions((int)_EBP);
              update_anim_manager((char *)&_EBP->_pad_29ac[220]);
              update_anim_manager((char *)&_EBP->_pad_29ac[4800]);
              update_anim_manager((char *)&_EBP->_pad_29ac[1836]);
              update_anim_manager((char *)&_EBP->_pad_29ac[2824]);
              update_anim_manager((char *)&_EBP->_pad_29ac[3812]);
              update_track_parcels((_DWORD *)_EBP->game + 4815136);
              initialize_cutscene((int)_EBP->_pad_2984);
              update_player_movement_flags((int *)_EBP);
              if ( *((int *)MEMORY[0x4DF904] + 4299517) < 10 )
                _EBP->movement_progress = _EBP->movement_rate_scalar;
              v226 = _EBP->game;
              if ( (*((_DWORD *)v226 + 19) & 0x400000) == 0 )
                goto LABEL_371;
              if ( LOBYTE(_EBP->completion_handoff_active) )
                goto LABEL_371;
              if ( _EBP->control_override_active )
                goto LABEL_371;
              movement_state = _EBP->movement_state;
              if ( movement_state )
              {
                if ( movement_state != 4 )
                  goto LABEL_371;
              }
              __asm
              {
                fld     dword ptr [ebp+2730h]
                fcomp   ds:flt_497234
                fnstsw  ax
              }
              if ( (_AX & 0x4100) == 0 )
              {
                __asm
                {
                  fld     dword ptr [ebp+2734h]
                  fadd    dword ptr [ebp+2730h]
                  fst     dword ptr [ebp+2730h]
                }
                _EBP->movement_progress = _ET1;
                __asm
                {
                  fcomp   ds:flt_497220
                  fnstsw  ax
                }
                if ( (_AX & 0x4100) == 0 )
                  _EBP->movement_progress = 0.0;
                goto LABEL_371;
              }
              if ( *((_BYTE *)v226 + 43092) )
              {
                if ( *((_BYTE *)v226 + 16721360) )
                {
                  if ( (*(_BYTE *)(*((_DWORD *)v226 + 4180341) + 6 * *((_DWORD *)v226 + 4180343) + 116) & 1) == 0 )
                  {
                    if ( (*(_BYTE *)(*((_DWORD *)v226 + 4180341) + 6 * *((_DWORD *)v226 + 4180343) + 116) & 2) == 0 )
                      goto LABEL_371;
                    goto LABEL_370;
                  }
                  goto LABEL_365;
                }
                if ( (_EBP->control_source->control_flags_a & 0x4000) != 0 )
                {
LABEL_365:
                  play_movement_state_sound((int)_EBP);
                  update_movement_flag_emitters((char *)_EBP, (int)_EBP);
                  __asm
                  {
                    fld     dword ptr [ebp+2734h]
                    fadd    ds:flt_4973D8
                    fstp    dword ptr [ebp+2730h]
                  }
                  _EBP->movement_progress = _ET1;
                  goto LABEL_371;
                }
                if ( (_EBP->control_source->control_flags_b & 0x4000) != 0 )
                {
LABEL_370:
                  _EBP->movement_progress = _EBP->movement_rate_scalar;
                  play_movement_state_sound((int)_EBP);
                  update_movement_flag_emitters((char *)_EBP, (int)_EBP);
                }
              }
LABEL_371:
              update_row_event_display((_DWORD **)_EBP->game + 4835830);
              ++*((_DWORD *)_EBP->game + 4147935);
              ++*((_DWORD *)_EBP->game + 4180343);
              v232 = _EBP->game;
              if ( *((_DWORD *)v232 + 4180343) == 21000 )
                show_times_up_message((int *)v232 + 4835850);
              update_times_up((int)_EBP->game + 19343400);
              return result;
            }
          }
          *(_DWORD *)_EBP[1]._pad_00 = 0;
          goto LABEL_350;
        }
      }
      if ( _EBP->follow_state._pad_3c[0] && LOBYTE(_EBP->completion_handoff_active) )
      {
        _EBP->track_z_offset = 320.0;
        _EBP->track_z_anchor = 320.0;
      }
      else
      {
        if ( _EBP->control_override_active )
        {
          __asm
          {
            fld     dword ptr [ebp+29CCh]
            fadd    st, st
            fsubr   dword ptr [ebp+273Ch]
            fst     dword ptr [ebp+273Ch]
          }
          _EBP->track_z_offset = _ET1;
          __asm { fstp    dword ptr [ebp+2740h] }
          _EBP->track_z_anchor = _ET1;
          __asm
          {
            fld     dword ptr [ebp+273Ch]
            fcomp   ds:flt_497234
            fnstsw  ax
          }
          if ( (_AX & 0x100) != 0 )
          {
            __asm { fld     ds:flt_497234 }
          }
          else
          {
            __asm
            {
              fld     dword ptr [ebp+273Ch]
              fcomp   ds:flt_4975E0
              fnstsw  ax
            }
            if ( (_AX & 0x4100) != 0 )
              __asm { fld     dword ptr [ebp+273Ch] }
            else
              __asm { fld     ds:flt_4975E0 }
          }
        }
        else
        {
          resolve_uncaptured_cursor_sensitivity_scale(flt_4DF950[*(_DWORD *)_EBP->_pad_2970]);
          _EAX = _EBP->control_source;
          __asm
          {
            fstp    st
            fld     dword ptr [eax+28h]
            fsub    dword ptr [ebp+2740h]
            fadd    dword ptr [ebp+273Ch]
            fcom    ds:flt_497234
            fst     dword ptr [ebp+273Ch]
          }
          _EBP->track_z_offset = _ET1;
          __asm { fnstsw  ax }
          if ( (BYTE1(_EAX) & 1) != 0 )
          {
            __asm
            {
              fstp    st
              fld     ds:flt_497234
            }
          }
          else
          {
            __asm
            {
              fcom    ds:flt_4975E0
              fnstsw  ax
            }
            if ( (_AX & 0x4100) == 0 )
            {
              __asm
              {
                fstp    st
                fld     ds:flt_4975E0
              }
            }
          }
          __asm { fstp    dword ptr [ebp+273Ch] }
          _EBP->track_z_offset = _ET1;
          _EBP->track_z_anchor = _EBP->control_source->steering_x;
          if ( *(_DWORD *)_EBP->_pad_2970 != 1 )
            goto LABEL_40;
          _EAX = _EBP->control_source;
          __asm { fld     dword ptr [eax+28h] }
        }
        __asm { fstp    dword ptr [ebp+273Ch] }
        _EBP->track_z_offset = _ET1;
      }
LABEL_40:
      if ( !LOBYTE(_EBP->completion_handoff_active) )
      {
        __asm
        {
          fld     dword ptr [ebp+273Ch]
          fsubr   ds:flt_497264
          fmul    ds:flt_4975DC
          fcom    ds:flt_4975D8
          fnstsw  ax
        }
        if ( (_AX & 0x100) != 0 )
        {
          __asm
          {
            fstp    st
            fld     ds:flt_4975D8
          }
        }
        else
        {
          __asm
          {
            fcom    ds:flt_4975D4
            fnstsw  ax
          }
          if ( (_AX & 0x4100) == 0 )
          {
            __asm
            {
              fstp    st
              fld     ds:flt_4975D4
            }
          }
        }
        if ( _EBP->movement_state == 2 )
        {
          __asm { fstp    st }
        }
        else
        {
          _ECX = _EBP->game;
          __asm
          {
            fld     dword ptr [ecx+38h]
            fmul    ds:flt_497270
            fxch    st(1)
            fsub    dword ptr [ebp+68h]
            fmulp   st(1), st
            fadd    dword ptr [ebp+68h]
            fstp    dword ptr [ebp+68h]
          }
          _EBP->position.x = _ET1;
        }
      }
      _EBX = &_EBP->position;
      v34 = convert_math_type32_to_16(_EBP->position.x, 16.0);
      convert_math_type16_to_32(v34, 16.0);
      __asm { fst     [esp+58h+var_40] }
      __asm { fstp    dword ptr [ebx] }
      _EBX->x = _ET1;
      v36 = _EBP->game;
      *((_WORD *)v36 + 3 * *((_DWORD *)v36 + 4180343) + 8295872) = convert_math_type32_to_16(v245, 16.0);
      v37 = _EBP->game;
      if ( *((_DWORD *)v37 + 4180343) )
      {
        __asm
        {
          fld     dword ptr [ebp+70h]
          fsub    dword ptr unk_643194
        }
        __asm { fstp    [esp+58h+var_58]; float }
        *((_WORD *)v37 + 3 * *((_DWORD *)v37 + 4180343) + 8295873) = convert_math_type32_to_16(v239, 32.0);
        v17 = convert_math_type16_to_32(*((_WORD *)_EBP->game + 3 * *((_DWORD *)_EBP->game + 4180343) + 8295873), 32.0);
        __asm { fadd    dword ptr unk_643194 }
      }
      else
      {
        *((_WORD *)v37 + 3 * *((_DWORD *)v37 + 4180343) + 8295873) = convert_math_type32_to_16(_EBP->position.z, 32.0);
        v17 = convert_math_type16_to_32(*((_WORD *)_EBP->game + 3 * *((_DWORD *)_EBP->game + 4180343) + 8295873), 32.0);
      }
      __asm { fstp    dword ptr unk_643194 }
      v38 = _EBP->game;
      if ( *((_BYTE *)v38 + 43092) )
      {
        if ( (_EBP->control_source->control_flags_a & 0x4000) != 0 )
          *((_BYTE *)v38 + 6 * *((_DWORD *)v38 + 4180343) + 16591748) |= 1u;
        if ( (_EBP->control_source->control_flags_b & 0x4000) != 0 )
          *((_BYTE *)_EBP->game + 6 * *((_DWORD *)_EBP->game + 4180343) + 16591748) |= 2u;
      }
      control_source = _EBP->control_source;
      if ( (control_source->control_flags_b & 0x4000) == 0 && (control_source->control_flags_a & 0x4000) == 0 )
        *((_BYTE *)_EBP->game + 43092) = 1;
      v40 = _EBP->game;
      if ( *((_BYTE *)v40 + 43092) )
        *((_BYTE *)v40 + 6 * *((_DWORD *)v40 + 4180343) + 16591748) |= 4u;
      goto LABEL_61;
    }
  }
  return result;
}

