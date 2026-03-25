/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_turnoverdouble_path_template_pair @ 0x427640 */
/* selector: initialize_turnoverdouble_path_template_pair */

int32_t __thiscall initialize_turnoverdouble_path_template_pair(
        PathTemplate *self,
        float arg2,
        int32_t arg3,
        char *texture_a,
        char *texture_b)
{
  signed int v6; // ebx
  double v7; // st7
  int v8; // edi
  int v9; // edi
  int v10; // ecx
  int v11; // ebx
  double v12; // st7
  double v13; // st7
  PathTemplateSample *primary_samples; // edi
  PathTemplateSample *v15; // edi
  double v16; // st7
  Vec4 *p_basis_up; // ecx
  PathTemplateSample *v18; // eax
  PathTemplateSample *v19; // ecx
  double v20; // st7
  double v21; // st6
  Vec4 *p_position; // eax
  int v23; // edi
  PathTemplateSample *v24; // ecx
  float *p_x; // eax
  double v26; // st7
  PathTemplateSample *secondary_samples; // edx
  float *v28; // eax
  double v29; // st7
  Vec3 *p_delta_dir_to_next; // ecx
  Vec3 *v31; // ecx
  PathTemplateStripMesh *strip_mesh; // eax
  Vec3 *vertices; // ebx
  signed int v34; // edx
  int v35; // esi
  signed int width_cells; // ecx
  signed int v37; // edi
  double v38; // st7
  PathTemplateSample *v39; // eax
  float *v40; // eax
  float v41; // ecx
  double v42; // st7
  signed int i; // edi
  int v44; // esi
  int v45; // ecx
  ObjectFaceQuad *v46; // ebx
  float v48; // [esp+0h] [ebp-64h]
  float v49; // [esp+0h] [ebp-64h]
  float v50; // [esp+14h] [ebp-50h]
  float v51; // [esp+14h] [ebp-50h]
  int v52; // [esp+18h] [ebp-4Ch]
  float v53; // [esp+18h] [ebp-4Ch]
  float v54; // [esp+1Ch] [ebp-48h]
  int v55; // [esp+1Ch] [ebp-48h]
  ObjectFaceQuad *facequads; // [esp+20h] [ebp-44h]
  float v57; // [esp+24h] [ebp-40h]
  float v58; // [esp+24h] [ebp-40h]
  float v59; // [esp+24h] [ebp-40h]
  float v60; // [esp+24h] [ebp-40h]
  float v61; // [esp+24h] [ebp-40h]
  Vec3 *v62; // [esp+24h] [ebp-40h]
  signed int v63; // [esp+24h] [ebp-40h]
  float v64; // [esp+28h] [ebp-3Ch]
  float v65; // [esp+28h] [ebp-3Ch]
  float v66; // [esp+28h] [ebp-3Ch]
  float v67; // [esp+2Ch] [ebp-38h]
  float v68; // [esp+2Ch] [ebp-38h]
  float v69; // [esp+30h] [ebp-34h]
  float v70; // [esp+30h] [ebp-34h]
  float v71; // [esp+34h] [ebp-30h]
  float v72; // [esp+34h] [ebp-30h]
  float v73; // [esp+34h] [ebp-30h]
  float v74; // [esp+38h] [ebp-2Ch]
  float v75; // [esp+38h] [ebp-2Ch]
  float v76; // [esp+38h] [ebp-2Ch]
  float v77; // [esp+3Ch] [ebp-28h]
  float v78; // [esp+3Ch] [ebp-28h]
  float v79; // [esp+3Ch] [ebp-28h]
  float v80; // [esp+40h] [ebp-24h]
  float v81; // [esp+44h] [ebp-20h]
  float v82; // [esp+44h] [ebp-20h]
  float v83; // [esp+48h] [ebp-1Ch]
  float v84; // [esp+4Ch] [ebp-18h]
  float v85; // [esp+50h] [ebp-14h]
  float v86; // [esp+60h] [ebp-4h]
  float arg2a; // [esp+68h] [ebp+4h]
  int arg2b; // [esp+68h] [ebp+4h]
  int arg2c; // [esp+68h] [ebp+4h]
  float arg2d; // [esp+68h] [ebp+4h]
  int32_t arg3a; // [esp+6Ch] [ebp+8h]
  int32_t arg3b; // [esp+6Ch] [ebp+8h]
  int32_t arg3c; // [esp+6Ch] [ebp+8h]
  int32_t arg3d; // [esp+6Ch] [ebp+8h]
  float arg3e; // [esp+6Ch] [ebp+8h]
  char *v96; // [esp+78h] [ebp+14h]

  v6 = 0;
  self->kind = PATH_TEMPLATE_KIND_TURNOVERDOUBLE;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = arg3;
  v52 = (__int64)(arg2 * 9.424778);
  self->width_or_scale = 1.0;
  self->segment_count = v52 + 8;
  self->segment_count_f = (float)(v52 + 8);
  v7 = (double)v52;
  v54 = v7;
  arg2a = v7 * 0.079577468;
  allocate_path_nodes(self);
  self->special_runtime_flag_9c = 0;
  arg3a = 0;
  v8 = 0;
  do
  {
    self->primary_samples[v8].center_x = (double)(int)self->width_cells * 0.5 - 4.0;
    self->primary_samples[v8].rotation_scalar_98 = 0.0;
    self->primary_samples[v8].rotation_scalar_94 = 0.0;
    self->primary_samples[v8].special_scalar = 0.0;
    self->primary_samples[v8].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v8].transform);
    self->primary_samples[v8].transform.position.x = self->primary_samples[v8].center_x;
    v57 = (float)arg3a;
    self->primary_samples[v8].transform.position.y = 0.0;
    self->primary_samples[v8].transform.position.z = v57;
    self->primary_samples[v8].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[v8].transform);
    self->secondary_samples[v8].transform.position.x = self->primary_samples[v8].center_x;
    self->secondary_samples[v8].transform.position.y = 0.49000001;
    self->secondary_samples[v8++].transform.position.z = v57;
    self->secondary_samples[v8 - 1].delta_length = 1.0;
    ++arg3a;
  }
  while ( v8 < 6 );
  arg3b = v52 + 6;
  v9 = v52 + 6;
  do
  {
    self->primary_samples[v9].center_x = (double)(int)self->width_cells * 0.5 - 4.0;
    self->primary_samples[v9].rotation_scalar_98 = 0.0;
    self->primary_samples[v9].rotation_scalar_94 = 0.0;
    self->primary_samples[v9].special_scalar = 0.0;
    self->primary_samples[v9].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v9].transform);
    v58 = (float)arg3b;
    self->primary_samples[v9].transform.position.x = self->primary_samples[v9].center_x;
    self->primary_samples[v9].transform.position.y = 0.0;
    self->primary_samples[v9].transform.position.z = v58;
    self->primary_samples[v9].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[v9].transform);
    self->secondary_samples[v9].transform.position.x = self->primary_samples[v9].center_x;
    self->secondary_samples[v9].transform.position.y = 0.49000001;
    self->secondary_samples[v9].transform.position.z = v58;
    self->secondary_samples[v9++].delta_length = 1.0;
    v10 = ++arg3b + -6 - v52;
  }
  while ( v10 < 2 );
  arg3c = 0;
  if ( v52 > 0 )
  {
    v11 = 6;
    do
    {
      v12 = (double)arg3c;
      v59 = v12 * 6.2831855 / v54;
      v13 = v12 * 12.566371 / v54;
      v50 = v13;
      if ( v13 > 6.2831855 )
        v50 = 12.566371 - v50;
      primary_samples = self->primary_samples;
      v48 = v59 + 1.5707964;
      primary_samples[v11].center_x = sine(v48) * primary_samples->center_x;
      self->primary_samples[v11].rotation_scalar_98 = -v50;
      self->primary_samples[v11].rotation_scalar_94 = 0.0;
      self->primary_samples[v11].special_scalar = 0.0;
      self->primary_samples[v11].lateral_scale = 1.0;
      set_matrix_identity(&self->primary_samples[v11].transform);
      v15 = self->primary_samples;
      v49 = v50 * 0.5;
      v60 = sine(v49);
      v16 = sine(v50);
      self->primary_samples[v11].transform.position.x = v15[v11].center_x - (v16 * v60 + v16 * v60);
      self->primary_samples[v11].transform.position.z = (float)(arg3c + 6);
      self->primary_samples[v11].transform.position.y = (arg2a - cosine(v50) * arg2a) * 0.40000001;
      v61 = cosine(v50);
      v64 = sine(v50);
      p_basis_up = &self->primary_samples[v11].transform.basis_up;
      p_basis_up->x = v64;
      p_basis_up->y = v61;
      p_basis_up->z = 0.0;
      v18 = &self->primary_samples[v11];
      v71 = v18->transform.position.x - v18[-1].transform.position.x;
      v74 = v18->transform.position.y - v18[-1].transform.position.y;
      v77 = v18->transform.position.z - v18[-1].transform.position.z;
      v18 = (PathTemplateSample *)((char *)v18 + 32);
      v18->transform.basis_right.x = v71;
      v18->transform.basis_right.y = v74;
      v18->transform.basis_right.z = v77;
      normalize_vector((Vec3 *)&self->primary_samples[v11].transform.basis_forward);
      cross_vectors(
        (Vec3 *)&self->primary_samples[v11],
        (Vec3 *)&self->primary_samples[v11].transform.basis_up,
        (Vec3 *)&self->primary_samples[v11].transform.basis_forward);
      qmemcpy(&self->secondary_samples[v11], &self->primary_samples[v11], 0x40u);
      v19 = self->primary_samples;
      v20 = v19[v11].transform.basis_up.x * 0.49000001;
      v81 = v19[v11].transform.basis_up.y * 0.49000001;
      v21 = v19[v11].transform.basis_up.z * 0.49000001;
      p_position = &self->secondary_samples[v11++].transform.position;
      v83 = v21;
      p_position->x = v20 + p_position->x;
      p_position->y = v81 + p_position->y;
      p_position->z = v83 + p_position->z;
      ++arg3c;
    }
    while ( arg3c < v52 );
    v6 = 0;
  }
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v23 = 0;
    do
    {
      v24 = self->primary_samples;
      p_x = &v24[v23].delta_dir_to_next.x;
      v72 = v24[v23 + 1].transform.position.x - v24[v23].transform.position.x;
      v75 = v24[v23 + 1].transform.position.y - v24[v23].transform.position.y;
      v26 = v24[v23 + 1].transform.position.z - v24[v23].transform.position.z;
      *p_x = v72;
      p_x[1] = v75;
      v78 = v26;
      p_x[2] = v78;
      self->primary_samples[v23].delta_length = normalize_vector(&self->primary_samples[v23].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      v28 = &secondary_samples[v23].delta_dir_to_next.x;
      v65 = secondary_samples[v23 + 1].transform.position.x - secondary_samples[v23].transform.position.x;
      v67 = secondary_samples[v23 + 1].transform.position.y - secondary_samples[v23].transform.position.y;
      v29 = secondary_samples[v23 + 1].transform.position.z - secondary_samples[v23].transform.position.z;
      *v28 = v65;
      v28[1] = v67;
      v69 = v29;
      v28[2] = v69;
      ++v6;
      self->secondary_samples[v23].delta_length = normalize_vector(&self->secondary_samples[v23].delta_dir_to_next);
      ++v23;
    }
    while ( v6 < (signed int)(self->segment_count - 1) );
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
  vertices = strip_mesh->vertices;
  facequads = strip_mesh->facequads;
  v34 = 0;
  v62 = vertices;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    v35 = 0;
    do
    {
      width_cells = self->width_cells;
      v37 = 0;
      arg2b = 0;
      for ( arg3d = width_cells; v37 <= width_cells; arg2b = v37 )
      {
        v38 = (double)arg2b - (double)arg3d * 0.5;
        v39 = &self->primary_samples[v35];
        if ( v34 == self->segment_count )
        {
          vertices = v62;
          v84 = v38 * v39[-1].transform.basis_right.x;
          v85 = v38 * v39[-1].transform.basis_right.y;
          v42 = v38 * v39[-1].transform.basis_right.z;
          v86 = v39[-1].transform.position.z + 1.0;
          v66 = v39[-1].transform.position.x + v84;
          v68 = v39[-1].transform.position.y + v85;
          v40 = &v62[v37 + v34 * (width_cells + 1)].x;
          *v40 = v66;
          v70 = v86 + v42;
          v40[1] = v68;
          v41 = v70;
        }
        else
        {
          v80 = v38 * v39->transform.basis_right.x;
          v82 = v38 * v39->transform.basis_right.y;
          v73 = v80 + v39->transform.position.x;
          v76 = v82 + v39->transform.position.y;
          v79 = v38 * v39->transform.basis_right.z + v39->transform.position.z;
          v40 = &vertices[v37 + v34 * (width_cells + 1)].x;
          *v40 = v73;
          v40[1] = v76;
          v41 = v79;
        }
        v40[2] = v41;
        width_cells = self->width_cells;
        ++v37;
        arg3d = width_cells;
      }
      ++v34;
      ++v35;
    }
    while ( v34 <= (signed int)self->segment_count );
  }
  for ( i = 0; i < (signed int)self->segment_count; ++i )
  {
    v44 = 0;
    arg2c = 0;
    if ( (int)self->width_cells > 0 )
    {
      arg3e = (double)(i % 8) * 0.125;
      v51 = (double)(i % 8 + 1) * 0.125;
      do
      {
        v45 = 0;
        v63 = v44 + 1;
        v55 = 0;
        arg2d = (double)arg2c * 0.125;
        v53 = (double)(v44 + 1) * 0.125;
        while ( 1 )
        {
          v46 = &facequads[2 * v44 + 2 * i * self->width_cells + v45];
          v46->flags = 0;
          if ( v45 )
          {
            v46->vertex_index_a = i * (LOWORD(self->width_cells) + 1) + v44 + 1;
            v46->vertex_index_b = v44 + i * (LOWORD(self->width_cells) + 1);
            v46->vertex_index_c = v44 + (i + 1) * (LOWORD(self->width_cells) + 1);
            v46->vertex_index_d = (i + 1) * (LOWORD(self->width_cells) + 1) + v44 + 1;
            v46->texture_ref = get_or_create_texture_ref((TextureRefList *)dword_4B7790, v96, 0, 0);
            v46->u0 = v53;
            v46->v0 = arg3e;
            v46->u1 = arg2d;
            v46->v1 = arg3e;
            v46->u2 = arg2d;
            v46->v2 = v51;
            v46->u3 = v53;
          }
          else
          {
            v46->vertex_index_a = v44 + i * (LOWORD(self->width_cells) + 1);
            v46->vertex_index_b = i * (LOWORD(self->width_cells) + 1) + v44 + 1;
            v46->vertex_index_c = (i + 1) * (LOWORD(self->width_cells) + 1) + v44 + 1;
            v46->vertex_index_d = v44 + (i + 1) * (LOWORD(self->width_cells) + 1);
            v46->texture_ref = get_or_create_texture_ref((TextureRefList *)dword_4B7790, texture_b, 0, 0);
            v46->u0 = arg2d;
            v46->v0 = arg3e;
            v46->u1 = v53;
            v46->v1 = arg3e;
            v46->u2 = v53;
            v46->v2 = v51;
            v46->u3 = arg2d;
          }
          v46->v3 = v51;
          if ( ++v55 >= 2 )
            break;
          v45 = v55;
        }
        ++v44;
        arg2c = v63;
      }
      while ( v63 < (signed int)self->width_cells );
    }
  }
  return finalize_path_template_record(self);
}

