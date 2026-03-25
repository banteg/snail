/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_looptheloopw_path_template_pair @ 0x41bb40 */
/* selector: initialize_looptheloopw_path_template_pair */

int32_t __thiscall initialize_looptheloopw_path_template_pair(
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
  int v11; // ebx
  int v12; // edi
  double v13; // st7
  double v14; // st7
  float *p_center_x; // ebx
  PathTemplateSample *v16; // eax
  PathTemplateSample *v17; // edx
  signed int v18; // ebx
  int v19; // edi
  float *p_x; // eax
  double v21; // st7
  double v22; // st7
  PathTemplateSample *secondary_samples; // ecx
  float *v24; // eax
  double v25; // st7
  Vec3 *p_delta_dir_to_next; // edx
  Vec3 *v27; // ecx
  PathTemplateStripMesh *strip_mesh; // eax
  signed int v29; // edi
  int v30; // edx
  signed int width_cells; // ecx
  signed int v32; // ebx
  double v33; // st7
  float *v34; // eax
  float *v35; // ecx
  float *v36; // edx
  double v37; // st6
  signed int i; // ebx
  int v39; // edi
  int v40; // ecx
  ObjectFaceQuad *v41; // ebp
  float v43; // [esp+0h] [ebp-74h]
  float v44; // [esp+0h] [ebp-74h]
  float v45; // [esp+14h] [ebp-60h]
  float v46; // [esp+14h] [ebp-60h]
  float v47; // [esp+18h] [ebp-5Ch]
  float v48; // [esp+18h] [ebp-5Ch]
  int v49; // [esp+1Ch] [ebp-58h]
  float v50; // [esp+1Ch] [ebp-58h]
  float v51; // [esp+20h] [ebp-54h]
  ObjectFaceQuad *facequads; // [esp+20h] [ebp-54h]
  int v53; // [esp+24h] [ebp-50h]
  float v54; // [esp+24h] [ebp-50h]
  int v55; // [esp+24h] [ebp-50h]
  float v56; // [esp+28h] [ebp-4Ch]
  int v57; // [esp+28h] [ebp-4Ch]
  float v58; // [esp+2Ch] [ebp-48h]
  Vec3 *vertices; // [esp+2Ch] [ebp-48h]
  signed int v60; // [esp+2Ch] [ebp-48h]
  int v61; // [esp+30h] [ebp-44h]
  float v62; // [esp+34h] [ebp-40h]
  float v63; // [esp+34h] [ebp-40h]
  float v64; // [esp+38h] [ebp-3Ch]
  float v65; // [esp+38h] [ebp-3Ch]
  float v66; // [esp+3Ch] [ebp-38h]
  float v67; // [esp+3Ch] [ebp-38h]
  float v68; // [esp+40h] [ebp-34h]
  float v69; // [esp+40h] [ebp-34h]
  float v70; // [esp+44h] [ebp-30h]
  float v71; // [esp+44h] [ebp-30h]
  float v72; // [esp+48h] [ebp-2Ch]
  float v73; // [esp+48h] [ebp-2Ch]
  float v74; // [esp+4Ch] [ebp-28h]
  float v75; // [esp+4Ch] [ebp-28h]
  float v76; // [esp+50h] [ebp-24h]
  float v77; // [esp+54h] [ebp-20h]
  float v78; // [esp+5Ch] [ebp-18h]
  float v79; // [esp+60h] [ebp-14h]
  float v80; // [esp+70h] [ebp-4h]
  float arg2a; // [esp+78h] [ebp+4h]
  int arg2b; // [esp+78h] [ebp+4h]
  int arg2c; // [esp+78h] [ebp+4h]
  float arg2d; // [esp+78h] [ebp+4h]
  int32_t arg3a; // [esp+7Ch] [ebp+8h]
  int32_t arg3b; // [esp+7Ch] [ebp+8h]
  float arg3f; // [esp+7Ch] [ebp+8h]
  int32_t arg3c; // [esp+7Ch] [ebp+8h]
  int32_t arg3d; // [esp+7Ch] [ebp+8h]
  float arg3e; // [esp+7Ch] [ebp+8h]
  char *v91; // [esp+88h] [ebp+14h]

  self->kind = PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY;
  v47 = 0.0;
  if ( arg3 == 4 )
  {
    self->kind = PATH_TEMPLATE_KIND_LOOPTHELOOPW;
    v47 = 0.30000001;
  }
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = arg3;
  v49 = (__int64)(arg2 * 6.2831855);
  v53 = v49 + 14;
  self->width_or_scale = 1.0;
  self->segment_count = v49 + 14;
  self->segment_count_f = (float)(v49 + 14);
  v6 = (double)v49;
  v51 = v6;
  arg2a = v6 * 0.15915494;
  allocate_path_nodes(self);
  self->special_runtime_flag_9c = 1;
  arg3a = 0;
  v7 = 0;
  do
  {
    v45 = (float)arg3a;
    self->primary_samples[v7].center_x = (double)(int)self->width_cells * 0.5 - 4.0 - v45 * 0.14285715 * v47;
    self->primary_samples[v7].rotation_scalar_98 = 0.0;
    self->primary_samples[v7].rotation_scalar_94 = 0.0;
    self->primary_samples[v7].special_scalar = 0.0;
    self->primary_samples[v7].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v7].transform);
    self->primary_samples[v7].transform.position.x = self->primary_samples[v7].center_x;
    self->primary_samples[v7].transform.position.y = 0.0;
    self->primary_samples[v7].transform.position.z = v45;
    self->primary_samples[v7].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[v7].transform);
    self->secondary_samples[v7].transform.position.x = self->primary_samples[v7].center_x;
    self->secondary_samples[v7].transform.position.y = 0.49000001;
    self->secondary_samples[v7++].transform.position.z = v45;
    self->secondary_samples[v7 - 1].delta_length = 1.0;
    ++arg3a;
  }
  while ( v7 < 7 );
  v8 = 0;
  arg3b = 0;
  v9 = v49 + 7;
  do
  {
    self->primary_samples[v9].center_x = (1.0 - (double)arg3b * 0.16666667) * v47
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
  if ( v49 > 0 )
  {
    v58 = arg2a - 0.49000001;
    v11 = 168 * v53;
    v61 = 168 * v53;
    v12 = 7;
    while ( 1 )
    {
      v13 = (double)arg3c;
      v46 = v13;
      v14 = v13 * 6.2831855 / v51;
      v54 = v14;
      v56 = v14 * 0.5;
      v43 = v54 * 8.0;
      v62 = sine(v43);
      v63 = sine(v56) * v62 * 0.39269909;
      self->primary_samples[v12].center_x = (*(float *)((char *)self->primary_samples + v11 - 24)
                                           - self->primary_samples->center_x)
                                          * v46
                                          / v51
                                          + self->primary_samples->center_x;
      p_center_x = &self->primary_samples[v12].center_x;
      v44 = v56 + 4.712389;
      *p_center_x = sine(v44) * v47 + *p_center_x;
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
      self->secondary_samples[v12].transform.position.z = sine(v54) * v58 + 7.0;
      self->secondary_samples[v12].transform.position.y = arg2a - cosine(v54) * v58;
      v16 = &self->primary_samples[v12];
      v16->transform.basis_right.x = 1.0;
      v16->transform.basis_right.y = 0.0;
      v16->transform.basis_right.z = 0.0;
      self->primary_samples[v12].transform.basis_up.x = 0.0;
      self->primary_samples[v12].transform.basis_up.y = arg2a - self->primary_samples[v12].transform.position.y;
      self->primary_samples[v12].transform.basis_up.z = 7.0 - self->primary_samples[v12].transform.position.z;
      normalize_vector((Vec3 *)&self->primary_samples[v12].transform.basis_up);
      cross_vectors(
        (Vec3 *)&self->primary_samples[v12].transform.basis_forward,
        (Vec3 *)&self->primary_samples[v12],
        (Vec3 *)&self->primary_samples[v12].transform.basis_up);
      rotate_matrix_world_z(&self->primary_samples[v12].transform, v63);
      v17 = &self->secondary_samples[v12];
      v17->transform.basis_right.x = 1.0;
      v17->transform.basis_right.y = 0.0;
      v17->transform.basis_right.z = 0.0;
      self->secondary_samples[v12].transform.basis_up.x = 0.0;
      self->secondary_samples[v12].transform.basis_up.y = arg2a - self->secondary_samples[v12].transform.position.y;
      self->secondary_samples[v12].transform.basis_up.z = 7.0 - self->secondary_samples[v12].transform.position.z;
      normalize_vector((Vec3 *)&self->secondary_samples[v12].transform.basis_up);
      cross_vectors(
        (Vec3 *)&self->secondary_samples[v12].transform.basis_forward,
        (Vec3 *)&self->secondary_samples[v12],
        (Vec3 *)&self->secondary_samples[v12].transform.basis_up);
      rotate_matrix_world_z(&self->secondary_samples[v12++].transform, v63);
      if ( ++arg3c >= v49 )
        break;
      v11 = v61;
    }
  }
  v18 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v19 = 0;
    do
    {
      p_x = &self->primary_samples[v19].transform.basis_right.x;
      v21 = p_x[54] - p_x[12];
      p_x += 32;
      v70 = v21;
      v72 = p_x[23] - *(p_x - 19);
      v22 = p_x[24] - *(p_x - 18);
      *p_x = v70;
      p_x[1] = v72;
      v74 = v22;
      p_x[2] = v74;
      self->primary_samples[v19].delta_length = normalize_vector(&self->primary_samples[v19].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      v24 = &secondary_samples[v19].delta_dir_to_next.x;
      v64 = secondary_samples[v19 + 1].transform.position.x - secondary_samples[v19].transform.position.x;
      v66 = secondary_samples[v19 + 1].transform.position.y - secondary_samples[v19].transform.position.y;
      v25 = secondary_samples[v19 + 1].transform.position.z - secondary_samples[v19].transform.position.z;
      *v24 = v64;
      v24[1] = v66;
      v68 = v25;
      v24[2] = v68;
      ++v18;
      self->secondary_samples[v19].delta_length = normalize_vector(&self->secondary_samples[v19].delta_dir_to_next);
      ++v19;
    }
    while ( v18 < (signed int)(self->segment_count - 1) );
  }
  p_delta_dir_to_next = &self->primary_samples[self->segment_count - 1].delta_dir_to_next;
  p_delta_dir_to_next->x = 0.0;
  p_delta_dir_to_next->y = 0.0;
  p_delta_dir_to_next->z = 1.0;
  self->primary_samples[self->segment_count - 1].delta_length = 1.0;
  v27 = &self->secondary_samples[self->segment_count - 1].delta_dir_to_next;
  v27->x = 0.0;
  v27->y = 0.0;
  v27->z = 1.0;
  self->secondary_samples[self->segment_count - 1].delta_length = 1.0;
  request_object_vertices(self->strip_mesh, (self->segment_count + 1) * (self->width_cells + 1));
  request_object_facequads(self->strip_mesh, 2 * self->segment_count * self->width_cells);
  strip_mesh = self->strip_mesh;
  v29 = 0;
  vertices = strip_mesh->vertices;
  facequads = strip_mesh->facequads;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    v30 = 0;
    v57 = 0;
    do
    {
      width_cells = self->width_cells;
      v32 = 0;
      arg2b = 0;
      for ( arg3d = width_cells; v32 <= width_cells; arg3d = width_cells )
      {
        v33 = (double)arg2b - (double)arg3d * 0.5;
        v34 = (float *)((char *)&self->primary_samples->transform.basis_right.x + v30);
        if ( v29 == self->segment_count )
        {
          v78 = v33 * *(v34 - 42);
          v79 = v33 * *(v34 - 41);
          v80 = *(v34 - 28) + 1.0;
          v65 = *(v34 - 30) + v78;
          v67 = *(v34 - 29) + v79;
          v36 = &vertices[v32 + v29 * (width_cells + 1)].x;
          v37 = v80 + v33 * *(v34 - 40);
          *v36 = v65;
          v36[1] = v67;
          v69 = v37;
          v36[2] = v69;
          v30 = v57;
        }
        else
        {
          v76 = v33 * *v34;
          v77 = v33 * v34[1];
          v71 = v76 + v34[12];
          v73 = v77 + v34[13];
          v75 = v33 * v34[2] + v34[14];
          v35 = &vertices[v32 + v29 * (width_cells + 1)].x;
          *v35 = v71;
          v35[1] = v73;
          v35[2] = v75;
        }
        width_cells = self->width_cells;
        arg2b = ++v32;
      }
      ++v29;
      v30 += 168;
      v57 = v30;
    }
    while ( v29 <= (signed int)self->segment_count );
  }
  for ( i = 0; i < (signed int)self->segment_count; ++i )
  {
    v39 = 0;
    arg2c = 0;
    if ( (int)self->width_cells > 0 )
    {
      arg3e = (double)(i % 8) * 0.125;
      v48 = (double)(i % 8 + 1) * 0.125;
      do
      {
        v40 = 0;
        v60 = v39 + 1;
        v55 = 0;
        arg2d = (double)arg2c * 0.125;
        v50 = (double)(v39 + 1) * 0.125;
        while ( 1 )
        {
          v41 = &facequads[2 * v39 + 2 * i * self->width_cells + v40];
          v41->flags = 0;
          if ( v40 )
          {
            v41->vertex_index_a = i * (LOWORD(self->width_cells) + 1) + v39 + 1;
            v41->vertex_index_b = v39 + i * (LOWORD(self->width_cells) + 1);
            v41->vertex_index_c = v39 + (i + 1) * (LOWORD(self->width_cells) + 1);
            v41->vertex_index_d = (i + 1) * (LOWORD(self->width_cells) + 1) + v39 + 1;
            v41->texture_ref = get_or_create_texture_ref((TextureRefList *)dword_4B7790, v91, 0, 0);
            v41->u0 = v50;
            v41->v0 = arg3e;
            v41->u1 = arg2d;
            v41->v1 = arg3e;
            v41->u2 = arg2d;
            v41->v2 = v48;
            v41->u3 = v50;
          }
          else
          {
            v41->vertex_index_a = v39 + i * (LOWORD(self->width_cells) + 1);
            v41->vertex_index_b = i * (LOWORD(self->width_cells) + 1) + v39 + 1;
            v41->vertex_index_c = (i + 1) * (LOWORD(self->width_cells) + 1) + v39 + 1;
            v41->vertex_index_d = v39 + (i + 1) * (LOWORD(self->width_cells) + 1);
            v41->texture_ref = get_or_create_texture_ref((TextureRefList *)dword_4B7790, texture_b, 0, 0);
            v41->u0 = arg2d;
            v41->v0 = arg3e;
            v41->u1 = v50;
            v41->v1 = arg3e;
            v41->u2 = v50;
            v41->v2 = v48;
            v41->u3 = arg2d;
          }
          v41->v3 = v48;
          if ( ++v55 >= 2 )
            break;
          v40 = v55;
        }
        ++v39;
        arg2c = v60;
      }
      while ( v60 < (signed int)self->width_cells );
    }
  }
  return finalize_path_template_record(self);
}

