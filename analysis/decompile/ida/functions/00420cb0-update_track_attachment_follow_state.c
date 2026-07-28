/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_track_attachment_follow_state @ 0x420cb0 */
/* selector: update_track_attachment_follow_state */

// Advances one live attachment-follow session along its borrowed Path and SubLoc, updates progress and local height, publishes the interpolated basis into the live Player matrix, stores the up basis in owned `cRPathFollowGoldy::orientation_up`, writes the output position, and returns the mode consumed by `update_subgoldy`. `FollowState` remains only a compatibility alias. Windows `cdb` confirmed `ARCADE007` mid-follow samples at local height `-0.49f` and the direct fall-state handoff. The static `voice 4` lane is unreachable: traversal terminates at `sample_index == segment_count` before the later doubled-count guard can hold. Android and iOS preserve that guard, the aggregate orientation copy, and the exact authored `cRPathFollowGoldy::Traverse(float, tVector&, tVector*)` symbol; Windows independently supplies the 0x40-byte layout and offsets.
int32_t __thiscall update_track_attachment_follow_state(
        cRPathFollowGoldy *follow_state,
        float path_factor,
        Vec3 *out_position,
        Vec3 *motion)
{
  uint32_t sample_index; // ecx
  Path *template_record; // esi
  PathTemplateSample *secondary_samples; // edx
  double v8; // st7
  float *p_delta_length; // edx
  double v10; // st7
  uint32_t v11; // ecx
  Path *v12; // eax
  uint32_t segment_count; // eax
  uint32_t v14; // esi
  struct Path *attachment_template_record; // esi
  int32_t track_cell_row_index; // eax
  struct Path *v17; // esi
  uint32_t v18; // ebx
  Path *v19; // edx
  int v20; // edi
  int v21; // eax
  float *p_x; // ecx
  double v23; // st7
  Path *v24; // edx
  Path *v25; // ecx
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
  TransformMatrix *p_transform; // edx
  PathTemplateSample *v48; // ecx
  double v49; // st7
  TransformMatrix *v50; // esi
  TrackRowCell *source_cell; // ecx
  double v52; // st7
  double v53; // st7
  double v54; // st6
  double v55; // st6
  double v56; // st5
  float v57; // edx
  float z; // ecx
  Path *v59; // edx
  float v60; // eax
  bool v61; // zf
  int v62; // ecx
  int v63; // ecx
  PathTemplateSample *primary_samples; // eax
  double v65; // st7
  PathTemplateSample *v66; // eax
  double v67; // st7
  double v68; // st7
  Player *player; // ecx
  double v70; // st7
  float arg2; // [esp+0h] [ebp-1A0h]
  float alpha; // [esp+Ch] [ebp-194h]
  float v73; // [esp+20h] [ebp-180h]
  float v74; // [esp+20h] [ebp-180h]
  float out_angle; // [esp+24h] [ebp-17Ch] BYREF
  float arg1; // [esp+28h] [ebp-178h]
  float v77; // [esp+2Ch] [ebp-174h]
  float v78; // [esp+30h] [ebp-170h]
  float v79; // [esp+34h] [ebp-16Ch]
  float v80; // [esp+38h] [ebp-168h]
  TransformMatrix transform; // [esp+3Ch] [ebp-164h] BYREF
  float v82; // [esp+7Ch] [ebp-124h]
  float v83; // [esp+80h] [ebp-120h]
  float v84; // [esp+84h] [ebp-11Ch]
  float v85; // [esp+88h] [ebp-118h]
  float v86; // [esp+8Ch] [ebp-114h]
  float v87; // [esp+94h] [ebp-10Ch]
  float v88; // [esp+98h] [ebp-108h]
  TransformMatrix from; // [esp+A0h] [ebp-100h] BYREF
  TransformMatrix v90; // [esp+E0h] [ebp-C0h] BYREF
  TransformMatrix v91; // [esp+120h] [ebp-80h] BYREF
  TransformMatrix to; // [esp+160h] [ebp-40h] BYREF

  sample_index = follow_state->sample_index;
  template_record = follow_state->template_record;
  secondary_samples = template_record->secondary_samples;
  v8 = path_factor * secondary_samples[sample_index].delta_length;
  p_delta_length = &secondary_samples[sample_index].delta_length;
  v73 = v8;
  if ( v8 + follow_state->progress <= *p_delta_length )
  {
LABEL_11:
    v18 = follow_state->sample_index;
    out_angle = v73 + follow_state->progress;
    follow_state->progress = out_angle;
    v19 = follow_state->template_record;
    v20 = v19->segment_count - 1;
    v21 = v18;
    p_x = &v19->primary_samples[v18].transform.basis_right.x;
    if ( v18 == v20 )
      v80 = p_x[36];
    else
      v80 = out_angle / v19->secondary_samples[v18].delta_length * (p_x[78] - p_x[36]) + p_x[36];
    if ( v18 == v20 )
      v74 = p_x[39];
    else
      v74 = out_angle / v19->secondary_samples[v21].delta_length * (p_x[81] - p_x[39]) + p_x[39];
    if ( v18 == v20 )
      arg1 = p_x[40];
    else
      arg1 = out_angle / v19->secondary_samples[v21].delta_length * (p_x[82] - p_x[40]) + p_x[40];
    if ( v19->kind == PATH_TEMPLATE_KIND_NONLINEAR_42 )
    {
      v38 = out_position;
      arg2 = out_position->x - v80;
      compute_kind42_attachment_transform(v19, arg1, arg2, 0.49000001, &transform, &out_angle);
      v39 = follow_state->sample_index;
      if ( v39 == 0 || v39 == follow_state->template_record->segment_count - 1 )
      {
        set_matrix_identity(&from);
        from.position.x = transform.position.x;
        v40 = follow_state->sample_index;
        from.position.y = transform.position.y;
        from.position.z = transform.position.z;
        to = transform;
        if ( v40 != 0 )
          arg1 = 1.0 - follow_state->progress;
        else
          arg1 = follow_state->progress;
        linear_interpolate_matrix(&transform, &from, &to, arg1);
      }
      p_output_position = &follow_state->output_position;
      p_y = &motion->y;
      y = transform.position.y;
      v44 = follow_state->template_record->secondary_samples[follow_state->sample_index].delta_dir_to_next.z
          * follow_state->progress
          + follow_state->source_cell->anchor_position.z
          + follow_state->template_record->secondary_samples[follow_state->sample_index].transform.position.z;
      transform.basis_right.x = transform.basis_right.x * v74;
      transform.basis_right.y = transform.basis_right.y * v74;
      transform.basis_right.z = transform.basis_right.z * v74;
      v45 = motion->y + follow_state->vertical_offset;
      follow_state->output_position.x = transform.position.x;
      x = transform.basis_right.x;
      follow_state->output_position.y = y;
      follow_state->vertical_offset = v45;
      follow_state->output_position.z = v44;
      p_transform = &g_game_base->subgame.player.body.transform;
      g_game_base->subgame.player.body.transform.basis_right.x = x;
      p_transform->basis_right.y = transform.basis_right.y;
      p_transform->basis_right.z = transform.basis_right.z;
      g_game_base->subgame.player.body.transform.basis_up = transform.basis_up;
      g_game_base->subgame.player.body.transform.basis_forward = transform.basis_forward;
    }
    else
    {
      v48 = v19->secondary_samples;
      v49 = out_angle * v48[v21].delta_dir_to_next.x;
      v50 = &v48[v21].transform;
      source_cell = follow_state->source_cell;
      v77 = v49 * v74 + source_cell->anchor_position.x + v50->position.x;
      v78 = out_angle * v50[2].basis_right.y * v74 + source_cell->anchor_position.y + v50->position.y;
      v79 = out_angle * v50[2].basis_right.z + source_cell->anchor_position.z + v50->position.z;
      if ( v18 == v20 )
      {
        set_matrix_identity(&transform);
      }
      else
      {
        v90 = *v50;
        v91 = v19->secondary_samples[v18 + 1].transform;
        memset(&v90.position, 0, sizeof(v90.position));
        memset(&v91.position, 0, sizeof(v91.position));
        alpha = out_angle / v19->secondary_samples[v21].delta_length;
        linear_interpolate_matrix(&transform, &v90, &v91, alpha);
      }
      p_output_position = &follow_state->output_position;
      v38 = out_position;
      p_y = &motion->y;
      transform.basis_right.x = transform.basis_right.x * v74;
      transform.basis_right.y = transform.basis_right.y * v74;
      transform.basis_right.z = transform.basis_right.z * v74;
      v52 = motion->y + follow_state->vertical_offset;
      follow_state->vertical_offset = v52;
      v87 = transform.basis_up.x * v52;
      v88 = transform.basis_up.y * v52;
      v53 = v52 * transform.basis_up.z;
      v54 = out_position->x - v80;
      v82 = v54 * transform.basis_right.x;
      v83 = transform.basis_right.y * v54;
      v85 = v82 + v77;
      v86 = v83 + v78;
      v55 = v54 * transform.basis_right.z + v79;
      v77 = v85 + v87;
      v56 = v86 + v88;
      follow_state->output_position.x = v77;
      v78 = v56;
      follow_state->output_position.y = v78;
      v79 = v55 + v53;
      follow_state->output_position.z = v79;
      g_game_base->subgame.player.body.transform.basis_right = transform.basis_right;
      g_game_base->subgame.player.body.transform.basis_up = transform.basis_up;
      g_game_base->subgame.player.body.transform.basis_forward = transform.basis_forward;
    }
    v57 = transform.basis_up.y;
    follow_state->orientation_up.x = transform.basis_up.x;
    z = transform.basis_up.z;
    follow_state->orientation_up.y = v57;
    v59 = follow_state->template_record;
    follow_state->orientation_up.z = z;
    v60 = *(float *)&follow_state->sample_index;
    v61 = LODWORD(v60) == v59->segment_count - 1;
    arg1 = v60;
    if ( v61 )
    {
      v62 = 168 * LODWORD(v60);
      follow_state->orientation_b = v59->primary_samples[LODWORD(v60)].rotation_scalar_98;
      follow_state->orientation_a = v59->primary_samples[LODWORD(v60)].rotation_scalar_94;
    }
    else
    {
      v63 = 7 * LODWORD(v60);
      primary_samples = v59->primary_samples;
      v62 = 24 * v63;
      v65 = *(float *)((char *)&primary_samples[1].rotation_scalar_98 + v62)
          - *(float *)((char *)&primary_samples->rotation_scalar_98 + v62);
      if ( v65 <= 3.1415927 )
      {
        if ( v65 < -3.1415927 )
          v65 = v65 + 6.2831855;
      }
      else
      {
        v65 = v65 - 6.2831855;
      }
      follow_state->orientation_b = follow_state->progress
                                  / *(float *)((char *)&v59->secondary_samples->delta_length + v62)
                                  * v65
                                  + *(float *)((char *)&primary_samples->rotation_scalar_98 + v62);
      v66 = v59->primary_samples;
      v67 = *(float *)((char *)&v66[1].rotation_scalar_94 + v62) - *(float *)((char *)&v66->rotation_scalar_94 + v62);
      if ( v67 <= 3.1415927 )
      {
        if ( v67 < -3.1415927 )
          v67 = v67 + 6.2831855;
      }
      else
      {
        v67 = v67 - 6.2831855;
      }
      v38 = out_position;
      follow_state->orientation_a = follow_state->progress
                                  / *(float *)((char *)&v59->secondary_samples->delta_length + v62)
                                  * v67
                                  + *(float *)((char *)&v66->rotation_scalar_94 + v62);
    }
    v68 = follow_state->progress / *(float *)((char *)&v59->secondary_samples->delta_length + v62);
    player = follow_state->player;
    follow_state->orientation_b = (v68 + (double)SLODWORD(arg1))
                                * v59->installed_heading_delta
                                / (double)(int)v59->segment_count;
    if ( player->sub_hover.state == SUB_HOVER_STATE_ACTIVE )
      goto LABEL_62;
    v70 = v38->x - v80;
    if ( v70 < 0.0 )
      v70 = -v70;
    if ( v70 <= (double)(int)v59->width_cells * 0.5 + 0.30000001 || follow_state->vertical_offset > 0.0 )
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
      v73 = v73 - v10;
      if ( v11 == 2 * template_record->segment_count )
        play_voice_manager(&g_voice_manager, 4, 1u, -1);
      v12 = follow_state->template_record;
      if ( v12->has_entry_mesh_transition != 0 )
      {
        segment_count = v12->segment_count;
        v14 = follow_state->sample_index;
        if ( v14 == segment_count - 1 )
        {
          attachment_template_record = g_game_base->subgame.runtime_rows[get_track_cell_row_index(follow_state->source_cell)].primary_attachment_cell->attachment_template_record;
          g_game_base->subgame.runtime_rows[get_track_cell_row_index(follow_state->source_cell)].primary_attachment_cell->object = attachment_template_record->entry_base_strip_mesh;
          g_game_base->subgame.runtime_rows[get_track_cell_row_index(follow_state->source_cell)].primary_attachment_cell->color.a = 1.0;
        }
        else if ( v14 == (int)(3 * segment_count) / 7 )
        {
          track_cell_row_index = get_track_cell_row_index(follow_state->source_cell);
          g_game_base->subgame.runtime_rows[track_cell_row_index].primary_attachment_cell->bod.list_flags |= 0x80u;
          v17 = g_game_base->subgame.runtime_rows[get_track_cell_row_index(follow_state->source_cell)].primary_attachment_cell->attachment_template_record;
          g_game_base->subgame.runtime_rows[get_track_cell_row_index(follow_state->source_cell)].primary_attachment_cell->object = v17->entry_transition_strip_mesh;
          g_game_base->subgame.runtime_rows[get_track_cell_row_index(follow_state->source_cell)].primary_attachment_cell->color.a = 0.60000002;
        }
      }
      template_record = follow_state->template_record;
      sample_index = follow_state->sample_index;
      if ( sample_index == template_record->segment_count )
        break;
      p_delta_length = &template_record->secondary_samples[sample_index].delta_length;
      if ( v73 + follow_state->progress <= *p_delta_length )
        goto LABEL_11;
    }
    follow_state->active = 0;
    if ( v73 >= 1.0 )
      v73 = 0.99900001;
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
      v28 = v73 + v25->width_or_scale;
      v29 = v25->secondary_samples;
      v30 = v28 * v29[v27 - 1].transform.basis_forward.x;
      v31 = &v29[v27];
      p_anchor_position = &follow_state->source_cell->anchor_position;
      v85 = v30;
      v86 = v28 * v31[-1].transform.basis_forward.y;
      v33 = v28 * v31[-1].transform.basis_forward.z;
      v34 = p_anchor_position->x + v31[-1].transform.position.x;
      v83 = v31[-1].transform.position.y + p_anchor_position->y;
      v84 = v31[-1].transform.position.z + p_anchor_position->z;
      v77 = v34 + v85;
      v35 = v83 + v86;
      out_position->x = v77;
      v78 = v35;
      v36 = v84 + v33;
      out_position->y = v78;
      v79 = v36;
      out_position->z = v79;
      out_position->x = v26;
      follow_state->player->cutscene_pitch_cycle_step = g_game_base->subgame.subgame_rate * 0.013888888;
      follow_state->player->cutscene_pitch_cycle = follow_state->player->cutscene_pitch_cycle_step;
      play_voice_manager(&g_voice_manager, 15, 0, -1);
    }
    else
    {
      out_position->z = v24->secondary_samples[v24->segment_count - 1].transform.position.z
                      + follow_state->source_cell->anchor_position.z
                      + v24->width_or_scale
                      + v73;
    }
    follow_state->player->heading_roll = follow_state->template_record->installed_heading_delta
                                       + follow_state->player->heading_roll;
    return 3;
  }
}
