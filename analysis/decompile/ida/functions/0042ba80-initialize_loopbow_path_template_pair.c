/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_loopbow_path_template_pair @ 0x42ba80 */
/* selector: initialize_loopbow_path_template_pair */

// Builds the LoopBow attachment path-template pair; iOS Path.o names this `cRPath::BuildLoopBow(float, int, bool, char*, char*)`.
void __thiscall initialize_loopbow_path_template_pair(
        Path *self,
        float curve_scale,
        uint32_t width_cells_arg,
        bool mode,
        char *texture_a,
        char *texture_b,
        char *vertical_texture)
{
  int v8; // esi
  double v9; // st7
  int v10; // edi
  int v11; // ebx
  int v12; // edi
  int v13; // ecx
  int v14; // ebx
  double v15; // st7
  float *p_center_x; // edi
  PathTemplateSample *v17; // eax
  PathTemplateSample *v18; // edx
  float v19; // esi
  PathTemplateSample *primary_samples; // edx
  double v21; // st7
  double v22; // st6
  Vec3 *p_position; // eax
  signed int v24; // ebx
  int v25; // edi
  PathTemplateSample *v26; // edx
  float *p_x; // eax
  double v28; // st7
  PathTemplateSample *secondary_samples; // ecx
  float *v30; // eax
  double v31; // st7
  Vec3 *p_delta_dir_to_next; // edx
  Vec3 *v33; // ecx
  Object *object; // eax
  signed int v35; // edx
  int v36; // ebx
  signed int width_cells; // ecx
  signed int v38; // edi
  double v39; // st7
  float *v40; // eax
  float *v41; // ecx
  float *v42; // ecx
  double v43; // st6
  int v44; // edi
  int v45; // ecx
  ObjectFaceQuad *v46; // ebx
  float angle; // [esp+0h] [ebp-B0h]
  float anglea; // [esp+0h] [ebp-B0h]
  int v49; // [esp+14h] [ebp-9Ch]
  int v50; // [esp+14h] [ebp-9Ch]
  int v51; // [esp+14h] [ebp-9Ch]
  int v52; // [esp+14h] [ebp-9Ch]
  int v53; // [esp+14h] [ebp-9Ch]
  float v54; // [esp+14h] [ebp-9Ch]
  float v55; // [esp+18h] [ebp-98h]
  float v56; // [esp+18h] [ebp-98h]
  Vec3 *vertices; // [esp+18h] [ebp-98h]
  signed int v58; // [esp+18h] [ebp-98h]
  float v59; // [esp+1Ch] [ebp-94h]
  int i; // [esp+1Ch] [ebp-94h]
  int v61; // [esp+1Ch] [ebp-94h]
  float v62; // [esp+20h] [ebp-90h]
  float v63; // [esp+20h] [ebp-90h]
  float v64; // [esp+20h] [ebp-90h]
  float v65; // [esp+24h] [ebp-8Ch]
  float v66; // [esp+24h] [ebp-8Ch]
  float v67; // [esp+28h] [ebp-88h]
  float v68; // [esp+28h] [ebp-88h]
  float v69; // [esp+2Ch] [ebp-84h]
  float v70; // [esp+2Ch] [ebp-84h]
  float v71; // [esp+30h] [ebp-80h]
  float v72; // [esp+30h] [ebp-80h]
  int v73; // [esp+34h] [ebp-7Ch]
  float v74; // [esp+34h] [ebp-7Ch]
  float v75; // [esp+38h] [ebp-78h]
  int v76; // [esp+38h] [ebp-78h]
  ObjectFaceQuad *facequads; // [esp+38h] [ebp-78h]
  int v78; // [esp+3Ch] [ebp-74h]
  float v79; // [esp+3Ch] [ebp-74h]
  int v80; // [esp+3Ch] [ebp-74h]
  float v81; // [esp+40h] [ebp-70h]
  float v82; // [esp+40h] [ebp-70h]
  float v83; // [esp+44h] [ebp-6Ch]
  float v84; // [esp+44h] [ebp-6Ch]
  float v85; // [esp+48h] [ebp-68h]
  float v86; // [esp+48h] [ebp-68h]
  float v87; // [esp+4Ch] [ebp-64h]
  float v88; // [esp+50h] [ebp-60h]
  float v89; // [esp+50h] [ebp-60h]
  float v90; // [esp+54h] [ebp-5Ch]
  float v91; // [esp+60h] [ebp-50h]
  float v92; // [esp+64h] [ebp-4Ch]
  float v93; // [esp+68h] [ebp-48h]
  TransformMatrix transform; // [esp+70h] [ebp-40h] BYREF
  float arg2; // [esp+B4h] [ebp+4h]

  v8 = 0;
  self->kind = PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY;
  v71 = 0.0;
  if ( width_cells_arg == 4 )
  {
    self->kind = PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY;
    v71 = 0.5;
  }
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = width_cells_arg;
  v73 = (__int64)(curve_scale * 6.2831855);
  v78 = v73 + 14;
  self->width_or_scale = 1.0;
  self->segment_count = v73 + 14;
  self->segment_count_f = (float)(v73 + 14);
  v9 = (double)v73;
  v59 = v9;
  arg2 = v9 * 0.15915494;
  get_path_nodes(self);
  self->has_entry_mesh_transition = 1;
  v49 = 0;
  v10 = 0;
  do
  {
    v62 = (float)v49;
    self->primary_samples[v10].center_x = (double)(int)self->width_cells * 0.5 - 4.0 - v62 * 0.14285715 * v71;
    self->primary_samples[v10].rotation_scalar_98 = 0.0;
    self->primary_samples[v10].rotation_scalar_94 = 0.0;
    self->primary_samples[v10].special_scalar = 0.0;
    self->primary_samples[v10].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v10].transform);
    self->primary_samples[v10].transform.position.x = self->primary_samples[v10].center_x;
    self->primary_samples[v10].transform.position.y = 0.0;
    self->primary_samples[v10].transform.position.z = v62;
    self->primary_samples[v10].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[v10].transform);
    self->secondary_samples[v10].transform.position.x = self->primary_samples[v10].center_x;
    self->secondary_samples[v10].transform.position.y = 0.49000001;
    self->secondary_samples[v10++].transform.position.z = v62;
    self->secondary_samples[v10 - 1].delta_length = 1.0;
    ++v49;
  }
  while ( v10 < 7 );
  v11 = 0;
  v50 = 0;
  v12 = v73 + 7;
  do
  {
    self->primary_samples[v12].center_x = (1.0 - (double)v50 * 0.16666667) * v71
                                        + 4.0
                                        - (double)(int)self->width_cells * 0.5;
    self->primary_samples[v12].rotation_scalar_98 = 0.0;
    self->primary_samples[v12].rotation_scalar_94 = 0.0;
    self->primary_samples[v12].special_scalar = 0.0;
    self->primary_samples[v12].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v12].transform);
    self->primary_samples[v12].transform.position.x = self->primary_samples[v12].center_x;
    self->primary_samples[v12].transform.position.y = 0.0;
    v75 = (float)(v11 + 7);
    self->primary_samples[v12].transform.position.z = v75;
    self->primary_samples[v12].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[v12].transform);
    ++v11;
    self->secondary_samples[v12].transform.position.x = self->primary_samples[v12].center_x;
    v50 = v11;
    self->secondary_samples[v12].transform.position.y = 0.49000001;
    self->secondary_samples[v12++].transform.position.z = v75;
    self->secondary_samples[v12 - 1].delta_length = 1.0;
  }
  while ( v11 < 7 );
  v51 = 0;
  if ( v73 > 0 )
  {
    v63 = arg2 - 0.49000001;
    v13 = 168 * v78;
    v76 = 168 * v78;
    v14 = 7;
    while ( 1 )
    {
      v15 = (double)v51;
      v79 = v15 * 6.2831855 / v59;
      self->primary_samples[v14].center_x = (*(float *)((char *)self->primary_samples + v13 - 24)
                                           - self->primary_samples->center_x)
                                          * v15
                                          / v59
                                          + self->primary_samples->center_x;
      p_center_x = &self->primary_samples[v14].center_x;
      v55 = v79 * 0.5;
      angle = v55 + 4.712389;
      *p_center_x = sine(angle) * v71 + *p_center_x;
      self->primary_samples[v14].rotation_scalar_98 = 0.0;
      self->primary_samples[v14].rotation_scalar_94 = 0.0;
      self->primary_samples[v14].special_scalar = 0.0;
      self->primary_samples[v14].lateral_scale = 1.0;
      set_matrix_identity(&self->primary_samples[v14].transform);
      self->primary_samples[v14].transform.position.x = self->primary_samples[v14].center_x;
      self->primary_samples[v14].transform.position.z = sine(v79) * arg2 + 7.0;
      self->primary_samples[v14].transform.position.y = arg2 - cosine(v79) * arg2;
      set_matrix_identity(&self->secondary_samples[v14].transform);
      self->secondary_samples[v14].transform.position.x = self->primary_samples[v14].center_x;
      self->secondary_samples[v14].transform.position.z = sine(v79) * v63 + 7.0;
      self->secondary_samples[v14].transform.position.y = arg2 - cosine(v79) * v63;
      v17 = &self->primary_samples[v14];
      v17->transform.basis_right.x = 1.0;
      v17->transform.basis_right.y = 0.0;
      v17->transform.basis_right.z = 0.0;
      self->primary_samples[v14].transform.basis_up.x = 0.0;
      self->primary_samples[v14].transform.basis_up.y = arg2 - self->primary_samples[v14].transform.position.y;
      self->primary_samples[v14].transform.basis_up.z = 7.0 - self->primary_samples[v14].transform.position.z;
      normalize_vector(&self->primary_samples[v14].transform.basis_up);
      cross_vectors(
        &self->primary_samples[v14].transform.basis_forward,
        &self->primary_samples[v14].transform.basis_right,
        &self->primary_samples[v14].transform.basis_up);
      v18 = &self->secondary_samples[v14];
      v18->transform.basis_right.x = 1.0;
      v18->transform.basis_right.y = 0.0;
      v18->transform.basis_right.z = 0.0;
      self->secondary_samples[v14].transform.basis_up.x = 0.0;
      self->secondary_samples[v14].transform.basis_up.y = arg2 - self->secondary_samples[v14].transform.position.y;
      self->secondary_samples[v14].transform.basis_up.z = 7.0 - self->secondary_samples[v14].transform.position.z;
      normalize_vector(&self->secondary_samples[v14].transform.basis_up);
      cross_vectors(
        &self->secondary_samples[v14].transform.basis_forward,
        &self->secondary_samples[v14].transform.basis_right,
        &self->secondary_samples[v14].transform.basis_up);
      set_matrix_identity(&transform);
      v19 = v55;
      v56 = sine(v55);
      anglea = sine(v19) * v56 * 0.52359879;
      rotate_matrix_local_y(&transform, anglea);
      self->primary_samples[v14].transform.position.z = self->primary_samples[v14].transform.position.z - 7.0;
      self->secondary_samples[v14].transform.position.z = self->secondary_samples[v14].transform.position.z - 7.0;
      multiply_matrix(&self->primary_samples[v14].transform, &transform);
      multiply_matrix(&self->secondary_samples[v14].transform, &transform);
      self->primary_samples[v14].transform.position.z = self->primary_samples[v14].transform.position.z + 7.0;
      self->secondary_samples[v14].transform.position.z = self->secondary_samples[v14].transform.position.z + 7.0;
      qmemcpy(&self->secondary_samples[v14], &self->primary_samples[v14], 0x40u);
      primary_samples = self->primary_samples;
      v21 = primary_samples[v14].transform.basis_up.x * 0.49000001;
      v88 = primary_samples[v14].transform.basis_up.y * 0.49000001;
      v22 = primary_samples[v14].transform.basis_up.z * 0.49000001;
      p_position = &self->secondary_samples[v14++].transform.position;
      v90 = v22;
      p_position->x = v21 + p_position->x;
      p_position->y = v88 + p_position->y;
      p_position->z = v90 + p_position->z;
      if ( ++v51 >= v73 )
        break;
      v13 = v76;
    }
    v8 = 0;
  }
  v24 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v25 = 0;
    do
    {
      v26 = self->primary_samples;
      p_x = &v26[v25].delta_dir_to_next.x;
      v65 = v26[v25 + 1].transform.position.x - v26[v25].transform.position.x;
      v67 = v26[v25 + 1].transform.position.y - v26[v25].transform.position.y;
      v28 = v26[v25 + 1].transform.position.z - v26[v25].transform.position.z;
      *p_x = v65;
      p_x[1] = v67;
      v69 = v28;
      p_x[2] = v69;
      self->primary_samples[v25].delta_length = normalize_vector(&self->primary_samples[v25].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      v30 = &secondary_samples[v25].delta_dir_to_next.x;
      v81 = secondary_samples[v25 + 1].transform.position.x - secondary_samples[v25].transform.position.x;
      v83 = secondary_samples[v25 + 1].transform.position.y - secondary_samples[v25].transform.position.y;
      v31 = secondary_samples[v25 + 1].transform.position.z - secondary_samples[v25].transform.position.z;
      *v30 = v81;
      v30[1] = v83;
      v85 = v31;
      v30[2] = v85;
      ++v24;
      self->secondary_samples[v25].delta_length = normalize_vector(&self->secondary_samples[v25].delta_dir_to_next);
      ++v25;
    }
    while ( v24 < (signed int)(self->segment_count - 1) );
  }
  p_delta_dir_to_next = &self->primary_samples[self->segment_count - 1].delta_dir_to_next;
  p_delta_dir_to_next->x = 0.0;
  p_delta_dir_to_next->y = 0.0;
  p_delta_dir_to_next->z = 1.0;
  self->primary_samples[self->segment_count - 1].delta_length = 1.0;
  v33 = &self->secondary_samples[self->segment_count - 1].delta_dir_to_next;
  v33->x = 0.0;
  v33->y = 0.0;
  v33->z = 1.0;
  self->secondary_samples[self->segment_count - 1].delta_length = 1.0;
  request_object_vertices(self->bod.object, (self->segment_count + 1) * (self->width_cells + 1));
  request_object_facequads(self->bod.object, 2 * self->segment_count * self->width_cells);
  object = self->bod.object;
  facequads = object->facequads;
  v35 = 0;
  vertices = object->vertices;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    v36 = 0;
    v80 = 0;
    do
    {
      width_cells = self->width_cells;
      v38 = 0;
      v52 = 0;
      for ( i = width_cells; v38 <= width_cells; i = width_cells )
      {
        v39 = (double)v52 - (double)i * 0.5;
        v40 = (float *)((char *)&self->primary_samples->transform.basis_right.x + v36);
        if ( v35 == self->segment_count )
        {
          v36 = v80;
          v92 = v39 * *(v40 - 42);
          v93 = v39 * *(v40 - 41);
          v91 = *(v40 - 28) + 1.0;
          v82 = *(v40 - 30) + v92;
          v84 = *(v40 - 29) + v93;
          v42 = &vertices[v38 + v35 * (width_cells + 1)].x;
          v43 = v91 + v39 * *(v40 - 40);
          *v42 = v82;
          v42[1] = v84;
          v86 = v43;
          v42[2] = v86;
        }
        else
        {
          v87 = v39 * *v40;
          v89 = v39 * v40[1];
          v66 = v87 + v40[12];
          v68 = v89 + v40[13];
          v70 = v39 * v40[2] + v40[14];
          v41 = &vertices[v38 + v35 * (width_cells + 1)].x;
          *v41 = v66;
          v41[1] = v68;
          v41[2] = v70;
        }
        width_cells = self->width_cells;
        v52 = ++v38;
      }
      ++v35;
      v36 += 168;
      v80 = v36;
    }
    while ( v35 <= (signed int)self->segment_count );
  }
  v44 = 0;
  if ( (int)self->segment_count > 0 )
  {
    while ( 1 )
    {
      v53 = 0;
      if ( (int)self->width_cells > 0 )
      {
        v74 = (double)(v44 % 8) * 0.125;
        v64 = (double)(v44 % 8 + 1) * 0.125;
        do
        {
          v45 = 0;
          v58 = v8 + 1;
          v61 = 0;
          v72 = (double)v53 * 0.125;
          v54 = (double)(v8 + 1) * 0.125;
          while ( 1 )
          {
            v46 = &facequads[2 * v8 + 2 * v44 * self->width_cells + v45];
            v46->header_word = 0;
            if ( v45 != 0 )
            {
              v46->vertex_0 = v44 * (LOWORD(self->width_cells) + 1) + v8 + 1;
              v46->vertex_1 = v8 + v44 * (LOWORD(self->width_cells) + 1);
              v46->vertex_2 = v8 + (v44 + 1) * (LOWORD(self->width_cells) + 1);
              v46->vertex_3 = (v44 + 1) * (LOWORD(self->width_cells) + 1) + v8 + 1;
              v46->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_b, nullptr, 0);
              v46->uv[0].u = v54;
              v46->uv[0].v = v74;
              v46->uv[1].u = v72;
              v46->uv[1].v = v74;
              v46->uv[2].u = v72;
              v46->uv[2].v = v64;
              v46->uv[3].u = v54;
            }
            else
            {
              v46->vertex_0 = v8 + v44 * (LOWORD(self->width_cells) + 1);
              v46->vertex_1 = v44 * (LOWORD(self->width_cells) + 1) + v8 + 1;
              v46->vertex_2 = (v44 + 1) * (LOWORD(self->width_cells) + 1) + v8 + 1;
              v46->vertex_3 = v8 + (v44 + 1) * (LOWORD(self->width_cells) + 1);
              v46->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_a, nullptr, 0);
              v46->uv[0].u = v72;
              v46->uv[0].v = v74;
              v46->uv[1].u = v54;
              v46->uv[1].v = v74;
              v46->uv[2].u = v54;
              v46->uv[2].v = v64;
              v46->uv[3].u = v72;
            }
            v46->uv[3].v = v64;
            if ( ++v61 >= 2 )
              break;
            v45 = v61;
          }
          ++v8;
          v53 = v58;
        }
        while ( v58 < (signed int)self->width_cells );
      }
      if ( ++v44 >= (signed int)self->segment_count )
        break;
      v8 = 0;
    }
  }
  calc_path_length_z(self);
}
