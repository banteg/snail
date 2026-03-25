/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_detour_path_template_pair @ 0x42e720 */
/* selector: initialize_detour_path_template_pair */

int32_t __thiscall initialize_detour_path_template_pair(
        PathTemplate *self,
        int32_t arg2,
        char *texture_a,
        char *texture_b)
{
  signed int v5; // ebx
  double width_cells; // st7
  PathTemplateSample *primary_samples; // ecx
  int i; // edi
  double v9; // st7
  PathTemplateSample *v10; // ebp
  Vec4 *p_basis_up; // eax
  PathTemplateSample *v12; // edx
  float *p_x; // eax
  double v14; // st7
  PathTemplateSample *v15; // ebp
  Vec4 *v16; // eax
  PathTemplateSample *secondary_samples; // edx
  float *v18; // eax
  double v19; // st7
  signed int v20; // ebp
  int v21; // edi
  PathTemplateSample *v22; // ecx
  float *v23; // eax
  double v24; // st7
  PathTemplateSample *v25; // edx
  float *v26; // eax
  double v27; // st7
  Vec3 *p_delta_dir_to_next; // ecx
  Vec3 *v29; // eax
  PathTemplateStripMesh *strip_mesh; // eax
  Vec3 *vertices; // ebp
  signed int v32; // edx
  signed int v33; // ecx
  int32_t v34; // edi
  double v35; // st7
  float *v36; // eax
  float *v37; // eax
  float v38; // ecx
  double v39; // st7
  int v40; // edi
  int v41; // ecx
  ObjectFaceQuad *v42; // ebp
  float v44; // [esp+0h] [ebp-68h]
  float v45; // [esp+0h] [ebp-68h]
  float v46; // [esp+0h] [ebp-68h]
  float v47; // [esp+14h] [ebp-54h]
  float v48; // [esp+18h] [ebp-50h]
  int j; // [esp+1Ch] [ebp-4Ch]
  float v50; // [esp+1Ch] [ebp-4Ch]
  float v51; // [esp+20h] [ebp-48h]
  int v52; // [esp+20h] [ebp-48h]
  ObjectFaceQuad *facequads; // [esp+24h] [ebp-44h]
  float v54; // [esp+28h] [ebp-40h]
  Vec3 *v55; // [esp+28h] [ebp-40h]
  signed int v56; // [esp+28h] [ebp-40h]
  float v57; // [esp+2Ch] [ebp-3Ch]
  float v58; // [esp+30h] [ebp-38h]
  float v59; // [esp+38h] [ebp-30h]
  float v60; // [esp+38h] [ebp-30h]
  float v61; // [esp+3Ch] [ebp-2Ch]
  float v62; // [esp+3Ch] [ebp-2Ch]
  float v63; // [esp+40h] [ebp-28h]
  float v64; // [esp+44h] [ebp-24h]
  float v65; // [esp+44h] [ebp-24h]
  float v66; // [esp+48h] [ebp-20h]
  float v67; // [esp+48h] [ebp-20h]
  float v68; // [esp+4Ch] [ebp-1Ch]
  float v69; // [esp+4Ch] [ebp-1Ch]
  float v70; // [esp+50h] [ebp-18h]
  float v71; // [esp+50h] [ebp-18h]
  float v72; // [esp+50h] [ebp-18h]
  float v73; // [esp+54h] [ebp-14h]
  float v74; // [esp+54h] [ebp-14h]
  float v75; // [esp+54h] [ebp-14h]
  float v76; // [esp+58h] [ebp-10h]
  float v77; // [esp+58h] [ebp-10h]
  float v78; // [esp+58h] [ebp-10h]
  float v79; // [esp+64h] [ebp-4h]
  int32_t arg2a; // [esp+6Ch] [ebp+4h]
  int32_t arg2b; // [esp+6Ch] [ebp+4h]
  int32_t arg2c; // [esp+6Ch] [ebp+4h]
  float arg2d; // [esp+6Ch] [ebp+4h]

  v5 = 0;
  self->kind = PATH_TEMPLATE_KIND_DETOUR;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = arg2;
  self->width_or_scale = 1.0;
  self->segment_count = 22;
  self->segment_count_f = 22.0;
  allocate_path_nodes(self);
  width_cells = (double)(int)self->width_cells;
  primary_samples = self->primary_samples;
  self->special_runtime_flag_9c = 0;
  primary_samples->center_x = width_cells * 0.5 - 4.0;
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
  self->secondary_samples->transform.position.z = 0.0;
  self->primary_samples[21].center_x = 4.0 - (double)(int)self->width_cells * 0.5;
  self->primary_samples[21].rotation_scalar_98 = 0.0;
  self->primary_samples[21].rotation_scalar_94 = 0.0;
  self->primary_samples[21].special_scalar = 0.0;
  self->primary_samples[21].lateral_scale = 1.0;
  set_matrix_identity(&self->primary_samples[21].transform);
  self->primary_samples[21].transform.position.x = self->primary_samples[21].center_x;
  self->primary_samples[21].transform.position.y = 0.0;
  self->primary_samples[21].transform.position.z = 21.0;
  set_matrix_identity(&self->secondary_samples[21].transform);
  self->secondary_samples[21].transform.position.x = self->primary_samples[21].center_x;
  arg2a = 0;
  self->secondary_samples[21].transform.position.y = 0.49000001;
  self->secondary_samples[21].transform.position.z = 21.0;
  for ( i = 1; i < 21; ++i )
  {
    v9 = (double)arg2a;
    v10 = self->primary_samples;
    v51 = v9 * 0.31415927;
    v44 = v9 * 0.47123891;
    v10[i].center_x = cosine(v44) * v10->center_x;
    self->primary_samples[i].rotation_scalar_98 = 0.0;
    self->primary_samples[i].rotation_scalar_94 = 0.0;
    self->primary_samples[i].special_scalar = 0.0;
    self->primary_samples[i].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[i].transform);
    self->primary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    ++arg2a;
    self->primary_samples[i].transform.position.y = 0.0;
    v54 = (float)arg2a;
    self->primary_samples[i].transform.position.z = v54;
    set_matrix_identity(&self->secondary_samples[i].transform);
    self->secondary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    self->secondary_samples[i].transform.position.y = self->primary_samples[i].transform.position.y + 0.49000001;
    self->secondary_samples[i].transform.position.z = v54;
    if ( i <= 1 )
    {
      set_matrix_rotation_identity(&self->primary_samples[i - 1].transform);
      set_matrix_rotation_identity(&self->secondary_samples[i - 1].transform);
    }
    else
    {
      p_basis_up = &self->primary_samples[i - 1].transform.basis_up;
      p_basis_up->x = 0.0;
      p_basis_up->y = 1.0;
      p_basis_up->z = 0.0;
      v12 = self->primary_samples;
      p_x = &v12[i - 1].transform.basis_forward.x;
      v59 = v12[i].transform.position.x - v12[i - 1].transform.position.x;
      v61 = p_x[47] - p_x[5];
      v14 = p_x[48] - p_x[6];
      *p_x = v59;
      p_x[1] = v61;
      v63 = v14;
      p_x[2] = v63;
      normalize_vector((Vec3 *)&self->primary_samples[i - 1].transform.basis_forward);
      cross_vectors(
        (Vec3 *)&self->primary_samples[i - 1],
        (Vec3 *)&self->primary_samples[i - 1].transform.basis_up,
        (Vec3 *)&self->primary_samples[i - 1].transform.basis_forward);
      v15 = &self->primary_samples[i];
      v45 = (1.0 - cosine(v51)) * 0.5 * v15[-1].center_x * 0.39269909;
      rotate_matrix_world_z(&v15[-1].transform, v45);
      v16 = &self->secondary_samples[i - 1].transform.basis_up;
      v16->x = 0.0;
      v16->y = 1.0;
      v16->z = 0.0;
      secondary_samples = self->secondary_samples;
      v18 = &secondary_samples[i - 1].transform.basis_forward.x;
      v70 = secondary_samples[i].transform.position.x - secondary_samples[i - 1].transform.position.x;
      v73 = v18[47] - v18[5];
      v19 = v18[48] - v18[6];
      *v18 = v70;
      v76 = v19;
      v18[1] = v73;
      v18[2] = v76;
      normalize_vector((Vec3 *)&self->secondary_samples[i - 1].transform.basis_forward);
      cross_vectors(
        (Vec3 *)&self->secondary_samples[i - 1],
        (Vec3 *)&self->secondary_samples[i - 1].transform.basis_up,
        (Vec3 *)&self->secondary_samples[i - 1].transform.basis_forward);
      v46 = (1.0 - cosine(v51)) * 0.5 * self->primary_samples[i - 1].center_x * 0.39269909;
      rotate_matrix_world_z(&self->secondary_samples[i - 1].transform, v46);
    }
  }
  v20 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v21 = 0;
    do
    {
      v22 = self->primary_samples;
      v23 = &v22[v21].delta_dir_to_next.x;
      v71 = v22[v21 + 1].transform.position.x - v22[v21].transform.position.x;
      v74 = v22[v21 + 1].transform.position.y - v22[v21].transform.position.y;
      v24 = v22[v21 + 1].transform.position.z - v22[v21].transform.position.z;
      *v23 = v71;
      v23[1] = v74;
      v77 = v24;
      v23[2] = v77;
      self->primary_samples[v21].delta_length = normalize_vector(&self->primary_samples[v21].delta_dir_to_next);
      v25 = self->secondary_samples;
      v26 = &v25[v21].delta_dir_to_next.x;
      v64 = v25[v21 + 1].transform.position.x - v25[v21].transform.position.x;
      v66 = v25[v21 + 1].transform.position.y - v25[v21].transform.position.y;
      v27 = v25[v21 + 1].transform.position.z - v25[v21].transform.position.z;
      *v26 = v64;
      v26[1] = v66;
      v68 = v27;
      v26[2] = v68;
      ++v20;
      self->secondary_samples[v21].delta_length = normalize_vector(&self->secondary_samples[v21].delta_dir_to_next);
      ++v21;
    }
    while ( v20 < (signed int)(self->segment_count - 1) );
  }
  p_delta_dir_to_next = &self->primary_samples[self->segment_count - 1].delta_dir_to_next;
  p_delta_dir_to_next->x = 0.0;
  p_delta_dir_to_next->y = 0.0;
  p_delta_dir_to_next->z = 1.0;
  self->primary_samples[self->segment_count - 1].delta_length = 1.0;
  v29 = &self->secondary_samples[self->segment_count - 1].delta_dir_to_next;
  v29->x = 0.0;
  v29->y = 0.0;
  v29->z = 1.0;
  self->secondary_samples[self->segment_count - 1].delta_length = 1.0;
  request_object_vertices(self->strip_mesh, (self->segment_count + 1) * (self->width_cells + 1));
  request_object_facequads(self->strip_mesh, 2 * self->segment_count * self->width_cells);
  strip_mesh = self->strip_mesh;
  vertices = strip_mesh->vertices;
  facequads = strip_mesh->facequads;
  v32 = 0;
  v55 = vertices;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    do
    {
      v33 = self->width_cells;
      v34 = 0;
      arg2b = 0;
      for ( j = v33; v34 <= v33; arg2b = v34 )
      {
        v35 = (double)arg2b - (double)j * 0.5;
        v36 = (float *)((char *)&self->primary_samples->transform.basis_right.x + v5);
        if ( v32 == self->segment_count )
        {
          vertices = v55;
          v57 = v35 * *(v36 - 42);
          v58 = v35 * *(v36 - 41);
          v39 = v35 * *(v36 - 40);
          v79 = *(v36 - 28) + 1.0;
          v65 = *(v36 - 30) + v57;
          v67 = *(v36 - 29) + v58;
          v37 = &v55[v34 + v32 * (v33 + 1)].x;
          *v37 = v65;
          v69 = v79 + v39;
          v37[1] = v67;
          v38 = v69;
        }
        else
        {
          v60 = v35 * *v36;
          v62 = v35 * v36[1];
          v72 = v60 + v36[12];
          v75 = v62 + v36[13];
          v78 = v35 * v36[2] + v36[14];
          v37 = &vertices[v34 + v32 * (v33 + 1)].x;
          *v37 = v72;
          v37[1] = v75;
          v38 = v78;
        }
        v37[2] = v38;
        v33 = self->width_cells;
        ++v34;
        j = v33;
      }
      ++v32;
      v5 += 168;
    }
    while ( v32 <= (signed int)self->segment_count );
    v5 = 0;
  }
  if ( (int)self->segment_count > 0 )
  {
    do
    {
      v40 = 0;
      arg2c = 0;
      if ( (int)self->width_cells > 0 )
      {
        v47 = (double)(v5 % 8) * 0.125;
        v50 = (double)(v5 % 8 + 1) * 0.125;
        do
        {
          v41 = 0;
          v56 = v40 + 1;
          v52 = 0;
          arg2d = (double)arg2c * 0.125;
          v48 = (double)(v40 + 1) * 0.125;
          while ( 1 )
          {
            v42 = &facequads[2 * v40 + 2 * v5 * self->width_cells + v41];
            v42->flags = 0;
            if ( v41 )
            {
              v42->vertex_index_a = v5 * (LOWORD(self->width_cells) + 1) + v40 + 1;
              v42->vertex_index_b = v40 + v5 * (LOWORD(self->width_cells) + 1);
              v42->vertex_index_c = v40 + (v5 + 1) * (LOWORD(self->width_cells) + 1);
              v42->vertex_index_d = (v5 + 1) * (LOWORD(self->width_cells) + 1) + v40 + 1;
              v42->texture_ref = get_or_create_texture_ref((TextureRefList *)dword_4B7790, texture_b, 0, 0);
              v42->u0 = v48;
              v42->v0 = v47;
              v42->u1 = arg2d;
              v42->v1 = v47;
              v42->u2 = arg2d;
              v42->v2 = v50;
              v42->u3 = v48;
            }
            else
            {
              v42->vertex_index_a = v40 + v5 * (LOWORD(self->width_cells) + 1);
              v42->vertex_index_b = v5 * (LOWORD(self->width_cells) + 1) + v40 + 1;
              v42->vertex_index_c = (v5 + 1) * (LOWORD(self->width_cells) + 1) + v40 + 1;
              v42->vertex_index_d = v40 + (v5 + 1) * (LOWORD(self->width_cells) + 1);
              v42->texture_ref = get_or_create_texture_ref((TextureRefList *)dword_4B7790, texture_a, 0, 0);
              v42->u0 = arg2d;
              v42->v0 = v47;
              v42->u1 = v48;
              v42->v1 = v47;
              v42->u2 = v48;
              v42->v2 = v50;
              v42->u3 = arg2d;
            }
            v42->v3 = v50;
            if ( ++v52 >= 2 )
              break;
            v41 = v52;
          }
          ++v40;
          arg2c = v56;
        }
        while ( v56 < (signed int)self->width_cells );
      }
      ++v5;
    }
    while ( v5 < (signed int)self->segment_count );
  }
  return finalize_path_template_record(self);
}

