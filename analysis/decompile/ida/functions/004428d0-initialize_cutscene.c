/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_cutscene @ 0x4428d0 */
/* selector: initialize_cutscene */

// Seeds and polls the player-side cutscene controller from the live player transform, the cached snail-hotspot transforms, and the completion handoff state; Windows `update_subgoldy` calls it every tick, and it dispatches `update_cutscene` whenever the controller is active. Cross-port Android symbols still match the helper family to `cRCutScene::Init()`.
int32_t __thiscall initialize_cutscene(PlayerPresentationController *presentation)
{
  int32_t result; // eax
  Player *owner_player; // ecx
  Player *v4; // ecx
  TransformMatrix *p_live_matrix; // eax
  double v6; // st7
  float *pad_00; // eax
  TransformMatrix *v8; // ebp
  const void *v9; // esi
  double y; // st7
  double v11; // st7
  unsigned __int8 v13; // c0
  unsigned __int8 v14; // c3
  double v15; // st7
  unsigned __int8 v17; // c0
  unsigned __int8 v18; // c3
  TransformMatrix *v19; // edx
  double v20; // st7
  double v21; // st7
  double v22; // st7
  double v23; // st7
  float *v24; // eax
  const void *v25; // esi
  float v26; // [esp+0h] [ebp-170h]
  float v27; // [esp+0h] [ebp-170h]
  float v28; // [esp+0h] [ebp-170h]
  float v29; // [esp+0h] [ebp-170h]
  float v30; // [esp+0h] [ebp-170h]
  float v31; // [esp+14h] [ebp-15Ch]
  float v32; // [esp+18h] [ebp-158h]
  float v33; // [esp+1Ch] [ebp-154h]
  float v34; // [esp+24h] [ebp-14Ch]
  float v35; // [esp+28h] [ebp-148h]
  TransformMatrix v36; // [esp+30h] [ebp-140h] BYREF
  TransformMatrix v37; // [esp+70h] [ebp-100h] BYREF
  TransformMatrix v38; // [esp+B0h] [ebp-C0h] BYREF
  TransformMatrix v39; // [esp+F0h] [ebp-80h] BYREF
  TransformMatrix v40; // [esp+130h] [ebp-40h] BYREF

  result = (int32_t)MEMORY[0x4DF904];
  if ( !*((_BYTE *)MEMORY[0x4DF904] + 476705) )
  {
    update_snail_skin_transition(&presentation->snail_skin_transition);
    owner_player = presentation->owner_player;
    if ( owner_player->cutscene_pitch_cycle <= 0.0 )
    {
      if ( owner_player->attachment_exit_pending )
      {
        qmemcpy(&v36, &owner_player->live_matrix, sizeof(v36));
        qmemcpy(&v37, &owner_player->live_matrix, sizeof(v37));
        set_matrix_rotation_identity(&v36);
        linear_interpolate_matrix(&presentation->owner_player->live_matrix, &v36, &v37, 0.97000003);
      }
    }
    else
    {
      owner_player->cutscene_pitch_cycle = owner_player->cutscene_pitch_cycle_step + owner_player->cutscene_pitch_cycle;
      v4 = presentation->owner_player;
      if ( v4->cutscene_pitch_cycle > 1.0 )
        v4->cutscene_pitch_cycle = 0.0;
      p_live_matrix = &presentation->owner_player->live_matrix;
      qmemcpy(&v36, p_live_matrix, sizeof(v36));
      qmemcpy(&v37, p_live_matrix, sizeof(v37));
      set_matrix_rotation_identity(&v36);
      v6 = (-0.78539819 - presentation->owner_player->cutscene_pitch_cycle * 6.2831855) * 1.4;
      v31 = v6;
      if ( v6 < -6.2831855 )
        v31 = -6.2831855;
      rotate_matrix_world_x(&v36, v31);
      linear_interpolate_matrix(&presentation->owner_player->live_matrix, &v36, &v37, 0.94);
    }
    pad_00 = (float *)presentation->owner_player->_pad_00;
    v8 = &presentation->live_matrix;
    v9 = pad_00 + 14;
    pad_00 += 2649;
    qmemcpy(&presentation->live_matrix, v9, sizeof(presentation->live_matrix));
    presentation->live_matrix.position.x = *pad_00;
    presentation->live_matrix.position.y = pad_00[1];
    presentation->live_matrix.position.z = pad_00[2];
    qmemcpy(&v36, &presentation->live_matrix, sizeof(v36));
    linear_interpolate_matrix(&presentation->live_matrix, &v36, &presentation->cached_cutscene_matrix, 0.69999999);
    y = presentation->live_matrix.basis_up.y;
    presentation->live_matrix.position.x = v36.position.x;
    presentation->live_matrix.position.y = v36.position.y;
    presentation->live_matrix.position.z = v36.position.z;
    if ( y > 0.0 )
    {
      v26 = (presentation->live_matrix.position.x - presentation->cached_cutscene_matrix.position.x) * 0.80000001;
      rotate_matrix_world_y(&presentation->live_matrix, v26);
    }
    v11 = presentation->wobble.roll_phase_step + presentation->wobble.roll_phase;
    presentation->wobble.roll_phase = v11;
    if ( !(v13 | v14) )
      presentation->wobble.roll_phase = v11 - 1.0;
    v15 = presentation->wobble.lift_phase_step + presentation->wobble.lift_phase;
    presentation->wobble.lift_phase = v15;
    if ( !(v17 | v18) )
      presentation->wobble.lift_phase = v15 - 1.0;
    qmemcpy(&v40, v8, sizeof(v40));
    set_matrix_identity(&v38);
    v27 = presentation->wobble.roll_phase * 6.2831855;
    v28 = sine(v27) * 0.017449999;
    rotate_matrix_world_z(&v38, v28);
    invert_matrix_from_source(&v39, v19);
    multiply_matrix_in_place(&presentation->live_matrix, &v39);
    presentation->live_matrix.position.y = presentation->live_matrix.position.y + 1.3;
    multiply_matrix_in_place(&presentation->live_matrix, &v38);
    presentation->live_matrix.position.y = presentation->live_matrix.position.y - 1.3;
    multiply_matrix_in_place(&presentation->live_matrix, &v40);
    v29 = presentation->wobble.lift_phase * 6.2831855;
    v20 = sine(v29);
    v32 = v20 * presentation->live_matrix.basis_up.x;
    v33 = v20 * presentation->live_matrix.basis_up.y;
    v21 = v20 * presentation->live_matrix.basis_up.z;
    v34 = v32 * 0.029999999;
    v35 = v33 * 0.029999999;
    presentation->live_matrix.position.x = v34 + presentation->live_matrix.position.x;
    presentation->live_matrix.position.y = v35 + presentation->live_matrix.position.y;
    presentation->live_matrix.position.z = v21 * 0.029999999 + presentation->live_matrix.position.z;
    v22 = *(float *)&presentation->invincible_shell._pad_90[4];
    qmemcpy(&presentation->cached_cutscene_matrix, v8, sizeof(presentation->cached_cutscene_matrix));
    if ( v22 > 0.0 )
    {
      v30 = *(float *)&presentation->invincible_shell._pad_90[4] * -2.0943952;
      rotate_matrix_world_y(&presentation->live_matrix, v30);
      v23 = *(float *)&presentation->invincible_shell._pad_90[8] + *(float *)&presentation->invincible_shell._pad_90[4];
      *(float *)&presentation->invincible_shell._pad_90[4] = v23;
      if ( v23 > 1.0 )
        *(_DWORD *)&presentation->invincible_shell._pad_90[4] = 1065353216;
    }
    if ( presentation->invincible_shell._pad_90[12] )
    {
      presentation->jetpack_channel.live_matrix.position.x = presentation->jetpack_channel.release_step.x
                                                           + presentation->jetpack_channel.live_matrix.position.x;
      presentation->jetpack_channel.live_matrix.position.y = presentation->jetpack_channel.release_step.y
                                                           + presentation->jetpack_channel.live_matrix.position.y;
      presentation->jetpack_channel.live_matrix.position.z = presentation->jetpack_channel.release_step.z
                                                           + presentation->jetpack_channel.live_matrix.position.z;
      presentation->weapon_channels[0].live_matrix.position.x = presentation->weapon_channels[0].release_step.x
                                                              + presentation->weapon_channels[0].live_matrix.position.x;
      presentation->weapon_channels[0].live_matrix.position.y = presentation->weapon_channels[0].release_step.y
                                                              + presentation->weapon_channels[0].live_matrix.position.y;
      presentation->weapon_channels[0].live_matrix.position.z = presentation->weapon_channels[0].release_step.z
                                                              + presentation->weapon_channels[0].live_matrix.position.z;
      presentation->weapon_channels[2].live_matrix.position.x = presentation->weapon_channels[2].release_step.x
                                                              + presentation->weapon_channels[2].live_matrix.position.x;
      presentation->weapon_channels[2].live_matrix.position.y = presentation->weapon_channels[2].release_step.y
                                                              + presentation->weapon_channels[2].live_matrix.position.y;
      presentation->weapon_channels[2].live_matrix.position.z = presentation->weapon_channels[2].release_step.z
                                                              + presentation->weapon_channels[2].live_matrix.position.z;
      presentation->weapon_channels[1].live_matrix.position.x = presentation->weapon_channels[1].release_step.x
                                                              + presentation->weapon_channels[1].live_matrix.position.x;
      presentation->weapon_channels[1].live_matrix.position.y = presentation->weapon_channels[1].release_step.y
                                                              + presentation->weapon_channels[1].live_matrix.position.y;
      presentation->weapon_channels[1].live_matrix.position.z = presentation->weapon_channels[1].release_step.z
                                                              + presentation->weapon_channels[1].live_matrix.position.z;
    }
    else
    {
      qmemcpy(&presentation->jetpack_channel.live_matrix, v8, sizeof(presentation->jetpack_channel.live_matrix));
      qmemcpy(&presentation->weapon_channels[0].live_matrix, v8, sizeof(presentation->weapon_channels[0].live_matrix));
      qmemcpy(&presentation->weapon_channels[2].live_matrix, v8, sizeof(presentation->weapon_channels[2].live_matrix));
      qmemcpy(&presentation->weapon_channels[1].live_matrix, v8, sizeof(presentation->weapon_channels[1].live_matrix));
    }
    v24 = (float *)presentation->owner_player->_pad_00;
    qmemcpy(&presentation->snail_hotspot_source_matrix_a, v8, sizeof(presentation->snail_hotspot_source_matrix_a));
    v25 = v24 + 14;
    v24 += 2649;
    qmemcpy(&presentation->snail_hotspot_source_matrix_b, v25, sizeof(presentation->snail_hotspot_source_matrix_b));
    presentation->snail_hotspot_source_matrix_b.position.x = *v24;
    presentation->snail_hotspot_source_matrix_b.position.y = v24[1];
    presentation->snail_hotspot_source_matrix_b.position.z = v24[2];
    update_snail_skin(presentation);
    if ( presentation->cutscene_ai.state )
    {
      update_cutscene(&presentation->cutscene_ai);
    }
    else if ( !presentation->anim_manager.queued_animation_count && !presentation->owner_player->control_override_active )
    {
      dispatch_cutscene_animation(presentation, 1, 0, -1);
    }
    update_jet_particles((int)&presentation->owner_player->_pad_2744[8]);
  }
  return result;
}

