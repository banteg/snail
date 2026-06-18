/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: handle_subgoldy_collisions @ 0x444cf0 */
/* selector: handle_subgoldy_collisions */

// Processes Goldy's live collision sweep against rings, parcels, health pickups, garbage, salt, slugs, and related runtime object pools, updating score and the contact-damage gauge side effects as each hit resolves. Cross-port Android and iOS symbols match this helper to `cRSubGoldy::Collision()`.
int32_t __thiscall handle_subgoldy_collisions(Player *player)
{
  int i; // edi
  float *v3; // eax
  double v4; // st7
  int j; // edi
  float *v6; // eax
  double v7; // st7
  int k; // edi
  double v9; // st7
  __int64 v10; // rax
  int m; // edi
  Game *game; // edx
  int v13; // ecx
  float *v14; // eax
  double v15; // st7
  double v16; // st7
  Game *v17; // eax
  double v18; // st7
  Game *v19; // eax
  __int64 v20; // rax
  double v21; // st7
  double v22; // st6
  double v23; // st7
  double subgame_rate; // st7
  int n; // edi
  float *v26; // eax
  double v27; // st7
  Game *v28; // eax
  int v29; // ebx
  int ii; // edi
  float *v31; // eax
  double v32; // st7
  double y; // st7
  double v35; // st7
  char v36; // c0
  Game *v37; // eax
  double v38; // st7
  double v39; // st7
  double v41; // st7
  char v42; // c0
  Game *v43; // eax
  double v44; // st7
  double v45; // st7
  int jj; // edi
  int32_t result; // eax
  double v48; // st7
  __int16 v49; // fps
  bool v50; // c0
  char v51; // c2
  bool v52; // c3
  double v53; // st7
  bool v54; // c0
  char v55; // c2
  bool v56; // c3
  __int16 v57; // fps
  Game *v58; // ecx
  int v59; // eax
  Game *v60; // ecx
  int32_t v61; // eax
  int v62; // eax
  int v63; // eax
  int32_t movement_flag_selector; // eax
  int32_t player_slot; // [esp-Ch] [ebp-90h]
  float v66; // [esp+10h] [ebp-74h]
  Vec3 v67; // [esp+18h] [ebp-6Ch] BYREF
  Vec3 v68; // [esp+24h] [ebp-60h] BYREF
  Vec3 v69; // [esp+30h] [ebp-54h]
  int v70; // [esp+3Ch] [ebp-48h]
  float v71; // [esp+40h] [ebp-44h]
  float v72; // [esp+44h] [ebp-40h]
  Vec3 vector; // [esp+48h] [ebp-3Ch] BYREF
  float v74; // [esp+54h] [ebp-30h]
  float v75; // [esp+58h] [ebp-2Ch]
  float v76[3]; // [esp+60h] [ebp-24h] BYREF
  Vec3 v77; // [esp+6Ch] [ebp-18h] BYREF
  Vec3 v78; // [esp+78h] [ebp-Ch] BYREF

  if ( !player->attachment_exit_pending && !player->_pad_41c[0] && !player->control_override_active )
  {
    if ( SLOBYTE(player->movement_flags) >= 0 )
    {
      for ( i = 0; i < 6080; i += 152 )
      {
        v3 = (float *)&player->game->_pad_00[i];
        if ( *((_DWORD *)v3 + 876112) == 1 && *((_BYTE *)v3 + 3504468) == 1 )
        {
          v69.x = v3[876106] - player->cached_camera_target_world.x;
          v69.y = v3[876107] - player->cached_camera_target_world.y;
          v4 = v3[876108] - player->cached_camera_target_world.z;
          v69.z = v4;
          vector = v69;
          if ( v4 < 1.0 && normalize_vector(&vector) < 0.98000002 )
          {
            if ( player->damage_retrigger_timer == 0.0 )
              player->damage_retrigger_timer = player->damage_retrigger_step;
            player->game->_pad_74622[i + 3027762] = 0;
            apply_damage_gauge_delta((float *)&player->damage_gauge.state, 0.15000001, 0);
          }
        }
      }
    }
    for ( j = 0; j < 3520; j += 176 )
    {
      v6 = (float *)&player->game->_pad_00[j];
      if ( *((_DWORD *)v6 + 875232) == 1 )
      {
        v69.x = v6[875226] - player->cached_camera_target_world.x;
        v69.y = v6[875227] - player->cached_camera_target_world.y;
        v7 = v6[875228] - player->cached_camera_target_world.z;
        v69.z = v7;
        v67 = v69;
        if ( v7 < 1.0 && normalize_vector(&v67) < 0.49000001 )
        {
          *(_DWORD *)&player->game->_pad_74622[j + 3024222] = 2;
          apply_damage_gauge_delta((float *)&player->damage_gauge.state, 0.02, 0);
        }
      }
    }
    for ( k = *(_DWORD *)&player->game->_pad_74622[3033886]; k; k = *(_DWORD *)(k + 128) )
    {
      if ( *(_DWORD *)(k + 132) == 1 )
      {
        v69.x = *(float *)(k + 104) - player->cached_camera_target_world.x;
        v69.y = *(float *)(k + 108) - player->cached_camera_target_world.y;
        v9 = *(float *)(k + 112) - player->cached_camera_target_world.z;
        v69.z = v9;
        v67 = v69;
        if ( v9 < 1.0 && normalize_vector(&v67) < 0.98000002 )
        {
          if ( (player->movement_flags & 0x80) == 0 )
          {
            player->velocity.x = player->velocity.x - v67.x * player->velocity.z * 0.18000001;
            player->velocity.z = player->velocity.z - v67.z * player->velocity.z * 0.1;
          }
          *(_DWORD *)(k + 132) = 2;
          if ( v67.x >= 0.0 )
            *(_DWORD *)(k + 136) = 1;
          else
            *(_DWORD *)(k + 136) = 2;
          add_subgoldy_score((int *)player, SUBGOLDY_SCORE_GARBAGE, 0);
          apply_damage_gauge_delta((float *)&player->damage_gauge.state, 0.039999999, 0);
          v10 = (__int64)((double)next_math_random_value() * -0.000061035156);
          play_sound_effect(39 - v10);
        }
      }
    }
    for ( m = 0; m < 1888; m += 236 )
    {
      game = player->game;
      v13 = *(_DWORD *)&game->_pad_74622[m + 3022334];
      v14 = (float *)&game->_pad_00[m];
      if ( v13 == 1 || v13 == 4 )
      {
        v69.x = v14[874754] - player->cached_camera_target_world.x;
        v69.y = v14[874755] - player->cached_camera_target_world.y;
        v15 = v14[874756] - player->cached_camera_target_world.z;
        v69.z = v15;
        v67 = v69;
        if ( v15 < 2.0 )
        {
          v16 = normalize_vector(&v67);
          v66 = v16;
          if ( v16 < 1.5675001 )
          {
            if ( (player->movement_flags & 0x80) != 0 )
            {
              kill_slug_hazard((int)&player->game->_pad_74622[m + 3022206]);
            }
            else if ( player->control_override_active )
            {
              subgame_rate = player->game->subgame_rate;
              player->velocity.z = subgame_rate * subgame_rate * 0.0040000002 * -8.0;
              apply_damage_gauge_delta((float *)&player->damage_gauge.state, 1.0, 0);
            }
            else
            {
              v17 = player->game;
              player->control_override_active = 1;
              player->follow_state.active = 0;
              v70 = 0;
              v18 = v17->subgame_rate;
              player->velocity.x = 0.0;
              v71 = v18 * 0.2;
              player->velocity.y = v71;
              v72 = v18 * -0.2;
              player->velocity.z = v72;
              begin_post_follow_carryover((int)player);
              v19 = player->game;
              player->presentation.cutscene_ai.state = 10;
              v19->_pad_74622[m + 3022423] = 1;
              v20 = (__int64)((double)next_math_random_value() * -0.000061035156);
              play_slug_voice((int)&player->game->_pad_74622[m + 3022206], 34 - v20);
              v21 = v66 * 0.5;
              player->presentation.wobble.lift_phase_step = 0.0;
              v74 = v21 * v67.x;
              v75 = v67.y * v21;
              vector.x = v74 + player->cached_camera_target_world.x;
              v22 = v75 + player->cached_camera_target_world.y;
              v76[0] = vector.x;
              player_slot = player->player_slot;
              vector.y = v22;
              v23 = v21 * v67.z + player->cached_camera_target_world.z;
              v76[1] = vector.y;
              vector.z = v23;
              v76[2] = vector.z;
              firework_shoot(v76, player_slot, 92, 80);
            }
          }
        }
      }
    }
    for ( n = 0; n < 7000; n += 140 )
    {
      v26 = (float *)&player->game->_pad_00[n];
      if ( *((_DWORD *)v26 + 4815150) == 1 )
      {
        vector.x = v26[4815140] - player->cached_camera_target_world.x;
        vector.y = v26[4815141] - player->cached_camera_target_world.y;
        v27 = v26[4815142] - player->cached_camera_target_world.z;
        vector.z = v27;
        v77 = vector;
        if ( v27 < 1.0 && normalize_vector(&v77) < 1.24 )
        {
          add_subgoldy_score((int *)player, SUBGOLDY_SCORE_PARCEL_COLLECT, 0);
          play_voice_manager((int)unk_751498, 10, 1u, -1);
          play_sound_effect(27);
          *(_DWORD *)&player->game->_pad_ff25e8[n + 2539216] = 4;
          v28 = player->game;
          v29 = *(_DWORD *)&player->presentation.cutscene_ai._pad_59[3] + 1;
          *(_DWORD *)&player->presentation.cutscene_ai._pad_59[3] = v29;
          if ( !v28->level_mode )
            sprintf(
              (char *const)(*(_DWORD *)&v28->_pad_74622[3044722] + 716),
              "%i/%i",
              v29,
              *(_DWORD *)&v28->_pad_74622[1293246]);
        }
      }
    }
  }
  for ( ii = 0; ii < 928; ii += 116 )
  {
    v31 = (float *)&player->game->_pad_00[ii];
    if ( *((_DWORD *)v31 + 874510) == 1 )
    {
      v67.x = v31[874500] - player->cached_camera_target_world.x;
      v67.y = v31[874501] - player->cached_camera_target_world.y;
      v32 = v31[874502] - player->cached_camera_target_world.z;
      v68.x = v67.x;
      v68.y = v67.y;
      v67.z = v32;
      y = player->live_matrix.position.y;
      v68.z = v67.z;
      if ( y >= 0.49000001 && v67.z < 1.0 )
      {
        v35 = v67.y;
        if ( v36 )
          v35 = -v35;
        if ( v35 < 0.40000001 && normalize_vector(&v68) < 0.98000002 )
        {
          play_sound_effect(14);
          *(_DWORD *)&player->game->_pad_74622[ii + 3021334] = 2;
          health_collect_particles((int)player, (int)&player->game->_pad_74622[ii + 3021278]);
          apply_damage_gauge_delta((float *)&player->damage_gauge.state, -0.5, 0);
        }
      }
    }
  }
  v37 = player->game;
  if ( *(_DWORD *)&v37->_pad_74622[3020814] == 1 )
  {
    v67.x = *(float *)&v37->_pad_74622[3020790] - player->cached_camera_target_world.x;
    v67.y = *(float *)&v37->_pad_74622[3020794] - player->cached_camera_target_world.y;
    v38 = *(float *)&v37->_pad_74622[3020798] - player->cached_camera_target_world.z;
    v68.x = v67.x;
    v68.y = v67.y;
    v67.z = v38;
    v39 = player->live_matrix.position.y;
    v68.z = v67.z;
    if ( v39 >= 0.49000001 && v67.z < 1.0 )
    {
      v41 = v67.y;
      if ( v42 )
        v41 = -v41;
      if ( v41 < 0.40000001 && normalize_vector(&v68) < 0.98000002 )
      {
        *(_DWORD *)&player->game->_pad_74622[3020814] = 2;
        noop_runtime_ai();
        player->velocity.z = player->game->subgame_rate * 0.5;
      }
    }
  }
  v43 = player->game;
  if ( *(_DWORD *)&v43->_pad_74622[3020922] == 1 )
  {
    v67.x = *(float *)&v43->_pad_74622[3020882] - player->cached_camera_target_world.x;
    v67.y = *(float *)&v43->_pad_74622[3020886] - player->cached_camera_target_world.y;
    v44 = *(float *)&v43->_pad_74622[3020890] - player->cached_camera_target_world.z;
    v68.x = v67.x;
    v68.y = v67.y;
    v67.z = v44;
    v45 = player->live_matrix.position.y;
    v68.z = v67.z;
    if ( v45 >= 0.49000001 && v67.z < 1.0 && normalize_vector(&v68) < 3.0 )
    {
      *(_DWORD *)&player->game->_pad_74622[3020922] = 2;
      arm_jetpack_gauge((int)&player->jetpack_gauge);
    }
  }
  for ( jj = 0; jj < 1008; jj += 504 )
  {
    result = (int32_t)&player->game->_pad_00[jj];
    if ( *(_DWORD *)(result + 3520524) == 1 )
    {
      vector.x = *(float *)(result + 3520500) - player->cached_camera_target_world.x;
      vector.y = *(float *)(result + 3520504) - player->cached_camera_target_world.y;
      v48 = *(float *)(result + 3520508) - player->cached_camera_target_world.z;
      HIWORD(result) = HIWORD(vector.x);
      vector.z = v48;
      v50 = v48 < 1.0;
      v51 = 0;
      v52 = v48 == 1.0;
      v78 = vector;
      LOWORD(result) = v49;
      if ( v48 < 1.0 )
      {
        v53 = normalize_vector(&v78);
        v54 = v53 < 0.98000002;
        v55 = 0;
        v56 = v53 == 0.98000002;
        LOWORD(result) = v57;
        if ( v53 < 0.98000002 )
        {
          *(_DWORD *)&player->game->_pad_74622[jj + 3043818] = 2;
          if ( !LOBYTE(player->completion_handoff_active) )
          {
            v58 = player->game;
            v59 = *(_DWORD *)&v58->_pad_74622[jj + 3043826];
            if ( v59 == 3 || v59 == 7 )
            {
              player->velocity.z = -0.1;
              play_sound_effect(43);
            }
            else
            {
              player->velocity.z = v58->subgame_rate * 0.5;
            }
          }
          v60 = player->game;
          result = *(_DWORD *)&v60->_pad_74622[jj + 3043826];
          switch ( result )
          {
            case 4:
            case 5:
              v63 = *(_DWORD *)&player->_pad_3f0[20];
              if ( v63 < 10 )
              {
                if ( (v60->runtime_flags & 0x10) != 0 && v60->level_mode != 3 )
                  *(_DWORD *)&player->_pad_3f0[20] = v63 + 1;
                play_voice_manager((int)unk_751498, 5, 1u, -1);
              }
              movement_flag_selector = player->movement_flag_selector;
              if ( movement_flag_selector >= 8 )
              {
                if ( movement_flag_selector == 8 )
                  player->movement_flag_selector = 7;
              }
              else
              {
                player->movement_flag_selector = movement_flag_selector + 1;
              }
              v62 = player->movement_flag_selector - 1;
              if ( v62 > 6 )
LABEL_105:
                v62 = 6;
LABEL_106:
              play_sound_effect(v62 + 1);
              add_subgoldy_score((int *)player, SUBGOLDY_SCORE_RING, 0);
              continue;
            case 8:
              v61 = player->movement_flag_selector;
              if ( v61 >= 8 )
              {
                if ( v61 == 8 )
                  player->movement_flag_selector = 7;
              }
              else
              {
                player->movement_flag_selector = v61 + 1;
              }
              v62 = player->movement_flag_selector - 1;
              if ( v62 > 6 )
                goto LABEL_105;
              goto LABEL_106;
            case 1:
              add_subgoldy_score((int *)player, SUBGOLDY_SCORE_RING, 0);
              play_sound_effect(1);
              break;
            case 2:
            case 6:
              add_subgoldy_score((int *)player, SUBGOLDY_SCORE_RING, 0);
              play_sound_effect(42);
              player->nuke_effect_progress = player->nuke_effect_progress_step;
              result = initialize_nuke(&player->nuke);
              break;
          }
        }
      }
    }
  }
  return result;
}
