/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_sbend_path_template_pair @ 0x42df00 */
/* selector: initialize_sbend_path_template_pair */

int32_t __thiscall initialize_sbend_path_template_pair(
        PathTemplate *self,
        uint32_t arg2,
        float arg3,
        float arg4,
        char arg5,
        char *texture_a,
        char *texture_b)
{
  int v8; // edi
  int v9; // ebx
  int v10; // ebx
  Vec4 *p_basis_up; // edx
  PathTemplateSample *primary_samples; // ecx
  float *p_x; // eax
  double v14; // st7
  PathTemplateSample *v15; // eax
  double v16; // st7
  double v17; // st6
  Vec4 *p_position; // eax
  signed int i; // ebx
  float *v20; // eax
  double v21; // st7
  double v22; // st7
  PathTemplateSample *secondary_samples; // ecx
  float *v24; // eax
  double v25; // st7
  Vec3 *p_delta_dir_to_next; // edx
  Vec3 *v27; // edx
  PathTemplateStripMesh *strip_mesh; // eax
  signed int v29; // edx
  Vec3 *vertices; // esi
  int v31; // ebx
  signed int width_cells; // ecx
  signed int v33; // edi
  double v34; // st7
  PathTemplateSample *v35; // eax
  float *v36; // eax
  float v37; // ecx
  double v38; // st7
  signed int j; // edi
  int v40; // esi
  int v41; // ecx
  ObjectFaceQuad *v42; // ebx
  float v44; // [esp+0h] [ebp-5Ch]
  float v45; // [esp+0h] [ebp-5Ch]
  int v46; // [esp+14h] [ebp-48h]
  int v47; // [esp+14h] [ebp-48h]
  ObjectFaceQuad *facequads; // [esp+18h] [ebp-44h]
  float v49; // [esp+1Ch] [ebp-40h]
  signed int v50; // [esp+1Ch] [ebp-40h]
  float v51; // [esp+20h] [ebp-3Ch]
  float v52; // [esp+20h] [ebp-3Ch]
  float v53; // [esp+24h] [ebp-38h]
  float v54; // [esp+24h] [ebp-38h]
  float v55; // [esp+28h] [ebp-34h]
  float v56; // [esp+28h] [ebp-34h]
  float v57; // [esp+2Ch] [ebp-30h]
  float v58; // [esp+2Ch] [ebp-30h]
  float v59; // [esp+2Ch] [ebp-30h]
  float v60; // [esp+30h] [ebp-2Ch]
  float v61; // [esp+30h] [ebp-2Ch]
  float v62; // [esp+30h] [ebp-2Ch]
  float v63; // [esp+34h] [ebp-28h]
  float v64; // [esp+34h] [ebp-28h]
  float v65; // [esp+34h] [ebp-28h]
  float v66; // [esp+38h] [ebp-24h]
  float v67; // [esp+3Ch] [ebp-20h]
  float v68; // [esp+3Ch] [ebp-20h]
  float v69; // [esp+40h] [ebp-1Ch]
  float v70; // [esp+44h] [ebp-18h]
  float v71; // [esp+48h] [ebp-14h]
  float v72; // [esp+58h] [ebp-4h]
  float arg2c; // [esp+60h] [ebp+4h]
  uint32_t arg2a; // [esp+60h] [ebp+4h]
  float arg2b; // [esp+60h] [ebp+4h]
  int arg3a; // [esp+64h] [ebp+8h]
  float arg3b; // [esp+64h] [ebp+8h]
  float arg4a; // [esp+68h] [ebp+Ch]
  int arg5a; // [esp+6Ch] [ebp+10h]
  int arg5b; // [esp+6Ch] [ebp+10h]
  int arg5c; // [esp+6Ch] [ebp+10h]
  float arg5d; // [esp+6Ch] [ebp+10h]

  v8 = 0;
  self->kind = PATH_TEMPLATE_KIND_HALFPIPE_FAMILY;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = arg2;
  v9 = (__int64)(arg3 * 3.1415927);
  v46 = v9;
  self->width_or_scale = 1.0;
  self->segment_count = v9 + 1;
  self->segment_count_f = (float)(v9 + 1);
  allocate_path_nodes(self);
  self->special_runtime_flag_9c = 0;
  if ( arg5 )
    self->primary_samples->center_x = 0.0;
  else
    self->primary_samples->center_x = (double)(int)self->width_cells * 0.5 - 4.0;
  self->primary_samples->rotation_scalar_98 = 0.0;
  self->primary_samples->rotation_scalar_94 = 0.0;
  self->primary_samples->special_scalar = 0.0;
  self->primary_samples->lateral_scale = 1.0;
  set_matrix_identity(&self->primary_samples->transform);
  self->primary_samples->transform.position.x = self->primary_samples->center_x;
  self->primary_samples->transform.position.y = 0.0;
  self->primary_samples->transform.position.z = 0.0;
  set_matrix_identity(&self->secondary_samples->transform);
  arg5a = 0;
  self->secondary_samples->transform.position.x = self->primary_samples->center_x;
  self->secondary_samples->transform.position.y = 0.49000001;
  self->secondary_samples->transform.position.z = 0.0;
  if ( v9 > 0 )
  {
    v10 = 1;
    do
    {
      self->primary_samples[v10].center_x = self->primary_samples->center_x;
      self->primary_samples[v10].rotation_scalar_98 = 0.0;
      self->primary_samples[v10].rotation_scalar_94 = 0.0;
      self->primary_samples[v10].special_scalar = 0.0;
      self->primary_samples[v10].lateral_scale = 1.0;
      v49 = (float)v46;
      arg2c = (double)arg5a * 6.2831855 / v49;
      set_matrix_identity(&self->primary_samples[v10].transform);
      self->primary_samples[v10].transform.position.x = self->primary_samples[v10].center_x;
      v44 = arg2c * 0.5;
      self->primary_samples[v10].transform.position.y = (1.0 - cosine(v44)) * 0.5 * arg3;
      v45 = arg2c * 1.5;
      self->primary_samples[v10].transform.position.z = (1.0 - cosine(v45)) * 0.5 * arg4 * 0.33333334 + 1.0;
      p_basis_up = &self->primary_samples[v10].transform.basis_up;
      p_basis_up->x = 1.0;
      p_basis_up->y = 0.0;
      p_basis_up->z = 0.0;
      primary_samples = self->primary_samples;
      p_x = &primary_samples[v10].transform.basis_forward.x;
      v57 = primary_samples[v10].transform.position.x - primary_samples[v10 - 1].transform.position.x;
      v60 = primary_samples[v10].transform.position.y - primary_samples[v10 - 1].transform.position.y;
      v14 = primary_samples[v10].transform.position.z - primary_samples[v10 - 1].transform.position.z;
      *p_x = v57;
      p_x[1] = v60;
      v63 = v14;
      p_x[2] = v63;
      normalize_vector((Vec3 *)&self->primary_samples[v10].transform.basis_forward);
      cross_vectors(
        (Vec3 *)&self->primary_samples[v10].transform.basis_up,
        (Vec3 *)&self->primary_samples[v10].transform.basis_forward,
        (Vec3 *)&self->primary_samples[v10]);
      qmemcpy(&self->secondary_samples[v10], &self->primary_samples[v10], 0x40u);
      v15 = self->primary_samples;
      v16 = v15[v10].transform.basis_up.x * 0.49000001;
      v67 = v15[v10].transform.basis_up.y * 0.49000001;
      v17 = v15[v10].transform.basis_up.z * 0.49000001;
      p_position = &self->secondary_samples[v10++].transform.position;
      v69 = v17;
      p_position->x = v16 + p_position->x;
      p_position->y = v67 + p_position->y;
      p_position->z = v69 + p_position->z;
      ++arg5a;
    }
    while ( arg5a < v46 );
    v8 = 0;
  }
  for ( i = 0; i < (signed int)(self->segment_count - 1); ++v8 )
  {
    v20 = &self->primary_samples[v8].transform.basis_right.x;
    v21 = v20[54] - v20[12];
    v20 += 32;
    v58 = v21;
    v61 = v20[23] - *(v20 - 19);
    v22 = v20[24] - *(v20 - 18);
    *v20 = v58;
    v20[1] = v61;
    v64 = v22;
    v20[2] = v64;
    self->primary_samples[v8].delta_length = normalize_vector(&self->primary_samples[v8].delta_dir_to_next);
    secondary_samples = self->secondary_samples;
    v24 = &secondary_samples[v8].delta_dir_to_next.x;
    v51 = secondary_samples[v8 + 1].transform.position.x - secondary_samples[v8].transform.position.x;
    v53 = secondary_samples[v8 + 1].transform.position.y - secondary_samples[v8].transform.position.y;
    v25 = secondary_samples[v8 + 1].transform.position.z - secondary_samples[v8].transform.position.z;
    *v24 = v51;
    v24[1] = v53;
    v55 = v25;
    v24[2] = v55;
    ++i;
    self->secondary_samples[v8].delta_length = normalize_vector(&self->secondary_samples[v8].delta_dir_to_next);
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
  arg2a = (uint32_t)vertices;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    v31 = 0;
    do
    {
      width_cells = self->width_cells;
      v33 = 0;
      arg5b = 0;
      for ( arg3a = width_cells; v33 <= width_cells; arg5b = v33 )
      {
        v34 = (double)arg5b - (double)arg3a * 0.5;
        v35 = &self->primary_samples[v31];
        if ( v29 == self->segment_count )
        {
          vertices = (Vec3 *)arg2a;
          v70 = v34 * v35[-1].transform.basis_right.x;
          v71 = v34 * v35[-1].transform.basis_right.y;
          v38 = v34 * v35[-1].transform.basis_right.z;
          v72 = v35[-1].transform.position.z + 1.0;
          v52 = v35[-1].transform.position.x + v70;
          v54 = v35[-1].transform.position.y + v71;
          v36 = (float *)(arg2a + 12 * (v33 + v29 * (width_cells + 1)));
          *v36 = v52;
          v56 = v72 + v38;
          v36[1] = v54;
          v37 = v56;
        }
        else
        {
          v66 = v34 * v35->transform.basis_right.x;
          v68 = v34 * v35->transform.basis_right.y;
          v59 = v66 + v35->transform.position.x;
          v62 = v68 + v35->transform.position.y;
          v65 = v34 * v35->transform.basis_right.z + v35->transform.position.z;
          v36 = &vertices[v33 + v29 * (width_cells + 1)].x;
          *v36 = v59;
          v36[1] = v62;
          v37 = v65;
        }
        v36[2] = v37;
        width_cells = self->width_cells;
        ++v33;
        arg3a = width_cells;
      }
      ++v29;
      ++v31;
    }
    while ( v29 <= (signed int)self->segment_count );
  }
  for ( j = 0; j < (signed int)self->segment_count; ++j )
  {
    v40 = 0;
    arg5c = 0;
    if ( (int)self->width_cells > 0 )
    {
      arg3b = (double)(j % 8) * 0.125;
      arg4a = (double)(j % 8 + 1) * 0.125;
      do
      {
        v41 = 0;
        v50 = v40 + 1;
        v47 = 0;
        arg5d = (double)arg5c * 0.125;
        arg2b = (double)(v40 + 1) * 0.125;
        while ( 1 )
        {
          v42 = &facequads[2 * v40 + 2 * j * self->width_cells + v41];
          v42->flags = 0;
          if ( v41 )
          {
            v42->vertex_index_a = j * (LOWORD(self->width_cells) + 1) + v40 + 1;
            v42->vertex_index_b = v40 + j * (LOWORD(self->width_cells) + 1);
            v42->vertex_index_c = v40 + (j + 1) * (LOWORD(self->width_cells) + 1);
            v42->vertex_index_d = (j + 1) * (LOWORD(self->width_cells) + 1) + v40 + 1;
            v42->texture_ref = get_or_create_texture_ref((TextureRefList *)dword_4B7790, texture_b, 0, 0);
            v42->u0 = arg2b;
            v42->v0 = arg3b;
            v42->u1 = arg5d;
            v42->v1 = arg3b;
            v42->u2 = arg5d;
            v42->v2 = arg4a;
            v42->u3 = arg2b;
          }
          else
          {
            v42->vertex_index_a = v40 + j * (LOWORD(self->width_cells) + 1);
            v42->vertex_index_b = j * (LOWORD(self->width_cells) + 1) + v40 + 1;
            v42->vertex_index_c = (j + 1) * (LOWORD(self->width_cells) + 1) + v40 + 1;
            v42->vertex_index_d = v40 + (j + 1) * (LOWORD(self->width_cells) + 1);
            v42->texture_ref = get_or_create_texture_ref((TextureRefList *)dword_4B7790, texture_a, 0, 0);
            v42->u0 = arg5d;
            v42->v0 = arg3b;
            v42->u1 = arg2b;
            v42->v1 = arg3b;
            v42->u2 = arg2b;
            v42->v2 = arg4a;
            v42->u3 = arg5d;
          }
          v42->v3 = arg4a;
          if ( ++v47 >= 2 )
            break;
          v41 = v47;
        }
        ++v40;
        arg5c = v50;
      }
      while ( v50 < (signed int)self->width_cells );
    }
  }
  return finalize_path_template_record(self);
}

