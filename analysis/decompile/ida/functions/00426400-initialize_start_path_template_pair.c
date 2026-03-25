/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_start_path_template_pair @ 0x426400 */
/* selector: initialize_start_path_template_pair */

int32_t __thiscall initialize_start_path_template_pair(
        PathTemplate *self,
        float arg2,
        int32_t arg3,
        char *texture_path)
{
  double v5; // st7
  uint32_t segment_count; // eax
  double v7; // st7
  int i; // edi
  int v9; // edi
  bool v10; // zf
  int v11; // edi
  PathTemplateSample *v12; // eax
  PathTemplateSample *primary_samples; // edx
  float *p_x; // eax
  double v15; // st7
  PathTemplateSample *v16; // ecx
  PathTemplateSample *v17; // eax
  double v18; // st7
  double v19; // st7
  signed int v20; // ebx
  int v21; // edi
  PathTemplateSample *v22; // edx
  float *v23; // eax
  double v24; // st7
  PathTemplateSample *secondary_samples; // ecx
  float *v26; // eax
  double v27; // st7
  PathTemplateStripMesh *strip_mesh; // eax
  signed int v29; // edi
  int v30; // ebx
  signed int width_cells; // ecx
  signed int v32; // edx
  PathTemplateSample *v33; // eax
  double v34; // st7
  int v35; // eax
  float *v36; // ecx
  signed int j; // ebx
  int v38; // edi
  int v39; // ecx
  ObjectFaceQuad *v40; // ebp
  float v42; // [esp+0h] [ebp-58h]
  int v43; // [esp+14h] [ebp-44h]
  float v44; // [esp+14h] [ebp-44h]
  float v45; // [esp+18h] [ebp-40h]
  float v46; // [esp+18h] [ebp-40h]
  float v47; // [esp+1Ch] [ebp-3Ch]
  int v48; // [esp+1Ch] [ebp-3Ch]
  int v49; // [esp+1Ch] [ebp-3Ch]
  float v50; // [esp+20h] [ebp-38h]
  ObjectFaceQuad *facequads; // [esp+20h] [ebp-38h]
  float v52; // [esp+24h] [ebp-34h]
  float v53; // [esp+24h] [ebp-34h]
  Vec3 *vertices; // [esp+24h] [ebp-34h]
  signed int v55; // [esp+24h] [ebp-34h]
  float v56; // [esp+34h] [ebp-24h]
  float v57; // [esp+38h] [ebp-20h]
  float v58; // [esp+3Ch] [ebp-1Ch]
  float v59; // [esp+40h] [ebp-18h]
  float v60; // [esp+40h] [ebp-18h]
  float v61; // [esp+44h] [ebp-14h]
  float v62; // [esp+44h] [ebp-14h]
  float v63; // [esp+48h] [ebp-10h]
  float v64; // [esp+4Ch] [ebp-Ch]
  float v65; // [esp+4Ch] [ebp-Ch]
  float v66; // [esp+4Ch] [ebp-Ch]
  float v67; // [esp+50h] [ebp-8h]
  float v68; // [esp+50h] [ebp-8h]
  float v69; // [esp+50h] [ebp-8h]
  float v70; // [esp+54h] [ebp-4h]
  float v71; // [esp+54h] [ebp-4h]
  float v72; // [esp+54h] [ebp-4h]
  float arg2a; // [esp+5Ch] [ebp+4h]
  int arg2b; // [esp+5Ch] [ebp+4h]
  int arg2c; // [esp+5Ch] [ebp+4h]
  float arg2d; // [esp+5Ch] [ebp+4h]
  int32_t arg3a; // [esp+60h] [ebp+8h]
  int32_t arg3b; // [esp+60h] [ebp+8h]
  int32_t arg3c; // [esp+60h] [ebp+8h]
  int32_t arg3d; // [esp+60h] [ebp+8h]
  float arg3e; // [esp+60h] [ebp+8h]
  char *v82; // [esp+68h] [ebp+10h]

  self->kind = 36;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = arg3;
  v43 = (__int64)(arg2 * 3.1415927);
  self->width_or_scale = 1.0;
  self->segment_count = v43 + 16;
  self->segment_count_f = (float)(v43 + 15);
  v5 = (double)v43;
  v45 = v5;
  arg2a = v5 * 0.31830987;
  allocate_path_nodes(self);
  segment_count = self->segment_count;
  self->special_runtime_flag_9c = 0;
  v7 = arg2a + arg2a;
  arg3a = 0;
  self->segment_count = segment_count - 1;
  for ( i = 0; i < 5; self->secondary_samples[i - 1].delta_length = 1.0 )
  {
    self->primary_samples[i].center_x = 0.0;
    self->primary_samples[i].rotation_scalar_98 = 0.0;
    self->primary_samples[i].rotation_scalar_94 = 0.0;
    self->primary_samples[i].special_scalar = 0.0;
    self->primary_samples[i].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[i].transform);
    self->primary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    v47 = v7;
    self->primary_samples[i].transform.position.y = v47;
    v50 = (float)arg3a;
    self->primary_samples[i].transform.position.z = v50;
    self->primary_samples[i].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[i].transform);
    self->secondary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    v52 = v7 + 0.49000001;
    self->secondary_samples[i].transform.position.y = v52;
    self->secondary_samples[i++].transform.position.z = v50;
    ++arg3a;
  }
  v48 = 11;
  arg3b = v43 + 5;
  v9 = v43 + 5;
  do
  {
    self->primary_samples[v9].center_x = 0.0;
    self->primary_samples[v9].rotation_scalar_98 = 0.0;
    self->primary_samples[v9].rotation_scalar_94 = 0.0;
    self->primary_samples[v9].special_scalar = 0.0;
    self->primary_samples[v9].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v9].transform);
    self->primary_samples[v9].transform.position.x = self->primary_samples[v9].center_x;
    self->primary_samples[v9].transform.position.y = 0.0;
    self->primary_samples[v9].transform.position.z = (float)arg3b;
    self->primary_samples[v9].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[v9].transform);
    self->secondary_samples[v9].transform.position.x = self->primary_samples[v9].center_x;
    self->secondary_samples[v9].transform.position.y = 0.49000001;
    self->secondary_samples[v9].transform.position.z = self->primary_samples[v9].transform.position.z;
    self->secondary_samples[v9++].delta_length = 1.0;
    v10 = v48 == 1;
    ++arg3b;
    --v48;
  }
  while ( !v10 );
  arg3c = 0;
  if ( v43 > 0 )
  {
    v11 = 5;
    do
    {
      self->primary_samples[v11].center_x = 0.0;
      self->primary_samples[v11].rotation_scalar_98 = 0.0;
      self->primary_samples[v11].rotation_scalar_94 = 0.0;
      self->primary_samples[v11].special_scalar = 0.0;
      self->primary_samples[v11].lateral_scale = 1.0;
      set_matrix_identity(&self->primary_samples[v11].transform);
      self->primary_samples[v11].transform.position.x = self->primary_samples[v11].center_x;
      v53 = (float)(arg3c + 5);
      self->primary_samples[v11].transform.position.z = v53;
      v42 = (double)arg3c * 3.1415927 / v45;
      self->primary_samples[v11].transform.position.y = (cosine(v42) + 1.0) * arg2a;
      set_matrix_identity(&self->secondary_samples[v11].transform);
      self->secondary_samples[v11].transform.position.x = self->primary_samples[v11].center_x;
      self->secondary_samples[v11].transform.position.z = v53;
      self->secondary_samples[v11].transform.position.y = self->primary_samples[v11].transform.position.y + 0.49000001;
      if ( v11 <= 5 )
      {
        set_matrix_rotation_identity(&self->primary_samples[v11 - 1].transform);
        set_matrix_rotation_identity(&self->secondary_samples[v11 - 1].transform);
      }
      else
      {
        v12 = &self->primary_samples[v11 - 1];
        v12->transform.basis_right.x = 1.0;
        v12->transform.basis_right.y = 0.0;
        v12->transform.basis_right.z = 0.0;
        primary_samples = self->primary_samples;
        p_x = &primary_samples[v11 - 1].transform.basis_forward.x;
        v56 = primary_samples[v11].transform.position.x - primary_samples[v11 - 1].transform.position.x;
        v57 = p_x[47] - p_x[5];
        v15 = p_x[48] - p_x[6];
        *p_x = v56;
        p_x[1] = v57;
        v58 = v15;
        p_x[2] = v58;
        normalize_vector((Vec3 *)&self->primary_samples[v11 - 1].transform.basis_forward);
        cross_vectors(
          (Vec3 *)&self->primary_samples[v11 - 1].transform.basis_up,
          (Vec3 *)&self->primary_samples[v11 - 1].transform.basis_forward,
          (Vec3 *)&self->primary_samples[v11 - 1]);
        v16 = &self->secondary_samples[v11 - 1];
        v16->transform.basis_right.x = 1.0;
        v16->transform.basis_right.y = 0.0;
        v16->transform.basis_right.z = 0.0;
        v17 = &self->secondary_samples[v11];
        v18 = v17->transform.position.x - v17[-1].transform.position.x;
        v17 = (PathTemplateSample *)((char *)v17 - 136);
        v64 = v18;
        v67 = v17[1].transform.basis_up.y - v17->transform.basis_up.y;
        v19 = v17[1].transform.basis_up.z - v17->transform.basis_up.z;
        v17->transform.basis_right.x = v64;
        v17->transform.basis_right.y = v67;
        v70 = v19;
        v17->transform.basis_right.z = v70;
        normalize_vector((Vec3 *)&self->secondary_samples[v11 - 1].transform.basis_forward);
        cross_vectors(
          (Vec3 *)&self->secondary_samples[v11 - 1].transform.basis_up,
          (Vec3 *)&self->secondary_samples[v11 - 1].transform.basis_forward,
          (Vec3 *)&self->secondary_samples[v11 - 1]);
      }
      ++v11;
      ++arg3c;
    }
    while ( arg3c < v43 );
  }
  v20 = 0;
  if ( (int)self->segment_count > 0 )
  {
    v21 = 0;
    do
    {
      v22 = self->primary_samples;
      v23 = &v22[v21].delta_dir_to_next.x;
      v65 = v22[v21 + 1].transform.position.x - v22[v21].transform.position.x;
      v68 = v22[v21 + 1].transform.position.y - v22[v21].transform.position.y;
      v24 = v22[v21 + 1].transform.position.z - v22[v21].transform.position.z;
      *v23 = v65;
      v23[1] = v68;
      v71 = v24;
      v23[2] = v71;
      self->primary_samples[v21].delta_length = normalize_vector(&self->primary_samples[v21].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      v26 = &secondary_samples[v21].delta_dir_to_next.x;
      v59 = secondary_samples[v21 + 1].transform.position.x - secondary_samples[v21].transform.position.x;
      v61 = secondary_samples[v21 + 1].transform.position.y - secondary_samples[v21].transform.position.y;
      v27 = secondary_samples[v21 + 1].transform.position.z - secondary_samples[v21].transform.position.z;
      *v26 = v59;
      v26[1] = v61;
      v63 = v27;
      v26[2] = v63;
      ++v20;
      self->secondary_samples[v21].delta_length = normalize_vector(&self->secondary_samples[v21].delta_dir_to_next);
      ++v21;
    }
    while ( v20 < (signed int)self->segment_count );
  }
  request_object_vertices(self->strip_mesh, (self->segment_count + 1) * (self->width_cells + 1));
  request_object_facequads(self->strip_mesh, 2 * self->segment_count * self->width_cells);
  strip_mesh = self->strip_mesh;
  v29 = 0;
  facequads = strip_mesh->facequads;
  vertices = strip_mesh->vertices;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    v30 = 0;
    do
    {
      width_cells = self->width_cells;
      v32 = 0;
      arg2b = 0;
      for ( arg3d = width_cells; v32 <= width_cells; arg3d = width_cells )
      {
        v33 = &self->primary_samples[v30];
        v34 = (double)arg2b - (double)arg3d * 0.5;
        v60 = v34 * v33->transform.basis_right.x;
        v62 = v34 * v33->transform.basis_right.y;
        v66 = v60 + v33->transform.position.x;
        v69 = v62 + v33->transform.position.y;
        v72 = v34 * v33->transform.basis_right.z + v33->transform.position.z;
        v35 = v32 + v29 * (width_cells + 1);
        arg2b = ++v32;
        v36 = &vertices[v35].x;
        *v36 = v66;
        v36[1] = v69;
        v36[2] = v72;
        width_cells = self->width_cells;
      }
      ++v29;
      ++v30;
    }
    while ( v29 <= (signed int)self->segment_count );
  }
  for ( j = 0; j < (signed int)self->segment_count; ++j )
  {
    v38 = 0;
    arg2c = 0;
    if ( (int)self->width_cells > 0 )
    {
      arg3e = (double)(j % 8) * 0.125;
      v46 = (double)(j % 8 + 1) * 0.125;
      do
      {
        v39 = 0;
        v55 = v38 + 1;
        v49 = 0;
        arg2d = (double)arg2c * 0.125;
        v44 = (double)(v38 + 1) * 0.125;
        while ( 1 )
        {
          v40 = &facequads[2 * v38 + 2 * j * self->width_cells + v39];
          if ( v39 )
          {
            v40->flags = 4;
            v40->vertex_index_a = j * (LOWORD(self->width_cells) + 1) + v38 + 1;
            v40->vertex_index_b = v38 + j * (LOWORD(self->width_cells) + 1);
            v40->vertex_index_c = v38 + (j + 1) * (LOWORD(self->width_cells) + 1);
            v40->vertex_index_d = (j + 1) * (LOWORD(self->width_cells) + 1) + v38 + 1;
            v40->texture_ref = get_or_create_texture_ref(dword_4B7790, v82, 0, 0);
            v40->u0 = v44;
            v40->v0 = arg3e;
            v40->u1 = arg2d;
            v40->v1 = arg3e;
            v40->u2 = arg2d;
            v40->v2 = v46;
            v40->u3 = v44;
          }
          else
          {
            v40->vertex_index_a = v38 + j * (LOWORD(self->width_cells) + 1);
            v40->vertex_index_b = j * (LOWORD(self->width_cells) + 1) + v38 + 1;
            v40->vertex_index_c = (j + 1) * (LOWORD(self->width_cells) + 1) + v38 + 1;
            v40->vertex_index_d = v38 + (j + 1) * (LOWORD(self->width_cells) + 1);
            v40->texture_ref = get_or_create_texture_ref(dword_4B7790, v82, 0, 0);
            v40->u0 = arg2d;
            v40->v0 = arg3e;
            v40->u1 = v44;
            v40->v1 = arg3e;
            v40->u2 = v44;
            v40->v2 = v46;
            v40->u3 = arg2d;
          }
          v40->v3 = v46;
          if ( ++v49 >= 2 )
            break;
          v39 = v49;
        }
        ++v38;
        arg2c = v55;
      }
      while ( v55 < (signed int)self->width_cells );
    }
  }
  return finalize_path_template_record(self);
}

