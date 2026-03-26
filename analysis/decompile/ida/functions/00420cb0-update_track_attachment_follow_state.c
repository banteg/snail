/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_track_attachment_follow_state @ 0x420cb0 */
/* selector: update_track_attachment_follow_state */

// Advances one live attachment-follow session along the current template, updates segment, progress, and local height, writes the interpolated output transform back into the follow struct, and returns a small mode code consumed by `update_subgoldy`. Windows `cdb` confirmed `ARCADE007` produces mid-follow samples with local height `-0.49f`, and the case-1 or case-3 return path feeds one direct fall-state handoff inside `update_subgoldy`. Raw BN plus IDA also show the nearby `voice 4` call guarded by `sample_index + 1 == template->sample_count << 1`, which conflicts with the same helper's `sample_index == template->sample_count` termination under the current typed counters, so that milestone lane remains unresolved rather than ported.
int32_t __thiscall update_track_attachment_follow_state(
        FollowState *follow_state,
        float path_factor,
        Vec3 *out_position,
        Vec3 *motion)
{
  uint32_t sample_index; // ecx
  PathTemplate *template_record; // esi
  PathTemplateSample *secondary_samples; // edx
  double v8; // st7
  float *p_delta_length; // edx
  double v10; // st7
  uint32_t v11; // ecx
  PathTemplate *v12; // eax
  uint32_t segment_count; // eax
  uint32_t v14; // esi
  int v15; // esi
  int track_cell_row_index; // eax
  int v17; // esi
  uint32_t v18; // ebx
  PathTemplate *v19; // edx
  int v20; // edi
  int v21; // eax
  float *p_x; // ecx
  double v23; // st7
  PathTemplate *v24; // edx
  PathTemplate *v25; // ecx
  double v26; // st7
  uint32_t v27; // esi
  double v28; // st6
  PathTemplateSample *v29; // ecx
  double v30; // st5
  PathTemplateSample *v31; // eax
  Vec3 *p_anchor_position; // ecx
  double v33; // st6
  double v34; // st5
  double v35; // st5
  double v36; // st5
  Vec3 *v38; // ebx
  uint32_t v39; // eax
  uint32_t v40; // eax
  Vec3 *p_output_position; // esi
  float *p_y; // edi
  float y; // ecx
  double v44; // st7
  double v45; // st6
  float x; // eax
  char *v47; // edx
  float *v48; // ecx
  char *v49; // eax
  PathTemplateSample *v50; // ecx
  double v51; // st7
  float *v52; // esi
  TrackRowCell *source_cell; // ecx
  double v54; // st7
  double v55; // st7
  double v56; // st6
  double v57; // st6
  double v58; // st5
  char *v59; // eax
  float *v60; // edx
  char *v61; // ecx
  float v62; // edx
  float z; // ecx
  PathTemplate *v64; // edx
  float v65; // eax
  bool v66; // zf
  int v67; // ecx
  int v68; // ecx
  PathTemplateSample *primary_samples; // eax
  double v70; // st7
  PathTemplateSample *v71; // eax
  double v72; // st7
  double v73; // st7
  Player *player; // ecx
  double v75; // st7
  float v76; // [esp+0h] [ebp-1A0h]
  float v77; // [esp+Ch] [ebp-194h]
  float v78; // [esp+20h] [ebp-180h]
  float v79; // [esp+20h] [ebp-180h]
  int v80; // [esp+24h] [ebp-17Ch] BYREF
  float progress; // [esp+28h] [ebp-178h]
  float v82; // [esp+2Ch] [ebp-174h]
  float v83; // [esp+30h] [ebp-170h]
  float v84; // [esp+34h] [ebp-16Ch]
  float v85; // [esp+38h] [ebp-168h]
  TransformMatrix v86; // [esp+3Ch] [ebp-164h] BYREF
  float v87; // [esp+7Ch] [ebp-124h]
  float v88; // [esp+80h] [ebp-120h]
  float v89; // [esp+84h] [ebp-11Ch]
  float v90; // [esp+88h] [ebp-118h]
  float v91; // [esp+8Ch] [ebp-114h]
  float v92; // [esp+94h] [ebp-10Ch]
  float v93; // [esp+98h] [ebp-108h]
  TransformMatrix v94; // [esp+A0h] [ebp-100h] BYREF
  TransformMatrix v95; // [esp+E0h] [ebp-C0h] BYREF
  TransformMatrix v96; // [esp+120h] [ebp-80h] BYREF
  TransformMatrix v97; // [esp+160h] [ebp-40h] BYREF

  sample_index = follow_state->sample_index;
  template_record = follow_state->template_record;
  secondary_samples = template_record->secondary_samples;
  v8 = path_factor * secondary_samples[sample_index].delta_length;
  p_delta_length = &secondary_samples[sample_index].delta_length;
  v78 = v8;
  if ( v8 + follow_state->progress <= *p_delta_length )
  {
LABEL_11:
    v18 = follow_state->sample_index;
    *(float *)&v80 = v78 + follow_state->progress;
    follow_state->progress = *(float *)&v80;
    v19 = follow_state->template_record;
    v20 = v19->segment_count - 1;
    v21 = v18;
    p_x = &v19->primary_samples[v18].transform.basis_right.x;
    if ( v18 == v20 )
      v85 = p_x[36];
    else
      v85 = *(float *)&v80 / v19->secondary_samples[v18].delta_length * (p_x[78] - p_x[36]) + p_x[36];
    if ( v18 == v20 )
      v79 = p_x[39];
    else
      v79 = *(float *)&v80 / v19->secondary_samples[v21].delta_length * (p_x[81] - p_x[39]) + p_x[39];
    if ( v18 == v20 )
      progress = p_x[40];
    else
      progress = *(float *)&v80 / v19->secondary_samples[v21].delta_length * (p_x[82] - p_x[40]) + p_x[40];
    if ( v19->kind == PATH_TEMPLATE_KIND_NONLINEAR_42 )
    {
      v38 = out_position;
      v76 = out_position->x - v85;
      compute_kind42_attachment_transform(progress, v76, 0.49000001, &v86, (float *)&v80);
      v39 = follow_state->sample_index;
      if ( !v39 || v39 == follow_state->template_record->segment_count - 1 )
      {
        set_matrix_identity(&v94);
        v94.position.x = v86.position.x;
        v40 = follow_state->sample_index;
        v94.position.y = v86.position.y;
        v94.position.z = v86.position.z;
        qmemcpy(&v97, &v86, sizeof(v97));
        if ( v40 )
          progress = 1.0 - follow_state->progress;
        else
          progress = follow_state->progress;
        linear_interpolate_matrix(&v86, &v94, &v97, progress);
      }
      p_output_position = &follow_state->output_position;
      p_y = &motion->y;
      y = v86.position.y;
      v44 = follow_state->template_record->secondary_samples[follow_state->sample_index].delta_dir_to_next.z
          * follow_state->progress
          + follow_state->source_cell->anchor_position.z
          + follow_state->template_record->secondary_samples[follow_state->sample_index].transform.position.z;
      v86.basis_right.x = v86.basis_right.x * v79;
      v86.basis_right.y = v86.basis_right.y * v79;
      v86.basis_right.z = v86.basis_right.z * v79;
      v45 = motion->y + follow_state->vertical_offset;
      follow_state->output_position.x = v86.position.x;
      x = v86.basis_right.x;
      follow_state->output_position.y = y;
      follow_state->vertical_offset = v45;
      follow_state->output_position.z = v44;
      v47 = (char *)MEMORY[0x4DF904] + 4390324;
      *((float *)MEMORY[0x4DF904] + 1097581) = x;
      *((_DWORD *)v47 + 1) = LODWORD(v86.basis_right.y);
      *((_DWORD *)v47 + 2) = LODWORD(v86.basis_right.z);
      v48 = (float *)((char *)&loc_42FDC4 + (_DWORD)MEMORY[0x4DF904]);
      *v48 = v86.basis_up.x;
      v48[1] = v86.basis_up.y;
      v48[2] = v86.basis_up.z;
      v49 = (char *)MEMORY[0x4DF904] + 4390356;
      *((_DWORD *)MEMORY[0x4DF904] + 1097589) = LODWORD(v86.basis_forward.x);
      *((_DWORD *)v49 + 1) = LODWORD(v86.basis_forward.y);
      *((_DWORD *)v49 + 2) = LODWORD(v86.basis_forward.z);
    }
    else
    {
      v50 = v19->secondary_samples;
      v51 = *(float *)&v80 * v50[v21].delta_dir_to_next.x;
      v52 = &v50[v21].transform.basis_right.x;
      source_cell = follow_state->source_cell;
      v82 = v51 * v79 + source_cell->anchor_position.x + v52[12];
      v83 = *(float *)&v80 * v52[33] * v79 + source_cell->anchor_position.y + v52[13];
      v84 = *(float *)&v80 * v52[34] + source_cell->anchor_position.z + v52[14];
      if ( v18 == v20 )
      {
        set_matrix_identity(&v86);
      }
      else
      {
        qmemcpy(&v95, v52, sizeof(v95));
        qmemcpy(&v96, &v19->secondary_samples[v18 + 1], sizeof(v96));
        memset(&v95.position, 0, 12);
        memset(&v96.position, 0, 12);
        v77 = *(float *)&v80 / v19->secondary_samples[v21].delta_length;
        linear_interpolate_matrix(&v86, &v95, &v96, v77);
      }
      p_output_position = &follow_state->output_position;
      v38 = out_position;
      p_y = &motion->y;
      v86.basis_right.x = v86.basis_right.x * v79;
      v86.basis_right.y = v86.basis_right.y * v79;
      v86.basis_right.z = v86.basis_right.z * v79;
      v54 = motion->y + follow_state->vertical_offset;
      follow_state->vertical_offset = v54;
      v92 = v86.basis_up.x * v54;
      v93 = v86.basis_up.y * v54;
      v55 = v54 * v86.basis_up.z;
      v56 = out_position->x - v85;
      v87 = v56 * v86.basis_right.x;
      v88 = v86.basis_right.y * v56;
      v90 = v87 + v82;
      v91 = v88 + v83;
      v57 = v56 * v86.basis_right.z + v84;
      v82 = v90 + v92;
      v58 = v91 + v93;
      follow_state->output_position.x = v82;
      v83 = v58;
      follow_state->output_position.y = v83;
      v84 = v57 + v55;
      follow_state->output_position.z = v84;
      v59 = (char *)MEMORY[0x4DF904] + 4390324;
      *((_DWORD *)MEMORY[0x4DF904] + 1097581) = LODWORD(v86.basis_right.x);
      *((_DWORD *)v59 + 1) = LODWORD(v86.basis_right.y);
      *((_DWORD *)v59 + 2) = LODWORD(v86.basis_right.z);
      v60 = (float *)((char *)&loc_42FDC4 + (_DWORD)MEMORY[0x4DF904]);
      *v60 = v86.basis_up.x;
      v60[1] = v86.basis_up.y;
      v60[2] = v86.basis_up.z;
      v61 = (char *)MEMORY[0x4DF904] + 4390356;
      *((_DWORD *)MEMORY[0x4DF904] + 1097589) = LODWORD(v86.basis_forward.x);
      *((_DWORD *)v61 + 1) = LODWORD(v86.basis_forward.y);
      *((_DWORD *)v61 + 2) = LODWORD(v86.basis_forward.z);
    }
    v62 = v86.basis_up.y;
    follow_state->orientation_c = v86.basis_up.x;
    z = v86.basis_up.z;
    follow_state->orientation_d = v62;
    v64 = follow_state->template_record;
    follow_state->orientation_e = z;
    v65 = *(float *)&follow_state->sample_index;
    v66 = LODWORD(v65) == v64->segment_count - 1;
    progress = v65;
    if ( v66 )
    {
      v67 = 168 * LODWORD(v65);
      follow_state->orientation_b = v64->primary_samples[LODWORD(v65)].rotation_scalar_98;
      follow_state->orientation_a = v64->primary_samples[LODWORD(v65)].rotation_scalar_94;
    }
    else
    {
      v68 = 7 * LODWORD(v65);
      primary_samples = v64->primary_samples;
      v67 = 24 * v68;
      v70 = *(float *)((char *)&primary_samples[1].rotation_scalar_98 + v67)
          - *(float *)((char *)&primary_samples->rotation_scalar_98 + v67);
      if ( v70 <= 3.1415927 )
      {
        if ( v70 < -3.1415927 )
          v70 = v70 + 6.2831855;
      }
      else
      {
        v70 = v70 - 6.2831855;
      }
      follow_state->orientation_b = follow_state->progress
                                  / *(float *)((char *)&v64->secondary_samples->delta_length + v67)
                                  * v70
                                  + *(float *)((char *)&primary_samples->rotation_scalar_98 + v67);
      v71 = v64->primary_samples;
      v72 = *(float *)((char *)&v71[1].rotation_scalar_94 + v67) - *(float *)((char *)&v71->rotation_scalar_94 + v67);
      if ( v72 <= 3.1415927 )
      {
        if ( v72 < -3.1415927 )
          v72 = v72 + 6.2831855;
      }
      else
      {
        v72 = v72 - 6.2831855;
      }
      v38 = out_position;
      follow_state->orientation_a = follow_state->progress
                                  / *(float *)((char *)&v64->secondary_samples->delta_length + v67)
                                  * v72
                                  + *(float *)((char *)&v71->rotation_scalar_94 + v67);
    }
    v73 = follow_state->progress / *(float *)((char *)&v64->secondary_samples->delta_length + v67);
    player = follow_state->player;
    follow_state->orientation_b = (v73 + (double)SLODWORD(progress))
                                * v64->installed_heading_delta
                                / (double)(int)v64->segment_count;
    if ( player->jetpack_gauge.state == 1 )
      goto LABEL_62;
    v75 = v38->x - v85;
    if ( v75 < 0.0 )
      v75 = -v75;
    if ( v75 <= (double)(int)v64->width_cells * 0.5 + 0.30000001 || follow_state->vertical_offset > 0.0 )
    {
LABEL_62:
      if ( follow_state->vertical_offset < 0.0 )
      {
        follow_state->vertical_offset = 0.0;
        *p_y = 0.0;
      }
      return 0;
    }
    else
    {
      v38->x = p_output_position->x;
      v38->y = p_output_position->y;
      v38->z = p_output_position->z;
      follow_state->player->heading_roll = follow_state->template_record->installed_heading_delta
                                         + follow_state->player->heading_roll;
      if ( v38->x >= -4.0 )
      {
        if ( v38->x <= 4.0 )
          v38->x = v38->x;
        else
          v38->x = 4.0;
        return follow_state->template_record->side_exit_mode == 0;
      }
      else
      {
        v38->x = -4.0;
        return follow_state->template_record->side_exit_mode == 0;
      }
    }
  }
  else
  {
    while ( 1 )
    {
      v10 = *p_delta_length - follow_state->progress;
      v11 = sample_index + 1;
      follow_state->progress = 0.0;
      follow_state->sample_index = v11;
      v78 = v78 - v10;
      if ( v11 == 2 * template_record->segment_count )
        play_voice_manager((int)unk_751498, 4, 1u, -1);
      v12 = follow_state->template_record;
      if ( v12->special_runtime_flag_9c )
      {
        segment_count = v12->segment_count;
        v14 = follow_state->sample_index;
        if ( v14 == segment_count - 1 )
        {
          v15 = *(_DWORD *)(*(_DWORD *)((char *)&unk_641184
                                      + (_DWORD)MEMORY[0x4DF904]
                                      + 244 * get_track_cell_row_index(follow_state->source_cell->_pad_00))
                          + 56);
          *(_DWORD *)(*(_DWORD *)((char *)&unk_641184
                                + (_DWORD)MEMORY[0x4DF904]
                                + 244 * get_track_cell_row_index(follow_state->source_cell->_pad_00))
                    + 36) = *(_DWORD *)(v15 + 164);
          *(_DWORD *)(*(_DWORD *)((char *)&unk_641184
                                + (_DWORD)MEMORY[0x4DF904]
                                + 244 * get_track_cell_row_index(follow_state->source_cell->_pad_00))
                    + 52) = 1065353216;
        }
        else if ( v14 == (int)(3 * segment_count) / 7 )
        {
          track_cell_row_index = get_track_cell_row_index(follow_state->source_cell->_pad_00);
          *(_DWORD *)(*(_DWORD *)((char *)&unk_641184 + (_DWORD)MEMORY[0x4DF904] + 244 * track_cell_row_index) + 4) |= 0x80u;
          v17 = *(_DWORD *)(*(_DWORD *)((char *)&unk_641184
                                      + (_DWORD)MEMORY[0x4DF904]
                                      + 244 * get_track_cell_row_index(follow_state->source_cell->_pad_00))
                          + 56);
          *(_DWORD *)(*(_DWORD *)((char *)&unk_641184
                                + (_DWORD)MEMORY[0x4DF904]
                                + 244 * get_track_cell_row_index(follow_state->source_cell->_pad_00))
                    + 36) = *(_DWORD *)(v17 + 160);
          *(_DWORD *)(*(_DWORD *)((char *)&unk_641184
                                + (_DWORD)MEMORY[0x4DF904]
                                + 244 * get_track_cell_row_index(follow_state->source_cell->_pad_00))
                    + 52) = 1058642330;
        }
      }
      template_record = follow_state->template_record;
      sample_index = follow_state->sample_index;
      if ( sample_index == template_record->segment_count )
        break;
      p_delta_length = &template_record->secondary_samples[sample_index].delta_length;
      if ( v78 + follow_state->progress <= *p_delta_length )
        goto LABEL_11;
    }
    follow_state->active = 0;
    if ( v78 >= 1.0 )
      v78 = 0.99900001;
    v23 = path_factor
        * follow_state->template_record->secondary_samples[follow_state->template_record->segment_count - 1].delta_length;
    motion->z = v23;
    if ( v23 > 1.0 )
      motion->z = 1.0;
    v24 = follow_state->template_record;
    if ( v24->kind == PATH_TEMPLATE_KIND_SUPERTRAMP )
    {
      motion->y = motion->z * 0.69999999;
      v25 = follow_state->template_record;
      v26 = out_position->x;
      v27 = v25->segment_count;
      v28 = v78 + v25->width_or_scale;
      v29 = v25->secondary_samples;
      v30 = v28 * v29[v27 - 1].transform.basis_forward.x;
      v31 = &v29[v27];
      p_anchor_position = &follow_state->source_cell->anchor_position;
      v90 = v30;
      v91 = v28 * v31[-1].transform.basis_forward.y;
      v33 = v28 * v31[-1].transform.basis_forward.z;
      v34 = p_anchor_position->x + v31[-1].transform.position.x;
      v88 = v31[-1].transform.position.y + p_anchor_position->y;
      v89 = v31[-1].transform.position.z + p_anchor_position->z;
      v82 = v34 + v90;
      v35 = v88 + v91;
      out_position->x = v82;
      v83 = v35;
      v36 = v89 + v33;
      out_position->y = v83;
      v84 = v36;
      out_position->z = v84;
      out_position->x = v26;
      follow_state->player->cutscene_pitch_cycle_step = *((float *)MEMORY[0x4DF904] + 119188) * 0.013888888;
      follow_state->player->cutscene_pitch_cycle = follow_state->player->cutscene_pitch_cycle_step;
      play_voice_manager((int)unk_751498, 15, 0, -1);
    }
    else
    {
      out_position->z = v24->secondary_samples[v24->segment_count - 1].transform.position.z
                      + follow_state->source_cell->anchor_position.z
                      + v24->width_or_scale
                      + v78;
    }
    follow_state->player->heading_roll = follow_state->template_record->installed_heading_delta
                                       + follow_state->player->heading_roll;
    return 3;
  }
}

