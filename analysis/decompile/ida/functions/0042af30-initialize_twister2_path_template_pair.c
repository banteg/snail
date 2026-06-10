/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_twister2_path_template_pair @ 0x42af30 */
/* selector: initialize_twister2_path_template_pair */

int32_t __thiscall initialize_twister2_path_template_pair(
        PathTemplate *self,
        float arg2,
        int32_t arg3,
        char arg4,
        char *texture_a,
        char *texture_b)
{
  signed int v7; // ebx
  double width_cells; // st7
  PathTemplateSample *primary_samples; // ecx
  int v10; // ebp
  int i; // edi
  double v12; // st7
  Vec4 *p_basis_up; // edx
  PathTemplateSample *v14; // ecx
  float *p_x; // eax
  double v16; // st7
  Vec4 *v17; // edx
  PathTemplateSample *secondary_samples; // ecx
  float *v19; // eax
  double v20; // st7
  signed int v21; // ebp
  int v22; // edi
  PathTemplateSample *v23; // ecx
  float *v24; // eax
  double v25; // st7
  PathTemplateSample *v26; // edx
  float *v27; // eax
  double v28; // st7
  Vec3 *p_delta_dir_to_next; // ecx
  Vec3 *v30; // eax
  PathTemplateStripMesh *strip_mesh; // eax
  Vec3 *vertices; // ebp
  signed int v33; // edx
  signed int v34; // ecx
  signed int v35; // edi
  double v36; // st7
  float *v37; // eax
  float *v38; // eax
  float v39; // ecx
  double v40; // st7
  int v41; // edi
  int v42; // ecx
  ObjectFaceQuad *v43; // ebp
  float v45; // [esp+10h] [ebp-4Ch]
  int v46; // [esp+14h] [ebp-48h]
  ObjectFaceQuad *facequads; // [esp+18h] [ebp-44h]
  float v48; // [esp+1Ch] [ebp-40h]
  signed int v49; // [esp+1Ch] [ebp-40h]
  float v50; // [esp+20h] [ebp-3Ch]
  float v51; // [esp+24h] [ebp-38h]
  float v52; // [esp+2Ch] [ebp-30h]
  float v53; // [esp+2Ch] [ebp-30h]
  float v54; // [esp+30h] [ebp-2Ch]
  float v55; // [esp+30h] [ebp-2Ch]
  float v56; // [esp+34h] [ebp-28h]
  float v57; // [esp+38h] [ebp-24h]
  float v58; // [esp+38h] [ebp-24h]
  float v59; // [esp+3Ch] [ebp-20h]
  float v60; // [esp+3Ch] [ebp-20h]
  float v61; // [esp+40h] [ebp-1Ch]
  float v62; // [esp+40h] [ebp-1Ch]
  float v63; // [esp+44h] [ebp-18h]
  float v64; // [esp+44h] [ebp-18h]
  float v65; // [esp+44h] [ebp-18h]
  float v66; // [esp+48h] [ebp-14h]
  float v67; // [esp+48h] [ebp-14h]
  float v68; // [esp+48h] [ebp-14h]
  float v69; // [esp+4Ch] [ebp-10h]
  float v70; // [esp+4Ch] [ebp-10h]
  float v71; // [esp+4Ch] [ebp-10h]
  float v72; // [esp+58h] [ebp-4h]
  Vec3 *arg2a; // [esp+60h] [ebp+4h]
  float arg2b; // [esp+60h] [ebp+4h]
  int32_t arg3a; // [esp+64h] [ebp+8h]
  float arg3b; // [esp+64h] [ebp+8h]
  float arg3e; // [esp+64h] [ebp+8h]
  float arg3f; // [esp+64h] [ebp+8h]
  int32_t arg3c; // [esp+64h] [ebp+8h]
  float arg3d; // [esp+64h] [ebp+8h]
  int arg4a; // [esp+68h] [ebp+Ch]
  int arg4b; // [esp+68h] [ebp+Ch]
  float arg4c; // [esp+68h] [ebp+Ch]

  v7 = 0;
  self->kind = PATH_TEMPLATE_KIND_TWISTER2;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = arg3;
  self->width_or_scale = 1.0;
  self->segment_count = 52;
  self->segment_count_f = 52.0;
  allocate_path_template_samples(self);
  width_cells = (double)(int)self->width_cells;
  primary_samples = self->primary_samples;
  self->special_runtime_flag_9c = 0;
  primary_samples->center_x = width_cells * 0.5 - 4.0;
  if ( !arg4 )
    self->primary_samples->center_x = self->primary_samples->center_x * -1.0;
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
  self->primary_samples[51].center_x = (double)(int)self->width_cells * 0.5 - 4.0;
  if ( !arg4 )
    self->primary_samples[51].center_x = self->primary_samples[51].center_x * -1.0;
  self->primary_samples[51].rotation_scalar_98 = 0.0;
  self->primary_samples[51].rotation_scalar_94 = 0.0;
  self->primary_samples[51].special_scalar = 0.0;
  self->primary_samples[51].lateral_scale = 1.0;
  set_matrix_identity(&self->primary_samples[51].transform);
  self->primary_samples[51].transform.position.x = self->primary_samples[51].center_x;
  self->primary_samples[51].transform.position.y = 0.0;
  self->primary_samples[51].transform.position.z = 51.0;
  set_matrix_identity(&self->secondary_samples[51].transform);
  self->secondary_samples[51].transform.position.x = self->primary_samples[51].center_x;
  self->secondary_samples[51].transform.position.y = 0.49000001;
  v10 = 0;
  self->secondary_samples[51].transform.position.z = 51.0;
  arg3a = 0;
  for ( i = 1; i < 51; ++i )
  {
    v12 = (double)arg3a * 0.25132743;
    arg3b = v12;
    v48 = v12 * 0.5;
    if ( !arg4 )
      arg3b = arg3b + 3.1415927;
    self->primary_samples[i].center_x = 2.5 - (cosine(arg3b) + 1.0) * 0.5 * 5.0;
    self->primary_samples[i].rotation_scalar_98 = 0.0;
    self->primary_samples[i].rotation_scalar_94 = 0.0;
    self->primary_samples[i].special_scalar = 0.0;
    self->primary_samples[i].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[i].transform);
    self->primary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    arg3e = sine(arg3b);
    ++v10;
    self->primary_samples[i].transform.position.y = sine(v48) * arg3e * arg2;
    arg3f = (float)v10;
    self->primary_samples[i].transform.position.z = arg3f;
    set_matrix_identity(&self->secondary_samples[i].transform);
    self->secondary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    self->secondary_samples[i].transform.position.y = self->primary_samples[i].transform.position.y + 0.49000001;
    self->secondary_samples[i].transform.position.z = arg3f;
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
      v14 = self->primary_samples;
      p_x = &v14[i - 1].transform.basis_forward.x;
      v52 = v14[i].transform.position.x - v14[i - 1].transform.position.x;
      v54 = p_x[47] - p_x[5];
      v16 = p_x[48] - p_x[6];
      *p_x = v52;
      p_x[1] = v54;
      v56 = v16;
      p_x[2] = v56;
      normalize_vector((Vec3 *)&self->primary_samples[i - 1].transform.basis_forward);
      cross_vectors(
        (Vec3 *)&self->primary_samples[i - 1],
        (Vec3 *)&self->primary_samples[i - 1].transform.basis_up,
        (Vec3 *)&self->primary_samples[i - 1].transform.basis_forward);
      cross_vectors(
        (Vec3 *)&self->primary_samples[i - 1].transform.basis_up,
        (Vec3 *)&self->primary_samples[i - 1].transform.basis_forward,
        (Vec3 *)&self->primary_samples[i - 1]);
      orthogonalize_matrix(&self->primary_samples[i - 1].transform);
      v17 = &self->secondary_samples[i - 1].transform.basis_up;
      v17->x = 0.0;
      v17->y = 1.0;
      v17->z = 0.0;
      secondary_samples = self->secondary_samples;
      v19 = &secondary_samples[i - 1].transform.basis_forward.x;
      v63 = secondary_samples[i].transform.position.x - secondary_samples[i - 1].transform.position.x;
      v66 = v19[47] - v19[5];
      v20 = v19[48] - v19[6];
      *v19 = v63;
      v19[1] = v66;
      v69 = v20;
      v19[2] = v69;
      normalize_vector((Vec3 *)&self->secondary_samples[i - 1].transform.basis_forward);
      cross_vectors(
        (Vec3 *)&self->secondary_samples[i - 1],
        (Vec3 *)&self->secondary_samples[i - 1].transform.basis_up,
        (Vec3 *)&self->secondary_samples[i - 1].transform.basis_forward);
      cross_vectors(
        (Vec3 *)&self->secondary_samples[i - 1].transform.basis_up,
        (Vec3 *)&self->secondary_samples[i - 1].transform.basis_forward,
        (Vec3 *)&self->secondary_samples[i - 1]);
      orthogonalize_matrix(&self->secondary_samples[i - 1].transform);
    }
    arg3a = v10;
  }
  v21 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v22 = 0;
    do
    {
      v23 = self->primary_samples;
      v24 = &v23[v22].delta_dir_to_next.x;
      v64 = v23[v22 + 1].transform.position.x - v23[v22].transform.position.x;
      v67 = v23[v22 + 1].transform.position.y - v23[v22].transform.position.y;
      v25 = v23[v22 + 1].transform.position.z - v23[v22].transform.position.z;
      *v24 = v64;
      v24[1] = v67;
      v70 = v25;
      v24[2] = v70;
      self->primary_samples[v22].delta_length = normalize_vector(&self->primary_samples[v22].delta_dir_to_next);
      v26 = self->secondary_samples;
      v27 = &v26[v22].delta_dir_to_next.x;
      v57 = v26[v22 + 1].transform.position.x - v26[v22].transform.position.x;
      v59 = v26[v22 + 1].transform.position.y - v26[v22].transform.position.y;
      v28 = v26[v22 + 1].transform.position.z - v26[v22].transform.position.z;
      *v27 = v57;
      v27[1] = v59;
      v61 = v28;
      v27[2] = v61;
      ++v21;
      self->secondary_samples[v22].delta_length = normalize_vector(&self->secondary_samples[v22].delta_dir_to_next);
      ++v22;
    }
    while ( v21 < (signed int)(self->segment_count - 1) );
  }
  p_delta_dir_to_next = &self->primary_samples[self->segment_count - 1].delta_dir_to_next;
  p_delta_dir_to_next->x = 0.0;
  p_delta_dir_to_next->y = 0.0;
  p_delta_dir_to_next->z = 1.0;
  self->primary_samples[self->segment_count - 1].delta_length = 1.0;
  v30 = &self->secondary_samples[self->segment_count - 1].delta_dir_to_next;
  v30->x = 0.0;
  v30->y = 0.0;
  v30->z = 1.0;
  self->secondary_samples[self->segment_count - 1].delta_length = 1.0;
  request_object_vertices(self->strip_mesh, (self->segment_count + 1) * (self->width_cells + 1));
  request_object_facequads(self->strip_mesh, 2 * self->segment_count * self->width_cells);
  strip_mesh = self->strip_mesh;
  vertices = strip_mesh->vertices;
  facequads = strip_mesh->facequads;
  v33 = 0;
  arg2a = vertices;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    do
    {
      v34 = self->width_cells;
      v35 = 0;
      arg4a = 0;
      for ( arg3c = v34; v35 <= v34; arg4a = v35 )
      {
        v36 = (double)arg4a - (double)arg3c * 0.5;
        v37 = (float *)((char *)&self->primary_samples->transform.basis_right.x + v7);
        if ( v33 == self->segment_count )
        {
          vertices = arg2a;
          v50 = v36 * *(v37 - 42);
          v51 = v36 * *(v37 - 41);
          v40 = v36 * *(v37 - 40);
          v72 = *(v37 - 28) + 1.0;
          v58 = *(v37 - 30) + v50;
          v60 = *(v37 - 29) + v51;
          v38 = &arg2a[v35 + v33 * (v34 + 1)].x;
          *v38 = v58;
          v62 = v72 + v40;
          v38[1] = v60;
          v39 = v62;
        }
        else
        {
          v53 = v36 * *v37;
          v55 = v36 * v37[1];
          v65 = v53 + v37[12];
          v68 = v55 + v37[13];
          v71 = v36 * v37[2] + v37[14];
          v38 = &vertices[v35 + v33 * (v34 + 1)].x;
          *v38 = v65;
          v38[1] = v68;
          v39 = v71;
        }
        v38[2] = v39;
        v34 = self->width_cells;
        ++v35;
        arg3c = v34;
      }
      ++v33;
      v7 += 168;
    }
    while ( v33 <= (signed int)self->segment_count );
    v7 = 0;
  }
  if ( (int)self->segment_count > 0 )
  {
    do
    {
      v41 = 0;
      arg4b = 0;
      if ( (int)self->width_cells > 0 )
      {
        arg3d = (double)(v7 % 8) * 0.125;
        v45 = (double)(v7 % 8 + 1) * 0.125;
        do
        {
          v42 = 0;
          v49 = v41 + 1;
          v46 = 0;
          arg4c = (double)arg4b * 0.125;
          arg2b = (double)(v41 + 1) * 0.125;
          while ( 1 )
          {
            v43 = &facequads[2 * v41 + 2 * v7 * self->width_cells + v42];
            v43->flags = 0;
            if ( v42 )
            {
              v43->vertex_index_a = v7 * (LOWORD(self->width_cells) + 1) + v41 + 1;
              v43->vertex_index_b = v41 + v7 * (LOWORD(self->width_cells) + 1);
              v43->vertex_index_c = v41 + (v7 + 1) * (LOWORD(self->width_cells) + 1);
              v43->vertex_index_d = (v7 + 1) * (LOWORD(self->width_cells) + 1) + v41 + 1;
              v43->texture_ref = get_or_create_texture_ref(&texture_list, texture_b, 0, 0);
              v43->u0 = arg2b;
              v43->v0 = arg3d;
              v43->u1 = arg4c;
              v43->v1 = arg3d;
              v43->u2 = arg4c;
              v43->v2 = v45;
              v43->u3 = arg2b;
            }
            else
            {
              v43->vertex_index_a = v41 + v7 * (LOWORD(self->width_cells) + 1);
              v43->vertex_index_b = v7 * (LOWORD(self->width_cells) + 1) + v41 + 1;
              v43->vertex_index_c = (v7 + 1) * (LOWORD(self->width_cells) + 1) + v41 + 1;
              v43->vertex_index_d = v41 + (v7 + 1) * (LOWORD(self->width_cells) + 1);
              v43->texture_ref = get_or_create_texture_ref(&texture_list, texture_a, 0, 0);
              v43->u0 = arg4c;
              v43->v0 = arg3d;
              v43->u1 = arg2b;
              v43->v1 = arg3d;
              v43->u2 = arg2b;
              v43->v2 = v45;
              v43->u3 = arg4c;
            }
            v43->v3 = v45;
            if ( ++v46 >= 2 )
              break;
            v42 = v46;
          }
          ++v41;
          arg4b = v49;
        }
        while ( v49 < (signed int)self->width_cells );
      }
      ++v7;
    }
    while ( v7 < (signed int)self->segment_count );
  }
  return finalize_path_template(self);
}

