/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_loopout_path_template_pair @ 0x41c5f0 */
/* selector: initialize_loopout_path_template_pair */

int32_t __thiscall initialize_loopout_path_template_pair(
        PathTemplate *self,
        float arg2,
        int32_t arg3,
        char *texture_a,
        char *texture_b)
{
  double v6; // st7
  int v7; // edi
  int v8; // ebx
  int v9; // edi
  double v10; // st7
  int v11; // edi
  double v12; // st7
  float *p_center_x; // ebx
  PathTemplateSample *v14; // ecx
  PathTemplateSample *v15; // eax
  signed int v16; // ebx
  int v17; // edi
  float *p_x; // eax
  double v19; // st7
  double v20; // st7
  PathTemplateSample *secondary_samples; // ecx
  float *v22; // eax
  double v23; // st7
  Vec3 *p_delta_dir_to_next; // edx
  Vec3 *v25; // ecx
  PathTemplateStripMesh *strip_mesh; // eax
  signed int v27; // edi
  int v28; // edx
  signed int width_cells; // ecx
  signed int v30; // ebx
  double v31; // st7
  float *v32; // eax
  float *v33; // ecx
  double v34; // st7
  float *v35; // edx
  signed int i; // ebx
  int v37; // edi
  int v38; // ecx
  uint32_t v39; // ebp
  float v41; // [esp+0h] [ebp-64h]
  int v42; // [esp+14h] [ebp-50h]
  float v43; // [esp+14h] [ebp-50h]
  float v44; // [esp+18h] [ebp-4Ch]
  float v45; // [esp+18h] [ebp-4Ch]
  float v46; // [esp+18h] [ebp-4Ch]
  float v47; // [esp+1Ch] [ebp-48h]
  int v48; // [esp+1Ch] [ebp-48h]
  int v49; // [esp+1Ch] [ebp-48h]
  float v50; // [esp+20h] [ebp-44h]
  Vec3 *vertices; // [esp+20h] [ebp-44h]
  signed int v52; // [esp+20h] [ebp-44h]
  ObjectFaceQuad *facequads; // [esp+24h] [ebp-40h]
  float v54; // [esp+28h] [ebp-3Ch]
  float v55; // [esp+28h] [ebp-3Ch]
  float v56; // [esp+2Ch] [ebp-38h]
  float v57; // [esp+2Ch] [ebp-38h]
  float v58; // [esp+30h] [ebp-34h]
  float v59; // [esp+30h] [ebp-34h]
  float v60; // [esp+34h] [ebp-30h]
  float v61; // [esp+34h] [ebp-30h]
  float v62; // [esp+38h] [ebp-2Ch]
  float v63; // [esp+38h] [ebp-2Ch]
  float v64; // [esp+3Ch] [ebp-28h]
  float v65; // [esp+3Ch] [ebp-28h]
  float v66; // [esp+40h] [ebp-24h]
  float v67; // [esp+44h] [ebp-20h]
  float v68; // [esp+44h] [ebp-20h]
  float v69; // [esp+4Ch] [ebp-18h]
  float v70; // [esp+50h] [ebp-14h]
  float v71; // [esp+60h] [ebp-4h]
  float arg2a; // [esp+68h] [ebp+4h]
  int arg2b; // [esp+68h] [ebp+4h]
  int arg2c; // [esp+68h] [ebp+4h]
  float arg2d; // [esp+68h] [ebp+4h]
  int32_t arg3a; // [esp+6Ch] [ebp+8h]
  int32_t arg3b; // [esp+6Ch] [ebp+8h]
  float arg3f; // [esp+6Ch] [ebp+8h]
  int32_t arg3c; // [esp+6Ch] [ebp+8h]
  int32_t arg3d; // [esp+6Ch] [ebp+8h]
  float arg3e; // [esp+6Ch] [ebp+8h]
  char *v82; // [esp+78h] [ebp+14h]

  self->kind = PATH_TEMPLATE_KIND_LOOPOUT;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = arg3;
  v42 = (__int64)(arg2 * 6.2831855);
  self->width_or_scale = 1.0;
  self->segment_count = v42 + 14;
  self->segment_count_f = (float)(v42 + 14);
  v6 = (double)v42;
  v47 = v6;
  arg2a = v6 * 0.15915494;
  allocate_path_template_samples(self);
  self->special_runtime_flag_9c = 1;
  arg3a = 0;
  v7 = 0;
  do
  {
    v44 = (float)arg3a;
    self->primary_samples[v7].center_x = (double)(int)self->width_cells * 0.5 - 4.0 - v44 * 0.11111111 * 0.30000001;
    self->primary_samples[v7].rotation_scalar_98 = 0.0;
    self->primary_samples[v7].rotation_scalar_94 = 0.0;
    self->primary_samples[v7].special_scalar = 0.0;
    self->primary_samples[v7].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v7].transform);
    self->primary_samples[v7].transform.position.x = self->primary_samples[v7].center_x;
    self->primary_samples[v7].transform.position.y = 0.0;
    self->primary_samples[v7].transform.position.z = v44;
    self->primary_samples[v7].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[v7].transform);
    self->secondary_samples[v7].transform.position.x = self->primary_samples[v7].center_x;
    self->secondary_samples[v7].transform.position.y = 0.49000001;
    self->secondary_samples[v7++].transform.position.z = v44;
    self->secondary_samples[v7 - 1].delta_length = 1.0;
    ++arg3a;
  }
  while ( v7 < 10 );
  v8 = 0;
  arg3b = 0;
  v9 = v42 + 10;
  do
  {
    self->primary_samples[v9].center_x = (1.0 - (double)arg3b * 0.33333334) * 0.30000001
                                       + 4.0
                                       - (double)(int)self->width_cells * 0.5;
    self->primary_samples[v9].rotation_scalar_98 = 0.0;
    self->primary_samples[v9].rotation_scalar_94 = 0.0;
    self->primary_samples[v9].special_scalar = 0.0;
    self->primary_samples[v9].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v9].transform);
    self->primary_samples[v9].transform.position.x = self->primary_samples[v9].center_x;
    self->primary_samples[v9].transform.position.y = 0.0;
    arg3f = (float)(v8 + 10);
    self->primary_samples[v9].transform.position.z = arg3f;
    self->primary_samples[v9].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[v9].transform);
    v10 = arg3f;
    ++v8;
    self->secondary_samples[v9].transform.position.x = self->primary_samples[v9].center_x;
    arg3b = v8;
    self->secondary_samples[v9].transform.position.y = 0.49000001;
    self->secondary_samples[v9++].transform.position.z = v10;
    self->secondary_samples[v9 - 1].delta_length = 1.0;
  }
  while ( v8 < 4 );
  arg3c = 0;
  v67 = -arg2a;
  if ( v42 > 0 )
  {
    v50 = arg2a + 0.49000001;
    v11 = 10;
    do
    {
      v12 = (double)arg3c;
      v45 = v12 * 6.2831855 / v47;
      self->primary_samples[v11].center_x = (self->primary_samples[v42 + 10].center_x - self->primary_samples->center_x)
                                          * v12
                                          / v47
                                          + self->primary_samples->center_x;
      p_center_x = &self->primary_samples[v11].center_x;
      v41 = v45 * 0.5 + 4.712389;
      *p_center_x = sine(v41) * 0.30000001 + *p_center_x;
      self->primary_samples[v11].rotation_scalar_98 = 0.0;
      self->primary_samples[v11].rotation_scalar_94 = 0.0;
      self->primary_samples[v11].special_scalar = 0.0;
      self->primary_samples[v11].lateral_scale = 1.0;
      set_matrix_identity(&self->primary_samples[v11].transform);
      self->primary_samples[v11].transform.position.x = self->primary_samples[v11].center_x;
      self->primary_samples[v11].transform.position.z = sine(v45) * arg2a + 10.0;
      self->primary_samples[v11].transform.position.y = cosine(v45) * arg2a + v67;
      set_matrix_identity(&self->secondary_samples[v11].transform);
      self->secondary_samples[v11].transform.position.x = self->primary_samples[v11].center_x;
      self->secondary_samples[v11].transform.position.z = sine(v45) * v50 + 10.0;
      self->secondary_samples[v11].transform.position.y = cosine(v45) * v50 + v67;
      v14 = &self->primary_samples[v11];
      v14->transform.basis_right.x = 1.0;
      v14->transform.basis_right.y = 0.0;
      v14->transform.basis_right.z = 0.0;
      self->primary_samples[v11].transform.basis_up.x = 0.0;
      self->primary_samples[v11].transform.basis_up.y = -(v67 - self->primary_samples[v11].transform.position.y);
      self->primary_samples[v11].transform.basis_up.z = -(10.0 - self->primary_samples[v11].transform.position.z);
      normalize_vector((Vec3 *)&self->primary_samples[v11].transform.basis_up);
      cross_vectors(
        (Vec3 *)&self->primary_samples[v11].transform.basis_forward,
        (Vec3 *)&self->primary_samples[v11],
        (Vec3 *)&self->primary_samples[v11].transform.basis_up);
      v15 = &self->secondary_samples[v11];
      v15->transform.basis_right.x = 1.0;
      v15->transform.basis_right.y = 0.0;
      v15->transform.basis_right.z = 0.0;
      self->secondary_samples[v11].transform.basis_up.x = 0.0;
      self->secondary_samples[v11].transform.basis_up.y = -(v67 - self->secondary_samples[v11].transform.position.y);
      self->secondary_samples[v11].transform.basis_up.z = -(10.0 - self->secondary_samples[v11].transform.position.z);
      normalize_vector((Vec3 *)&self->secondary_samples[v11].transform.basis_up);
      cross_vectors(
        (Vec3 *)&self->secondary_samples[v11].transform.basis_forward,
        (Vec3 *)&self->secondary_samples[v11],
        (Vec3 *)&self->secondary_samples[v11].transform.basis_up);
      ++v11;
      ++arg3c;
    }
    while ( arg3c < v42 );
  }
  v16 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v17 = 0;
    do
    {
      p_x = &self->primary_samples[v17].transform.basis_right.x;
      v19 = p_x[54] - p_x[12];
      p_x += 32;
      v60 = v19;
      v62 = p_x[23] - *(p_x - 19);
      v20 = p_x[24] - *(p_x - 18);
      *p_x = v60;
      p_x[1] = v62;
      v64 = v20;
      p_x[2] = v64;
      self->primary_samples[v17].delta_length = normalize_vector(&self->primary_samples[v17].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      v22 = &secondary_samples[v17].delta_dir_to_next.x;
      v54 = secondary_samples[v17 + 1].transform.position.x - secondary_samples[v17].transform.position.x;
      v56 = secondary_samples[v17 + 1].transform.position.y - secondary_samples[v17].transform.position.y;
      v23 = secondary_samples[v17 + 1].transform.position.z - secondary_samples[v17].transform.position.z;
      *v22 = v54;
      v22[1] = v56;
      v58 = v23;
      v22[2] = v58;
      ++v16;
      self->secondary_samples[v17].delta_length = normalize_vector(&self->secondary_samples[v17].delta_dir_to_next);
      ++v17;
    }
    while ( v16 < (signed int)(self->segment_count - 1) );
  }
  p_delta_dir_to_next = &self->primary_samples[self->segment_count - 1].delta_dir_to_next;
  p_delta_dir_to_next->x = 0.0;
  p_delta_dir_to_next->y = 0.0;
  p_delta_dir_to_next->z = 1.0;
  self->primary_samples[self->segment_count - 1].delta_length = 1.0;
  v25 = &self->secondary_samples[self->segment_count - 1].delta_dir_to_next;
  v25->x = 0.0;
  v25->y = 0.0;
  v25->z = 1.0;
  self->secondary_samples[self->segment_count - 1].delta_length = 1.0;
  request_object_vertices(self->strip_mesh, (self->segment_count + 1) * (self->width_cells + 1));
  request_object_facequads(self->strip_mesh, 2 * self->segment_count * self->width_cells);
  strip_mesh = self->strip_mesh;
  v27 = 0;
  vertices = strip_mesh->vertices;
  facequads = strip_mesh->facequads;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    v28 = 0;
    v48 = 0;
    do
    {
      width_cells = self->width_cells;
      v30 = 0;
      arg2b = 0;
      for ( arg3d = width_cells; v30 <= width_cells; arg3d = width_cells )
      {
        v31 = (double)arg2b - (double)arg3d * 0.5;
        v32 = (float *)((char *)&self->primary_samples->transform.basis_right.x + v28);
        if ( v27 == self->segment_count )
        {
          v69 = v31 * *(v32 - 42);
          v70 = v31 * *(v32 - 41);
          v34 = v31 * *(v32 - 40);
          v71 = *(v32 - 28) + 1.0;
          v55 = *(v32 - 30) + v69;
          v57 = *(v32 - 29) + v70;
          v35 = &vertices[v30 + v27 * (width_cells + 1)].x;
          *v35 = v55;
          v35[1] = v57;
          v59 = v71 + v34;
          v35[2] = v59;
          v28 = v48;
        }
        else
        {
          v66 = v31 * *v32;
          v68 = v31 * v32[1];
          v61 = v66 + v32[12];
          v63 = v68 + v32[13];
          v65 = v31 * v32[2] + v32[14];
          v33 = &vertices[v30 + v27 * (width_cells + 1)].x;
          *v33 = v61;
          v33[1] = v63;
          v33[2] = v65;
        }
        width_cells = self->width_cells;
        arg2b = ++v30;
      }
      ++v27;
      v28 += 168;
      v48 = v28;
    }
    while ( v27 <= (signed int)self->segment_count );
  }
  for ( i = 0; i < (signed int)self->segment_count; ++i )
  {
    v37 = 0;
    arg2c = 0;
    if ( (int)self->width_cells > 0 )
    {
      arg3e = (double)(i % 8) * 0.125;
      v46 = (double)(i % 8 + 1) * 0.125;
      do
      {
        v38 = 0;
        v52 = v37 + 1;
        v49 = 0;
        arg2d = (double)arg2c * 0.125;
        v43 = (double)(v37 + 1) * 0.125;
        while ( 1 )
        {
          v39 = (uint32_t)facequads + 96 * v37 + 96 * i * self->width_cells + 48 * v38;
          *(_WORD *)v39 = 0;
          if ( v38 )
          {
            *(_WORD *)(v39 + 2) = i * (LOWORD(self->width_cells) + 1) + v37 + 1;
            *(_WORD *)(v39 + 4) = v37 + i * (LOWORD(self->width_cells) + 1);
            *(_WORD *)(v39 + 6) = v37 + (i + 1) * (LOWORD(self->width_cells) + 1);
            *(_WORD *)(v39 + 8) = (i + 1) * (LOWORD(self->width_cells) + 1) + v37 + 1;
            *(_DWORD *)(v39 + 12) = get_or_create_texture_ref((TextureRefList *)dword_4B7790, v82, 0, 0);
            *(float *)(v39 + 16) = v43;
            *(float *)(v39 + 20) = arg3e;
            *(float *)(v39 + 24) = arg2d;
            *(float *)(v39 + 28) = arg3e;
            *(float *)(v39 + 32) = arg2d;
            *(float *)(v39 + 36) = v46;
            *(float *)(v39 + 40) = v43;
          }
          else
          {
            *(_WORD *)(v39 + 2) = v37 + i * (LOWORD(self->width_cells) + 1);
            *(_WORD *)(v39 + 4) = i * (LOWORD(self->width_cells) + 1) + v37 + 1;
            *(_WORD *)(v39 + 6) = (i + 1) * (LOWORD(self->width_cells) + 1) + v37 + 1;
            *(_WORD *)(v39 + 8) = v37 + (i + 1) * (LOWORD(self->width_cells) + 1);
            *(_DWORD *)(v39 + 12) = get_or_create_texture_ref((TextureRefList *)dword_4B7790, texture_b, 0, 0);
            *(float *)(v39 + 16) = arg2d;
            *(float *)(v39 + 20) = arg3e;
            *(float *)(v39 + 24) = v43;
            *(float *)(v39 + 28) = arg3e;
            *(float *)(v39 + 32) = v43;
            *(float *)(v39 + 36) = v46;
            *(float *)(v39 + 40) = arg2d;
          }
          *(float *)(v39 + 44) = v46;
          if ( ++v49 >= 2 )
            break;
          v38 = v49;
        }
        ++v37;
        arg2c = v52;
      }
      while ( v52 < (signed int)self->width_cells );
    }
  }
  return finalize_path_template(self);
}

