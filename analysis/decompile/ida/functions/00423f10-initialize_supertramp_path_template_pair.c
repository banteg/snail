/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_supertramp_path_template_pair @ 0x423f10 */
/* selector: initialize_supertramp_path_template_pair */

int32_t __thiscall initialize_supertramp_path_template_pair(
        PathTemplate *self,
        float arg2,
        int32_t arg3,
        char *texture_a,
        char *texture_b,
        char *texture_c)
{
  double v7; // st7
  uint32_t segment_count; // eax
  int v9; // edi
  int v10; // edi
  PathTemplateSample *v11; // ecx
  PathTemplateSample *v12; // eax
  signed int v13; // ebx
  int v14; // edi
  PathTemplateSample *primary_samples; // edx
  float *p_x; // eax
  double v17; // st7
  PathTemplateSample *secondary_samples; // ecx
  float *v19; // eax
  double v20; // st7
  PathTemplateStripMesh *strip_mesh; // eax
  signed int v22; // ebx
  ObjectFaceQuad *facequads; // edx
  signed int width_cells; // ecx
  signed int v25; // edi
  PathTemplateSample *v26; // eax
  double v27; // st7
  int v28; // eax
  float *v29; // ecx
  signed int j; // ebx
  int v31; // edi
  int v32; // ecx
  uint32_t v33; // eax
  uint32_t v34; // ebp
  char *v35; // ecx
  TextureRef *texture_ref; // eax
  uint32_t v37; // ebp
  float v39; // [esp+0h] [ebp-2Ch]
  int v40; // [esp+4h] [ebp-28h]
  int v41; // [esp+4h] [ebp-28h]
  float v42; // [esp+4h] [ebp-28h]
  float v43; // [esp+8h] [ebp-24h]
  int i; // [esp+8h] [ebp-24h]
  int v45; // [esp+8h] [ebp-24h]
  float v46; // [esp+Ch] [ebp-20h]
  ObjectFaceQuad *v47; // [esp+Ch] [ebp-20h]
  float v48; // [esp+10h] [ebp-1Ch]
  float v49; // [esp+10h] [ebp-1Ch]
  Vec3 *vertices; // [esp+10h] [ebp-1Ch]
  signed int v51; // [esp+10h] [ebp-1Ch]
  float v52; // [esp+14h] [ebp-18h]
  float v53; // [esp+14h] [ebp-18h]
  float v54; // [esp+18h] [ebp-14h]
  float v55; // [esp+18h] [ebp-14h]
  float v56; // [esp+1Ch] [ebp-10h]
  float v57; // [esp+20h] [ebp-Ch]
  float v58; // [esp+20h] [ebp-Ch]
  float v59; // [esp+24h] [ebp-8h]
  float v60; // [esp+24h] [ebp-8h]
  float v61; // [esp+28h] [ebp-4h]
  float v62; // [esp+28h] [ebp-4h]
  float arg2a; // [esp+30h] [ebp+4h]
  int arg2b; // [esp+30h] [ebp+4h]
  int arg2c; // [esp+30h] [ebp+4h]
  float arg2d; // [esp+30h] [ebp+4h]
  int32_t arg3a; // [esp+34h] [ebp+8h]
  int32_t arg3b; // [esp+34h] [ebp+8h]
  int32_t arg3c; // [esp+34h] [ebp+8h]
  float arg3d; // [esp+34h] [ebp+8h]
  int v71; // [esp+48h] [ebp+1Ch]

  self->kind = PATH_TEMPLATE_KIND_SUPERTRAMP;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = arg3;
  v40 = (__int64)(arg2 * 1.0461504);
  self->width_or_scale = 1.0;
  self->segment_count = v40 + 8;
  self->segment_count_f = (float)(v40 + 7);
  v7 = (double)v40;
  v46 = v7;
  arg2a = v7 * 0.95588547;
  allocate_path_nodes(self);
  segment_count = self->segment_count;
  self->special_runtime_flag_9c = 0;
  arg3a = 0;
  self->segment_count = segment_count - 1;
  v9 = 0;
  do
  {
    self->primary_samples[v9].center_x = 0.0;
    self->primary_samples[v9].rotation_scalar_98 = 0.0;
    self->primary_samples[v9].rotation_scalar_94 = 0.0;
    self->primary_samples[v9].special_scalar = 0.0;
    self->primary_samples[v9].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v9].transform);
    self->primary_samples[v9].transform.position.x = self->primary_samples[v9].center_x;
    v48 = (float)arg3a;
    self->primary_samples[v9].transform.position.y = 0.0;
    self->primary_samples[v9].transform.position.z = v48;
    self->primary_samples[v9].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[v9].transform);
    self->secondary_samples[v9].transform.position.x = self->primary_samples[v9].center_x;
    self->secondary_samples[v9].transform.position.y = 0.49000001;
    self->secondary_samples[v9++].transform.position.z = v48;
    self->secondary_samples[v9 - 1].delta_length = 1.0;
    ++arg3a;
  }
  while ( v9 < 7 );
  arg3b = 0;
  if ( v40 >= 0 )
  {
    v43 = arg2a - 0.49000001;
    v10 = 7;
    do
    {
      self->primary_samples[v10].center_x = 0.0;
      self->primary_samples[v10].rotation_scalar_98 = 0.0;
      self->primary_samples[v10].rotation_scalar_94 = 0.0;
      self->primary_samples[v10].special_scalar = 0.0;
      self->primary_samples[v10].lateral_scale = 1.0;
      v49 = (double)arg3b * 1.0461504 / v46;
      set_matrix_identity(&self->primary_samples[v10].transform);
      self->primary_samples[v10].transform.position.x = self->primary_samples[v10].center_x;
      self->primary_samples[v10].transform.position.z = sine(v49) * arg2a + 7.0;
      self->primary_samples[v10].transform.position.y = arg2a - cosine(v49) * arg2a;
      set_matrix_identity(&self->secondary_samples[v10].transform);
      self->secondary_samples[v10].transform.position.x = self->primary_samples[v10].center_x;
      self->secondary_samples[v10].transform.position.z = sine(v49) * v43 + 7.0;
      self->secondary_samples[v10].transform.position.y = arg2a - cosine(v49) * v43;
      v11 = &self->primary_samples[v10];
      v11->transform.basis_right.x = 1.0;
      v11->transform.basis_right.y = 0.0;
      v11->transform.basis_right.z = 0.0;
      self->primary_samples[v10].transform.basis_up.x = 0.0;
      self->primary_samples[v10].transform.basis_up.y = arg2a - self->primary_samples[v10].transform.position.y;
      self->primary_samples[v10].transform.basis_up.z = 7.0 - self->primary_samples[v10].transform.position.z;
      normalize_vector((Vec3 *)&self->primary_samples[v10].transform.basis_up);
      cross_vectors(
        (Vec3 *)&self->primary_samples[v10].transform.basis_forward,
        (Vec3 *)&self->primary_samples[v10],
        (Vec3 *)&self->primary_samples[v10].transform.basis_up);
      v12 = &self->secondary_samples[v10];
      v12->transform.basis_right.x = 1.0;
      v12->transform.basis_right.y = 0.0;
      v12->transform.basis_right.z = 0.0;
      self->secondary_samples[v10].transform.basis_up.x = 0.0;
      self->secondary_samples[v10].transform.basis_up.y = arg2a - self->secondary_samples[v10].transform.position.y;
      self->secondary_samples[v10].transform.basis_up.z = 7.0 - self->secondary_samples[v10].transform.position.z;
      normalize_vector((Vec3 *)&self->secondary_samples[v10].transform.basis_up);
      cross_vectors(
        (Vec3 *)&self->secondary_samples[v10].transform.basis_forward,
        (Vec3 *)&self->secondary_samples[v10],
        (Vec3 *)&self->secondary_samples[v10].transform.basis_up);
      ++v10;
      ++arg3b;
    }
    while ( arg3b <= v40 );
  }
  v13 = 0;
  if ( (int)self->segment_count > 0 )
  {
    v14 = 0;
    do
    {
      primary_samples = self->primary_samples;
      p_x = &primary_samples[v14].delta_dir_to_next.x;
      v57 = primary_samples[v14 + 1].transform.position.x - primary_samples[v14].transform.position.x;
      v59 = primary_samples[v14 + 1].transform.position.y - primary_samples[v14].transform.position.y;
      v17 = primary_samples[v14 + 1].transform.position.z - primary_samples[v14].transform.position.z;
      *p_x = v57;
      p_x[1] = v59;
      v61 = v17;
      p_x[2] = v61;
      self->primary_samples[v14].delta_length = normalize_vector(&self->primary_samples[v14].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      v19 = &secondary_samples[v14].delta_dir_to_next.x;
      v52 = secondary_samples[v14 + 1].transform.position.x - secondary_samples[v14].transform.position.x;
      v54 = secondary_samples[v14 + 1].transform.position.y - secondary_samples[v14].transform.position.y;
      v20 = secondary_samples[v14 + 1].transform.position.z - secondary_samples[v14].transform.position.z;
      *v19 = v52;
      v19[1] = v54;
      v56 = v20;
      v19[2] = v56;
      ++v13;
      self->secondary_samples[v14].delta_length = normalize_vector(&self->secondary_samples[v14].delta_dir_to_next);
      ++v14;
    }
    while ( v13 < (signed int)self->segment_count );
  }
  request_object_vertices(self->strip_mesh, (self->segment_count + 1) * (self->width_cells + 1));
  request_object_facequads(self->strip_mesh, 2 * self->segment_count * self->width_cells);
  strip_mesh = self->strip_mesh;
  v22 = 0;
  arg3c = 0;
  vertices = strip_mesh->vertices;
  facequads = strip_mesh->facequads;
  v47 = facequads;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    v41 = 0;
    do
    {
      width_cells = self->width_cells;
      v25 = 0;
      arg2b = 0;
      for ( i = width_cells; v25 <= width_cells; i = width_cells )
      {
        v26 = &self->primary_samples[v41];
        v22 = arg3c;
        v27 = (double)arg2b - (double)i * 0.5;
        v53 = v27 * v26->transform.basis_right.x;
        v55 = v27 * v26->transform.basis_right.y;
        v58 = v53 + v26->transform.position.x;
        v60 = v55 + v26->transform.position.y;
        v62 = v27 * v26->transform.basis_right.z + v26->transform.position.z;
        v28 = v25 + arg3c * (width_cells + 1);
        arg2b = ++v25;
        v29 = &vertices[v28].x;
        *v29 = v58;
        v29[1] = v60;
        v29[2] = v62;
        width_cells = self->width_cells;
      }
      arg3c = ++v22;
      ++v41;
    }
    while ( v22 <= (signed int)self->segment_count );
  }
  for ( j = 0; j < (signed int)self->segment_count; ++j )
  {
    v31 = 0;
    arg2c = 0;
    if ( (int)self->width_cells <= 0 )
      continue;
    arg3d = (double)(j % 8) * 0.125;
    v42 = (double)(j % 8 + 1) * 0.125;
    do
    {
      v32 = 0;
      v51 = v31 + 1;
      v45 = 0;
      arg2d = (double)arg2c * 0.125;
      v39 = (double)(v31 + 1) * 0.125;
      while ( 1 )
      {
        v33 = v32 + 2 * (v31 + j * self->width_cells);
        if ( !v32 )
        {
          v34 = (uint32_t)facequads + 48 * v33;
          *(_WORD *)v34 = 0;
          *(_WORD *)(v34 + 2) = v31 + j * (LOWORD(self->width_cells) + 1);
          *(_WORD *)(v34 + 4) = j * (LOWORD(self->width_cells) + 1) + v31 + 1;
          *(_WORD *)(v34 + 6) = (j + 1) * (LOWORD(self->width_cells) + 1) + v31 + 1;
          *(_WORD *)(v34 + 8) = v31 + (j + 1) * (LOWORD(self->width_cells) + 1);
          if ( j == self->segment_count - 1 )
          {
            v35 = (char *)v71;
            goto LABEL_22;
          }
          if ( (((unsigned __int8)j ^ (unsigned __int8)v31) & 1) != 0 )
          {
            v35 = texture_b;
LABEL_22:
            texture_ref = get_or_create_texture_ref((TextureRefList *)dword_4B7790, v35, 0, 0);
          }
          else
          {
            texture_ref = get_or_create_texture_ref((TextureRefList *)dword_4B7790, texture_b, 0, 0);
          }
          *(_DWORD *)(v34 + 12) = texture_ref;
          *(float *)(v34 + 16) = arg2d;
          *(float *)(v34 + 20) = arg3d;
          *(float *)(v34 + 24) = v39;
          *(float *)(v34 + 28) = arg3d;
          *(float *)(v34 + 32) = v39;
          *(float *)(v34 + 36) = v42;
          *(float *)(v34 + 40) = arg2d;
          *(float *)(v34 + 44) = v42;
          goto LABEL_28;
        }
        v37 = (uint32_t)facequads + 48 * v33;
        *(_WORD *)v37 = 0;
        *(_WORD *)(v37 + 2) = j * (LOWORD(self->width_cells) + 1) + v31 + 1;
        *(_WORD *)(v37 + 4) = v31 + j * (LOWORD(self->width_cells) + 1);
        *(_WORD *)(v37 + 6) = v31 + (j + 1) * (LOWORD(self->width_cells) + 1);
        *(_WORD *)(v37 + 8) = (j + 1) * (LOWORD(self->width_cells) + 1) + v31 + 1;
        *(_DWORD *)(v37 + 12) = get_or_create_texture_ref((TextureRefList *)dword_4B7790, texture_c, 0, 0);
        *(float *)(v37 + 16) = v39;
        *(float *)(v37 + 20) = arg3d;
        *(float *)(v37 + 24) = arg2d;
        *(float *)(v37 + 28) = arg3d;
        *(float *)(v37 + 32) = arg2d;
        *(float *)(v37 + 36) = v42;
        *(float *)(v37 + 40) = v39;
        *(float *)(v37 + 44) = v42;
LABEL_28:
        if ( ++v45 >= 2 )
          break;
        v32 = v45;
        facequads = v47;
      }
      ++v31;
      facequads = v47;
      arg2c = v51;
    }
    while ( v51 < (signed int)self->width_cells );
  }
  return finalize_path_template_record(self);
}

