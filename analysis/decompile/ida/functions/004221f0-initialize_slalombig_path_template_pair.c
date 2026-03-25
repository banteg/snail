/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_slalombig_path_template_pair @ 0x4221f0 */
/* selector: initialize_slalombig_path_template_pair */

int32_t __thiscall initialize_slalombig_path_template_pair(
        PathTemplate *self,
        int32_t arg2,
        uint32_t arg3,
        char *texture_a,
        char *texture_b)
{
  int v6; // ebp
  int v7; // ebx
  int i; // edi
  int v9; // edi
  int32_t v10; // ebx
  int v11; // edi
  double v12; // st7
  double v13; // st7
  Vec4 *p_basis_up; // eax
  PathTemplateSample *primary_samples; // edx
  float *p_x; // eax
  double v17; // st7
  PathTemplateSample *v18; // eax
  Vec4 *v19; // edx
  PathTemplateSample *secondary_samples; // ecx
  float *v21; // eax
  double v22; // st7
  signed int v23; // ebx
  int v24; // edi
  PathTemplateSample *v25; // ecx
  float *v26; // eax
  double v27; // st7
  PathTemplateSample *v28; // edx
  float *v29; // eax
  double v30; // st7
  Vec3 *p_delta_dir_to_next; // ecx
  Vec3 *v32; // eax
  PathTemplateStripMesh *strip_mesh; // eax
  signed int v34; // edx
  int v35; // ebx
  signed int width_cells; // ecx
  signed int v37; // edi
  double v38; // st7
  PathTemplateSample *v39; // eax
  float *v40; // ecx
  float *v41; // ecx
  double v42; // st6
  int v43; // ebx
  int v44; // ecx
  uint32_t v45; // edi
  float v47; // [esp+0h] [ebp-64h]
  float v48; // [esp+0h] [ebp-64h]
  float v49; // [esp+14h] [ebp-50h]
  float v50; // [esp+18h] [ebp-4Ch]
  float v51; // [esp+18h] [ebp-4Ch]
  float v52; // [esp+1Ch] [ebp-48h]
  Vec3 *vertices; // [esp+1Ch] [ebp-48h]
  int v54; // [esp+1Ch] [ebp-48h]
  float v55; // [esp+20h] [ebp-44h]
  float v56; // [esp+20h] [ebp-44h]
  signed int v57; // [esp+20h] [ebp-44h]
  ObjectFaceQuad *facequads; // [esp+24h] [ebp-40h]
  float v59; // [esp+28h] [ebp-3Ch]
  float v60; // [esp+2Ch] [ebp-38h]
  float v61; // [esp+34h] [ebp-30h]
  float v62; // [esp+34h] [ebp-30h]
  float v63; // [esp+38h] [ebp-2Ch]
  float v64; // [esp+38h] [ebp-2Ch]
  float v65; // [esp+3Ch] [ebp-28h]
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
  signed int arg3a; // [esp+6Ch] [ebp+8h]
  signed int arg3b; // [esp+6Ch] [ebp+8h]
  float arg3f; // [esp+6Ch] [ebp+8h]
  signed int arg3c; // [esp+6Ch] [ebp+8h]
  float arg3g; // [esp+6Ch] [ebp+8h]
  float arg3h; // [esp+6Ch] [ebp+8h]
  signed int arg3d; // [esp+6Ch] [ebp+8h]
  float arg3e; // [esp+6Ch] [ebp+8h]
  char *v93; // [esp+78h] [ebp+14h]

  v6 = 0;
  self->width_cells = arg3;
  self->kind = PATH_TEMPLATE_KIND_SLALOMBIG;
  v7 = arg2 + 4;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_or_scale = 1.0;
  self->segment_count = arg2 + 8;
  self->segment_count_f = (float)(arg2 + 8);
  allocate_path_nodes(self);
  self->special_runtime_flag_9c = 0;
  arg3a = 0;
  for ( i = 0; i < 4; ++i )
  {
    self->primary_samples[i].center_x = 0.0;
    self->primary_samples[i].rotation_scalar_98 = 0.0;
    self->primary_samples[i].rotation_scalar_94 = 0.0;
    self->primary_samples[i].special_scalar = 0.0;
    self->primary_samples[i].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[i].transform);
    v55 = (float)arg3a;
    self->primary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    self->primary_samples[i].transform.position.y = 0.0;
    self->primary_samples[i].transform.position.z = v55;
    set_matrix_identity(&self->secondary_samples[i].transform);
    self->secondary_samples[i].transform.position.x = self->primary_samples[i].center_x;
    self->secondary_samples[i].transform.position.y = 0.49000001;
    self->secondary_samples[i].transform.position.z = v55;
    ++arg3a;
  }
  arg3b = arg2 + 4;
  v9 = v7;
  do
  {
    self->primary_samples[v9].center_x = 0.0;
    self->primary_samples[v9].rotation_scalar_98 = 0.0;
    self->primary_samples[v9].rotation_scalar_94 = 0.0;
    self->primary_samples[v9].special_scalar = 0.0;
    self->primary_samples[v9].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v9].transform);
    self->primary_samples[v9].transform.position.x = self->primary_samples[v9].center_x;
    arg3f = (float)arg3b;
    self->primary_samples[v9].transform.position.y = 0.0;
    self->primary_samples[v9].transform.position.z = arg3f;
    set_matrix_identity(&self->secondary_samples[v9].transform);
    self->secondary_samples[v9].transform.position.x = self->primary_samples[v9].center_x;
    self->secondary_samples[v9].transform.position.y = 0.49000001;
    self->secondary_samples[v9++].transform.position.z = arg3f;
    arg3b = ++v7;
  }
  while ( v7 + -4 - arg2 < 4 );
  v10 = 0;
  arg3c = 0;
  if ( arg2 > 0 )
  {
    v11 = 4;
    do
    {
      v56 = (float)arg2;
      v12 = (double)arg3c / v56;
      v50 = v12 * 6.2831855;
      v13 = v12 - 0.5;
      if ( v13 >= 0.0 )
        v52 = v13;
      else
        v52 = -v13;
      if ( v13 < 0.0 )
        v13 = -v13;
      arg3g = v13;
      self->primary_samples[v11].center_x = sine(v50) * (1.0 - arg3g) * (1.0 - v52) * 4.4444447;
      self->primary_samples[v11].rotation_scalar_98 = 0.0;
      self->primary_samples[v11].rotation_scalar_94 = 0.0;
      self->primary_samples[v11].special_scalar = 0.0;
      self->primary_samples[v11].lateral_scale = 1.0;
      set_matrix_identity(&self->primary_samples[v11].transform);
      self->primary_samples[v11].transform.position.x = self->primary_samples[v11].center_x;
      self->primary_samples[v11].transform.position.y = 0.0;
      arg3h = (float)(v10 + 4);
      self->primary_samples[v11].transform.position.z = arg3h;
      set_matrix_identity(&self->secondary_samples[v11].transform);
      self->secondary_samples[v11].transform.position.x = self->primary_samples[v11].center_x;
      self->secondary_samples[v11].transform.position.y = 0.49000001;
      self->secondary_samples[v11].transform.position.z = arg3h;
      if ( v11 <= 4 )
      {
        set_matrix_rotation_identity(&self->primary_samples[v11 - 1].transform);
        set_matrix_rotation_identity(&self->secondary_samples[v11 - 1].transform);
      }
      else
      {
        p_basis_up = &self->primary_samples[v11 - 1].transform.basis_up;
        p_basis_up->x = 0.0;
        p_basis_up->y = 1.0;
        p_basis_up->z = 0.0;
        primary_samples = self->primary_samples;
        p_x = &primary_samples[v11 - 1].transform.basis_forward.x;
        v61 = primary_samples[v11].transform.position.x - primary_samples[v11 - 1].transform.position.x;
        v63 = p_x[47] - p_x[5];
        v17 = p_x[48] - p_x[6];
        *p_x = v61;
        p_x[1] = v63;
        v65 = v17;
        p_x[2] = v65;
        normalize_vector((Vec3 *)&self->primary_samples[v11 - 1].transform.basis_forward);
        cross_vectors(
          (Vec3 *)&self->primary_samples[v11 - 1],
          (Vec3 *)&self->primary_samples[v11 - 1].transform.basis_up,
          (Vec3 *)&self->primary_samples[v11 - 1].transform.basis_forward);
        v18 = &self->primary_samples[v11];
        v47 = v18[-1].center_x * 0.2617994;
        rotate_matrix_world_z(&v18[-1].transform, v47);
        v19 = &self->secondary_samples[v11 - 1].transform.basis_up;
        v19->x = 0.0;
        v19->y = 1.0;
        v19->z = 0.0;
        secondary_samples = self->secondary_samples;
        v21 = &secondary_samples[v11 - 1].transform.basis_forward.x;
        v72 = secondary_samples[v11].transform.position.x - secondary_samples[v11 - 1].transform.position.x;
        v75 = v21[47] - v21[5];
        v22 = v21[48] - v21[6];
        *v21 = v72;
        v21[1] = v75;
        v78 = v22;
        v21[2] = v78;
        normalize_vector((Vec3 *)&self->secondary_samples[v11 - 1].transform.basis_forward);
        cross_vectors(
          (Vec3 *)&self->secondary_samples[v11 - 1],
          (Vec3 *)&self->secondary_samples[v11 - 1].transform.basis_up,
          (Vec3 *)&self->secondary_samples[v11 - 1].transform.basis_forward);
        v48 = self->primary_samples[v11 - 1].center_x * 0.2617994;
        rotate_matrix_world_z(&self->secondary_samples[v11 - 1].transform, v48);
      }
      ++v10;
      ++v11;
      arg3c = v10;
    }
    while ( v10 < arg2 );
  }
  v23 = 0;
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v24 = 0;
    do
    {
      v25 = self->primary_samples;
      v26 = &v25[v24].delta_dir_to_next.x;
      v73 = v25[v24 + 1].transform.position.x - v25[v24].transform.position.x;
      v76 = v25[v24 + 1].transform.position.y - v25[v24].transform.position.y;
      v27 = v25[v24 + 1].transform.position.z - v25[v24].transform.position.z;
      *v26 = v73;
      v26[1] = v76;
      v79 = v27;
      v26[2] = v79;
      self->primary_samples[v24].delta_length = normalize_vector(&self->primary_samples[v24].delta_dir_to_next);
      v28 = self->secondary_samples;
      v29 = &v28[v24].delta_dir_to_next.x;
      v66 = v28[v24 + 1].transform.position.x - v28[v24].transform.position.x;
      v68 = v28[v24 + 1].transform.position.y - v28[v24].transform.position.y;
      v30 = v28[v24 + 1].transform.position.z - v28[v24].transform.position.z;
      *v29 = v66;
      v29[1] = v68;
      v70 = v30;
      v29[2] = v70;
      ++v23;
      self->secondary_samples[v24].delta_length = normalize_vector(&self->secondary_samples[v24].delta_dir_to_next);
      ++v24;
    }
    while ( v23 < (signed int)(self->segment_count - 1) );
  }
  p_delta_dir_to_next = &self->primary_samples[self->segment_count - 1].delta_dir_to_next;
  p_delta_dir_to_next->x = 0.0;
  p_delta_dir_to_next->y = 0.0;
  p_delta_dir_to_next->z = 1.0;
  self->primary_samples[self->segment_count - 1].delta_length = 1.0;
  v32 = &self->secondary_samples[self->segment_count - 1].delta_dir_to_next;
  v32->x = 0.0;
  v32->y = 0.0;
  v32->z = 1.0;
  self->secondary_samples[self->segment_count - 1].delta_length = 1.0;
  request_object_vertices(self->strip_mesh, (self->segment_count + 1) * (self->width_cells + 1));
  request_object_facequads(self->strip_mesh, 2 * self->segment_count * self->width_cells);
  strip_mesh = self->strip_mesh;
  facequads = strip_mesh->facequads;
  vertices = strip_mesh->vertices;
  v34 = 0;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    v35 = 0;
    do
    {
      width_cells = self->width_cells;
      v37 = 0;
      arg2a = 0;
      for ( arg3d = width_cells; v37 <= width_cells; arg3d = width_cells )
      {
        v38 = (double)arg2a - (double)arg3d * 0.5;
        v39 = &self->primary_samples[v35];
        if ( v34 == self->segment_count )
        {
          v59 = v38 * v39[-1].transform.basis_right.x;
          v60 = v38 * v39[-1].transform.basis_right.y;
          v81 = v39[-1].transform.position.z + 1.0;
          v67 = v39[-1].transform.position.x + v59;
          v6 = 0;
          v69 = v39[-1].transform.position.y + v60;
          v41 = &vertices[v37 + v34 * (width_cells + 1)].x;
          v42 = v81 + v38 * v39[-1].transform.basis_right.z;
          *v41 = v67;
          v41[1] = v69;
          v71 = v42;
          v41[2] = v71;
        }
        else
        {
          v62 = v38 * v39->transform.basis_right.x;
          v64 = v38 * v39->transform.basis_right.y;
          v74 = v62 + v39->transform.position.x;
          v77 = v64 + v39->transform.position.y;
          v80 = v38 * v39->transform.basis_right.z + v39->transform.position.z;
          v40 = &vertices[v37 + v34 * (width_cells + 1)].x;
          *v40 = v74;
          v40[1] = v77;
          v40[2] = v80;
        }
        width_cells = self->width_cells;
        arg2a = ++v37;
      }
      ++v34;
      ++v35;
    }
    while ( v34 <= (signed int)self->segment_count );
  }
  v43 = 0;
  if ( (int)self->segment_count > 0 )
  {
    while ( 1 )
    {
      arg2b = 0;
      if ( (int)self->width_cells > 0 )
      {
        arg3e = (double)(v43 % 8) * 0.125;
        v51 = (double)(v43 % 8 + 1) * 0.125;
        do
        {
          v44 = 0;
          v57 = v6 + 1;
          v54 = 0;
          arg2c = (double)arg2b * 0.125;
          v49 = (double)(v6 + 1) * 0.125;
          while ( 1 )
          {
            v45 = (uint32_t)facequads + 96 * v6 + 96 * v43 * self->width_cells + 48 * v44;
            *(_WORD *)v45 = 0;
            if ( v44 )
            {
              *(_WORD *)(v45 + 2) = v43 * (LOWORD(self->width_cells) + 1) + v6 + 1;
              *(_WORD *)(v45 + 4) = v6 + v43 * (LOWORD(self->width_cells) + 1);
              *(_WORD *)(v45 + 6) = v6 + (v43 + 1) * (LOWORD(self->width_cells) + 1);
              *(_WORD *)(v45 + 8) = (v43 + 1) * (LOWORD(self->width_cells) + 1) + v6 + 1;
              *(_DWORD *)(v45 + 12) = get_or_create_texture_ref((TextureRefList *)dword_4B7790, v93, 0, 0);
              *(float *)(v45 + 16) = v49;
              *(float *)(v45 + 20) = arg3e;
              *(float *)(v45 + 24) = arg2c;
              *(float *)(v45 + 28) = arg3e;
              *(float *)(v45 + 32) = arg2c;
              *(float *)(v45 + 36) = v51;
              *(float *)(v45 + 40) = v49;
            }
            else
            {
              *(_WORD *)(v45 + 2) = v6 + v43 * (LOWORD(self->width_cells) + 1);
              *(_WORD *)(v45 + 4) = v43 * (LOWORD(self->width_cells) + 1) + v6 + 1;
              *(_WORD *)(v45 + 6) = (v43 + 1) * (LOWORD(self->width_cells) + 1) + v6 + 1;
              *(_WORD *)(v45 + 8) = v6 + (v43 + 1) * (LOWORD(self->width_cells) + 1);
              *(_DWORD *)(v45 + 12) = get_or_create_texture_ref((TextureRefList *)dword_4B7790, texture_b, 0, 0);
              *(float *)(v45 + 16) = arg2c;
              *(float *)(v45 + 20) = arg3e;
              *(float *)(v45 + 24) = v49;
              *(float *)(v45 + 28) = arg3e;
              *(float *)(v45 + 32) = v49;
              *(float *)(v45 + 36) = v51;
              *(float *)(v45 + 40) = arg2c;
            }
            *(float *)(v45 + 44) = v51;
            if ( ++v54 >= 2 )
              break;
            v44 = v54;
          }
          ++v6;
          arg2b = v57;
        }
        while ( v57 < (signed int)self->width_cells );
      }
      if ( ++v43 >= (signed int)self->segment_count )
        break;
      v6 = 0;
    }
  }
  return finalize_path_template_record(self);
}

