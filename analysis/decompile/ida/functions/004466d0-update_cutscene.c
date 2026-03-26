/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_cutscene @ 0x4466d0 */
/* selector: update_cutscene */

// Advances the player-side cutscene controller, consuming the live snail hotspot bank as the intro/completion/death camera anchor source, including the authored `CameraSkidStop -> CameraIntroTalk` blend path, and handling the handoff into `initialize_completion_screen`. Cross-port Android and iOS symbols match this helper to `cRCutScene::AI()`.
int32_t __thiscall update_cutscene(CutsceneAI *cutscene_ai)
{
  int32_t state; // eax
  int32_t result; // eax
  PlayerPresentationController *presentation; // ecx
  Vec3 *v5; // ecx
  double v6; // st7
  __int16 v7; // fps
  bool v8; // c0
  char v9; // c2
  bool v10; // c3
  double v11; // st7
  Vec3 *v12; // eax
  double v13; // st7
  double v14; // st7
  double v15; // st7
  double v16; // st7
  double v17; // st7
  __int16 v18; // fps
  bool v19; // c0
  char v20; // c2
  bool v21; // c3
  PlayerPresentationController *v22; // ecx
  double v23; // st7
  Vec3 *v24; // edx
  double v25; // st7
  double v26; // st7
  double v27; // st7
  __int16 v28; // fps
  bool v29; // c0
  char v30; // c2
  bool v31; // c3
  PlayerPresentationController *v32; // ecx
  Player *player; // ecx
  PlayerPresentationController *v34; // ecx
  PlayerPresentationController *v35; // eax
  int v36; // eax
  Vec3 *v37; // ecx
  Vec3 *v38; // eax
  float z; // edx
  float progress; // eax
  double v41; // st7
  double v42; // st7
  double v43; // st7
  __int16 v44; // fps
  bool v45; // c0
  char v46; // c2
  bool v47; // c3
  Vec3 *v48; // edx
  Vec4 *p_position; // [esp+0h] [ebp-FCh]
  float v50; // [esp+0h] [ebp-FCh]
  Vec4 *v51; // [esp+0h] [ebp-FCh]
  float v52; // [esp+0h] [ebp-FCh]
  float v53; // [esp+0h] [ebp-FCh]
  float v54; // [esp+0h] [ebp-FCh]
  float v55; // [esp+0h] [ebp-FCh]
  float v56; // [esp+0h] [ebp-FCh]
  float v57; // [esp+0h] [ebp-FCh]
  Vec4 *v58; // [esp+0h] [ebp-FCh]
  float v59; // [esp+0h] [ebp-FCh]
  float v60; // [esp+0h] [ebp-FCh]
  Vec4 *v61; // [esp+0h] [ebp-FCh]
  float v62; // [esp+14h] [ebp-E8h]
  float v63; // [esp+14h] [ebp-E8h]
  float v64; // [esp+18h] [ebp-E4h]
  float v65; // [esp+18h] [ebp-E4h]
  float v66; // [esp+18h] [ebp-E4h]
  float v67; // [esp+1Ch] [ebp-E0h]
  float v68; // [esp+1Ch] [ebp-E0h]
  Vec3 v69; // [esp+24h] [ebp-D8h] BYREF
  float v70; // [esp+34h] [ebp-C8h]
  float v71; // [esp+38h] [ebp-C4h]
  TransformMatrix v72; // [esp+3Ch] [ebp-C0h] BYREF
  TransformMatrix v73; // [esp+7Ch] [ebp-80h] BYREF
  float x; // [esp+ECh] [ebp-10h]
  float y; // [esp+F0h] [ebp-Ch]
  float v76; // [esp+F4h] [ebp-8h]
  Vec3 v77; // 0:^1C.12

  state = cutscene_ai->state;
  cutscene_ai->unresolved_58 = 0;
  result = state - 1;
  switch ( result )
  {
    case 0:
      presentation = cutscene_ai->presentation;
      cutscene_ai->state = 2;
      cutscene_ai->progress = 0.0;
      cutscene_ai->progress_step = 0.0083333338;
      cutscene_ai->unresolved_58 = 1;
      dispatch_cutscene_animation(presentation, 9, 1u, -1);
      dispatch_cutscene_animation(cutscene_ai->presentation, 9, 0, -1);
      dispatch_cutscene_animation(cutscene_ai->presentation, 1, 0, -1);
      goto LABEL_3;
    case 1:
LABEL_3:
      cutscene_ai->unresolved_08 = 1;
      set_matrix_identity(&cutscene_ai->live_matrix);
      v5 = &cutscene_ai->presentation->snail_hotspots_world[18];
      p_position = &cutscene_ai->presentation->live_matrix.position;
      cutscene_ai->live_matrix.position.x = v5->x;
      cutscene_ai->live_matrix.position.y = v5->y;
      cutscene_ai->live_matrix.position.z = v5->z;
      look_at_point(&cutscene_ai->live_matrix, (const Vec3 *)p_position);
      v6 = cutscene_ai->progress + cutscene_ai->progress_step;
      cutscene_ai->progress = v6;
      v8 = v6 < 1.0;
      v9 = 0;
      v10 = v6 == 1.0;
      LOWORD(result) = v7;
      if ( v6 > 1.0 )
      {
        cutscene_ai->progress_step = 0.0083333338;
        cutscene_ai->state = 8;
        cutscene_ai->progress = 0.0;
      }
      return result;
    case 4:
      v34 = cutscene_ai->presentation;
      cutscene_ai->state = 7;
      cutscene_ai->unresolved_08 = -1;
      dispatch_cutscene_animation(v34, 8, 1u, -1);
      dispatch_cutscene_animation(cutscene_ai->presentation, 9, 0, -1);
      dispatch_cutscene_animation(cutscene_ai->presentation, 9, 0, -1);
      v35 = cutscene_ai->presentation;
      cutscene_ai->state = 6;
      cutscene_ai->progress = 0.0;
      cutscene_ai->progress_step = 0.0083333338;
      *(_DWORD *)&v35->invincible_shell._pad_90[8] = 1015580809;
      *(_DWORD *)&cutscene_ai->presentation->invincible_shell._pad_90[4] = *(_DWORD *)&cutscene_ai->presentation->invincible_shell._pad_90[8];
      cutscene_ai->unresolved_58 = 1;
      v36 = *((_DWORD *)MEMORY[0x4DF904] + 119190);
      if ( v36 )
      {
        if ( v36 == 1 )
          initialize_completion_screen(
            (int)MEMORY[0x4DF904] + 19820016,
            *(_DWORD *)&cutscene_ai->player->presentation.cutscene_ai.unresolved_58,
            1u);
      }
      else
      {
        initialize_completion_screen(
          (int)MEMORY[0x4DF904] + 19820016,
          *(_DWORD *)&cutscene_ai->player->presentation.cutscene_ai.unresolved_58,
          *(_DWORD *)&cutscene_ai->player->presentation.cutscene_ai.unresolved_58 == *((_DWORD *)MEMORY[0x4DF904]
                                                                                     + 561662));
      }
      play_sound_effect(46);
      goto LABEL_25;
    case 5:
LABEL_25:
      cutscene_ai->unresolved_08 = -1;
      set_matrix_identity(&v73);
      v37 = &cutscene_ai->presentation->snail_hotspots_world[12];
      v38 = &cutscene_ai->presentation->snail_hotspots_world[18];
      v72.position.x = v37->x;
      v72.position.y = v37->y;
      v72.position.z = v37->z;
      x = v38->x;
      z = v38->z;
      y = v38->y;
      progress = cutscene_ai->progress;
      v76 = z;
      v65 = y - v72.position.y;
      v67 = z - v72.position.z;
      v70 = v65 * progress;
      v71 = v67 * progress;
      v63 = (x - v72.position.x) * progress + v72.position.x;
      v73.position.x = v63;
      v66 = v72.position.y + v70;
      v73.position.y = v66;
      v68 = v72.position.z + v71;
      v41 = cutscene_ai->progress * 3.1415927;
      v73.position.z = v68;
      v57 = v41;
      v42 = sine(v57);
      v58 = &cutscene_ai->presentation->live_matrix.position;
      v73.position.x = v73.position.x - v42 * 0.5;
      look_at_point(&v73, (const Vec3 *)v58);
      qmemcpy(&v72, cutscene_ai->presentation->owner_player->_pad_200, sizeof(v72));
      v59 = cutscene_ai->progress * 1.5707964;
      v60 = sine(v59);
      linear_interpolate_matrix(&cutscene_ai->live_matrix, &v72, &v73, v60);
      v43 = cutscene_ai->progress + cutscene_ai->progress_step;
      cutscene_ai->progress = v43;
      v45 = v43 < 1.0;
      v46 = 0;
      v47 = v43 == 1.0;
      LOWORD(result) = v44;
      if ( v43 > 1.0 )
      {
        cutscene_ai->state = 7;
        cutscene_ai->progress = 0.0;
        cutscene_ai->progress_step = 0.016666668;
      }
      return result;
    case 6:
      cutscene_ai->unresolved_08 = -1;
      cutscene_ai->unresolved_58 = 1;
      set_matrix_identity(&cutscene_ai->live_matrix);
      v48 = &cutscene_ai->presentation->snail_hotspots_world[18];
      v61 = &cutscene_ai->presentation->live_matrix.position;
      cutscene_ai->live_matrix.position.x = v48->x;
      cutscene_ai->live_matrix.position.y = v48->y;
      cutscene_ai->live_matrix.position.z = v48->z;
      look_at_point(&cutscene_ai->live_matrix, (const Vec3 *)v61);
      result = cutscene_ai->presentation->anim_manager.queued_animation_count;
      if ( !result )
        result = dispatch_cutscene_animation(cutscene_ai->presentation, 9, 0, -1);
      goto LABEL_29;
    case 7:
      *((_BYTE *)&loc_42FEC4 + (_DWORD)MEMORY[0x4DF904]) = 0;
      cutscene_ai->unresolved_08 = 1;
      set_matrix_identity(&v72);
      v11 = cutscene_ai->progress * 3.1415927;
      v12 = &cutscene_ai->presentation->snail_hotspots_world[18];
      v72.position.x = v12->x;
      v50 = v11;
      v72.position.y = v12->y;
      v72.position.z = v12->z;
      v13 = sine(v50);
      v51 = &cutscene_ai->presentation->live_matrix.position;
      v72.position.x = v13 + v13 + v72.position.x;
      look_at_point(&v72, (const Vec3 *)v51);
      qmemcpy(&v73, cutscene_ai->presentation->owner_player->_pad_200, sizeof(v73));
      v52 = cutscene_ai->progress * 1.5707964;
      v53 = sine(v52);
      linear_interpolate_matrix(&cutscene_ai->live_matrix, &v72, &v73, v53);
      v77.x = cutscene_ai->live_matrix.position.x - cutscene_ai->presentation->live_matrix.position.x;
      v77.y = cutscene_ai->live_matrix.position.y - cutscene_ai->presentation->live_matrix.position.y;
      v77.z = cutscene_ai->live_matrix.position.z - cutscene_ai->presentation->live_matrix.position.z;
      v69 = v77;
      v14 = normalize_vector(&v69);
      if ( v14 < 1.5 )
      {
        v15 = 1.5 - v14;
        v62 = v69.x * v15;
        v64 = v69.y * v15;
        v16 = v15 * v69.z;
        cutscene_ai->live_matrix.position.x = v62 + cutscene_ai->live_matrix.position.x;
        cutscene_ai->live_matrix.position.y = v64 + cutscene_ai->live_matrix.position.y;
        cutscene_ai->live_matrix.position.z = v16 + cutscene_ai->live_matrix.position.z;
      }
      v17 = cutscene_ai->progress + cutscene_ai->progress_step;
      cutscene_ai->progress = v17;
      v19 = v17 < 1.0;
      v20 = 0;
      v21 = v17 == 1.0;
      LOWORD(result) = v18;
      if ( v17 > 1.0 )
      {
        cutscene_ai->state = 9;
        cutscene_ai->progress = 0.0;
        cutscene_ai->progress_step = 0.0083333338;
      }
      return result;
    case 8:
      qmemcpy(
        &cutscene_ai->live_matrix,
        cutscene_ai->presentation->owner_player->_pad_200,
        sizeof(cutscene_ai->live_matrix));
      cutscene_ai->state = 0;
      return result;
    case 9:
      v22 = cutscene_ai->presentation;
      cutscene_ai->unresolved_08 = -1;
      dispatch_cutscene_animation(v22, 7, 1u, -1);
      cutscene_ai->state = 11;
      cutscene_ai->progress = 0.0;
      cutscene_ai->progress_step = 0.0083333338;
      cutscene_ai->unresolved_58 = 1;
      play_voice_manager((int)unk_751498, 3, 2u, -1);
      cutscene_ai->presentation->owner_player->attachment_exit_gate_a = 1;
      release_snail_weapons((int)cutscene_ai->presentation);
      goto LABEL_11;
    case 10:
LABEL_11:
      cutscene_ai->unresolved_08 = -1;
      set_matrix_identity(&v73);
      v23 = cutscene_ai->progress * 3.1415927;
      v24 = &cutscene_ai->presentation->snail_hotspots_world[18];
      v73.position.x = v24->x;
      v73.position.y = v24->y;
      v54 = v23;
      v73.position.z = v24->z;
      v25 = sine(v54);
      v73.position.x = v25 + v25 + v73.position.x;
      if ( v73.position.y < 0.0 )
        v73.position.y = 0.0;
      look_at_point(&v73, (const Vec3 *)&cutscene_ai->presentation->live_matrix.position);
      v26 = cutscene_ai->progress;
      qmemcpy(&v72, cutscene_ai->presentation->owner_player->_pad_200, sizeof(v72));
      v55 = v26 * 1.5707964;
      v56 = sine(v55);
      linear_interpolate_matrix(&cutscene_ai->live_matrix, &v72, &v73, v56);
      v27 = cutscene_ai->progress + cutscene_ai->progress_step;
      cutscene_ai->progress = v27;
      v29 = v27 < 1.0;
      v30 = 0;
      v31 = v27 == 1.0;
      LOWORD(result) = v28;
      if ( v27 > 1.0 )
      {
        cutscene_ai->state = 12;
        cutscene_ai->progress = 0.0;
        cutscene_ai->progress_step = 0.016666668;
      }
      break;
    case 11:
      cutscene_ai->unresolved_08 = -1;
      cutscene_ai->unresolved_58 = 1;
      set_matrix_identity(&cutscene_ai->live_matrix);
      v32 = cutscene_ai->presentation;
      cutscene_ai->live_matrix.position.x = cutscene_ai->presentation->snail_hotspots_world[18].x;
      cutscene_ai->live_matrix.position.y = v32->snail_hotspots_world[18].y;
      cutscene_ai->live_matrix.position.z = v32->snail_hotspots_world[18].z;
      if ( cutscene_ai->live_matrix.position.y < 0.0 )
        cutscene_ai->live_matrix.position.y = 0.0;
      look_at_point(&cutscene_ai->live_matrix, (const Vec3 *)&v32->live_matrix.position);
      player = cutscene_ai->player;
      LOBYTE(result) = player->_pad_78[12];
      if ( (_BYTE)result
        || (initialize_subgoldy_death(player), result = (int32_t)cutscene_ai->player, *(_BYTE *)(result + 1101)) )
      {
LABEL_29:
        cutscene_ai->progress = cutscene_ai->progress_step + cutscene_ai->progress;
      }
      else
      {
        LOBYTE(result) = play_voice_manager((int)unk_751498, 11, 2u, -1);
        cutscene_ai->player->attachment_exit_gate_b = 1;
        cutscene_ai->player->attachment_exit_gate_a = 1;
        cutscene_ai->progress = cutscene_ai->progress_step + cutscene_ai->progress;
      }
      break;
    default:
      return result;
  }
  return result;
}

