/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_looptheloop_path_template_pair @ 0x41b0f0 */
/* selector: initialize_looptheloop_path_template_pair */

int32_t __thiscall initialize_looptheloop_path_template_pair(
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
  int v11; // ecx
  int v12; // edi
  double v13; // st7
  float *p_center_x; // ebx
  PathTemplateSample *v15; // eax
  PathTemplateSample *v16; // edx
  signed int v17; // ebx
  int v18; // edi
  float *p_x; // eax
  double v20; // st7
  double v21; // st7
  PathTemplateSample *secondary_samples; // ecx
  float *v23; // eax
  double v24; // st7
  Vec3 *p_delta_dir_to_next; // edx
  Vec3 *v26; // ecx
  PathTemplateStripMesh *strip_mesh; // eax
  signed int v28; // edi
  int v29; // edx
  signed int width_cells; // ecx
  signed int v31; // ebx
  double v32; // st7
  float *v33; // eax
  float *v34; // ecx
  double v35; // st7
  float *v36; // edx
  signed int i; // ebx
  int v38; // edi
  int v39; // ecx
  ObjectFaceQuad *v40; // ebp
  float v42; // [esp+0h] [ebp-68h]
  float v43; // [esp+14h] [ebp-54h]
  float v44; // [esp+14h] [ebp-54h]
  int v45; // [esp+18h] [ebp-50h]
  float v46; // [esp+18h] [ebp-50h]
  float v47; // [esp+1Ch] [ebp-4Ch]
  float v48; // [esp+1Ch] [ebp-4Ch]
  ObjectFaceQuad *facequads; // [esp+1Ch] [ebp-4Ch]
  float v50; // [esp+20h] [ebp-48h]
  int v51; // [esp+20h] [ebp-48h]
  int v52; // [esp+20h] [ebp-48h]
  int v53; // [esp+24h] [ebp-44h]
  float v54; // [esp+24h] [ebp-44h]
  Vec3 *vertices; // [esp+24h] [ebp-44h]
  signed int v56; // [esp+24h] [ebp-44h]
  int v57; // [esp+28h] [ebp-40h]
  float v58; // [esp+2Ch] [ebp-3Ch]
  float v59; // [esp+2Ch] [ebp-3Ch]
  float v60; // [esp+30h] [ebp-38h]
  float v61; // [esp+30h] [ebp-38h]
  float v62; // [esp+34h] [ebp-34h]
  float v63; // [esp+34h] [ebp-34h]
  float v64; // [esp+38h] [ebp-30h]
  float v65; // [esp+38h] [ebp-30h]
  float v66; // [esp+3Ch] [ebp-2Ch]
  float v67; // [esp+3Ch] [ebp-2Ch]
  float v68; // [esp+40h] [ebp-28h]
  float v69; // [esp+40h] [ebp-28h]
  float v70; // [esp+44h] [ebp-24h]
  float v71; // [esp+48h] [ebp-20h]
  float v72; // [esp+50h] [ebp-18h]
  float v73; // [esp+54h] [ebp-14h]
  float v74; // [esp+64h] [ebp-4h]
  float arg2a; // [esp+6Ch] [ebp+4h]
  int arg2b; // [esp+6Ch] [ebp+4h]
  int arg2c; // [esp+6Ch] [ebp+4h]
  float arg2d; // [esp+6Ch] [ebp+4h]
  int32_t arg3a; // [esp+70h] [ebp+8h]
  int32_t arg3b; // [esp+70h] [ebp+8h]
  float arg3f; // [esp+70h] [ebp+8h]
  int32_t arg3c; // [esp+70h] [ebp+8h]
  int32_t arg3d; // [esp+70h] [ebp+8h]
  float arg3e; // [esp+70h] [ebp+8h]
  char *v85; // [esp+7Ch] [ebp+14h]

  self->kind = PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY;
  v43 = 0.0;
  if ( arg3 == 4 )
  {
    self->kind = PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY;
    v43 = 0.30000001;
  }
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = arg3;
  v45 = (__int64)(arg2 * 6.2831855);
  v53 = v45 + 14;
  self->width_or_scale = 1.0;
  self->segment_count = v45 + 14;
  self->segment_count_f = (float)(v45 + 14);
  v6 = (double)v45;
  v50 = v6;
  arg2a = v6 * 0.15915494;
  allocate_path_template_samples(self);
  self->special_runtime_flag_9c = 1;
  arg3a = 0;
  v7 = 0;
  do
  {
    v47 = (float)arg3a;
    self->primary_samples[v7].center_x = (double)(int)self->width_cells * 0.5 - 4.0 - v47 * 0.14285715 * v43;
    self->primary_samples[v7].rotation_scalar_98 = 0.0;
    self->primary_samples[v7].rotation_scalar_94 = 0.0;
    self->primary_samples[v7].special_scalar = 0.0;
    self->primary_samples[v7].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v7].transform);
    self->primary_samples[v7].transform.position.x = self->primary_samples[v7].center_x;
    self->primary_samples[v7].transform.position.y = 0.0;
    self->primary_samples[v7].transform.position.z = v47;
    self->primary_samples[v7].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[v7].transform);
    self->secondary_samples[v7].transform.position.x = self->primary_samples[v7].center_x;
    self->secondary_samples[v7].transform.position.y = 0.49000001;
    self->secondary_samples[v7++].transform.position.z = v47;
    self->secondary_samples[v7 - 1].delta_length = 1.0;
    ++arg3a;
  }
  while ( v7 < 7 );
  v8 = 0;
  arg3b = 0;
  v9 = v45 + 7;
  do
  {
    self->primary_samples[v9].center_x = (1.0 - (double)arg3b * 0.16666667) * v43
                                       + 4.0
                                       - (double)(int)self->width_cells * 0.5;
    self->primary_samples[v9].rotation_scalar_98 = 0.0;
    self->primary_samples[v9].rotation_scalar_94 = 0.0;
    self->primary_samples[v9].special_scalar = 0.0;
    self->primary_samples[v9].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v9].transform);
    self->primary_samples[v9].transform.position.x = self->primary_samples[v9].center_x;
    self->primary_samples[v9].transform.position.y = 0.0;
    arg3f = (float)(v8 + 7);
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
  while ( v8 < 7 );
  arg3c = 0;
  if ( v45 > 0 )
  {
    v48 = arg2a - 0.49000001;
    v11 = 168 * v53;
    v57 = 168 * v53;
    v12 = 7;
    while ( 1 )
    {
      v13 = (double)arg3c;
      v54 = v13 * 6.2831855 / v50;
      self->primary_samples[v12].center_x = (*(float *)((char *)self->primary_samples + v11 - 24)
                                           - self->primary_samples->center_x)
                                          * v13
                                          / v50
                                          + self->primary_samples->center_x;
      p_center_x = &self->primary_samples[v12].center_x;
      v42 = v54 * 0.5 + 4.712389;
      *p_center_x = sine(v42) * v43 + *p_center_x;
      self->primary_samples[v12].rotation_scalar_98 = 0.0;
      self->primary_samples[v12].rotation_scalar_94 = 0.0;
      self->primary_samples[v12].special_scalar = 0.0;
      self->primary_samples[v12].lateral_scale = 1.0;
      set_matrix_identity(&self->primary_samples[v12].transform);
      self->primary_samples[v12].transform.position.x = self->primary_samples[v12].center_x;
      self->primary_samples[v12].transform.position.z = sine(v54) * arg2a + 7.0;
      self->primary_samples[v12].transform.position.y = arg2a - cosine(v54) * arg2a;
      set_matrix_identity(&self->secondary_samples[v12].transform);
      self->secondary_samples[v12].transform.position.x = self->primary_samples[v12].center_x;
      self->secondary_samples[v12].transform.position.z = sine(v54) * v48 + 7.0;
      self->secondary_samples[v12].transform.position.y = arg2a - cosine(v54) * v48;
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
      ++v12;
      if ( ++arg3c >= v45 )
        break;
      v11 = v57;
    }
  }
  v17 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v18 = 0;
    do
    {
      p_x = &self->primary_samples[v18].transform.basis_right.x;
      v20 = p_x[54] - p_x[12];
      p_x += 32;
      v64 = v20;
      v66 = p_x[23] - *(p_x - 19);
      v21 = p_x[24] - *(p_x - 18);
      *p_x = v64;
      p_x[1] = v66;
      v68 = v21;
      p_x[2] = v68;
      self->primary_samples[v18].delta_length = normalize_vector(&self->primary_samples[v18].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      v23 = &secondary_samples[v18].delta_dir_to_next.x;
      v58 = secondary_samples[v18 + 1].transform.position.x - secondary_samples[v18].transform.position.x;
      v60 = secondary_samples[v18 + 1].transform.position.y - secondary_samples[v18].transform.position.y;
      v24 = secondary_samples[v18 + 1].transform.position.z - secondary_samples[v18].transform.position.z;
      *v23 = v58;
      v23[1] = v60;
      v62 = v24;
      v23[2] = v62;
      ++v17;
      self->secondary_samples[v18].delta_length = normalize_vector(&self->secondary_samples[v18].delta_dir_to_next);
      ++v18;
    }
    while ( v17 < (signed int)(self->segment_count - 1) );
  }
  p_delta_dir_to_next = &self->primary_samples[self->segment_count - 1].delta_dir_to_next;
  p_delta_dir_to_next->x = 0.0;
  p_delta_dir_to_next->y = 0.0;
  p_delta_dir_to_next->z = 1.0;
  self->primary_samples[self->segment_count - 1].delta_length = 1.0;
  v26 = &self->secondary_samples[self->segment_count - 1].delta_dir_to_next;
  v26->x = 0.0;
  v26->y = 0.0;
  v26->z = 1.0;
  self->secondary_samples[self->segment_count - 1].delta_length = 1.0;
  request_object_vertices(self->strip_mesh, (self->segment_count + 1) * (self->width_cells + 1));
  request_object_facequads(self->strip_mesh, 2 * self->segment_count * self->width_cells);
  strip_mesh = self->strip_mesh;
  v28 = 0;
  vertices = strip_mesh->vertices;
  facequads = strip_mesh->facequads;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    v29 = 0;
    v51 = 0;
    do
    {
      width_cells = self->width_cells;
      v31 = 0;
      arg2b = 0;
      for ( arg3d = width_cells; v31 <= width_cells; arg3d = width_cells )
      {
        v32 = (double)arg2b - (double)arg3d * 0.5;
        v33 = (float *)((char *)&self->primary_samples->transform.basis_right.x + v29);
        if ( v28 == self->segment_count )
        {
          v72 = v32 * *(v33 - 42);
          v73 = v32 * *(v33 - 41);
          v35 = v32 * *(v33 - 40);
          v74 = *(v33 - 28) + 1.0;
          v59 = *(v33 - 30) + v72;
          v61 = *(v33 - 29) + v73;
          v36 = &vertices[v31 + v28 * (width_cells + 1)].x;
          *v36 = v59;
          v36[1] = v61;
          v63 = v74 + v35;
          v36[2] = v63;
          v29 = v51;
        }
        else
        {
          v70 = v32 * *v33;
          v71 = v32 * v33[1];
          v65 = v70 + v33[12];
          v67 = v71 + v33[13];
          v69 = v32 * v33[2] + v33[14];
          v34 = &vertices[v31 + v28 * (width_cells + 1)].x;
          *v34 = v65;
          v34[1] = v67;
          v34[2] = v69;
        }
        width_cells = self->width_cells;
        arg2b = ++v31;
      }
      ++v28;
      v29 += 168;
      v51 = v29;
    }
    while ( v28 <= (signed int)self->segment_count );
  }
  for ( i = 0; i < (signed int)self->segment_count; ++i )
  {
    v38 = 0;
    arg2c = 0;
    if ( (int)self->width_cells > 0 )
    {
      arg3e = (double)(i % 8) * 0.125;
      v44 = (double)(i % 8 + 1) * 0.125;
      do
      {
        v39 = 0;
        v56 = v38 + 1;
        v52 = 0;
        arg2d = (double)arg2c * 0.125;
        v46 = (double)(v38 + 1) * 0.125;
        while ( 1 )
        {
          v40 = &facequads[2 * v38 + 2 * i * self->width_cells + v39];
          v40->flags = 0;
          if ( v39 )
          {
            v40->vertex_index_a = i * (LOWORD(self->width_cells) + 1) + v38 + 1;
            v40->vertex_index_b = v38 + i * (LOWORD(self->width_cells) + 1);
            v40->vertex_index_c = v38 + (i + 1) * (LOWORD(self->width_cells) + 1);
            v40->vertex_index_d = (i + 1) * (LOWORD(self->width_cells) + 1) + v38 + 1;
            v40->texture_ref = get_or_create_texture_ref((TextureRefList *)dword_4B7790, v85, 0, 0);
            v40->u0 = v46;
            v40->v0 = arg3e;
            v40->u1 = arg2d;
            v40->v1 = arg3e;
            v40->u2 = arg2d;
            v40->v2 = v44;
            v40->u3 = v46;
          }
          else
          {
            v40->vertex_index_a = v38 + i * (LOWORD(self->width_cells) + 1);
            v40->vertex_index_b = i * (LOWORD(self->width_cells) + 1) + v38 + 1;
            v40->vertex_index_c = (i + 1) * (LOWORD(self->width_cells) + 1) + v38 + 1;
            v40->vertex_index_d = v38 + (i + 1) * (LOWORD(self->width_cells) + 1);
            v40->texture_ref = get_or_create_texture_ref((TextureRefList *)dword_4B7790, texture_b, 0, 0);
            v40->u0 = arg2d;
            v40->v0 = arg3e;
            v40->u1 = v46;
            v40->v1 = arg3e;
            v40->u2 = v46;
            v40->v2 = v44;
            v40->u3 = arg2d;
          }
          v40->v3 = v44;
          if ( ++v52 >= 2 )
            break;
          v39 = v52;
        }
        ++v38;
        arg2c = v56;
      }
      while ( v56 < (signed int)self->width_cells );
    }
  }
  return finalize_path_template(self);
}

