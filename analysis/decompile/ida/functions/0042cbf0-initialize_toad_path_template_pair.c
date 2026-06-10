/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_toad_path_template_pair @ 0x42cbf0 */
/* selector: initialize_toad_path_template_pair */

int32_t __thiscall initialize_toad_path_template_pair(PathTemplate *self, char arg2, char *texture_a, char *texture_b)
{
  int v5; // esi
  int v6; // esi
  int v7; // esi
  int v8; // ebx
  double v9; // st7
  Vec4 *p_basis_up; // ecx
  PathTemplateSample *v11; // eax
  double v12; // st7
  double v13; // st7
  PathTemplateSample *primary_samples; // ecx
  double v15; // st7
  double v16; // st6
  Vec4 *p_position; // eax
  signed int v18; // edi
  int v19; // esi
  PathTemplateSample *v20; // ecx
  float *p_x; // eax
  double v22; // st7
  PathTemplateSample *secondary_samples; // edx
  float *v24; // eax
  double v25; // st7
  Vec3 *p_delta_dir_to_next; // ecx
  Vec3 *v27; // eax
  PathTemplateStripMesh *strip_mesh; // eax
  Vec3 *vertices; // edi
  signed int v30; // edx
  int v31; // ebx
  signed int width_cells; // ecx
  signed int v33; // esi
  double v34; // st7
  PathTemplateSample *v35; // eax
  float *v36; // eax
  float v37; // ecx
  double v38; // st7
  signed int j; // ebx
  int v40; // esi
  int v41; // ecx
  ObjectFaceQuad *v42; // edi
  float v44; // [esp+0h] [ebp-68h]
  int v45; // [esp+14h] [ebp-54h]
  float v46; // [esp+14h] [ebp-54h]
  float v47; // [esp+18h] [ebp-50h]
  float v48; // [esp+18h] [ebp-50h]
  int v49; // [esp+1Ch] [ebp-4Ch]
  int i; // [esp+1Ch] [ebp-4Ch]
  float v51; // [esp+1Ch] [ebp-4Ch]
  float v52; // [esp+20h] [ebp-48h]
  int v53; // [esp+20h] [ebp-48h]
  ObjectFaceQuad *facequads; // [esp+24h] [ebp-44h]
  float angleb; // [esp+28h] [ebp-40h]
  float anglec; // [esp+28h] [ebp-40h]
  float angled; // [esp+28h] [ebp-40h]
  Vec3 *angle; // [esp+28h] [ebp-40h]
  signed int anglea; // [esp+28h] [ebp-40h]
  float v60; // [esp+2Ch] [ebp-3Ch]
  float v61; // [esp+2Ch] [ebp-3Ch]
  float v62; // [esp+30h] [ebp-38h]
  float v63; // [esp+30h] [ebp-38h]
  float v64; // [esp+34h] [ebp-34h]
  float v65; // [esp+34h] [ebp-34h]
  float v66; // [esp+38h] [ebp-30h]
  float v67; // [esp+38h] [ebp-30h]
  float v68; // [esp+38h] [ebp-30h]
  float v69; // [esp+3Ch] [ebp-2Ch]
  float v70; // [esp+3Ch] [ebp-2Ch]
  float v71; // [esp+3Ch] [ebp-2Ch]
  float v72; // [esp+40h] [ebp-28h]
  float v73; // [esp+40h] [ebp-28h]
  float v74; // [esp+40h] [ebp-28h]
  float v75; // [esp+44h] [ebp-24h]
  float v76; // [esp+48h] [ebp-20h]
  float v77; // [esp+48h] [ebp-20h]
  float v78; // [esp+4Ch] [ebp-1Ch]
  float v79; // [esp+50h] [ebp-18h]
  float v80; // [esp+54h] [ebp-14h]
  float v81; // [esp+64h] [ebp-4h]
  signed int arg2g; // [esp+6Ch] [ebp+4h]
  int arg2a; // [esp+6Ch] [ebp+4h]
  int arg2b; // [esp+6Ch] [ebp+4h]
  int arg2c; // [esp+6Ch] [ebp+4h]
  int arg2d; // [esp+6Ch] [ebp+4h]
  int arg2e; // [esp+6Ch] [ebp+4h]
  float arg2f; // [esp+6Ch] [ebp+4h]

  self->kind = PATH_TEMPLATE_KIND_TURNUNDER_TOAD_FAMILY;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = 4;
  if ( arg2 )
  {
    v5 = 1;
    v47 = -2.0;
    v52 = -1.0;
    v45 = 1;
    v49 = 3;
  }
  else
  {
    v45 = 2;
    v47 = 2.0;
    v5 = 2;
    v52 = 1.0;
    v49 = 1;
  }
  self->width_or_scale = 1.0;
  arg2g = v49 + v5 + 26;
  self->segment_count = arg2g;
  self->segment_count_f = (float)arg2g;
  allocate_path_template_samples(self);
  self->special_runtime_flag_9c = 0;
  arg2a = 0;
  v6 = 0;
  do
  {
    self->primary_samples[v6].center_x = v47;
    self->primary_samples[v6].rotation_scalar_98 = 0.0;
    self->primary_samples[v6].rotation_scalar_94 = 0.0;
    self->primary_samples[v6].special_scalar = 0.0;
    self->primary_samples[v6].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v6].transform);
    self->primary_samples[v6].transform.position.x = self->primary_samples[v6].center_x;
    angleb = (float)arg2a;
    self->primary_samples[v6].transform.position.y = 0.0;
    self->primary_samples[v6].transform.position.z = angleb;
    self->primary_samples[v6].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[v6].transform);
    self->secondary_samples[v6].transform.position.x = self->primary_samples[v6].center_x;
    self->secondary_samples[v6].transform.position.y = 0.49000001;
    self->secondary_samples[v6].transform.position.z = angleb;
    self->secondary_samples[v6++].delta_length = 1.0;
    ++arg2a;
  }
  while ( arg2a < v45 );
  arg2b = v45 + 26;
  v7 = v45 + 26;
  do
  {
    self->primary_samples[v7].center_x = v47;
    self->primary_samples[v7].rotation_scalar_98 = 0.0;
    self->primary_samples[v7].rotation_scalar_94 = 0.0;
    self->primary_samples[v7].special_scalar = 0.0;
    self->primary_samples[v7].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v7].transform);
    anglec = (float)arg2b;
    self->primary_samples[v7].transform.position.x = self->primary_samples[v7].center_x;
    self->primary_samples[v7].transform.position.y = 0.0;
    self->primary_samples[v7].transform.position.z = anglec;
    self->primary_samples[v7].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[v7].transform);
    self->secondary_samples[v7].transform.position.x = self->primary_samples[v7].center_x;
    self->secondary_samples[v7].transform.position.y = 0.49000001;
    self->secondary_samples[v7].transform.position.z = anglec;
    self->secondary_samples[v7++].delta_length = 1.0;
    ++arg2b;
  }
  while ( arg2b + -26 - v45 < v49 );
  arg2c = 0;
  v8 = v45;
  do
  {
    v44 = (double)arg2c * 0.24166098;
    angled = (1.0 - cosine(v44)) * 0.5 * v52 * 1.5707964;
    self->primary_samples[v8].center_x = v47;
    self->primary_samples[v8].rotation_scalar_98 = 0.0;
    self->primary_samples[v8].rotation_scalar_94 = 0.0;
    self->primary_samples[v8].special_scalar = 0.0;
    self->primary_samples[v8].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v8].transform);
    v9 = sine(angled);
    self->primary_samples[v8].transform.position.x = v9 + v9 + v47;
    self->primary_samples[v8].transform.position.z = (float)(v45 + arg2c);
    self->primary_samples[v8].transform.position.y = 0.0;
    p_basis_up = &self->primary_samples[v8].transform.basis_up;
    p_basis_up->x = 0.0;
    p_basis_up->y = 1.0;
    p_basis_up->z = 0.0;
    v11 = &self->primary_samples[v8];
    v12 = v11->transform.position.x - v11[-1].transform.position.x;
    v11 = (PathTemplateSample *)((char *)v11 + 32);
    v66 = v12;
    v69 = v11->transform.basis_up.y - v11[-1].transform.basis_up.y;
    v13 = v11->transform.basis_up.z - v11[-1].transform.basis_up.z;
    v11->transform.basis_right.x = v66;
    v11->transform.basis_right.y = v69;
    v72 = v13;
    v11->transform.basis_right.z = v72;
    normalize_vector((Vec3 *)&self->primary_samples[v8].transform.basis_forward);
    cross_vectors(
      (Vec3 *)&self->primary_samples[v8],
      (Vec3 *)&self->primary_samples[v8].transform.basis_up,
      (Vec3 *)&self->primary_samples[v8].transform.basis_forward);
    rotate_matrix_world_z(&self->primary_samples[v8].transform, angled);
    qmemcpy(&self->secondary_samples[v8], &self->primary_samples[v8], 0x40u);
    primary_samples = self->primary_samples;
    v15 = primary_samples[v8].transform.basis_up.x * 0.49000001;
    v76 = primary_samples[v8].transform.basis_up.y * 0.49000001;
    v16 = primary_samples[v8].transform.basis_up.z * 0.49000001;
    p_position = &self->secondary_samples[v8++].transform.position;
    v78 = v16;
    p_position->x = v15 + p_position->x;
    p_position->y = v76 + p_position->y;
    p_position->z = v78 + p_position->z;
    ++arg2c;
  }
  while ( arg2c < 26 );
  v18 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v19 = 0;
    do
    {
      v20 = self->primary_samples;
      p_x = &v20[v19].delta_dir_to_next.x;
      v67 = v20[v19 + 1].transform.position.x - v20[v19].transform.position.x;
      v70 = v20[v19 + 1].transform.position.y - v20[v19].transform.position.y;
      v22 = v20[v19 + 1].transform.position.z - v20[v19].transform.position.z;
      *p_x = v67;
      p_x[1] = v70;
      v73 = v22;
      p_x[2] = v73;
      self->primary_samples[v19].delta_length = normalize_vector(&self->primary_samples[v19].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      v24 = &secondary_samples[v19].delta_dir_to_next.x;
      v60 = secondary_samples[v19 + 1].transform.position.x - secondary_samples[v19].transform.position.x;
      v62 = secondary_samples[v19 + 1].transform.position.y - secondary_samples[v19].transform.position.y;
      v25 = secondary_samples[v19 + 1].transform.position.z - secondary_samples[v19].transform.position.z;
      *v24 = v60;
      v24[1] = v62;
      v64 = v25;
      v24[2] = v64;
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
  vertices = strip_mesh->vertices;
  facequads = strip_mesh->facequads;
  v30 = 0;
  angle = vertices;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    v31 = 0;
    do
    {
      width_cells = self->width_cells;
      v33 = 0;
      arg2d = 0;
      for ( i = width_cells; v33 <= width_cells; arg2d = v33 )
      {
        v34 = (double)arg2d - (double)i * 0.5;
        v35 = &self->primary_samples[v31];
        if ( v30 == self->segment_count )
        {
          vertices = angle;
          v79 = v34 * v35[-1].transform.basis_right.x;
          v80 = v34 * v35[-1].transform.basis_right.y;
          v38 = v34 * v35[-1].transform.basis_right.z;
          v81 = v35[-1].transform.position.z + 1.0;
          v61 = v35[-1].transform.position.x + v79;
          v63 = v35[-1].transform.position.y + v80;
          v36 = &angle[v33 + v30 * (width_cells + 1)].x;
          *v36 = v61;
          v65 = v81 + v38;
          v36[1] = v63;
          v37 = v65;
        }
        else
        {
          v75 = v34 * v35->transform.basis_right.x;
          v77 = v34 * v35->transform.basis_right.y;
          v68 = v75 + v35->transform.position.x;
          v71 = v77 + v35->transform.position.y;
          v74 = v34 * v35->transform.basis_right.z + v35->transform.position.z;
          v36 = &vertices[v33 + v30 * (width_cells + 1)].x;
          *v36 = v68;
          v36[1] = v71;
          v37 = v74;
        }
        v36[2] = v37;
        width_cells = self->width_cells;
        ++v33;
        i = width_cells;
      }
      ++v30;
      ++v31;
    }
    while ( v30 <= (signed int)self->segment_count );
  }
  for ( j = 0; j < (signed int)self->segment_count; ++j )
  {
    v40 = 0;
    arg2e = 0;
    if ( (int)self->width_cells > 0 )
    {
      v51 = (double)(j % 8) * 0.125;
      v46 = (double)(j % 8 + 1) * 0.125;
      do
      {
        v41 = 0;
        anglea = v40 + 1;
        v53 = 0;
        arg2f = (double)arg2e * 0.125;
        v48 = (double)(v40 + 1) * 0.125;
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
            v42->texture_ref = get_or_create_texture_ref(&texture_list, texture_b, 0, 0);
            v42->u0 = v48;
            v42->v0 = v51;
            v42->u1 = arg2f;
            v42->v1 = v51;
            v42->u2 = arg2f;
            v42->v2 = v46;
            v42->u3 = v48;
          }
          else
          {
            v42->vertex_index_a = v40 + j * (LOWORD(self->width_cells) + 1);
            v42->vertex_index_b = j * (LOWORD(self->width_cells) + 1) + v40 + 1;
            v42->vertex_index_c = (j + 1) * (LOWORD(self->width_cells) + 1) + v40 + 1;
            v42->vertex_index_d = v40 + (j + 1) * (LOWORD(self->width_cells) + 1);
            v42->texture_ref = get_or_create_texture_ref(&texture_list, texture_a, 0, 0);
            v42->u0 = arg2f;
            v42->v0 = v51;
            v42->u1 = v48;
            v42->v1 = v51;
            v42->u2 = v48;
            v42->v2 = v46;
            v42->u3 = arg2f;
          }
          v42->v3 = v46;
          if ( ++v53 >= 2 )
            break;
          v41 = v53;
        }
        ++v40;
        arg2e = anglea;
      }
      while ( anglea < (signed int)self->width_cells );
    }
  }
  return finalize_path_template(self);
}

