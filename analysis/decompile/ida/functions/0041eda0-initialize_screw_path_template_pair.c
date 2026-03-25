/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_screw_path_template_pair @ 0x41eda0 */
/* selector: initialize_screw_path_template_pair */

int32_t __thiscall initialize_screw_path_template_pair(
        PathTemplate *self,
        int32_t arg2,
        int32_t arg3,
        char *texture_a,
        char *texture_b)
{
  signed int v6; // ebx
  int i; // edi
  int v8; // ebp
  int v9; // edi
  int v10; // ebp
  int v11; // edi
  double v12; // st7
  PathTemplateSample *primary_samples; // ebp
  Vec4 *p_basis_up; // ecx
  PathTemplateSample *v15; // eax
  double v16; // st7
  double v17; // st7
  Vec4 *v18; // edx
  PathTemplateSample *v19; // eax
  signed int v20; // ebp
  int v21; // edi
  PathTemplateSample *v22; // edx
  float *p_x; // eax
  double v24; // st7
  PathTemplateSample *secondary_samples; // ecx
  float *v26; // eax
  double v27; // st7
  Vec3 *p_delta_dir_to_next; // edx
  Vec3 *v29; // ecx
  PathTemplateStripMesh *strip_mesh; // eax
  signed int v31; // edx
  Vec3 *vertices; // ebp
  signed int width_cells; // ecx
  int32_t v34; // edi
  double v35; // st7
  float *v36; // eax
  float *v37; // eax
  float v38; // ecx
  double v39; // st7
  int v40; // ebp
  int v41; // ecx
  ObjectFaceQuad *v42; // edi
  float v44; // [esp+0h] [ebp-64h]
  float v45; // [esp+14h] [ebp-50h]
  float v46; // [esp+18h] [ebp-4Ch]
  float v47; // [esp+18h] [ebp-4Ch]
  float v48; // [esp+1Ch] [ebp-48h]
  float v49; // [esp+1Ch] [ebp-48h]
  float v50; // [esp+1Ch] [ebp-48h]
  int v51; // [esp+1Ch] [ebp-48h]
  float v52; // [esp+20h] [ebp-44h]
  float v53; // [esp+20h] [ebp-44h]
  Vec3 *v54; // [esp+20h] [ebp-44h]
  signed int v55; // [esp+20h] [ebp-44h]
  ObjectFaceQuad *facequads; // [esp+24h] [ebp-40h]
  float v57; // [esp+28h] [ebp-3Ch]
  float v58; // [esp+28h] [ebp-3Ch]
  float v59; // [esp+2Ch] [ebp-38h]
  float v60; // [esp+34h] [ebp-30h]
  float v61; // [esp+34h] [ebp-30h]
  float v62; // [esp+38h] [ebp-2Ch]
  float v63; // [esp+38h] [ebp-2Ch]
  float v64; // [esp+3Ch] [ebp-28h]
  float v65; // [esp+40h] [ebp-24h]
  float v66; // [esp+40h] [ebp-24h]
  float v67; // [esp+40h] [ebp-24h]
  float v68; // [esp+44h] [ebp-20h]
  float v69; // [esp+44h] [ebp-20h]
  float v70; // [esp+48h] [ebp-1Ch]
  float v71; // [esp+48h] [ebp-1Ch]
  float v72; // [esp+4Ch] [ebp-18h]
  float v73; // [esp+4Ch] [ebp-18h]
  float v74; // [esp+4Ch] [ebp-18h]
  float v75; // [esp+50h] [ebp-14h]
  float v76; // [esp+50h] [ebp-14h]
  float v77; // [esp+50h] [ebp-14h]
  float v78; // [esp+54h] [ebp-10h]
  float v79; // [esp+54h] [ebp-10h]
  float v80; // [esp+54h] [ebp-10h]
  float v81; // [esp+60h] [ebp-4h]
  int32_t arg2a; // [esp+68h] [ebp+4h]
  int32_t arg2b; // [esp+68h] [ebp+4h]
  float arg2c; // [esp+68h] [ebp+4h]
  int32_t arg3a; // [esp+6Ch] [ebp+8h]
  int32_t arg3b; // [esp+6Ch] [ebp+8h]
  float arg3f; // [esp+6Ch] [ebp+8h]
  int arg3c; // [esp+6Ch] [ebp+8h]
  int32_t arg3d; // [esp+6Ch] [ebp+8h]
  float arg3e; // [esp+6Ch] [ebp+8h]
  char *v91; // [esp+78h] [ebp+14h]

  v6 = 0;
  self->width_cells = arg3;
  self->kind = PATH_TEMPLATE_KIND_SCREW;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_or_scale = 1.0;
  self->segment_count = arg2 + 8;
  self->segment_count_f = (float)(arg2 + 8);
  allocate_path_template_samples(self);
  self->special_runtime_flag_9c = 0;
  arg3a = 0;
  for ( i = 0; i < 3; ++i )
  {
    self->primary_samples[i].center_x = 0.5;
    self->primary_samples[i].rotation_scalar_98 = 0.0;
    self->primary_samples[i].rotation_scalar_94 = 0.0;
    self->primary_samples[i].special_scalar = 0.0;
    self->primary_samples[i].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[i].transform);
    v52 = (float)arg3a;
    self->primary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    self->primary_samples[i].transform.position.y = 0.0;
    self->primary_samples[i].transform.position.z = v52;
    set_matrix_identity(&self->secondary_samples[i].transform);
    self->secondary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    self->secondary_samples[i].transform.position.y = 0.49000001;
    self->secondary_samples[i].transform.position.z = v52;
    ++arg3a;
  }
  v8 = arg2 + 3;
  arg3b = arg2 + 3;
  v9 = arg2 + 3;
  do
  {
    self->primary_samples[v9].center_x = -0.5;
    self->primary_samples[v9].rotation_scalar_98 = 0.0;
    self->primary_samples[v9].rotation_scalar_94 = 0.0;
    self->primary_samples[v9].special_scalar = 0.0;
    self->primary_samples[v9].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v9].transform);
    arg3f = (float)arg3b;
    self->primary_samples[v9].transform.position.x = self->primary_samples[v9].center_x;
    self->primary_samples[v9].transform.position.y = 0.0;
    self->primary_samples[v9].transform.position.z = arg3f;
    set_matrix_identity(&self->secondary_samples[v9].transform);
    self->secondary_samples[v9].transform.position.x = self->primary_samples[v9].center_x;
    self->secondary_samples[v9].transform.position.y = 0.49000001;
    self->secondary_samples[v9++].transform.position.z = arg3f;
    arg3b = ++v8;
  }
  while ( v8 + -3 - arg2 < 5 );
  v10 = 0;
  arg3c = 0;
  if ( arg2 > 0 )
  {
    v11 = 3;
    do
    {
      v53 = (float)arg2;
      v12 = (double)arg3c * 6.2831855 / v53;
      v46 = v12;
      v44 = v12 * 0.5;
      self->primary_samples[v11].center_x = cosine(v44) * 0.5;
      self->primary_samples[v11].rotation_scalar_98 = 0.0;
      self->primary_samples[v11].rotation_scalar_94 = v46;
      self->primary_samples[v11].special_scalar = 0.0;
      self->primary_samples[v11].lateral_scale = 1.0;
      set_matrix_identity(&self->primary_samples[v11].transform);
      self->primary_samples[v11].transform.position.x = self->primary_samples[v11].center_x;
      v48 = (float)(v10 + 3);
      self->primary_samples[v11].transform.position.y = 0.0;
      self->primary_samples[v11].transform.position.z = v48;
      set_matrix_identity(&self->secondary_samples[v11].transform);
      primary_samples = self->primary_samples;
      self->secondary_samples[v11].transform.position.x = primary_samples[v11].center_x - sine(v46) * 0.49000001;
      self->secondary_samples[v11].transform.position.y = cosine(v46) * 0.49000001;
      self->secondary_samples[v11].transform.position.z = v48;
      if ( v11 <= 3 )
      {
        set_matrix_rotation_identity(&self->primary_samples[v11 - 1].transform);
        set_matrix_rotation_identity(&self->secondary_samples[v11 - 1].transform);
      }
      else
      {
        v49 = cosine(v46);
        v57 = -sine(v46);
        p_basis_up = &self->primary_samples[v11 - 1].transform.basis_up;
        p_basis_up->x = v57;
        p_basis_up->y = v49;
        p_basis_up->z = 0.0;
        v15 = &self->primary_samples[v11];
        v16 = v15->transform.position.x - v15[-1].transform.position.x;
        v15 = (PathTemplateSample *)((char *)v15 - 136);
        v60 = v16;
        v62 = v15[1].transform.basis_up.y - v15->transform.basis_up.y;
        v17 = v15[1].transform.basis_up.z - v15->transform.basis_up.z;
        v15->transform.basis_right.x = v60;
        v15->transform.basis_right.y = v62;
        v64 = v17;
        v15->transform.basis_right.z = v64;
        normalize_vector((Vec3 *)&self->primary_samples[v11 - 1].transform.basis_forward);
        cross_vectors(
          (Vec3 *)&self->primary_samples[v11 - 1],
          (Vec3 *)&self->primary_samples[v11 - 1].transform.basis_up,
          (Vec3 *)&self->primary_samples[v11 - 1].transform.basis_forward);
        v50 = cosine(v46);
        v65 = -sine(v46);
        v18 = &self->secondary_samples[v11 - 1].transform.basis_up;
        v18->x = v65;
        v18->y = v50;
        v18->z = 0.0;
        v19 = &self->secondary_samples[v11];
        v72 = v19->transform.position.x - v19[-1].transform.position.x;
        v75 = v19->transform.position.y - v19[-1].transform.position.y;
        v78 = v19->transform.position.z - v19[-1].transform.position.z;
        v19 = (PathTemplateSample *)((char *)v19 - 136);
        v19->transform.basis_right.x = v72;
        v19->transform.basis_right.y = v75;
        v19->transform.basis_right.z = v78;
        normalize_vector((Vec3 *)&self->secondary_samples[v11 - 1].transform.basis_forward);
        cross_vectors(
          (Vec3 *)&self->secondary_samples[v11 - 1],
          (Vec3 *)&self->secondary_samples[v11 - 1].transform.basis_up,
          (Vec3 *)&self->secondary_samples[v11 - 1].transform.basis_forward);
      }
      v10 = arg3c + 1;
      ++v11;
      ++arg3c;
    }
    while ( arg3c < arg2 );
    v6 = 0;
  }
  v20 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v21 = 0;
    do
    {
      v22 = self->primary_samples;
      p_x = &v22[v21].delta_dir_to_next.x;
      v73 = v22[v21 + 1].transform.position.x - v22[v21].transform.position.x;
      v76 = v22[v21 + 1].transform.position.y - v22[v21].transform.position.y;
      v24 = v22[v21 + 1].transform.position.z - v22[v21].transform.position.z;
      *p_x = v73;
      p_x[1] = v76;
      v79 = v24;
      p_x[2] = v79;
      self->primary_samples[v21].delta_length = normalize_vector(&self->primary_samples[v21].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      v26 = &secondary_samples[v21].delta_dir_to_next.x;
      v66 = secondary_samples[v21 + 1].transform.position.x - secondary_samples[v21].transform.position.x;
      v68 = secondary_samples[v21 + 1].transform.position.y - secondary_samples[v21].transform.position.y;
      v27 = secondary_samples[v21 + 1].transform.position.z - secondary_samples[v21].transform.position.z;
      *v26 = v66;
      v26[1] = v68;
      v70 = v27;
      v26[2] = v70;
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
  v31 = 0;
  vertices = strip_mesh->vertices;
  v54 = vertices;
  facequads = strip_mesh->facequads;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    do
    {
      width_cells = self->width_cells;
      v34 = 0;
      arg2a = 0;
      for ( arg3d = width_cells; v34 <= width_cells; arg2a = v34 )
      {
        v35 = (double)arg2a - (double)arg3d * 0.5;
        v36 = (float *)((char *)&self->primary_samples->transform.basis_right.x + v6);
        if ( v31 == self->segment_count )
        {
          vertices = v54;
          v58 = v35 * *(v36 - 42);
          v59 = v35 * *(v36 - 41);
          v39 = v35 * *(v36 - 40);
          v81 = *(v36 - 28) + 1.0;
          v67 = *(v36 - 30) + v58;
          v69 = *(v36 - 29) + v59;
          v37 = &v54[v34 + v31 * (width_cells + 1)].x;
          *v37 = v67;
          v71 = v81 + v39;
          v37[1] = v69;
          v38 = v71;
        }
        else
        {
          v61 = v35 * *v36;
          v63 = v35 * v36[1];
          v74 = v61 + v36[12];
          v77 = v63 + v36[13];
          v80 = v35 * v36[2] + v36[14];
          v37 = &vertices[v34 + v31 * (width_cells + 1)].x;
          *v37 = v74;
          v37[1] = v77;
          v38 = v80;
        }
        v37[2] = v38;
        width_cells = self->width_cells;
        ++v34;
        arg3d = width_cells;
      }
      ++v31;
      v6 += 168;
    }
    while ( v31 <= (signed int)self->segment_count );
    v6 = 0;
  }
  if ( (int)self->segment_count > 0 )
  {
    do
    {
      v40 = 0;
      arg2b = 0;
      if ( (int)self->width_cells > 0 )
      {
        arg3e = (double)(v6 % 8) * 0.125;
        v47 = (double)(v6 % 8 + 1) * 0.125;
        do
        {
          v41 = 0;
          v55 = v40 + 1;
          v51 = 0;
          arg2c = (double)arg2b * 0.125;
          v45 = (double)(v40 + 1) * 0.125;
          while ( 1 )
          {
            v42 = &facequads[2 * v40 + 2 * v6 * self->width_cells + v41];
            v42->flags = 0;
            if ( v41 )
            {
              v42->vertex_index_a = v6 * (LOWORD(self->width_cells) + 1) + v40 + 1;
              v42->vertex_index_b = v40 + v6 * (LOWORD(self->width_cells) + 1);
              v42->vertex_index_c = v40 + (v6 + 1) * (LOWORD(self->width_cells) + 1);
              v42->vertex_index_d = (v6 + 1) * (LOWORD(self->width_cells) + 1) + v40 + 1;
              v42->texture_ref = get_or_create_texture_ref((TextureRefList *)dword_4B7790, v91, 0, 0);
              v42->u0 = v45;
              v42->v0 = arg3e;
              v42->u1 = arg2c;
              v42->v1 = arg3e;
              v42->u2 = arg2c;
              v42->v2 = v47;
              v42->u3 = v45;
            }
            else
            {
              v42->vertex_index_a = v40 + v6 * (LOWORD(self->width_cells) + 1);
              v42->vertex_index_b = v6 * (LOWORD(self->width_cells) + 1) + v40 + 1;
              v42->vertex_index_c = (v6 + 1) * (LOWORD(self->width_cells) + 1) + v40 + 1;
              v42->vertex_index_d = v40 + (v6 + 1) * (LOWORD(self->width_cells) + 1);
              v42->texture_ref = get_or_create_texture_ref((TextureRefList *)dword_4B7790, texture_b, 0, 0);
              v42->u0 = arg2c;
              v42->v0 = arg3e;
              v42->u1 = v45;
              v42->v1 = arg3e;
              v42->u2 = v45;
              v42->v2 = v47;
              v42->u3 = arg2c;
            }
            v42->v3 = v47;
            if ( ++v51 >= 2 )
              break;
            v41 = v51;
          }
          ++v40;
          arg2b = v55;
        }
        while ( v55 < (signed int)self->width_cells );
      }
      ++v6;
    }
    while ( v6 < (signed int)self->segment_count );
  }
  return finalize_path_template(self);
}

