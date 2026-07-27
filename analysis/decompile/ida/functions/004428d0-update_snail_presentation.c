/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_snail_presentation @ 0x4428d0 */
/* selector: update_snail_presentation */

// Authored `cRSnail::AIGoldy()`, preserved by Android and iOS: this per-frame presentation method borrows `Player::live_transform()` and `cached_camera_target_world`, advances the Snail's matrices, skin, world hotspots, hover jets and animation channels, and updates the embedded cRCutScene owner. The historical `initialize_cutscene` label remains an alias; the distinct exact `initialize_cutscene_ai @ 0x446130` is the real cRCutScene initializer.
void __thiscall update_snail_presentation(Snail *snail)
{
  Player *owner_player; // ecx
  Player *v3; // ecx
  TransformMatrix *p_transform; // eax
  double v5; // st7
  float *v6; // eax
  TransformMatrix *v7; // ebp
  const void *v8; // esi
  double y; // st7
  double v10; // st7
  unsigned __int8 v12; // c0
  unsigned __int8 v13; // c3
  double v14; // st7
  unsigned __int8 v16; // c0
  unsigned __int8 v17; // c3
  double v18; // st7
  double v19; // st7
  double cutscene_roll_progress; // st7
  double v21; // st7
  float *v22; // eax
  const void *v23; // esi
  float v24; // [esp+0h] [ebp-170h]
  float v25; // [esp+0h] [ebp-170h]
  float v26; // [esp+0h] [ebp-170h]
  float v27; // [esp+0h] [ebp-170h]
  float v28; // [esp+0h] [ebp-170h]
  float angle; // [esp+14h] [ebp-15Ch]
  float v30; // [esp+18h] [ebp-158h]
  float v31; // [esp+1Ch] [ebp-154h]
  float v32; // [esp+24h] [ebp-14Ch]
  float v33; // [esp+28h] [ebp-148h]
  TransformMatrix transform; // [esp+30h] [ebp-140h] BYREF
  TransformMatrix to; // [esp+70h] [ebp-100h] BYREF
  TransformMatrix rhs; // [esp+B0h] [ebp-C0h] BYREF
  TransformMatrix out; // [esp+F0h] [ebp-80h] BYREF
  TransformMatrix v38; // [esp+130h] [ebp-40h] BYREF

  if ( g_game_base->subgame.subgame_pause_gate == 0 )
  {
    update_snail_skin_transition(&snail->snail_skin);
    owner_player = snail->owner_player;
    if ( owner_player->cutscene_pitch_cycle <= 0.0 )
    {
      if ( owner_player->attachment_exit_pending != 0 )
      {
        transform = owner_player->body.transform;
        to = owner_player->body.transform;
        set_matrix_rotation_identity(&transform);
        linear_interpolate_matrix(&snail->owner_player->body.transform, &transform, &to, 0.97000003);
      }
    }
    else
    {
      owner_player->cutscene_pitch_cycle = owner_player->cutscene_pitch_cycle_step + owner_player->cutscene_pitch_cycle;
      v3 = snail->owner_player;
      if ( v3->cutscene_pitch_cycle > 1.0 )
        v3->cutscene_pitch_cycle = 0.0;
      p_transform = &snail->owner_player->body.transform;
      transform = *p_transform;
      to = *p_transform;
      set_matrix_rotation_identity(&transform);
      v5 = (-0.78539819 - snail->owner_player->cutscene_pitch_cycle * 6.2831855) * 1.4;
      angle = v5;
      if ( v5 < -6.2831855 )
        angle = -6.2831855;
      rotate_matrix_local_x(&transform, angle);
      linear_interpolate_matrix(&snail->owner_player->body.transform, &transform, &to, 0.94);
    }
    v6 = (float *)snail->owner_player;
    v7 = &snail->body.transform;
    v8 = v6 + 14;
    v6 += 2649;
    qmemcpy(&snail->body.transform, v8, sizeof(snail->body.transform));
    snail->body.transform.position.x = *v6;
    snail->body.transform.position.y = v6[1];
    snail->body.transform.position.z = v6[2];
    transform = snail->body.transform;
    linear_interpolate_matrix(&snail->body.transform, &transform, &snail->cached_cutscene_matrix, 0.69999999);
    y = snail->body.transform.basis_up.y;
    snail->body.transform.position = transform.position;
    if ( y > 0.0 )
    {
      v24 = (snail->body.transform.position.x - snail->cached_cutscene_matrix.position.x) * 0.80000001;
      rotate_matrix_local_y(&snail->body.transform, v24);
    }
    v10 = snail->wobble.roll_phase_step + snail->wobble.roll_phase;
    snail->wobble.roll_phase = v10;
    if ( (v12 | v13) == 0 )
      snail->wobble.roll_phase = v10 - 1.0;
    v14 = snail->wobble.lift_phase_step + snail->wobble.lift_phase;
    snail->wobble.lift_phase = v14;
    if ( (v16 | v17) == 0 )
      snail->wobble.lift_phase = v14 - 1.0;
    v38 = *v7;
    set_matrix_identity(&rhs);
    v25 = snail->wobble.roll_phase * 6.2831855;
    v26 = sine(v25) * 0.017449999;
    rotate_matrix_local_z(&rhs, v26);
    invert_matrix_from_source(&out, &snail->body.transform);
    multiply_matrix_assign(&snail->body.transform, &out);
    snail->body.transform.position.y = snail->body.transform.position.y + 1.3;
    multiply_matrix_assign(&snail->body.transform, &rhs);
    snail->body.transform.position.y = snail->body.transform.position.y - 1.3;
    multiply_matrix_assign(&snail->body.transform, &v38);
    v27 = snail->wobble.lift_phase * 6.2831855;
    v18 = sine(v27);
    v30 = v18 * snail->body.transform.basis_up.x;
    v31 = v18 * snail->body.transform.basis_up.y;
    v19 = v18 * snail->body.transform.basis_up.z;
    v32 = v30 * 0.029999999;
    v33 = v31 * 0.029999999;
    snail->body.transform.position.x = v32 + snail->body.transform.position.x;
    snail->body.transform.position.y = v33 + snail->body.transform.position.y;
    snail->body.transform.position.z = v19 * 0.029999999 + snail->body.transform.position.z;
    cutscene_roll_progress = snail->cutscene_roll_progress;
    qmemcpy(&snail->cached_cutscene_matrix, v7, sizeof(snail->cached_cutscene_matrix));
    if ( cutscene_roll_progress > 0.0 )
    {
      v28 = snail->cutscene_roll_progress * -2.0943952;
      rotate_matrix_local_y(&snail->body.transform, v28);
      v21 = snail->cutscene_roll_step + snail->cutscene_roll_progress;
      snail->cutscene_roll_progress = v21;
      if ( v21 > 1.0 )
        snail->cutscene_roll_progress = 1.0;
    }
    if ( snail->channel_release_steps_active != 0 )
    {
      snail->jetpack_channel.body.transform.position.x = snail->jetpack_channel.release_step.x
                                                       + snail->jetpack_channel.body.transform.position.x;
      snail->jetpack_channel.body.transform.position.y = snail->jetpack_channel.release_step.y
                                                       + snail->jetpack_channel.body.transform.position.y;
      snail->jetpack_channel.body.transform.position.z = snail->jetpack_channel.release_step.z
                                                       + snail->jetpack_channel.body.transform.position.z;
      snail->weapon_channels[0].body.transform.position.x = snail->weapon_channels[0].release_step.x
                                                          + snail->weapon_channels[0].body.transform.position.x;
      snail->weapon_channels[0].body.transform.position.y = snail->weapon_channels[0].release_step.y
                                                          + snail->weapon_channels[0].body.transform.position.y;
      snail->weapon_channels[0].body.transform.position.z = snail->weapon_channels[0].release_step.z
                                                          + snail->weapon_channels[0].body.transform.position.z;
      snail->weapon_channels[2].body.transform.position.x = snail->weapon_channels[2].release_step.x
                                                          + snail->weapon_channels[2].body.transform.position.x;
      snail->weapon_channels[2].body.transform.position.y = snail->weapon_channels[2].release_step.y
                                                          + snail->weapon_channels[2].body.transform.position.y;
      snail->weapon_channels[2].body.transform.position.z = snail->weapon_channels[2].release_step.z
                                                          + snail->weapon_channels[2].body.transform.position.z;
      snail->weapon_channels[1].body.transform.position.x = snail->weapon_channels[1].release_step.x
                                                          + snail->weapon_channels[1].body.transform.position.x;
      snail->weapon_channels[1].body.transform.position.y = snail->weapon_channels[1].release_step.y
                                                          + snail->weapon_channels[1].body.transform.position.y;
      snail->weapon_channels[1].body.transform.position.z = snail->weapon_channels[1].release_step.z
                                                          + snail->weapon_channels[1].body.transform.position.z;
    }
    else
    {
      qmemcpy(&snail->jetpack_channel.body.transform, v7, sizeof(snail->jetpack_channel.body.transform));
      qmemcpy(&snail->weapon_channels[0].body.transform, v7, sizeof(snail->weapon_channels[0].body.transform));
      qmemcpy(&snail->weapon_channels[2].body.transform, v7, sizeof(snail->weapon_channels[2].body.transform));
      qmemcpy(&snail->weapon_channels[1].body.transform, v7, sizeof(snail->weapon_channels[1].body.transform));
    }
    v22 = (float *)snail->owner_player;
    qmemcpy(&snail->snail_hotspot_source_body.transform, v7, sizeof(snail->snail_hotspot_source_body.transform));
    v23 = v22 + 14;
    v22 += 2649;
    qmemcpy(&snail->snail_hotspot_body.transform, v23, sizeof(snail->snail_hotspot_body.transform));
    snail->snail_hotspot_body.transform.position.x = *v22;
    snail->snail_hotspot_body.transform.position.y = v22[1];
    snail->snail_hotspot_body.transform.position.z = v22[2];
    build_snail_world_hotspots(snail);
    if ( snail->cutscene.state != CUT_SCENE_STATE_INACTIVE )
    {
      update_cutscene(&snail->cutscene);
    }
    else if ( snail->anim_manager.queue_count == 0 && snail->owner_player->control_override_active == 0 )
    {
      dispatch_cutscene_animation(snail, 1, 0, -1);
    }
    update_jet_particles(&snail->owner_player->sub_hover);
  }
}
