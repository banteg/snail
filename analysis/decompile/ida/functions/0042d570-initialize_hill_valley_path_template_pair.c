/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_hill_valley_path_template_pair @ 0x42d570 */
/* selector: initialize_hill_valley_path_template_pair */

int32_t __thiscall initialize_hill_valley_path_template_pair(
        PathTemplate *self,
        int32_t arg2,
        float arg3,
        float arg4,
        char arg5,
        char *texture_a,
        char *texture_b)
{
  signed int v8; // ebx
  __int64 v9; // rax
  int v10; // edi
  bool v11; // zf
  int v12; // edi
  double v13; // st7
  int v14; // ebp
  int v15; // edi
  PathTemplateSample *v16; // eax
  PathTemplateSample *primary_samples; // edx
  float *p_x; // eax
  double v19; // st7
  PathTemplateSample *v20; // ecx
  PathTemplateSample *v21; // eax
  double v22; // st7
  double v23; // st7
  signed int v24; // ebp
  int v25; // edi
  float *v26; // eax
  double v27; // st7
  double v28; // st7
  PathTemplateSample *secondary_samples; // ecx
  float *v30; // eax
  double v31; // st7
  Vec3 *p_delta_dir_to_next; // edx
  Vec3 *v33; // ecx
  PathTemplateStripMesh *strip_mesh; // eax
  signed int v35; // edx
  Vec3 *vertices; // ebp
  signed int width_cells; // ecx
  signed int v38; // edi
  double v39; // st7
  float *v40; // eax
  float *v41; // eax
  float v42; // ecx
  double v43; // st7
  int v44; // edi
  int v45; // ecx
  ObjectFaceQuad *v46; // ebp
  int v48; // [esp+4h] [ebp-48h]
  ObjectFaceQuad *facequads; // [esp+8h] [ebp-44h]
  float v50; // [esp+Ch] [ebp-40h]
  signed int v51; // [esp+Ch] [ebp-40h]
  float v52; // [esp+10h] [ebp-3Ch]
  float v53; // [esp+14h] [ebp-38h]
  float v54; // [esp+1Ch] [ebp-30h]
  float v55; // [esp+1Ch] [ebp-30h]
  float v56; // [esp+20h] [ebp-2Ch]
  float v57; // [esp+20h] [ebp-2Ch]
  float v58; // [esp+24h] [ebp-28h]
  float v59; // [esp+28h] [ebp-24h]
  float v60; // [esp+28h] [ebp-24h]
  float v61; // [esp+2Ch] [ebp-20h]
  float v62; // [esp+2Ch] [ebp-20h]
  float v63; // [esp+30h] [ebp-1Ch]
  float v64; // [esp+30h] [ebp-1Ch]
  float v65; // [esp+34h] [ebp-18h]
  float v66; // [esp+34h] [ebp-18h]
  float v67; // [esp+34h] [ebp-18h]
  float v68; // [esp+38h] [ebp-14h]
  float v69; // [esp+38h] [ebp-14h]
  float v70; // [esp+38h] [ebp-14h]
  float v71; // [esp+3Ch] [ebp-10h]
  float v72; // [esp+3Ch] [ebp-10h]
  float v73; // [esp+3Ch] [ebp-10h]
  float v74; // [esp+48h] [ebp-4h]
  int32_t arg2a; // [esp+50h] [ebp+4h]
  int32_t arg2b; // [esp+50h] [ebp+4h]
  float arg2c; // [esp+50h] [ebp+4h]
  int arg3a; // [esp+54h] [ebp+8h]
  float arg3b; // [esp+54h] [ebp+8h]
  float arg4b; // [esp+58h] [ebp+Ch]
  float arg4a; // [esp+58h] [ebp+Ch]
  int arg5a; // [esp+5Ch] [ebp+10h]
  float arg5f; // [esp+5Ch] [ebp+10h]
  int arg5b; // [esp+5Ch] [ebp+10h]
  float arg5g; // [esp+5Ch] [ebp+10h]
  int arg5c; // [esp+5Ch] [ebp+10h]
  int arg5d; // [esp+5Ch] [ebp+10h]
  float arg5e; // [esp+5Ch] [ebp+10h]

  v8 = 0;
  self->kind = PATH_TEMPLATE_KIND_HALFPIPE_FAMILY;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = arg2;
  v9 = (__int64)arg4;
  v10 = v9 + 1;
  arg2a = v9;
  self->width_or_scale = 1.0;
  self->segment_count = v9 + 2;
  self->segment_count_f = (float)(v9 + 2);
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
  self->secondary_samples->transform.position.x = self->primary_samples->center_x;
  self->secondary_samples->transform.position.y = 0.49000001;
  v11 = arg5 == 0;
  self->secondary_samples->transform.position.z = 0.0;
  arg5a = v10;
  v12 = v10;
  if ( v11 )
    self->primary_samples[v12].center_x = (double)(int)self->width_cells * 0.5 - 4.0;
  else
    self->primary_samples[v12].center_x = 0.0;
  self->primary_samples[v12].rotation_scalar_98 = 0.0;
  self->primary_samples[v12].rotation_scalar_94 = 0.0;
  self->primary_samples[v12].special_scalar = 0.0;
  self->primary_samples[v12].lateral_scale = 1.0;
  set_matrix_identity(&self->primary_samples[v12].transform);
  self->primary_samples[v12].transform.position.x = self->primary_samples[v12].center_x;
  arg5f = (float)arg5a;
  self->primary_samples[v12].transform.position.y = 0.0;
  self->primary_samples[v12].transform.position.z = arg5f;
  set_matrix_identity(&self->secondary_samples[v12].transform);
  v13 = arg5f;
  v14 = 0;
  self->secondary_samples[v12].transform.position.x = self->primary_samples[v12].center_x;
  arg5b = 0;
  self->secondary_samples[v12].transform.position.y = 0.49000001;
  self->secondary_samples[v12].transform.position.z = v13;
  if ( arg2a > 0 )
  {
    v15 = 1;
    do
    {
      self->primary_samples[v15].center_x = self->primary_samples->center_x;
      self->primary_samples[v15].rotation_scalar_98 = 0.0;
      self->primary_samples[v15].rotation_scalar_94 = 0.0;
      self->primary_samples[v15].special_scalar = 0.0;
      self->primary_samples[v15].lateral_scale = 1.0;
      arg4b = (float)arg2a;
      arg5g = (double)arg5b * 6.2831855 / arg4b;
      set_matrix_identity(&self->primary_samples[v15].transform);
      self->primary_samples[v15].transform.position.x = self->primary_samples[v15].center_x;
      ++v14;
      self->primary_samples[v15].transform.position.y = (1.0 - cosine(arg5g)) * 0.5 * arg3;
      v50 = (float)v14;
      self->primary_samples[v15].transform.position.z = v50;
      set_matrix_identity(&self->secondary_samples[v15].transform);
      self->secondary_samples[v15].transform.position.x = self->primary_samples[v15].center_x;
      self->secondary_samples[v15].transform.position.y = (1.0 - cosine(arg5g)) * 0.5 * arg3 + 0.49000001;
      self->secondary_samples[v15].transform.position.z = v50;
      if ( v15 <= 1 )
      {
        set_matrix_rotation_identity(&self->primary_samples[v15 - 1].transform);
        set_matrix_rotation_identity(&self->secondary_samples[v15 - 1].transform);
      }
      else
      {
        v16 = &self->primary_samples[v15 - 1];
        v16->transform.basis_right.x = 1.0;
        v16->transform.basis_right.y = 0.0;
        v16->transform.basis_right.z = 0.0;
        primary_samples = self->primary_samples;
        p_x = &primary_samples[v15 - 1].transform.basis_forward.x;
        v54 = primary_samples[v15].transform.position.x - primary_samples[v15 - 1].transform.position.x;
        v56 = p_x[47] - p_x[5];
        v19 = p_x[48] - p_x[6];
        *p_x = v54;
        p_x[1] = v56;
        v58 = v19;
        p_x[2] = v58;
        normalize_vector((Vec3 *)&self->primary_samples[v15 - 1].transform.basis_forward);
        cross_vectors(
          (Vec3 *)&self->primary_samples[v15 - 1].transform.basis_up,
          (Vec3 *)&self->primary_samples[v15 - 1].transform.basis_forward,
          (Vec3 *)&self->primary_samples[v15 - 1]);
        v20 = &self->secondary_samples[v15 - 1];
        v20->transform.basis_right.x = 1.0;
        v20->transform.basis_right.y = 0.0;
        v20->transform.basis_right.z = 0.0;
        v21 = &self->secondary_samples[v15];
        v22 = v21->transform.position.x - v21[-1].transform.position.x;
        v21 = (PathTemplateSample *)((char *)v21 - 136);
        v65 = v22;
        v68 = v21[1].transform.basis_up.y - v21->transform.basis_up.y;
        v23 = v21[1].transform.basis_up.z - v21->transform.basis_up.z;
        v21->transform.basis_right.x = v65;
        v21->transform.basis_right.y = v68;
        v71 = v23;
        v21->transform.basis_right.z = v71;
        normalize_vector((Vec3 *)&self->secondary_samples[v15 - 1].transform.basis_forward);
        cross_vectors(
          (Vec3 *)&self->secondary_samples[v15 - 1].transform.basis_up,
          (Vec3 *)&self->secondary_samples[v15 - 1].transform.basis_forward,
          (Vec3 *)&self->secondary_samples[v15 - 1]);
      }
      ++v15;
      arg5b = v14;
    }
    while ( v14 < arg2a );
  }
  v24 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v25 = 0;
    do
    {
      v26 = &self->primary_samples[v25].transform.basis_right.x;
      v27 = v26[54] - v26[12];
      v26 += 32;
      v66 = v27;
      v69 = v26[23] - *(v26 - 19);
      v28 = v26[24] - *(v26 - 18);
      *v26 = v66;
      v26[1] = v69;
      v72 = v28;
      v26[2] = v72;
      self->primary_samples[v25].delta_length = normalize_vector(&self->primary_samples[v25].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      v30 = &secondary_samples[v25].delta_dir_to_next.x;
      v59 = secondary_samples[v25 + 1].transform.position.x - secondary_samples[v25].transform.position.x;
      v61 = secondary_samples[v25 + 1].transform.position.y - secondary_samples[v25].transform.position.y;
      v31 = secondary_samples[v25 + 1].transform.position.z - secondary_samples[v25].transform.position.z;
      *v30 = v59;
      v30[1] = v61;
      v63 = v31;
      v30[2] = v63;
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
  request_object_vertices(self->strip_mesh, (self->segment_count + 1) * (self->width_cells + 1));
  request_object_facequads(self->strip_mesh, 2 * self->segment_count * self->width_cells);
  strip_mesh = self->strip_mesh;
  v35 = 0;
  vertices = strip_mesh->vertices;
  arg2b = (int32_t)vertices;
  facequads = strip_mesh->facequads;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    do
    {
      width_cells = self->width_cells;
      v38 = 0;
      arg5c = 0;
      for ( arg3a = width_cells; v38 <= width_cells; arg5c = v38 )
      {
        v39 = (double)arg5c - (double)arg3a * 0.5;
        v40 = (float *)((char *)&self->primary_samples->transform.basis_right.x + v8);
        if ( v35 == self->segment_count )
        {
          vertices = (Vec3 *)arg2b;
          v52 = v39 * *(v40 - 42);
          v53 = v39 * *(v40 - 41);
          v43 = v39 * *(v40 - 40);
          v74 = *(v40 - 28) + 1.0;
          v60 = *(v40 - 30) + v52;
          v62 = *(v40 - 29) + v53;
          v41 = (float *)(arg2b + 12 * (v38 + v35 * (width_cells + 1)));
          *v41 = v60;
          v64 = v74 + v43;
          v41[1] = v62;
          v42 = v64;
        }
        else
        {
          v55 = v39 * *v40;
          v57 = v39 * v40[1];
          v67 = v55 + v40[12];
          v70 = v57 + v40[13];
          v73 = v39 * v40[2] + v40[14];
          v41 = &vertices[v38 + v35 * (width_cells + 1)].x;
          *v41 = v67;
          v41[1] = v70;
          v42 = v73;
        }
        v41[2] = v42;
        width_cells = self->width_cells;
        ++v38;
        arg3a = width_cells;
      }
      ++v35;
      v8 += 168;
    }
    while ( v35 <= (signed int)self->segment_count );
    v8 = 0;
  }
  if ( (int)self->segment_count > 0 )
  {
    do
    {
      v44 = 0;
      arg5d = 0;
      if ( (int)self->width_cells > 0 )
      {
        arg3b = (double)(v8 % 8) * 0.125;
        arg4a = (double)(v8 % 8 + 1) * 0.125;
        do
        {
          v45 = 0;
          v51 = v44 + 1;
          v48 = 0;
          arg5e = (double)arg5d * 0.125;
          arg2c = (double)(v44 + 1) * 0.125;
          while ( 1 )
          {
            v46 = &facequads[2 * v44 + 2 * v8 * self->width_cells + v45];
            v46->flags = 0;
            if ( v45 )
            {
              v46->vertex_index_a = v8 * (LOWORD(self->width_cells) + 1) + v44 + 1;
              v46->vertex_index_b = v44 + v8 * (LOWORD(self->width_cells) + 1);
              v46->vertex_index_c = v44 + (v8 + 1) * (LOWORD(self->width_cells) + 1);
              v46->vertex_index_d = (v8 + 1) * (LOWORD(self->width_cells) + 1) + v44 + 1;
              v46->texture_ref = get_or_create_texture_ref((TextureRefList *)dword_4B7790, texture_b, 0, 0);
              v46->u0 = arg2c;
              v46->v0 = arg3b;
              v46->u1 = arg5e;
              v46->v1 = arg3b;
              v46->u2 = arg5e;
              v46->v2 = arg4a;
              v46->u3 = arg2c;
            }
            else
            {
              v46->vertex_index_a = v44 + v8 * (LOWORD(self->width_cells) + 1);
              v46->vertex_index_b = v8 * (LOWORD(self->width_cells) + 1) + v44 + 1;
              v46->vertex_index_c = (v8 + 1) * (LOWORD(self->width_cells) + 1) + v44 + 1;
              v46->vertex_index_d = v44 + (v8 + 1) * (LOWORD(self->width_cells) + 1);
              v46->texture_ref = get_or_create_texture_ref((TextureRefList *)dword_4B7790, texture_a, 0, 0);
              v46->u0 = arg5e;
              v46->v0 = arg3b;
              v46->u1 = arg2c;
              v46->v1 = arg3b;
              v46->u2 = arg2c;
              v46->v2 = arg4a;
              v46->u3 = arg5e;
            }
            v46->v3 = arg4a;
            if ( ++v48 >= 2 )
              break;
            v45 = v48;
          }
          ++v44;
          arg5d = v51;
        }
        while ( v51 < (signed int)self->width_cells );
      }
      ++v8;
    }
    while ( v8 < (signed int)self->segment_count );
  }
  return finalize_path_template_record(self);
}

