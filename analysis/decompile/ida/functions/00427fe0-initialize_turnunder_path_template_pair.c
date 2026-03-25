/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_turnunder_path_template_pair @ 0x427fe0 */
/* selector: initialize_turnunder_path_template_pair */

int32_t __thiscall initialize_turnunder_path_template_pair(
        PathTemplate *self,
        float arg2,
        int32_t arg3,
        char *texture_a,
        char *texture_b)
{
  signed int v6; // ebx
  double v7; // st7
  int v8; // edi
  int v9; // edi
  int v10; // ecx
  int v11; // ebx
  double v12; // st7
  PathTemplateSample *primary_samples; // edi
  double v14; // st7
  Vec4 *p_basis_up; // eax
  PathTemplateSample *v16; // edx
  float *p_x; // eax
  double v18; // st7
  PathTemplateSample *v19; // ecx
  double v20; // st7
  double v21; // st6
  Vec4 *p_position; // eax
  int v23; // edi
  PathTemplateSample *v24; // ecx
  float *v25; // eax
  double v26; // st7
  PathTemplateSample *secondary_samples; // edx
  float *v28; // eax
  double v29; // st7
  Vec3 *p_delta_dir_to_next; // ecx
  Vec3 *v31; // ecx
  PathTemplateStripMesh *strip_mesh; // eax
  Vec3 *vertices; // ebx
  signed int v34; // edx
  int v35; // esi
  signed int width_cells; // ecx
  signed int v37; // edi
  double v38; // st7
  PathTemplateSample *v39; // eax
  float *v40; // eax
  float v41; // ecx
  double v42; // st7
  signed int i; // edi
  int v44; // esi
  int v45; // ecx
  ObjectFaceQuad *v46; // ebx
  float v48; // [esp+0h] [ebp-68h]
  float v49; // [esp+0h] [ebp-68h]
  float v50; // [esp+0h] [ebp-68h]
  int v51; // [esp+14h] [ebp-54h]
  float v52; // [esp+14h] [ebp-54h]
  float v53; // [esp+18h] [ebp-50h]
  float v54; // [esp+18h] [ebp-50h]
  float v55; // [esp+1Ch] [ebp-4Ch]
  int v56; // [esp+1Ch] [ebp-4Ch]
  ObjectFaceQuad *facequads; // [esp+20h] [ebp-48h]
  float v58; // [esp+24h] [ebp-44h]
  float v59; // [esp+24h] [ebp-44h]
  float v60; // [esp+24h] [ebp-44h]
  float v61; // [esp+24h] [ebp-44h]
  signed int v62; // [esp+24h] [ebp-44h]
  Vec3 *v63; // [esp+28h] [ebp-40h]
  float v64; // [esp+2Ch] [ebp-3Ch]
  float v65; // [esp+2Ch] [ebp-3Ch]
  float v66; // [esp+2Ch] [ebp-3Ch]
  float v67; // [esp+30h] [ebp-38h]
  float v68; // [esp+30h] [ebp-38h]
  float v69; // [esp+34h] [ebp-34h]
  float v70; // [esp+34h] [ebp-34h]
  float v71; // [esp+38h] [ebp-30h]
  float v72; // [esp+38h] [ebp-30h]
  float v73; // [esp+38h] [ebp-30h]
  float v74; // [esp+3Ch] [ebp-2Ch]
  float v75; // [esp+3Ch] [ebp-2Ch]
  float v76; // [esp+3Ch] [ebp-2Ch]
  float v77; // [esp+40h] [ebp-28h]
  float v78; // [esp+40h] [ebp-28h]
  float v79; // [esp+40h] [ebp-28h]
  float v80; // [esp+44h] [ebp-24h]
  float v81; // [esp+48h] [ebp-20h]
  float v82; // [esp+48h] [ebp-20h]
  float v83; // [esp+4Ch] [ebp-1Ch]
  float v84; // [esp+50h] [ebp-18h]
  float v85; // [esp+54h] [ebp-14h]
  float v86; // [esp+64h] [ebp-4h]
  float arg2a; // [esp+6Ch] [ebp+4h]
  int arg2b; // [esp+6Ch] [ebp+4h]
  int arg2c; // [esp+6Ch] [ebp+4h]
  float arg2d; // [esp+6Ch] [ebp+4h]
  int32_t arg3a; // [esp+70h] [ebp+8h]
  int32_t arg3b; // [esp+70h] [ebp+8h]
  int32_t arg3c; // [esp+70h] [ebp+8h]
  int32_t arg3d; // [esp+70h] [ebp+8h]
  float arg3e; // [esp+70h] [ebp+8h]
  char *v96; // [esp+7Ch] [ebp+14h]

  v6 = 0;
  self->kind = PATH_TEMPLATE_KIND_TURNUNDER_TOAD_FAMILY;
  self->is_mirrored_x = 0;
  self->side_exit_mode = 0;
  self->width_cells = arg3;
  v51 = (__int64)(arg2 * 6.2831855);
  self->width_or_scale = 1.0;
  self->segment_count = v51 + 8;
  self->segment_count_f = (float)(v51 + 8);
  v7 = (double)v51;
  v53 = v7;
  arg2a = v7 * 0.15915494;
  allocate_path_nodes(self);
  self->special_runtime_flag_9c = 0;
  arg3a = 0;
  v8 = 0;
  do
  {
    self->primary_samples[v8].center_x = -((double)(int)self->width_cells * 0.5 - 4.0);
    self->primary_samples[v8].rotation_scalar_98 = 0.0;
    self->primary_samples[v8].rotation_scalar_94 = 0.0;
    self->primary_samples[v8].special_scalar = 0.0;
    self->primary_samples[v8].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v8].transform);
    self->primary_samples[v8].transform.position.x = self->primary_samples[v8].center_x;
    v58 = (float)arg3a;
    self->primary_samples[v8].transform.position.y = 0.0;
    self->primary_samples[v8].transform.position.z = v58;
    self->primary_samples[v8].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[v8].transform);
    self->secondary_samples[v8].transform.position.x = self->primary_samples[v8].center_x;
    self->secondary_samples[v8].transform.position.y = 0.49000001;
    self->secondary_samples[v8++].transform.position.z = v58;
    self->secondary_samples[v8 - 1].delta_length = 1.0;
    ++arg3a;
  }
  while ( v8 < 6 );
  arg3b = v51 + 6;
  v9 = v51 + 6;
  do
  {
    self->primary_samples[v9].center_x = -(4.0 - (double)(int)self->width_cells * 0.5);
    self->primary_samples[v9].rotation_scalar_98 = 0.0;
    self->primary_samples[v9].rotation_scalar_94 = 0.0;
    self->primary_samples[v9].special_scalar = 0.0;
    self->primary_samples[v9].lateral_scale = 1.0;
    set_matrix_identity(&self->primary_samples[v9].transform);
    v59 = (float)arg3b;
    self->primary_samples[v9].transform.position.x = self->primary_samples[v9].center_x;
    self->primary_samples[v9].transform.position.y = 0.0;
    self->primary_samples[v9].transform.position.z = v59;
    self->primary_samples[v9].delta_length = 1.0;
    set_matrix_identity(&self->secondary_samples[v9].transform);
    self->secondary_samples[v9].transform.position.x = self->primary_samples[v9].center_x;
    self->secondary_samples[v9].transform.position.y = 0.49000001;
    self->secondary_samples[v9].transform.position.z = v59;
    self->secondary_samples[v9++].delta_length = 1.0;
    v10 = ++arg3b + -6 - v51;
  }
  while ( v10 < 2 );
  arg3c = 0;
  if ( v51 > 0 )
  {
    v11 = 6;
    do
    {
      v12 = (double)arg3c;
      v55 = v12 * -6.2831855 / v53;
      self->primary_samples[v11].center_x = (self->primary_samples[v51 + 6].center_x - self->primary_samples->center_x)
                                          * v12
                                          / v53
                                          + self->primary_samples->center_x;
      self->primary_samples[v11].rotation_scalar_98 = 0.0;
      self->primary_samples[v11].rotation_scalar_94 = 0.0;
      self->primary_samples[v11].special_scalar = 0.0;
      self->primary_samples[v11].lateral_scale = 1.0;
      set_matrix_identity(&self->primary_samples[v11].transform);
      primary_samples = self->primary_samples;
      v48 = v55 * 0.5;
      v60 = sine(v48);
      v14 = sine(v55);
      self->primary_samples[v11].transform.position.x = primary_samples[v11].center_x - (v14 * v60 + v14 * v60);
      self->primary_samples[v11].transform.position.z = (float)(arg3c + 6);
      self->primary_samples[v11].transform.position.y = (arg2a - cosine(v55) * arg2a) * -0.2;
      v49 = sine(v55) * 1.0471976;
      v61 = cosine(v49);
      v50 = sine(v55) * 1.0471976;
      v64 = -sine(v50);
      p_basis_up = &self->primary_samples[v11].transform.basis_up;
      p_basis_up->x = v64;
      p_basis_up->y = v61;
      p_basis_up->z = 0.0;
      v16 = self->primary_samples;
      p_x = &v16[v11].transform.basis_forward.x;
      v71 = v16[v11].transform.position.x - v16[v11 - 1].transform.position.x;
      v74 = v16[v11].transform.position.y - v16[v11 - 1].transform.position.y;
      v18 = v16[v11].transform.position.z - v16[v11 - 1].transform.position.z;
      *p_x = v71;
      p_x[1] = v74;
      v77 = v18;
      p_x[2] = v77;
      normalize_vector((Vec3 *)&self->primary_samples[v11].transform.basis_forward);
      cross_vectors(
        (Vec3 *)&self->primary_samples[v11],
        (Vec3 *)&self->primary_samples[v11].transform.basis_up,
        (Vec3 *)&self->primary_samples[v11].transform.basis_forward);
      qmemcpy(&self->secondary_samples[v11], &self->primary_samples[v11], 0x40u);
      v19 = self->primary_samples;
      v20 = v19[v11].transform.basis_up.x * 0.49000001;
      v81 = v19[v11].transform.basis_up.y * 0.49000001;
      v21 = v19[v11].transform.basis_up.z * 0.49000001;
      p_position = &self->secondary_samples[v11++].transform.position;
      v83 = v21;
      p_position->x = v20 + p_position->x;
      p_position->y = v81 + p_position->y;
      p_position->z = v83 + p_position->z;
      ++arg3c;
    }
    while ( arg3c < v51 );
    v6 = 0;
  }
  if ( (signed int)(self->segment_count - 1) > 0 )
  {
    v23 = 0;
    do
    {
      v24 = self->primary_samples;
      v25 = &v24[v23].delta_dir_to_next.x;
      v72 = v24[v23 + 1].transform.position.x - v24[v23].transform.position.x;
      v75 = v24[v23 + 1].transform.position.y - v24[v23].transform.position.y;
      v26 = v24[v23 + 1].transform.position.z - v24[v23].transform.position.z;
      *v25 = v72;
      v25[1] = v75;
      v78 = v26;
      v25[2] = v78;
      self->primary_samples[v23].delta_length = normalize_vector(&self->primary_samples[v23].delta_dir_to_next);
      secondary_samples = self->secondary_samples;
      v28 = &secondary_samples[v23].delta_dir_to_next.x;
      v65 = secondary_samples[v23 + 1].transform.position.x - secondary_samples[v23].transform.position.x;
      v67 = secondary_samples[v23 + 1].transform.position.y - secondary_samples[v23].transform.position.y;
      v29 = secondary_samples[v23 + 1].transform.position.z - secondary_samples[v23].transform.position.z;
      *v28 = v65;
      v28[1] = v67;
      v69 = v29;
      v28[2] = v69;
      ++v6;
      self->secondary_samples[v23].delta_length = normalize_vector(&self->secondary_samples[v23].delta_dir_to_next);
      ++v23;
    }
    while ( v6 < (signed int)(self->segment_count - 1) );
  }
  p_delta_dir_to_next = &self->primary_samples[self->segment_count - 1].delta_dir_to_next;
  p_delta_dir_to_next->x = 0.0;
  p_delta_dir_to_next->y = 0.0;
  p_delta_dir_to_next->z = 1.0;
  self->primary_samples[self->segment_count - 1].delta_length = 1.0;
  v31 = &self->secondary_samples[self->segment_count - 1].delta_dir_to_next;
  v31->x = 0.0;
  v31->y = 0.0;
  v31->z = 1.0;
  self->secondary_samples[self->segment_count - 1].delta_length = 1.0;
  request_object_vertices(self->strip_mesh, (self->segment_count + 1) * (self->width_cells + 1));
  request_object_facequads(self->strip_mesh, 2 * self->segment_count * self->width_cells);
  strip_mesh = self->strip_mesh;
  vertices = strip_mesh->vertices;
  facequads = strip_mesh->facequads;
  v34 = 0;
  v63 = vertices;
  if ( (self->segment_count & 0x80000000) == 0 )
  {
    v35 = 0;
    do
    {
      width_cells = self->width_cells;
      v37 = 0;
      arg2b = 0;
      for ( arg3d = width_cells; v37 <= width_cells; arg2b = v37 )
      {
        v38 = (double)arg2b - (double)arg3d * 0.5;
        v39 = &self->primary_samples[v35];
        if ( v34 == self->segment_count )
        {
          vertices = v63;
          v84 = v38 * v39[-1].transform.basis_right.x;
          v85 = v38 * v39[-1].transform.basis_right.y;
          v42 = v38 * v39[-1].transform.basis_right.z;
          v86 = v39[-1].transform.position.z + 1.0;
          v66 = v39[-1].transform.position.x + v84;
          v68 = v39[-1].transform.position.y + v85;
          v40 = &v63[v37 + v34 * (width_cells + 1)].x;
          *v40 = v66;
          v70 = v86 + v42;
          v40[1] = v68;
          v41 = v70;
        }
        else
        {
          v80 = v38 * v39->transform.basis_right.x;
          v82 = v38 * v39->transform.basis_right.y;
          v73 = v80 + v39->transform.position.x;
          v76 = v82 + v39->transform.position.y;
          v79 = v38 * v39->transform.basis_right.z + v39->transform.position.z;
          v40 = &vertices[v37 + v34 * (width_cells + 1)].x;
          *v40 = v73;
          v40[1] = v76;
          v41 = v79;
        }
        v40[2] = v41;
        width_cells = self->width_cells;
        ++v37;
        arg3d = width_cells;
      }
      ++v34;
      ++v35;
    }
    while ( v34 <= (signed int)self->segment_count );
  }
  for ( i = 0; i < (signed int)self->segment_count; ++i )
  {
    v44 = 0;
    arg2c = 0;
    if ( (int)self->width_cells > 0 )
    {
      arg3e = (double)(i % 8) * 0.125;
      v54 = (double)(i % 8 + 1) * 0.125;
      do
      {
        v45 = 0;
        v62 = v44 + 1;
        v56 = 0;
        arg2d = (double)arg2c * 0.125;
        v52 = (double)(v44 + 1) * 0.125;
        while ( 1 )
        {
          v46 = &facequads[2 * v44 + 2 * i * self->width_cells + v45];
          v46->flags = 0;
          if ( v45 )
          {
            v46->vertex_index_a = i * (LOWORD(self->width_cells) + 1) + v44 + 1;
            v46->vertex_index_b = v44 + i * (LOWORD(self->width_cells) + 1);
            v46->vertex_index_c = v44 + (i + 1) * (LOWORD(self->width_cells) + 1);
            v46->vertex_index_d = (i + 1) * (LOWORD(self->width_cells) + 1) + v44 + 1;
            v46->texture_ref = get_or_create_texture_ref((TextureRefList *)dword_4B7790, v96, 0, 0);
            v46->u0 = v52;
            v46->v0 = arg3e;
            v46->u1 = arg2d;
            v46->v1 = arg3e;
            v46->u2 = arg2d;
            v46->v2 = v54;
            v46->u3 = v52;
          }
          else
          {
            v46->vertex_index_a = v44 + i * (LOWORD(self->width_cells) + 1);
            v46->vertex_index_b = i * (LOWORD(self->width_cells) + 1) + v44 + 1;
            v46->vertex_index_c = (i + 1) * (LOWORD(self->width_cells) + 1) + v44 + 1;
            v46->vertex_index_d = v44 + (i + 1) * (LOWORD(self->width_cells) + 1);
            v46->texture_ref = get_or_create_texture_ref((TextureRefList *)dword_4B7790, texture_b, 0, 0);
            v46->u0 = arg2d;
            v46->v0 = arg3e;
            v46->u1 = v52;
            v46->v1 = arg3e;
            v46->u2 = v52;
            v46->v2 = v54;
            v46->u3 = arg2d;
          }
          v46->v3 = v54;
          if ( ++v56 >= 2 )
            break;
          v45 = v56;
        }
        ++v44;
        arg2c = v62;
      }
      while ( v62 < (signed int)self->width_cells );
    }
  }
  return finalize_path_template_record(self);
}

