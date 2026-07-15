/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_cutscene @ 0x4466d0 */
/* selector: update_cutscene */

// Authored `cRCutScene::AI()`: advances the exact embedded CutScene, blends from `Player::cameraman.live_matrix`, clears `Player::click_start.hide_prompt` at the intro handoff, consumes live snail hotspots for intro/completion/death camera anchors, and compares delivered parcels with `SubgameRuntime::level_definition.parcel_count` before the completion-screen handoff.
void __thiscall update_cutscene(CutScene *cutscene)
{
  CutSceneState state; // eax
  Snail *presentation; // ecx
  Vec3 *v4; // ecx
  double v5; // st7
  double v6; // st7
  double v7; // st7
  double v8; // st7
  double v9; // st7
  double v10; // st7
  double v11; // st7
  Snail *v12; // ecx
  double v13; // st7
  double v14; // st7
  double v15; // st7
  double v16; // st7
  Snail *v17; // ecx
  Player *player; // ecx
  Snail *v19; // ecx
  Snail *v20; // eax
  int32_t level_mode; // eax
  Vec3 *v22; // eax
  float z; // edx
  float progress; // eax
  double v25; // st7
  double v26; // st7
  double v27; // st7
  Vec3 *v28; // edx
  Vec3 *alpha; // [esp+0h] [ebp-FCh]
  float alphaa; // [esp+0h] [ebp-FCh]
  Vec3 *alphab; // [esp+0h] [ebp-FCh]
  float alphac; // [esp+0h] [ebp-FCh]
  float alphad; // [esp+0h] [ebp-FCh]
  float alphae; // [esp+0h] [ebp-FCh]
  float alphaf; // [esp+0h] [ebp-FCh]
  float alphag; // [esp+0h] [ebp-FCh]
  float alphah; // [esp+0h] [ebp-FCh]
  Vec3 *alphai; // [esp+0h] [ebp-FCh]
  float alphaj; // [esp+0h] [ebp-FCh]
  float alphak; // [esp+0h] [ebp-FCh]
  Vec3 *alphal; // [esp+0h] [ebp-FCh]
  float v42; // [esp+14h] [ebp-E8h]
  float v43; // [esp+14h] [ebp-E8h]
  float v44; // [esp+18h] [ebp-E4h]
  float v45; // [esp+18h] [ebp-E4h]
  float v46; // [esp+18h] [ebp-E4h]
  float v47; // [esp+1Ch] [ebp-E0h]
  float v48; // [esp+1Ch] [ebp-E0h]
  Vec3 vector; // [esp+24h] [ebp-D8h] BYREF
  float v50; // [esp+34h] [ebp-C8h]
  float v51; // [esp+38h] [ebp-C4h]
  TransformMatrix transform; // [esp+3Ch] [ebp-C0h] BYREF
  TransformMatrix to; // [esp+7Ch] [ebp-80h] BYREF
  float x; // [esp+ECh] [ebp-10h]
  float y; // [esp+F0h] [ebp-Ch]
  float v56; // [esp+F4h] [ebp-8h]
  Vec3 v57; // 0:^1C.12

  state = cutscene->state;
  cutscene->force_camera_update = 0;
  switch ( state )
  {
    case CUT_SCENE_STATE_INTRO_PENDING:
      presentation = cutscene->presentation;
      cutscene->state = CUT_SCENE_STATE_INTRO_ACTIVE;
      cutscene->progress = 0.0;
      cutscene->progress_step = 0.0083333338;
      cutscene->force_camera_update = 1;
      dispatch_cutscene_animation(presentation, 9, 1u, -1);
      dispatch_cutscene_animation(cutscene->presentation, 9, 0, -1);
      dispatch_cutscene_animation(cutscene->presentation, 1, 0, -1);
      goto LABEL_3;
    case CUT_SCENE_STATE_INTRO_ACTIVE:
LABEL_3:
      cutscene->camera_mode = 1;
      set_matrix_identity(&cutscene->live_matrix);
      v4 = &cutscene->presentation->snail_hotspots_world[18];
      alpha = &cutscene->presentation->body.transform.position;
      cutscene->live_matrix.position.x = v4->x;
      cutscene->live_matrix.position.y = v4->y;
      cutscene->live_matrix.position.z = v4->z;
      look_at_point(&cutscene->live_matrix, alpha);
      v5 = cutscene->progress + cutscene->progress_step;
      cutscene->progress = v5;
      if ( v5 > 1.0 )
      {
        cutscene->progress_step = 0.0083333338;
        cutscene->state = CUT_SCENE_STATE_INTRO_RETURN_BLEND;
        cutscene->progress = 0.0;
      }
      return;
    case CUT_SCENE_STATE_COMPLETION_PENDING:
      v19 = cutscene->presentation;
      cutscene->state = CUT_SCENE_STATE_COMPLETION_HOLD;
      cutscene->camera_mode = -1;
      dispatch_cutscene_animation(v19, 8, 1u, -1);
      dispatch_cutscene_animation(cutscene->presentation, 9, 0, -1);
      dispatch_cutscene_animation(cutscene->presentation, 9, 0, -1);
      v20 = cutscene->presentation;
      cutscene->state = CUT_SCENE_STATE_COMPLETION_BLEND;
      cutscene->progress = 0.0;
      cutscene->progress_step = 0.0083333338;
      v20->invincible_shell.cutscene_roll_step = 0.016666668;
      cutscene->presentation->invincible_shell.cutscene_roll_progress = cutscene->presentation->invincible_shell.cutscene_roll_step;
      cutscene->force_camera_update = 1;
      level_mode = g_game_base->subgame.level_mode;
      if ( level_mode )
      {
        if ( level_mode == 1 )
          initialize_completion_screen(&g_game_base->subgame.completion, cutscene->player->parcels_collected, 1u);
      }
      else
      {
        initialize_completion_screen(
          &g_game_base->subgame.completion,
          cutscene->player->parcels_collected,
          cutscene->player->parcels_collected == g_game_base->subgame.level_definition.parcel_count);
      }
      play_sound_effect(46);
      goto LABEL_25;
    case CUT_SCENE_STATE_COMPLETION_BLEND:
LABEL_25:
      cutscene->camera_mode = -1;
      set_matrix_identity(&to);
      v22 = &cutscene->presentation->snail_hotspots_world[18];
      transform.position = cutscene->presentation->snail_hotspots_world[12];
      x = v22->x;
      z = v22->z;
      y = v22->y;
      progress = cutscene->progress;
      v56 = z;
      v45 = y - transform.position.y;
      v47 = z - transform.position.z;
      v50 = v45 * progress;
      v51 = v47 * progress;
      v43 = (x - transform.position.x) * progress + transform.position.x;
      to.position.x = v43;
      v46 = transform.position.y + v50;
      to.position.y = v46;
      v48 = transform.position.z + v51;
      v25 = cutscene->progress * 3.1415927;
      to.position.z = v48;
      alphah = v25;
      v26 = sine(alphah);
      alphai = &cutscene->presentation->body.transform.position;
      to.position.x = to.position.x - v26 * 0.5;
      look_at_point(&to, alphai);
      qmemcpy(&transform, &cutscene->presentation->owner_player->cameraman, sizeof(transform));
      alphaj = cutscene->progress * 1.5707964;
      alphak = sine(alphaj);
      linear_interpolate_matrix(&cutscene->live_matrix, &transform, &to, alphak);
      v27 = cutscene->progress + cutscene->progress_step;
      cutscene->progress = v27;
      if ( v27 > 1.0 )
      {
        cutscene->state = CUT_SCENE_STATE_COMPLETION_HOLD;
        cutscene->progress = 0.0;
        cutscene->progress_step = 0.016666668;
      }
      return;
    case CUT_SCENE_STATE_COMPLETION_HOLD:
      cutscene->camera_mode = -1;
      cutscene->force_camera_update = 1;
      set_matrix_identity(&cutscene->live_matrix);
      v28 = &cutscene->presentation->snail_hotspots_world[18];
      alphal = &cutscene->presentation->body.transform.position;
      cutscene->live_matrix.position.x = v28->x;
      cutscene->live_matrix.position.y = v28->y;
      cutscene->live_matrix.position.z = v28->z;
      look_at_point(&cutscene->live_matrix, alphal);
      if ( !cutscene->presentation->anim_manager.queue_count )
        dispatch_cutscene_animation(cutscene->presentation, 9, 0, -1);
      goto LABEL_29;
    case CUT_SCENE_STATE_INTRO_RETURN_BLEND:
      *((_BYTE *)&g_player_intro_cutscene_latch_offset + (_DWORD)g_game_base) = 0;
      cutscene->camera_mode = 1;
      set_matrix_identity(&transform);
      v6 = cutscene->progress * 3.1415927;
      transform.position = cutscene->presentation->snail_hotspots_world[18];
      alphaa = v6;
      v7 = sine(alphaa);
      alphab = &cutscene->presentation->body.transform.position;
      transform.position.x = v7 + v7 + transform.position.x;
      look_at_point(&transform, alphab);
      qmemcpy(&to, &cutscene->presentation->owner_player->cameraman, sizeof(to));
      alphac = cutscene->progress * 1.5707964;
      alphad = sine(alphac);
      linear_interpolate_matrix(&cutscene->live_matrix, &transform, &to, alphad);
      v57.x = cutscene->live_matrix.position.x - cutscene->presentation->body.transform.position.x;
      v57.y = cutscene->live_matrix.position.y - cutscene->presentation->body.transform.position.y;
      v57.z = cutscene->live_matrix.position.z - cutscene->presentation->body.transform.position.z;
      vector = v57;
      v8 = normalize_vector(&vector);
      if ( v8 < 1.5 )
      {
        v9 = 1.5 - v8;
        v42 = vector.x * v9;
        v44 = vector.y * v9;
        v10 = v9 * vector.z;
        cutscene->live_matrix.position.x = v42 + cutscene->live_matrix.position.x;
        cutscene->live_matrix.position.y = v44 + cutscene->live_matrix.position.y;
        cutscene->live_matrix.position.z = v10 + cutscene->live_matrix.position.z;
      }
      v11 = cutscene->progress + cutscene->progress_step;
      cutscene->progress = v11;
      if ( v11 > 1.0 )
      {
        cutscene->state = CUT_SCENE_STATE_INTRO_FINISH;
        cutscene->progress = 0.0;
        cutscene->progress_step = 0.0083333338;
      }
      return;
    case CUT_SCENE_STATE_INTRO_FINISH:
      qmemcpy(&cutscene->live_matrix, &cutscene->presentation->owner_player->cameraman, sizeof(cutscene->live_matrix));
      cutscene->state = CUT_SCENE_STATE_INACTIVE;
      return;
    case CUT_SCENE_STATE_DEATH_PENDING:
      v12 = cutscene->presentation;
      cutscene->camera_mode = -1;
      dispatch_cutscene_animation(v12, 7, 1u, -1);
      cutscene->state = CUT_SCENE_STATE_DEATH_BLEND;
      cutscene->progress = 0.0;
      cutscene->progress_step = 0.0083333338;
      cutscene->force_camera_update = 1;
      play_voice_manager((int)g_voice_manager, 3, 2u, -1);
      cutscene->presentation->owner_player->attachment_exit_gate_a = 1;
      release_snail_weapons((int)cutscene->presentation);
      goto LABEL_11;
    case CUT_SCENE_STATE_DEATH_BLEND:
LABEL_11:
      cutscene->camera_mode = -1;
      set_matrix_identity(&to);
      v13 = cutscene->progress * 3.1415927;
      to.position = cutscene->presentation->snail_hotspots_world[18];
      alphae = v13;
      v14 = sine(alphae);
      to.position.x = v14 + v14 + to.position.x;
      if ( to.position.y < 0.0 )
        to.position.y = 0.0;
      look_at_point(&to, &cutscene->presentation->body.transform.position);
      v15 = cutscene->progress;
      qmemcpy(&transform, &cutscene->presentation->owner_player->cameraman, sizeof(transform));
      alphaf = v15 * 1.5707964;
      alphag = sine(alphaf);
      linear_interpolate_matrix(&cutscene->live_matrix, &transform, &to, alphag);
      v16 = cutscene->progress + cutscene->progress_step;
      cutscene->progress = v16;
      if ( v16 > 1.0 )
      {
        cutscene->state = CUT_SCENE_STATE_DEATH_HOLD;
        cutscene->progress = 0.0;
        cutscene->progress_step = 0.016666668;
      }
      break;
    case CUT_SCENE_STATE_DEATH_HOLD:
      cutscene->camera_mode = -1;
      cutscene->force_camera_update = 1;
      set_matrix_identity(&cutscene->live_matrix);
      v17 = cutscene->presentation;
      cutscene->live_matrix.position.x = cutscene->presentation->snail_hotspots_world[18].x;
      cutscene->live_matrix.position.y = v17->snail_hotspots_world[18].y;
      cutscene->live_matrix.position.z = v17->snail_hotspots_world[18].z;
      if ( cutscene->live_matrix.position.y < 0.0 )
        cutscene->live_matrix.position.y = 0.0;
      look_at_point(&cutscene->live_matrix, &v17->body.transform.position);
      player = cutscene->player;
      if ( LOBYTE(player->resurrect_active)
        || (initialize_subgoldy_death(player), cutscene->player->attachment_exit_gate_b) )
      {
LABEL_29:
        cutscene->progress = cutscene->progress_step + cutscene->progress;
      }
      else
      {
        play_voice_manager((int)g_voice_manager, 11, 2u, -1);
        cutscene->player->attachment_exit_gate_b = 1;
        cutscene->player->attachment_exit_gate_a = 1;
        cutscene->progress = cutscene->progress_step + cutscene->progress;
      }
      break;
    default:
      return;
  }
}
