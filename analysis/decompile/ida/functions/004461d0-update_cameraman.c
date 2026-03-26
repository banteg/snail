/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_cameraman @ 0x4461d0 */
/* selector: update_cameraman */

// Builds the live follow-camera pose from player transform, attachment state, motion scalars, and backdrop zoom before handing the matrix back to `update_subgame_camera`. Cross-port Android and iOS symbols match this helper to `cRCameraman::AI()`.
int32_t __thiscall update_cameraman(CameramanState *cameraman)
{
  Player *player; // eax
  TransformMatrix *p_desired_matrix; // ebx
  Player *v4; // ecx
  double v5; // st7
  double v6; // st7
  double v7; // st6
  Player *v8; // ecx
  PathTemplate *template_record; // edx
  PathTemplateKind kind; // eax
  double v11; // st7
  Player *v12; // ecx
  Player *v13; // ecx
  double v14; // st7
  double v15; // st7
  double v16; // st6
  double v17; // st7
  float *pad_00; // esi
  Player *v19; // eax
  Player *v20; // eax
  PathTemplate *v21; // ecx
  double v22; // st7
  double v23; // st7
  Game *game; // eax
  int32_t result; // eax
  float v26; // [esp+0h] [ebp-64h]
  float v27; // [esp+Ch] [ebp-58h]
  float v28; // [esp+Ch] [ebp-58h]
  float v29; // [esp+Ch] [ebp-58h]
  float v30; // [esp+Ch] [ebp-58h]
  float v31; // [esp+Ch] [ebp-58h]
  float v32; // [esp+Ch] [ebp-58h]
  float v33; // [esp+Ch] [ebp-58h]
  float v34; // [esp+20h] [ebp-44h]
  float v35; // [esp+20h] [ebp-44h]
  float v36; // [esp+20h] [ebp-44h]
  TransformMatrix v37; // [esp+24h] [ebp-40h] BYREF

  player = cameraman->player;
  cameraman->unresolved_cc = 0;
  p_desired_matrix = &cameraman->desired_matrix;
  v26 = player->cached_camera_target_world.x * 0.40000001;
  qmemcpy(
    &cameraman->desired_matrix,
    initialize_matrix_from_values(
      &v37,
      1.0,
      0.0,
      0.0,
      0.0,
      0.0,
      0.94600099,
      0.32416201,
      0.0,
      0.0,
      -0.32416201,
      0.94600099,
      0.0,
      v26,
      1.8,
      -0.5,
      1.0),
    sizeof(cameraman->desired_matrix));
  orthogonalize_matrix(&cameraman->desired_matrix);
  v4 = cameraman->player;
  v5 = (double)*((int *)cameraman->game + 20);
  if ( v5 <= v4->cached_camera_target_world.z )
  {
    cameraman->desired_matrix.position.y = v4->cached_camera_target_world.y * 0.34999999
                                         + cameraman->desired_matrix.position.y;
  }
  else
  {
    v6 = v4->cached_camera_target_world.z / v5 * 1.4 - 0.40000001;
    if ( v6 >= 0.0 )
    {
      if ( v6 > 1.0 )
        v6 = 1.0;
    }
    else
    {
      v6 = 0.0;
    }
    v34 = 1.0 - v6;
    v7 = (1.0 - v6) * v4->cached_camera_target_world.y * 1.15 + cameraman->desired_matrix.position.y;
    cameraman->desired_matrix.position.y = v7;
    cameraman->desired_matrix.position.y = v6 * 0.34999999 * v4->cached_camera_target_world.y + v7;
    v27 = v34 * 0.87249994;
    rotate_matrix_world_x(&cameraman->desired_matrix, v27);
  }
  v8 = cameraman->player;
  if ( v8->follow_state.active == 1
    && ((template_record = v8->follow_state.template_record,
         kind = template_record->kind,
         kind == PATH_TEMPLATE_KIND_FAMILY_10)
     || kind == 8
     || kind == 9
     || kind == 10
     || kind == PATH_TEMPLATE_KIND_TWISTER
     || kind == PATH_TEMPLATE_KIND_TWISTER2
     || kind == PATH_TEMPLATE_KIND_START
     || kind == (PATH_TEMPLATE_KIND_LOOPTHELOOPW|0x8)) )
  {
    v11 = (v8->position.z - v8->follow_state.source_cell->anchor_position.z) / template_record->segment_count_f;
    if ( v11 >= 0.0 )
    {
      if ( v11 > 1.0 )
        v11 = 1.0;
    }
    else
    {
      v11 = 0.0;
    }
    v28 = v11 * 6.2831855;
    cameraman->attachment_lift_envelope = (0.5 - cosine(v28) * 0.5) * 0.34999999;
  }
  else
  {
    cameraman->attachment_lift_envelope = 0.0;
  }
  v12 = cameraman->player;
  if ( v12->cutscene_pitch_cycle > 0.0 )
  {
    v29 = v12->cutscene_pitch_cycle * 4.712389 + 1.5707964;
    cameraman->attachment_lift_envelope = (0.5 - cosine(v29) * 0.5) * 0.23999999 + cameraman->attachment_lift_envelope;
  }
  v13 = cameraman->player;
  v14 = (cameraman->attachment_lift_envelope - cameraman->smoothed_attachment_lift_envelope) * 0.1
      + cameraman->smoothed_attachment_lift_envelope;
  cameraman->smoothed_attachment_lift_envelope = v14;
  cameraman->desired_matrix.position.y = v14 * v13->cached_camera_target_world.y + cameraman->desired_matrix.position.y;
  cameraman->desired_matrix.position.x = v13->cached_camera_target_world.x * 0.33333334
                                       + cameraman->desired_matrix.position.x;
  v15 = v13->cached_camera_target_world.z + cameraman->desired_matrix.position.z + 0.40000001;
  cameraman->desired_matrix.position.z = v15;
  v16 = v15 - cameraman->previous_desired_matrix.position.z;
  if ( v16 <= 3.0 )
  {
    if ( v16 < 1.7 )
      cameraman->previous_desired_matrix.position.z = v15 - 1.7;
  }
  else
  {
    cameraman->previous_desired_matrix.position.z = v15 - 3.0;
  }
  v17 = (-2.0 - (v13->cached_camera_target_world.y - 0.49000001) * 5.0) * 0.017449999;
  v35 = v17;
  if ( v17 >= -1.2214999 )
  {
    if ( v35 > 1.2214999 )
      v35 = 1.2214999;
    rotate_matrix_world_x(&cameraman->desired_matrix, v35);
  }
  else
  {
    rotate_matrix_world_x(&cameraman->desired_matrix, -1.2214999);
  }
  pad_00 = (float *)cameraman->player->_pad_00;
  v30 = pad_00[214] * 3.1415927;
  v31 = (0.5 - cosine(v30) * 0.5) * pad_00[213] * 6.2831855 + pad_00[2649] * -8.0 * 0.017449999 * 0.17;
  rotate_matrix_world_z(&cameraman->desired_matrix, v31);
  if ( cameraman->player->follow_state.active == 1 )
  {
    set_matrix_identity(&v37);
    rotate_matrix_world_z(&v37, cameraman->player->follow_state.orientation_a);
    multiply_matrix_in_place(&cameraman->desired_matrix, &v37);
    rotate_matrix_world_z(&cameraman->desired_matrix, cameraman->player->follow_state.orientation_b);
  }
  v19 = cameraman->player;
  if ( v19->attachment_exit_pending )
    rotate_matrix_world_z(&cameraman->desired_matrix, v19->post_follow_value_a);
  rotate_matrix_world_z(&cameraman->desired_matrix, *(float *)&cameraman->player->_pad_340[48]);
  v20 = cameraman->player;
  if ( v20->follow_state.active == 1 && (v21 = v20->follow_state.template_record, v21->kind == PATH_TEMPLATE_KIND_WORM) )
  {
    v22 = (v20->position.z - v20->follow_state.source_cell->anchor_position.z) / v21->segment_count_f;
    if ( v22 >= 0.0 )
    {
      if ( v22 > 1.0 )
        v22 = 1.0;
    }
    else
    {
      v22 = 0.0;
    }
    v32 = v22 * 6.2831855;
    v36 = 0.5 - cosine(v32) * 0.5;
    sub_449C00();
    v23 = v36 * 50.0 + 110.0;
  }
  else
  {
    v23 = 110.0;
  }
  game = cameraman->game;
  cameraman->fov_degrees = (v23 - cameraman->fov_degrees) * 0.30000001 + cameraman->fov_degrees;
  v33 = *((float *)game + 14) * 0.30000001;
  result = (int32_t)linear_interpolate_matrix(
                      &cameraman->live_matrix,
                      &cameraman->previous_desired_matrix,
                      &cameraman->desired_matrix,
                      v33);
  qmemcpy(&cameraman->previous_desired_matrix, p_desired_matrix, sizeof(cameraman->previous_desired_matrix));
  return result;
}

