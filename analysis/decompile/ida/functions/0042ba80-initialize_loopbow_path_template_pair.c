/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_loopbow_path_template_pair @ 0x42ba80 */
/* selector: initialize_loopbow_path_template_pair */

int32_t __thiscall initialize_loopbow_path_template_pair(
        PathTemplate *self,
        float arg2,
        uint32_t arg3,
        char *texture_a,
        char *texture_b)
{
  int v6; // esi
  double v7; // st7
  int v8; // edi
  int v9; // ebx
  int v10; // edi
  int v11; // ecx
  int v12; // ebx
  double v13; // st7
  float *p_center_x; // edi
  PathTemplateSample *v15; // eax
  PathTemplateSample *v16; // edx
  float v17; // esi
  PathTemplateSample *primary_samples; // edx
  double v19; // st7
  double v20; // st6
  Vec4 *p_position; // eax
  signed int v22; // ebx
  int v23; // edi
  PathTemplateSample *v24; // edx
  float *p_x; // eax
  double v26; // st7
  PathTemplateSample *secondary_samples; // ecx
  float *v28; // eax
  double v29; // st7
  Vec3 *p_delta_dir_to_next; // edx
  Vec3 *v31; // ecx
  PathTemplateStripMesh *strip_mesh; // eax
  signed int v33; // edx
  int v34; // ebx
  signed int width_cells; // ecx
  signed int v36; // edi
  double v37; // st7
  float *v38; // eax
  float *v39; // ecx
  float *v40; // ecx
  double v41; // st6
  int v42; // edi
  int v43; // ecx
  ObjectFaceQuad *v44; // ebx
  float v46; // [esp+0h] [ebp-B0h]
  float v47; // [esp+0h] [ebp-B0h]
  int v48; // [esp+14h] [ebp-9Ch]
  int v49; // [esp+14h] [ebp-9Ch]
  int v50; // [esp+14h] [ebp-9Ch]
  int v51; // [esp+14h] [ebp-9Ch]
  int v52; // [esp+14h] [ebp-9Ch]
  float v53; // [esp+14h] [ebp-9Ch]
  float v54; // [esp+18h] [ebp-98h]
  float v55; // [esp+18h] [ebp-98h]
  Vec3 *vertices; // [esp+18h] [ebp-98h]
  signed int v57; // [esp+18h] [ebp-98h]
  float v58; // [esp+1Ch] [ebp-94h]
  int i; // [esp+1Ch] [ebp-94h]
  int v60; // [esp+1Ch] [ebp-94h]
  float v61; // [esp+20h] [ebp-90h]
  float v62; // [esp+20h] [ebp-90h]
  float v63; // [esp+20h] [ebp-90h]
  float v64; // [esp+24h] [ebp-8Ch]
  float v65; // [esp+24h] [ebp-8Ch]
  float v66; // [esp+28h] [ebp-88h]
  float v67; // [esp+28h] [ebp-88h]
  float v68; // [esp+2Ch] [ebp-84h]
  float v69; // [esp+2Ch] [ebp-84h]
  float v70; // [esp+30h] [ebp-80h]
  float v71; // [esp+30h] [ebp-80h]
  int v72; // [esp+34h] [ebp-7Ch]
  float v73; // [esp+34h] [ebp-7Ch]
  float v74; // [esp+38h] [ebp-78h]
  int v75; // [esp+38h] [ebp-78h]
  ObjectFaceQuad *facequads; // [esp+38h] [ebp-78h]
  int v77; // [esp+3Ch] [ebp-74h]
  float v78; // [esp+3Ch] [ebp-74h]
  int v79; // [esp+3Ch] [ebp-74h]
  float v80; // [esp+40h] [ebp-70h]
  float v81; // [esp+40h] [ebp-70h]
  float v82; // [esp+44h] [ebp-6Ch]
  float v83; // [esp+44h] [ebp-6Ch]
  float v84; // [esp+48h] [ebp-68h]
  float v85; // [esp+48h] [ebp-68h]
  float v86; // [esp+4Ch] [ebp-64h]
  float v87; // [esp+50h] [ebp-60h]
  float v88; // [esp+50h] [ebp-60h]
  float v89; // [esp+54h] [ebp-5Ch]
  float v90; // [esp+60h] [ebp-50h]
  float v91; // [esp+64h] [ebp-4Ch]
  float v92; // [esp+68h] [ebp-48h]
  TransformMatrix v93; // [esp+70h] [ebp-40h] BYREF
  float arg2a; // [esp+B4h] [ebp+4h]
  char *v95; // [esp+C4h] [ebp+14h]

  v6 = 0;
  self->kind = PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY;
  v70 = 0.0;
  if ( arg3 == 4 )
  {
    self->kind = PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY;
    v70 = 0.5;
  }
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = arg3;
  v72 = (__int64)(arg2 * 6.2831855);
  v77 = v72 + 14;
  self->width_or_scale = 1.0;
  self->segment_count = v72 + 14;
  self->segment_count_f = (float)(v72 + 14);
  v7 = (double)v72;
  v58 = v7;
  arg2a = v7 * 0.15915494;
  allocate_path_template_samples(self);
  self->special_runtime_flag_9c = 1;
  v48 = 0;
  v8 = 0;
  do
  {
    v61 = (float)v48;
    self->primary_samples[v8].center_x = (double)(int)self->width_cells * 0.5 - 4.0 - v61 * 0.14285715 * v70;
    self->primary_samples[v8].rotation_scalar_98 = 0.0;
    self->primary_samples[v8].rotation_scalar_94 = 0.0;
    self->primary_samples[v8].special_scalar = 0.0;
    self->primary_samples[v8].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v8].transform);
    self->primary_samples[v8].transform.position.x = self->primary_samples[v8].center_x;
    self->primary_samples[v8].transform.position.y = 0.0;
    self->primary_samples[v8].transform.position.z = v61;
    self->primary_samples[v8].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[v8].transform);
    self->secondary_samples[v8].transform.position.x = self->primary_samples[v8].center_x;
    self->secondary_samples[v8].transform.position.y = 0.49000001;
    self->secondary_samples[v8++].transform.position.z = v61;
    self->secondary_samples[v8 - 1].delta_length = 1.0;
    ++v48;
  }
  while ( v8 < 7 );
  v9 = 0;
  v49 = 0;
  v10 = v72 + 7;
  do
  {
    self->primary_samples[v10].center_x = (1.0 - (double)v49 * 0.16666667) * v70
                                        + 4.0
                                        - (double)(int)self->width_cells * 0.5;
    self->primary_samples[v10].rotation_scalar_98 = 0.0;
    self->primary_samples[v10].rotation_scalar_94 = 0.0;
    self->primary_samples[v10].special_scalar = 0.0;
    self->primary_samples[v10].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v10].transform);
    self->primary_samples[v10].transform.position.x = self->primary_samples[v10].center_x;
    self->primary_samples[v10].transform.position.y = 0.0;
    v74 = (float)(v9 + 7);
    self->primary_samples[v10].transform.position.z = v74;
    self->primary_samples[v10].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[v10].transform);
    ++v9;
    self->secondary_samples[v10].transform.position.x = self->primary_samples[v10].center_x;
    v49 = v9;
    self->secondary_samples[v10].transform.position.y = 0.49000001;
    self->secondary_samples[v10++].transform.position.z = v74;
    self->secondary_samples[v10 - 1].delta_length = 1.0;
  }
  while ( v9 < 7 );
  v50 = 0;
  if ( v72 > 0 )
  {
    v62 = arg2a - 0.49000001;
    v11 = 168 * v77;
    v75 = 168 * v77;
    v12 = 7;
    while ( 1 )
    {
      v13 = (double)v50;
      v78 = v13 * 6.2831855 / v58;
      self->primary_samples[v12].center_x = (*(float *)((char *)self->primary_samples + v11 - 24)
                                           - self->primary_samples->center_x)
                                          * v13
                                          / v58
                                          + self->primary_samples->center_x;
      p_center_x = &self->primary_samples[v12].center_x;
      v54 = v78 * 0.5;
      v46 = v54 + 4.712389;
      *p_center_x = sine(v46) * v70 + *p_center_x;
      self->primary_samples[v12].rotation_scalar_98 = 0.0;
      self->primary_samples[v12].rotation_scalar_94 = 0.0;
      self->primary_samples[v12].special_scalar = 0.0;
      self->primary_samples[v12].lateral_scale = 1.0;
      set_matrix_identity(&self->primary_samples[v12].transform);
      self->primary_samples[v12].transform.position.x = self->primary_samples[v12].center_x;
      self->primary_samples[v12].transform.position.z = sine(v78) * arg2a + 7.0;
      self->primary_samples[v12].transform.position.y = arg2a - cosine(v78) * arg2a;
      set_matrix_identity(&self->secondary_samples[v12].transform);
      self->secondary_samples[v12].transform.position.x = self->primary_samples[v12].center_x;
      self->secondary_samples[v12].transform.position.z = sine(v78) * v62 + 7.0;
      self->secondary_samples[v12].transform.position.y = arg2a - cosine(v78) * v62;
      v15 = &self->primary_samples[v12];
      v15->transform.basis_right.x = 1.0;
      v15->transform.basis_right.y = 0.0;
      v15->transform.basis_right.z = 0.0;
      self->primary_samples[v12].transform.basis_up.x = 0.0;
      self->primary_samples[v12].transform.basis_up.y = arg2a - self->primary_samples[v12].transform.position.y;
      self->primary_samples[v12].transform.basis_up.z = 7.0 - self->primary_samples[v12].transform.position.z;
      normalize_vector((Vec3 *)&self->primary_samples[v12].transform.basis_up);
      cross_vectors(
        (Vec3 *)&self->primary_samples[v12].transform.basis_forward,
        (Vec3 *)&self->primary_samples[v12],
        (Vec3 *)&self->primary_samples[v12].transform.basis_up);
      v16 = &self->secondary_samples[v12];
      v16->transform.basis_right.x = 1.0;
      v16->transform.basis_right.y = 0.0;
      v16->transform.basis_right.z = 0.0;
      self->secondary_samples[v12].transform.basis_up.x = 0.0;
      self->secondary_samples[v12].transform.basis_up.y = arg2a - self->secondary_samples[v12].transform.position.y;
      self->secondary_samples[v12].transform.basis_up.z = 7.0 - self->secondary_samples[v12].transform.position.z;
      normalize_vector((Vec3 *)&self->secondary_samples[v12].transform.basis_up);
      cross_vectors(
        (Vec3 *)&self->secondary_samples[v12].transform.basis_forward,
        (Vec3 *)&self->secondary_samples[v12],
        (Vec3 *)&self->secondary_samples[v12].transform.basis_up);
      set_matrix_identity(&v93);
      v17 = v54;
      v55 = sine(v54);
      v47 = sine(v17) * v55 * 0.52359879;
      rotate_matrix_world_y(&v93, v47);
      self->primary_samples[v12].transform.position.z = self->primary_samples[v12].transform.position.z - 7.0;
      self->secondary_samples[v12].transform.position.z = self->secondary_samples[v12].transform.position.z - 7.0;
      sub_44D1D0(&self->primary_samples[v12], &v93.basis_right.x);
      sub_44D1D0(&self->secondary_samples[v12], &v93.basis_right.x);
      self->primary_samples[v12].transform.position.z = self->primary_samples[v12].transform.position.z + 7.0;
      self->secondary_samples[v12].transform.position.z = self->secondary_samples[v12].transform.position.z + 7.0;
      qmemcpy(&self->secondary_samples[v12], &self->primary_samples[v12], 0x40u);
      primary_samples = self->primary_samples;
      v19 = primary_samples[v12].transform.basis_up.x * 0.49000001;
      v87 = primary_samples[v12].transform.basis_up.y * 0.49000001;
      v20 = primary_samples[v12].transform.basis_up.z * 0.49000001;
      p_position = &self->secondary_samples[v12++].transform.position;
      v89 = v20;
      p_position->x = v19 + p_position->x;
      p_position->y = v87 + p_position->y;
      p_position->z = v89 + p_position->z;
      if ( ++v50 >= v72 )
        break;
      v11 = v75;
    }
    v6 = 0;
  }
  v22 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v23 = 0;
    do
    {
      v24 = self->primary_samples;
      p_x = &v24[v23].delta_dir_to_next.x;
      v64 = v24[v23 + 1].transform.position.x - v24[v23].transform.position.x;
      v66 = v24[v23 + 1].transform.position.y - v24[v23].transform.position.y;
      v26 = v24[v23 + 1].transform.position.z - v24[v23].transform.position.z;
      *p_x = v64;
      p_x[1] = v66;
      v68 = v26;
      p_x[2] = v68;
      self->primary_samples[v23].delta_length = normalize_vector(&self->primary_samples[v23].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      v28 = &secondary_samples[v23].delta_dir_to_next.x;
      v80 = secondary_samples[v23 + 1].transform.position.x - secondary_samples[v23].transform.position.x;
      v82 = secondary_samples[v23 + 1].transform.position.y - secondary_samples[v23].transform.position.y;
      v29 = secondary_samples[v23 + 1].transform.position.z - secondary_samples[v23].transform.position.z;
      *v28 = v80;
      v28[1] = v82;
      v84 = v29;
      v28[2] = v84;
      ++v22;
      self->secondary_samples[v23].delta_length = normalize_vector(&self->secondary_samples[v23].delta_dir_to_next);
      ++v23;
    }
    while ( v22 < (signed int)(self->segment_count - 1) );
  }
  p_delta_dir_to_next = &self->primary_samples[self->segment_count - 1].delta_dir_to_next;
  p_delta_dir_to_next->x = 0.0;
  p_delta_dir_to_next->y = 0.0;
  p_delta_dir_to_next->z = 1.0;
  self->primary_samples[self->segment_count - 1].delta_length = 1.0;
  v31 = &self->secondary_samples[self->segment_count - 1].delta_dir_to_next;
  v31->x = 0.0;
  v31->y = 0.0;
  v31->z = 1.0;
  self->secondary_samples[self->segment_count - 1].delta_length = 1.0;
  request_object_vertices(self->strip_mesh, (self->segment_count + 1) * (self->width_cells + 1));
  request_object_facequads(self->strip_mesh, 2 * self->segment_count * self->width_cells);
  strip_mesh = self->strip_mesh;
  facequads = strip_mesh->facequads;
  v33 = 0;
  vertices = strip_mesh->vertices;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    v34 = 0;
    v79 = 0;
    do
    {
      width_cells = self->width_cells;
      v36 = 0;
      v51 = 0;
      for ( i = width_cells; v36 <= width_cells; i = width_cells )
      {
        v37 = (double)v51 - (double)i * 0.5;
        v38 = (float *)((char *)&self->primary_samples->transform.basis_right.x + v34);
        if ( v33 == self->segment_count )
        {
          v34 = v79;
          v91 = v37 * *(v38 - 42);
          v92 = v37 * *(v38 - 41);
          v90 = *(v38 - 28) + 1.0;
          v81 = *(v38 - 30) + v91;
          v83 = *(v38 - 29) + v92;
          v40 = &vertices[v36 + v33 * (width_cells + 1)].x;
          v41 = v90 + v37 * *(v38 - 40);
          *v40 = v81;
          v40[1] = v83;
          v85 = v41;
          v40[2] = v85;
        }
        else
        {
          v86 = v37 * *v38;
          v88 = v37 * v38[1];
          v65 = v86 + v38[12];
          v67 = v88 + v38[13];
          v69 = v37 * v38[2] + v38[14];
          v39 = &vertices[v36 + v33 * (width_cells + 1)].x;
          *v39 = v65;
          v39[1] = v67;
          v39[2] = v69;
        }
        width_cells = self->width_cells;
        v51 = ++v36;
      }
      ++v33;
      v34 += 168;
      v79 = v34;
    }
    while ( v33 <= (signed int)self->segment_count );
  }
  v42 = 0;
  if ( (int)self->segment_count > 0 )
  {
    while ( 1 )
    {
      v52 = 0;
      if ( (int)self->width_cells > 0 )
      {
        v73 = (double)(v42 % 8) * 0.125;
        v63 = (double)(v42 % 8 + 1) * 0.125;
        do
        {
          v43 = 0;
          v57 = v6 + 1;
          v60 = 0;
          v71 = (double)v52 * 0.125;
          v53 = (double)(v6 + 1) * 0.125;
          while ( 1 )
          {
            v44 = &facequads[2 * v6 + 2 * v42 * self->width_cells + v43];
            v44->flags = 0;
            if ( v43 )
            {
              v44->vertex_index_a = v42 * (LOWORD(self->width_cells) + 1) + v6 + 1;
              v44->vertex_index_b = v6 + v42 * (LOWORD(self->width_cells) + 1);
              v44->vertex_index_c = v6 + (v42 + 1) * (LOWORD(self->width_cells) + 1);
              v44->vertex_index_d = (v42 + 1) * (LOWORD(self->width_cells) + 1) + v6 + 1;
              v44->texture_ref = get_or_create_texture_ref((TextureRefList *)dword_4B7790, v95, 0, 0);
              v44->u0 = v53;
              v44->v0 = v73;
              v44->u1 = v71;
              v44->v1 = v73;
              v44->u2 = v71;
              v44->v2 = v63;
              v44->u3 = v53;
            }
            else
            {
              v44->vertex_index_a = v6 + v42 * (LOWORD(self->width_cells) + 1);
              v44->vertex_index_b = v42 * (LOWORD(self->width_cells) + 1) + v6 + 1;
              v44->vertex_index_c = (v42 + 1) * (LOWORD(self->width_cells) + 1) + v6 + 1;
              v44->vertex_index_d = v6 + (v42 + 1) * (LOWORD(self->width_cells) + 1);
              v44->texture_ref = get_or_create_texture_ref((TextureRefList *)dword_4B7790, texture_b, 0, 0);
              v44->u0 = v71;
              v44->v0 = v73;
              v44->u1 = v53;
              v44->v1 = v73;
              v44->u2 = v53;
              v44->v2 = v63;
              v44->u3 = v71;
            }
            v44->v3 = v63;
            if ( ++v60 >= 2 )
              break;
            v43 = v60;
          }
          ++v6;
          v52 = v57;
        }
        while ( v57 < (signed int)self->width_cells );
      }
      if ( ++v42 >= (signed int)self->segment_count )
        break;
      v6 = 0;
    }
  }
  return finalize_path_template(self);
}

