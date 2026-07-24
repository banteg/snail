/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: calc_path_length_z @ 0x4217b0 */
/* selector: calc_path_length_z */

// Advances one Golb projectile attachment-follow session through the borrowed authored `Path::primary_samples`/`secondary_samples` banks and emits the interpolated position or exit velocity. iOS Path.o names this family `cRPathFollowGolb::Traverse(float, tVector&, tVector*)`.
int32_t __thiscall calc_path_length_z(GolbPathFollowState *state, float path_factor, Vec3 *position, Vec3 *velocity)
{
  int32_t sample_index; // ecx
  Path *template_record; // edx
  PathTemplateSample *secondary_samples; // esi
  double v8; // st7
  int32_t v9; // ecx
  double v10; // st6
  int32_t v11; // ebx
  int v12; // edi
  int v13; // eax
  float *p_x; // ecx
  Vec3 *v15; // edx
  Path *v16; // eax
  Path *v17; // edx
  uint32_t segment_count; // esi
  double v19; // st7
  PathTemplateSample *v20; // edx
  double v21; // st6
  PathTemplateSample *v22; // eax
  Vec3 *p_anchor_position; // edx
  double v24; // st7
  double v25; // st6
  double v26; // st6
  double v27; // st6
  float v28; // eax
  Vec3 *v29; // edx
  double v31; // st6
  Vec3 *v32; // esi
  Vec3 *v33; // edx
  Vec3 *p_output_position; // ecx
  double v35; // st7
  double v36; // st6
  PathTemplateSample *v37; // ecx
  double v38; // st7
  float *v39; // esi
  TrackRowCell *source_cell; // ecx
  double v41; // st7
  double v42; // st7
  double v43; // st6
  double v44; // st7
  TransformMatrix *p_flight_transform; // eax
  double v46; // st7
  Path *v47; // edi
  float x; // eax
  Vec3 *p_position; // edx
  float arg2; // [esp+0h] [ebp-114h]
  float alpha; // [esp+Ch] [ebp-108h]
  float v52; // [esp+20h] [ebp-F4h]
  float v53; // [esp+24h] [ebp-F0h]
  float arg1; // [esp+28h] [ebp-ECh] BYREF
  float v55; // [esp+2Ch] [ebp-E8h]
  float v56; // [esp+30h] [ebp-E4h]
  float v57; // [esp+34h] [ebp-E0h]
  float v58; // [esp+38h] [ebp-DCh]
  float v59; // [esp+3Ch] [ebp-D8h]
  float v60; // [esp+40h] [ebp-D4h]
  float v61; // [esp+44h] [ebp-D0h]
  float v62; // [esp+48h] [ebp-CCh]
  float v63; // [esp+4Ch] [ebp-C8h]
  float v64; // [esp+50h] [ebp-C4h]
  TransformMatrix transform; // [esp+54h] [ebp-C0h] BYREF
  TransformMatrix to; // [esp+94h] [ebp-80h] BYREF
  TransformMatrix from; // [esp+D4h] [ebp-40h] BYREF

  sample_index = state->sample_index;
  template_record = state->template_record;
  secondary_samples = template_record->secondary_samples;
  v8 = path_factor * secondary_samples[sample_index].delta_length;
  if ( v8 + state->progress <= secondary_samples[sample_index].delta_length )
  {
LABEL_4:
    v11 = state->sample_index;
    v53 = v8 + state->progress;
    state->progress = v53;
    v12 = template_record->segment_count - 1;
    v13 = v11;
    p_x = &template_record->primary_samples[v11].transform.basis_right.x;
    if ( v11 == v12 )
      v55 = p_x[36];
    else
      v55 = v53 / template_record->secondary_samples[v11].delta_length * (p_x[78] - p_x[36]) + p_x[36];
    if ( v11 == v12 )
      v52 = p_x[39];
    else
      v52 = v53 / template_record->secondary_samples[v13].delta_length * (p_x[81] - p_x[39]) + p_x[39];
    if ( v11 == v12 )
      arg1 = p_x[40];
    else
      arg1 = v53 / template_record->secondary_samples[v13].delta_length * (p_x[82] - p_x[40]) + p_x[40];
    if ( template_record->kind == PATH_TEMPLATE_KIND_NONLINEAR_42 )
    {
      v32 = position;
      arg2 = position->x - v55;
      compute_kind42_attachment_transform(template_record, arg1, arg2, 0.49000001, &transform, &arg1);
      v33 = velocity;
      p_output_position = &state->output_position;
      v35 = state->template_record->secondary_samples[state->sample_index].delta_dir_to_next.z * state->progress
          + state->source_cell->anchor_position.z
          + state->template_record->secondary_samples[state->sample_index].transform.position.z;
      transform.basis_right.x = transform.basis_right.x * v52;
      transform.basis_right.y = transform.basis_right.y * v52;
      transform.basis_right.z = transform.basis_right.z * v52;
      v36 = velocity->y + state->vertical_offset;
      state->output_position.x = transform.position.x;
      state->output_position.y = transform.position.y;
      state->vertical_offset = v36;
      state->output_position.z = v35;
    }
    else
    {
      v37 = template_record->secondary_samples;
      v38 = v53 * v37[v13].delta_dir_to_next.x;
      v39 = &v37[v13].transform.basis_right.x;
      source_cell = state->source_cell;
      v56 = v38 * v52 + v39[12] + source_cell->anchor_position.x;
      v57 = v53 * v39[33] * v52 + v39[13] + source_cell->anchor_position.y;
      v58 = v53 * v39[34] + v39[14] + source_cell->anchor_position.z;
      if ( v11 == v12 )
      {
        set_matrix_identity(&transform);
      }
      else
      {
        qmemcpy(&from, v39, sizeof(from));
        qmemcpy(&to, &template_record->secondary_samples[v11 + 1], sizeof(to));
        memset(&from.position, 0, sizeof(from.position));
        memset(&to.position, 0, sizeof(to.position));
        alpha = v53 / template_record->secondary_samples[v13].delta_length;
        linear_interpolate_matrix(&transform, &from, &to, alpha);
      }
      v33 = velocity;
      v32 = position;
      p_output_position = &state->output_position;
      transform.basis_right.x = transform.basis_right.x * v52;
      transform.basis_right.y = transform.basis_right.y * v52;
      transform.basis_right.z = transform.basis_right.z * v52;
      state->vertical_offset = velocity->y + state->vertical_offset;
      v41 = position->x - v55;
      v62 = v41 * transform.basis_right.x;
      v63 = transform.basis_right.y * v41;
      v42 = v41 * transform.basis_right.z;
      v59 = v62 + v56;
      v43 = v63 + v57;
      state->output_position.x = v59;
      v60 = v43;
      v44 = v42 + v58;
      state->output_position.y = v60;
      v61 = v44;
      state->output_position.z = v61;
    }
    p_flight_transform = &state->shot->flight_transform;
    p_flight_transform->basis_right.x = transform.basis_right.x;
    p_flight_transform->basis_right.y = transform.basis_right.y;
    p_flight_transform->basis_right.z = transform.basis_right.z;
    state->shot->flight_transform.basis_up = transform.basis_up;
    state->shot->flight_transform.basis_forward = transform.basis_forward;
    state->shot->velocity = state->shot->direction;
    v46 = v32->x - v55;
    if ( v46 < 0.0 )
      v46 = -v46;
    v47 = state->template_record;
    if ( v46 <= (double)(int)v47->width_cells * 0.5 + 0.30000001 )
    {
      if ( v47->kind != PATH_TEMPLATE_KIND_NONLINEAR_42 )
        v32->x = v32->x + v33->x;
      return 0;
    }
    else
    {
      x = p_output_position->x;
      p_position = &state->shot->flight_transform.position;
      state->active = 0;
      p_position->x = x;
      p_position->y = p_output_position->y;
      p_position->z = p_output_position->z;
      return state->template_record->side_exit_mode == 0;
    }
  }
  else
  {
    while ( 1 )
    {
      v9 = state->sample_index;
      v10 = secondary_samples[v9].delta_length - state->progress;
      state->progress = 0.0;
      state->sample_index = v9 + 1;
      v8 = v8 - v10;
      if ( v9 + 1 == template_record->segment_count )
        break;
      secondary_samples = template_record->secondary_samples;
      if ( v8 <= secondary_samples[v9 + 1].delta_length )
        goto LABEL_4;
    }
    state->active = 0;
    velocity->z = path_factor * template_record->secondary_samples[template_record->segment_count - 1].delta_length;
    v15 = &state->shot->flight_transform.position;
    v15->x = state->output_position.x;
    v15->y = state->output_position.y;
    v15->z = state->output_position.z;
    v16 = state->template_record;
    if ( v16->kind == PATH_TEMPLATE_KIND_SUPERTRAMP )
    {
      velocity->y = velocity->z * 0.69999999;
      arg1 = position->x;
      v17 = state->template_record;
      segment_count = v17->segment_count;
      v19 = v8 + v17->width_or_scale;
      v20 = v17->secondary_samples;
      v21 = v19 * v20[segment_count - 1].transform.basis_forward.x;
      v22 = &v20[segment_count];
      p_anchor_position = &state->source_cell->anchor_position;
      v59 = v21;
      v60 = v19 * v22[-1].transform.basis_forward.y;
      v24 = v19 * v22[-1].transform.basis_forward.z;
      v25 = p_anchor_position->x + v22[-1].transform.position.x;
      v63 = v22[-1].transform.position.y + p_anchor_position->y;
      v64 = v22[-1].transform.position.z + p_anchor_position->z;
      v56 = v25 + v59;
      v26 = v63 + v60;
      position->x = v56;
      v57 = v26;
      v27 = v64 + v24;
      position->y = v57;
      v58 = v27;
      position->z = v58;
      v28 = arg1;
      position->x = arg1;
      v29 = &state->shot->flight_transform.position;
      v29->x = v28;
      v29->y = position->y;
      v29->z = position->z;
    }
    else
    {
      v31 = v8
          + v16->secondary_samples[v16->segment_count - 1].transform.position.z
          + state->source_cell->anchor_position.z
          + v16->width_or_scale;
      position->z = v31;
      state->shot->flight_transform.position.z = v31;
    }
    return 3;
  }
}
